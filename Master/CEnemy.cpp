//////////////////////////////////////////////////
////
////	�G�l�~�[�N���X
////
//////////////////////////////////////////////////


//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "CEnemy.h"
#include "CEnemy_Small.h"
#include "CEnemy_Middle.h"
#include "CEnemy_Big.h"
#include "CEnemy_Special.h"
#include "Cplayer.h"
#include "common.h"
#include "CAttraction_Popcorn.h"
#include "CTexture.h"
#include "sound.h"
#include "COrnament.h"
#include "exp.h"
//=============================================================================
//	�萔��`
//=============================================================================

#define CHASE_SPEED (0.015f)
#define ENEMY_HITSTOP (30)//�q�b�g�X�g�b�v�̒���
//=============================================================================
//	�ÓI�ϐ�
//=============================================================================

//	�G�l�~�[�ړ��p�\����
CEnemy::ENEMY_MOVE CEnemy::m_EnemyMove[8] = {
	{ D3DXVECTOR3(0.0f,0.0f,1.0f),D3DXToRadian(-90.0f) },
	{ D3DXVECTOR3(1.0f,0.0f,1.0f),D3DXToRadian(-45.0f) },
	{ D3DXVECTOR3(1.0f,0.0f,0.0f),D3DXToRadian(0.0f) },
	{ D3DXVECTOR3(1.0f,0.0f,-1.0f),D3DXToRadian(45.0f) },
	{ D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DXToRadian(90.0f) },
	{ D3DXVECTOR3(-1.0f,0.0f,-1.0f),D3DXToRadian(135.0f) },
	{ D3DXVECTOR3(-1.0f,0.0f,0.0f),D3DXToRadian(180.0f) },
	{ D3DXVECTOR3(-1.0f,0.0f,1.0f),D3DXToRadian(-135.0f) },

};

//	�G�l�~�[�G�~�b�^�[
CEnemy::ENEMY_EMITTER CEnemy::m_EnemyEmitter[]
{
	/*{ 0 ,0, TYPE_SMALL,	   D3DXVECTOR3( 10.0f, 0.0f , 15.0f),D3DXVECTOR3(10.0f, 0.0f , 15.0f), DIRE_NORTH	   ,false },
	{ 0	,0, TYPE_MIDDLE,	   D3DXVECTOR3(20.0f, 0.0f , 20.0f), D3DXVECTOR3(20.0f, 0.0f , 20.0f), DIRE_EAST	   ,false },
	{ 0	,0, TYPE_SPECIAL,	   D3DXVECTOR3(30.0f, 0.0f , 30.0f), D3DXVECTOR3(30.0f, 0.0f , 30.0f), DIRE_NORTHWEST ,false },
	{ 0	,0, TYPE_BIG,		   D3DXVECTOR3(20.0f, 0.0f , 10.0f), D3DXVECTOR3(20.0f, 0.0f , 10.0f), DIRE_SOUTHEAST ,false },
	{ 0	,0, TYPE_SMALL,	   D3DXVECTOR3(0.0f , 0.0f , 0.0f)  ,D3DXVECTOR3(0.0f , 0.0f , 0.0f), DIRE_NORTHEAST ,false },
	*/
	{ 300 , TYPE_SMALL,D3DXVECTOR3(0.0f, 0.0f , 75.0f), DIRE_SOUTH,false },
	{ 300 , TYPE_SMALL,D3DXVECTOR3(0.0f, 0.0f , 75.0f), DIRE_SOUTH,false },
	{ 300 , TYPE_SMALL,D3DXVECTOR3(0.0f, 0.0f , 75.0f), DIRE_SOUTH,false },
	{ 300 , TYPE_SMALL,D3DXVECTOR3(0.0f, 0.0f , 75.0f), DIRE_SOUTH,false },
	{ 300 , TYPE_SMALL,D3DXVECTOR3(0.0f, 0.0f , 75.0f), DIRE_SOUTH,false },
	{ 300 , TYPE_SMALL,D3DXVECTOR3(75.0f, 0.0f , 15.0f), DIRE_SOUTH,false },
	{ 300 , TYPE_SMALL,D3DXVECTOR3(75.0f, 0.0f , 15.0f), DIRE_SOUTH,false },
	{ 300 , TYPE_SMALL,D3DXVECTOR3(75.0f, 0.0f , 15.0f), DIRE_SOUTH,false },
	{ 300 , TYPE_SMALL,D3DXVECTOR3(75.0f, 0.0f , 15.0f), DIRE_SOUTH,false },
	{ 300 , TYPE_SMALL,D3DXVECTOR3(75.0f, 0.0f , 15.0f), DIRE_SOUTH,false },
	{ 300 , TYPE_SMALL,D3DXVECTOR3(0.0f, 0.0f , -75.0f), DIRE_SOUTH,false },
	{ 300 , TYPE_SMALL,D3DXVECTOR3(0.0f, 0.0f , -75.0f), DIRE_SOUTH,false },
	{ 300 , TYPE_SMALL,D3DXVECTOR3(0.0f, 0.0f , -75.0f), DIRE_SOUTH,false },
	{ 300 , TYPE_SMALL,D3DXVECTOR3(0.0f, 0.0f , -75.0f), DIRE_SOUTH,false },
	{ 300 , TYPE_SMALL,D3DXVECTOR3(0.0f, 0.0f , -75.0f), DIRE_SOUTH,false },
	{ 300 , TYPE_SMALL,D3DXVECTOR3(-75.0f, 0.0f , -1.5f), DIRE_SOUTH,false },
	{ 300 , TYPE_SMALL,D3DXVECTOR3(-75.0f, 0.0f , -1.5f), DIRE_SOUTH,false },
	{ 300 , TYPE_SMALL,D3DXVECTOR3(-75.0f, 0.0f , -1.5f), DIRE_SOUTH,false },
	{ 300 , TYPE_SMALL,D3DXVECTOR3(-75.0f, 0.0f , -1.5f), DIRE_SOUTH,false },
	{ 300 , TYPE_SMALL,D3DXVECTOR3(-75.0f, 0.0f , -1.5f), DIRE_SOUTH,false },

	{ 600 , TYPE_SMALL,D3DXVECTOR3(0.0f, 0.0f , 75.0f), DIRE_SOUTH,false },
	{ 600 , TYPE_SMALL,D3DXVECTOR3(0.0f, 0.0f , 75.0f), DIRE_SOUTH,false },
	{ 600 , TYPE_SMALL,D3DXVECTOR3(0.0f, 0.0f , 75.0f), DIRE_SOUTH,false },
	{ 600 , TYPE_SMALL,D3DXVECTOR3(0.0f, 0.0f , 75.0f), DIRE_SOUTH,false },
	{ 600 , TYPE_SMALL,D3DXVECTOR3(0.0f, 0.0f , 75.0f), DIRE_SOUTH,false },
	{ 600 , TYPE_SMALL,D3DXVECTOR3(75.0f, 0.0f , 15.0f), DIRE_SOUTH,false },
	{ 600 , TYPE_SMALL,D3DXVECTOR3(75.0f, 0.0f , 15.0f), DIRE_SOUTH,false },
	{ 600 , TYPE_SMALL,D3DXVECTOR3(75.0f, 0.0f , 15.0f), DIRE_SOUTH,false },
	{ 600 , TYPE_SMALL,D3DXVECTOR3(75.0f, 0.0f , 15.0f), DIRE_SOUTH,false },
	{ 600 , TYPE_SMALL,D3DXVECTOR3(75.0f, 0.0f , 15.0f), DIRE_SOUTH,false },
	{ 600 , TYPE_SMALL,D3DXVECTOR3(0.0f, 0.0f , -75.0f), DIRE_SOUTH,false },
	{ 600 , TYPE_SMALL,D3DXVECTOR3(0.0f, 0.0f , -75.0f), DIRE_SOUTH,false },
	{ 600 , TYPE_SMALL,D3DXVECTOR3(0.0f, 0.0f , -75.0f), DIRE_SOUTH,false },
	{ 600 , TYPE_SMALL,D3DXVECTOR3(0.0f, 0.0f , -75.0f), DIRE_SOUTH,false },
	{ 600 , TYPE_SMALL,D3DXVECTOR3(0.0f, 0.0f , -75.0f), DIRE_SOUTH,false },
	{ 600 , TYPE_SMALL,D3DXVECTOR3(-75.0f, 0.0f , -1.5f), DIRE_SOUTH,false },
	{ 600 , TYPE_SMALL,D3DXVECTOR3(-75.0f, 0.0f , -1.5f), DIRE_SOUTH,false },
	{ 600 , TYPE_SMALL,D3DXVECTOR3(-75.0f, 0.0f , -1.5f), DIRE_SOUTH,false },
	{ 600 , TYPE_SMALL,D3DXVECTOR3(-75.0f, 0.0f , -1.5f), DIRE_SOUTH,false },
	{ 600 , TYPE_SMALL,D3DXVECTOR3(-75.0f, 0.0f , -1.5f), DIRE_SOUTH,false },
};

int CEnemy::m_ENEMY_MAX = sizeof(CEnemy_Small::m_EnemyEmitter) / sizeof(m_EnemyEmitter[0]);

int CEnemy::m_EnemyNum[TYPE_MAX] = {};

//=============================================================================
//	����
//=============================================================================

CEnemy::CEnemy()
{
	m_EnemyNum[TYPE_ALL]++;
}

CEnemy::CEnemy(int EnemyType)
{
	m_Type = EnemyType;
	m_EnemyIndex = m_EnemyNum[TYPE_ALL];
	//mEnemyNum[TYPE_ALL]++_;
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
//	�j��
//=============================================================================

CEnemy::~CEnemy()
{
	m_EnemyEmitter[m_EnemyIndex].CreateCheck = false;
	m_EnemyNum[TYPE_ALL]--;
	SkinMesh.cHierarchy.DestroyFrame(Thing.pFrameRoot);
	//SkinMesh.cHierarchy.DestroyMeshContainer()
}

void CEnemy::Create(void)
{
	int i;
	for (i = 0; i < m_ENEMY_MAX; i++)
	{
		if (!m_EnemyEmitter[i].CreateCheck)
		{
			//if (m_FrameCount == m_EnemyEmitter[i].CreateFrame)
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






C3DObj *CEnemy::Get_Enemy(int index)
{
	C3DObj *penemy = C3DObj::Get(index);
	if (penemy)
	{
		if (penemy->Get_3DObjType() == C3DObj::TYPE_ENEMY)
		{
			return penemy;
		}
	}
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
	float l;
	C3DObj *pplayer = CPlayer::Get_Player();
	if (m_Type == TYPE_SPECIAL)
	{
		l = 15;//�͈�
	}
	else if (m_Type == TYPE_BIG)
	{
		l = 20;//�͈�
	}
	else
	{
		l = 10;//�͈�
	}


	D3DXMATRIX playerworld = pplayer->Get_mtxWorld();
	float cc = (playerworld._41 - m_mtxWorld._41) * (playerworld._41 - m_mtxWorld._41) + (playerworld._43 - m_mtxWorld._43) *  (playerworld._43 - m_mtxWorld._43);


	return cc < (l * l);

}

bool CEnemy::PopCheck(void)
{
	float l;
	int i;
	C3DObj *ppop;
	D3DXMATRIX popworld;
	float cc;
	for (i = 0; i < MAX_GAMEOBJ; i++)
	{
		ppop = Popcorn::Get_Popcorn(i);
		if (ppop)
		{
			popworld = ppop->Get_mtxWorld();
			if (m_Type == TYPE_SPECIAL)
			{
				l = 15;//�͈�
			}
			else if (m_Type == TYPE_BIG)
			{
				l = 20;//�͈�
			}
			else
			{
				l = 10;//�͈�
			}
			cc = (popworld._41 - m_mtxWorld._41) * (popworld._41 - m_mtxWorld._41) + (popworld._43 - m_mtxWorld._43) *  (popworld._43 - m_mtxWorld._43);
			return cc < (l * l);
		}
	}
	
	return false;
}

void CEnemy::Chase_Player(void)
{
	C3DObj *pplayer = CPlayer::Get_Player();
	D3DXMATRIX playerworld = pplayer->Get_mtxWorld();
	float x = playerworld._41 - m_mtxWorld._41;
	float z = playerworld._43 - m_mtxWorld._43;

	D3DXMATRIX mtxtrans;
	D3DXMatrixTranslation(&mtxtrans, x * CHASE_SPEED, m_mtxWorld._42, z * CHASE_SPEED);
	m_mtxTranslation *= mtxtrans;

	float angle = (float)(atan2(-z, x));
	D3DXMatrixRotationY(&m_mtxRotation, angle);
}

bool CEnemy::Draw_Check(void)
{
	C3DObj *pplayer = CPlayer::Get_Player();
	//float l = SYLINDERSIZE;//�͈�
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
		if (m_DrawCheck)
		{
			PlaySound(NORMALHIT_SE);
			Exp_Set(HIT, m_mtxWorld._41, m_mtxWorld._42 + 1, m_mtxWorld._43 + 1, 4.0, 0);
			m_Hp--;
			m_EnemyFlying = true;
			m_FlyingMove = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43) - m_PosKeep;
			m_FlyingMove.y = flyinghigh;
			if (m_Hp <= 0)
			{
				Exp_Set(STAR, m_mtxWorld._41, m_mtxWorld._42 + 1, m_mtxWorld._43 + 1, 5.0, 0);
				Add_Mp(m_Mp);
				Add_Score(m_Score);
			}
		}

	}
}

void CEnemy::Enemy_Flying(float speed)
{
	if (m_EnemyFlying)
	{
		if (m_Hp > 0)
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
					m_mtxTranslation._42 = 0.0f;
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




bool CEnemy::Chase_Popcorn(void)
{
	int i;
	C3DObj *ppop;
	THING_NORMAL thingpop;
	D3DXMATRIX playerworld;
	D3DXMATRIX mtxtrans;
	float x;
	float z;
	float angle;
	for (i = 0; i < MAX_GAMEOBJ; i++)
	{
		ppop = Popcorn::Get_Popcorn(i);
		if (ppop)
		{
			if (ppop->Get_DrawCheck())
			{
				Thing.vPosition = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);
				thingpop = ppop->GetNormalModel(MODELL_POPCORN);
				thingpop.Sphere.fRadius = 15.0f;
				if (C3DObj::Collision_AnimeVSNormal(&Thing, &thingpop))
				{
					thingpop.Sphere.fRadius = 4.0f;
					if (!C3DObj::Collision_AnimeVSNormal(&Thing, &thingpop))
					{
						playerworld = ppop->Get_mtxWorld();
						x = playerworld._41 - m_mtxWorld._41;
						z = playerworld._43 - m_mtxWorld._43;

						mtxtrans;
						D3DXMatrixTranslation(&mtxtrans, x * CHASE_SPEED, 0.0f, z * CHASE_SPEED);
						m_mtxTranslation *= mtxtrans;

						angle = (float)(atan2(-z, x));
						D3DXMatrixRotationY(&m_mtxRotation, angle);

						return true;
					}
				}
				thingpop.Sphere.fRadius = 4.0f;
			}
		}
	}
	return false;
}

void CEnemy::Color_Change(int texindex)
{
	if (m_ColorType != texindex)
	{
		if (Thing.texture[0])
		{
			Thing.texture[0]->Release();
			Thing.texture[0] = NULL;


			char color[TEXTURE_FILENAME_MAX] = {};
			strcpy(color, CTexture::Texture_GetFailName(texindex));

			D3DXCreateTextureFromFile
			(
				m_pD3DDevice,
				//�؂�ւ������ԍ����w��[0]�̓e�N�X�`���̏ꏊ
				color,
				&Thing.texture[0]//�Z�b�g���������f���ԍ�
			);

			m_ColorType = texindex;
		}
	}
}

void CEnemy::Ornament_Check(void)
{
	int i;
	C3DObj *pornament;
	THING_NORMAL thingorna;
	for (i = 0; i < MAX_GAMEOBJ; i++)
	{
		pornament = COrnament::Get_Ornament(i);
		if (pornament)
		{
			if (pornament->Get_DrawCheck())
			{
				Thing.vPosition = D3DXVECTOR3(m_mtxTranslation._41, m_mtxTranslation._42, m_mtxTranslation._43);
				thingorna = pornament->GetNormalModel();
				if (C3DObj::Collision_AnimeVSNormal(&Thing, &thingorna))
				{
					if (!pornament->Get_DamageFlag())
					{
						m_mtxTranslation = m_mtxKeepTranslation;
						m_Direction++;
						if (m_Direction >= 9)
						{
							m_Direction = 0;
						}
						break;
					}
					else
					{
						DamageFlag_Change();
						Position_Keep(pornament->Get_mtxWorld());
					}
				}
			}
		}

	}
}

void CEnemy::Enable_Check(void)
{
	if (m_CreateCount == m_FrameCount)
	{
		m_Enable = true;
		m_EnemyNum[TYPE_ALL]++;
	}

}