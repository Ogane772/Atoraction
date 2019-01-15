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

//=============================================================================
//	定数定義
//=============================================================================


//=============================================================================
//	静的変数
//=============================================================================

//	エネミー移動用構造体
CEnemy::ENEMY_MOVE CEnemy::m_EnemyMove[8] = {
	{ D3DXVECTOR3(0.0f,0.0f,1.0f),D3DXToRadian(-90.0) },
	{ D3DXVECTOR3(1.0f,0.0f,1.0f),D3DXToRadian(-45.0) },
	{ D3DXVECTOR3(1.0f,0.0f,0.0f),D3DXToRadian(0.0) },
	{ D3DXVECTOR3(1.0f,0.0f,-1.0f),D3DXToRadian(45.0) },
	{ D3DXVECTOR3(-1.0f,0.0f,-1.0f),D3DXToRadian(135.0) },
	{ D3DXVECTOR3(-1.0f,0.0f,1.0f),D3DXToRadian(-135.0) },
	{ D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DXToRadian(90.0) },
};

//	エネミーエミッター
CEnemy::ENEMY_EMITTER CEnemy::m_EnemyEmitter[]
{
	{ 0   , TYPE_SMALL, D3DXVECTOR3( 10.0, 1.6 , 10.0), DIRE_NORTH	   ,false },
    { 0	  , TYPE_SMALL, D3DXVECTOR3( 20.0, 1.6 , 20.0), DIRE_EAST	   ,false },
	{ 0	  , TYPE_SMALL, D3DXVECTOR3( 30.0, 1.6 , 30.0), DIRE_NORTHWEST ,false },
	{ 0	  , TYPE_SMALL, D3DXVECTOR3( 20.0, 1.6 , 10.0), DIRE_SOUTHEAST ,false },
	{ 0	  , TYPE_SMALL, D3DXVECTOR3( 0.0 , 1.6 , 0.0 ), DIRE_NORTHEAST ,false },

	{ 100 , TYPE_SMALL, D3DXVECTOR3( 50.0, 1.6 , 10.0), DIRE_SOUTH     ,false },
	{ 100 , TYPE_SMALL, D3DXVECTOR3( 60.0, 1.6 , 30.0), DIRE_SOUTH     ,false },
	{ 100 , TYPE_SMALL, D3DXVECTOR3( 70.0, 1.6 , 50.0), DIRE_SOUTH     ,false },
	{ 100 , TYPE_SMALL, D3DXVECTOR3( 80.0, 1.6 , 80.0), DIRE_SOUTH     ,false },
	{ 100 , TYPE_SMALL, D3DXVECTOR3( 90.0, 1.6 , 50.0), DIRE_SOUTH     ,false },
	{ 100 , TYPE_SMALL, D3DXVECTOR3(-50.0, 1.6 , 60.0), DIRE_SOUTH     ,false },
	{ 300 , TYPE_SMALL, D3DXVECTOR3(-50.0, 1.6 , 10.0), DIRE_SOUTH     ,false },
	{ 300 , TYPE_SMALL, D3DXVECTOR3(-50.0, 1.6 , 20.0), DIRE_SOUTH     ,false },
	{ 300 , TYPE_SMALL, D3DXVECTOR3(-50.0, 1.6 , 30.0), DIRE_SOUTH     ,false },
	{ 300 , TYPE_SMALL, D3DXVECTOR3(-50.0, 1.6 , 40.0), DIRE_SOUTH     ,false },
	{ 300 , TYPE_SMALL, D3DXVECTOR3(-50.0, 1.6 , 50.0), DIRE_SOUTH     ,false },
	{ 300 , TYPE_SMALL, D3DXVECTOR3(-50.0, 1.6 , 60.0), DIRE_SOUTH     ,false },
	{ 500 , TYPE_SMALL, D3DXVECTOR3( 50.0, 1.6 ,-10.0), DIRE_SOUTH     ,false },
	{ 500 , TYPE_SMALL, D3DXVECTOR3( 50.0, 1.6 ,-20.0), DIRE_SOUTH     ,false },
	{ 500 , TYPE_SMALL, D3DXVECTOR3( 50.0, 1.6 ,-30.0), DIRE_SOUTH     ,false },
	{ 500 , TYPE_SMALL, D3DXVECTOR3( 50.0, 1.6 ,-40.0), DIRE_SOUTH     ,false },
	{ 500 , TYPE_SMALL, D3DXVECTOR3( 50.0, 1.6 ,-50.0), DIRE_SOUTH     ,false },
	{ 500 , TYPE_SMALL, D3DXVECTOR3( 50.0, 1.6 ,-60.0), DIRE_SOUTH     ,false },
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


void CEnemy::EnemyDamage(void)
{
	m_Hp--;
	if (m_Hp <= 0)
	{
		m_TimeKeep = m_FrameCount;
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


