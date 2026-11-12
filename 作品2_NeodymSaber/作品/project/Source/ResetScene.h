#pragma once
#include "../Library/sceneBase.h"
class ResetScene :public SceneBase
{
public:
	ResetScene();
	~ResetScene();
	void Update() override;
	void Draw() override;
};

