#include "Player_Gate.h"
#include"StageManager.h"
#include"EnemyManager.h"
#include<assert.h>
#include "debugScreen.h"
#include"Player.h"
#include "playScene.h"

Player_Gate::Player_Gate(const VECTOR& _pos)
{
	transform.position = _pos;
	transform.scale = STAGE_OBJECT_GATE_SCALE;

	Reset();
}

Player_Gate::Player_Gate(const VECTOR& _pos, const VECTOR& _rot, int _hModel) : Player_Gate(_pos)
{
	hModel = MV1DuplicateModel(_hModel);
	transform.rotation = _rot;
}

Player_Gate::~Player_Gate()
{
	if (hModel < 0)
		MV1DeleteModel(hModel);
}

void Player_Gate::Update()
{
	Player* player = FindGameObject<Player>();
	VECTOR Ppos = player->GetPos();

	VECTOR openpos = transform.position - Ppos;

	EnemyManager* enemy = FindGameObject<EnemyManager>();
	
	if (openpos.z < 300)
	{
		if(!anopen)
		open = true;
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

void Player_Gate::Draw()
{
	Object3D::Draw();
}

void Player_Gate::Reset()
{
	transform.position.y = 310;
	gateopenstate = false;
	anopen = false;
	open = false;
}
