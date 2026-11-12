#include "ParticleBase.h"
#include "MoveNum.h"
#include "../Library/Time.h"
#include "EnemyValue.h"

ParticleBase::ParticleBase(const std::string& _name, const int& _hModel, const VECTOR& _pos, const VECTOR& _rot, const float& _scale, const float& _lifTime, const float& _fadeOut, const VECTOR& _velocity, const VECTOR& _reduce, const VECTOR& _rotSpeed)
{
	name = _name;
	hModel = _hModel;
	transform.position = _pos;
	transform.rotation = _rot;
	transform.scale = VGet(_scale, _scale, _scale);
	lifeTime = _lifTime;
	fadeOutTime = _fadeOut;
	velocity = _velocity;
	reduceVel = _reduce;
	rotSpeed = _rotSpeed;
	destroy = false;
	MV1SetMaterialDifColor(hModel, 0, ENEMY_EXPLOSION_PARTS_DIF_COLOR);
	MV1SetMaterialAmbColor(hModel, 0, ENEMY_EXPLOSION_PARTS_AMB_COLOR);
}

ParticleBase::~ParticleBase()
{
}

void ParticleBase::Update()
{
	float delta = Time::GameDeltaTime();
	transform.position += velocity * delta;
	transform.rotation += rotSpeed * delta;
	MoveNum move;
	VECTOR reduceXZ = VGet(reduceVel.x, 0, reduceVel.z);
	move.MoveToTargetV(velocity, reduceXZ, VZero);
	velocity.y -= reduceVel.y;
	lifeTime -= delta;
	if (lifeTime <= 0)
		destroy = true;
}

void ParticleBase::Draw()
{
	float rate = lifeTime / fadeOutTime;
	if (rate > 1.0f)
		rate = 1.0f;
	else
	{
		COLOR_F dif = ENEMY_EXPLOSION_PARTS_DIF_COLOR;
		dif.r = rate;
		MV1SetMaterialDifColor(hModel, 0, dif);
	}
	Object3D::Draw();
}
