//////////////////////////////////////////////////
////
////	�A�g���N�V����(�ϗ���)�N���X
////
//////////////////////////////////////////////////

//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================

#include "Cwheel.h"
#include "Cplayer.h"
#include "Cphysx.h"
#include "debug_font.h"
//=============================================================================
//	�萔��`
//=============================================================================
#define SPEED (0.05f)
#define SIZE (0.8f)
#define WHEEL_HP (40)
#define WHEEL_MP (1)
#define WHEEL_ATK (1)
#define SCORE (1)
#define WHEEL_SCALE (2)
//=============================================================================
//	�ÓI�ϐ�
//=============================================================================
static bool ferris_flg;				 //�ړ��ƕǌ��˂̃`�F���W
static int ferris_counter;				 //�ϗ��Ԓ�~
static float rotate_ferris;			//�ϗ��Ԃ̊p�x
//=============================================================================
//	�O���[�o���ϐ�
//=============================================================================

//=============================================================================
//	����
//===========
Cwheel::Cwheel() :CAttraction(TYPE_WHEEL)
{
	Initialize();
}

Cwheel::~Cwheel()
{

}

void Cwheel::Initialize()
{
	m_AttractionIndex = Get_AttractionIndex(TYPE_ALL);

	m_Enable = true;
	ferris_flg = true;
	ferris_counter = 0;
	hp = WHEEL_HP;
	mp = WHEEL_MP;
	atk = WHEEL_ATK;
	CPlayer *playerget = CPlayer::Get_Player(0);
	D3DXMATRIX mtx = playerget->Get_mtxWorld();
	D3DXMatrixTranslation(&m_mtxTranslation, mtx._41, mtx._42, mtx._43);//X,Y,Z��n��
	D3DXMatrixScaling(&m_mtxScaling, WHEEL_SCALE, WHEEL_SCALE, WHEEL_SCALE);
	m_mtxWorld = m_mtxScaling * m_mtxTranslation;

	NxMat33 mat1;
	mat1.rotZ(0);
	NxVec3 scaleDwarf = NxVec3(WHEEL_SCALE, WHEEL_SCALE, WHEEL_SCALE);	//	���f���X�P�[��
	NxVec3 BBDwarf = NxVec3(0.0, 0.0, 0.0);	//	�����蔻��̑傫��
	NxVec3 BBDwarf2 = NxVec3(0, 0, 0);
	NxA_pWheel = CreateMeshAsBox(NxVec3(mtx._41, mtx._42, mtx._43 + 5), mat1, scaleDwarf, BBDwarf, MODELL_WHEEL);
}

void Cwheel::Update(void)
{
	//�����Ă���
	if (ferris_flg == true)
	{
		/*
		Ferris_position += Ferris_right * SPECIAL_SPEED;
		Ferris_position -= Ferris_front * SPECIAL_SPEED;

		if (Ferris_position.x < -45.0f)
		{
			ferris_flg = false;
		}

		rotate_ferris -= 1.0f;
		kakudoXFerris = D3DXToRadian(rotate_ferris);*/
	}
	//�Î~
	else
	{
		/*
		ferris_counter++;

		if (ferris_counter > 300)
		{
			ferris_flg = true;
			Ferris_position.x = 45.0f;
			Ferris_position.z = 45.0f;
			ferris_counter = 0;
		}*/
	}
	if (m_Enable)
	{//�����ŉ�]�v�Z���s��

		NxVec3 tr = NxA_pWheel->getGlobalPosition();
		D3DXMatrixTranslation(&m_mtxTranslation, tr.x, tr.y, tr.z);
		D3DXMatrixScaling(&m_mtxScaling, WHEEL_SCALE, WHEEL_SCALE, WHEEL_SCALE);
		D3DXMatrixRotationY(&m_mtxRotation, D3DXToRadian(0));
		m_mtxWorld = m_mtxRotation * m_mtxScaling * m_mtxTranslation;

	}
}

void Cwheel::Draw(void)
{
	//DebugFont_Draw(900, 30, "ugoki = %f\n,", ugoki);
	//DebugFont_Draw(900, 60, "Bugoki = %d\n,", Bugoki);
	if (m_Enable)
	{
		DrawDX2(m_mtxWorld, NxA_pWheel, MODELL_WHEEL);
		//DrawDirectXMesh(NxA_pSmall);
	}
}

void Cwheel::Finalize(void)
{
	Attraction_Finalize(m_AttractionIndex);
	NxA_pWheel = NULL;
	
}