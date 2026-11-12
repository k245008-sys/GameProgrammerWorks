#include "Emitter.h"
#include "ParticleBase.h"
#include <assert.h>

Emitter::Emitter()
{
	hModels.insert({ "Arm", MV1LoadModel("data/model/EnemyParts/arm.mv1") });
	hModels.insert({ "Body", MV1LoadModel("data/model/EnemyParts/body.mv1") });
	hModels.insert({ "Clavicle", MV1LoadModel("data/model/EnemyParts/clavicle.mv1") });
	hModels.insert({ "Foot", MV1LoadModel("data/model/EnemyParts/foot.mv1") });
	hModels.insert({ "Hand", MV1LoadModel("data/model/EnemyParts/hand.mv1") });
	hModels.insert({ "Head", MV1LoadModel("data/model/EnemyParts/head.mv1") });
	hModels.insert({ "Joint1", MV1LoadModel("data/model/EnemyParts/joint_01.mv1") });
	hModels.insert({ "Joint2", MV1LoadModel("data/model/EnemyParts/joint_02.mv1") });
	hModels.insert({ "Joint3", MV1LoadModel("data/model/EnemyParts/joint_03.mv1") });
	hModels.insert({ "Leg", MV1LoadModel("data/model/EnemyParts/leg_02.mv1") });
	hModels.insert({ "LegGuard", MV1LoadModel("data/model/EnemyParts/legguard.mv1") });
	hModels.insert({ "LegJoint", MV1LoadModel("data/model/EnemyParts/legjoint.mv1") });
	hModels.insert({ "Shoulder", MV1LoadModel("data/model/EnemyParts/shoulder.mv1") });
	hModels.insert({ "UpLeg", MV1LoadModel("data/model/EnemyParts/upleg.mv1") });
	hModels.insert({ "Waist1", MV1LoadModel("data/model/EnemyParts/waist.mv1") });
	hModels.insert({ "Waist2", MV1LoadModel("data/model/EnemyParts/waist_01.mv1") });

	for (auto& m : hModels)
	//	assert(m.second > 0);

	particles.clear();
}

Emitter::~Emitter()
{
	for (auto& m : hModels)
		MV1DeleteModel(m.second);
	hModels.clear();
	for (auto it = particles.begin(); it != particles.end();)
	{
		it = particles.erase(it);
		it++;
	}
	particles.clear();
}

void Emitter::Update()
{
	for (auto it = particles.begin(); it != particles.end();)
	{
		(*it)->Update();
		if ((*it)->Destroy())
		{
			it = particles.erase(it);
			continue;
		}
		it++;
	}
}

void Emitter::Draw()
{
	for (auto& p : particles)
		p->Draw();
}

void Emitter::Create(const std::string& _type, const VECTOR& _pos, const VECTOR& _rot, const float& _scale, const float& _lifeTime, const float& _fadeOutTime, const VECTOR& _velocity, const VECTOR& _reduceVel, const VECTOR& _rotSpeed)
{
	particles.emplace_back(new ParticleBase(_type, hModels[_type], _pos, _rot, _scale, _lifeTime, _fadeOutTime, _velocity, _reduceVel, _rotSpeed));
}

void Emitter::Create(const std::string& _type, const VECTOR& _pos, const float& _scale, const float& _lifeTime, const float& _fadeOutTime, const VECTOR& _velocity, const VECTOR& _reduceVel, const VECTOR& _rotSpeed)
{
	Create(_type, _pos, VZero, _scale, _lifeTime, _fadeOutTime, _velocity, _reduceVel, _rotSpeed);
}

void Emitter::Create(const std::string& _type, const VECTOR& _pos, const float& _lifeTime, const float& _fadeOutTime, const VECTOR& _velocity, const VECTOR& _reduceVel, const VECTOR& _rotSpeed)
{
	Create(_type, _pos, 1.0f, _lifeTime, _fadeOutTime, _velocity, _reduceVel, _rotSpeed);
}
