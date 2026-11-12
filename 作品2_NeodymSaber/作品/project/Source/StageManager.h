#pragma once
#include "../Library/gameObject.h"
#include <string>
#include <vector>
#include "Object3D.h"

/*
	ステージの作成に必要なクラスの管理
	石井
*/
namespace 
{

	const std::string M_MODEL() { return "data/model/"; }
	const std::string M_STAGE_OBGECT() { return "data/model/StageObjects/"; }
	const std::string M_MV1() { return ".mv1"; }

	enum class StageObjectType
	{
		SMALL_SQUARE,
		HILL,
		BIG_SQUARE,
		SCAFFOLD,
		GATE,
		GATE_FLAME,
	};


	enum class GROUND
	{
		N_FLEAM,//通路の地面
		SLOAP,//坂
		L_FLEAM,//曲がり角の地面
		T_FLEAM,//T字路の地面
	};

	enum class COLLISION
	{
		N_COL,//通路の当たり判定ブロック
		S_COL,//坂の当たり判定ブロック
		L_COL,//曲がり角の当たり判定ブロック
		H_COL,
		HILL_COL,//広場のの当たり判定ブロック
		HILL_W_COL,
		HILL_G_COL,
		E_GATE,
		P_GATE,
		W_GATE,
		H_GATE,

	};

	enum class WALL
	{
		N_WALL,//通路の壁
		S_WALL,//坂の壁
		L_WALL,//曲がり角の壁
		T_WALL,//T字路の壁

	};

	enum class HILL
	{
		G_HILL,//ゲート付き広場の壁
		N_HILL,//広場の地面
		HILL_E,
		HILL_N,
		F_HILL,//広場の壁
		HILL_CEILING,
	};

	enum class GATE
	{
		E_GATE,//エネミーのゲート
		P_GATE,//プレイヤーのゲート
		S_GATE,//動かないゲート
		F_GATE,
		W_GATE,
		H_GATE,
	};

	enum class CEILING
	{
		N_CEILING,//通路の天井
		C_CEILING,//曲がり角の天井
		S_CEILING,//坂の天井
	};

	enum class MAP
	{
		LOAD,//通常通路
		L_LOAD,//曲がり角
		WIGHT_LOAD,//横通路
		SLOAP,//斜め通路
		ATHLETICS,//アスレチック通路
		NOM_SQUARE,//丸型フロア
		G2_SQUARE,//2のゲートのフロア
		FINAL_SQUARE,//最後のフロア
		HILL_FLORE
	};

	const VECTOR STAGE_OBJECT_GATE_SCALE = VGet(1.0f, 1.0f, 1.4f);

	const VECTOR STAGE_OBJECT_GATECOLL_SCALE = VGet(3.5f, 0.8f, 2.0f);

	const VECTOR STAGE_OBJECT_GROUND_SCALE = VGet(1.0f, 1.0f, 1.0f);

	const VECTOR STAGE_OBJECT_GROUNDCOL_SCALE = VGet(1.0f, 3.0f, 1.0f);

	const VECTOR STAGE_OBJECT_WALL_SCALE = VGet(0.5f, 1.0f, 0.5f);

	const VECTOR STAGE_COLLSION_HIGE_SCALE = VGet(1.0f, 0.6f, 1.5f);
}

class StageManager :public GameObject
{
public:
	StageManager();
	~StageManager();
	void Update()override;
	void Draw()override;

	void Restate();

	std::vector<Object3D*> GetStageObjects() { return stageObjects; }

	std::vector<Object3D*> GetCollsionObjects() { return collsionObjects; }

	std::vector<Object3D*> GetAllObjects()
	{
		std::vector<Object3D*> all = stageObjects;
		for (auto& c : collsionObjects)
		{
			all.emplace_back(c);
		}
		return all;
	}


	void Create(const StageObjectType& _type, const VECTOR& _pos, const VECTOR& _scale);//ステージのオブジェクト生成関数

	void CreateGround(const GROUND& _type,const VECTOR& _pos, const VECTOR& _rot);////ステージの地面生成関数

	void GateGround(const GATE& _type, const VECTOR& _pos, const VECTOR& _rot);////ステージのゲート生成関数

	void CreateCeiling(const CEILING& _type, const VECTOR& _pos, const VECTOR& _rot);////天井の生成関数

	void CreateHill_Ground(const HILL& _type, const VECTOR& _pos, const VECTOR& _rot);////フロアの生成関数

	void CreateWall(const WALL& _type,const VECTOR& _pos, const VECTOR& _rot);////壁の生成関数

	void CreateColision(const COLLISION& _type, const VECTOR& _pos, const VECTOR& _rot);////壁の生成関数

	void Map(const MAP& _type, const VECTOR& _pos, const VECTOR& _rot);//MAP作成

	void Test_Stage();

private:
	std::vector<Object3D*> stageObjects;
	std::vector<Object3D*> collsionObjects;

	bool coll;
	bool push;

	int objectModle[4];
	int groundModle[4];
	int gateModle[3];
	int ceilingModle[3];
	int hillModle[6];
	int wallModle[1];
	int s_wallModle;
	int collisionModle[6];
};
