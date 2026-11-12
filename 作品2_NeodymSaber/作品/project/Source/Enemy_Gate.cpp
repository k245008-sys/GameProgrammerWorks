#include "Enemy_Gate.h"
#include"StageManager.h"
#include<assert.h>
#include "debugScreen.h"
#include"Player.h"

Enemy_Gate::Enemy_Gate(const VECTOR& _pos)
{
	transform.position = _pos;
	transform.scale = STAGE_OBJECT_GATE_SCALE;

	gateopenstate = false;
	anopen = false;
	open = false;
	test = 0;
}

Enemy_Gate::Enemy_Gate(const VECTOR& _pos, const VECTOR& _rot, int _hModel):Enemy_Gate(_pos)
{
	hModel = MV1DuplicateModel(_hModel);
	transform.rotation = _rot;
}

Enemy_Gate::~Enemy_Gate()
{
	if (hModel < 0)
		MV1DeleteModel(hModel);
}

void Enemy_Gate::Update()
{
	Player* player = FindGameObject<Player>();
	VECTOR Ppos = player->GetPos();

	VECTOR openpos = transform.position - Ppos;
		
	test = (int)openpos.x;

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

void Enemy_Gate::Draw()
{
	Object3D::Draw();
}

void Enemy_Gate::Reset()
{
	transform.position.y = 310;
	gateopenstate = false;
	anopen = false;
	open = false;
}
