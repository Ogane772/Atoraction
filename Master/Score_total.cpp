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
#include "CTexture.h"
#include "sound.h"
#include "CEnemy.h"
//=============================================================================
//	グローバル変数宣言
//=============================================================================

static bool g_bend;			//	フェードインアウトフラグ
static bool Clear_flg;		//	クリア判定
static float Percent;		//	制圧率
static float Enemy_Percent;
static float Mark_Percent;
static int score_counter;	//	秒数
static int score_total;		//	合計
static float score_per;		//	加算用
static float Mark_per;
static int total;

C2DObj *pScore_total;
//=============================================================================
//	初期化処理
//=============================================================================

void Score_total_Initialize(void)
{
	PlaySound(RESULT_BGM);
	//C2DObj::Texture_Release(CTexture::TEX_SCREENSHOT);	//	テクスチャ破棄
	//C2DObj::Texture_Load(CTexture::TEX_SCREENSHOT);	//	テクスチャ読み込み
	pScore_total = new C2DObj;
	g_bend = false;
	Clear_flg = false;
	score_per = 0;
	Mark_per = 0;
	score_counter = 0;
	score_total = 0;
	total = 0;
	Percent = 0.0f;
	Enemy_Percent = 0.0f;
	Mark_Percent = 0;
	CGameObj::m_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);	//	αテスト有効
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
	Enemy_Percent = 762 * Get_EnemyPer();
	Percent = 100 * Get_EnemyPer();
	//score_total = CUserInterFace::Get_UIScore();
	
	//ゲームオーバー
	if (Get_EnemyPer() * 100 < 70)
	{
		Clear_flg = false;
	}
	//ゲームクリアー
	if (Get_EnemyPer() * 100 >= 70)
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
			PlaySound(ENTER_SE);
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
	
	pScore_total->m_Sprite_Draw(CTexture::TEX_SCREENSHOT, 0, 0, 0, 0, pScore_total->Texture_GetWidth(CTexture::TEX_SCREENSHOT, 1), pScore_total->Texture_GetHeight(CTexture::TEX_SCREENSHOT, 1));

	//撃破数
		//文字
		pScore_total->m_Sprite_Draw(CTexture::TEX_RESULT_BREAK, 100, 100, 0, 0, pScore_total->Texture_GetWidth(CTexture::TEX_RESULT_BREAK, 1), pScore_total->Texture_GetHeight(CTexture::TEX_RESULT_BREAK, 1));
		//値
		if (score_counter >= 100)
		{
			ResultScore_Draw(500, 100, CPlayer::Get_KoCount(), 5,CTexture::TEX_TOTAL, 0);
		}


		// 線
			//文字
			pScore_total->m_Sprite_Draw(CTexture::TEX_RESULT_BOU, 50, 600, 0, 0, pScore_total->Texture_GetWidth(CTexture::TEX_RESULT_BOU, 1), pScore_total->Texture_GetHeight(CTexture::TEX_RESULT_BOU, 1));

	//制圧率
		//文字
		pScore_total->m_Sprite_Draw(CTexture::TEX_RESULT_PER, 100, 400, 0, 0, pScore_total->Texture_GetWidth(CTexture::TEX_RESULT_PER, 1), pScore_total->Texture_GetHeight(CTexture::TEX_RESULT_PER, 1));
		if (score_counter >= 200)
		{
			////ゲージ
			//pScore_total->m_Sprite_Draw(CTexture::TEX_PER_GAUGE01, 530, 465, 0, 0, pScore_total->Texture_GetWidth(CTexture::TEX_PER_GAUGE01, 1), pScore_total->Texture_GetHeight(CTexture::TEX_PER_GAUGE01, 1));
			//pScore_total->m_Sprite_Draw(CTexture::TEX_PER_GAUGE02, 530, 465, 0, 0, score_per * 2, pScore_total->Texture_GetHeight(CTexture::TEX_PER_GAUGE02, 1));
			////指標
			//pScore_total->m_Sprite_Draw(CTexture::TEX_BER, 510 + score_per * 2, 440, 0, 0, pScore_total->Texture_GetWidth(CTexture::TEX_BER, 1), pScore_total->Texture_GetHeight(CTexture::TEX_BER, 1));
		

			//ゲージ
			pScore_total->Sprite_Draw(CTexture::TEX_MP3, 631, 470, 0, 0, 791, 54, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
			pScore_total->Sprite_Draw(CTexture::TEX_HP3, 631, 470, 0, 0, score_per, 54, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
			pScore_total->Sprite_Draw(CTexture::TEX_UI_BER, 500, 437, 0, 0, 1024, 172, 0.0f, 0.0f, 1.0f, 0.8f, 0.0f);
			//指標					
			pScore_total->Sprite_Draw(CTexture::TEX_UI_MEMORI, 614 + 532, 450, 0, 0, 43, 38, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
			pScore_total->Sprite_Draw(CTexture::TEX_UI_MEMORI, 614 + 532, 510, 0, 0, 43, 38, 43 / 2, 38 / 2, 1.0f, 1.0f, D3DXToRadian(180));

			//値
			ResultScore_Draw(1500, 380, (int)Percent, 2, 1);

			//指標とゲージ動かしてるとこ
			if (score_per <= Enemy_Percent)
			{
				score_per+= 3;
			}

			
		}
		
		


	

	//合計
		//文字
		pScore_total->m_Sprite_Draw(CTexture::TEX_RESULT_TOTAL, 140, 700, 0, 0, pScore_total->Texture_GetWidth(CTexture::TEX_RESULT_TOTAL, 1), pScore_total->Texture_GetHeight(CTexture::TEX_RESULT_TOTAL, 1));
		
		if (score_counter >= 450)
		{
			if (Clear_flg == false)
			{
				//値
				ResultScore_Draw(600, 710, score_total, 5, 1);
				//スコアまで
				if (score_total < C3DObj::Get_Score())
				{
					score_total += 100;
				}
			}
			if (Clear_flg == true)
			{

				if (score_counter >= 500)
				{
					//クリアボーナス用
					pScore_total->m_Sprite_Draw(CTexture::TEX_CLEAR_BONUS, 1260, 580, 0, 0, pScore_total->Texture_GetWidth(CTexture::TEX_CLEAR_BONUS, 1), pScore_total->Texture_GetHeight(CTexture::TEX_CLEAR_BONUS, 1));
					//2倍までプラス
					if (score_total < C3DObj::Get_Score())
					{
						score_total += 100;
					}
				}

				//値
				ResultScore_Draw(600, 710, C3DObj::Get_Score() + score_total, 5, 0);
			}
		}

}


