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
#define COFFEE_SCALE (2)
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

CCoffeeCup::CCoffeeCup() :CAttraction(TYPE_COFFEE),C3DObj(C3DObj::TYPE_ATTRACTION)
{
	Initialize();
}

CCoffeeCup::~CCoffeeCup()
{

}

void CCoffeeCup::Initialize()
{
	m_AttractionIndex = Get_AttractionIndex(TYPE_ALL);

	m_Enable = true;
	
	angCup = 0.0f;//�J�b�v�̉�]
	CoolTime = 0;//�N�[���^�C��
	B_CoolTime;//�N�[���^�C���̃u�[��
	
	B_CoolTime = true;
	m_Hp = COFFEE_CUP_HP;
	m_Mp = COFFEE_CUP_MP;
	m_Attack = COFFEE_CUP_ATK;

	C3DObj *playerget = CPlayer::Get_Player();
	D3DXMATRIX mtx = playerget->Get_mtxWorld();
	D3DXMatrixTranslation(&m_mtxTranslation, mtx._41, 0, mtx._43);//X,Y,Z��n��
	D3DXMatrixScaling(&m_mtxScaling, COFFEE_SCALE, COFFEE_SCALE, COFFEE_SCALE);
	m_mtxWorld = m_mtxScaling * m_mtxTranslation;

	
}

void CCoffeeCup::Update(void)
{
	if (m_Enable)
	{//�����ŉ�]�v�Z���s��
	 //��]
		if (B_CoolTime)
		{
			angCup += 3.5f;
			
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


		D3DXMatrixTranslation(&m_mtxTranslation, m_mtxTranslation._41, -0.3, m_mtxTranslation._43);
		D3DXMatrixRotationY(&m_mtxRotation, D3DXToRadian(angCup));
		m_mtxWorld2 = m_mtxScaling* m_mtxRotation  * m_mtxTranslation;

		D3DXMatrixTranslation(&m_mtxTranslation, m_mtxTranslation._41, 0, m_mtxTranslation._43);
		D3DXMatrixRotationY(&m_mtxRotation, D3DXToRadian(0));
		m_mtxWorld = m_mtxScaling * m_mtxRotation * m_mtxTranslation;

	}
}

void CCoffeeCup::Draw(void)
{
	if (m_Enable)
	{
		Model_Draw(MODELL_CUP_TABLE, m_mtxWorld);
		Model_Draw(MODELL_CUP, m_mtxWorld2);
	}
}

void CCoffeeCup::Finalize(void)
{
	Attraction_Finalize(m_AttractionIndex);
}

void CCoffeeCup::CoffeeCup_Create(void)
{

}