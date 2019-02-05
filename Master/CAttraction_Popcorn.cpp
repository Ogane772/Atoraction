//////////////////////////////////////////////////
////
////	�A�g���N�V����(�|�b�v�R�[��)�N���X
////
//////////////////////////////////////////////////

//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================

#include "CAttraction_Popcorn.h"
#include "Cplayer.h"
#include "debug_font.h"
//=============================================================================
//	�萔��`
//=============================================================================
#define SPEED (0.05f)
#define POPCORN_SIZE (4)//�����蔻��傫��
#define POPCORN_SCALE (1) //���f���̑傫��
#define POPCORN_HP (40)
#define POPCORN_MP (1)
#define POPCORN_ATK (1)
#define SCORE (1)
#define POPCORN_HEAL (1)
#define POPCORN_EREA (10)
//=============================================================================
//	�ÓI�ϐ�
//=============================================================================
//	�����o�ϐ��ɂ���@�J�E���g��m_FrameCount�łƂ�@CEnemySmall�Q�l�ɂ���

//=============================================================================
//	�O���[�o���ϐ�
//=============================================================================

//=============================================================================
//	����
//=============================================================================

Popcorn::Popcorn(D3DXMATRIX mtxWorld) :CAttraction(AT_POPCORN), C3DObj(AT_POPCORN)
{
	Initialize(mtxWorld);
}

Popcorn::~Popcorn()
{//�͈͓��ɂ�����v���C���[��
	if (m_Enable)
	{
		C3DObj *playerget = CPlayer::Get_Player();
		if (PlayerCheck())
		{
			if (m_FrameCount % 60 == 0)
			{
				int hp = playerget->Get_Hp();
				hp++;
				if (hp > HP_MAX)
				{
					hp = HP_MAX;
				}
			}
		}
	}
}

void Popcorn::Initialize(D3DXMATRIX mtxWorld)
{
	m_AttractionIndex = Get_AttractionIndex(AT_ALL);

	m_Enable = true;

	CoolTime = 0;//�N�[���^�C��
	B_CoolTime;//�N�[���^�C���̃u�[��

	B_CoolTime = true;
	m_Hp = POPCORN_HP;
	m_Mp = POPCORN_MP;
	m_Attack = POPCORN_ATK;

	C3DObj *playerget = CPlayer::Get_Player();
	D3DXMATRIX mtx = playerget->Get_mtxWorld();
	D3DXMatrixTranslation(&m_mtxTranslation, mtxWorld._41, 0, mtxWorld._43);//X,Y,Z��n��
	D3DXMatrixScaling(&m_mtxScaling, POPCORN_SCALE, POPCORN_SCALE, POPCORN_SCALE);
	m_mtxWorld = m_mtxScaling * m_mtxTranslation;


	Thing_Normal_model = GetNormalModel(MODELL_POPCORN);
	InitSphere(m_pD3DDevice, Thing_Normal_model, D3DXVECTOR3(0, 0.0, 0),4.0f);//�����蔻��̕ύX
	Thing_Normal_model->vPosition = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);
}

void Popcorn::Update(void)
{
	if (m_Enable)
	{
		//�G�t�F�N�g�������s��
	}
}

void Popcorn::Draw(void)
{
	//DebugFont_Draw(600, 30, "Dodai = %f\n,", angCup);
	//DebugFont_Draw(600, 60, "CoolTime = %d\n,", CoolTime);
	if (m_Enable)
	{

		Thing_Normal_model->vPosition = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);
		m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		DrawDX_Normal(m_mtxWorld, MODELL_POPCORN, Thing_Normal_model);
	}
}

void Popcorn::Finalize(void)
{
	Attraction_Finalize(m_AttractionIndex);
}

bool Popcorn::PlayerCheck(void)
{
	C3DObj *pplayer = CPlayer::Get_Player();
	float l = POPCORN_EREA;//�͈�
	D3DXMATRIX playerworld = pplayer->Get_mtxWorld();
	float cc = (playerworld._41 - m_mtxWorld._41) * (playerworld._41 - m_mtxWorld._41) + (playerworld._43 - m_mtxWorld._43) *  (playerworld._43 - m_mtxWorld._43);


	return cc < (l * l);

}