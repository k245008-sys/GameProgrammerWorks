#pragma once
#include "CameraBase.h"
#include "CameraAdjustValue.h"
#include "StateManager.h"
#include <string>
#include "Object3D.h"

//カメラクラス

class InputManager;
class Player;
class MoveNum;
class StageManager;
class EnemyManager;

class Camera : public CameraBase
{
public:

	Camera();
	~Camera();
	void Update() override;
	void Draw() override;

	//リセット関数ーーーーーーーーーー
	
	//リスタート用関数
	void ResetCamera();
	//カメラの回転を遷移しPlayerを基準にリセット
	void ResetCameraRot();		
	
	//挙動系の関数ーーーーーーーーー
	
	//視野の最大値を設定
	void LimitAngle();
	//カメラの振動
	void ShakeCamera();
	//カメラを回転させる関数
	void RotationCamera();
	//位置補完する値まで遷移する関数
	void TransitionDelay();
	//Playerから一定の位置にカメラを固定する関数
	void FollowToPlayer(VECTOR _targetGoal, VECTOR _posGoal);
	//カメラの遷移の動き
	bool TransitionPos(VECTOR _goalPos, VECTOR& _transPos, float _TransSpeed);


	//Find系関数ーーーーーーーーーー
	
	//フィールド(メンバ変数)のクラスポインタにFindする処理をまとめる
	void AssignFindObjToField() override;


	//判定関数ーーーーーーーーーーー
	
	//ステージとのPlayerとCameraの線分の当たり判定
	bool CameraToPlayerLineStageColider();


	//ステート関数ーーーーーーーーー
	
	//一つ前のステートを記憶する関数
	void RecordToBeforeStateName(); 


	//加算用関数ーーーーーーーーーー

	//Position加算関数
	void AddPos(VECTOR _pos) { transform.position += _pos; }
	//RotationのY軸加算関数
	void AddRotY(float _RotSpeed) { transform.rotation.y += _RotSpeed; }


	//代入用関数ーーーーーーーーーー

	/// <summary>
	/// カメラの振動用の値をセットする関数
	/// </summary>
	/// <param name="_shakeRangeMax">振動する範囲</param>
	/// <param name="_shakeSpeed">振れの速度</param>
	/// <param name="_shakeTime">振動させる時間</param>
	void SetShakeCamera(VECTOR _shakeRangeMax, VECTOR _shakeSpeed, float _shakeTime);
	//positionのセッター
	void SetPos(VECTOR _pos) { transform.position = _pos; }
	//Playerを中心にカメラを設置する。
	void SetCenterToPlayer(VECTOR _targetGowal, VECTOR _posGoal, VECTOR _rotation);
	//targetのセッター
	void SetNormalTarget(VECTOR  _target) { normalTarget = _target; }
	//targetのセッター
	void SetAimTarget(VECTOR  _target) { aimTarget = _target; }
	//Rotationのセッター
	void SetRot(VECTOR _rotasion) { transform.rotation = _rotasion ; }
	//遷移する速度用のセッター
	void SetTransSpeed(float _TransSpeed) { transSpeed = _TransSpeed; }
	//判定するかしないかの切り替えセッター
	void SetIsCollision(bool _isCollision) { isCollision = _isCollision; }
	//Direcsionのセッター
	void SetDirection(const MATRIX& _direction) { direction = _direction; }
	/// <summary>
	/// カメラの角度のリセットをする際の値をセットする関数
	/// </summary>
	/// <param name="_speed">回転させる速さ</param>
	/// <param name="_rotY">どの角度まで回すか</param>
	/// <param name="_isReset">リセットを始めるかどうか</param>
	void SetRestRot(float _speed, float _rotY, bool _isReset);


	//参照用関数ーーーーーーーーーー

	//NormalTarget参照用関数
	VECTOR GetNormalTarget() const { return normalTarget; }
	//判定で当たった位置を参照する関数
	VECTOR GetCollHitPos() const { return collHitPos; }
	//AimTargetのゲッター
	VECTOR GetAimTarget();
	//位置の補完する値を参照する関数
	VECTOR GetDelayPos() const { return delayPos; }
	/// <summary>
	/// 遷移したい場所までのベクトルを作成する関数
	/// </summary>
	/// <param name="_startPos">遷移の開始位置</param>
	/// <param name="_goalPos">遷移の終了地点</param>
	/// <param name="_direction">向き</param>
	/// <returns></returns>
	VECTOR GetTransGoalPos(VECTOR _startPos, VECTOR _goalPos, MATRIX _direction);
	//Direcsion参照用関数
	MATRIX GetDirection() const { return direction; }
	//一つ前のステートを参照する関数
	std::string GetBeforeStateName() const { return beforeState; }
	//判定が当たったかどうか
	bool GetIsHit() const { return isHit; }

private:

	//ポインター
	
	//インプットマネージャー用ポインター
	InputManager* inputManager;	
	//プレイヤー用ポインター
	Player* player;				
	//ステージマネージャー用ポインター
	StageManager* stageManager;	

	//ステート

	//現在のステート保管用変数
	std::string nowState;
	//一つ前のステート保管用変数
	std::string beforeState;
	//ステートの判定
	void jugeState() override;


	//位置
	
	//位置の遷移先を保管する変数
	VECTOR posGoal;		
	//ステージとの判定で当たった場所を保管する変数
	VECTOR collHitPos;
	//位置を判定でどれだけずらすか
	VECTOR collAdjustPos;
	//遷移後の位置を保管する変数
	VECTOR transGoalPos;
	//位置を補完する値を保管する変数
	VECTOR delayPos;


	//注視点
	
	//通常時の注視点の値を補完する変数
	VECTOR normalTarget;
	//エイム時の注視点の値をする変数
	VECTOR aimTarget;
	//注視点の遷移したい位置を入れる変数
	VECTOR targetGoal;


	//向き
	
	//カメラの向き
	MATRIX direction;


	//速度
	
	//遷移する速度を入れる変数
	float transSpeed;


	//Bool系

	//判定で当たったかどうか
	bool isHit; 
	//判定するかどうか
	bool isCollision;
	//補完の遷移をするか
	bool isDelay;


	//ーーーーーーーーーー振動

	//ShakePosの反転処理
	void ShakePosSign();

	//ShakePosの範囲制限
	void ShakePosRimit();

	//振動用の座標
	VECTOR shakePos;			
	//振動の広さ。マイナスから０、０からプラスの長さを足した物
	VECTOR shakeLength;	
	//振動の範囲の最大値
	VECTOR shakeRangeMax;
	//振動の範囲の最小値
	VECTOR shakeRangeMin;
	//振動の速さ
	VECTOR shakeSpeed;
	//振動用のプラスマイナス切り替え用
	VECTOR shakeSign;
	//振動用のカウンター
	float shakeCounter;
	//振動する時間
	float shakeTime;
	//振動中かそうでないか。
	bool isShakeing;
	//ーーーーーーーーーー

	//プレイヤーの値を入れる変数
	VECTOR pRot;

	//ーーーーーーーーーー回転リセット

	//どこまで回転させるかの角度をいれる変数
	float resetRotasionY;
	//回転のスピード
	float resetSpeed;
	//リセットを始めるかどうか
	bool isRotReset;
};