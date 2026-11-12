#include "UiManager.h"
#include<assert.h>
#include"UiBase.h"
#include "UiValue.h"
#include "Combo.h"
#include"Blue_Ui.h"
#include"Red_Ui.h"
#include"SwordPin.h"
#include"GageBase.h"
#include"Combogage.h"
#include"HpGage.h"
#include"avoid.h"
#include"Red_Sword_Gege.h"
#include"Blue_Sword_Gage.h"

//GetGraphSize( GrHandle , &SizeX , &SizeY ) ;

UiManager::UiManager()
{
	flameImage[SWORD_PIN] = LoadGraph("data/texture/hukidasi_ver.3-1.png");
	assert(flameImage[SWORD_PIN] >= 0);

	gageImage[SWORD_PIN] = LoadGraph("data/texture/hukidasi_meta-3.png");
	assert(gageImage[SWORD_PIN] >= 0);

	gage[SWORD_PIN] = new SwordPin(gaegpos[SWORD_PIN], gageImage[SWORD_PIN], flameImage[SWORD_PIN]);

	gageImage[COMBO_GAGE] = LoadGraph("data/texture/combo_gage_re-1.png");
	assert(gageImage[COMBO_GAGE] >= 0);

	flameImage[COMBO_GAGE] = LoadGraph("data/texture/combo_fream_ver3-1.png");
	assert(flameImage[COMBO_GAGE] >= 0);

	hImage[COMBO] = LoadGraph("data/texture/num03.png");
	assert(hImage[COMBO] >= 0);

	pos[COMBO_GAGE] = UI_COMBO_POS;

	comboImages.emplace_back(hImage[COMBO]);
	comboImages.emplace_back(LoadGraph("data/texture/num04.png"));
	comboImages.emplace_back(LoadGraph("data/texture/num05.png"));
	ui[COMBO] = new Combo(pos[COMBO_GAGE], comboImages);

	gage[COMBO_GAGE] = new Combogage(pos[COMBO_GAGE], gageImage[COMBO_GAGE],flameImage[COMBO_GAGE]);

	flameImage[HP_GAGE] = LoadGraph("data/texture/HP_fream_ver3-1.png");
	assert(flameImage[HP_GAGE] >= 0);

	gageImage[HP_GAGE] = LoadGraph("data/texture/HP_gage_ver3-2.png");
	assert(gageImage[HP_GAGE] >= 0);

	gaegpos[HP_GAGE] = UI_HPGAGE_POS;

	gage[HP_GAGE] = new HpGage(gaegpos[HP_GAGE], gageImage[HP_GAGE], flameImage[HP_GAGE]);

	flameImage[AVOID] = LoadGraph("data/texture/kaihi_fream-1.png");
	assert(flameImage[AVOID] >= 0);

	gageImage[AVOID] = LoadGraph("data/texture/kaihi_icon-1.png");
	assert(gageImage[AVOID] >= 0);

	gaegpos[AVOID] = UI_AVOID_POS;

	gage[AVOID] = new avoid(gaegpos[AVOID], gageImage[AVOID], flameImage[AVOID]);

	flameImage[BLUE_UI] = LoadGraph("data/texture/blue_LBY-1.png");
	assert(flameImage[BLUE_UI] >= 0);

	gageImage[BLUE_UI] = LoadGraph("data/texture/blue_ui-1.png");
	assert(gageImage[BLUE_UI] >= 0);

	gaegpos[BLUE_UI] = UI_BLUEGAGE_POS;

	gage[BLUE_UI] = new Blue_Ui(gaegpos[BLUE_UI], gageImage[BLUE_UI], flameImage[BLUE_UI]);

	flameImage[RED_UI] = LoadGraph("data/texture/red_RB-1.png");
	assert(flameImage[RED_UI] >= 0);

	gageImage[RED_UI] = LoadGraph("data/texture/red_ui-1.png");
	assert(gageImage[RED_UI] >= 0);

	gaegpos[RED_UI] = UI_REDGAGE_POS;

	gage[RED_UI] = new Red_Ui(gaegpos[RED_UI], gageImage[RED_UI], flameImage[RED_UI]);

	flameImage[RED_GAGE] = LoadGraph("data/texture/red_gage_Ver4-1.png");
	assert(flameImage[RED_GAGE] >= 0);

	gageImage[RED_GAGE] = LoadGraph("data/texture/red_meta_ver3-1.png");
	assert(gageImage[RED_GAGE] >= 0);

	gaegpos[RED_GAGE] = UI_REDGAGE_POS;

	gage[RED_GAGE] = new Red_Sword_Gege(gaegpos[RED_GAGE], gageImage[RED_GAGE], flameImage[RED_GAGE]);

	flameImage[BLUE_GAGE] = LoadGraph("data/texture/blue_gage_Ver4-1.png");
	assert(flameImage[BLUE_GAGE] >= 0);

	gageImage[BLUE_GAGE] = LoadGraph("data/texture/blue_meta_ver3-1.png");
	assert(gageImage[BLUE_GAGE] >= 0);

	gaegpos[BLUE_GAGE] = UI_BLUEGAGE_POS;

	gage[BLUE_GAGE] = new Blue_Sword_Gage(gaegpos[BLUE_GAGE], gageImage[BLUE_GAGE], flameImage[BLUE_GAGE]);

	enable = true;
}

UiManager::~UiManager()
{
	for (int i = 0; i < UI_MAX; i++)
	{
		DeleteGraph(hImage[i]);
	}

	for (int i = 0; i < GAGE_MAX; i++)
	{
		DeleteGraph(flameImage[i]);
	}

	for (int t = 0; t < (int)comboImages.size(); t++)
	{
		if (comboImages[t] > 0)
			DeleteGraph(comboImages[t]);
	}
}

void UiManager::Update()
{
	if (!enable)
		return;

	ui[COMBO]->Update();

	for (int i = 0; i < GAGE_MAX; i++)
	{
		gage[i]->Update();
	}
}

void UiManager::Draw()
{
	if (!enable)
		return;

	ui[COMBO]->Draw();

	for (int i = 0; i < GAGE_MAX; i++)
	{
		gage[i]->Draw();
	}
}