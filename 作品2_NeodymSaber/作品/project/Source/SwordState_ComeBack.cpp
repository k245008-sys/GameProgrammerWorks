#include "SwordState_ComeBack.h"
#include "Sword_Throw.h"
#include "SwordValue.h"
#include "Player.h"

void SwordState_ComeBack::Update()
{
	Player* player = parent->GetParent();
	VECTOR dist = player->GetPos() - parent->GetPos();
	float rotY = atan2f(dist.x, dist.z);
	parent->SetRotY(rotY);
	float rotX = -atan2f(dist.y, sqrtf(dist.x * dist.x + dist.z * dist.z));
	parent->SetRotX(rotX);
	//parent->SetRotZ(atan2f(dist.x, dist.y));
	parent->SetVelocity(VNorm(dist) * SWORD_COME_BACK_SPEED);

	if (VSize(dist) <= SWORD_COME_BACK_JUDGE_FINISH_DIST)
		nextStateName = "Equipped";
}

void SwordState_ComeBack::End()
{
}
