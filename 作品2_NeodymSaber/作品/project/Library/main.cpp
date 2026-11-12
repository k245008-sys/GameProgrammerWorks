#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include "App.h"
#include "../Source/config.h"
#include "../resource.h"

#define CoGVersion (2.1)	//120fps対策あり

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);
	SetOutApplicationLogValidFlag(FALSE); // ログを出さない

	SetMainWindowText(WINDOW_NAME);
	SetWindowSizeExtendRate(WINDOW_EXTEND);
	ChangeWindowMode(WINDOW_MODE); // Windowモードの場合

	// アイコン読み込み
	HICON hIcon = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON), 0);
	SetWindowIconHandle(hIcon);

	//Effekseer追加
	//DirectX11を使用できるようにする(DirectX9も可、一部機能不可)
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	//Effekseer追加
	//Effekseerの初期化
	//引数は画面に表示する最大パーティクル数を設定する。
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}

	//フルスクに切り替え時リソースが消えるのを防ぐ
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	//DXライブラリのデバイスロスト時にコールバッグを設定
	//ただしDirect11を使用時は実行不要
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	//Effekseerに2D描画を設定(2Dのみ)
	Effekseer_Set2DSetting(SCREEN_WIDTH, SCREEN_HEIGHT);

	SetDrawScreen(DX_SCREEN_BACK);
	SetAlwaysRunFlag(TRUE);
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	AppInit();
	int mStartTime = GetNowCount();
	while (true) {
		int cur = GetNowCount();
		if (cur < mStartTime + 16) //120fps対策
			continue;
		mStartTime = cur;
		AppUpdate();
		ClearDrawScreen();
		AppDraw();
		if (ProcessMessage() == -1 || CheckHitKey(KEY_INPUT_ESCAPE) != 0 )
			break;
		ScreenFlip();
	}
	AppRelease();

	//Effekseerを終了する
	Effkseer_End();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
} 