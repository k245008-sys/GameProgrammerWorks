#include "H_Col.h"
#include "W_Col.h"
#include"StageManager.h"
#include<assert.h>
#include "debugScreen.h"
#include"Player.h"
#include "EnemyManager.h"

H_Col::H_Col(const VECTOR& _pos)
{
	transform.position = _pos;
	transform.scale = STAGE_OBJECT_GATECOLL_SCALE;

	gateopenstate = false;

	open = false;
}

H_Col::H_Col(const VECTOR& _pos, const VECTOR& _rot, int _hModel) :H_Col(_pos)
{
	hModel = MV1DuplicateModel(_hModel);
	transform.rotation = _rot;
}

H_Col::~H_Col()
{
	if (hModel < 0)
	MV1DeleteModel(hModel);
}

void H_Col::Update()
{

	Player* player = FindGameObject<Player>();
	VECTOR Ppos = player->GetPos();

	VECTOR openpos = transform.position - Ppos;
	EnemyManager* enemy = FindGameObject<EnemyManager>();

	if (enemy->GetEnableOpen(3))
	{
		open = true;
	}

	if (openpos.x > 0)
	{
		if (Ppos.z > 21682 && Ppos.z < 22917)
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

void H_Col::Draw()
{
		MATRIX mat = GetDrawMatrix();
		MV1SetMatrix(hModel, mat);
}

void H_Col::Reset()
{
	transform.position.y = 310;
	gateopenstate = false;
	anopen = false;
	open = false;
}
