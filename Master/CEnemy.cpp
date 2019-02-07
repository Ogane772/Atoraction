//////////////////////////////////////////////////
////
////	エネミークラス
////
//////////////////////////////////////////////////


//=============================================================================
//	インクルードファイル
//=============================================================================

#include "CEnemy.h"
#include "CEnemy_Small.h"
#include "CEnemy_Middle.h"
#include "CEnemy_Big.h"
#include "CEnemy_Special.h"
#include "Cplayer.h"
#include "common.h"
//=============================================================================
//	定数定義
//=============================================================================


//=============================================================================
//	静的変数
//=============================================================================

//	エネミー移動用構造体
CEnemy::ENEMY_MOVE CEnemy::m_EnemyMove[8] = {
	{ D3DXVECTOR3(0.0f,0.0f,1.0f),D3DXToRadian(-90.0f) },
	{ D3DXVECTOR3(1.0f,0.0f,1.0f),D3DXToRadian(-45.0f) },
	{ D3DXVECTOR3(1.0f,0.0f,0.0f),D3DXToRadian(0.0f) },
	{ D3DXVECTOR3(1.0f,0.0f,-1.0f),D3DXToRadian(45.0f) },
	{ D3DXVECTOR3(-1.0f,0.0f,-1.0f),D3DXToRadian(135.0f) },
	{ D3DXVECTOR3(-1.0f,0.0f,1.0f),D3DXToRadian(-135.0f) },
	{ D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DXToRadian(90.0f) },
};

//	エネミーエミッター
CEnemy::ENEMY_EMITTER CEnemy::m_EnemyEmitter[]
{
	{ 0   , TYPE_SMALL, D3DXVECTOR3( 10.0f, 0.0f , 10.0f), DIRE_NORTH	   ,false },
    { 0	  , TYPE_MIDDLE, D3DXVECTOR3( 20.0f, 0.0f , 20.0f), DIRE_EAST	   ,false },
	{ 0	  , TYPE_SPECIAL, D3DXVECTOR3( 30.0f, 0.0f , 30.0f), DIRE_NORTHWEST ,false },
	{ 0	  , TYPE_BIG, D3DXVECTOR3( 20.0f, 0.0f , 10.0f), DIRE_SOUTHEAST ,false },
/*	{ 0	  , TYPE_SMALL, D3DXVECTOR3( 0.0f , 0.0f , 0.0f ), DIRE_NORTHEAST ,false },

	{ 100 , TYPE_SMALL, D3DXVECTOR3( 50.0f, 0.0f , 10.0f), DIRE_SOUTH     ,false },
	{ 130 , TYPE_SMALL, D3DXVECTOR3( 60.0f, 0.0f , 30.0f), DIRE_SOUTH     ,false },
	{ 160 , TYPE_SMALL, D3DXVECTOR3( 70.0f, 0.0f , 50.0f), DIRE_SOUTH     ,false },
	{ 190 , TYPE_SMALL, D3DXVECTOR3( 80.0f, 0.0f , 80.0f), DIRE_SOUTH     ,false },
	{ 210 , TYPE_SMALL, D3DXVECTOR3( 90.0f, 0.0f , 50.0f), DIRE_SOUTH     ,false },
	{ 240 , TYPE_SMALL, D3DXVECTOR3(-50.0f, 0.0f , 60.0f), DIRE_SOUTH     ,false },
	/*{ 300 , TYPE_SMALL, D3DXVECTOR3(-50.0f, 0.0f , 10.0f), DIRE_SOUTH     ,false },
	{ 300 , TYPE_SMALL, D3DXVECTOR3(-50.0f, 0.0f , 20.0f), DIRE_SOUTH     ,false },
	{ 300 , TYPE_SMALL, D3DXVECTOR3(-50.0f, 0.0f , 30.0f), DIRE_SOUTH     ,false },
	{ 300 , TYPE_SMALL, D3DXVECTOR3(-50.0f, 0.0f , 40.0f), DIRE_SOUTH     ,false },
	{ 300 , TYPE_SMALL, D3DXVECTOR3(-50.0f, 0.0f , 50.0f), DIRE_SOUTH     ,false },
	{ 300 , TYPE_SMALL, D3DXVECTOR3(-50.0f, 0.0f , 60.0f), DIRE_SOUTH     ,false },
	{ 500 , TYPE_SMALL, D3DXVECTOR3( 50.0f, 0.0f ,-10.0f), DIRE_SOUTH     ,false },
	{ 500 , TYPE_SMALL, D3DXVECTOR3( 50.0f, 0.0f ,-20.0f), DIRE_SOUTH     ,false },
	{ 500 , TYPE_SMALL, D3DXVECTOR3( 50.0f, 0.0f ,-30.0f), DIRE_SOUTH     ,false },
	{ 500 , TYPE_SMALL, D3DXVECTOR3( 50.0f, 0.0f ,-40.0f), DIRE_SOUTH     ,false },
	{ 500 , TYPE_SMALL, D3DXVECTOR3( 50.0f, 0.0f ,-50.0f), DIRE_SOUTH     ,false },
	{ 500 , TYPE_SMALL, D3DXVECTOR3( 50.0f, 0.0f ,-60.0f), DIRE_SOUTH     ,false },*/
};

int CEnemy::m_ENEMY_MAX = sizeof(CEnemy_Small::m_EnemyEmitter) / sizeof(m_EnemyEmitter[0]);

int CEnemy::m_EnemyNum[TYPE_MAX] = {};

//=============================================================================
//	生成
//=============================================================================

CEnemy::CEnemy()
{
	m_EnemyNum[TYPE_ALL]++;
}

CEnemy::CEnemy(int EnemyType)
{
	m_Type = EnemyType;
	m_EnemyIndex = m_EnemyNum[TYPE_ALL];
	m_EnemyNum[TYPE_ALL]++;
	m_EnemyNum[EnemyType]++;
	m_Attack = 0;
	m_Score = 0;
	m_Direction = 0;
	m_DirectionAngle = 0;
	m_MoveCheck = 0;
	m_EnemyFlying = false;
	m_EnemyFlyingDown = false;
	m_FlyingCount = 0;

	
}


//=============================================================================
//	破棄
//=============================================================================

CEnemy::~CEnemy()
{
	m_EnemyEmitter[m_EnemyIndex].CreateCheck = false;
	m_EnemyNum[TYPE_ALL]--;
}

void CEnemy::Create(void)
{
	for (int i = 0;i < m_ENEMY_MAX;i++)
	{
		if (!m_EnemyEmitter[i].CreateCheck)
		{
			if (m_FrameCount == m_EnemyEmitter[i].CreateFrame)
			{
				if (m_EnemyEmitter[i].Type == TYPE_SMALL)
				{
					CEnemy_Small *penemysmall = new CEnemy_Small(&m_EnemyEmitter[i]);
					m_EnemyEmitter[i].CreateCheck = true;
				}
				if (m_EnemyEmitter[i].Type == TYPE_MIDDLE)
				{
					CEnemy_Middle *penemymiddle = new CEnemy_Middle(&m_EnemyEmitter[i]);
					m_EnemyEmitter[i].CreateCheck = true;
				}
				if (m_EnemyEmitter[i].Type == TYPE_SPECIAL)
				{
					CEnemy_Special *penemyspecial = new CEnemy_Special(&m_EnemyEmitter[i]);
					m_EnemyEmitter[i].CreateCheck = true;
				}
				if (m_EnemyEmitter[i].Type == TYPE_BIG)
				{
					CEnemy_Big *penemybig = new CEnemy_Big(&m_EnemyEmitter[i]);
					m_EnemyEmitter[i].CreateCheck = true;
				}
			}
		}
	}
}

void CEnemy::Enemy_Finalize(int Index)
{
	m_EnemyEmitter[Index].CreateCheck = false;
}


void CEnemy::EnemyMove(int direction, float speed)
{
	if (direction < 8)
	{
		D3DXMatrixTranslation(&m_mtxTranslation, m_EnemyMove[direction].Move.x * speed, m_EnemyMove[direction].Move.y * speed, m_EnemyMove[direction].Move.z * speed);
	}
	
}

void CEnemy::EnemyAngleChange(int direction)
{
	if (direction < 8)
	{
		D3DXMatrixRotationY(&m_mtxRotation, m_EnemyMove[direction].Angle);
	}
}






C3DObj *CEnemy::Get_Enemy(int type)
{
	C3DObj *penemy = C3DObj::Get(type);
	if (penemy)
	{
		if (penemy->Get_3DObjType() == C3DObj::TYPE_ENEMY)
		{

			return penemy;

		}
	}
	return NULL;
}


C3DObj *CEnemy::Get_AllEnemy(void)
{
	return NULL;
}

C3DObj *CEnemy::Get_Map_Enemy(int Index)
{
	C3DObj *pEnemy = C3DObj::Get(Index);
	if (pEnemy)
	{
		if (pEnemy->Get_3DObjType() == C3DObj::TYPE_ENEMY)
		{
			if (pEnemy->Get_DrawCheck())
			{
				return pEnemy;
			}
		}
	}
	return NULL;
}


bool CEnemy::PlayerCheck(void)
{
	C3DObj *pplayer = CPlayer::Get_Player();
	float l = 10;//範囲
	D3DXMATRIX playerworld = pplayer->Get_mtxWorld();
	float cc = (playerworld._41 - m_mtxWorld._41) * (playerworld._41 - m_mtxWorld._41) + (playerworld._43 - m_mtxWorld._43) *  (playerworld._43 - m_mtxWorld._43);


	return cc < (l * l);

}

void CEnemy::Chase_Player(void)
{
	C3DObj *pplayer = CPlayer::Get_Player();
	D3DXMATRIX playerworld = pplayer->Get_mtxWorld();
	float x = playerworld._41 - m_mtxWorld._41;
	float z = playerworld._43 - m_mtxWorld._43;

	D3DXMATRIX mtxtrans;
	D3DXMatrixTranslation(&mtxtrans, x * 0.015f, 0.0f, z * 0.015f);
	m_mtxTranslation *= mtxtrans;

	float angle = (float)(atan2(-z, x));
	D3DXMatrixRotationY(&m_mtxRotation, angle);
}

bool CEnemy::Draw_Check(void)
{
	C3DObj *pplayer = CPlayer::Get_Player();
	//float l = SYLINDERSIZE;//範囲
	D3DXMATRIX playerworld = pplayer->Get_mtxWorld();
	float cc = (playerworld._41 - m_mtxWorld._41) * (playerworld._41 - m_mtxWorld._41) + (playerworld._43 - m_mtxWorld._43) *  (playerworld._43 - m_mtxWorld._43);

	if (cc < (FIELDSIZE * FIELDSIZE))
	{
		m_DrawCheck = true;
	}
	else
	{
		m_DrawCheck = false;
	}

	return m_DrawCheck;
}

void CEnemy::Comeback_Move(float speed)
{
	if (m_MoveCheck)
	{
		D3DXMATRIX mtxtrans;
		D3DXMatrixTranslation(&mtxtrans, m_EnemyMove[m_Direction].Move.x * speed, m_EnemyMove[m_Direction].Move.y * speed, m_EnemyMove[m_Direction].Move.z * speed);
		m_mtxTranslation *= mtxtrans;

		if (m_FrameCount - m_TimeKeep >= 180)
		{
			m_MoveCheck = false;
			m_Direction += 2;
		}
	}
	else
	{
		float angle = (float)(atan2(-m_mtxWorld._43, -m_mtxWorld._41));
		D3DXMatrixRotationY(&m_mtxRotation, angle);
		D3DXVECTOR3 move = (D3DXVECTOR3((float)(cos(angle)), 0.0f, (float)(sin(angle))));

		D3DXMATRIX mtxtrans;
		D3DXMatrixTranslation(&m_mtxTranslation, m_mtxWorld._41 + move.x, m_mtxWorld._42, m_mtxWorld._43 + move.z);

	}
}

void CEnemy::Enemy_Damage(float flyinghigh)
{
	if (!m_EnemyFlying)
	{
		m_Hp--;
		m_EnemyFlying = true;
		m_FlyingMove = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43) - m_PosKeep;
		m_FlyingMove.y = flyinghigh;

	}
}

void CEnemy::Enemy_Flying(float speed)
{
	if (m_EnemyFlying)
	{
		if (m_Hp != 0)
		{
			if (!m_EnemyFlyingDown)
			{
				D3DXMatrixTranslation(&m_mtxTranslation, m_mtxWorld._41 + m_FlyingMove.x * speed, m_mtxWorld._42 + m_FlyingMove.y, m_mtxWorld._43 + m_FlyingMove.z * speed);
				m_FlyingCount++;
				if (m_FlyingCount >= 60)
				{
					m_EnemyFlyingDown = true;
				}
			}
			else
			{
				
				D3DXMatrixTranslation(&m_mtxTranslation, m_mtxWorld._41 + m_FlyingMove.x * speed, m_mtxWorld._42 - m_FlyingMove.y, m_mtxWorld._43 + m_FlyingMove.z * speed);
				m_FlyingCount--;
				if (m_FlyingCount <= 0)
				{
					m_EnemyFlying = false;
					m_EnemyFlyingDown = false;
					m_DamageFlag = false;
					
				}
			}
		}
		else
		{
			D3DXMatrixTranslation(&m_mtxTranslation, m_mtxWorld._41 + m_FlyingMove.x * (speed * 2), m_mtxWorld._42 + m_FlyingMove.y, m_mtxWorld._43 + m_FlyingMove.z * (speed * 2));
		}
	}
}