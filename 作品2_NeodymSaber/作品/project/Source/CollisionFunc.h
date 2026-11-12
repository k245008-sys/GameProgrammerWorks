#pragma once
#include "StageManager.h"

class CollisionFunc
{
public:
	bool MinDistStageResult(MV1_COLL_RESULT_POLY& _nearResult, const VECTOR& _startPos, const VECTOR& _endPos, const bool& _isAll = true, StageManager* _stageManager = nullptr)
	{
		if (_stageManager == nullptr)
			_stageManager = FindGameObject<StageManager>();
		bool evenOneTrue = false; // ˆê‚Â‚Å‚à“–‚½‚Á‚½‚©
		float minDist = 0;
		std::vector<Object3D*> objs;
		objs = _stageManager->GetCollsionObjects();
		for (auto& stage : objs)
		{
			// ƒ‚ƒfƒ‹‚Ì”»’èî•ñ‚ðXV
			MV1RefreshCollInfo(stage->GetModel());
			MV1_COLL_RESULT_POLY result = MV1CollCheck_Line(stage->GetModel(), -1, _startPos, _endPos);
			if (result.HitFlag == TRUE)
			{
				// Å’Z‹——£‚Ìî•ñ‚ðŽæ“¾
				float dist = VSize(result.HitPosition - _startPos);
				if (minDist > dist || !evenOneTrue)
				{
					evenOneTrue = true;
					minDist = dist;
					_nearResult = result;
					continue;
				}
			}
		}
		return evenOneTrue;
	}
};