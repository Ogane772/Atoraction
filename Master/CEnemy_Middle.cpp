//////////////////////////////////////////////////
////
////	�G�l�~�[(�X���[��)�N���X
////
//////////////////////////////////////////////////

//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================

#include "CEnemy_Middle.h"
#include "Cplayer.h"
#include "input.h"
#include "CSkinAnimation.h"
#include "debug_font.h"
#include "CTexture.h"
#include "exp.h"
//=============================================================================
//	�萔��`
//=============================================================================

#define MIDDLE_SIZE (0.8f)
#define MIDDLE_ATTACK (5)
#define MIDDLE_HP (3)
#define MIDDLE_MP (4)
#define MIDDLE_SCORE (1000)
#define FRY_HEIGHT (0.1f)
#define FRY_SPEED (0.05f)
#define WALK_SPEED (0.01f)
#define ATTACK_SPEED (0.02f)
//�G�l�~�[�X���[���̃A�j���[�V�����ԍ���`
enum ANIMATION {
	DEATH,
	ATTACK,
	WALK,
	
	
	

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

CEnemy_Middle::CEnemy_Middle(ENEMY_EMITTER *Emitter) :CEnemy(TYPE_MIDDLE), C3DObj(C3DObj::TYPE_ENEMY)
{
	Initialize(Emitter);
}

//=============================================================================
//	�j��
//=============================================================================

CEnemy_Middle::~CEnemy_Middle()
{

}

void CEnemy_Middle::Initialize(ENEMY_EMITTER *Emitter)
{
	SkinMesh.InitThing(m_pD3DDevice, &Thing, ANIME_MODEL_FILES[MODELL_ANIME_MIDDLE].filename);
	Thing.Sphere.fRadius = 1.3f;
	Thing.Sphere.vCenter = D3DXVECTOR3(0, 1.2f, 0);
	SkinMesh.InitSphere(m_pD3DDevice, &Thing);

	m_EnemyIndex = Get_EnemyIndex(TYPE_ALL);
	//���f�����擾
	//Thing_Anime_model = GetAnimeModel();
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
	m_Hp = MIDDLE_HP;
	m_Attack = MIDDLE_ATTACK;
	m_Score = MIDDLE_SCORE;
	m_Mp = MIDDLE_MP;
	m_Direction = Emitter->InitDirection;

	D3DXMatrixTranslation(&m_mtxTranslation, Emitter->InitPos.x, Emitter->InitPos.y, Emitter->InitPos.z);
	D3DXMatrixScaling(&m_mtxScaling, 1, 1, 1);
	m_mtxWorld = m_mtxScaling * m_mtxTranslation;

	Thing.vPosition = D3DXVECTOR3(m_mtxTranslation._41, m_mtxTranslation._42, m_mtxTranslation._43);
}

void CEnemy_Middle::Finalize(void)
{
	Enemy_Finalize(m_EnemyIndex);
}

void CEnemy_Middle::Update(void)
{
	if (!m_DamageFlag)
	{

		if (m_DrawCheck)	//	�͈͓��ɂ��邩
		{
			if (!PlayerCheck())	//	�߂��Ƀv���C���[�����邩
			{
				if ((!Chase_Popcorn()) && (!m_AttackCheck))
				{
					Middle_Move();
				}
				else
				{
					Middle_Attack();
				}
			}
			else
			{
				Chase_Player();

				Middle_Attack();

			}
		}
		else
		{
			Comeback_Move(MIDDLE_SPEED);

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
		Color_Change(CTexture::TEX_MIDDLE_END);
		if (!m_DrawCheck)
		{
			C3DObj_delete();
		}
	}

}



void CEnemy_Middle::Draw(void)
{

	if (m_Enable)
	{
		if (m_DrawCheck)
		{//�����蔻��ʒu�X�V
			m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);	//�@���C�e�B���O�L��
			Thing.vPosition = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);
			DrawDX_Anime(m_mtxWorld, MODELL_ANIME_MIDDLE, &Thing);
			m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);	//�@���C�e�B���O�L��
		}
	}
}


void CEnemy_Middle::Middle_Move(void)
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

		D3DXMATRIX mtxtrans;
		D3DXMatrixTranslation(&mtxtrans, m_EnemyMove[m_Direction].Move.x * MIDDLE_SPEED, m_EnemyMove[m_Direction].Move.y * MIDDLE_SPEED, m_EnemyMove[m_Direction].Move.z * MIDDLE_SPEED);
		m_mtxTranslation *= mtxtrans;

		if (m_FrameCount - m_TimeKeep >= 60 * m_Movetime)
		{
			m_MoveCheck = false;
		}
	}
}


void CEnemy_Middle::Middle_Attack(void)
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
			Color_Change(CTexture::TEX_MIDDLE_ANOTHER);
		}
		if (m_FrameCount - m_AttackTime >= 120)
		{
			if (m_FrameCount - m_AttackTime == 130)
			{
				Exp_Set(ENEMY_HIKKAI, m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43, 3.0, 0);
			}
			Animation_Change(ATTACK, ATTACK_SPEED);
		}
		if (m_FrameCount - m_AttackTime >= 130)
		{
			Color_Change(CTexture::TEX_MIDDLE);
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




