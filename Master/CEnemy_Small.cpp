//////////////////////////////////////////////////
////
////	エネミー(スモール)クラス
////
//////////////////////////////////////////////////

//=============================================================================
//	インクルードファイル
//=============================================================================

#include "CEnemy_Small.h"
#include "Cplayer.h"
#include "input.h"
//=============================================================================
//	定数定義
//=============================================================================

#define SMALL_SIZE (0.8f)
#define SMALL_ATTACK (3)
#define SMALL_HP (1)
#define SMALL_MP (2)
#define SMALL_SCORE (1)
//=============================================================================
//	静的変数
//=============================================================================



//=============================================================================
//	グローバル変数
//=============================================================================
int t;
//=============================================================================
//	生成
//=============================================================================

CEnemy_Small::CEnemy_Small(ENEMY_EMITTER *Emitter):CEnemy(TYPE_SMALL)
{
	Initialize(Emitter);
}

//=============================================================================
//	破棄
//=============================================================================

CEnemy_Small::~CEnemy_Small()
{

}


void CEnemy_Small::EnemySmall_Create(void)
{

}

void CEnemy_Small::Initialize(ENEMY_EMITTER *Emitter)
{
	m_EnemyIndex = Get_EnemyIndex(TYPE_ALL);

	m_Enable = true;
	m_MoveCheck = false;
	m_DrawCheck = true;
	m_Hp = SMALL_HP;
	m_Attack = SMALL_ATTACK;
	m_Score = SMALL_SCORE;
	m_Direction = Emitter->InitDirection;
	
	D3DXMatrixTranslation(&m_mtxTranslation, Emitter->InitPos.x, Emitter->InitPos.y, Emitter->InitPos.z);
	D3DXMatrixScaling(&m_mtxScaling, 1, 1, 1);
	m_mtxWorld = m_mtxScaling * m_mtxTranslation;

	NxMat33 mat1;
	//mat1.rotZ(0);
	NxVec3 scaleDwarf = NxVec3(1, 1, 1);	//	モデルスケール
	NxVec3 BBDwarf = NxVec3(1.0f, 1.5f, 1.5f);	//	当たり判定の大きさ

	
	NxA_pSmall = CreateMeshAsSphere(NxVec3(Emitter->InitPos.x, Emitter->InitPos.y, Emitter->InitPos.z), 1.7, MODELL_SMALL);
	
}


void CEnemy_Small::Finalize(void)
{
	
	Enemy_Finalize(m_EnemyIndex);
	
	/*USERDATA* pUserData = (USERDATA*)NxA_pSmall->userData;
	pUserData->ContactPairFlag = 0;*/
	NxA_pSmall = NULL;
	
}


void CEnemy_Small::Update(void)
{
	if (m_Enable)
	{
		if (m_Hp > 0)
		{
			
			if (m_DrawCheck)
			{
				if (!m_MoveCheck)
				{
					
					m_Direction++;
					if (m_Direction >= 10)
					{
						m_Direction = 0;
					}
					EnemyAngleChange(NxA_pSmall, m_Direction);
					D3DXMatrixRotationY(&m_mtxRotation, m_EnemyMove[m_Direction].Angle);
					m_TimeKeep = m_FrameCount;
					t = rand() % 3 + 1;
					m_MoveCheck = true;
				}
				else
				{
					EnemyMove(NxA_pSmall, m_Direction, SMALL_SPEED);
					if (m_FrameCount - m_TimeKeep >= 60 *t)
					{
						m_MoveCheck = false;
					}
				}
			}
			else
			{
				if (m_MoveCheck)
				{
					EnemyMove(NxA_pSmall, m_Direction, SMALL_SPEED);
					if (m_FrameCount - m_TimeKeep >= 180)
					{
						m_MoveCheck = false;
						m_Direction += 2;
					}
				}
				else
				{
					float angle = atan2(-m_mtxWorld._43, -m_mtxWorld._41);
					D3DXMatrixRotationY(&m_mtxRotation, angle);
					D3DXVECTOR3 move = D3DXVECTOR3(cos(angle), 0, sin(angle));
					move *= SMALL_SPEED;
					myData* mydata = (myData*)NxA_pSmall->userData;
					mydata->meshTranslation.x += move.x;
					mydata->meshTranslation.y += move.y;
					mydata->meshTranslation.z += move.z;
					NxA_pSmall->setGlobalPosition(mydata->meshTranslation);
				}
			}
		}
		
			
	



		NxVec3 tr = NxA_pSmall->getGlobalPosition();
		D3DXMatrixTranslation(&m_mtxTranslation, tr.x, tr.y, tr.z);
		m_mtxWorld = m_mtxScaling * m_mtxRotation * m_mtxTranslation;
		
		


		if (45.0*45.0 < (m_mtxWorld._41*m_mtxWorld._41) + (m_mtxWorld._43 * m_mtxWorld._43))
		{
			if (m_Hp <= 0)
			{
				m_Enable = false;
				CPlayer::m_delete = true;

			}
			else
			{
				m_DrawCheck = false;
			}
			
		}
		else
		{

			m_DrawCheck = true;
		}
	}
}



void CEnemy_Small::Draw(void)
{
	if (Get_Enemy(m_EnemyIndex))
	{
		if (m_Enable)
		{
			if (m_DrawCheck)
			{
				DrawDX2(m_mtxWorld, NxA_pSmall, MODELL_SMALL);
			}
		}
	}
}


void CEnemy_Small::Damage(void)
{
	
	if (m_Hp > 0)
	{
		m_Hp -= 1;
		if (m_Hp == 0)
		{
			CPlayer::Add_KoCount();
		}
	}
	
	
}









