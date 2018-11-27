//=============================================================================
//	インクルードファイル
//=============================================================================

#include "input.h"
#include "fade.h"
#include "C2DObj.h"
#include "scene.h"


//=============================================================================
//	グローバル変数宣言
//=============================================================================

static bool g_bend;
C2DObj *r;
//=============================================================================
//	初期化処理
//=============================================================================

void Result_Initialize(void)
{
	r = new C2DObj;
	g_bend = false;
	
}

//=============================================================================
//	終了処理
//=============================================================================

void Result_Finalize(void)
{
	delete r;
}

//=============================================================================
//	更新処理
//=============================================================================

void Result_Update(void)
{
	if (!g_bend)
	{
		if (Keyboard_IsTrigger(DIK_SPACE))
		{
			Fade_Start(true, 3, 0, 0, 0);
			g_bend = true;
		}
	}
	else
	{
		if (!Fade_IsFade())
		{
			Fade_Start(false, 3, 0, 0, 0);
			Scene_Change(SCENE_INDEX_TITLE);
		}
	}
}

//=============================================================================
//	描画処理
//=============================================================================

void Result_Draw(void)
{
	r->m_Sprite_Draw(4, 0, 0, 0, 0, r->Texture_GetWidth(4, 1), r->Texture_GetHeight(4, 1));
}


