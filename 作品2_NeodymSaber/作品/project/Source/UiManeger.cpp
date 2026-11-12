#include "UiManeger.h"
#include"UiBase.h"
#include<assert.h>

UiManeger::UiManeger()
{
	hImage = LoadGraph("data/texture/Kari_Conbo-1.png");
	assert(hImage >= 0);
	pos = {0,0};

	ui->Init(pos, hImage);
}

UiManeger::~UiManeger()
{
	DeleteGraph(hImage);
}

void UiManeger::Update()
{

}

void UiManeger::Draw()
{

}
