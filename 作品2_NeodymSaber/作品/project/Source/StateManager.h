#pragma once
#include <unordered_map>
#include <string>
#include "StateBase.h"

/*
	キャラのステートを管理するクラス
	綾部
*/

class DynamicObjBase;

class StateManager
{
public:
	/// <param name="_defState">デフォルトにするステート</param>
	StateManager(const std::string& _defStateName);
	~StateManager();
	void Update();
	void Draw();

	void AssignFindObjToFieldAll();

	void AddState(const std::string& _name, StateBase* _state);
	// 現在ステートを指定したステートへ移行させる
	void ChangeCurrentState(const std::string& _nextStateName);
	void ChangeCurrentStateOnce(const std::string& _nextStateName);

	std::string GetCurrentStateName() { return currentStateName; }
	StateBase* GetCurrentState() { return states[currentStateName]; }
	StateBase* GetState(const std::string& _state) { return states[_state]; }
	int GetStateSize() { return (int)states.size(); }

	// このクラスを持つオブジェクトのポインタをセットする用
	void SetParentToCurrentState(DynamicObjBase* _parent) { states[currentStateName]->SetParent(_parent); }

private:
	std::unordered_map<std::string, StateBase*> states;
	std::string currentStateName;
	std::string nextStateName;
};