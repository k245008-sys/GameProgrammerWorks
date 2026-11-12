#include "Combo.h"
#include"UiValue.h"
#include"assert.h"
#include"ScoreManager.h"

Combo::Combo()
{
	combo_Num = 0;
	combo_num = 0;
	shakeY = 0;
	addDigPosX = 0;
	combo = nullptr;
}

Combo::Combo(const VECTOR2I& Pos, std::vector<int> image)
{
	hImages = image;
	pos = Pos;
	combo_Num = 0;
	combo_num = 0;
	shakeY = 0;
	addDigPosX = 0;
	combo = nullptr;
}

Combo::~Combo()
{
}

void Combo::Update()
{
	combo = SceneManager::CommonScene()->FindGameObject<ScoreManager>();

		//コンボの値をCombo_numにコピー
	combo_num = combo->GetCurrentCombo();
		shakeY = combo->GetyShake();

	//コンボの桁数を設定
	if (combo_num <= 9) {
		combo_Num = 1;
		addDigPosX = 0;
	}

	if (combo_num > 9 && combo_num < 99) {
		addDigPosX = ONE_COMBO_FOTE_SIZEX / 2.0f;
		combo_Num = 2;
	}

	if (combo_num > 99) {
		addDigPosX = ONE_COMBO_FOTE_SIZEX;
		combo_Num = 3;
	}
}

void Combo::Draw()
{
	int texture = 0;
	int max = sizeof(COMBO_STAGING_NUM) / sizeof(COMBO_STAGING_NUM[0]);
	for (int c = 0; c < max; c++)
	{
		if (combo_num >= COMBO_STAGING_NUM[c])
		{
			texture = c;
			if (texture > (int)hImages.size() - 1)
				texture = (int)hImages.size() - 1;
		}
	}
	if (combo_num > 0)
	{
		int dig = 0;
			int copy = combo_num;
		for (int i = 0; i < combo_Num; i++)
		{
			DrawRectGraph((int)(pos.x - (ONE_COMBO_FOTE_SIZEX * dig) + COMBO_POS_SHIFTX + addDigPosX), (int)(pos.y + COMBO_POS_SHIFTY - shakeY), copy % 10 * ONE_COMBO_FOTE_SIZEX, 0,ONE_COMBO_FOTE_SIZEX,COMBO_FOTE_SIZEY, hImages[texture], true, false);

			copy /= 10;
			dig++;
		}
	}
}


