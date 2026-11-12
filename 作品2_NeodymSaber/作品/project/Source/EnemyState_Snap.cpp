#include "EnemyState_Snap.h"
#include "Sword_Throw.h"
#include "SwordValue.h"
#include "Player.h"
#include "EnemyBase.h"

void EnemyState_Snap::Update()
{
	parent->SetEnableGravity(false);
	EnemyState_SnapBase::Update();
	// ÔŒ•‚ÌŽ¥—Í”ÍˆÍ‚É‚¢‚È‚¢‚©‚ÂÂŒ•ˆø‚«Šñ‚¹‚ª‚È‚¢ŽžA‘Ò‹@ó‘Ô‚Ö
	Sword_Throw* sw_throw = player->GetSword_Throw();
	VECTOR distToSwThrow = sw_throw->GetPos()
		- parent->GetPos();
	if (sw_throw->GetCurrentStateName() == "Pierced"
		&& VSize(distToSwThrow) < SWORD_PIERCED_ATTRACT_DIST && parent->GetWhatAttracted() == "Throw")
		return;
	if (player->GetCurrentStateName() != "Attract")
		nextStateName = "Idle";
}

void EnemyState_Snap::End()
{
	EnemyState_SnapBase::End();
	if (parent == nullptr)
		return;
	parent->SetEnableGravity(true);
}
