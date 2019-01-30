//////////////////////////////////////////////////
////
////	�A�g���N�V����(�R�[�q�[�J�b�v)�N���X
////
//////////////////////////////////////////////////

//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================

#include "Ccoffee_cup.h"
#include "Cplayer.h"
#include "debug_font.h"
//=============================================================================
//	�萔��`
//=============================================================================
#define SPEED (0.05f)
#define COFFEE_SIZE (4)
#define COFFEE_CUP_HP (40)
#define COFFEE_CUP_MP (1)
#define COFFEE_CUP_ATK (1)
#define SCORE (1)
#define COFFEE_SCALE (1)
#define COFFEE_TABLE_SCALE (3)
//=============================================================================
//	�ÓI�ϐ�
//=============================================================================
//	�����o�ϐ��ɂ���@�J�E���g��m_FrameCount�łƂ�@CEnemySmall�Q�l�ɂ���

//=============================================================================
//	�O���[�o���ϐ�
//=============================================================================
THING_NORMAL *thing_cup2, *thing_cup3, *thing_cup4;
//=============================================================================
//	����
//=============================================================================

CCoffeeCup::CCoffeeCup(D3DXMATRIX mtxWorld) :CAttraction(AT_COFFEE), C3DObj(AT_COFFEE)
{
	Initialize(mtxWorld);
}

CCoffeeCup::~CCoffeeCup()
{

}

void CCoffeeCup::Initialize(D3DXMATRIX mtxWorld)
{
	m_AttractionIndex = Get_AttractionIndex(AT_ALL);

	m_Enable = true;

	angCup = 0.0f;//�J�b�v�̉�]
	CoolTime = 0;//�N�[���^�C��
	B_CoolTime;//�N�[���^�C���̃u�[��

	B_CoolTime = true;
	m_Hp = COFFEE_CUP_HP;
	m_Mp = COFFEE_CUP_MP;
	m_Attack = COFFEE_CUP_ATK;
	//�R�[�q�[�J�b�v�e�[�u���̂݃u�����_�[�ő傫����ς��邱��
	C3DObj *playerget = CPlayer::Get_Player();
	D3DXMATRIX mtx = playerget->Get_mtxWorld();
	D3DXMatrixTranslation(&m_mtxTranslation, mtxWorld._41, 0, mtxWorld._43);//X,Y,Z��n��
	D3DXMatrixScaling(&m_mtxScaling, COFFEE_SCALE, COFFEE_SCALE, COFFEE_SCALE);
	m_mtxWorld = m_mtxScaling * m_mtxTranslation;

	Thing_Normal_model = GetNormalModel(MODELL_CUP_BLUE);
	thing_cup2 = GetNormalModel(MODELL_CUP_YELLOW);
	thing_cup3 = GetNormalModel(MODELL_CUP_GREEN);
	thing_cup4 = GetNormalModel(MODELL_CUP_TABLE);
}

void CCoffeeCup::Update(void)
{

	if (m_Enable)
	{//�����ŉ�]�v�Z���s��
	 //��]
		if (B_CoolTime)
		{
			angCup += 1.0f;

			if (angCup>355.0f)
			{
				B_CoolTime = false;
				angCup = 0.0f;

			}
		}

		if (!B_CoolTime)
		{
			CoolTime++;
		}
		//5�b��������
		if (CoolTime > 100)
		{
			B_CoolTime = true;
			CoolTime = 0;
		}
		D3DXMatrixTranslation(&m_mtxTranslation, m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);
		D3DXMatrixRotationY(&m_mtxRotation, D3DXToRadian(angCup));
		m_mtxWorld = m_mtxScaling* m_mtxRotation  * m_mtxTranslation;

		D3DXMatrixTranslation(&m_mtxTranslation, -1.5, -0.5, -1);
		D3DXMatrixRotationY(&m_mtxRotation, D3DXToRadian(angCup));
		m_mtxWorld2 = m_mtxScaling * m_mtxRotation  * m_mtxTranslation;

		D3DXMatrixTranslation(&m_mtxTranslation, 0, -0.5, 1.5);

		D3DXMatrixRotationY(&m_mtxRotation, D3DXToRadian(angCup));
		m_mtxWorld3 = m_mtxScaling* m_mtxRotation  * m_mtxTranslation;


		D3DXMatrixTranslation(&m_mtxTranslation, 1.5, -0.5, -1);

		D3DXMatrixRotationY(&m_mtxRotation, D3DXToRadian(angCup));
		m_mtxWorld4 = m_mtxScaling* m_mtxRotation  * m_mtxTranslation;



		D3DXMatrixMultiply(&m_mtxWorld2, &m_mtxWorld2, &m_mtxWorld);

		D3DXMatrixMultiply(&m_mtxWorld3, &m_mtxWorld3, &m_mtxWorld);

		D3DXMatrixMultiply(&m_mtxWorld4, &m_mtxWorld4, &m_mtxWorld);

	}
}

void CCoffeeCup::Draw(void)
{
	//DebugFont_Draw(600, 30, "Dodai = %f\n,", angCup);
	//DebugFont_Draw(600, 60, "CoolTime = %d\n,", CoolTime);
	if (m_Enable)
	{

		Thing_Normal_model->vPosition = D3DXVECTOR3(m_mtxWorld2._41, m_mtxWorld2._42, m_mtxWorld2._43);
		thing_cup2->vPosition = D3DXVECTOR3(m_mtxWorld3._41, m_mtxWorld3._42, m_mtxWorld3._43);
		thing_cup3->vPosition = D3DXVECTOR3(m_mtxWorld4._41, m_mtxWorld4._42, m_mtxWorld4._43);
		thing_cup4->vPosition = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);

		DrawDX_Normal(m_mtxWorld, MODELL_CUP_TABLE, thing_cup4);

		DrawDX_Normal(m_mtxWorld2,  MODELL_CUP_BLUE, Thing_Normal_model);

		DrawDX_Normal(m_mtxWorld3, MODELL_CUP_YELLOW, thing_cup2);

		DrawDX_Normal(m_mtxWorld4, MODELL_CUP_GREEN, thing_cup3);
		
	}
}

void CCoffeeCup::Finalize(void)
{
	Attraction_Finalize(m_AttractionIndex);
}

void CCoffeeCup::CoffeeCup_Create(void)
{

}