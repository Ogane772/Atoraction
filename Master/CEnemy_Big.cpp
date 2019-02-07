//////////////////////////////////////////////////
////
////	�G�l�~�[(�r�b�O)�N���X
////
//////////////////////////////////////////////////

//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================

#include "CEnemy_Big.h"
#include "Cplayer.h"
#include "input.h"
#include "CSkinAnimation.h"
#include "debug_font.h"
//=============================================================================
//	�萔��`
//=============================================================================

#define BIG_SIZE (0.8f)
#define BIG_ATTACK (15)
#define BIG_HP (10)
#define BIG_MP (60)
#define BIG_SCORE (10000)
#define FRY_HEIGHT (0.2f)
#define FRY_SPEED (0.05f)
#define WALK_SPEED (0.01f)
#define ATTACK_SPEED (0.05f)
enum ANIMATION {
	
	WALK,
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

CEnemy_Big::CEnemy_Big(ENEMY_EMITTER *Emitter) :CEnemy(TYPE_BIG), C3DObj(C3DObj::TYPE_ENEMY)
{
	Initialize(Emitter);
}

//=============================================================================
//	�j��
//=============================================================================

CEnemy_Big::~CEnemy_Big()
{

}

void CEnemy_Big::Initialize(ENEMY_EMITTER *Emitter)
{


	SkinMesh.InitThing(m_pD3DDevice, &Thing, ANIME_MODEL_FILES[MODELL_ANIME_BIG].filename);
	Thing.Sphere.fRadius = 1.3;
	Thing.Sphere.vCenter = D3DXVECTOR3(0, 1.2, 0);
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
	m_Hp = BIG_HP;
	m_Attack = BIG_ATTACK;
	m_Score = BIG_SCORE;
	m_Direction = Emitter->InitDirection;

	D3DXMatrixTranslation(&m_mtxTranslation, Emitter->InitPos.x, Emitter->InitPos.y, Emitter->InitPos.z);
	D3DXMatrixScaling(&m_mtxScaling, 1, 1, 1);
	m_mtxWorld = m_mtxScaling * m_mtxTranslation;

	Thing.vPosition = D3DXVECTOR3(m_mtxTranslation._41, m_mtxTranslation._42, m_mtxTranslation._43);
}


void CEnemy_Big::Finalize(void)
{

	Enemy_Finalize(m_EnemyIndex);

}


void CEnemy_Big::Update(void) 
{
	if (!m_DamageFlag)
	{

		if (m_DrawCheck)	//	�͈͓��ɂ��邩
		{
			if (!PlayerCheck())	//	�߂��Ƀv���C���[�����邩
			{
				Big_Move();
			}
			else
			{
				Chase_Player();

				Big_Attack();

			}
		}
		else
		{
			Comeback_Move(BIG_SPEED);

		}

	}
	else
	{
		Enemy_Damage(FRY_HEIGHT);
		Enemy_Flying(FRY_SPEED);



	}
	m_mtxWorld = m_mtxScaling * m_mtxRotation * m_mtxTranslation;
	Draw_Check();

}



void CEnemy_Big::Draw(void)
{

	if (m_Enable)
	{
		if (m_DrawCheck)
		{//�����蔻��ʒu�X�V
			m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);	//�@���C�e�B���O�L��
			Thing.vPosition = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);
			DrawDX_Anime(m_mtxWorld, MODELL_ANIME_SMALL, &Thing);
			m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);	//�@���C�e�B���O�L��
		}
	}
	C3DObj::HitCheck();
	DebugFont_Draw(500, 400, "%d", TrackDesc.Speed);
}


void CEnemy_Big::Big_Move(void)
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
		D3DXMatrixTranslation(&mtxtrans, m_EnemyMove[m_Direction].Move.x * BIG_SPEED, m_EnemyMove[m_Direction].Move.y * BIG_SPEED, m_EnemyMove[m_Direction].Move.z * BIG_SPEED);
		m_mtxTranslation *= mtxtrans;

		if (m_FrameCount - m_TimeKeep >= 60 * m_Movetime)
		{
			m_MoveCheck = false;
		}
	}
}

void CEnemy_Big::Big_Attack(void)
{
	if (!m_AttackCheck)
	{
		m_AttackTime = m_FrameCount;
		m_AttackCheck = true;

		Animation_Change(ATTACK, ATTACK_SPEED);
	}
	else
	{
		if (m_FrameCount - m_AttackTime >= 350)
		{

			m_AttackCheck = false;
			m_AttackTime = 0;
		}
	}
}




