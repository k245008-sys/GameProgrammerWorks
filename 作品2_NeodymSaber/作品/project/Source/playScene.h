#pragma once
#include "../Library/sceneBase.h"
#include "SoundManager.h"


/*
	ゲームプレイに必要なクラスの管理
	綾部
*/

class Player;
class EnemyManager;
class StageManager;
class ShotManager;
class CollisionManager;
class OffScreenEnemyGuidManager;
class SoundManager;
class UiManager;
class Camera;
class Light;
class Debug;
class GameOver;
class ResultScene;
class Emitter;
class RoundShadowManager;
class TitleScene;
class Fade;

enum PlayState
{
	TITLE,
	BEFORE,
	PLAY,
	CLEAR,
	GAMEOVER,
	RESULT,
};

class PlayScene : public SceneBase
{
public:
	PlayScene();
	~PlayScene();
	void Update() override;
	void Draw() override;

	void HitStop(const float& _time) { hitStopTime = _time; }
	bool GetIsGameOver() { return isGameOver; }
	int GetShadowTexture() { return shadowTexture; }
	void ChangeState(const PlayState& _state);
	void Restart();
	PlayState GetState() { return state; }

private:
	/// <summary>
	/// Update()内でデルタタイムによる処理分けをするため別作成
	/// </summary>
	void UpdateGame();
	// １秒経ったとき何フレーム処理したか計算する
	void CalcFPS();
	void SlowMotion();

	void StartUI();
	void StartUIDraw();

	PlayState state;

	Player* player;
	StageManager* stageManager;
	EnemyManager* enemyManager;
	ShotManager* shotManager;
	CollisionManager* collisionManager;
	OffScreenEnemyGuidManager* enemyGuidManager;
	SoundManager* sound;
	UiManager* uiManager;
	Camera* camera;
	Light* light;
	Debug* debug;
	GameOver* gameover;
	ResultScene* result;
	Emitter* emitter;
	RoundShadowManager* shadow;
	TitleScene* title;
	Fade* fade;

	// スローモーション
	float slowMotionTime;
	float slowMotionRate;
	// ヒットストップ
	float hitStopTime;

	// ラグ時間
	float lag;
	// 現実での１フレーム処理時間
	float realDeltaTime;

	// fps表示
	bool appearFps;
	float fps;
	int frameCount;
	float fpsTime;

	bool isGameOver;
	float overTime;

	int shadowTexture;

	int clearImage;

	float fadeRate;
	float time;

	float startTime;
	std::unordered_map<std::string, int> startImages;
	VECTOR2 uiPos;
	float uiSpeedX;
	float appearTime;
	float alphaRate;
};