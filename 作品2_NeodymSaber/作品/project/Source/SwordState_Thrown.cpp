#include "SwordState_Thrown.h"
#include "Sword_Throw.h"
#include "SwordValue.h"
#include "Player.h"
#include "StageManager.h"
#include "Camera.h"
#include "CommonFunc_SwordState.h"

void SwordState_Thrown::Update()
{
	if (elapsedTime == 0)
		firstPos = parent->GetPos();
	elapsedTime += Time::GameDeltaTime();

	Player* player = parent->GetParent();
	CommonFunc_SwordState swFunc;
	if (VSize(parent->GetPos() - player->GetPos()) > SWORD_THROW_FLY_DIST_LIMIT)
	{
		parent->ChangeState("ComeBack");
	}
	else
	{
		VECTOR swVel = parent->GetVelocity();
		Sword_Throw* sw_throw = dynamic_cast<Sword_Throw*>(parent);
		if (sw_throw != nullptr)
			swFunc.JudgeAndDoFall(parent->GetPos(), swVel.y, firstPos, sw_throw->GetTargetPos(), false);
		parent->SetVelocity(swVel);
	}

	// 背景オブジェクトとの当たり判定
	MV1_COLL_RESULT_POLY collResult = swFunc.IsCollStageObj(parent->GetPos(),
		parent->GetPos() + parent->GetVelocity() * Time::GameDeltaTime());
	if (collResult.HitFlag == TRUE)
	{
		nextStateName = "Pierced";
		parent->SetPos(collResult.HitPosition + collResult.Normal * SWORD_THROW_ADJUST_PIERCED_POS_Y);
		parent->SetVelocity(VZero);
	}
}

void SwordState_Thrown::End()
{
	if (nextStateName != "Pierced")
		parent->SetDefaultLocalRootPos();
	else
		parent->SetFrameLocalPos(SWORD_THROW_ROOT_NAME, SWORD_THROW_ADJUST_PIERCED_LOCAL_POS);
	parent->SetVelocityY(0);
}
