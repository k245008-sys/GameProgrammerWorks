#pragma once
#include"effectBase.h"
#include <EffekseerForDXLib.h>
class Hit :public EffectBase
{
public:
	Hit();
	Hit(VECTOR pos, VECTOR rot, int eData);
	~Hit();
	void Update()override;
	void Draw()override;
	void UpdateEffect();
	void SetUpdate();
	int GetEffectData();
	bool Finish()override;
private:
	int hEffectData;		//エフェクトのハンドラ
	int hPlayingEffect;		//エフェクトの再生をさせるハンドラ
	int appearanceTime;		//再生時間
	VECTOR position;		//座標
	VECTOR rotation;
	bool finishHandle;
};

