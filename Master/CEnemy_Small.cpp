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
#include "debug_font.h"
#include "CTexture.h"
#include "exp.h"
//=============================================================================
//	�萔��`
//=============================================================================

#define SMALL_SPEED (0.05f)
#define SMALL_SIZE (0.8f)
#define SMALL_ATTACK (3)
#define SMALL_HP (1)
#define SMALL_MP (2)
#define SMALL_SCORE (100)
#define FRY_HEIGHT (0.5f)	//	��ԍ���
#define FRY_SPEED (0.05f)	//	��ԑ���
//	�A�j���[�V�����X�s�[�h
#define WALK_SPEED (0.01f)
#define ATTACK_SPEED (0.02f)
//�G�l�~�[�X���[���̃A�j���[�V�����ԍ���`
enum ANIMATION {
	STOP,
	WALK,
	DASH,
	ATTACK,
	DEATH,

	ANIME_MAX
};
//=============================================================================
//	�ÓI�ϐ�
//=============================================================================


//=============================================================================
//	�O���[�o���ϐ�
//=============================================================================

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


//=============================================================================
//	������
//=============================================================================

void CEnemy_Small::Initialize(ENEMY_EMITTER *Emitter)
{


	SkinMesh.InitThing(m_pD3DDevice, &Thing, ANIME_MODEL_FILES[MODELL_ANIME_SMALL].filename);
	Thing.Sphere.fRadius = 1.3f;
	Thing.Sphere.vCenter = D3DXVECTOR3(0, 1.2f, 0);
	SkinMesh.InitSphere(m_pD3DDevice, &Thing);

	//Thing = GetAnimeModel(MODELL_ANIME_SMALL);
	//Thing.Sphere.fRadius = 1.3f;
	//Thing.Sphere.vCenter = D3DXVECTOR3(0, 1.2f, 0);

	m_EnemyIndex = Get_EnemyIndex(TYPE_ALL);
	//���f�����擾
	//�A�j���[�V�����g���b�N�𓾂�
	for (DWORD i = 0; i < Thing.pAnimController->GetNumAnimationSets(); i++)
	{//AnimSet�ɃA�j���[�V�������i�[
		Thing.pAnimController->GetAnimationSet(i, &pAnimSet[i]);
	}

	
	//�A�j���[�V������񏉊���
	TrackDesc.Weight = 1;
	TrackDesc.Enable = true;
	TrackDesc.Position = 0;//�A�j���[�V�����^�C�����Z�b�g
	TrackDesc.Speed = WALK_SPEED;//���[�V�����X�s�[�h
	Thing.pAnimController->SetTrackDesc(0, &TrackDesc);//�A�j�����Z�b�g
	Thing.pAnimController->SetTrackAnimationSet(0, pAnimSet[WALK]);//�����A�j���[�V�����Z�b�g
	m_Enable = true;
	m_MoveCheck = false;
	m_DrawCheck = true;
	m_Hp = SMALL_HP;
	m_Attack = SMALL_ATTACK;
	m_Score = SMALL_SCORE;
	m_Mp = SMALL_MP;
	m_Direction = Emitter->InitDirection;
	
	D3DXMatrixTranslation(&m_mtxTranslation, Emitter->InitPos.x, Emitter->InitPos.y, Emitter->InitPos.z);
	D3DXMatrixScaling(&m_mtxScaling, 1, 1, 1);
	m_mtxWorld = m_mtxScaling * m_mtxTranslation;
	m_mtxKeepTranslation = m_mtxTranslation;
	Thing.vPosition = D3DXVECTOR3(m_mtxTranslation._41, m_mtxTranslation._42, m_mtxTranslation._43);
}

//=============================================================================
//	�I������
//=============================================================================
void CEnemy_Small::Finalize(void)
{
	
	Enemy_Finalize(m_EnemyIndex);
	
}

//=============================================================================
//	�X�V����
//=============================================================================
void CEnemy_Small::Update(void)
{
	if (!m_DamageFlag)
	{

		if (m_DrawCheck)	//	�͈͓��ɂ��邩
		{
			if (!PlayerCheck())	//	�߂��Ƀv���C���[�����邩
			{
				if ((!Chase_Popcorn()) && (!m_AttackCheck))
				{
					//Small_Move();
				}
				else
				{
					Small_Attack();
				}
			}
			else
			{
				Chase_Player();

				Small_Attack();

			}
		}
		else
		{
			Comeback_Move(SMALL_SPEED);
			
		}

	}
	else
	{
		Enemy_Damage(FRY_HEIGHT);
		Enemy_Flying(FRY_SPEED);



	}

	Ornament_Check();

	m_mtxWorld = m_mtxScaling * m_mtxRotation * m_mtxTranslation;
	m_mtxKeepTranslation = m_mtxTranslation;
	
	Draw_Check();

	if (m_Hp <= 0)
	{
		Color_Change(CTexture::TEX_SMALL_END);
		if (!m_DrawCheck)
		{
			C3DObj_delete();
		}
	}
}

	



//=============================================================================
//	�`�揈��
//=============================================================================
void CEnemy_Small::Draw(void)
{
	
	if (m_Enable)
	{
		if (m_DrawCheck)
		{//�����蔻��ʒu�X�V
			m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);	//�@���C�e�B���O�L��
			
			Thing.vPosition = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);
			DrawDX_Anime(m_mtxWorld, MODELL_ANIME_SMALL, &Thing);
			m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);	//�@���C�e�B���O�L��

			if (m_AttackCheck)
			{
				DebugFont_Draw(300, 500, "%d",m_FrameCount - m_AttackTime);
			}
		}
	}
}


//=============================================================================
//	�ړ�����
//=============================================================================
void CEnemy_Small::Small_Move(void)
{
	if (!m_MoveCheck)
	{
		m_Direction++;
		if (m_Direction >= 9)
		{
			m_Direction = 0;
		}
		
		Animation_Change(WALK, WALK_SPEED);
		D3DXMatrixRotationY(&m_mtxRotation, m_EnemyMove[m_Direction].Angle);
		m_TimeKeep = m_FrameCount;
		m_Movetime = rand() % 3 + 1;
		m_MoveCheck = true;
	}
	else
	{
		Color_Change(CTexture::TEX_SMALL);
		D3DXMATRIX mtxtrans;
		D3DXMatrixTranslation(&mtxtrans, m_EnemyMove[m_Direction].Move.x * SMALL_SPEED, m_EnemyMove[m_Direction].Move.y * SMALL_SPEED, m_EnemyMove[m_Direction].Move.z * SMALL_SPEED);
		m_mtxTranslation *= mtxtrans;

		if (m_FrameCount - m_TimeKeep >= 60 * m_Movetime)
		{
			m_MoveCheck = false;
		}
	}
}

//=============================================================================
//	�U������
//=============================================================================
void CEnemy_Small::Small_Attack(void)
{
	if (!m_AttackCheck)
	{
		m_AttackTime = m_FrameCount;
		m_AttackCheck = true;
		
		
	}
	else
	{
		if (m_FrameCount - m_AttackTime >= 60)
		{
			Color_Change(CTexture::TEX_SMALL_ANOTHER);
		}
		if (m_FrameCount - m_AttackTime >= 120)
		{
			if (m_FrameCount - m_AttackTime == 130)
			{
				//Exp_Set(ENEMY_HIKKAI, m_mtxTranslation._41, m_mtxTranslation._42, m_mtxTranslation._43, 1.0, 0);
			}
			Animation_Change(ATTACK, ATTACK_SPEED);
		}
		if (m_FrameCount - m_AttackTime >= 140)
		{
			Color_Change(CTexture::TEX_SMALL);
			m_AttakFlag = true;
		}
		if (m_FrameCount - m_AttackTime >= 160)
		{
			Animation_Change(WALK, WALK_SPEED);
			m_AttackCheck = false;
			m_AttackTime = 0;
			m_AttakFlag = false;
		}
	
	}
}
