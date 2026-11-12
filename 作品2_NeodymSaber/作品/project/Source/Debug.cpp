#include "Debug.h"
#include "Player.h"
#include "Camera.h"
#include "CameraStateBase.h"
#include "InputManager.h"
#include "config.h"
#include <assert.h>

Debug::Debug()
{
	cameraPtr = nullptr;
	playerPtr = nullptr;
	inputManagerPtr = nullptr;
	cameraStateBasePtr = nullptr;

	player.position = VGet(0.0f, 0.0f, 0.0f);
	player.rotation = VGet(0.0f, 0.0f, 0.0f);
	player.velocity = 0.0f;
	player.state = "NULL";

	camera.position = VGet(0.0f, 0.0f, 0.0f);
	camera.rotation = VGet(0.0f, 0.0f, 0.0f);
	camera.velocity = 0.0f;
	camera.state = "NULL";

	cameraTarget = VGet(0.0f, 0.0f, 0.0f);
	cameraAimTarget = VGet(0.0f, 0.0f, 0.0f);
	cameraDelayPos = VGet(0.0f, 0.0f, 0.0f);

	hImage[POINT_FIXATION_MARK] = LoadGraph("data/texture/TargetPoint.png");
	assert(hImage[POINT_FIXATION_MARK] >= 0);

	playerDbgOn = false;
	cameraDbgOn = false;
	DeleteDbgDisp = false;

}

Debug::~Debug()
{
	for (int i = 0; i < (int)(sizeof(hImage) / sizeof(hImage[0])); i++)
	{
		DeleteGraph(hImage[i]);
	}
}

void Debug::Update()
{
#ifdef _DEBUG

	player.position = playerPtr->GetPos();
	player.rotation = playerPtr->GetRot();
	player.state = playerPtr->GetCurrentStateName();

	camera.position = cameraPtr->GetPos();
	camera.rotation = cameraPtr->GetRot();
	cameraTarget = cameraPtr->GetNormalTarget();
	cameraAimTarget = cameraPtr->GetAimTarget();
	camera.state = cameraPtr->GetCurrentStateName();
	cameraDelayPos = cameraPtr->GetDelayPos();

	if (inputManagerPtr->IsKeyPushDown("C"))
	{
		if (cameraDbgOn == false)
		{
			cameraDbgOn = true;
		}
		else
		{
			cameraDbgOn = false;
		}	
	}
	
	if (inputManagerPtr->IsKeyPushDown("P"))
	{
		if (playerDbgOn == false)
		{
			playerDbgOn = true;
		}
		else
		{
			playerDbgOn = false;
		}
		
	}

#endif
}

void Debug::Draw()
{
	Color c = WHITE_C; 

	if (playerDbgOn == true)
	{
		if (DeleteDbgDisp == false)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
			DrawBox(0, 150, 380, 600, 0x454545, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			SetFontSize(20);
			//Playerの情報表示
			DrawFormatString(10, 200, GetColor(c.r, c.g, c.b), "pPos = %.1f, %.1f, %.1f",
				player.position.x, player.position.y, player.position.z);

			DrawFormatString(10, 250, GetColor(c.r, c.g, c.b), "pState = %s\n", player.state.c_str());
			
			DrawString(10, 300, "6 = 加速", GetColor(c.r, c.g, c.b));

			DrawString(10, 350, "7 = 初期地点", GetColor(c.r, c.g, c.b));

			DrawString(10, 400, "8 = 坂地点", GetColor(c.r, c.g, c.b));

			DrawString(10, 450, "9 = SPGageMax", GetColor(c.r, c.g, c.b));

			DrawString(10, 500, "0 = 青剣GageMas", GetColor(c.r, c.g, c.b));

			//DrawString(10, 550, "G = HP減少");

			SetFontSize(0);
		}
	}
	else if(cameraDbgOn == true)
	{
		if (DeleteDbgDisp == false)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
			DrawBox(0, 150, 380, 600, 0x454545, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			SetFontSize(20);

			//Cameraの情報表示
			DrawFormatStringF(0.0f, 300.0f, GetColor(c.r, c.g, c.b), "cPos = %.1f, %.1f, %.1f",
				camera.position.x, camera.position.y, camera.position.z);

			DrawFormatStringF(0.0f, 350.0f, GetColor(c.r, c.g, c.b), "cRota = %.2f, %.2f, %.2f",
				camera.rotation.x, camera.rotation.y, camera.rotation.z);

			DrawFormatStringF(0.0f, 400.0f, GetColor(c.r, c.g, c.b), "cTarget = %.1f, %.1f, %.1f",
				cameraTarget.x, cameraTarget.y, cameraTarget.z);
			
			//DrawFormatStringF(0.0f, 450.0f, GetColor(c.r, c.g, c.b), "cAimTar = %.1f, %.1f, %.1f",
			//	cameraAimTarget.x, cameraAimTarget.y, cameraAimTarget.z);

			DrawFormatStringF(0.0f, 450.0f, GetColor(c.r, c.g, c.b), "cState = %s\n", camera.state.c_str());

			DrawFormatStringF(0.0f, 500.0f, GetColor(c.r, c.g, c.b), "BeforeState = %s\n", cameraPtr->GetBeforeStateName().c_str());


			DrawFormatStringF(0.0f, 550.0f, GetColor(c.r, c.g, c.b), "cDelayPos = %.1f, %.1f, %.1f",
				cameraDelayPos.x, cameraDelayPos.y, cameraDelayPos.z);

			//DrawFormatStringF(0.0f, 500.0f, GetColor(c.r, c.g, c.b), "cHitPos = %.1f, %.1f, %.1f",
				//cameraPtr->GetCollHitPos().x, cameraPtr->GetCollHitPos().y, cameraPtr->GetCollHitPos().z);

			//DrawFormatStringF(0.0f, 550.0f, GetColor(c.r, c.g, c.b), "isHit = %d", cameraPtr->GetIsHit());


			DrawRotaGraphF(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 1.0f, 1.0 * DEGREE, hImage[POINT_FIXATION_MARK], true, false);

			SetFontSize(0);
		}
	}
	else if (playerDbgOn == true && cameraDbgOn == true)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawBox(0, 150, 380, 600, 0x454545, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		SetFontSize(20);



		SetFontSize(0);
	}
	
}

void Debug::AssignFindObjToField()
{
	playerPtr = FindGameObject<Player>();
	cameraPtr = FindGameObject<Camera>();
	inputManagerPtr = SceneManager::CommonScene()->FindGameObject<InputManager>();
	cameraStateBasePtr = FindGameObject<CameraStateBase>();
}
