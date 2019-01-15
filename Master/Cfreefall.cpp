//////////////////////////////////////////////////
////
////	�A�g���N�V����(�t���[�t�H�[��)�N���X
////
//////////////////////////////////////////////////

//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================

#include "Cfreefall.h"
#include "Cplayer.h"
#include "debug_font.h"
//=============================================================================
//	�萔��`
//=============================================================================
#define SPEED (0.05f)
#define SIZE (0.8f)
#define FREEFALL_HP (40)
#define FREEFALL_MP (1)
#define FREEFALL_ATK (1)
#define SCORE (1)
#define FREEFALL_SCALE (1)
//=============================================================================
//	�ÓI�ϐ�
//=============================================================================

#define FREEFALL_UP		(25.0f)
#define FREEFALL_DOWN	(0.0f)
THING_NORMAL *fall;
/*static float ugoki;//�~�Ղ̏㉺�̓���
static bool Bugoki = false;
static float moveY = 0.0f;//�~�Ղ̍��W
static int CoolTime = 0;//�N�[���^�C��*/
//=============================================================================
//	�O���[�o���ϐ�
//=============================================================================

//=============================================================================
//	����
//=============================================================================
Cfreefall::Cfreefall() :CAttraction(TYPE_FALL), C3DObj(C3DObj::TYPE_ATTRACTION)
{
	Initialize();
}

Cfreefall::~Cfreefall()
{

}

void Cfreefall::Initialize()
{
	m_AttractionIndex = Get_AttractionIndex(TYPE_ALL);

	m_Enable = true;
	Bugoki = false;
	ugoki = 0.0f;
	CoolTime = 0;
	moveY = 0.0f;
	m_Hp = FREEFALL_HP;
	m_Mp = FREEFALL_MP;
	m_Attack = FREEFALL_ATK;

	C3DObj *playerget = CPlayer::Get_Player();
	D3DXMATRIX mtx = playerget->Get_mtxWorld();
	D3DXMatrixTranslation(&m_mtxTranslation, mtx._41, mtx._42, mtx._43);//X,Y,Z��n��
	D3DXMatrixScaling(&m_mtxScaling, FREEFALL_SCALE, FREEFALL_SCALE, FREEFALL_SCALE);
	m_mtxWorld = m_mtxScaling * m_mtxTranslation;
	Thing_Normal_model = GetNormalModel(MODELL_HASIRA);
	fall = GetNormalModel(MODELL_ENBAN);
}

void Cfreefall::Update(void)
{
	if (m_Enable)
	{//�����ňړ��v�Z���s��

		D3DXMatrixScaling(&m_mtxScaling, FREEFALL_SCALE, FREEFALL_SCALE, FREEFALL_SCALE);
		D3DXMatrixRotationY(&m_mtxRotation, D3DXToRadian(0));
		m_mtxWorld = m_mtxScaling *m_mtxRotation * m_mtxTranslation;

		if (!Bugoki)
		{
			if (ugoki <= 25.0f)
			{
				ugoki += 0.1f;
			}
			if (ugoki >= 25.0f)
			{
				CoolTime++;
				if (CoolTime >= 120)
				{
					Bugoki = true;
					CoolTime = 0;
				}
			}
		}
		if (Bugoki)
		{
			if (ugoki >= 0.0f)
			{
				ugoki -= 0.5f;
			}
			if (ugoki <= 0.0f)
			{
				CoolTime++;
				if (CoolTime >= 120)
				{
					Bugoki = false;
					CoolTime = 0;
				}
			}
		}

		D3DXMatrixScaling(&m_mtxScaling, FREEFALL_SCALE, FREEFALL_SCALE, FREEFALL_SCALE);
		D3DXMatrixRotationY(&m_mtxRotation, D3DXToRadian(0));
		m_mtxWorld2 = m_mtxScaling * m_mtxRotation * m_mtxTranslation;

	}
}

void Cfreefall::Draw(void)
{
	//	DebugFont_Draw(800, 30, "ugoki = %f\n,", ugoki);
	//	DebugFont_Draw(800, 60, "Bugoki = %d\n,", Bugoki);
	if (m_Enable)
	{

		Thing_Normal_model->vPosition = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);
		fall->vPosition = D3DXVECTOR3(m_mtxWorld2._41, m_mtxWorld2._42, m_mtxWorld2._43);

		DrawDX_Normal(m_mtxWorld2, MODELL_HASIRA, Thing_Normal_model);
		DrawDX_Normal(m_mtxWorld,  MODELL_ENBAN, fall);
	}
}

void Cfreefall::Finalize(void)
{
	Attraction_Finalize(m_AttractionIndex);
}