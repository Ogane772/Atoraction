
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
#include "CEnemy.h"
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

CUserInterFace::CUserInterFace() :CGameObj(CGameObj::TYPE_UI)
{
	
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
	C3DObj *playerget = CPlayer::Get_Player();



	int hp = playerget->Get_Hp();
	Sprite_Draw(TEX_HP,20, 10, 0, 0, HP_GAGE_WIDTH, HP_GAGE_HEIGHT);
	Sprite_Draw(TEX_HP2, 20, 10, 0, 0, HP_GAGE_WIDTH * hp / HP_MAX, HP_GAGE_HEIGHT);

	//MP
	int mp = playerget->Get_Mp();
	Sprite_Draw(TEX_HP, 20, 70, 0, 0, MP_MAX*5, HP_GAGE_HEIGHT);
	Sprite_Draw(TEX_MP, 20, 70, 0, 0, mp*5, HP_GAGE_HEIGHT);

	//MPストック
	int stock = playerget->Get_MpStock();
	Sprite_Draw(TEX_STOCK, MP_MAX * 6, 60, 0, 0, CTexture::Texture_GetWidth(TEX_STOCK,1), CTexture::Texture_GetHeight(TEX_STOCK, 1));
	Mp_Draw(MP_MAX * 6, 80, stock, 2,0);

	//制限時間
	
	int t = CGameObj::m_FrameCount / 60;
	Num_Draw(WINDOW_WIDTH / 2-25, -25, GAMEEND/60-t,2,0,true);
	int tt = CGameObj::m_FrameCount % 61*1.7;
	if (CGameObj::m_FrameCount >= GAMEEND)
	{
		tt = 100;
	}
	Mp_Draw(WINDOW_WIDTH / 2+230, 80, 100 - tt, 2,true);

	//	撃破数
	int ko = CPlayer::Get_KoCount();
	Num_Draw(WINDOW_WIDTH / 3, WINDOW_HIGHT / 2+90, ko, 3, 1,false);


	//マップ----------------------------------------------------
	D3DXMATRIX playermatrix = playerget->Get_mtxTranslation();
	
	//下絵
	Sprite_Draw(TEX_MAP, 850.0f, 0.0f, 0.0f, 0.0f, 150, 150);
	//プレイヤ
	Sprite_Draw(TEX_Player_Icon, 880.0f + playermatrix._41, 60.0f - playermatrix._43, 0.0f, 0.0f, 60, 30);
	

	//エネミー
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		C3DObj *enemyget = CEnemy::Get_Map_Enemy(i);
		if (enemyget)
		{
			D3DXMATRIX enemymatrix = enemyget->Get_mtxTranslation();

			Sprite_Draw(TEX_ENEMY_ICON, 905.0f + enemymatrix._41, 70.0f - enemymatrix._43, 0.0f, 0.0f, 6, 6);
		}
	}
}

void CUserInterFace::Finalize(void)
{

}

void CUserInterFace::UICreate(void)
{
	CUserInterFace *pui = new CUserInterFace;

}