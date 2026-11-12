#include "E_Col.h"
#include "W_Col.h"
#include"StageManager.h"
#include<assert.h>
#include "debugScreen.h"
#include"Player.h"

E_Col::E_Col(const VECTOR& _pos)
{
	transform.position = _pos;
	transform.scale = STAGE_OBJECT_GATECOLL_SCALE;

	gateopenstate = false;

	open = false;
}

E_Col::E_Col(const VECTOR& _pos, const VECTOR& _rot, int _hModel) :E_Col(_pos)
{
	hModel = MV1DuplicateModel(_hModel);
	transform.rotation = _rot;
}

E_Col::~E_Col()
{
	if (hModel < 0)
		MV1DeleteModel(hModel);
}

void E_Col::Update()
{
	Player* player = FindGameObject<Player>();
	VECTOR Ppos = player->GetPos();

	VECTOR openpos = transform.position - Ppos;

	if (Ppos.z > 21682 && Ppos.z < 22917)
	{
		if (!gateopenstate)
		{
			if (openpos.x > -300)
			{
				open = true;
			}

			if (transform.position.y <= 1881)
			{
				if (open)
				{
					transform.position.y += 7;
				}
			}
		}
		if (gateopenstate)
		{
			if (openpos.x > 300)
			{
				anopen = true;
			}
		}
	}

	if (anopen)
	{
		if (transform.position.y > 1081)
		{
			transform.position.y -= 7;
		}
	}



	if (transform.position.y > 1881)
	{
		gateopenstate = true;
		transform.position.y = 1881;
	}

	if (transform.position.y < 1081)
	{
		transform.position.y = 1081;
	}
}

void E_Col::Draw()
{
		MATRIX mat = GetDrawMatrix();
		MV1SetMatrix(hModel, mat);
}

void E_Col::Reset()
{
	transform.position.y = 310;
	gateopenstate = false;
	anopen = false;
	open = false;
}
