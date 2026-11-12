#pragma once
#include "DynamicObjBase.h"
#include "Animator.h"
#include "CharaValue.h"
#include "StageManager.h"
#include "Stairs.h"

/*
	プレイヤーと敵の基底クラス
	綾部
*/

class RoundShadow;

class CharaBase : public DynamicObjBase
{
public:
	CharaBase();
	virtual ~CharaBase();
	virtual void Update()override;
	virtual void Draw()override;

	virtual void AssignFindObjToField()override;

	StateManager* GetStateManager() { return stateManager; }
	bool GetIsSnap()const { return isSnap; }
	std::string GetCurrentAnim()const { return anim->GetPlay(); }
	virtual bool GetIsAnimFinish() { return anim->IsFinish(); }
	bool GetIsGround() const { return isGround; }
	float GetWallCollSize()const { return wallCollSize; }

	void SetIsSnap(const bool& _isSnap) { isSnap = _isSnap; }
	void SetWasSnap(const bool& _wasSnap) { wasSnap = _wasSnap; }
	void SetEnableGravity(const bool& _enableGravity) { enableGravity = _enableGravity; }

	void Gravity();
	void WallCollision(const VECTOR& _adjustStartPos, const bool& _enableY = false);
	// 地上にいるかの判定
	void GroundingCollision(const float& _downCollSize);

	virtual void UpdateAnim() { anim->Update(); }
	virtual void PlayAnim(const std::string& _name) { anim->Play(_name); }
	float GetAnimBlendFrame(const std::string& _name) { return anim->GetBlendFrame(_name); }
	float GetAnimDefBlendFrame(const std::string& _name) { return anim->GetDefBlendFrame(_name); }
	virtual void SetAnimBlendFrame(const std::string& _name, const float& _blendFrame) { anim->SetBlendFrame(_name, _blendFrame); }
	virtual void ResetAnimBlendFrame(const std::string& _name) { anim->ResetBlendFrame(_name); }

	void MovePosAndStageColl(const VECTOR& _targetPos);
	void ShakePos(const VECTOR& _velocity, const VECTOR& _range, const float& _time);

	void SetAnim(Animator* _anim) {anim = _anim;}

protected:
	void Shake();
	virtual void ResetWasSnap();
	VECTOR ShadowCollision();

	StageManager* stageManager;
	Animator* anim;
	RoundShadow* roundShadow;

	VECTOR adjustDrawPos;
	bool isGround;
	float downCollSizeOnGround;
	float downCollSizeInAir;
	VECTOR adjustRayStartPosWall;
	float wallCollSize;
	bool isSnap;
	bool wasSnap;
	VECTOR adjustDownCollStartPos;
	VECTOR shakePos;
	VECTOR shakeVel;
	VECTOR shakeRange;
	float shakeTime;
	bool enableGravity;
};