#include "SwordState_Pierced.h"
#include "Sword_Throw.h"
#include "SwordValue.h"
#include "Player.h"
#include "EnemyManager.h"
#include "EffectValue.h"
#include "CommonFunc_CollDraw.h"
#include "SoundManager.h"
#include "SoundValue.h"

void SwordState_Pierced::Update()
{
	if (elapsedTime == 0)
	{
		attractDist = SWORD_PIERCED_ATTRACT_DIST;
		SoundManager* sound = SceneManager::CommonScene()->FindGameObject<SoundManager>();
		sound->Play("SwordPierce");
		effect->Create("AttractRangeRed", parent->GetPos(),parent->GetRot(),
			EFFECT_ATTRACT_RANGE_RED_SETTING.scale * attractDist);
	}

	parent->SetVelocity(VZero);
	effect->SetScale("AttractRangeRed", EFFECT_ATTRACT_RANGE_RED_SETTING.scale * attractDist);

	elapsedTime += Time::GameDeltaTime();
	Sword_Throw* sw_throw = dynamic_cast<Sword_Throw*>(parent);
	if (sw_throw != nullptr)
		sw_throw->ReduceAttractGaugeAmount(SWORD_THROW_ATTRACT_GAUGE_AMOUNT_MAX / SWORD_PIERCED_TIME / 60);
	Player* player = parent->GetParent();
	if (sw_throw->GetAttractGaugeAmount() <= 0 &&
		player->GetCurrentStateName() != "Snap")
		nextStateName = "ComeBack";

	EnemyManager* enemyManager = FindGameObject<EnemyManager>();
	for (auto& it : enemyManager->GetEnemies())
	{
		if (it->GetCurrentStateName() == "Snap" && it->GetWhatAttracted() == "Slash")
			continue;
		VECTOR dist = it->GetPos() - parent->GetPos();
		if (VSize(dist) < SWORD_PIERCED_ATTRACT_DIST)
		{
			it->SetWhatAttracted("Throw");
			it->Snap(parent->GetPos(), ENEMY_SNAP_JUDGE_FINISH_DIST_TO_SWORD_THROW);
		}
		else if (it->GetCurrentStateName() == "Snap" && it->GetWhatAttracted() == "Throw")
			it->ChangeStateOnce("Idle");
	}
}

void SwordState_Pierced::Draw()
{
	CommonFunc_CollDraw colllDraw;
	colllDraw.AttractRange_Red(parent->GetPos());
}

void SwordState_Pierced::End()
{
	parent->SetDefaultLocalRootPos();
	effect->Delete("AttractRangeRed");
}
