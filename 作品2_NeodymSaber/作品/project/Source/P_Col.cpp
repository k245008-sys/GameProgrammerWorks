#include "P_Col.h"
#include "W_Col.h"
#include"StageManager.h"
#include<assert.h>
#include "debugScreen.h"
#include"Player.h"
#include "EnemyManager.h"

P_Col::P_Col(const VECTOR& _pos)
{
	transform.position = _pos;
	transform.scale = STAGE_OBJECT_GATECOLL_SCALE;

	gateopenstate = false;
	anopen = false;
	open = false;
}

P_Col::P_Col(const VECTOR& _pos, const VECTOR& _rot, int _hModel) :P_Col(_pos)
{
	hModel = MV1DuplicateModel(_hModel);
	transform.rotation = _rot;
}

P_Col::~P_Col()
{
	if (hModel < 0)
		MV1DeleteModel(hModel);
}

void P_Col::Update()
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

void P_Col::Draw()
{
	MATRIX mat = GetDrawMatrix();
	MV1SetMatrix(hModel, mat);

		//Object3D::Draw();
}

void P_Col::Reset()
{
	transform.position.y = 310;
	gateopenstate = false;
	anopen = false;
	open = false;
}
