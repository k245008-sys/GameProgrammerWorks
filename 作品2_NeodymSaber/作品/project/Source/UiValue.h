#pragma once


namespace
{

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// UIの画面座標
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	const VECTOR2I UI_COMBO_POS = VECTOR2I(1610, 300);

	const VECTOR2I UI_SPGAGE_POS = VECTOR2I(150, 60);

	const VECTOR2I UI_HPGAGE_POS = VECTOR2I(30, 15);

	const VECTOR2I UI_AVOID_POS = VECTOR2I(930, 950);

	const VECTOR2I UI_REDGAGE_POS = VECTOR2I(1328, 975);

	const VECTOR2I UI_BLUEGAGE_POS = VECTOR2I(45, 975);

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// UIのサイズ
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	const int ONE_COMBO_FOTE_SIZEX = 64;//65
	const int COMBO_FOTE_SIZEY = 128;
	const int SWORD_PIN_FOTE_SIZE = 155;
	const int COMBO_GAGE_FOTE_SIZE = 307;
	const int SWORD_FOTE_SIZE = 155;

	const int SP_GAGE_FOTE_SIZEX = 373;
	const int SP_GAGE_FOTE_SIZEY = 71;

	const int SP_BOTTRN_FOTE_SIZEX = 446;
	const int SP_BOTTRN_FOTE_SIZEY = 71;

	const int SWORD_GAGE_FOTE_SIZEX = 547;
	const int SWORD_GAGE_FOTE_SIZEY = 73;


	const int HP_GAGE_FOTE_SIZEX = 138;
	const int HP_GAGE_FOTE_SIZEY = 49;

	const int HP_GAGE_ONE_FOTE_SIZEX = 127;
	const int HP_GAGE_ONE_FOTE_SIZEY = 72;

	const int HP_GAGE_FLAME_FOTE_SIZEX = 629;
	const int HP_GAGE_FLAME_FOTE_SIZEY = 71;

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// ランキング
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	const float RANKING_SPACE_X = 580.0f;

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// コンボ
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	// 画像描画位置修正
	const int COMBO_POS_SHIFTX = 90;
	const int COMBO_POS_SHIFTY = 55;
	const int COMBO_GAGE_POS_SHIFTX = 142;
	const int COMBO_GAGE_POS_SHIFTY = 147;

	const int SP_BOTTRN_FOTE_SHIFTX = 75;

	const int COMBO_STAGING_NUM[]
		= { 0, 10, 20 };

	const int TOTAL_COMBO_ENABLE_ADD_CURRENT_COMBO_NUM = 20;

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// 画面外赤剣ピン
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// 
	// 吹き出し画像の中心
	const float SWORD_PIN_CENTER_RETE = 77.5;
	// 表示する画面端の位置調整
	const VECTOR2I SWORD_PIN_ADJUST_CLAPM_SIZE = VECTOR2I(-150, -150);
	// 素材の角度調整
	const float SWORD_PIN_ADJUST_ANGLE = DEGREE * -45;
	
	// ALHPA値の最高値
	const int SWORD_PIN_ALHPA_MAX = 170;
	// ALHPA値の最低値
	const int SWORD_PIN_ALHPA_MIN = 60;

	// 画面外赤剣ピンの画像描画位置修正
	const int SWORD_PIN_POS_SHIFTX = 60;
	const int SWORD_PIN_POS_SHIFTY = 65;
}