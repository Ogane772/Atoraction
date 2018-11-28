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
#define SPEED (0.1f)
#define SPECIAL_SPEED (0.3f)
#define SIZE (0.8f)
#define WHEEL_HP (40)
#define WHEEL_MP (1)
#define WHEEL_ATK (1)
#define SCORE (1)
#define WHEEL_SCALE (3)
//=============================================================================
//	�ÓI�ϐ�
//=============================================================================

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
	rotate_ferris = 0;
	Ferris_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Wheel_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Wheel_Flg = false;
	Rotate_Ferris = 0.0f;
	Ferris_Angel_stock = 0.0f;

	hp = WHEEL_HP;
	mp = WHEEL_MP;
	atk = WHEEL_ATK;
	kakudoXFerris = D3DXToRadian(0);
	CPlayer *playerget = CPlayer::Get_Player(0);
	D3DXMATRIX mtx = playerget->Get_mtxWorld();
	D3DXMatrixTranslation(&m_mtxTranslation, mtx._41, mtx._42, mtx._43);//X,Y,Z��n��
	D3DXMatrixScaling(&m_mtxScaling, WHEEL_SCALE, WHEEL_SCALE, WHEEL_SCALE);
	m_mtxWorld = m_mtxScaling * m_mtxTranslation;

	NxMat33 mat1;
	mat1.rotZ(0);
	NxVec3 scaleDwarf = NxVec3(WHEEL_SCALE, WHEEL_SCALE, WHEEL_SCALE);	//	���f���X�P�[��
	NxVec3 BBDwarf = NxVec3(0.0, 0.0, 0.0);	//	�����蔻��̑傫��
	NxA_pWheel = CreateMeshAsBox(NxVec3(mtx._41, mtx._42, mtx._43), mat1, scaleDwarf, BBDwarf, MODELL_WHEEL, true);

	//�e�̐����|�W�V����
	Wheel_position.x = mtx._41;
	Wheel_position.y = mtx._42;
	Wheel_position.z = mtx._43;
	//g_Bullet[i].btCollision.cx = g_Bullet[i].btX;
	//g_Bullet[i].btCollision.cy = g_Bullet[i].btY;

	CPlayer *player = CPlayer::Get_Player(0);

	//�v���C���[�̊p�x���X�g�b�N��
	Ferris_Angel_stock = player->Get_Player_Angle();
	Wheel_position_stock = player->Get_PlayerFront();
	Wheel_Flg = true;
}

void Cwheel::Update(void)
{
	if (m_Enable)
	{//�����ŉ�]�v�Z���s��
	 //�����Ă���
		if (Wheel_Flg == true)
		{

			Wheel_position += Wheel_position_stock * SPEED;
			Rotate_Ferris += 2.0f;

			//Wheel.btCollision.cx = Wheel.btX;
			//Wheel.btCollision.cy = Wheel.btY;

			//�A�e����ʊO�ɏo����e�𖳌��ɂ���


			//��
			if (Wheel_position.z >= 100.0f)//100.0f�͕ǂ̍��W�Ȃ�Ŏ����ŕς��Ă�
			{
				Wheel_Flg = false;
				Rotate_Ferris = 0.0f;
			}
			//��O
			if (Wheel_position.z <= -100.0f)
			{
				Rotate_Ferris = 0.0f;
			}
			//�E
			if (Wheel_position.x >= 100.0f)
			{
				Wheel_Flg = false;
				Rotate_Ferris = 0.0f;
			}
			//��
			if (Wheel_position.x <= -100.0f)
			{
				Wheel_Flg = false;
				Rotate_Ferris = 0.0f;
			}
		}
	}


	NxVec3 tr = NxA_pWheel->getGlobalPosition();
	D3DXMatrixTranslation(&m_mtxTranslation, Wheel_position.x, Wheel_position.y, Wheel_position.z);
	D3DXMatrixScaling(&m_mtxScaling, WHEEL_SCALE, WHEEL_SCALE, WHEEL_SCALE);
	D3DXMatrixRotationX(&m_mtxRotation, -kakudoXFerris);
	D3DXMatrixRotationY(&m_mtxRotation2, D3DXToRadian(Ferris_Angel_stock));

	m_mtxWorld = m_mtxRotation2 * m_mtxRotation *  m_mtxScaling * m_mtxTranslation;

}

void Cwheel::Draw(void)
{
	DebugFont_Draw(500, 30, "Ferris_position.x = %f\n,", Wheel_position.x);
	DebugFont_Draw(500, 60, "ferris_flg = %d\n,", ferris_flg);
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