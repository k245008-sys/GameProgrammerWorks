#include "EnemyState_Dead.h"
#include "../Library/Time.h"
#include "EnemyBase.h"
#include "EnemyValue.h"
#include "EffectManager.h"
#include "EffectValue.h"

void EnemyState_Dead::Update()
{
	if (elapsedTime == 0)
	{
		int size = (int)(sizeof(ENEMY_ANIM_SETTING_DAMAGE) / sizeof(ENEMY_ANIM_SETTING_DAMAGE[0]));
		int rand = GetRand(size - 1) + 1;
		parent->PlayAnim("Damage" + std::to_string(rand));
	}
	elapsedTime += Time::GameDeltaTime();

	parent->MoveVelocityXZ(ENEMY_DEAD_REDUCE_KNOCK_BACK_SPEED_Z, VZero);

	if (elapsedTime >= ENEMY_DEAD_TIME)
	{
		EffectManager* effect = SceneManager::CommonScene()->FindGameObject<EffectManager>();
		effect->Create("Hit", parent->GetPos() + EFFECT_HIT_ADJUST_POS,
			VZero, EFFECT_HIT_DEAD_SCALE);
		parent->ExplosionParts();
		parent->Destroy();
	}
}

void EnemyState_Dead::End()
{
}
