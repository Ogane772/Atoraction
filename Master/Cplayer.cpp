//=============================================================================
//
//	Playerクラス
//
//=============================================================================

//=============================================================================
//	インクルードファイル
//=============================================================================

#include "Cplayer.h"
#include "input.h"
#include "move.h"
#include "model.h"
#include "CAttraction.h"
#include "debug_font.h"

//=============================================================================
//	定数定義
//=============================================================================
#define SPEED (0.2)
#define PLAYER_SAIZ (1)
#define MPSTOCK_INIT (5)
//=============================================================================
//	静的変数
//=============================================================================

//D3DXMATRIX CPlayer::m_mtxWorld;
CPlayer *CPlayer::m_pPlayer[PLAYER_MAX] = {};
int CPlayer::m_PlayerNum = 0;
//=============================================================================
// 生成
//=============================================================================
CPlayer::CPlayer()
{
	Player_Initialize();
	m_PlayerIndex = m_PlayerNum;
	m_PlayerNum++;
}

CPlayer *CPlayer::PlayerCreate(void)
{
	m_pPlayer[m_PlayerNum - 1] = new CPlayer;
	return m_pPlayer[m_PlayerNum - 1];
}


//=============================================================================
// 破棄
//=============================================================================
CPlayer::~CPlayer()
{
	//Player_Finalize();
	m_PlayerNum--;
}

//=============================================================================
// 更新
//=============================================================================
void CPlayer::Update(void)
{
	if (Keyboard_IsPress(DIK_W))
	{
		m_mtxTranslation *= Move(FLONT, SPEED);
	}
	if (Keyboard_IsPress(DIK_S))
	{
		m_mtxTranslation *= Move(BACK, SPEED);
	}
	if (Keyboard_IsPress(DIK_D))
	{
		m_mtxTranslation *= Move(RIGHT, SPEED);
	}
	if (Keyboard_IsPress(DIK_A))
	{
		m_mtxTranslation *= Move(LEFT, SPEED);
	}
	if (Keyboard_IsRelease(DIK_O))
	{
		CAttraction::Create(CAttraction::TYPE_COFFEE);
	}
	if (Keyboard_IsRelease(DIK_I))
	{
		CAttraction::Create(CAttraction::TYPE_FALL);
	}
	if (Keyboard_IsRelease(DIK_U))
	{
		CAttraction::Create(CAttraction::TYPE_WHEEL);
	}

	if (45.0*45.0 < (m_mtxTranslation._41*m_mtxTranslation._41) + (m_mtxTranslation._43 * m_mtxTranslation._43))
	{
		m_mtxTranslation = m_mtxKeepTranslation;
	}
	else
	{
		m_mtxKeepTranslation = m_mtxTranslation;
	}

	//	MP
	if (m_FrameCount % 60 == 0)
	{
		m_Mp++;
		if (m_Mp >= MP_MAX)
		{
			m_MpStock++;
			m_Mp = 0;
		}
	}



}
//=============================================================================
// 描画
//=============================================================================

void CPlayer::Draw(void)
{


	m_mtxWorld = m_mtxScaling * m_mtxTranslation;

	myData* mydata = (myData*)NxA_pPlayer->userData;

	/*mydata->meshTranslation.x = m_mtxWorld._41;
	mydata->meshTranslation.y = m_mtxWorld._42;
	mydata->meshTranslation.z = m_mtxWorld._43;
	NxA_pPlayer->setGlobalPosition(mydata->meshTranslation);*/

	DrawDX2(m_mtxWorld, NxA_pPlayer, MODELL_PLAYER);
	//DrawDirectXMesh(NxA_pBoss);
	//DrawDirectXMesh(NxA_pPlayer);
	//	デバッグ
	//DebugFont_Draw(300, 30, "%f\n,%f\n,%f\n,", m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);
	RenderPhysX();
}

//	初期化
void CPlayer::Player_Initialize(void)
{
	m_Hp = HP_MAX;
	m_Mp = 0;
	m_MpStock = MPSTOCK_INIT;
	m_Enable = true;
	D3DXMatrixTranslation(&m_mtxTranslation, 0, 1, 0);
	D3DXMatrixScaling(&m_mtxScaling, 0.5f, 1.0f, 0.5f);
	m_mtxKeepTranslation = m_mtxTranslation;
	m_mtxWorld = m_mtxScaling * m_mtxTranslation;

	NxMat33 mat1;
	//mat1.rotZ(0);
	NxVec3 scaleDwarf = NxVec3(1, 1, 1);	//	モデルスケール
	NxVec3 BBDwarf = NxVec3(1.0f, 1.0f, 1.0f);	//	当たり判定の大きさ

												//NxA_pPlayer = CreateMeshAsBox(NxVec3(0, 1, 0), mat1, scaleDwarf, BBDwarf, MODELL_PLAYER);
	NxA_pPlayer = CreateMeshAsSphere(NxVec3(0, 1, 0), 1.0, MODELL_PLAYER);

}

//	終了処理
void CPlayer::Finalize(void)
{
	for (int i = 0;i < m_PlayerNum;i++)
	{
		if (m_pPlayer[i])
		{
			delete m_pPlayer[i];
		}
	}
}

