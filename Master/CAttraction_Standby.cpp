//////////////////////////////////////////////////
////
////	アトラクション(建設中)クラス
////
//////////////////////////////////////////////////

//=============================================================================
//	インクルードファイル
//=============================================================================

#include "CAttraction_Standby.h"
#include "input.h"
#include "Cplayer.h"
#include "debug_font.h"
#include "time.h"
#include "move.h"
//=============================================================================
//	定数定義
//=============================================================================
//コースターモデルはここで表示 時間管理も
#define SPEED (0.05f)
#define SIZE (0.8f)
#define END_TIME (120)	//待機時間	

//仮の数字
#define STANDBY_HP (40)
#define STANDBY_MP (1)
#define STANDBY_ATK (3)
#define SCORE (1)
#define STANDBY_SCALE (1)
//=============================================================================
//	静的変数
//=============================================================================

//=============================================================================
//	グローバル変数
//=============================================================================

//=============================================================================
//	生成
//=============================================================================

Standby::Standby() :CAttraction(AT_STANDBY), C3DObj(AT_STANDBY)
{
	Initialize();
}

Standby::~Standby()
{

}

void Standby::Initialize()
{
	m_AttractionIndex = Get_AttractionIndex(AT_ALL);

	m_Enable = true;

	CoolTime = 0;//クールタイム
	B_CoolTime;//クールタイムのブール

	B_CoolTime = true;

	C3DObj *playerget = CPlayer::Get_Player();
	D3DXMATRIX mtx = playerget->Get_mtxWorld();
	D3DXMatrixTranslation(&m_mtxTranslation, mtx._41, 0, mtx._43);//X,Y,Zを渡す
	D3DXMatrixScaling(&m_mtxScaling, STANDBY_SCALE, STANDBY_SCALE, STANDBY_SCALE);
	m_mtxWorld = m_mtxScaling * m_mtxTranslation;

	Thing_Normal_model = GetNormalModel(MODELL_STANDBY);
}

void Standby::Update(void)
{
	//有効時間を引く
	/*
	if (m_FrameCount - m_TimeKeep <= END_TIME)
	{
		
		C3DObj *playerget = CPlayer::Get_Player();
		D3DXMATRIX playermatrix = playerget->Get_mtxTranslation();

		m_mtxTranslation = playermatrix;
		D3DXMatrixScaling(&m_mtxScaling, STANDBY_SCALE, STANDBY_SCALE, STANDBY_SCALE);
		D3DXMatrixRotationY(&m_mtxRotation, D3DXToRadian(0));
		m_mtxWorld = m_mtxScaling * m_mtxRotation * m_mtxTranslation;
	}
	else
	{
		C3DObj_delete();
	}*/
}

void Standby::Draw(void)
{
	//DebugFont_Draw(600, 30, "Coaster  = %d\n,", *coaster);
	//DebugFont_Draw(600, 60, "CoolTime = %d\n,", endfream);
	//DebugFont_Draw(600, 0, "U = %f\n,", u);
	if (m_Enable)
	{
		Thing_Normal_model->vPosition = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);

		DrawDX_Normal(m_mtxWorld, MODELL_STANDBY, Thing_Normal_model);
	}
}

void Standby::Finalize(void)
{
	Attraction_Finalize(m_AttractionIndex);
}

void Standby::Standby_Create(void)
{

}



C3DObj *Standby::Get_Standby(void)
{
	for (int i = 0; i < MAX_GAMEOBJ; i++)
	{
		C3DObj *Standby = C3DObj::Get(i);
		if (Standby)
		{
			if (Standby->Get_3DObjType() == C3DObj::TYPE_STADBY)
			{
				return Standby;
			}
		}
	}
	return NULL;
}