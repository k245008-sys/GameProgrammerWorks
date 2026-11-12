#include "Object3D.h"
#include <stdio.h>
#include <vector>
#include "ColorValue.h"
#include"MoveNum.h"
#include "../Library/Time.h"
#include "../Library/myDxLib.h"

Object3D::Object3D()
{
	hModel = -1;
	defRootPos = VZero;
}

Object3D::~Object3D()
{
	if (hModel > 0)
	{
		MV1DeleteModel(hModel);
		hModel = -1;
	}
}

void Object3D::Update()
{
}

void Object3D::Draw()
{
	MATRIX mat = GetDrawMatrix();
	MV1SetMatrix(hModel, mat);
	MV1DrawModel(hModel);
}

MATRIX Object3D::GetDrawMatrix()
{
	MATRIX mat = MGetScale(transform.scale);
	mat *= MGetRotZ(transform.rotation.z);
	mat *= MGetRotX(transform.rotation.x);
	mat *= MGetRotY(transform.rotation.y);
	mat *= MGetTranslate(transform.position);
	return mat;
}

void Object3D::MoveRotY(const float& _speed, const float& _rotY)
{
	MoveNum moveNum;
	moveNum.MoveRot(transform.rotation.y, _speed, _rotY);
}

MATRIX Object3D::MGetFrameLocal(const char* _frame)
{
	int frame = MV1SearchFrame(hModel, _frame);
	return MV1GetFrameLocalMatrix(hModel, frame);
}

MATRIX Object3D::MGetFrameWorld(const char* _frame)
{
	int frame = MV1SearchFrame(hModel, _frame);
	return MV1GetFrameLocalWorldMatrix(hModel, frame);
}

MATRIX Object3D::MGetFrameLocalRot(const char* _frame)
{
	MATRIX mat = MGetFrameLocal(_frame);
	return MGetRotElem(mat);
}

VECTOR Object3D::GetFrameWorldPos(const char* _frame)
{
	int frame = MV1SearchFrame(hModel, _frame);
	return MV1GetFramePosition(hModel, frame);
}

VECTOR Object3D::GetFrameWorldRot(const char* _frame)
{
	MATRIX mat = MGetFrameWorld(_frame);
	mat = MGetRotElem(mat);
	return GetMatrixRot(mat);
}

VECTOR Object3D::GetFrameLocalPos(const char* _frame)
{
	MATRIX mat = MGetFrameLocal(_frame);
	return MGetTranslateElem(mat);
}

VECTOR Object3D::GetFrameLocalRot(const char* _frame)
{
	MATRIX mat = MGetFrameLocalRot(_frame);
	return GetMatrixRot(mat);
}

void Object3D::SetFrameLocalPos(const char* _frame, const VECTOR& _pos)
{
	int frame = MV1SearchFrame(hModel, _frame);
	MATRIX mat = MGetFrameLocalRot(_frame);
	mat *= MGetTranslate(_pos);
	MV1SetFrameUserLocalMatrix(hModel, frame, mat);
}

void Object3D::SetFrameLocalPosX(const char* _frame, const float& _posX)
{
	int frame = MV1SearchFrame(hModel, _frame);
	MATRIX mat = MGetFrameLocalRot(_frame);
	VECTOR pos = GetFrameLocalPos(_frame);
	pos.x = _posX;
	mat *= MGetTranslate(pos);
	MV1SetFrameUserLocalMatrix(hModel, frame, mat);
}

void Object3D::SetFrameLocalPosY(const char* _frame, const float& _posY)
{
	int frame = MV1SearchFrame(hModel, _frame);
	MATRIX mat = MGetFrameLocalRot(_frame);
	VECTOR pos = GetFrameLocalPos(_frame);
	pos.y = _posY;
	mat *= MGetTranslate(pos);
	MV1SetFrameUserLocalMatrix(hModel, frame, mat);
}

void Object3D::SetFrameLocalPosZ(const char* _frame, const float& _posZ)
{
	int frame = MV1SearchFrame(hModel, _frame);
	MATRIX mat = MGetFrameLocalRot(_frame);
	VECTOR pos = GetFrameLocalPos(_frame);
	pos.z = _posZ;
	mat *= MGetTranslate(pos);
	MV1SetFrameUserLocalMatrix(hModel, frame, mat);
}

void Object3D::SetFrameLocalRot(const char* _frame, const VECTOR& _rot)
{
	int frame = MV1SearchFrame(hModel, _frame);
	MATRIX mat = MGetRotElem(MGetRotZXY(_rot));
	mat *= MGetTranslate(GetFrameLocalPos(_frame));
	MV1SetFrameUserLocalMatrix(hModel, frame, mat);
}

void Object3D::SetFrameLocalRotX(const char* _frame, const float& _rotX)
{
	int frame = MV1SearchFrame(hModel, _frame);
	MATRIX mat = MGetRotX(_rotX);
	mat *= MGetRotY(GetFrameLocalRot(_frame).y);
	mat *= MGetRotZ(GetFrameLocalRot(_frame).z);
	mat *= MGetTranslate(GetFrameLocalPos(_frame));
	MV1SetFrameUserLocalMatrix(hModel, frame, mat);
}

void Object3D::SetFrameLocalRotY(const char* _frame, const float& _rotY)
{
	int frame = MV1SearchFrame(hModel, _frame);
	MATRIX mat = MGetRotZ(GetFrameLocalRot(_frame).z);
	mat *= MGetRotX(GetFrameLocalRot(_frame).x);
	mat *= MGetRotY(_rotY);
	mat *= MGetTranslate(GetFrameLocalPos(_frame));
	MV1SetFrameUserLocalMatrix(hModel, frame, mat);
}

void Object3D::SetFrameLocalRotZ(const char* _frame, const float& _rotZ)
{
	int frame = MV1SearchFrame(hModel, _frame);
	MATRIX mat = MGetRotZ(_rotZ);
	mat *= MGetRotX(GetFrameLocalRot(_frame).x);
	mat *= MGetRotY(GetFrameLocalRot(_frame).y);
	mat *= MGetTranslate(GetFrameLocalPos(_frame));
	MV1SetFrameUserLocalMatrix(hModel, frame, mat);
}