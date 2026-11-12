#include "Sword_Slash.h"
#include <assert.h>
#include "SwordValue.h"
#include "Player.h"
#include "ColorValue.h"
#include "InputManager.h"
#include "CommonFunc_CollDraw.h"

Sword_Slash::Sword_Slash()
{
	stateManager = new StateManager("Equipped");
	stateManager->AddState("Held", &s_held);
	stateManager->AddState("Equipped", &s_equipped);

	hModel = MV1LoadModel("data/model/sword_blue.mv1");
	assert(hModel > 0);
	rootFrameName = SWORD_SLASH_ROOT_NAME;
	defRootPos = SWORD_SLASH_ADJUST_LOCAL_POS;
	SetFrameLocalPos(rootFrameName.c_str(), defRootPos);
	SetFrameLocalRot(rootFrameName.c_str(), VGet(DEGREE * 180, 0, 0));

	transform.scale = SWORD_SLASH_SCALE;
	appearColl = false;
}

Sword_Slash::~Sword_Slash()
{
}

void Sword_Slash::Update()
{
	SwordBase::Update();

#ifdef _DEBUG
	InputManager* input = SceneManager::CommonScene()->FindGameObject<InputManager>();
	if (input->IsKeyPushDown(SWORD_SLASH_DRAW_COLL_INPUT))
		appearColl = appearColl ? false : true;
#endif
}

void Sword_Slash::Draw()
{
	if (parent->GetStateManager()->GetCurrentStateName() == "Aim" ||
		parent->GetStateManager()->GetCurrentStateName() == "Throw")
	{
		transform.position = parent->GetLeftHandPos();
		transform.rotation = parent->GetLeftHandRot();
	}
	else
	{
		transform.position = parent->GetRightHandPos();
		transform.rotation = parent->GetRightHandRot();
	}
	SwordBase::Draw();

#ifdef _DEBUG
	if (appearColl)
	{
		CommonFunc_CollDraw cDraw;
		cDraw.DrawCapsule(GetCollRootPos(), GetCollTipPos(), SWORD_SLASH_COLL_RAD, SWORD_SLASH_DRAW_COLL_COLOR, SWORD_SLASH_DRAW_COLL_ALPHA_PERCENT);
	}
#endif
}


VECTOR Sword_Slash::GetCollBasePos()
{
	MATRIX baseMRot = MGetRotZXY(GetFrameWorldRot("sword_blue_grp"));
	VECTOR basePos = GetFrameWorldPos("sword_blue_grp");
	basePos += SWORD_SLASH_ADJUST_COLL_BASE_POS * baseMRot;
	return basePos;
}

VECTOR Sword_Slash::GetCollRootPos()
{
	return GetCollBasePos() + SWORD_SLASH_ADJUST_COLL_ROOT_POS_FROM_BASE_POS * GetBaseRot();
}

VECTOR Sword_Slash::GetCollTipPos()
{
	return GetCollBasePos() + SWORD_SLASH_ADJUST_COLL_TIP_POS_FROM_BASE_POS * GetBaseRot();
}