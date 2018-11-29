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

CEnemy::ENEMY_MOVE CEnemy::m_EnemyMove[8] = {
	{ D3DXVECTOR3(0.0f,0.0f,1.0f),D3DXToRadian(-90.0) },
	{ D3DXVECTOR3(1.0f,0.0f,1.0f),D3DXToRadian(-45.0) },
	{ D3DXVECTOR3(1.0f,0.0f,0.0f),D3DXToRadian(0.0) },
	{ D3DXVECTOR3(1.0f,0.0f,-1.0f),D3DXToRadian(45.0) },
	{ D3DXVECTOR3(-1.0f,0.0f,-1.0f),D3DXToRadian(135.0) },
	{ D3DXVECTOR3(-1.0f,0.0f,1.0f),D3DXToRadian(-135.0) },
	{ D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DXToRadian(90.0) },
};

CEnemy::ENEMY_EMITTER CEnemy::m_EnemyEmitter[]
{
	{ 0  , TYPE_SMALL, D3DXVECTOR3(10.0, 1.6 ,10.0), DIRE_NORTH	  ,false },
	{ 0	 , TYPE_SMALL, D3DXVECTOR3(20.0, 1.6 ,20.0), DIRE_EAST	  ,false },
	{ 0, TYPE_SMALL, D3DXVECTOR3(30.0, 1.6 ,30.0), DIRE_NORTHWEST ,false },
	{ 0, TYPE_SMALL, D3DXVECTOR3(20.0, 1.6 ,10.0), DIRE_SOUTHEAST ,false },
	{ 0, TYPE_SMALL, D3DXVECTOR3(0.0,  1.6 ,0.0) , DIRE_NORTHEAST ,false },
	{ 100 , TYPE_SMALL, D3DXVECTOR3(50.0, 1.6 ,10.0), DIRE_SOUTH  ,false },
	{ 100 , TYPE_SMALL, D3DXVECTOR3(50.0, 1.6 ,20.0), DIRE_SOUTH  ,false },
	{ 100 , TYPE_SMALL, D3DXVECTOR3(50.0, 1.6 ,30.0), DIRE_SOUTH  ,false },
	{ 100 , TYPE_SMALL, D3DXVECTOR3(50.0, 1.6 ,40.0), DIRE_SOUTH  ,false },
	{ 100 , TYPE_SMALL, D3DXVECTOR3(50.0, 1.6 ,50.0), DIRE_SOUTH  ,false },
	{ 100 , TYPE_SMALL, D3DXVECTOR3(-50.0, 1.6 ,60.0), DIRE_SOUTH  ,false },
	{ 300 , TYPE_SMALL, D3DXVECTOR3(-50.0, 1.6 ,10.0), DIRE_SOUTH  ,false },
	{ 300 , TYPE_SMALL, D3DXVECTOR3(-50.0, 1.6 ,20.0), DIRE_SOUTH  ,false },
	{ 300 , TYPE_SMALL, D3DXVECTOR3(-50.0, 1.6 ,30.0), DIRE_SOUTH  ,false },
	{ 300 , TYPE_SMALL, D3DXVECTOR3(-50.0, 1.6 ,40.0), DIRE_SOUTH  ,false },
	{ 300 , TYPE_SMALL, D3DXVECTOR3(-50.0, 1.6 ,50.0), DIRE_SOUTH  ,false },
	{ 300 , TYPE_SMALL, D3DXVECTOR3(-50.0, 1.6 ,60.0), DIRE_SOUTH  ,false },
	{ 500 , TYPE_SMALL, D3DXVECTOR3(50.0, 1.6 ,-10.0), DIRE_SOUTH  ,false },
	{ 500 , TYPE_SMALL, D3DXVECTOR3(50.0, 1.6 ,-20.0), DIRE_SOUTH  ,false },
	{ 500 , TYPE_SMALL, D3DXVECTOR3(50.0, 1.6 ,-30.0), DIRE_SOUTH  ,false },
	{ 500 , TYPE_SMALL, D3DXVECTOR3(50.0, 1.6 ,-40.0), DIRE_SOUTH  ,false },
	{ 500 , TYPE_SMALL, D3DXVECTOR3(50.0, 1.6 ,-50.0), DIRE_SOUTH  ,false },
	{ 500 , TYPE_SMALL, D3DXVECTOR3(50.0, 1.6 ,-60.0), DIRE_SOUTH  ,false },
};

int CEnemy::m_ENEMY_MAX = sizeof(CEnemy_Small::m_EnemyEmitter) / sizeof(m_EnemyEmitter[0]);



CEnemy *CEnemy::m_pEnemy[sizeof(CEnemy::m_EnemyEmitter) / sizeof(m_EnemyEmitter[0])] = {};

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
	m_EnemyNum[TYPE_ALL]--;
}


CEnemy *CEnemy::Create(int Index)
{
	if (!m_EnemyEmitter[Index].CreateCheck)
	{
		if (m_FrameCount == m_EnemyEmitter[Index].CreateFrame)
		{
			if (m_EnemyEmitter[Index].Type == TYPE_SMALL)
			{
				m_pEnemy[m_EnemyNum[TYPE_ALL] - 1] = new CEnemy_Small(&m_EnemyEmitter[Index]);
				m_EnemyEmitter[Index].CreateCheck = true;
				return m_pEnemy[m_EnemyNum[TYPE_ALL] - 1];
			}
		}
	}

	return NULL;
}



void CEnemy::Enemy_Finalize(int Index)
{
	if (m_pEnemy[Index])
	{
		m_EnemyEmitter[Index].CreateCheck = false;
		delete m_pEnemy[Index];
		
		m_pEnemy[Index] = NULL;
	}
}


void CEnemy::EnemyMove(NxActor *actor, int direction, float speed)
{
	if (direction < 8)
	{
		D3DXVECTOR3 move;
		move = m_EnemyMove[direction].Move * speed;
		myData* mydata = (myData*)actor->userData;
		mydata->meshTranslation.x += move.x;
		mydata->meshTranslation.y += move.y;
		mydata->meshTranslation.z += move.z;
		actor->setGlobalPosition(mydata->meshTranslation);
	}
	
}

void CEnemy::EnemyAngleChange(NxActor *actor, int direction)
{
	if (direction < 8)
	{
		NxMat33 matR;
		matR.rotY(m_EnemyMove[direction].Angle);
		actor->setGlobalOrientation(matR);
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



