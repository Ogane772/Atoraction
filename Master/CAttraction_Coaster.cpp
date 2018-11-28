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

Coaster::Coaster() :CAttraction(TYPE_COASTER)
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
	endfream = J_TIME;
	keepfream = m_FrameCount;
	CPlayer *player = CPlayer::Get_Player(0);
	coaster = player->Get_Coaster();
	u = 0;

	//B_BaseTime = 0;
	//B_MoveTime = 0;

	D3DXMATRIX playermatrix = player->Get_mtxkeep();

	hp = COSTER_HP;
	mp = COSTER_MP;
	atk = COSTER_ATK;
	CPlayer *playerget = CPlayer::Get_Player(0);
	D3DXMATRIX mtx = playerget->Get_mtxWorld();
	D3DXMatrixTranslation(&m_mtxTranslation, mtx._41, mtx._42, mtx._43);//X,Y,Zを渡す
	D3DXMatrixScaling(&m_mtxScaling, COSTER_SCALE, COSTER_SCALE, COSTER_SCALE);
	m_mtxWorld = m_mtxScaling * m_mtxTranslation;

	NxMat33 mat1;
	mat1.rotZ(0);
	NxVec3 scaleDwarf = NxVec3(COSTER_SCALE, COSTER_SCALE, COSTER_SCALE);	//	モデルスケール
	NxVec3 BBDwarf = NxVec3(0.0, 0.0, 0.0);	//	当たり判定の大きさ
	NxA_Coaster = CreateMeshAsBox(NxVec3(mtx._41, mtx._42 - 10, mtx._43), mat1, scaleDwarf, BBDwarf, MODELL_COASTER, false);


}

void Coaster::Update(void)
{
	if (m_Enable && *coaster)
	{
		CPlayer *player = CPlayer::Get_Player(0);
		D3DXMATRIX playermatrix = player->Get_mtx();

		//有効時間を引く
		endfream = J_TIME - (m_FrameCount - keepfream);
		if (*coaster == false)
		{
			endfream = clock();
			endfream = J_TIME;
		}

		if (endfream <= 0)
		{
			*coaster = false;
		}

		if (Keyboard_IsPress(DIK_D))
		{
			u += 10;
		}

		if (Keyboard_IsPress(DIK_A))
		{
			u -= 10;
		}
		if (Keyboard_IsTrigger(DIK_L))
		{
			*coaster = false;
		}

		NxVec3 tr = NxA_Coaster->getGlobalPosition();
		D3DXMatrixTranslation(&m_mtxTranslation, tr.x, tr.y, tr.z);
		D3DXMatrixScaling(&m_mtxScaling, COSTER_SCALE, COSTER_SCALE, COSTER_SCALE);
		D3DXMatrixRotationY(&m_mtxRotation, D3DXToRadian(u));
		
		

		m_mtxWorld = m_mtxRotation * m_mtxScaling * playermatrix;

	}
}

void Coaster::Draw(void)
{
	DebugFont_Draw(600, 30, "Coaster  = %d\n,", *coaster);
	DebugFont_Draw(600, 60, "CoolTime = %d\n,", endfream);
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