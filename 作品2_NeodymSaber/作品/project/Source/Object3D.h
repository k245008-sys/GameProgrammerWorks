#pragma once
#include "../Library/gameObject.h"

/*
	モデルを持ったオブジェクトの基底クラス
	綾部
*/

namespace
{
	// 座標・回転・拡縮をまとめた値
	struct Transform
	{
		VECTOR position;
		VECTOR rotation;
		VECTOR scale;
		Transform()
		{
			position = VZero;
			rotation = VZero;
			scale = VGet(1, 1, 1);
		}
	};
}

class Object3D : public GameObject
{
public:
	Object3D();
	virtual ~Object3D();
	virtual void Update()override;
	virtual void Draw()override;

	// フィールド(メンバ変数)のクラスポインタにFindする処理をまとめる
	// PlaySceneクラスがUpdate前に全て呼ぶ
	virtual void AssignFindObjToField()override {}

	int GetModel() { return hModel; }
	VECTOR GetPos() { return transform.position; }
	VECTOR GetRot() { return transform.rotation; }
	VECTOR GetScale() { return transform.scale; }
	MATRIX GetDrawMatrix();

	void SetPos(const VECTOR& _pos) { transform.position = _pos; }
	void SetRot(const VECTOR& _rot) { transform.rotation = _rot; }
	void SetRotX(const float& _rotX) { transform.rotation.x = _rotX; }
	void SetRotY(const float& _rotY) { transform.rotation.y = _rotY; }
	void SetRotZ(const float& _rotZ) { transform.rotation.z = _rotZ; }
	void SetScale(const VECTOR& _scale) { transform.scale = _scale; }
	void SetScale(const float& _scale) { transform.scale = VGet(_scale, _scale, _scale); }

	void MoveRotY(const float& _speed, const float& _rotY);

	// モデルのフレーム(ボーン)関係
	MATRIX MGetFrameLocal(const char* _frame);
	MATRIX MGetFrameWorld(const char* _frame);
	MATRIX MGetFrameLocalRot(const char* _frame);
	VECTOR GetFrameWorldPos(const char* _frame);
	VECTOR GetFrameWorldRot(const char* _frame);
	VECTOR GetFrameLocalPos(const char* _frame);
	VECTOR GetFrameLocalRot(const char* _frame);
	void SetFrameLocalPos(const char* _frame, const VECTOR& _pos);
	void SetFrameLocalPosX(const char* _frame, const float& _posX);
	void SetFrameLocalPosY(const char* _frame, const float& _posY);
	void SetFrameLocalPosZ(const char* _frame, const float& _posZ);
	void SetFrameLocalRot(const char* _frame, const VECTOR& _rot);
	void SetFrameLocalRotX(const char* _frame, const float& _rotX);
	void SetFrameLocalRotY(const char* _frame, const float& _rotY);
	void SetFrameLocalRotZ(const char* _frame, const float& _rotZ);
	void SetDefaultLocalRootPos() { SetFrameLocalPos(rootFrameName.c_str(), defRootPos); }

protected:
	int hModel; // モデルハンドル
	Transform transform; // 座標・回転・拡縮データ
	std::string rootFrameName; // ルート(足元)ボーンの名前
	VECTOR defRootPos; // ルート座標の初期値
};