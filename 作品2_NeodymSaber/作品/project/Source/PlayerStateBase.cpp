#include "PlayerStateBase.h"
#include "Player.h"
#include "Camera.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "EffectManager.h"

void PlayerStateBase::AssignFindObjToField()
{
	input = SceneManager::CommonScene()->FindGameObject<InputManager>();
	sound = SceneManager::CommonScene()->FindGameObject<SoundManager>();
	effect = SceneManager::CommonScene()->FindGameObject<EffectManager>();
	camera = FindGameObject<Camera>();
}

void PlayerStateBase::SetParent(DynamicObjBase* _parent)
{
	parent = dynamic_cast<Player*>(_parent);
}
