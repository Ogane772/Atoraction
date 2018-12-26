//=============================================================================
//	インクルードファイル
//=============================================================================

#include "input.h"
#include "fade.h"
#include "C2DObj.h"
#include "scene.h"
#include "game.h"
#include "score_draw.h"
#include "CUserInterface.h"
#include "Cplayer.h"

//=============================================================================
//	グローバル変数宣言
//=============================================================================

static bool g_bend;			//	フェードインアウトフラグ
static bool Clear_flg;		//	クリア判定
static float Percent;		//	制圧率
static int score_counter;	//	秒数
static int score_total;		//	合計
static int score_per;		//	加算用
static int total;
C2DObj *pScore_total;
//=============================================================================
//	初期化処理
//=============================================================================

void Score_total_Initialize(void)
{
	pScore_total = new C2DObj;
	g_bend = false;
	Clear_flg = false;
	score_per = 0;
	score_counter = 0;
	score_total = 0;
	total = 0;
	Percent = 0;
}

//=============================================================================
//	終了処理
//=============================================================================

void Score_total_Finalize(void)
{
	delete pScore_total;
}

//=============================================================================
//	更新処理
//=============================================================================

void Score_total_Update(void)
{
	//スコア画面でカウンタースタート
	score_counter++;

	//ゲージの長さに対する制圧率
	Percent = 200 * Get_CheckPer();

	//score_total = CUserInterFace::Get_UIScore();
	
	//ゲームオーバー
	if (Get_CheckPer() * 100 < 80)
	{
		Clear_flg = false;
	}
	//ゲームクリアー
	if (Get_CheckPer() * 100 >= 80)
	{
		Clear_flg = true;
	}

	//	スペースでタイトル画面へ
	if (!g_bend)
	{
		if (Keyboard_IsTrigger(DIK_SPACE))
		{
			Fade_Start(true, 3, 0, 0, 0);
			g_bend = true;
			score_counter = 0;
		}
	}
	else
	{
		if (!Fade_IsFade())
		{
			Fade_Start(false, 3, 0, 0, 0);
			Scene_Change(SCENE_INDEX_RESULT);
		}
	}
}

//=============================================================================
//	描画処理
//=============================================================================

void Score_total_Draw(void)
{
	//撃破数
		//文字
		pScore_total->m_Sprite_Draw(14, 100, 70, 0, 0, pScore_total->Texture_GetWidth(14, 1), pScore_total->Texture_GetHeight(14, 1));
		//値
		if (score_counter >= 100)
		{
			ResultScore_Draw(300, 30, CPlayer::Get_KoCount(), 5, 1);
		}

	//制圧率
		//文字
		pScore_total->m_Sprite_Draw(15, 100, 200, 0, 0, pScore_total->Texture_GetWidth(15, 1), pScore_total->Texture_GetHeight(15, 1));
		if (score_counter >= 200)
		{
			//ゲージ
			pScore_total->m_Sprite_Draw(7, 400, 215, 0, 0, pScore_total->Texture_GetWidth(7, 1), pScore_total->Texture_GetHeight(7, 1));
			pScore_total->m_Sprite_Draw(6, 400, 215, 0, 0, score_per, pScore_total->Texture_GetHeight(6, 1));
			//指標
			pScore_total->m_Sprite_Draw(18, 380 + score_per, 204, 0, 0, pScore_total->Texture_GetWidth(18, 1), pScore_total->Texture_GetHeight(18, 1));
		
			//値
			ResultScore_Draw(600, 170, Percent/2, 2, 1);

			//指標とゲージ動かしてるとこ
			if (score_per <= Percent)
			{
				score_per++;
			}
		}
		
		


	//線
		//文字
		pScore_total->m_Sprite_Draw(16, 50, 300, 0, 0, pScore_total->Texture_GetWidth(16, 1), pScore_total->Texture_GetHeight(16, 1));
	

	//合計
		//文字
		pScore_total->m_Sprite_Draw(17, 120, 400, 0, 0, pScore_total->Texture_GetWidth(17, 1), pScore_total->Texture_GetHeight(17, 1));
		
		if (score_counter >= 450)
		{
			if (Clear_flg == false)
			{
				//値
				ResultScore_Draw(300, 360, score_total, 5, 1);
				//スコアまで
				if (score_total < CUserInterFace::Get_UIScore())
				{
					score_total += 100;
				}
			}
			if (Clear_flg == true)
			{
				if (score_counter >= 500)
				{
					//クリアボーナス用
					pScore_total->m_Sprite_Draw(20, 700, 280, 0, 0, pScore_total->Texture_GetWidth(20, 1), pScore_total->Texture_GetHeight(20, 1));
					//2倍までプラス
					if (score_total < (CUserInterFace::Get_UIScore() * 2))
					{
						score_total += 2;
					}
				}

				//値
				ResultScore_Draw(300, 360, score_total, 5, 1);
			}
		}

}


