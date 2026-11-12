#include "F_Gate.h"
#include"StageManager.h"
#include"EnemyManager.h"
#include<assert.h>
#include "debugScreen.h"
#include"Player.h"

F_Gate::F_Gate(const VECTOR& _pos)
{
	transform.position = _pos;
	transform.scale = STAGE_OBJECT_GATE_SCALE;

	gateopenstate = false;
	open = false;
}

F_Gate::F_Gate(const VECTOR& _pos, const VECTOR& _rot, int _hModel):F_Gate(_pos)
{
	hModel = MV1DuplicateModel(_hModel);
	transform.rotation = _rot;
}

F_Gate::~F_Gate()
{
	if (hModel < 0)
		MV1DeleteModel(hModel);
}

void F_Gate::Update()
{
	Player* player = FindGameObject<Player>();
	VECTOR Ppos = player->GetPos();

	VECTOR openpos = transform.position - Ppos;

	EnemyManager* enemy = FindGameObject<EnemyManager>();

		if (enemy->GetEnableOpen(1))
		{
			open = true;
		}

	if (openpos.z < 0)
	{
		if (!enemy->GetEnableOpen(2))
		{
			open = false;
			transform.position.y -= 7;
		}
	}

	if (open)
	{
		if (transform.position.y < 1000)
		{
			transform.position.y += 7;
		}

	}
	else
	{
		if (transform.position.y > 310)
		{
			transform.position.y -= 7;
		}
	}

	if (transform.position.y > 1000)
	{
		transform.position.y = 1000;
	}

	if (transform.position.y < 310)
	{
		transform.position.y = 310;
	}

}

void F_Gate::Draw()
{
	//DebugPrintf(0, 500, "ExtRate : %d", test);
	Object3D::Draw();
}

void F_Gate::Reset()
{
	transform.position.y = 310;
	gateopenstate = false;
	anopen = false;
	open = false;
}
