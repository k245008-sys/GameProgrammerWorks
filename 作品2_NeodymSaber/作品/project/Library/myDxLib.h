#pragma once
#include <DxLib.h>
#include <math.h>

namespace DxLib
{
	// “x”‚ÉŠ|‚¯‚Äƒ‰ƒWƒAƒ“‚É‚Å‚«‚é
	const float DEGREE = DX_PI_F / 180.0f;
	// ‰Šú‰»È—ª
	const VECTOR VZero = VGet(0, 0, 0);

	// ƒxƒNƒgƒ‹‚Ì‰ÁŽZ
	inline const VECTOR operator +(const VECTOR& v1, const VECTOR& v2) { return VAdd(v1, v2); }
	inline VECTOR& operator +=(VECTOR& v1, const VECTOR& v2) { return v1 = VAdd(v1, v2); }
	// ƒxƒNƒgƒ‹‚ÌŒ¸ŽZ
	inline const VECTOR operator -(const VECTOR& v1, const VECTOR& v2) { return VSub(v1, v2); }
	inline VECTOR& operator -=(VECTOR& v1, const VECTOR& v2) { return v1 = VSub(v1, v2); }
	// ƒxƒNƒgƒ‹‚ÌŠ|‚¯ŽZ
	inline const VECTOR operator *(const VECTOR& v1, const VECTOR& v2) { return VGet(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z); }
	inline VECTOR& operator *=(VECTOR& v1, const VECTOR& v2) { return v1 = VGet(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z); }
	// ƒxƒNƒgƒ‹‚ÌŠ„‚èŽZ
	inline const VECTOR operator /(const VECTOR& v1, const VECTOR& v2) { return VGet(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z); }
	inline VECTOR& operator /=(VECTOR& v1, const VECTOR& v2) { return v1 = VGet(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z); }
	// ƒxƒNƒgƒ‹‚ÌŠg‘å
	inline const VECTOR operator *(const VECTOR& v1, float scale) { return VScale(v1, scale); }
	inline VECTOR& operator *=(VECTOR& v1, float scale) { return v1 = VScale(v1, scale); }
	// ƒxƒNƒgƒ‹‚Ìk¬
	inline const VECTOR operator /(const VECTOR& v1, float scale) { return VScale(v1, 1 / scale); }
	inline VECTOR& operator /=(VECTOR& v1, float scale) { return v1 = VScale(v1, 1 / scale); }
	// ƒxƒNƒgƒ‹‚ÌðŒ‰‰ŽZ
	inline bool operator ==(const VECTOR& v1, const VECTOR& v2) { return (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z); }
	inline bool operator !=(const VECTOR& v1, const VECTOR& v2) { return (v1.x != v2.x || v1.y != v2.y || v1.z != v2.z); }
	inline bool operator >=(const VECTOR& v1, const VECTOR& v2) { return (v1.x >= v2.x && v1.y >= v2.y && v1.z >= v2.z); }
	inline bool operator >(const VECTOR& v1, const VECTOR& v2) { return (v1.x > v2.x && v1.y >= v2.y && v1.z > v2.z); }
	inline bool operator <=(const VECTOR& v1, const VECTOR& v2) { return (v1.x <= v2.x && v1.y <= v2.y && v1.z <= v2.z); }
	inline bool operator <(const VECTOR& v1, const VECTOR& v2) { return (v1.x < v2.x && v1.y < v2.y && v1.z < v2.z); }

	// s—ñ‚Ì‘«‚µŽZ
	inline const MATRIX operator +(const MATRIX& m1, const MATRIX& m2) { return MAdd(m1, m2); }
	inline MATRIX& operator +=(MATRIX& m1, const MATRIX& m2) { return m1 = MAdd(m1, m2); }
	// s—ñ‚ÌŠ|‚¯ŽZ
	inline const MATRIX operator *(const MATRIX& m1, const MATRIX& m2) { return MMult(m1, m2); }
	inline MATRIX& operator *=(MATRIX& m1, const MATRIX& m2) { return m1 = MMult(m1, m2); }

	// ƒxƒNƒgƒ‹‚És—ñ‚ðŠ|‚¯‚é
	inline const VECTOR operator *(const VECTOR& v, const MATRIX& m1) { return VTransform(v, m1); }
	inline VECTOR& operator *=(VECTOR& v, const MATRIX& m1) { return v = VTransform(v, m1); }

	// VECTORŒ^‚Ì‰ñ“]’l‚ðs—ñ‚É•ÏŠ·‚·‚é
	inline MATRIX MGetRotZXY(const VECTOR& _rot)
	{
		MATRIX mr = MGetRotZ(_rot.z);
		mr *= MGetRotX(_rot.x);
		mr *= MGetRotY(_rot.y);
		return mr;
	}
	// ‰ñ“]s—ñ‚ÌX‰ñ“]‚ðŽæ“¾
	inline float GetMatrixRotX(const MATRIX& _rot)
	{
		MATRIX mRot = MGetRotElem(_rot);
		float rotX = 0;
		GetMatrixZXYRotation(&mRot, &rotX, 0, 0);
		return rotX;
	}
	// ‰ñ“]s—ñ‚ÌY‰ñ“]‚ðŽæ“¾
	inline float GetMatrixRotY(const MATRIX& _rot)
	{
		MATRIX mRot = MGetRotElem(_rot);
		float rotY = 0;
		GetMatrixZXYRotation(&mRot, 0, &rotY, 0);
		return rotY;
	}
	// ‰ñ“]s—ñ‚ÌZ‰ñ“]‚ðŽæ“¾
	inline float GetMatrixRotZ(const MATRIX& _rot)
	{
		MATRIX mRot = MGetRotElem(_rot);
		float rotZ = 0;
		GetMatrixZXYRotation(&mRot, 0, 0, &rotZ);
		return rotZ;
	}
	// ‰ñ“]s—ñ‚ðVECTORŒ^‚ÅŽæ“¾
	inline VECTOR GetMatrixRot(const MATRIX& _rot)
	{
		VECTOR rot = VZero;
		rot.x = GetMatrixRotX(_rot);
		rot.y = GetMatrixRotY(_rot);
		rot.z = GetMatrixRotZ(_rot);
		return rot;
	}

	// ‚QŽŸŒ³ƒxƒNƒgƒ‹ƒNƒ‰ƒX
	struct VECTOR2
	{
		float x, y;
		VECTOR2() :x(0), y(0) {}
		VECTOR2(const float& _x, const float& _y) :x(_x), y(_y) {}
	};
	// ‰Šú‰»È—ª
	const VECTOR2 V2Zero = VECTOR2(0, 0);

	// ‚QŽŸŒ³ƒxƒNƒgƒ‹‚Ì‰ÁŽZ
	inline const VECTOR2 operator +(const VECTOR2& v1, const VECTOR2& v2) { return VECTOR2(v1.x + v2.x, v1.y + v2.y); }
	inline VECTOR2& operator +=(VECTOR2& v1, const VECTOR2& v2) { return v1 = VECTOR2(v1.x + v2.x, v1.y + v2.y); }
	// ‚QŽŸŒ³ƒxƒNƒgƒ‹‚ÌŒ¸ŽZ
	inline const VECTOR2 operator -(const VECTOR2& v1, const VECTOR2& v2) { return VECTOR2(v1.x - v2.x, v1.y - v2.y); }
	inline VECTOR2& operator -=(VECTOR2& v1, const VECTOR2& v2) { return v1 = VECTOR2(v1.x - v2.x, v1.y - v2.y); }
	// ‚QŽŸŒ³ƒxƒNƒgƒ‹‚ÌŠg‘å
	inline const VECTOR2 operator *(const VECTOR2& v, const float& scale) { return VECTOR2(v.x * scale, v.y * scale); }
	inline VECTOR2& operator *=(VECTOR2& v, const float& scale) { return v = VECTOR2(v.x * scale, v.y * scale); }
	// ‚QŽŸŒ³ƒxƒNƒgƒ‹‚Ìk¬
	inline const VECTOR2 operator /(const VECTOR2& v, const float& scale) { return VECTOR2(v.x / scale, v.y / scale); }
	inline VECTOR2& operator /=(VECTOR2& v, const float& scale) { return v = VECTOR2(v.x / scale, v.y / scale); }
	// ‚QŽŸŒ³ƒxƒNƒgƒ‹‚ÌðŒ‰‰ŽZ
	inline bool operator ==(const VECTOR2& v1, const VECTOR2& v2) { return (v1.x == v2.x && v1.y == v2.y); }
	inline bool operator !=(const VECTOR2& v1, const VECTOR2& v2) { return (v1.x != v2.x || v1.y != v2.y); }

	// ‚QŽŸŒ³ƒxƒNƒgƒ‹ƒNƒ‰ƒX(intŒ^)
	struct VECTOR2I
	{
		int x, y;
		VECTOR2I() :x(0), y(0) {}
		VECTOR2I(const int& _x, const int& _y) :x(_x), y(_y) {}
	};

	// ‚QŽŸŒ³ƒxƒNƒgƒ‹‚Ì‰ÁŽZ(int)
	inline const VECTOR2I  operator +(const VECTOR2I& v1, const VECTOR2I& v2) { return VECTOR2I(v1.x + v2.x, v1.y + v2.y); }
	inline VECTOR2I& operator +=(VECTOR2I& v1, const VECTOR2I& v2) { return v1 = VECTOR2I(v1.x + v2.x, v1.y + v2.y); }
	// ‚QŽŸŒ³ƒxƒNƒgƒ‹‚ÌŒ¸ŽZ(int)
	inline const VECTOR2I  operator -(const VECTOR2I& v1, const VECTOR2I& v2) { return VECTOR2I(v1.x - v2.x, v1.y - v2.y); }
	inline VECTOR2I& operator -=(VECTOR2I& v1, const VECTOR2I& v2) { return v1 = VECTOR2I(v1.x - v2.x, v1.y - v2.y); }
	// ‚QŽŸŒ³ƒxƒNƒgƒ‹‚ÌŠg‘å(int)
	inline const VECTOR2I  operator *(const VECTOR2I& v, const float& scale) { return VECTOR2I((int)(v.x * scale), (int)(v.y * scale)); }
	inline VECTOR2I& operator *=(VECTOR2I& v, const float& scale) { return v = VECTOR2I((int)(v.x * scale), (int)(v.y * scale)); }
	// ‚QŽŸŒ³ƒxƒNƒgƒ‹‚Ìk¬(int)
	inline const VECTOR2I  operator /(const VECTOR2I& v, const float& scale) { return VECTOR2I((int)(v.x / scale), (int)(v.y / scale)); }
	inline VECTOR2I& operator /=(VECTOR2I& v, const float& scale) { return v = VECTOR2I((int)(v.x / scale), (int)(v.y / scale)); }
	// ‚QŽŸŒ³ƒxƒNƒgƒ‹‚ÌðŒ‰‰ŽZ(int)
	inline bool operator ==(const VECTOR2I& v1, const VECTOR2I& v2) { return (v1.x == v2.x && v1.y == v2.y); }
	inline bool operator !=(const VECTOR2I& v1, const VECTOR2I& v2) { return (v1.x != v2.x || v1.y != v2.y); }
}