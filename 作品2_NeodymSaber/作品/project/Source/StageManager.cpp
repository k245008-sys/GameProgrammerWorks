#include "StageManager.h"
#include"StageValue.h"
#include "Stage_Ground.h"
#include"hand_rail.h"
#include "Hill_Ground.h"
#include"L_Ground.h"
#include"Wall.h"
#include"S_Wall.h"
#include "Stairs.h"
#include"Step.h"
#include"Square.h"
#include"Gate.h"
#include"W_Gate.h"
#include"H_Gate.h"
#include"F_Gate.h"
#include"Player_Gate.h"
#include"E_Col.h"
#include"P_Col.h"
#include"W_Col.h"
#include"H_Col.h"
#include"Slope_Col.h"
#include"High_Col.h"
#include"Col_Slope.h"
#include"Enemy_Gate.h"
#include"GateFlame.h"
#include"Hill.h"
#include"Hill_corner.h"
#include"Hillend.h"
#include"Hill_ceiling.h"
#include"G_Colhill.h"
#include"N_Colhill.h"
#include"F_Hill.h"
#include"N_Hill.h"
#include"Ceiling.h"
#include"S_Ceiling.h"
#include"C_Ceiling.h"
#include"Pipe.h"
#include "OffScreenEnemyGuid.h"

StageManager::StageManager()
{
	stageObjects.clear();
	collsionObjects.clear();

	objectModle[0] = MV1LoadModel((M_MODEL() + "hill_pipe" + M_MV1()).c_str());
	objectModle[1] = MV1LoadModel((M_MODEL() + "BG_hill" + M_MV1()).c_str());
	objectModle[2] = MV1LoadModel((M_MODEL() + "BG_handrail" + M_MV1()).c_str());
	objectModle[3] = MV1LoadModel((M_STAGE_OBGECT() + "Wall/gate_frame" + M_MV1()).c_str());

	groundModle[0] = MV1LoadModel((M_STAGE_OBGECT() + "Ground/fl" + M_MV1()).c_str());
	groundModle[1] = MV1LoadModel((M_STAGE_OBGECT() + "Ground/fl_S" + M_MV1()).c_str());
	groundModle[2] = MV1LoadModel((M_STAGE_OBGECT() + "Wall/wall_c" + M_MV1()).c_str());
	//groundModle[3] = MV1LoadModel((M_STAGE_OBGECT() + "Wall/gate_frame" + M_MV1()).c_str());
	
	gateModle[0] = MV1LoadModel((M_STAGE_OBGECT() + "Wall/gate" + M_MV1()).c_str());
	//groundModle[1] = MV1LoadModel((M_STAGE_OBGECT() + "Ground/fl_S" + M_MV1()).c_str());
	//groundModle[2] = MV1LoadModel((M_STAGE_OBGECT() + "Wall/wall_c" + M_MV1()).c_str());

	ceilingModle[0] = MV1LoadModel((M_STAGE_OBGECT() + "Ceiling/cei" + M_MV1()).c_str());
	ceilingModle[1] = MV1LoadModel((M_STAGE_OBGECT() + "Ceiling/cei_C" + M_MV1()).c_str());
	ceilingModle[2] = MV1LoadModel((M_STAGE_OBGECT() + "Ceiling/cei_S" + M_MV1()).c_str());

	hillModle[0] = MV1LoadModel((M_STAGE_OBGECT() + "Hell/re_floor_center" + M_MV1()).c_str());
	hillModle[1] = MV1LoadModel((M_STAGE_OBGECT() + "Hell/hall_gate" + M_MV1()).c_str());
	hillModle[2] = MV1LoadModel((M_STAGE_OBGECT() + "Hell/re_floor_corner" + M_MV1()).c_str());
	hillModle[3] = MV1LoadModel((M_STAGE_OBGECT() + "Hell/re_floor_end" + M_MV1()).c_str());
	hillModle[4] = MV1LoadModel((M_STAGE_OBGECT() + "Hell/hall_plane" + M_MV1()).c_str());
	hillModle[5] = MV1LoadModel((M_STAGE_OBGECT() + "Hell/hall_floor1" + M_MV1()).c_str());

	wallModle[0] = MV1LoadModel((M_STAGE_OBGECT() + "Wall/wall" + M_MV1()).c_str());
	s_wallModle = MV1LoadModel((M_STAGE_OBGECT() + "Wall/wall_s" + M_MV1()).c_str());

	collisionModle[0] = MV1LoadModel((M_STAGE_OBGECT() + "Wall/wall_hide" + M_MV1()).c_str());
	collisionModle[1] = MV1LoadModel((M_STAGE_OBGECT() + "Wall/wall_hide_s" + M_MV1()).c_str());
	collisionModle[2] = MV1LoadModel((M_STAGE_OBGECT() + "Ground/cei_S_hit" + M_MV1()).c_str());
	collisionModle[3] = MV1LoadModel((M_STAGE_OBGECT() + "Hell/hall_floor1" + M_MV1()).c_str());
	collisionModle[4] = MV1LoadModel((M_STAGE_OBGECT() + "Hell/hall_gate" + M_MV1()).c_str());
	collisionModle[5] = MV1LoadModel((M_STAGE_OBGECT() + "Hell/hall_plane" + M_MV1()).c_str());

	Test_Stage();

	coll = false;
	push = false;

	Restate();
}

StageManager::~StageManager()
{

	stageObjects.clear();
	collsionObjects.clear();

	for (int s = 0; s < (int)stageObjects.size(); s++)
	{
		if (stageObjects[s] != nullptr)
			delete stageObjects[s];
	}

	for (int s = 0; s < (int)collsionObjects.size(); s++)
	{
		if (collsionObjects[s] != nullptr)
			delete collsionObjects[s];
	}
}

void StageManager::Update()
{
	for (auto& it : stageObjects)
	{
		it->Update();
	}

	for (auto& it : collsionObjects)
	{
		it->Update();
	}
}

void StageManager::Draw()
{
	for (auto& it : stageObjects)
	{
		it->Draw();
	}

	for (auto& it : collsionObjects)
	{
		it->Draw();
	}
}

void StageManager::Restate()
{

	for (auto& it : stageObjects)
	{
		Player_Gate* pGate = dynamic_cast<Player_Gate*>(it);
		if (pGate != nullptr)
		{
			pGate->Reset();
		}

		F_Gate* fGate = dynamic_cast<F_Gate*>(it);
		if (fGate != nullptr)
		{
			fGate->Reset();
		}

		W_Gate* wGate = dynamic_cast<W_Gate*>(it);
		if (wGate != nullptr)
		{
			wGate->Reset();
		}

		H_Gate* hGate = dynamic_cast<H_Gate*>(it);
		if (hGate != nullptr)
		{
			hGate->Reset();
		}

		Enemy_Gate* eGate = dynamic_cast<Enemy_Gate*>(it);
		if (eGate != nullptr)
		{
			eGate->Reset();
		}
	}

	for (auto& it : collsionObjects)
	{
		P_Col* p_col = dynamic_cast<P_Col*>(it);
		if (p_col != nullptr)
		{
			p_col->Reset();
		}

		H_Col* h_col = dynamic_cast<H_Col*>(it);
		if (h_col != nullptr)
		{
			h_col->Reset();
		}

		W_Col* w_col = dynamic_cast<W_Col*>(it);
		if (w_col != nullptr)
		{
			w_col->Reset();
		}

		E_Col* e_col = dynamic_cast<E_Col*>(it);
		if (e_col != nullptr)
		{
			e_col->Reset();
		}
	}
}

void StageManager::Create(const StageObjectType& _type, const VECTOR& _pos, const VECTOR& _scale)
{
	switch (_type)
	{
	case StageObjectType::SMALL_SQUARE:
		break;
	case StageObjectType::HILL:
		stageObjects.emplace_back(new Pipe(_pos, _scale, objectModle[0]));
		break;
	case StageObjectType::BIG_SQUARE:
		stageObjects.emplace_back(new Square(_pos, _scale,objectModle[1]));
		break;
	case StageObjectType::SCAFFOLD:
		stageObjects.emplace_back(new hand_rail(_pos, _scale, objectModle[2]));
		break;
	case StageObjectType::GATE:
		break;
	case StageObjectType::GATE_FLAME:
		stageObjects.emplace_back(new GateFlame(_pos, _scale, objectModle[3]));
		break;
	}
}

void StageManager::CreateGround(const GROUND& _type,const VECTOR& _pos, const VECTOR& _rot)
{
	switch (_type)
	{
	case GROUND::N_FLEAM:
		stageObjects.emplace_back(new Stage_Ground(_pos, _rot, groundModle[0]));
		break;
	case GROUND::SLOAP:
		stageObjects.emplace_back(new Step(_pos, _rot, groundModle[1]));
		break;
	case GROUND::L_FLEAM:
		stageObjects.emplace_back(new L_Ground(_pos, _rot, groundModle[2]));
		break;
	case GROUND::T_FLEAM:
		break;
	}
}

void StageManager::GateGround(const GATE& _type, const VECTOR& _pos, const VECTOR& _rot)
{
	switch (_type)
	{
	case GATE::E_GATE:
		stageObjects.emplace_back(new Enemy_Gate(_pos, _rot, gateModle[0]));
		break;
	case GATE::P_GATE:
		stageObjects.emplace_back(new Player_Gate(_pos, _rot, gateModle[0]));
		break;
	case GATE::S_GATE:
		stageObjects.emplace_back(new Gate(_pos, _rot, gateModle[0]));
		break;
	case GATE::F_GATE:
		stageObjects.emplace_back(new F_Gate(_pos, _rot, gateModle[0]));
		break;
	case GATE::W_GATE:
		stageObjects.emplace_back(new W_Gate(_pos, _rot, gateModle[0]));
		break;
	case GATE::H_GATE:
		stageObjects.emplace_back(new H_Gate(_pos, _rot, gateModle[0]));
		break;
	}
}

void StageManager::CreateCeiling(const CEILING& _type, const VECTOR& _pos, const VECTOR& _rot)
{
	switch (_type)
	{
	case CEILING::N_CEILING:
		stageObjects.emplace_back(new Ceiling(_pos, _rot,ceilingModle[0]));
		break;
	case CEILING::C_CEILING:
		stageObjects.emplace_back(new C_Ceiling(_pos, _rot, ceilingModle[1]));
		break;
	case CEILING::S_CEILING:
		stageObjects.emplace_back(new S_Ceiling(_pos, _rot, ceilingModle[2]));
		break;
	}
}

void StageManager::CreateHill_Ground(const HILL& _type,const VECTOR& _pos, const VECTOR& _rot)
{
	switch (_type)
	{
	case HILL::F_HILL:
		stageObjects.emplace_back(new Hill(_pos, _rot,hillModle[0]));
		break;
	case HILL::G_HILL:
		stageObjects.emplace_back(new F_Hill(_pos, _rot, hillModle[1]));
		break;
	case HILL::HILL_N:
		stageObjects.emplace_back(new Hill_corner(_pos, _rot, hillModle[2]));
		break;
	case HILL::HILL_E:
		stageObjects.emplace_back(new Hillend(_pos, _rot, hillModle[3]));
		break;
	case HILL::N_HILL:
		stageObjects.emplace_back(new N_Hill(_pos, _rot, hillModle[4]));
		break;
	case HILL::HILL_CEILING:
		stageObjects.emplace_back(new Hill_ceiling(_pos, _rot, hillModle[5]));
		break;
	}
}

void StageManager::CreateWall(const WALL& _type, const VECTOR& _pos, const VECTOR& _rot)
{
	
	switch (_type)
	{
	case WALL::N_WALL:
		stageObjects.emplace_back(new Wall(_pos, _rot, wallModle[0]));
		break;
	case WALL::S_WALL:
		stageObjects.emplace_back(new S_Wall(_pos, _rot, s_wallModle));
		break;
	case WALL::L_WALL:
		break;
	case WALL::T_WALL:
		break;
	}
}

void StageManager::CreateColision(const COLLISION& _type, const VECTOR& _pos, const VECTOR& _rot)
{
	
	switch (_type)
	{
	case COLLISION::N_COL:
		collsionObjects.emplace_back(new Stairs(_pos, _rot, collisionModle[0]));
		break;
	case COLLISION::S_COL:
		collsionObjects.emplace_back(new Slope_Col(_pos, _rot, collisionModle[1]));
		break;
	case COLLISION::L_COL:
		collsionObjects.emplace_back(new Col_Slope(_pos, _rot, collisionModle[2]));
		break;
	case COLLISION::H_COL:
		collsionObjects.emplace_back(new High_Col(_pos, _rot, collisionModle[0]));
		break;
	case COLLISION::HILL_COL:
		collsionObjects.emplace_back(new Hill_Ground(_pos, _rot, collisionModle[3]));
		break;
	case COLLISION::HILL_G_COL:
		collsionObjects.emplace_back(new G_Colhill(_pos, _rot, collisionModle[4]));
		break;
	case COLLISION::HILL_W_COL:
		collsionObjects.emplace_back(new N_Colhill(_pos, _rot, collisionModle[5]));
		break;
	case COLLISION::E_GATE:
		collsionObjects.emplace_back(new E_Col(_pos, _rot, collisionModle[0]));
		break;
	case COLLISION::P_GATE:
		collsionObjects.emplace_back(new P_Col(_pos, _rot, collisionModle[0]));
		break;
	case COLLISION::W_GATE:
		collsionObjects.emplace_back(new W_Col(_pos, _rot, collisionModle[0]));
		break;
	case COLLISION::H_GATE:
		collsionObjects.emplace_back(new H_Col(_pos, _rot, collisionModle[0]));
		break;
	}
	
}

void StageManager::Map(const MAP& _type, const VECTOR& _pos, const VECTOR& _rot)
{
	switch (_type)
	{
	case MAP::HILL_FLORE:
		CreateHill_Ground(HILL::F_HILL, VGet(_pos.x, _pos.y, _pos.z), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		CreateHill_Ground(HILL::HILL_E, VGet(_pos.x, _pos.y - 13, _pos.z - 1370), VGet(0.0f, OBJECT_ROT * 3, 0.0f) * DEGREE);
		CreateHill_Ground(HILL::HILL_E, VGet(_pos.x, _pos.y - 13, _pos.z + 1370), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);
		CreateHill_Ground(HILL::HILL_E, VGet(_pos.x + 1370, _pos.y - 13, _pos.z), VGet(0.0f, OBJECT_ROT * 2, 0.0f) * DEGREE);
		CreateHill_Ground(HILL::HILL_E, VGet(_pos.x - 1370, _pos.y - 13, _pos.z), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		CreateHill_Ground(HILL::HILL_N, VGet(_pos.x - 1370, _pos.y - 10, _pos.z - 1370), VGet(0.0f, OBJECT_ROT * 3, 0.0f) * DEGREE);
		CreateHill_Ground(HILL::HILL_N, VGet(_pos.x + 1370, _pos.y - 10, _pos.z - 1370), VGet(0.0f, OBJECT_ROT * 2, 0.0f) * DEGREE);

		CreateHill_Ground(HILL::HILL_N, VGet(_pos.x - 1370, _pos.y - 10, _pos.z + 1370), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		CreateHill_Ground(HILL::HILL_N, VGet(_pos.x + 1370, _pos.y - 10, _pos.z + 1370), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);

		break;

	case MAP::LOAD:
		CreateGround(GROUND::N_FLEAM,VGet(_pos.x, _pos.y, _pos.z - (GROUND_POS_Z * 4)), VGet(0.0f, _rot.y, 0.0f) * DEGREE);
		CreateGround(GROUND::N_FLEAM, VGet(_pos.x, _pos.y, _pos.z - (GROUND_POS_Z * 3)), VGet(0.0f, _rot.y, 0.0f) * DEGREE);
		CreateGround(GROUND::N_FLEAM, VGet(_pos.x, _pos.y, _pos.z - (GROUND_POS_Z * 2)), VGet(0.0f, _rot.y, 0.0f) * DEGREE);
		CreateGround(GROUND::N_FLEAM, VGet(_pos.x, _pos.y, _pos.z - (GROUND_POS_Z * 1)), VGet(0.0f, _rot.y, 0.0f) * DEGREE);
		CreateGround(GROUND::N_FLEAM, VGet(_pos.x, _pos.y, _pos.z), VGet(0.0f, _rot.y, 0.0f) * DEGREE);

		CreateWall(WALL::N_WALL,VGet(_pos.x, _pos.y + WALL_POS_Y, _pos.z - (GROUND_POS_Z * 4)), VGet(0.0f, _rot.y, 0.0f) * DEGREE);
		CreateWall(WALL::N_WALL, VGet(_pos.x, _pos.y + WALL_POS_Y, _pos.z - (GROUND_POS_Z * 3)), VGet(0.0f, _rot.y, 0.0f) * DEGREE);
		CreateWall(WALL::N_WALL, VGet(_pos.x, _pos.y + WALL_POS_Y, _pos.z - (GROUND_POS_Z * 2)), VGet(0.0f, _rot.y, 0.0f) * DEGREE);
		CreateWall(WALL::N_WALL, VGet(_pos.x, _pos.y + WALL_POS_Y, _pos.z - (GROUND_POS_Z * 1)), VGet(0.0f, _rot.y, 0.0f) * DEGREE);
		CreateWall(WALL::N_WALL, VGet(_pos.x, _pos.y + WALL_POS_Y, _pos.z), VGet(0.0f, _rot.y, 0.0f) * DEGREE);

		CreateCeiling(CEILING::N_CEILING, VGet(_pos.x, _pos.y + CEILING_POS_Y, _pos.z - (GROUND_POS_Z * 4)), VGet(0.0f, _rot.y, 0.0f) * DEGREE);
		CreateCeiling(CEILING::N_CEILING, VGet(_pos.x, _pos.y + CEILING_POS_Y, _pos.z - (GROUND_POS_Z * 3)), VGet(0.0f, _rot.y, 0.0f) * DEGREE);
		CreateCeiling(CEILING::N_CEILING, VGet(_pos.x, _pos.y + CEILING_POS_Y, _pos.z - (GROUND_POS_Z * 2)), VGet(0.0f, _rot.y, 0.0f) * DEGREE);
		CreateCeiling(CEILING::N_CEILING, VGet(_pos.x, _pos.y + CEILING_POS_Y, _pos.z - (GROUND_POS_Z * 1)), VGet(0.0f, _rot.y, 0.0f) * DEGREE);
		CreateCeiling(CEILING::N_CEILING, VGet(_pos.x, _pos.y + CEILING_POS_Y, _pos.z), VGet(0.0f, _rot.y, 0.0f) * DEGREE);

		CreateColision(COLLISION::N_COL, VGet(_pos.x + 675, _pos.y + COLLISION_BLOCK_Y, _pos.z  + 130), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x + 750, _pos.y + COLLISION_BLOCK_Y, _pos.z + 130), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		CreateColision(COLLISION::N_COL, VGet(_pos.x + 675, _pos.y + COLLISION_BLOCK_Y, _pos.z - 30), VGet(0.0f,0.0f, 0.0f) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x + 675, _pos.y + COLLISION_BLOCK_Y, _pos.z - 930), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x + 675, _pos.y + COLLISION_BLOCK_Y, _pos.z - 1830), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x + 675, _pos.y + COLLISION_BLOCK_Y, _pos.z - 2730), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x + 675, _pos.y + COLLISION_BLOCK_Y, _pos.z - 3380), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x + 675, _pos.y + COLLISION_BLOCK_Y, _pos.z - 3520), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		CreateColision(COLLISION::N_COL, VGet(_pos.x + 675, _pos.y + COLLISION_BLOCK_Y, _pos.z - 3690), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x + 750, _pos.y + COLLISION_BLOCK_Y, _pos.z - 3690), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		CreateColision(COLLISION::N_COL, VGet(_pos.x - 675, _pos.y + COLLISION_BLOCK_Y, _pos.z + 130), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x - 750, _pos.y + COLLISION_BLOCK_Y, _pos.z + 130), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		CreateColision(COLLISION::N_COL, VGet(_pos.x - 675, _pos.y + COLLISION_BLOCK_Y, _pos.z - 30), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x - 675, _pos.y + COLLISION_BLOCK_Y, _pos.z - 930), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		CreateColision(COLLISION::N_COL,VGet(_pos.x - 675, _pos.y + COLLISION_BLOCK_Y, _pos.z - 1830), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		CreateColision(COLLISION::N_COL,VGet(_pos.x - 675, _pos.y + COLLISION_BLOCK_Y, _pos.z - 2730), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x - 675, _pos.y + COLLISION_BLOCK_Y, _pos.z - 3380), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x - 675, _pos.y + COLLISION_BLOCK_Y, _pos.z - 3520), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		CreateColision(COLLISION::N_COL, VGet(_pos.x - 675, _pos.y + COLLISION_BLOCK_Y, _pos.z - 3690), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x - 750, _pos.y + COLLISION_BLOCK_Y, _pos.z - 3690), VGet(0.0f, 0.0f, 0.0f) * DEGREE);


		CreateColision(COLLISION::N_COL, VGet(_pos.x, _pos.y - 40, _pos.z + 500), VGet(0.0f, OBJECT_ROT, OBJECT_ROT) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x, _pos.y - 40, _pos.z + 70), VGet(0.0f, OBJECT_ROT, OBJECT_ROT) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x, _pos.y - 40, _pos.z - 700), VGet(0.0f, OBJECT_ROT, OBJECT_ROT) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x, _pos.y - 40, _pos.z - 1400), VGet(0.0f, OBJECT_ROT, OBJECT_ROT) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x, _pos.y - 40, _pos.z - 2100), VGet(0.0f, OBJECT_ROT, OBJECT_ROT) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x, _pos.y - 40, _pos.z - 2800), VGet(0.0f, OBJECT_ROT, OBJECT_ROT) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x, _pos.y - 40, _pos.z - 3500), VGet(0.0f, OBJECT_ROT, OBJECT_ROT) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x, _pos.y - 40, _pos.z - 3750), VGet(0.0f, OBJECT_ROT, OBJECT_ROT) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x, _pos.y - 40, _pos.z - 4250), VGet(0.0f, OBJECT_ROT, OBJECT_ROT) * DEGREE);

		CreateColision(COLLISION::N_COL, VGet(_pos.x , _pos.y + 750, _pos.z + 70), VGet(0.0f, OBJECT_ROT, OBJECT_ROT) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x, _pos.y + 750, _pos.z - 700), VGet(0.0f, OBJECT_ROT, OBJECT_ROT) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x, _pos.y + 750, _pos.z - 1400), VGet(0.0f, OBJECT_ROT, OBJECT_ROT) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x, _pos.y + 750, _pos.z - 2100), VGet(0.0f, OBJECT_ROT, OBJECT_ROT) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x, _pos.y + 750, _pos.z - 2800), VGet(0.0f, OBJECT_ROT, OBJECT_ROT) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x, _pos.y + 750, _pos.z - 3500), VGet(0.0f, OBJECT_ROT, OBJECT_ROT) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x, _pos.y + 750, _pos.z - 3750), VGet(0.0f, OBJECT_ROT, OBJECT_ROT) * DEGREE);


		Create(StageObjectType::HILL, VGet(_pos.x, _pos.y + 700, _pos.z), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		Create(StageObjectType::HILL, VGet(_pos.x, _pos.y + 700, _pos.z - 500), VGet(0.0f, OBJECT_ROT * 2, 0.0f) * DEGREE);

		Create(StageObjectType::HILL, VGet(_pos.x, _pos.y + 700, _pos.z - 2500), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		Create(StageObjectType::HILL, VGet(_pos.x, _pos.y + 700, _pos.z - 3000), VGet(0.0f, OBJECT_ROT * 2, 0.0f) * DEGREE);
		break;
	case MAP::L_LOAD:
		CreateGround(GROUND::N_FLEAM, VGet(_pos.x - 12, _pos.y, _pos.z - 810), VGet(_rot.x, _rot.y + 180.0f, _rot.z) * DEGREE);

		CreateGround(GROUND::L_FLEAM, VGet(_pos.x + 300, _pos.y + 394, _pos.z - 2), VGet(_rot.x, _rot.y, _rot.z) * DEGREE);

		CreateGround(GROUND::N_FLEAM, VGet(_pos.x + 1109, _pos.y, _pos.z + 310), VGet(_rot.x, _rot.y * 0.0f, _rot.z) * DEGREE);
		CreateCeiling(CEILING::C_CEILING, VGet(_pos.x + 410, _pos.y + 800, _pos.z - 116), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);

		CreateColision(COLLISION::N_COL, VGet(_pos.x + 1250, _pos.y + COLLISION_BLOCK_Y, _pos.z - 353), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x + 655, _pos.y + COLLISION_BLOCK_Y, _pos.z - 1020), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		CreateColision(COLLISION::N_COL, VGet(_pos.x - 680, _pos.y + COLLISION_BLOCK_Y, _pos.z - 500), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x - 680, _pos.y + COLLISION_BLOCK_Y, _pos.z + 100), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x + 770, _pos.y + COLLISION_BLOCK_Y, _pos.z + 975), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x + 170, _pos.y + COLLISION_BLOCK_Y, _pos.z + 975), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x - 300, _pos.y + COLLISION_BLOCK_Y, _pos.z + 975), VGet(0.0f, 40.0f, 0.0f) * DEGREE);

		Create(StageObjectType::HILL, VGet(_pos.x, _pos.y + 700, _pos.z), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);

		CreateColision(COLLISION::N_COL, VGet(_pos.x, _pos.y + 750, _pos.z - 850), VGet(0.0f, OBJECT_ROT, 90.0f) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x, _pos.y + 750, _pos.z - 700), VGet(0.0f, OBJECT_ROT, OBJECT_ROT) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x, _pos.y + 750, _pos.z), VGet(0.0f, OBJECT_ROT, OBJECT_ROT) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x, _pos.y + 750, _pos.z + 700), VGet(0.0f, OBJECT_ROT, OBJECT_ROT) * DEGREE);

		CreateColision(COLLISION::N_COL, VGet(_pos.x + 700, _pos.y + 750, _pos.z + 300), VGet(0.0f, 0.0f, OBJECT_ROT) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x + 1200, _pos.y + 750, _pos.z + 300), VGet(0.0f, 0.0f, OBJECT_ROT) * DEGREE);

		CreateColision(COLLISION::N_COL, VGet(_pos.x, _pos.y - 40, _pos.z - 850), VGet(0.0f, OBJECT_ROT, 90.0f) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x, _pos.y - 40, _pos.z - 700), VGet(0.0f, OBJECT_ROT, OBJECT_ROT) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x, _pos.y - 40, _pos.z), VGet(0.0f, OBJECT_ROT, OBJECT_ROT) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x, _pos.y - 40, _pos.z + 700), VGet(0.0f, OBJECT_ROT, OBJECT_ROT) * DEGREE);

		CreateColision(COLLISION::N_COL, VGet(_pos.x + 700, _pos.y - 40, _pos.z + 300), VGet(0.0f, 0.0f, OBJECT_ROT) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x + 1200, _pos.y - 40, _pos.z + 300), VGet(0.0f, 0.0f, OBJECT_ROT) * DEGREE);
		//VGet(_rot.x, _rot.y, _rot.z)
		break;
	case MAP::WIGHT_LOAD:
		CreateGround(GROUND::N_FLEAM, VGet(_pos.x, _pos.y, _pos.z), VGet(0.0f, _rot.y, 0.0f) * DEGREE);
		CreateGround(GROUND::N_FLEAM, VGet(_pos.x + (GROUND_POS_Z * 1), _pos.y, _pos.z), VGet(0.0f, _rot.y, 0.0f) * DEGREE);
		CreateGround(GROUND::N_FLEAM, VGet(_pos.x + (GROUND_POS_Z * 2), _pos.y, _pos.z), VGet(0.0f, _rot.y, 0.0f) * DEGREE);

		CreateWall(WALL::N_WALL, VGet(_pos.x, _pos.y + WALL_POS_Y, _pos.z), VGet(0.0f, _rot.y, 0.0f) * DEGREE);
		CreateWall(WALL::N_WALL, VGet(_pos.x + (GROUND_POS_Z * 1), _pos.y + WALL_POS_Y, _pos.z), VGet(0.0f, _rot.y, 0.0f) * DEGREE);
		CreateWall(WALL::N_WALL, VGet(_pos.x + (GROUND_POS_Z * 2), _pos.y + WALL_POS_Y, _pos.z), VGet(0.0f, _rot.y, 0.0f) * DEGREE);

		CreateCeiling(CEILING::N_CEILING, VGet(_pos.x, _pos.y + CEILING_POS_Y, _pos.z), VGet(0.0f, _rot.y, 0.0f) * DEGREE);
		CreateCeiling(CEILING::N_CEILING, VGet(_pos.x + (GROUND_POS_Z * 1), _pos.y + CEILING_POS_Y, _pos.z), VGet(0.0f, _rot.y, 0.0f) * DEGREE);
		CreateCeiling(CEILING::N_CEILING, VGet(_pos.x + (GROUND_POS_Z * 2), _pos.y + CEILING_POS_Y, _pos.z), VGet(0.0f, _rot.y, 0.0f) * DEGREE);

		CreateColision(COLLISION::N_COL, VGet(_pos.x - 148, _pos.y + COLLISION_BLOCK_Y, _pos.z + 665), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x - 148, _pos.y + COLLISION_BLOCK_Y, _pos.z - 665), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);

		CreateColision(COLLISION::N_COL, VGet(_pos.x - 148, _pos.y + COLLISION_BLOCK_Y, _pos.z + 750), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x - 148, _pos.y + COLLISION_BLOCK_Y, _pos.z - 750), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);

		CreateColision(COLLISION::N_COL, VGet(_pos.x + 48, _pos.y + COLLISION_BLOCK_Y, _pos.z + 665), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x + 1320, _pos.y + COLLISION_BLOCK_Y, _pos.z + 665), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x + 1720, _pos.y + COLLISION_BLOCK_Y, _pos.z + 665), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);

		CreateColision(COLLISION::N_COL, VGet(_pos.x + 49, _pos.y + COLLISION_BLOCK_Y, _pos.z - 665), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x + 1320, _pos.y + COLLISION_BLOCK_Y, _pos.z - 665), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x + 1720, _pos.y + COLLISION_BLOCK_Y, _pos.z - 665), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);

		CreateColision(COLLISION::N_COL, VGet(_pos.x + 1890, _pos.y + COLLISION_BLOCK_Y, _pos.z - 665), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x + 1890, _pos.y + COLLISION_BLOCK_Y, _pos.z - 750), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);

		CreateColision(COLLISION::N_COL, VGet(_pos.x + 1890, _pos.y + COLLISION_BLOCK_Y, _pos.z + 665), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x + 1890, _pos.y + COLLISION_BLOCK_Y, _pos.z + 750), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);



		Create(StageObjectType::HILL, VGet(_pos.x, _pos.y + 700, _pos.z), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);
		Create(StageObjectType::HILL, VGet(_pos.x + 700, _pos.y + 700, _pos.z), VGet(0.0f, OBJECT_ROT * 3, 0.0f) * DEGREE);
		Create(StageObjectType::HILL, VGet(_pos.x + 1200, _pos.y + 700, _pos.z), VGet(0.0f, OBJECT_ROT * 3, 0.0f) * DEGREE);

		CreateColision(COLLISION::N_COL, VGet(_pos.x - 540, _pos.y - 40, _pos.z), VGet(0.0f, 0.0f, OBJECT_ROT) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x - 40, _pos.y - 40, _pos.z), VGet(0.0f, 0.0f, OBJECT_ROT) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x, _pos.y - 40, _pos.z), VGet(0.0f, 0.0f, OBJECT_ROT) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x + 700, _pos.y - 40, _pos.z), VGet(0.0f, 0.0f, OBJECT_ROT) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x + 1200, _pos.y - 40, _pos.z), VGet(0.0f, 0.0f, OBJECT_ROT) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x + 1900, _pos.y - 40, _pos.z), VGet(0.0f, 0.0f, OBJECT_ROT) * DEGREE);
		//CreateColision(COLLISION::N_COL, VGet(_pos.x + 2400, _pos.y - 40, _pos.z), VGet(0.0f, 0.0f, OBJECT_ROT) * DEGREE);

		CreateColision(COLLISION::N_COL, VGet(_pos.x, _pos.y + 750, _pos.z), VGet(0.0f, 0.0f, OBJECT_ROT) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x + 700, _pos.y + 750, _pos.z), VGet(0.0f, 0.0f, OBJECT_ROT) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x + 1200, _pos.y + 750, _pos.z), VGet(0.0f, 0.0f, OBJECT_ROT) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x + 1900, _pos.y + 750, _pos.z), VGet(0.0f, 0.0f, OBJECT_ROT) * DEGREE);

		break;
	case MAP::SLOAP:
		CreateGround(GROUND::SLOAP, VGet(_pos.x, _pos.y + 392, _pos.z), VGet(_rot.x, _rot.y, _rot.z) * DEGREE);

		//792
		CreateWall(WALL::S_WALL, VGet(_pos.x ,_pos.y + 792, _pos.z), VGet(_rot.x, _rot.y, _rot.z) * DEGREE);

		CreateCeiling(CEILING::S_CEILING, VGet(_pos.x, _pos.y + 1188, _pos.z - 22), VGet(_rot.x, _rot.y, _rot.z) * DEGREE);

		CreateColision(COLLISION::S_COL, VGet(_pos.x - 50, _pos.y + 500, _pos.z - 665), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);

		CreateColision(COLLISION::S_COL, VGet(_pos.x - 52, _pos.y + 500, _pos.z + 665), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);

		CreateColision(COLLISION::S_COL, VGet(_pos.x - 50, _pos.y + 800, _pos.z - 665), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);

		CreateColision(COLLISION::S_COL, VGet(_pos.x - 52, _pos.y + 800, _pos.z + 665), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);

		CreateColision(COLLISION::L_COL, VGet(_pos.x, _pos.y + 390, _pos.z), VGet(_rot.x, _rot.y, _rot.z) * DEGREE);

		CreateColision(COLLISION::N_COL, VGet(_pos.x + 900, _pos.y + 750, _pos.z), VGet(0.0f, 0.0f, OBJECT_ROT) * DEGREE);

		CreateColision(COLLISION::N_COL, VGet(_pos.x - 800, _pos.y + 1530, _pos.z), VGet(0.0f, 0.0f, OBJECT_ROT) * DEGREE);

		CreateColision(COLLISION::N_COL, VGet(_pos.x - 200, _pos.y + 1230, _pos.z), VGet(0.0f, 0.0f, 60.0f) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x + 200, _pos.y + 1030, _pos.z), VGet(0.0f, 0.0f, 60.0f) * DEGREE);
		break;
	case MAP::ATHLETICS:
		//Create(StageObjectType::SMALL_SQUARE, VGet(_pos.x, _pos.y, _pos.z), VGet(0.0f, 90.0f, 0.0f) * DEGREE);
		/*
		Create(StageObjectType::HILL, VGet(_pos.x, _pos.y, _pos.z), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		Create(StageObjectType::HILL, VGet(_pos.x + 3000, _pos.y, _pos.z + 2000), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		Create(StageObjectType::HILL, VGet(_pos.x - 3000, _pos.y, _pos.z + 2000), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		Create(StageObjectType::HILL, VGet(_pos.x, _pos.y, _pos.z + 5000), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		Create(StageObjectType::HILL, VGet(_pos.x + 4500, _pos.y, _pos.z + 7000), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		Create(StageObjectType::HILL, VGet(_pos.x - 3000, _pos.y, _pos.z + 8000), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		Create(StageObjectType::HILL, VGet(_pos.x - 6000, _pos.y, _pos.z + 9500), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		Create(StageObjectType::HILL, VGet(_pos.x - 5999, _pos.y, _pos.z + 13650), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		Create(StageObjectType::HILL, VGet(_pos.x + 3000, _pos.y, _pos.z + 8000), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		Create(StageObjectType::HILL, VGet(_pos.x + 500, _pos.y, _pos.z+ 11000), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		CreateHill_Ground(VGet(_pos.x - 80000, _pos.y + 250, _pos.z + 10995), VGet(90.0f, 0.0f, 0.0f) * DEGREE);
		CreateHill_Ground(VGet(_pos.x - 10000, _pos.y + 250, _pos.z + 10995), VGet(90.0f, 0.0f, 0.0f) * DEGREE);


		Create(StageObjectType::HILL, VGet(_pos.x - 6945, _pos.y, _pos.z + 9900), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		Create(StageObjectType::HILL, VGet(_pos.x - 6945, _pos.y, _pos.z + 9100), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		Create(StageObjectType::HILL, VGet(_pos.x - 7895, _pos.y, _pos.z + 9900), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		Create(StageObjectType::HILL, VGet(_pos.x - 7895, _pos.y, _pos.z + 9100), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		Create(StageObjectType::HILL, VGet(_pos.x - 8845, _pos.y, _pos.z + 9900), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		Create(StageObjectType::HILL, VGet(_pos.x - 8845, _pos.y, _pos.z + 9100), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		Create(StageObjectType::HILL, VGet(_pos.x - 9795, _pos.y, _pos.z + 9900), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		Create(StageObjectType::HILL, VGet(_pos.x - 9795, _pos.y, _pos.z + 9100), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		Create(StageObjectType::HILL, VGet(_pos.x - 6945, _pos.y, _pos.z + 10735), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		Create(StageObjectType::HILL, VGet(_pos.x - 6945, _pos.y, _pos.z + 11570), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		Create(StageObjectType::HILL, VGet(_pos.x - 7895, _pos.y, _pos.z + 10735), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		Create(StageObjectType::HILL, VGet(_pos.x - 7895, _pos.y, _pos.z + 11570), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		Create(StageObjectType::HILL, VGet(_pos.x - 8845, _pos.y, _pos.z + 10735), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		Create(StageObjectType::HILL, VGet(_pos.x - 8845, _pos.y, _pos.z + 11570), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		Create(StageObjectType::HILL, VGet(_pos.x - 9795, _pos.y, _pos.z + 10735), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		Create(StageObjectType::HILL, VGet(_pos.x - 9795, _pos.y, _pos.z + 11570), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		Create(StageObjectType::HILL, VGet(_pos.x - 6945, _pos.y, _pos.z + 12400), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		Create(StageObjectType::HILL, VGet(_pos.x - 6945, _pos.y, _pos.z + 13220), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		Create(StageObjectType::HILL, VGet(_pos.x - 7895, _pos.y, _pos.z + 12400), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		Create(StageObjectType::HILL, VGet(_pos.x - 7895, _pos.y, _pos.z + 13220), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		Create(StageObjectType::HILL, VGet(_pos.x - 8845, _pos.y, _pos.z + 12400), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		Create(StageObjectType::HILL, VGet(_pos.x - 8845, _pos.y, _pos.z + 13220), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		Create(StageObjectType::HILL, VGet(_pos.x - 9795, _pos.y, _pos.z + 12400), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		Create(StageObjectType::HILL, VGet(_pos.x - 9795, _pos.y, _pos.z + 13220), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		Create(StageObjectType::HILL, VGet(_pos.x - 6945, _pos.y, _pos.z + 14050), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		Create(StageObjectType::HILL, VGet(_pos.x - 7895, _pos.y, _pos.z + 14050), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		Create(StageObjectType::HILL, VGet(_pos.x - 8845, _pos.y, _pos.z + 14050), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		Create(StageObjectType::HILL, VGet(_pos.x - 9795, _pos.y, _pos.z + 14050), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		*/
		break;
	case MAP::NOM_SQUARE:
		//CreateColision(COLLISION::P_GATE, VGet(_pos.x + NOM_SQUARE_GATE_POS_X, _pos.y, _pos.z + 105), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);
		GateGround(GATE::P_GATE, VGet(_pos.x + NOM_SQUARE_GATE_POS_X, _pos.y, _pos.z + 105), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);
		Create(StageObjectType::GATE_FLAME, VGet(_pos.x + NOM_SQUARE_GATE_POS_X, _pos.y + NOM_SQUARE_GATE_POS_Y, _pos.z + 105), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);

		CreateColision(COLLISION::P_GATE, VGet(_pos.x + NOM_SQUARE_GATE_POS_X, _pos.y, _pos.z + 4490), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);
		GateGround(GATE::F_GATE, VGet(_pos.x + NOM_SQUARE_GATE_POS_X, _pos.y, _pos.z + 4490), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);
		Create(StageObjectType::GATE_FLAME, VGet(_pos.x + NOM_SQUARE_GATE_POS_X, _pos.y + NOM_SQUARE_GATE_POS_Y, _pos.z + 4490), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);

		//CreateColision(COLLISION::HILL_COL, VGet(_pos.x + 4105, _pos.y - 33, _pos.z + 4105), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		CreateHill_Ground(HILL::G_HILL, VGet(_pos.x + 20, _pos.y + 1000, _pos.z + 237), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);
		CreateHill_Ground(HILL::G_HILL, VGet(_pos.x + 20, _pos.y + 1000, _pos.z + 4358), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);

		CreateColision(COLLISION::HILL_G_COL, VGet(_pos.x + 20, _pos.y + 1000, _pos.z + 240 + 50), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);
		CreateColision(COLLISION::HILL_G_COL, VGet(_pos.x + 20, _pos.y + 1000, _pos.z + 4350 - 50), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);

		CreateHill_Ground(HILL::N_HILL, VGet(_pos.x - 2055, _pos.y + 1000, _pos.z + 2320), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		CreateHill_Ground(HILL::N_HILL, VGet(_pos.x + 2055, _pos.y + 1000, _pos.z + 2320), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		CreateColision(COLLISION::HILL_W_COL, VGet(_pos.x - 2055 + 50, _pos.y + 1000, _pos.z + 2320), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		CreateColision(COLLISION::HILL_W_COL, VGet(_pos.x + 2055 - 50, _pos.y + 1000, _pos.z + 2320), VGet(0.0f, 0.0f, 0.0f) * DEGREE);



		CreateColision(COLLISION::HILL_COL, VGet(GROUND_POS_X + 20, -20, 3400 + 2320), VGet(0.0f, 0.0f, 0.0f));
		CreateHill_Ground(HILL::HILL_CEILING, VGet(GROUND_POS_X + 20, GROUND_POS_Y + 2050, 3400 + 2320), VGet(0.0f, 0.0f, OBJECT_ROT * 2) * DEGREE);
		Map(MAP::HILL_FLORE, VGet(GROUND_POS_X + 20, GROUND_POS_Y, 3400 + 2320), VGet(0.0f, 0.0f, 0.0f));

		break;
	case MAP::G2_SQUARE:

		CreateColision(COLLISION::W_GATE, VGet(_pos.x - 2200, _pos.y, _pos.z), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		GateGround(GATE::W_GATE, VGet(_pos.x - 2200, _pos.y, _pos.z), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x - 2200, _pos.y - 40, _pos.z), VGet(0.0f, 0.0f, OBJECT_ROT) * DEGREE);
		Create(StageObjectType::GATE_FLAME, VGet(_pos.x  - 2200, _pos.y + NOM_SQUARE_GATE_POS_Y, _pos.z), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		CreateHill_Ground(HILL::HILL_CEILING, VGet(_pos.x, _pos.y + 2050, _pos.z), VGet(OBJECT_ROT * 2, 0.0f, 0.0f) * DEGREE);

		Map(MAP::HILL_FLORE, VGet(_pos.x, _pos.y, _pos.z), VGet(180.0f, 0.0f, 0.0f) * DEGREE);
		CreateColision(COLLISION::HILL_COL, VGet(_pos.x, -20, _pos.z), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		CreateHill_Ground(HILL::G_HILL, VGet(_pos.x - 2065, _pos.y + 1000, _pos.z), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		CreateHill_Ground(HILL::N_HILL, VGet(_pos.x, _pos.y + 1000, _pos.z - 2055), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);
		CreateHill_Ground(HILL::N_HILL, VGet(_pos.x, _pos.y + 1000, _pos.z + 2075), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);

		CreateColision(COLLISION::HILL_G_COL, VGet(_pos.x - 2070 + 50, _pos.y + 1000, _pos.z), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		CreateColision(COLLISION::HILL_W_COL, VGet(_pos.x, _pos.y + 1000, _pos.z - 2055 + 50), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);
		CreateColision(COLLISION::HILL_W_COL, VGet(_pos.x, _pos.y + 1000, _pos.z + 2075 - 50), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);
		CreateColision(COLLISION::HILL_W_COL, VGet(_pos.x + 50, _pos.y + 1000, _pos.z + 2075 - 50), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);


		CreateHill_Ground(HILL::HILL_CEILING, VGet(_pos.x + 4105, _pos.y + 2050, _pos.z), VGet(OBJECT_ROT * 2, 0.0f, 0.0f) * DEGREE);

		Map(MAP::HILL_FLORE, VGet(_pos.x + 4105, _pos.y, _pos.z), VGet(OBJECT_ROT * 2, 0.0f, 0.0f) * DEGREE);

		CreateColision(COLLISION::HILL_COL, VGet(_pos.x + 4105, -20, _pos.z), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		CreateHill_Ground(HILL::N_HILL, VGet(_pos.x + 4105, _pos.y + 1000, _pos.z - 2055), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);
		CreateHill_Ground(HILL::N_HILL, VGet(_pos.x + 6160, _pos.y + 1000, _pos.z), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		CreateColision(COLLISION::HILL_W_COL, VGet(_pos.x + 4105, _pos.y + 1000, _pos.z - 2055 + 50), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);
		CreateColision(COLLISION::HILL_W_COL, VGet(_pos.x + 6160 - 50, _pos.y + 1000, _pos.z), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		CreateHill_Ground(HILL::HILL_CEILING, VGet(_pos.x + 4105, _pos.y + 2050, _pos.z + 4105), VGet(OBJECT_ROT * 2, 0.0f, 0.0f) * DEGREE);

		Map(MAP::HILL_FLORE, VGet(_pos.x + 4105, _pos.y, _pos.z + 4105), VGet(OBJECT_ROT * 2, 0.0f, 0.0f) * DEGREE);

		CreateColision(COLLISION::HILL_COL, VGet(_pos.x + 4105, _pos.y - 20, _pos.z + 4105), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		CreateHill_Ground(HILL::N_HILL, VGet(_pos.x + 6160, _pos.y + 1000, _pos.z + 4105), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		CreateHill_Ground(HILL::N_HILL, VGet(_pos.x + 2050, _pos.y + 1000, _pos.z + 4105), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		CreateColision(COLLISION::HILL_W_COL, VGet(_pos.x + 6110, _pos.y + 1000, _pos.z + 4105), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		CreateColision(COLLISION::HILL_W_COL, VGet(_pos.x + 2100, _pos.y + 1000, _pos.z + 4105), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		CreateColision(COLLISION::HILL_W_COL, VGet(_pos.x + 2100, _pos.y + 1000, _pos.z + 4055), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		CreateHill_Ground(HILL::HILL_CEILING, VGet(_pos.x + 4105, _pos.y + 2050, _pos.z + 8215), VGet(OBJECT_ROT * 2, 0.0f, 0.0f) * DEGREE);
		Map(MAP::HILL_FLORE, VGet(_pos.x + 4105, _pos.y, _pos.z + 8215), VGet(180.0f, 0.0f, 0.0f) * DEGREE);

		CreateColision(COLLISION::HILL_COL, VGet(_pos.x + 4105, _pos.y - 20, _pos.z + 8215), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		CreateHill_Ground(HILL::N_HILL, VGet(_pos.x + 6160, _pos.y + 1000, _pos.z + 8215), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		CreateHill_Ground(HILL::G_HILL, VGet(_pos.x + 2050, _pos.y + 1000, _pos.z + 8215), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		CreateHill_Ground(HILL::N_HILL, VGet(_pos.x + 4105, _pos.y + 1000, _pos.z + 10260), VGet(0.0f, OBJECT_ROT * 3, 0.0f) * DEGREE);

		CreateColision(COLLISION::HILL_W_COL, VGet(_pos.x + 6110, _pos.y + 1000, _pos.z + 8215), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		CreateColision(COLLISION::HILL_G_COL, VGet(_pos.x + 2105, _pos.y + 1000, _pos.z + 8215), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		CreateColision(COLLISION::HILL_W_COL, VGet(_pos.x + 4105, _pos.y + 1000, _pos.z + 10210), VGet(0.0f, OBJECT_ROT * 3, 0.0f) * DEGREE);

		CreateColision(COLLISION::H_GATE, VGet(_pos.x + 1900, _pos.y, _pos.z + 8215), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		GateGround(GATE::H_GATE, VGet(_pos.x + 1900, _pos.y, _pos.z + 8215), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		CreateColision(COLLISION::N_COL, VGet(_pos.x + 1900, _pos.y - 40, _pos.z + 8215), VGet(0.0f, 0.0f, OBJECT_ROT) * DEGREE);
		Create(StageObjectType::GATE_FLAME, VGet(_pos.x + 1900, _pos.y + NOM_SQUARE_GATE_POS_Y, _pos.z + 8215), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		for (int i = 0; i < 9; i++)
		{
			Create(StageObjectType::BIG_SQUARE, VGet(_pos.x + 6000, _pos.y + 630, (_pos.z - 1350) + 1370 * i), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		}
		for (int i = 0; i < 3; i++)
		{
			Create(StageObjectType::BIG_SQUARE, VGet((_pos.x + 5090) - 1370 * i, _pos.y + 630, _pos.z + 10000), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);
		}

		for (int i = 0; i < 3; i++)
		{
			Create(StageObjectType::BIG_SQUARE, VGet((_pos.x + 5090) - 1370 * i, _pos.y + 630, _pos.z + 2350), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);


		}

		for (int i = 0; i < 9; i++)
		{
			CreateColision(COLLISION::H_COL, VGet(_pos.x + 6000, _pos.y + 600, (_pos.z - 1350) + 1370 * i), VGet(0.0f, 0.0f, OBJECT_ROT) * DEGREE);
		}

		for (int i = 0; i < 3; i++)
		{
			CreateColision(COLLISION::H_COL, VGet((_pos.x + 5090) - 1370 * i, _pos.y + 600, _pos.z + 10000), VGet(0.0f, OBJECT_ROT, OBJECT_ROT) * DEGREE);
		}

		for (int i = 0; i < 3; i++)
		{
			CreateColision(COLLISION::H_COL, VGet((_pos.x + 5090) - 1370 * i, _pos.y + 600, _pos.z + 2350), VGet(0.0f, OBJECT_ROT, OBJECT_ROT) * DEGREE);
		}

		Create(StageObjectType::HILL, VGet(_pos.x + 5950, _pos.y + 570, (_pos.z - 1350) + 1370 * 2), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		Create(StageObjectType::HILL, VGet(_pos.x + 5950, _pos.y + 570, (_pos.z - 1350) + 1370 * 5), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		Create(StageObjectType::HILL, VGet(_pos.x + 5950, _pos.y + 570, (_pos.z - 1350) + 1370 * 7), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		Create(StageObjectType::HILL, VGet(_pos.x + 5950, _pos.y + 570, (_pos.z - 1350) + 1370 * 9), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		Create(StageObjectType::HILL, VGet(_pos.x + 5950, _pos.y + 570, _pos.z - 1350), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		Create(StageObjectType::HILL, VGet(_pos.x + 4990, _pos.y + 570, _pos.z + 2350), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);

		Create(StageObjectType::HILL, VGet(_pos.x + 2550, _pos.y + 570, _pos.z + 2350), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);

		Create(StageObjectType::HILL, VGet(_pos.x + 3620, _pos.y + 570, _pos.z + 10000), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);

		Create(StageObjectType::SCAFFOLD, VGet(_pos.x + 2250, _pos.y + 525, _pos.z + 9750), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);
		Create(StageObjectType::SCAFFOLD, VGet(_pos.x + 2250, _pos.y + 525, _pos.z + 2100), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);
		Create(StageObjectType::SCAFFOLD, VGet(_pos.x + 2250, _pos.y + 525, _pos.z + 2600), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);
		Create(StageObjectType::SCAFFOLD, VGet(_pos.x + 5740, _pos.y + 525, _pos.z - 1910), VGet(0.0f, 0.0f, 0.0f) * DEGREE);


		break;
	case MAP::FINAL_SQUARE:

		CreateColision(COLLISION::HILL_COL, VGet(_pos.x, _pos.y - 20, _pos.z), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		CreateColision(COLLISION::HILL_COL, VGet(_pos.x, _pos.y - 20, _pos.z + 4105), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
		CreateColision(COLLISION::HILL_COL, VGet(_pos.x, _pos.y - 20, _pos.z - 4105), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

		CreateHill_Ground(HILL::HILL_CEILING, VGet(_pos.x, _pos.y + 2050, _pos.z), VGet(0.0f, 0.0f, OBJECT_ROT * 2) * DEGREE);
		CreateHill_Ground(HILL::HILL_CEILING, VGet(_pos.x, _pos.y + 2050, _pos.z - 4105), VGet(0.0f, 0.0f, OBJECT_ROT * 2) * DEGREE);
		CreateHill_Ground(HILL::HILL_CEILING, VGet(_pos.x, _pos.y + 2050, _pos.z + 4105), VGet(0.0f, 0.0f, OBJECT_ROT * 2) * DEGREE);

			Map(MAP::HILL_FLORE, VGet(_pos.x, _pos.y, _pos.z), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
			Map(MAP::HILL_FLORE, VGet(_pos.x , _pos.y, _pos.z - 4105), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
			Map(MAP::HILL_FLORE, VGet(_pos.x, _pos.y, _pos.z + 4105), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

			CreateColision(COLLISION::HILL_COL, VGet(_pos.x - 4105, _pos.y -20, _pos.z), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
			CreateColision(COLLISION::HILL_COL, VGet(_pos.x - 4105, _pos.y - 20, _pos.z + 4105), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
			CreateColision(COLLISION::HILL_COL, VGet(_pos.x - 4105, _pos.y - 20, _pos.z - 4105), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

			CreateHill_Ground(HILL::HILL_CEILING, VGet(_pos.x - 4105, _pos.y + 2050, _pos.z), VGet(0.0f, 0.0f, OBJECT_ROT * 2) * DEGREE);
			CreateHill_Ground(HILL::HILL_CEILING, VGet(_pos.x - 4105, _pos.y + 2050, _pos.z - 4105), VGet(0.0f, 0.0f, OBJECT_ROT * 2) * DEGREE);
			CreateHill_Ground(HILL::HILL_CEILING, VGet(_pos.x - 4105, _pos.y + 2050, _pos.z + 4105), VGet(0.0f, 0.0f, OBJECT_ROT * 2) * DEGREE);

			Map(MAP::HILL_FLORE, VGet(_pos.x - 4105, _pos.y, _pos.z), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
			Map(MAP::HILL_FLORE, VGet(_pos.x - 4105, _pos.y, _pos.z - 4105), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
			Map(MAP::HILL_FLORE, VGet(_pos.x - 4105, _pos.y, _pos.z + 4105), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

			CreateColision(COLLISION::E_GATE, VGet(_pos.x + 2195, _pos.y, _pos.z), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
			GateGround(GATE::E_GATE, VGet(_pos.x + 2195, _pos.y, _pos.z), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
			Create(StageObjectType::GATE_FLAME, VGet(_pos.x + 2195, _pos.y + NOM_SQUARE_GATE_POS_Y, _pos.z), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

			CreateHill_Ground(HILL::G_HILL, VGet(_pos.x + 2060, _pos.y + 1000, _pos.z), VGet(0.0f, OBJECT_ROT * 2, 0.0f) * DEGREE);

			CreateHill_Ground(HILL::N_HILL, VGet(_pos.x + 2060, _pos.y + 1000, _pos.z - 4105), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
			CreateHill_Ground(HILL::N_HILL, VGet(_pos.x + 2060, _pos.y + 1000, _pos.z + 4105), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

			CreateHill_Ground(HILL::N_HILL, VGet(_pos.x - 6160, _pos.y + 1000, _pos.z), VGet(0.0f, OBJECT_ROT * 2, 0.0f) * DEGREE);
			CreateHill_Ground(HILL::N_HILL, VGet(_pos.x - 6160, _pos.y + 1000, _pos.z - 4105), VGet(0.0f, OBJECT_ROT* 2, 0.0f) * DEGREE);
			CreateHill_Ground(HILL::N_HILL, VGet(_pos.x - 6160, _pos.y + 1000, _pos.z + 4105), VGet(0.0f, OBJECT_ROT * 2, 0.0f) * DEGREE);

			CreateHill_Ground(HILL::N_HILL, VGet(_pos.x - 4105, _pos.y + 1000, _pos.z - 6160), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);
			CreateHill_Ground(HILL::N_HILL, VGet(_pos.x, _pos.y + 1000, _pos.z - 6160), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);

			CreateHill_Ground(HILL::N_HILL, VGet(_pos.x - 4105, _pos.y + 1000, _pos.z + 6160), VGet(0.0f, OBJECT_ROT * 3, 0.0f) * DEGREE);
			CreateHill_Ground(HILL::N_HILL, VGet(_pos.x, _pos.y + 1000, _pos.z + 6160), VGet(0.0f, OBJECT_ROT * 3, 0.0f) * DEGREE);



			CreateColision(COLLISION::HILL_G_COL, VGet(_pos.x + 2075 - 50, _pos.y + 1000, _pos.z), VGet(0.0f, OBJECT_ROT * 2, 0.0f) * DEGREE);

			CreateColision(COLLISION::HILL_W_COL, VGet(_pos.x + 2075 - 50, _pos.y + 1000, _pos.z - 4105), VGet(0.0f, 0.0f, 0.0f) * DEGREE);
			CreateColision(COLLISION::HILL_W_COL, VGet(_pos.x + 2075 - 50, _pos.y + 1000, _pos.z + 4105), VGet(0.0f, 0.0f, 0.0f) * DEGREE);

			CreateColision(COLLISION::HILL_W_COL, VGet(_pos.x - 6160 + 50, _pos.y + 1000, _pos.z), VGet(0.0f, OBJECT_ROT * 2, 0.0f) * DEGREE);
			CreateColision(COLLISION::HILL_W_COL, VGet(_pos.x - 6160 + 50, _pos.y + 1000, _pos.z - 4105), VGet(0.0f, OBJECT_ROT * 2, 0.0f) * DEGREE);
			CreateColision(COLLISION::HILL_W_COL, VGet(_pos.x - 6160 + 50, _pos.y + 1000, _pos.z + 4105), VGet(0.0f, OBJECT_ROT * 2, 0.0f) * DEGREE);

			CreateColision(COLLISION::HILL_W_COL, VGet(_pos.x - 4105, _pos.y + 1000, _pos.z - 6160 + 50), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);
			CreateColision(COLLISION::HILL_W_COL, VGet(_pos.x, _pos.y + 1000, _pos.z - 6160 + 50), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);

			CreateColision(COLLISION::HILL_W_COL, VGet(_pos.x - 4105, _pos.y + 1000, _pos.z + 6160 - 50), VGet(0.0f, OBJECT_ROT * 3, 0.0f) * DEGREE);
			CreateColision(COLLISION::HILL_W_COL, VGet(_pos.x, _pos.y + 1000, _pos.z + 6160 - 50), VGet(0.0f, OBJECT_ROT * 3, 0.0f) * DEGREE);
		break;
	}

}

void StageManager::Test_Stage()
{

	CreateColision(COLLISION::N_COL, VGet(180, 405, -5520), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);
	GateGround(GATE::S_GATE, VGet( 180, 310, -5720), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);
	Create(StageObjectType::GATE_FLAME, VGet( 180, 405, -5720), VGet(0.0f, OBJECT_ROT, 0.0f) * DEGREE);

	Map(MAP::LOAD, VGet(GROUND_POS_X, GROUND_POS_Y, -1550), VGet(0.0f, OBJECT_ROT, 0.0f));

	Map(MAP::LOAD,VGet(GROUND_POS_X, GROUND_POS_Y, 2900),VGet(0.0f, OBJECT_ROT, 0.0f));

	Map(MAP::NOM_SQUARE, VGet(GROUND_POS_X, GROUND_POS_Y, 3400), VGet(0.0f, 0.0f, 0.0f));

	Map(MAP::LOAD, VGet(GROUND_POS_X, GROUND_POS_Y, 12055), VGet(0.0f, OBJECT_ROT * 3, 0.0f));

	Map(MAP::L_LOAD, VGet(187, GROUND_POS_Y, 13757), VGet(0.0f, OBJECT_ROT, 0.0f));

	Map(MAP::WIGHT_LOAD, VGet(2188, GROUND_POS_Y, 14068), VGet(0.0f, OBJECT_ROT * 2, 0.0f));

	Map(MAP::G2_SQUARE, VGet(6750, GROUND_POS_Y, 14060), VGet(0.0f, 0.0f, 0.0f));

	Map(MAP::WIGHT_LOAD, VGet(6300, GROUND_POS_Y, 22300), VGet(0.0f, OBJECT_ROT * 2, 0.0f));

	Map(MAP::SLOAP, VGet(4970, GROUND_POS_Y, 22300), VGet(0.0f, OBJECT_ROT * 2, 0.0f));

	Map(MAP::WIGHT_LOAD, VGet(1851, 777, 22300), VGet(0.0f, 0.0f, 0.0f));

	Map(MAP::FINAL_SQUARE, VGet( -950, 777, 22300), VGet(0.0f, 0.0f, 0.0f));
}
