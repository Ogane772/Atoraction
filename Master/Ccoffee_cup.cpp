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
#define SIZE (0.8f)
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

CCoffeeCup::CCoffeeCup() :CAttraction(TYPE_COFFEE)
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
	angDodai = 0.0f;//�M(�y��)�̉�]
	angCup = 0.0f;//�J�b�v�̉�]
	CoolTime = 0;//�N�[���^�C��
	B_CoolTime;//�N�[���^�C���̃u�[��
	angCupCount = 0.0f;//�J�b�v�̉�]�̃J�E���g
	B_CoolTime = true;
	hp = COFFEE_CUP_HP;
	mp = COFFEE_CUP_MP;
	atk = COFFEE_CUP_ATK;
	CPlayer *playerget = CPlayer::Get_Player(0);
	D3DXMATRIX mtx = playerget->Get_mtxWorld();
	D3DXMatrixTranslation(&m_mtxTranslation, mtx._41, 0, mtx._43);//X,Y,Z��n��
	D3DXMatrixScaling(&m_mtxScaling, COFFEE_SCALE, COFFEE_SCALE, COFFEE_SCALE);
	m_mtxWorld = m_mtxScaling * m_mtxTranslation;

	NxMat33 mat1;
	mat1.rotZ(0);
	NxVec3 scaleDwarf = NxVec3(COFFEE_SCALE, COFFEE_SCALE, COFFEE_SCALE);	//	���f���X�P�[��
	NxVec3 BBDwarf = NxVec3(0.7, 1.0, 0.7);	//	�����蔻��̑傫��
	NxVec3 BBDwarf2 = NxVec3(0, 0, 0);
	NxA_pCoffee = CreateMeshAsBox(NxVec3(mtx._41, 0, mtx._43), mat1, scaleDwarf, BBDwarf, MODELL_CUP, false);
	NxA_pCoffeeTable = CreateMeshAsBox(NxVec3(mtx._41, 0, mtx._43), mat1, scaleDwarf, BBDwarf2, MODELL_CUP_TABLE, false);


}

void CCoffeeCup::Update(void)
{
	int x;
	if (m_Enable)
	{//�����ŉ�]�v�Z���s��
	 //��]
		if (B_CoolTime)
		{
			angCup += 3.5f;
			//angCupCount += 3.5f;
			if (angCup>355.0f)
			{
				B_CoolTime = false;
				angCup = 0.0f;
				//angCupCount = 0.0f;
			}
		}
		if (!B_CoolTime)
		{
			CoolTime++;
			x = 0.1;
		}
		//5�b��������
		if (CoolTime > 100)
		{
			B_CoolTime = true;
			CoolTime = 0;
			x = 0.0;
		}


		NxVec3 tr2 = NxA_pCoffeeTable->getGlobalPosition();
		//D3DXMatrixTranslation(&m_mtxTranslation, tr2.x,0, tr2.z);
		//D3DXMatrixScaling(&m_mtxScaling, COFFEE_SCALE, COFFEE_SCALE, COFFEE_SCALE);
		D3DXMatrixRotationY(&m_mtxRotation, D3DXToRadian(0));
		m_mtxWorld = m_mtxScaling * m_mtxRotation * m_mtxTranslation;

		NxVec3 tr = NxA_pCoffee->getGlobalPosition();
		//D3DXMatrixTranslation(&m_mtxTranslation, tr2.x, 0, tr2.z);
		//D3DXMatrixScaling(&m_mtxScaling, COFFEE_SCALE, COFFEE_SCALE, COFFEE_SCALE);
		D3DXMatrixRotationY(&m_mtxRotation, D3DXToRadian(angCup));
		m_mtxWorld2 = m_mtxScaling* m_mtxRotation  * m_mtxTranslation;

		/*myData* mydata = (myData*)NxA_pCoffee->userData;
		D3DXMATRIX mtx = m_mtxWorld2;

		mydata->meshTranslation.x = mtx._41;
		mydata->meshTranslation.y = mtx._42;
		mydata->meshTranslation.z = mtx._43;
		NxA_pCoffee->setGlobalPosition(mydata->meshTranslation);*/
	}
}

void CCoffeeCup::Draw(void)
{
	DebugFont_Draw(600, 30, "Dodai = %f\n,", angCup);
	DebugFont_Draw(600, 60, "CoolTime = %d\n,", CoolTime);
	if (m_Enable)
	{
		DrawDX2(m_mtxWorld2, NxA_pCoffee, MODELL_CUP);
		DrawDX2(m_mtxWorld, NxA_pCoffeeTable, MODELL_CUP_TABLE);
		//DrawDirectXMesh(NxA_pSmall);
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