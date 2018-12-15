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
#include "Cphysx.h"
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

	NxMat33 mat1;
	mat1.rotZ(0);
	NxVec3 scaleDwarf = NxVec3(COFFEE_SCALE, COFFEE_SCALE, COFFEE_SCALE);	//	���f���X�P�[��
	NxVec3 scaleDwarf2 = NxVec3(COFFEE_TABLE_SCALE, COFFEE_TABLE_SCALE, COFFEE_TABLE_SCALE);	//	���f���X�P�[��
	NxVec3 BBDwarf = NxVec3(0.7, 1.0, 0.7);	//	�����蔻��̑傫��
	NxVec3 BBDwarf2 = NxVec3(0, 0, 0);
	//NxA_pCoffee = CreateMeshAsBox(NxVec3(mtx._41, 0, mtx._43), mat1, scaleDwarf, BBDwarf, MODELL_CUP, false);

	NxA_pCoffeeBlue = CreateMeshAsBox(NxVec3(mtx._41 , 0, mtx._43), mat1, scaleDwarf, BBDwarf, MODELL_CUP_BLUE, false);
	NxA_pCoffeeYellow = CreateMeshAsBox(NxVec3(mtx._41, 0, mtx._43), mat1, scaleDwarf, BBDwarf, MODELL_CUP_YELLOW, false);
	NxA_pCoffeeGreen = CreateMeshAsBox(NxVec3(mtx._41, 0, mtx._43), mat1, scaleDwarf, BBDwarf, MODELL_CUP_GREEN, false);

	NxA_pCoffeeTable = CreateMeshAsBox(NxVec3(mtx._41, 0, mtx._43), mat1, scaleDwarf2, BBDwarf2, MODELL_CUP_TABLE, false);

	m_SphereCollision = {
		D3DXVECTOR3(m_mtxTranslation._41,m_mtxTranslation._42,m_mtxTranslation._43),COFFEE_SIZE
	};
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
		
		NxVec3 tr4 = NxA_pCoffeeTable->getGlobalPosition();
		D3DXMatrixTranslation(&m_mtxTranslation, tr4.x, 0.0, tr4.z);
		D3DXMatrixRotationY(&m_mtxRotation, D3DXToRadian(angCup));
		m_mtxWorld = m_mtxScaling* m_mtxRotation  * m_mtxTranslation;

		NxVec3 tr = NxA_pCoffeeBlue->getGlobalPosition();
		D3DXMatrixTranslation(&m_mtxTranslation, -1.5, -0.5, -1);


		D3DXMatrixRotationY(&m_mtxRotation, D3DXToRadian(angCup));
		m_mtxWorld2 = m_mtxScaling * m_mtxRotation  * m_mtxTranslation;
		
		

		NxVec3 tr1 = NxA_pCoffeeYellow->getGlobalPosition();
		D3DXMatrixTranslation(&m_mtxTranslation, 0, -0.5, 1.5);

		D3DXMatrixRotationY(&m_mtxRotation, D3DXToRadian(angCup));
		m_mtxWorld3 = m_mtxScaling* m_mtxRotation  * m_mtxTranslation;


		NxVec3 tr2 = NxA_pCoffeeGreen->getGlobalPosition();
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

		DrawDX2(m_mtxWorld, NxA_pCoffeeTable, MODELL_CUP_TABLE);
		
		DrawDX2(m_mtxWorld2, NxA_pCoffeeBlue, MODELL_CUP_BLUE);
		
		DrawDX2(m_mtxWorld3, NxA_pCoffeeYellow, MODELL_CUP_YELLOW);

		DrawDX2(m_mtxWorld4, NxA_pCoffeeGreen, MODELL_CUP_GREEN);
		

		
	//	Debug_Collision(m_SphereCollision, m_mtxTranslation);
		
	}
}

void CCoffeeCup::Finalize(void)
{
	Attraction_Finalize(m_AttractionIndex);
	NxA_pCoffee = NULL;
	NxA_pCoffeeTable = NULL;
}

void CCoffeeCup::CoffeeCup_Create(void)
{

}