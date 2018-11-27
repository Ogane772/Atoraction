
//////////////////////////////////////////////////
////
////	UIクラス
////
//////////////////////////////////////////////////

//=============================================================================
//	インクルードファイル
//=============================================================================

#include "CUserInterface.h"
#include "Cplayer.h"
#include "CCamera.h"
#include "common.h"
#include "score_draw.h"
//=============================================================================
//	定数定義
//=============================================================================
#define HP_GAGE_WIDTH (300)	//HPゲージの幅
#define HP_GAGE_HEIGHT (40)	//ゲージの高さ

#define MP_GAGE_WIDTH (350)	//MPゲージの幅

//=============================================================================
//	静的変数
//=============================================================================



//=============================================================================
//	グローバル変数
//=============================================================================

//=============================================================================
//	生成
//=============================================================================

CUserInterFace::CUserInterFace()
{
	m_GameObjNum--;
}

//=============================================================================
//	破棄
//=============================================================================

CUserInterFace::~CUserInterFace()
{

}




void CUserInterFace::Update(void)
{

}
void CUserInterFace::Draw(void)
{
	CPlayer *pp = CPlayer::Get_Player(0);
	int hp = pp->Get_Hp();
	Sprite_Draw(TEX_HP,20, 10, 0, 0, HP_GAGE_WIDTH, HP_GAGE_HEIGHT);
	Sprite_Draw(TEX_HP2, 20, 10, 0, 0, HP_GAGE_WIDTH * hp / HP_MAX, HP_GAGE_HEIGHT);

	//MP
	int mp = pp->Get_Mp();
	Sprite_Draw(TEX_HP, 20, 70, 0, 0, MP_MAX*5, HP_GAGE_HEIGHT);
	Sprite_Draw(TEX_MP, 20, 70, 0, 0, mp*5, HP_GAGE_HEIGHT);

	//MPストック
	int stock = pp->Get_MpStock();
	Sprite_Draw(TEX_STOCK, MP_MAX * 6, 60, 0, 0, CTexture::Texture_GetWidth(TEX_STOCK,1), CTexture::Texture_GetHeight(TEX_STOCK, 1));
	Mp_Draw(MP_MAX * 6, 80, stock, 2,0);

	//制限時間
	int t = CGameObj::m_FrameCount / 60;
	Num_Draw(WINDOW_WIDTH / 6, -25, GAMEEND/60-t,2,0);
	int tt = CGameObj::m_FrameCount % 60*1.7;
	Mp_Draw(WINDOW_WIDTH / 2+170, 80, 99 - tt, 2,1);
}

void CUserInterFace::Finalize(void)
{

}