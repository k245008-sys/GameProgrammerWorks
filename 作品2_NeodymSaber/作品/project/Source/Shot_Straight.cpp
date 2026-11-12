#include "Shot_Straight.h"
#include "ShotValue.h"
#include "ColorValue.h"
#include "EffectManager.h"

Shot_Straight::Shot_Straight()
{
	enable = false;
	elapsedTime = 0;
	speed = 0;
	velocity = VZero;
}

Shot_Straight::~Shot_Straight()
{
}

void Shot_Straight::Update()
{
	if (!enable)
		return;
	elapsedTime += Time::GameDeltaTime();
	transform.position += velocity * Time::GameDeltaTime();

	if (elapsedTime >= SHOT_DELETE_TIME)
		enable = false;
}

void Shot_Straight::Draw()
{
	if (!enable)
		return;
}

void Shot_Straight::EnableOn(const VECTOR& _pos, const VECTOR& _rot, const float& _speed)
{
	enable = true;
	transform.position = _pos;
	transform.rotation = _rot;
	MATRIX mRot = MGetRotZXY(transform.rotation);
	speed = _speed;
	velocity = VGet(0, 0, _speed) * mRot;
	elapsedTime = 0;
	EffectManager* effect = SceneManager::CommonScene()->FindGameObject<EffectManager>();
	effect->Create("Shot", &transform.position, VZero, VGet(1, 1, 1));
}

void Shot_Straight::EnableOff()
{
	enable = false;
	EffectManager* effect = SceneManager::CommonScene()->FindGameObject<EffectManager>();
	effect->Delete(&transform.position);
}
