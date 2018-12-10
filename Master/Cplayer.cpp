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
#define ANGLE_Y (4)

//=============================================================================
//	静的変数
//=============================================================================

//D3DXMATRIX CPlayer::m_mtxWorld;
CPlayer *CPlayer::m_pPlayer[PLAYER_MAX] = {};
int CPlayer::m_PlayerNum = 0;
//=============================================================================
// 生�E
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
// 破棁E
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
	if (g_CosterMode)//コースターの晁E
	{
		m_mtxTranslation *= Move(FLONT, SPEED);
	}
	if (!g_CosterMode)//コースターじゃなぁE��ぁE
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
		//プレイヤーの角度変更
		if (Keyboard_IsPress(DIK_W))
		{
			if (player_kakudo != 0 && (player_kakudo >= -180 && player_kakudo < 0))
			{
				Model_Angle(true);//アングルフラグがtrueだったら右回転false左
			}
			if (player_kakudo != 360 && (player_kakudo >= 180 && player_kakudo < 360))
			{
				Model_Angle(true);
			}
			if (player_kakudo != 0 && (player_kakudo < 180 && player_kakudo >= 0))
			{
				Model_Angle(false);
			}
			if (player_kakudo != -360 && (player_kakudo < -180 && player_kakudo >= -360))
			{
				Model_Angle(false);
			}
		}

		if (Keyboard_IsPress(DIK_A))
		{
			if (player_kakudo != -90 && (player_kakudo <= 90 && player_kakudo > -90))
			{
				Model_Angle(false);
			}
			if (player_kakudo != -90 && (player_kakudo >= -270 && player_kakudo < -90))
			{
				Model_Angle(true);
			}
			if (player_kakudo != 270 && (player_kakudo > 90 && player_kakudo < 270))
			{
				Model_Angle(true);
			}
			if (player_kakudo != 270 && (player_kakudo >= 270 && player_kakudo < 360))
			{
				Model_Angle(false);
			}
		}

		if (Keyboard_IsPress(DIK_S))
		{
			if (player_kakudo != 180 && (player_kakudo >= 0 && player_kakudo < 180))
			{
				Model_Angle(true);
			}
			if (player_kakudo != 180 && (player_kakudo <= 360 && player_kakudo > 180))
			{
				Model_Angle(false);
			}
			if (player_kakudo != -180 && (player_kakudo < 0 && player_kakudo > -180))
			{
				Model_Angle(false);
			}
			if (player_kakudo != -180 && (player_kakudo >= -360 && player_kakudo < -180))
			{
				Model_Angle(false);
			}
		}

		if (Keyboard_IsPress(DIK_D))
		{
			if (player_kakudo != 90 && (player_kakudo >= -90 && player_kakudo < 90))
			{
				Model_Angle(true);
			}
			if (player_kakudo != 90 && (player_kakudo <= 270 && player_kakudo > 90))
			{
				Model_Angle(false);
			}
			if (player_kakudo != -270 && (player_kakudo <= -90 && player_kakudo > -270))
			{
				Model_Angle(false);
			}
			if (player_kakudo != -270 && (player_kakudo <= -270 && player_kakudo > -360))
			{
				Model_Angle(true);
			}
		}


		if (player_kakudo >= 360 || player_kakudo <= -360)
		{
			player_kakudo = 0;
		}

		if (Keyboard_IsTrigger(DIK_P))
		{
			CAttraction::Create(CAttraction::TYPE_COASTER);
			g_CosterMode = true;
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


	D3DXMatrixRotationY(&m_mtxRotation, D3DXToRadian(180 + player_kakudo));

	//D3DXMatrixTranslation(&m_mtxTranslation, tank_position.x + tank_angleX, tank_position.y, tank_position.z + tank_angleZ);

	m_mtxWorld = m_mtxRotation * m_mtxScaling * m_mtxTranslation;

	DrawDX2(m_mtxWorld, NxA_pPlayer, MODELL_PLAYER);
	//DrawDirectXMesh(NxA_pBoss);
	//DrawDirectXMesh(NxA_pPlayer);
	//	チE��チE��
	//DebugFont_Draw(300, 30, "%f\n,%f\n,%f\n,", m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);
	RenderPhysX();
}

//	初期匁E
void CPlayer::Player_Initialize(void)
{
	m_Hp = HP_MAX;
	m_Mp = 0;
	m_MpStock = MPSTOCK_INIT;
	m_Enable = true;
	g_CosterMode = false;
	//playerfront等�E初期匁E
	player_at = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	wheel_at = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	player_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	player_front = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXVec3Normalize(&player_front, &player_front);

	player_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVec3Cross(&player_right, &player_front, &player_up);
	D3DXVec3Normalize(&player_right, &player_right);
	D3DXVec3Cross(&player_up, &player_right, &player_front);
	D3DXVec3Normalize(&player_up, &player_up);
	player_kakudo = 0;

	D3DXMatrixTranslation(&m_mtxTranslation, 0, 1, 0);
	D3DXMatrixScaling(&m_mtxScaling, 0.5f, 1.0f, 0.5f);
	m_mtxKeepTranslation = m_mtxTranslation;
	m_mtxWorld = m_mtxScaling * m_mtxTranslation;

	NxMat33 mat1;
	//mat1.rotZ(0);
	NxVec3 scaleDwarf = NxVec3(1, 1, 1);	//	モチE��スケール
	NxVec3 BBDwarf = NxVec3(1.0f, 1.0f, 1.0f);	//	当たり判定�E大きさ

												//NxA_pPlayer = CreateMeshAsBox(NxVec3(0, 1, 0), mat1, scaleDwarf, BBDwarf, MODELL_PLAYER);
	NxA_pPlayer = CreateMeshAsSphere(NxVec3(0, 1, 0), 1.0, MODELL_PLAYER);

}

//	終亁E�E琁E
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

void CPlayer::Model_Angle(bool Angle_Flg)
{
	if (Angle_Flg == true)
	{
		player_kakudo += ANGLE_Y;
		D3DXMATRIX mtxR;
		//引数(&, 軸, angle)
		D3DXMatrixRotationAxis(&mtxR, &player_up, D3DXToRadian(ANGLE_Y));
		D3DXVec3TransformNormal(&player_front, &player_front, &mtxR);
		D3DXVec3TransformNormal(&player_right, &player_right, &mtxR);
	}
	else
	{
		player_kakudo += -ANGLE_Y;
		D3DXMATRIX mtxR;
		//引数(&, 軸, angle)
		D3DXMatrixRotationAxis(&mtxR, &player_up, D3DXToRadian(-ANGLE_Y));
		D3DXVec3TransformNormal(&player_front, &player_front, &mtxR);
		D3DXVec3TransformNormal(&player_right, &player_right, &mtxR);
	}
}

