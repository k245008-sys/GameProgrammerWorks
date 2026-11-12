#pragma once
#include "../Library/gameObject.h"
#include <unordered_map>

namespace
{
	enum SelectState
	{
		S_RETRY,
		S_TITLE,
		S_BLACK_IN,
	};
}

class InputManager;

class SelectUi : public GameObject
{
public:
	SelectUi(SceneBase* _scene);
	~SelectUi();
	void UpdateSelect();
	void DrawSelect();

	SelectState GetState() { return state; }
	bool GetSelectInput();
	void Reset();

private:
	std::unordered_map<std::string, int> hImages;
	SelectState state;
	InputManager* input;

	float time;
	float alphaRate;
	bool go;
};