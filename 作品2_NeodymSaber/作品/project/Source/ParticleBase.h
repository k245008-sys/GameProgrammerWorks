#pragma once
#include "Object3D.h"
#include <string>

class ParticleBase : public Object3D
{
public:
	ParticleBase(const std::string& _name, const int& _hModel, const VECTOR& _pos, const VECTOR& _rot, const float& _scale, const float& _lifTime, const float& _fadeOut, const VECTOR& _velocity, const VECTOR& _reduce = VZero, const VECTOR& _rotSpeed = VZero);
	~ParticleBase();
	virtual void Update()override;
	virtual void Draw()override;

	std::string GetName() { return name; }
	bool Destroy() { return destroy; }

private:
	std::string name;
	float lifeTime;
	float fadeOutTime;
	VECTOR velocity;
	VECTOR reduceVel;
	VECTOR rotSpeed;
	bool destroy;
};