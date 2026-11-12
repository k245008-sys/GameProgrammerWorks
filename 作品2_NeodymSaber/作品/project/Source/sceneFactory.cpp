#include "sceneFactory.h"
#include <windows.h>
#include <assert.h>
#include "bootScene.h"
#include"ResetScene.h"
#include "playScene.h"
#include "TitleScene.h"

SceneBase* SceneFactory::CreateFirst()
{
	return new BootScene();
}

SceneBase * SceneFactory::Create(const std::string& name)
{

	if (name == "ResetScene") {
		return new ResetScene();
	}
	if (name == "PlayScene") {
		return new PlayScene();
	}
	MessageBox(NULL, ("éüÇÃÉVÅ[ÉìÇÕÇ†ÇËÇ‹ÇπÇÒ\n" + name).c_str(), "SceneFactory", MB_ICONERROR | MB_OK);
	assert(false);
	return nullptr;
}
