#include "EnemyState_Damage.h"
#include "EnemyBase.h"
#include "Player.h"
#include "CommonFunc_EnemyState.h"
#include <string>

void EnemyState_Damage::Update()
{
	bool dropped = (parent->GetCurrentAnim() == "Dropped") && (!parent->GetIsAnimFinish());
	if (!dropped && !playAnim)
	{
		int size = (int)(sizeof(ENEMY_ANIM_SETTING_DAMAGE) / sizeof(ENEMY_ANIM_SETTING_DAMAGE[0]));
		int rand = GetRand(size - 1) + 1;
		parent->PlayAnim("Damage" + std::to_string(rand));
		playAnim = true;
	}

	parent->MoveVelocityXZ(ENEMY_DAMAGE_REDUCE_KNOCK_BACK_SPEED_Z, VZero);
	parent->AddVelocityY(-ENEMY_DAMAGE_REDUCE_KNOCK_BACK_SPEED_Y);

	elapsedTime += Time::GameDeltaTime();
	if (elapsedTime >= parent->GetDamageTime() ||
		VSize(parent->GetVelocityXZ()) == 0)
		parent->ChangeStateOnce("Idle");
}

void EnemyState_Damage::End()
{
	playAnim = false;
	if (parent == nullptr)
		return;
	if (nextStateName == "Idle")
		parent->SetAnimBlendFrame("Idle", ENEMY_ANIM_AFTER_DAMAGE_IDLE_BLEND_FRAME);
	parent->SetReduceKnockBackSpeed(VGet(0, -ENEMY_DAMAGE_REDUCE_KNOCK_BACK_SPEED_Y, ENEMY_DAMAGE_REDUCE_KNOCK_BACK_SPEED_Z));
}
