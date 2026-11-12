#include "CharaBase.h"
#include "CollisionFunc.h"

#include "RoundShadow.h"
#include "Util.h"

CharaBase::CharaBase()
{
	roundShadow = nullptr;
	stageManager = nullptr;
	anim = nullptr;								
	isGround = false;
	adjustDownCollStartPos = VZero;
	isSnap = false;
	wasSnap = false;
	downCollSizeOnGround = 0;
	downCollSizeInAir = 0;
	adjustRayStartPosWall = VZero;
	wallCollSize = 0;
	shakePos = VZero;
	shakeVel = VZero;
	shakeRange = VZero;
	shakeTime = 0;
	enableGravity = true;
	adjustDrawPos = VZero;
}

CharaBase::~CharaBase()
{
	if (hModel > 0)
		MV1DeleteModel(hModel);
	if (roundShadow != nullptr)
	{
		delete roundShadow;
		roundShadow = nullptr;
	}
}

void CharaBase::Update()
{
	if (stateManager->GetCurrentStateName() != "Snap")
		isSnap = false;
	DynamicObjBase::Update();
	Gravity();
	WallCollision(adjustRayStartPosWall);
	GroundingCollision(downCollSizeOnGround);
	transform.position += velocity * Time::GameDeltaTime();
	roundShadow->SetPos(ShadowCollision() + VGet(0, CHARA_SHADOW_ADJUST_Y, 0));
	// 地面に着いたらY速度を無くす
	if (isGround)
		velocity.y = 0;
	ResetWasSnap();

	UpdateAnim();
	Shake();
}

void CharaBase::Draw()
{
	MATRIX mScale = MGetScale(transform.scale);
	MATRIX mRot = MGetRotZ(transform.rotation.z);
	mRot *= MGetRotX(transform.rotation.x);
	// ボーンを調整するとアニメーションに影響してしまうため、描画時の回転を調整
	mRot *= MGetRotY(transform.rotation.y + CHARA_ADJUST_DRAW_ROT_Y);
	MATRIX mTrans = MGetTranslate(transform.position + shakePos * mRot);
	MV1SetMatrix(hModel, mScale * mRot * mTrans);
	MV1DrawModel(hModel);
	stateManager->SetParentToCurrentState(this);
	if (stateManager != nullptr)
		stateManager->Draw();
}

void CharaBase::AssignFindObjToField()
{
	stageManager = FindGameObject<StageManager>();
}

void CharaBase::Gravity()
{
	if (!enableGravity)
		return;
	if (!isGround)
	{
		velocity.y -= GRAVITY;
		if (velocity.y < CHARA_VELOCITY_Y_MIN)
			velocity.y = CHARA_VELOCITY_Y_MIN;
	}
}

void CharaBase::WallCollision(const VECTOR& _adjustStartPos, const bool& _enableY)
{
	using namespace Util;

	// 判定の基準となる移動ベクトル
	VECTOR baseVel = velocity * Time::GameDeltaTime();
	if (!_enableY)
		baseVel.y = 0;
	if (VSize(baseVel) == 0)
		return;
	CollisionFunc coll;
	MV1_COLL_RESULT_POLY result;
	VECTOR startPos = transform.position + _adjustStartPos;
	VECTOR endPos = transform.position + baseVel;
	// 衝突が無ければ処理しない
	if (!coll.MinDistStageResult(result, startPos, endPos, true, stageManager))
		return;
	// 下向きの面なら移動しない
	VECTOR norm = result.Normal;
	ClampNorm(norm);
	if (norm.y < 0)
	{
		SetVelocity(VZero);
		return;
	}
	float size = CHARA_ADJUST_COLL_SIZE;
	VECTOR hitPos = result.HitPosition + norm * size;
	VECTOR toHit = hitPos - transform.position;
	if (fabsf(norm.y) <= 0.05f)
		toHit.y = 0;
	bool gravity = false;
	if (!_enableY && fabsf(norm.y) <= 0.05f && velocity.y < 0 && !isGround)
	{
		toHit.y = velocity.y * Time::GameDeltaTime();
		gravity = true;
	}
	// 衝突した面の反対向き
	VECTOR insideNorm = result.Normal * -1;
	ClampNorm(insideNorm);
	// 衝突点からめり込んだ判定終点へのベクトル
	VECTOR alongVel = endPos - hitPos;
	// めり込んだベクトルを当たった面に平行な正射影にして、面に沿うようにする
	alongVel -= insideNorm * VDot(alongVel, insideNorm);
	if (alongVel.y < 0)
		alongVel.y = 0;
	endPos = transform.position + toHit + alongVel;
	bool second = false;
	if (coll.MinDistStageResult(result, startPos, endPos, true, stageManager))
	{
		second = true;
		norm = result.Normal;
		ClampNorm(norm);
		hitPos = result.HitPosition + norm * size;

		toHit = hitPos - transform.position;
		if (fabsf(norm.y) <= 0.05f)
			toHit.y = 0;
		if(gravity)
			toHit.y = velocity.y * Time::GameDeltaTime();

		alongVel = endPos - hitPos;
		insideNorm = norm * -1;
		alongVel -= insideNorm * VDot(alongVel, insideNorm);
		if (alongVel.y < 0)
			alongVel.y = 0;
	}

	VECTOR setVel = toHit + alongVel;
	if (setVel.y > 0 && fabsf(norm.y) <= 0.1f && !second && stateManager->GetCurrentStateName() == "Snap")
		setVel.y = 0;
	setVel /= Time::GameDeltaTime();
	if (_enableY)
		isGround = true;
	SetVelocity(setVel);
}

void CharaBase::GroundingCollision(const float& _downCollSize)
{
	CollisionFunc coll;
	MV1_COLL_RESULT_POLY result;
	// 地面にいる間の足場判定
	if (isGround)
	{
		VECTOR startPos = GetPosAfterMove() + VGet(0, 20.0f, 0);
		VECTOR endPos = GetPosAfterMove() + VGet(0, -downCollSizeOnGround, 0);
		if (coll.MinDistStageResult(result, startPos, endPos))
		{
			float height = fabsf(transform.position.y - result.HitPosition.y);
			VECTOR norm = result.Normal;
			if (transform.position.y <= result.HitPosition.y &&
				height >= CHARA_COLL_GROUND_RISE_HEIGHT && norm.y >= 0.8f)
				transform.position.y = result.HitPosition.y;
			return;
		}
	}
	// 空中時の着地判定
	VECTOR velDelta = velocity * Time::GameDeltaTime();
	if (coll.MinDistStageResult(result, transform.position, transform.position + velDelta + VGet(0,-downCollSizeInAir,0)))
	{
		if (transform.position.y < result.HitPosition.y)
		{
			isGround = false;
			return;
		}
		if (result.Normal.y >= 0.6f)
		{
			if (transform.position != result.HitPosition)
			{
				velocity.y = result.HitPosition.y - transform.position.y;
				velocity.y /= Time::GameDeltaTime();
			}
			isGround = true;
			return;
		}
	}
	isGround = false;
}

void CharaBase::MovePosAndStageColl(const VECTOR& _targetPos)
{
	VECTOR beforeVel = velocity;
	VECTOR baseVel = (_targetPos - transform.position) / Time::GameDeltaTime();
	SetVelocity(baseVel);
	WallCollision(adjustRayStartPosWall, true);
	transform.position += velocity * Time::GameDeltaTime();
	velocity = beforeVel;
}

void CharaBase::ShakePos(const VECTOR& _velocity, const VECTOR& _range, const float& _time)
{
	shakeVel = _velocity;
	shakeRange = _range;
	shakeTime = _time;
}

void CharaBase::ResetWasSnap()
{
	// スナップ先に着いたらY速度を無くす
	if (wasSnap)
	{
		wasSnap = false;
		velocity.y = 0;
	}
}

VECTOR CharaBase::ShadowCollision()
{
	CollisionFunc coll;
	MV1_COLL_RESULT_POLY result;
	VECTOR startPos = transform.position + adjustDownCollStartPos;
	VECTOR endPos = startPos + VGet(0, -CHARA_SHADOW_COLLISION_SIZE, 0);
	if (coll.MinDistStageResult(result, startPos, endPos, false))
	{
		roundShadow->SetNorm(result.Normal);
		return result.HitPosition;
	}
	return endPos;
}

void CharaBase::Shake()
{
	if (shakeTime <= 0)
	{
		shakePos = VZero;
		return;
	}

	shakeTime -= Time::GameDeltaTime();
	MoveNum moveNum;
	if (moveNum.MoveToTarget(shakePos.x, shakeVel.x * Time::GameDeltaTime(), shakeRange.x))
		shakeRange.x *= -1;
	if (moveNum.MoveToTarget(shakePos.y, shakeVel.y * Time::GameDeltaTime(), shakeRange.y))
		shakeRange.y *= -1;
	if (moveNum.MoveToTarget(shakePos.z, shakeVel.z * Time::GameDeltaTime(), shakeRange.z))
		shakeRange.z *= -1;
}
