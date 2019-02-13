//=============================================================================
//	インクルードファイル
//=============================================================================

#include "input.h"
#include "fade.h"
#include "C2DObj.h"
#include "scene.h"
#include "gamepad.h"
#include "sound.h"
//=============================================================================
//	グローバル変数宣言
//=============================================================================

static bool g_bend = false;	//	フェードインアウトフラグ
							//コントローラーに使う変数
static DIJOYSTATE2 js;
static LPDIRECTINPUTDEVICE8 pJoyDevice;
static HRESULT hr;
C2DObj *ptitle;
//=============================================================================
//	初期化処理
//=============================================================================

void Title_Initialize(void)
{
	ptitle = new C2DObj;
	g_bend = false;
	//コントローラー情報取得
	js = { 0 };
	pJoyDevice = *JoyDevice_Get();
	if (pJoyDevice)
	{
		hr = pJoyDevice->Acquire();
	}
	PlaySound(TITLE_BGM);
}

//=============================================================================
//	終了処理
//=============================================================================

void Title_Finalize(void)
{
	delete ptitle;
}

//=============================================================================
//	更新処理
//=============================================================================

void Title_Update(void)
{
	//コントローラー情報があるときのみ取得
	if (pJoyDevice)
	{
		pJoyDevice->GetDeviceState(sizeof(DIJOYSTATE2), &js);
	}
	//	スペースまたはAボタンでゲーム画面へ
	if (!g_bend)
	{
		if (Keyboard_IsTrigger(DIK_SPACE) || js.rgbButtons[0] & 0x80)
		{
			PlaySound(START_SE);
			Fade_Start(true, 3, 0, 0, 0);
			g_bend = true;
		}
	}
	else
	{
		if (!Fade_IsFade())
		{
			StopSound(TITLE_BGM);
			Fade_Start(false, 3, 0, 0, 0);
			Scene_Change(SCENE_INDEX_GAME);
		}
	}
}

//=============================================================================
//	描画処理
//=============================================================================

void Title_Draw(void)
{


	ptitle->m_Sprite_Draw(3, 0, 0, 0, 0, ptitle->Texture_GetWidth(3, 1), ptitle->Texture_GetHeight(3, 1));

}


