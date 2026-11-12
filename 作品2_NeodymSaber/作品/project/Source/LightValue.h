#pragma once

#include "ColorValue.h"

namespace
{
	const VECTOR MAIN_DIR_LIGHT_DIRECTION = { -5.0f, 5.0f, 8.5f };
	const COLOR_F MAIN_DIR_LIGHT_DIF_COLOR = { 1.0f, 1.0f, 1.0f, 1.0f };
	const COLOR_F MAIN_DIR_LIGHT_SPC_COLOR = { 0.0f, 0.0f, 0.0f, 0.0f };
	const COLOR_F MAIN_DIR_LIGHT_AMB_COLOR = { 1.0f, 1.0f, 1.0f, 1.0f };

	const VECTOR SUB_DIR_LIGHT_DIRECTION = { 2.8f, -5.0f, -3.5f };
	const COLOR_F SUB_DIR_LIGHT_DIF_COLOR = { 1.0f, 1.0f, 1.0f, 1.0f };
	const COLOR_F SUB_DIR_LIGHT_SPC_COLOR = { 0.0f, 0.0f, 0.0f, 0.0f };
	const COLOR_F SUB_DIR_LIGHT_AMB_COLOR = { 1.0f, 1.0f, 1.0f, 1.0f };

	const VECTOR POINT_LIGHT_ADUST_POS = { 0.0f, 250.0f, 0.0f };
	const float POINT_LIGHT_RANGE = 0.0f;
	const float POINT_LIGHT_ATTEN_ZERO = 0.00001f;
	const float POINT_LIGHT_ATTEN_ONE = 0.0f;
	const float POINT_LIGHT_ATTEN_TWO = -0.000009f;
}