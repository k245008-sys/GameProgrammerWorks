#pragma once
#include <string>

/*
	キャラのステートの基底クラス
	綾部
*/

class DynamicObjBase;

class StateBase
{
public:
	StateBase() : elapsedTime(0), nextStateName("") {}
	virtual ~StateBase() {}
	virtual void Update() {}
	virtual void Draw() {}

	virtual void AssignFindObjToField() {}

	std::string GetNextStateName() { return nextStateName; }
	void SetNextStateName(const std::string& _nextStateName) { nextStateName = _nextStateName; }
	void ResetElapsedTime() { elapsedTime = 0; }
	// ステート終了時に呼ばれる処理
	virtual void End() {}

	virtual void SetParent(DynamicObjBase* _parent) {}

protected:
	float elapsedTime; // ステート開始からの経過時間
	std::string nextStateName;
};