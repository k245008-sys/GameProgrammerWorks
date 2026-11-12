#include "EnemyState_Explosion.h"
#include "EnemyBase.h"
#include "EnemyManager.h"
#include "EnemyValue.h"
#include "EffectManager.h"
#include "EffectValue.h"
#include "Player.h"

void EnemyState_Explosion::Update()
{
	if (elapsedTime == 0)
	{
		parent->Destroy();
		VECTOR dist = player->GetPos() - parent->GetPos();
		EffectManager* effect = SceneManager::CommonScene()->FindGameObject<EffectManager>();
		effect->Create("Hit", parent->GetPos() + EFFECT_HIT_ADJUST_POS,
			VGet(0, atan2f(dist.x, dist.z), 0), EFFECT_HIT_EXPLOSION_MYSELF_SCALE);
		EnemyManager* enemyManager = FindGameObject<EnemyManager>();
		for (auto& enemy : enemyManager->GetEnemies())
		{
			dist = player->GetPos() - enemy->GetPos();
			if (VSize(dist) <= ENEMY_EXPLOSION_DIST)
				player->Damage(VGet(0,0,ENEMY_EXPLOSION_GIVE_KNOCK_BACK_SPEED) * MGetRotY(atan2f(dist.x, dist.z)));
			if (enemy->GetCurrentStateName() == "Explosion")
				continue;
			dist = enemy->GetPos() - parent->GetPos();
			if (VSize(dist) > ENEMY_EXPLOSION_DIST)
				continue;

			effect->Create("Hit", enemy->GetPos() + EFFECT_HIT_ADJUST_POS,
				VGet(0, atan2f(dist.x, dist.z), 0), EFFECT_HIT_EXPLOSION_AROUND_SCALE);
			parent->ExplosionParts();

			enemy->Damage(VNorm(dist) * ENEMY_EXPLOSION_GIVE_KNOCK_BACK_SPEED);
		}
	}
}

void EnemyState_Explosion::End()
{
}
