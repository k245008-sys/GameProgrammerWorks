#pragma once
#include "../Library/gameObject.h"

#include <unordered_map>
#include <string>

class ParticleBase;

class Emitter : public GameObject
{
public:
	Emitter();
	~Emitter();
	void Update()override;
	void Draw()override;

	void Create(const std::string& _type, const VECTOR& _pos, const VECTOR& _rot, const float& _scale, const float& _lifeTime, const float& _fadeOutTime,
		const VECTOR& _velocity, const VECTOR& _reduceVel, const VECTOR& _rotSpeed);
	void Create(const std::string& _type, const VECTOR& _pos, const float& _scale, const float& _lifeTime, const float& _fadeOutTime,
		const VECTOR& _velocity, const VECTOR& _reduceVel, const VECTOR& _rotSpeed);
	void Create(const std::string& _type, const VECTOR& _pos, const float& _lifeTime, const float& _fadeOutTime,
		const VECTOR& _velocity, const VECTOR& _reduceVel, const VECTOR& _rotSpeed);

private:
	std::unordered_map<std::string, int> hModels;
	std::list<ParticleBase*> particles;
};