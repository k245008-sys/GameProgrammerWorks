#pragma once
#include "Object3D.h"
#include "StateManager.h"
#include "../Library/Time.h"
#include "MoveNum.h"

/*
	ステートとアニメーションを持つ
	オブジェクトの基底クラス
	綾部
*/

class DynamicObjBase : public Object3D
{
public:
	DynamicObjBase();
	virtual ~DynamicObjBase();
	virtual void Update()override;
	virtual void Draw()override;

	virtual void AssignFindObjToField()override {}

	std::string GetCurrentStateName() { return stateManager->GetCurrentStateName(); }
	VECTOR GetVelocity() { return velocity; }
	VECTOR GetVelocityXZ() { return VGet(velocity.x, 0, velocity.z); }
	VECTOR GetPosAfterMove() { return transform.position + velocity * Time::GameDeltaTime(); }

	void SetVelocity(const VECTOR& _velocity) { velocity = _velocity; }
	void SetVelocityX(const float& _velocityX) { velocity.x = _velocityX; }
	void SetVelocityY(const float& _velocityY) { velocity.y = _velocityY; }
	void SetVelocityZ(const float& _velocityZ) { velocity.z = _velocityZ; }
	// 水平速度のみセット
	void SetVelocityXZ(const VECTOR& _velocity) { velocity = VGet(_velocity.x, velocity.y, _velocity.z); }
	void MoveVelocity(const float& _speed, const VECTOR& _target)
	{
		MoveNum moveNum;
		moveNum.MoveVector(velocity, _speed, _target);
	}
	// 水平速度のみ動かす
	void MoveVelocityXZ(const float& _speed, const VECTOR& _target)
	{
		MoveNum moveNum;
		moveNum.MoveVector(velocity, _speed, VGet(_target.x, velocity.y, _target.z));
	}
	void MoveVelocityY(const float& _speed, const float& _target)
	{
		MoveNum moveNum;
		moveNum.MoveToTarget(velocity.y, _speed, _target);
	}
	void AddVelocityY(const float& _speed)
	{
		velocity.y += _speed;
	}

	// ステートを今と同じでなければ指定して変更
	void ChangeStateOnce(const std::string& _stateName);
	// ステートを今と同じでも変更し直せる
	void ChangeState(const std::string& _stateName);

protected:
	StateManager* stateManager;

	VECTOR velocity;
};