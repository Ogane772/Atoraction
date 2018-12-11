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
#include "CEnemy.h"
#include "CEnemy_Small.h"
//=============================================================================
//	�萔��`
//=============================================================================
#define SPEED (0.5f)
#define SIZE (0.8f)
#define WHEEL_HP (40)
#define WHEEL_MP (1)
#define WHEEL_ATK (1)
#define SCORE (1)
#define WHEEL_SCALE (2)
//=============================================================================
//	�ÓI�ϐ�
//=============================================================================

//=============================================================================
//	�O���[�o���ϐ�
//=============================================================================

//=============================================================================
//	����
//===========
Cwheel::Cwheel() :CAttraction(TYPE_WHEEL), C3DObj(C3DObj::TYPE_ATTRACTION)
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
	m_Hp = WHEEL_HP;
	m_Mp = WHEEL_MP;
	m_Attack = WHEEL_ATK;
	
	C3DObj *playerget = CPlayer::Get_Player();	//	�v���C���[�擾
	move = playerget->Get_Front();

	D3DXMATRIX mtx = playerget->Get_mtxWorld();
	D3DXMatrixTranslation(&m_mtxTranslation, mtx._41, mtx._42, mtx._43);//X,Y,Z��n��
	D3DXMatrixScaling(&m_mtxScaling, WHEEL_SCALE, WHEEL_SCALE, WHEEL_SCALE);

	angle = playerget->Get_Angle();
	D3DXMatrixRotationY(&m_mtxRotation, D3DXToRadian(angle));

	m_mtxWorld = m_mtxScaling * m_mtxRotation * m_mtxTranslation;
	
	Wheel_position = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42*3, m_mtxWorld._43);
	
	
	NxMat33 mat1;
	NxVec3 scaleDwarf = NxVec3(WHEEL_SCALE, WHEEL_SCALE, WHEEL_SCALE);	//	���f���X�P�[��
	NxVec3 BBDwarf = NxVec3(1.5, 2.0, 2.0);	//	�����蔻��̑傫��
	NxVec3 BBDwarf2 = NxVec3(0, 0, 0);
	NxA_pWheel = CreateMeshAsBox(NxVec3(mtx._41, mtx._42, mtx._43 + 5), mat1, scaleDwarf, BBDwarf, MODELL_WHEEL);
}

void Cwheel::Update(void)
{
	//�����Ă���
	if (ferris_flg == true)
	{
		
		
	}
	//�Î~
	else
	{
		
	}

	if (m_Enable)
	{//�����ŉ�]�v�Z���s��

		rotate_ferris += 4;
		D3DXMatrixRotationX(&mtxR, D3DXToRadian(-rotate_ferris));
		Wheel_position += move*SPEED;


		NxVec3 tr = NxA_pWheel->getGlobalPosition();
		D3DXMatrixTranslation(&m_mtxTranslation, tr.x, tr.y, tr.z);
		D3DXMatrixScaling(&m_mtxScaling, WHEEL_SCALE, WHEEL_SCALE, WHEEL_SCALE);
		D3DXMATRIX mtxT;
		D3DXMatrixTranslation(&mtxT, move.x, move.y, move.z);
		D3DXMatrixTranslation(&m_mtxTranslation, Wheel_position.x, Wheel_position.y, Wheel_position.z);
		m_mtxWorld =m_mtxScaling * mtxR * m_mtxRotation * m_mtxTranslation;

		if (45.0*45.0 < (m_mtxWorld._41*m_mtxWorld._41) + (m_mtxWorld._43 * m_mtxWorld._43))
		{
			m_Enable = false;
			CPlayer::m_delete = true;
		}

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