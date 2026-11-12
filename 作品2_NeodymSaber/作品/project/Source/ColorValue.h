#pragma once
#include "../Library/myDxLib.h"

/*
	RGBÇÃíËêîílÇ‹Ç∆Çﬂ
	àªïî
*/

namespace
{
	struct Color
	{
		unsigned char r;
		unsigned char g;
		unsigned char b;
	};

	const unsigned int WHITE = GetColor(255, 255, 255);
	const unsigned int GRAY = GetColor(128, 128, 128);
	const unsigned int BLACK = GetColor(0, 0, 0);
	const unsigned int RED = GetColor(255, 0, 0);
	const unsigned int LIGHT_RED = GetColor(255, 128, 128);
	const unsigned int ORANGE = GetColor(255, 200, 0);
	const unsigned int GREEN = GetColor(0, 255, 0);
	const unsigned int BLUE = GetColor(0, 0, 255);
	const unsigned int PURPLE = GetColor(255, 0, 255);
	const unsigned int LIGHT_BLUE = GetColor(0, 255, 255);
	const unsigned int YELLOW = GetColor(255, 255, 0);

	const Color WHITE_C = { 255, 255, 255 };
	const Color GRAY_C = { 128,128,128 };
	const Color BLACK_C = { 0, 0, 0 };
	const Color RED_C = { 255, 0, 0 };
	const Color ORANGE_C = { 255, 200, 0 };
	const Color GREEN_C = { 0, 255, 0 };
	const Color BLUE_C = { 0, 0, 255 };
	const Color PURPLE_C = { 255, 0, 255 };
	const Color LIGHT_BLUE_C = { 0, 255, 255 };
	const Color YELLOW_C = { 255, 255, 0 };

	const COLOR_F NONE_F = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
	const COLOR_F WHITE_F = GetColorF(1.0f, 1.0f, 1.0f, 1.0f);
	const COLOR_F GRAY_F = GetColorF(0.5f, 0.5f, 0.5f, 1.0f);
	const COLOR_F BLACK_F = GetColorF(0.0f, 0.0f, 0.0f, 1.0f);
	const COLOR_F RED_F = GetColorF(1.0f, 0.0f, 0.0f, 1.0f);
	const COLOR_F LIGHT_RED_F = GetColorF(1.0f, 0.5f, 0.5f, 1.0f);
	const COLOR_F ORANGE_F = GetColorF(1.0f, 0.6f, 0.0f, 1.0f);
	const COLOR_F GREEN_F = GetColorF(0.0f, 1.0f, 0.0f, 1.0f);
	const COLOR_F BLUE_F = GetColorF(0.0f, 0.0f, 1.0f, 1.0f);
	const COLOR_F PURPLE_F = GetColorF(1.0f, 0.0f, 1.0f, 1.0f);
	const COLOR_F LIGHT_PURPLE_F = GetColorF(1.0f, 0.35f, 1.0f, 1.0f);
	const COLOR_F LIGHT_BLUE_F = GetColorF(0.0f, 1.0f, 1.0f, 1.0f);
	const COLOR_F YELLOW_F = GetColorF(1.0f, 1.0f, 0.0f, 1.0f);

	inline bool operator ==(const COLOR_F& c1, const COLOR_F& c2) { return (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a && c2.a); }
	inline COLOR_F operator +(const COLOR_F& c1, const COLOR_F& c2) { return GetColorF(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b, c1.a + c2.a); }
	inline COLOR_F operator -(const COLOR_F& c1, const COLOR_F& c2) { return GetColorF(c1.r - c2.r, c1.g - c2.g, c1.b - c2.b, c1.a - c2.a); }
	inline COLOR_F operator *(const COLOR_F& c1, const float& c2) { return GetColorF(c1.r * c2, c1.g * c2, c1.b * c2, c1.a * c2); }
}