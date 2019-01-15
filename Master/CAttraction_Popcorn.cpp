//////////////////////////////////////////////////
////
////	アトラクション(ポップコーン)クラス
////
//////////////////////////////////////////////////

//=============================================================================
//	インクルードファイル
//=============================================================================

#include "CAttraction_Popcorn.h"
#include "Cplayer.h"
#include "debug_font.h"
//=============================================================================
//	定数定義
//=============================================================================
#define SPEED (0.05f)
#define POPCORN_SIZE (4)//当たり判定大きさ
#define POPCORN_SCALE (1) //モデルの大きさ
#define POPCORN_HP (40)
#define POPCORN_MP (1)
#define POPCORN_ATK (1)
#define SCORE (1)
//=============================================================================
//	静的変数
//=============================================================================
//	メンバ変数にする　カウントはm_FrameCountでとる　CEnemySmall参考にして

//=============================================================================
//	グローバル変数
//=============================================================================

//=============================================================================
//	生成
//=============================================================================

Popcorn::Popcorn() :CAttraction(TYPE_POPCORN), C3DObj(C3DObj::TYPE_ATTRACTION)
{
	Initialize();
}

Popcorn::~Popcorn()
{

}

void Popcorn::Initialize()
{
	m_AttractionIndex = Get_AttractionIndex(TYPE_ALL);

	m_Enable = true;

	CoolTime = 0;//クールタイム
	B_CoolTime;//クールタイムのブール

	B_CoolTime = true;
	m_Hp = POPCORN_HP;
	m_Mp = POPCORN_MP;
	m_Attack = POPCORN_ATK;

	C3DObj *playerget = CPlayer::Get_Player();
	D3DXMATRIX mtx = playerget->Get_mtxWorld();
	D3DXMatrixTranslation(&m_mtxTranslation, mtx._41, 0, mtx._43);//X,Y,Zを渡す
	D3DXMatrixScaling(&m_mtxScaling, POPCORN_SCALE, POPCORN_SCALE, POPCORN_SCALE);
	m_mtxWorld = m_mtxScaling * m_mtxTranslation;


	Thing_Normal_model = GetNormalModel(MODELL_POPCORN);

}

void Popcorn::Update(void)
{
	if (m_Enable)
	{
		//エフェクト処理を行う
	}
}

void Popcorn::Draw(void)
{
	//DebugFont_Draw(600, 30, "Dodai = %f\n,", angCup);
	//DebugFont_Draw(600, 60, "CoolTime = %d\n,", CoolTime);
	if (m_Enable)
	{

		Thing_Normal_model->vPosition = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);

		DrawDX_Normal(m_mtxWorld, MODELL_POPCORN, Thing_Normal_model);
	}
}

void Popcorn::Finalize(void)
{
	Attraction_Finalize(m_AttractionIndex);
}