//////////////////////////////////////////////////
////
////	�G�l�~�[(�X���[��)�N���X
////
//////////////////////////////////////////////////

//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================

#include "CEnemy_Small.h"
#include "Cplayer.h"
#include "input.h"
#include "CSkinAnimation.h"
//=============================================================================
//	�萔��`
//=============================================================================

#define SMALL_SIZE (0.8f)
#define SMALL_ATTACK (3)
#define SMALL_HP (1)
#define SMALL_MP (2)
#define SMALL_SCORE (1)
//�G�l�~�[�X���[���̃A�j���[�V�����ԍ���`
enum ANIMATION {
	STOP,
	WALK,
	DASH,
	ATTACK,
	DEATH,
};
//=============================================================================
//	�ÓI�ϐ�
//=============================================================================
static LPD3DXANIMATIONSET pAnimSet[10] = { 0 };//�I���������f����10�܂ł̃A�j���[�V�������Z�b�g
static FLOAT fAnimTime = 0.0f;//�A�j���o�ߎ���
static BOOL boPlayAnim = true;//�A�j���Đ����邩�ǂ���
static D3DXTRACK_DESC TrackDesc;//�A�j���[�V�����g���b�N�ϐ�

//=============================================================================
//	�O���[�o���ϐ�
//=============================================================================
int t;
//=============================================================================
//	����
//=============================================================================

CEnemy_Small::CEnemy_Small(ENEMY_EMITTER *Emitter):CEnemy(TYPE_SMALL),C3DObj(C3DObj::TYPE_ENEMY)
{
	Initialize(Emitter);
}

//=============================================================================
//	�j��
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
	//���f�����擾
	Thing_Anime_model = GetAnimeModel(MODELL_ANIME_SMALL);
	//�A�j���[�V�����g���b�N�𓾂�
	for (DWORD i = 0; i < Thing_Anime_model->pAnimController->GetNumAnimationSets(); i++)
	{//AnimSet�ɃA�j���[�V�������i�[
		Thing_Anime_model->pAnimController->GetAnimationSet(i, &pAnimSet[i]);
	}
	//�A�j���[�V������񏉊���
	TrackDesc.Weight = 1;
	TrackDesc.Enable = true;
	TrackDesc.Position = 0;//�A�j���[�V�����^�C�����Z�b�g
	TrackDesc.Speed = 0.001;//���[�V�����X�s�[�h
	Thing_Anime_model->pAnimController->SetTrackDesc(0, &TrackDesc);//�A�j�����Z�b�g
	Thing_Anime_model->pAnimController->SetTrackAnimationSet(0, pAnimSet[WALK]);//�����A�j���[�V�����Z�b�g
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

}


void CEnemy_Small::Finalize(void)
{
	
	Enemy_Finalize(m_EnemyIndex);
	
}


void CEnemy_Small::Update(void)
{
	if (m_Enable)
	{
		if (m_Hp > 0)
		{
			//�A�j���[�V�����؂�ւ�
			if (Keyboard_IsPress(DIK_3))
			{
				TrackDesc.Weight = 1.0;
				TrackDesc.Enable = true;
				TrackDesc.Position = 0;
				TrackDesc.Speed = 0.001;//���[�V�����X�s�[�h
				Thing_Anime_model->pAnimController->SetTrackDesc(0, &TrackDesc);
				Thing_Anime_model->pAnimController->SetTrackAnimationSet(0, pAnimSet[DEATH]);
				Thing_Anime_model->pAnimController->SetTrackEnable(1, false);//�A�j���[�V������ZOFF
			}
			if (Keyboard_IsPress(DIK_2))
			{
				TrackDesc.Weight = 1.0;
				TrackDesc.Enable = true;
				TrackDesc.Position = 0;
				TrackDesc.Speed = 0.001;//���[�V�����X�s�[�h
				Thing_Anime_model->pAnimController->SetTrackDesc(0, &TrackDesc);
				Thing_Anime_model->pAnimController->SetTrackAnimationSet(0, pAnimSet[WALK]);
				Thing_Anime_model->pAnimController->SetTrackEnable(1, false);//�A�j���[�V������ZOFF
			}
			if (Keyboard_IsPress(DIK_1))
			{
				TrackDesc.Weight = 1.0;
				TrackDesc.Enable = true;
				TrackDesc.Position = 0;
				TrackDesc.Speed = 0.001;//���[�V�����X�s�[�h
				Thing_Anime_model->pAnimController->SetTrackDesc(0, &TrackDesc);
				Thing_Anime_model->pAnimController->SetTrackAnimationSet(0, pAnimSet[ATTACK]);
				Thing_Anime_model->pAnimController->SetTrackEnable(1, false);//�A�j���[�V������ZOFF
			}
			///////////////
			if (m_DrawCheck)
			{
				if (!PlayerCheck())
				{
					if (!m_MoveCheck)
					{
						m_Direction++;
						if (m_Direction >= 9)
						{
							m_Direction = 0;
						}
						//EnemyAngleChange(NULL, m_Direction);
						D3DXMatrixRotationY(&m_mtxRotation, m_EnemyMove[m_Direction].Angle);
						m_TimeKeep = m_FrameCount;
						t = rand() % 3 + 1;
						m_MoveCheck = true;
					}
					else
					{
						//EnemyMove(NULL, m_Direction, SMALL_SPEED);
						D3DXMATRIX mtxtrans;
						D3DXMatrixTranslation(&mtxtrans, m_EnemyMove[m_Direction].Move.x * SMALL_SPEED, m_EnemyMove[m_Direction].Move.y * SMALL_SPEED, m_EnemyMove[m_Direction].Move.z * SMALL_SPEED);
						m_mtxTranslation *= mtxtrans;
						if (m_FrameCount - m_TimeKeep >= 60 * t)
						{
							m_MoveCheck = false;
						}
					}
				}
				else
				{
					C3DObj *pplayer = CPlayer::Get_Player();
					D3DXMATRIX playerworld = pplayer->Get_mtxWorld();
					float x = playerworld._41 - m_mtxWorld._41;
					float z = playerworld._43 - m_mtxWorld._43;

					D3DXMATRIX mtxtrans;
					D3DXMatrixTranslation(&mtxtrans, x * 0.015, 0.0, z * 0.015);
					m_mtxTranslation *= mtxtrans;

					float angle = atan2(-z, x);
					D3DXMatrixRotationY(&m_mtxRotation, angle);

					/*myData* mydata = (myData*)NxA_pSmall->userData;
					mydata->meshTranslation.x += x*SMALL_SPEED;
					//mydata->meshTranslation.y += move.y;
					mydata->meshTranslation.z += z*SMALL_SPEED;
					NxA_pSmall->setGlobalPosition(mydata->meshTranslation);*/
				}
			}
			else
			{
				if (m_MoveCheck)
				{
					//EnemyMove(NxA_pSmall, m_Direction, SMALL_SPEED);
					D3DXMATRIX mtxtrans;
					D3DXMatrixTranslation(&mtxtrans, m_EnemyMove[m_Direction].Move.x * SMALL_SPEED, m_EnemyMove[m_Direction].Move.y * SMALL_SPEED, m_EnemyMove[m_Direction].Move.z * SMALL_SPEED);
					m_mtxTranslation *= mtxtrans;
					
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
					//move *= SMALL_SPEED;

					D3DXMATRIX mtxtrans;
					D3DXMatrixTranslation(&m_mtxTranslation, m_mtxWorld._41 + move.x, m_mtxWorld._42, m_mtxWorld._43 + move.z);
					//m_mtxTranslation *= mtxtrans;

					
					/*myData* mydata = (myData*)NxA_pSmall->userData;
					mydata->meshTranslation.x += move.x;
					mydata->meshTranslation.y += move.y;
					mydata->meshTranslation.z += move.z;
					NxA_pSmall->setGlobalPosition(mydata->meshTranslation);*/
				}
			}
		}
		
			
	



	//	NxVec3 tr = NxA_pSmall->getGlobalPosition();
	//	D3DXMatrixTranslation(&m_mtxTranslation, tr.x, tr.y, tr.z);
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
	
	if (m_Enable)
	{
		if (m_DrawCheck)
		{//�����蔻��ʒu�X�V
			Thing_Anime_model->vPosition = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);
			DrawDX_Anime(m_mtxWorld, MODELL_ANIME_SMALL, Thing_Anime_model);
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


bool CEnemy_Small::PlayerCheck(void)
{
	C3DObj *pplayer = CPlayer::Get_Player();
	float l = 10;
	D3DXMATRIX playerworld = pplayer->Get_mtxWorld();
	float cc = (playerworld._41 - m_mtxWorld._41) * (playerworld._41 - m_mtxWorld._41) + (playerworld._43 - m_mtxWorld._43) *  (playerworld._43 - m_mtxWorld._43);


	return cc < (l * l);

}






