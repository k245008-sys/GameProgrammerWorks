#pragma once
#include "../Library/gameObject.h"

#include <string>
#include "ColorValue.h"

/*
	デバッグ用クラス
	加藤
*/

class Player;
class Camera;
class InputManager;
class CameraStateBase;

enum ImageId
{
	POINT_FIXATION_MARK, //注視点用のマーク
	IMAGEMAX,
};

struct DebugNum //各値を収納する構造体
{
	VECTOR position;
	VECTOR rotation;
	float velocity;
	std::string state;
};

class Debug : public GameObject
{
public:

	Debug();
	~Debug();
	void Update() override;
	void Draw() override;

	void AssignFindObjToField() override;	//フィールド(メンバ変数)のクラスポインタにFindする処理をまとめる

private:

	Player* playerPtr; //Playerのポインター
	Camera* cameraPtr; //Cameraのポインター
	InputManager* inputManagerPtr; //InputManagerのポインター 
	CameraStateBase* cameraStateBasePtr;

	DebugNum player; //Playerの各値を入れる構造体の実態
	DebugNum camera; //Cameraの各値を入れる構造体の実態

	VECTOR cameraTarget;
	VECTOR cameraAimTarget;
	VECTOR cameraDelayPos;

	int hImage[IMAGEMAX];

	bool playerDbgOn; //Playerデバッグ機能起動用
	bool cameraDbgOn; //Cameraデバッグ機能起動用
	bool DeleteDbgDisp;	//表示のON、OFF切り替え用

};

