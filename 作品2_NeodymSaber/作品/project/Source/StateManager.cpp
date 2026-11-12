#include "StateManager.h"

StateManager::StateManager(const std::string& _defStateName)
{
	currentStateName = _defStateName;
	nextStateName = currentStateName;
	states.clear();
}

StateManager::~StateManager()
{
	for (auto& s : states)
	{
		if(s.second != nullptr)
		delete s.second;
	}
	states.clear();
}

void StateManager::Update()
{
	states[currentStateName]->Update();
	// 現在ステートの中の次ステート値が変わったらそれに移行させる
	nextStateName = states[currentStateName]->GetNextStateName();
	if (currentStateName != nextStateName)
		ChangeCurrentState(nextStateName);
}

void StateManager::Draw()
{
	states[currentStateName]->Draw();
}

void StateManager::AssignFindObjToFieldAll()
{
	for (auto& state : states)
	{
		state.second->AssignFindObjToField();
	}
}

void StateManager::AddState(const std::string& _name, StateBase* _state)
{
	states.insert({ _name, _state });
	states[_name]->SetNextStateName(nextStateName);
}

void StateManager::ChangeCurrentState(const std::string& _nextStateName)
{
	states[currentStateName]->SetNextStateName(_nextStateName);
	// 終了処理
	states[currentStateName]->End();
	states[currentStateName]->ResetElapsedTime();
	// 次ステートをセット
	currentStateName = _nextStateName;
	states[_nextStateName]->SetNextStateName(_nextStateName);
}

void StateManager::ChangeCurrentStateOnce(const std::string& _nextStateName)
{
	if (_nextStateName == currentStateName)
		return;
	ChangeCurrentState(_nextStateName);
}
