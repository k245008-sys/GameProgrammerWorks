#include "Camera.h"
#include "InputManager.h"
#include "Player.h"
#include "StageManager.h"
#include "Wall.h"
#include "MoveNum.h"
#include "CameraState_Normal.h"
#include "CameraState_Aim.h"
#include "CameraState_Debug.h"
#include "CameraState_Test.h"
#include "CameraState_Snap.h"
#include "CameraState_Attack.h"
#include "CameraState_Attract.h"
#include "CameraState_AttractAttack.h"
#include "CameraState_Avoid.h"
#include "CameraState_GameStart.h"
#include "CameraState_GameClear.h"
#include "CameraState_GameOver.h"
#include "Util.h"
#include "PlayerValue.h"

Camera::Camera()
{
	//ステート追加する時はここから追加
	stateManager = new StateManager("GameStart");
	stateManager->AddState("Normal", new CameraState_Nomal());
	stateManager->AddState("Aim", new CameraState_Aim());
	stateManager->AddState("Debug", new CameraState_Debug());
	stateManager->AddState("Test", new CameraState_Test());
	stateManager->AddState("Snap", new CameraState_Snap());
	stateManager->AddState("Attack", new CameraState_Attack());
	stateManager->AddState("Attract", new CameraState_Attract());
	stateManager->AddState("AttractAttack",new CameraState_AttractAttack());
	stateManager->AddState("Avoid", new CameraState_Avoid());
	stateManager->AddState("GameStart", new CameraState_GameStart());
	stateManager->AddState("GameClear", new CameraState_GameClear());
	stateManager->AddState("GameOver", new CameraState_GameOver());

	inputManager = nullptr;
	player = nullptr;
	stageManager = nullptr;

	transform.position = CAMERA_DEF_POS;
	posGoal = CAMERA_DEF_POS;
	normalTarget = CAMERA_DEF_TARGET_POS;
	aimTarget = CAMERA_DEF_TARGET_POS;
	targetGoal = CAMERA_DEF_TARGET_POS;
	collHitPos = VGet(0.0f, 0.0f, 0.0f);
	collAdjustPos = VGet(0.0f, 0.0f, 0.0f);
	transGoalPos = posGoal;
	delayPos = VGet(0.0f, 0.0f, 0.0f);

	direction = MGetIdent();

	isHit = false;
	isCollision = false;
	isDelay = false;
	
	nowState = "NULL";
	beforeState = "NULL";

	shakePos = VGet(0.0f, 0.0f, 0.0f);
	shakeLength = VGet(0.0f, 0.0f, 0.0f);
	shakeRangeMax = VGet(0.0f, 0.0f, 0.0f);
	shakeRangeMin = VGet(0.0f, 0.0f, 0.0f);
	shakeSpeed = VGet(0.0f, 0.0f, 0.0f);
	shakeSign = VGet(1, 1, 1);

	shakeCounter = 0.0f;
	shakeTime = 0.0f;
	transSpeed = 0.0f;
	
	isShakeing = false;

	resetRotasionY = 0.0f;
	resetSpeed = 0.0f;
	isRotReset = false;
	
	//プレイヤー用
	pRot = VGet(0.0f, 0.0f, 0.0f);
}

Camera::~Camera()
{
	if(stateManager != nullptr)
	delete stateManager;
}

void Camera::Update()
{
	direction = MGetRotZXY(transform.rotation);
	
	//ステートの判定
	jugeState();

	//一つ前のステートを記憶
	RecordToBeforeStateName();

	//カメラの角度のリセット
	ResetCameraRot();

	TransitionDelay();
	
	//カメラベースでステートを動かす
	CameraBase::Update();

#ifdef _DEBUG
	if (inputManager->IsKeyPushDown("Q"))
	{
		if (isCollision == false)
		{
			isCollision = true;
		}
		else
		{
			isCollision = false;
		}
		
	}

	if (inputManager->IsKeyPushDown("M"))
	{
		SetShakeCamera(CAMERA_SHAKE_RANGE_PLAYER_ATTRACT_SNAP_ENEMY,
			CAMERA_SHAKE_SPEED_PLAYER_ATTRACT_SNAP_ENEMY, CAMERA_SHAKE_TIME_PLAYER_ATTRACT_SNAP_ENEMY);
	}

#endif
	
	if (isCollision == true)
	{
		//ステージとの判定
		CameraToPlayerLineStageColider();
	}
	
	if (GetCurrentStateName() != "Debug")
	{
		//カメラの角度の制限
		LimitAngle();
	}

	//カメラの振動
	ShakeCamera();
	
	//位置と注視点をセット
	SetCameraPositionAndTarget_UpVecY(transform.position + shakePos * MGetRotZXY(transform.rotation), normalTarget + shakePos *  MGetRotZXY(transform.rotation));
}

void Camera::Draw()
{
	CameraBase::Draw();
}

void Camera::RotationCamera()
{
	/*視点の速度
	Y(横)回転の速度 += スティックの横入力の割合 * スティックの入力上限値
	X(縦)回転の速度 += スティックの縦入力の割合 * スティックの入力上限値
	*/

	//カメラの横回転だからY軸で回す。
	transform.rotation.y += (inputManager->GetStickOrKeyPos("R").x / (float)STICK_INPUT_MAX) * CAMERA_ROTATION_SPEED_MAX.x;

	//カメラの縦回転だからX軸で回す。
	transform.rotation.x += (inputManager->GetStickOrKeyPos("R").y / (float)STICK_INPUT_MAX) * CAMERA_ROTATION_SPEED_MAX.y;
}

void Camera::ResetCamera()
{
	//リスタートのセット系
	transform.rotation = VZero;
	transform.position = PLAYER_START_POS + CAMERA_DEF_POS;
	posGoal = transform.position;
	normalTarget = PLAYER_START_POS + CAMERA_DEF_TARGET_POS;
	delayPos = VGet(0.0f, 0.0f, 0.0f);
	targetGoal = normalTarget;
	transGoalPos = posGoal;
	SetIsCollision(true);
	stateManager->ChangeCurrentStateOnce("GameStart");
}

void Camera::ResetCameraRot()
{
	using namespace Util;

	if (isRotReset == true)
	{
		float target = resetRotasionY;
		//向きを抽出
		NormalizeAngle(target);
		NormalizeAngle(transform.rotation.y);
		//どれだけ離れているか距離を抽出
		float diff = target - transform.rotation.y;
		//180度を超えているかどうか
		bool over = (fabsf(diff) > DEGREE * 180);
		MoveNum move;

		if (over)
		{
			if (GetSign(diff) == 1)
			{
				//右回転させる
				transform.rotation.y -= resetSpeed * Time::GameDeltaTime();
				if (transform.rotation.y < DEGREE * -180)
				{
					NormalizeAngle(transform.rotation.y);
					if (transform.rotation.y < resetRotasionY)
						transform.rotation.y = resetRotasionY;
				}
			}
			else
			{
				//左回転させる
				transform.rotation.y += resetSpeed * Time::GameDeltaTime();
				if (transform.rotation.y > DEGREE * 180)
				{
					NormalizeAngle(transform.rotation.y);
					if (transform.rotation.y > resetRotasionY)
						transform.rotation.y = resetRotasionY;
				}
			}
		}
		else if (move.MoveToTarget(transform.rotation.y, resetSpeed * Time::GameDeltaTime(), target) == true)
		{
				isRotReset = false;
		}
	}
}

void Camera::AssignFindObjToField()
{
	inputManager = SceneManager::CommonScene()->FindGameObject<InputManager>();
	player = FindGameObject<Player>();
	stageManager = FindGameObject<StageManager>();
}

void Camera::SetShakeCamera(VECTOR _shakeRangeMax, VECTOR _shakeSpeed, float _shakeTime)
{
	//カメラの振動に必要な情報をセット
	isShakeing = true;
	shakeCounter = 0.0f;
	shakeRangeMax = _shakeRangeMax;
	shakeSpeed = _shakeSpeed;
	shakeTime = _shakeTime;
}

void Camera::SetCenterToPlayer(VECTOR _targetGoal, VECTOR _posGoal,  VECTOR _rotation)
{
	//引数を角度を中心に行きたい位置までのベクトルを作る
	normalTarget = GetTransGoalPos(player->GetPos(), _posGoal, MGetRotZXY(_rotation));

	//引数を角度を中心に行きたい位置までのベクトルを作る
	transform.position = GetTransGoalPos(player->GetPos(), _posGoal, MGetRotZXY(_rotation));
}

void Camera::SetRestRot(float _speed, float _rotY, bool _isReset)
{
	//カメラの回転のリセットに必要な情報をセット
	resetSpeed = _speed;
	resetRotasionY = _rotY;
	isRotReset = _isReset;
}

VECTOR Camera::GetAimTarget()
{
	//Aim用の位置をPlayerの位置から伸ばしてベクトルを作る
	aimTarget = VTransform(CAMERA_SWORD_AIM_POS, direction);
	aimTarget = (aimTarget + player->GetPos());

	return aimTarget;
}

void Camera::jugeState()
{
	//ゲームが始まるまでは判定をしない
	if (stateManager->GetCurrentStateName() != "GameStart")
	{
		//プレイヤーの各ステートに合わせカメラのステートを変更
		if (player->GetCurrentStateName() == "Aim")
		{
			stateManager->ChangeCurrentStateOnce("Aim");
		}
		else if (player->GetCurrentStateName() == "Attack")
		{
			stateManager->ChangeCurrentStateOnce("Attack");
		}
		else if (player->GetCurrentStateName() == "Attract")
		{
			stateManager->ChangeCurrentStateOnce("Attract");
		}
		else if (player->GetCurrentStateName() == "AttractAttack")
		{
			stateManager->ChangeCurrentStateOnce("AttractAttack");
		}
		else if (player->GetCurrentStateName() == "Snap")
		{
			stateManager->ChangeCurrentStateOnce("Snap");
		}
		else if (player->GetCurrentStateName() == "Avoid")
		{
			stateManager->ChangeCurrentStateOnce("Avoid");
		}
		else if (player->GetCurrentStateName() == "Clear")
		{
			stateManager->ChangeCurrentStateOnce("GameClear");
		}
		else if (player->GetCurrentStateName() == "Dead")
		{
			stateManager->ChangeCurrentStateOnce("GameOver");
		}
		else
		{
			//Cameraで設定しないステートはNormalにする
			if (stateManager->GetCurrentStateName() != "Debug")
			{
				stateManager->ChangeCurrentStateOnce("Normal");
			}
		}
	}

#ifdef _DEBUG

	if (inputManager->IsKeyPushDown("Z"))
	{
		if (stateManager->GetCurrentStateName() == "Normal")
		{
			stateManager->ChangeCurrentStateOnce("Debug");
		}
		else
		{
			stateManager->ChangeCurrentStateOnce("Normal");
		}
	}

#endif

	/*
	if (inputManager->IsKeyPushDown("T"))
	{
		nextStateName = "Test";
	}
	*/
}

void Camera::ShakePosSign()
{
	//シェイク反転処理
	if (shakePos.x < -shakeLength.x / 2 || shakePos.x > shakeLength.x / 2)
	{
		//Randによる変化
		shakeLength.x = shakeRangeMax.x;
		shakeSign.x *= -1; //座標反転
	}

	//上の反転処理のY座標版
	if (shakePos.y < -shakeLength.y / 2 || shakePos.y > shakeLength.y / 2)
	{
		shakeLength.y = shakeRangeMax.y;
		shakeSign.y *= -1;
	}

	//奥行の反転処理のY座標版
	if (shakePos.z < -shakeLength.z / 2 || shakePos.z > shakeLength.z / 2)
	{
		shakeLength.z = shakeRangeMax.z;
		shakeSign.z *= -1;
	}
}

void Camera::ShakePosRimit()
{
	//範囲外に出た時に範囲内に収まるように
	if (shakePos.x > shakeLength.x / 2)
	{
		shakePos.x = shakeLength.x / 2;
	}
	else if (shakePos.x < -shakeLength.x / 2)
	{
		shakePos.x = -shakeLength.x / 2;
	}

	if (shakePos.y > shakeLength.y / 2)
	{
		shakePos.y = shakeLength.y / 2;
	}
	else if (shakePos.y < -shakeLength.y / 2)
	{
		shakePos.y = -shakeLength.y / 2;
	}

	if (shakePos.z > shakeLength.z / 2)
	{
		shakePos.z = shakeLength.z / 2;
	}
	else if (shakePos.z < -shakeLength.z / 2)
	{
		shakePos.z = -shakeLength.z / 2;
	}
}

void Camera::LimitAngle()
{
	//X軸の上限設定
	if (transform.rotation.x >= CAMERA_ROTATION_MAX.x)
	{
		transform.rotation.x = CAMERA_ROTATION_MAX.x;
	}//Y軸の上限設定
	else if (transform.rotation.x <= CAMERA_ROTATION_MIN.x)
	{
		transform.rotation.x = CAMERA_ROTATION_MIN.x;
	}
}

void Camera::ShakeCamera()
{
	if (isShakeing == true)
	{
		shakeCounter += Time::GameDeltaTime();

		shakePos += shakeSpeed * shakeSign;

		//座標の反転処理
		ShakePosSign();

		//座標の範囲制限
		ShakePosRimit();

		//この関数の終了条件
		if (shakeCounter > shakeTime)
		{
			isShakeing = false;
			shakeCounter = 0;
			shakePos = VGet(0.0f, 0.0f, 0.0f);
			return;
		}
	}
}

bool Camera::CameraToPlayerLineStageColider()
{
	//カメラからプレイヤーのステージとの線分当たり判定
	for (auto& stage : stageManager->GetCollsionObjects())
	{
		//MV1RefreshCollInfo = モデルの判定情報を更新する
		MV1RefreshCollInfo(stage->GetModel());
		//MV1CollCheck_Line = 線分の当たり判定
		MV1_COLL_RESULT_POLY coll = MV1CollCheck_Line(stage->GetModel(), -1, player->GetPos() + CAMERA_STAGE_COLL_ADUJUST_POS, transform.position + (VNorm(coll.HitPosition - player->GetPos()) * CAMERA_COLL_ADJUST_LENGTH));

		isHit = false;
		
		if (coll.HitFlag == TRUE)
		{
			isHit = true;
			transform.position = coll.HitPosition -= (VNorm(coll.HitPosition - player->GetPos()) * CAMERA_COLL_ADJUST_LENGTH);
			return true;
		}	
	}
	return false;
}

//カメラの各クラスで座標を既定の位置に移動させる関数
bool Camera::TransitionPos(VECTOR _goalPos, VECTOR& _transPos, float _TransSpeed)
{
	//遷移から座標がずれていたらその位置まで修正
	MoveNum moveNum;
	if (moveNum.MoveVector(_transPos, _TransSpeed, GetTransGoalPos(delayPos, _goalPos, direction)) == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Camera::TransitionDelay()
{
	float velocity = VSize(player->GetVelocity());

	//速度が一定以下の場合最低速度をいれる。
	if (velocity < CAMERA_DELAY_UNDER_RIMIT_SPEED)
	{
		velocity = CAMERA_DELAY_UNDER_SPEED;
	}

	if (stateManager->GetCurrentStateName() == "Aim" ||
		stateManager->GetCurrentStateName() == "Snap")
	{
		delayPos = player->GetPos();
	}
	else
	{
		delayPos = player->GetDelayedPos();
	}
}


//カメラを既定の位置に置きPlayerに追従させる関数。
void Camera::FollowToPlayer(VECTOR _targetGoal, VECTOR _posGoal)
{
	//注視点ーーーーーーーーー

	//遷移した分を本体の変数に代入
	normalTarget = GetTransGoalPos(delayPos, _targetGoal, direction);


	//位置ーーーーーーーーーー

	//遷移した分を本体の変数に代入
	transform.position = GetTransGoalPos(delayPos, _posGoal, direction);
}

void Camera::RecordToBeforeStateName()
{
	//変数の変更がなければ関数を抜ける。
	if (nowState == stateManager->GetCurrentStateName())
	{
		return;
	}
	else
	{
		beforeState = nowState;
		nowState = stateManager->GetCurrentStateName();
		return;
	}
}

VECTOR Camera::GetTransGoalPos(VECTOR _startPos, VECTOR _goalPos, MATRIX _direction)
{
	//向きを基準に遷移先までのベクトルを作成
	transGoalPos = VTransform(_goalPos, _direction);
	//遷移をさせたい位置位置から遷移させる
	transGoalPos = (transGoalPos + _startPos);

	return transGoalPos;
}
