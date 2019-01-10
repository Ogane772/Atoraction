//////////////////////////////////////////////////
////
////	アトラクション(ジェットコースター)クラス
////
//////////////////////////////////////////////////

//=============================================================================
//	インクルードファイル
//=============================================================================

#include "CAttraction_Coaster .h"
#include "input.h"
#include "Cplayer.h"
#include "Cphysx.h"
#include "debug_font.h"
#include "time.h"
#include "move.h"
//=============================================================================
//	定数定義
//=============================================================================
//コースターモデルはここで表示 時間管理も
#define SPEED (0.05f)
#define SIZE (0.8f)
#define J_TIME (480)	//使用時間

//仮の数字
#define COSTER_HP (40)
#define COSTER_MP (1)
#define COSTER_ATK (3)
#define SCORE (1)
#define COSTER_SCALE (1)
//=============================================================================
//	静的変数
//=============================================================================

//=============================================================================
//	グローバル変数
//=============================================================================

//=============================================================================
//	生成
//=============================================================================

Coaster::Coaster() :CAttraction(TYPE_COASTER), C3DObj(C3DObj::TYPE_COASTER)
{
	Initialize();
}

Coaster::~Coaster()
{

}

void Coaster::Initialize()
{
	m_AttractionIndex = Get_AttractionIndex(TYPE_ALL);

	m_Enable = true;

	m_TimeKeep = m_FrameCount;

	u = 90;



	

	m_Hp = COSTER_HP;
	m_Mp = COSTER_MP;
	m_Attack = COSTER_ATK;
	
	C3DObj *playerget = CPlayer::Get_Player();
	D3DXMATRIX mtx = playerget->Get_mtxWorld();
	D3DXMatrixTranslation(&m_mtxTranslation, mtx._41, mtx._42, mtx._43);//X,Y,Zを渡す
	D3DXMatrixScaling(&m_mtxScaling, COSTER_SCALE, COSTER_SCALE, COSTER_SCALE);
	m_mtxWorld = m_mtxScaling * m_mtxTranslation;

	NxMat33 mat1;
	NxVec3 scaleDwarf = NxVec3(COSTER_SCALE, COSTER_SCALE, COSTER_SCALE);	//	モデルスケール
	NxVec3 BBDwarf = NxVec3(0.0, 0.0, 0.0);	//	当たり判定の大きさ
	NxA_Coaster = CreateMeshAsBox(NxVec3(mtx._41, mtx._42 - 10, mtx._43), mat1, scaleDwarf, BBDwarf, MODELL_COASTER, false);


}

void Coaster::Update(void)
{
	
	

	//有効時間を引く
	
	if (m_FrameCount - m_TimeKeep <= J_TIME)
	{
		C3DObj *playerget = CPlayer::Get_Player();
		D3DXMATRIX playermatrix = playerget->Get_mtxTranslation();
		
		m_mtxTranslation = playermatrix;
		NxVec3 tr = NxA_Coaster->getGlobalPosition();
		D3DXMatrixScaling(&m_mtxScaling, COSTER_SCALE, COSTER_SCALE, COSTER_SCALE);
		D3DXMatrixRotationY(&m_mtxRotation, D3DXToRadian(u));
		m_mtxWorld = m_mtxScaling * m_mtxRotation * m_mtxTranslation;
	}
	else
	{
		C3DObj_delete();
	}
}

void Coaster::Draw(void)
{
	//DebugFont_Draw(600, 30, "Coaster  = %d\n,", *coaster);
	//DebugFont_Draw(600, 60, "CoolTime = %d\n,", endfream);
	DebugFont_Draw(600, 0, "U = %f\n,", u);
	if (m_Enable)
	{
		DrawDX2(m_mtxWorld, NxA_Coaster, MODELL_COASTER);
	}
}

void Coaster::Finalize(void)
{
	Attraction_Finalize(m_AttractionIndex);
	NxA_Coaster = NULL;
}

void Coaster::Coaster_Create(void)
{

}



C3DObj *Coaster::Get_Coaster(void)
{
	for (int i = 0;i < MAX_GAMEOBJ;i++)
	{
		C3DObj *Coaster = C3DObj::Get(i);
		if (Coaster)
		{
			if (Coaster->Get_3DObjType() == C3DObj::TYPE_COASTER)
			{
				return Coaster;
			}
		}
	}
	return NULL;
}