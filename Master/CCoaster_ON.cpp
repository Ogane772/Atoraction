//////////////////////////////////////////////////
////
////	�A�g���N�V����(�W�F�b�g�R�[�X�^�[)�N���X
////
//////////////////////////////////////////////////

//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================

#include "CCoaster_ON.h"
#include "input.h"
#include "Cplayer.h"
#include "debug_font.h"
#include "time.h"
#include "move.h"
#include "CEnemy.h"
//=============================================================================
//	�萔��`
//=============================================================================
//�R�[�X�^�[���f���͂����ŕ\�� ���ԊǗ���
#define SPEED (-0.3f)
#define SIZE (0.8f)


//���̐���
#define COSTER_HP (40)
#define COSTER_MP (1)
#define COSTER_ATK (3)
#define SCORE (1)
#define COSTER_SCALE (1)
//=============================================================================
//	�ÓI�ϐ�
//=============================================================================

//=============================================================================
//	�O���[�o���ϐ�
//=============================================================================

//=============================================================================
//	����
//=============================================================================

CoasterON::CoasterON() :CAttraction(AT_COASTER_ON), C3DObj(AT_COASTER_ON)
{
	Initialize();
}

CoasterON::~CoasterON()
{

}

void CoasterON::Initialize()
{
	m_AttractionIndex = Get_AttractionIndex(AT_ALL);

	m_Enable = true;

	m_TimeKeep = m_FrameCount;

	u = 0;
	v = -90;
	m_Hp = COSTER_HP;
	m_Mp = COSTER_MP;
	m_Attack = COSTER_ATK;
	m_front = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	D3DXVec3Normalize(&m_front, &m_front);
	m_up = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	D3DXVec3Cross(&m_right, &m_front, &m_up);
	D3DXVec3Normalize(&m_right, &m_right);
	D3DXVec3Cross(&m_up, &m_right, &m_front);
	D3DXVec3Normalize(&m_up, &m_up);


	C3DObj *playerget = CPlayer::Get_Player();	//	�v���C���[�擾

	D3DXMATRIX mtx = playerget->Get_mtxWorld();
	D3DXMatrixTranslation(&m_mtxTranslation, 0, 0, -10.0f);
	angle = (float)(playerget->Get_Angle());
	D3DXMatrixRotationAxis(&mtxR, &m_up, D3DXToRadian(angle + 90));
	D3DXVec3TransformNormal(&m_front, &m_front, &mtxR);
	D3DXVec3TransformNormal(&m_right, &m_right, &mtxR);
	m_mtxWorld = m_mtxTranslation;
	//	m_mtxWorld = mtxR * m_mtxTranslation;


	D3DXMatrixTranslation(&m_mtxTranslation, mtx._41, mtx._42, mtx._43);//X,Y,Z��n��
	D3DXMatrixScaling(&m_mtxScaling, COSTER_SCALE, COSTER_SCALE, COSTER_SCALE);

	m_mtxWorld = m_mtxScaling * m_mtxWorld * mtxR * m_mtxTranslation;
	//m_mtxWorld = m_mtxScaling  * m_mtxWorld * m_mtxTranslation ;
	Thing_Normal_model = GetNormalModel(MODELL_COASTER);
	coaster_position = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42 * 3, m_mtxWorld._43);
}

void CoasterON::Update(void)
{
	//�L�����Ԃ�����

	C3DObj *playerget = CPlayer::Get_Player();	//	�v���C���[�擾
	u = (int)(playerget->Get_Angle());
	if (m_FrameCount - m_TimeKeep <= COSTERON_ENDTIME)
	{

		C3DObj *playerget = CPlayer::Get_Player();
		D3DXMATRIX playermatrix = playerget->Get_mtxTranslation();
		coaster_position += m_front*SPEED;
		m_mtxTranslation = playermatrix;
		D3DXMatrixTranslation(&m_mtxTranslation, coaster_position.x, coaster_position.y, coaster_position.z);//X,Y,Z��n��
		D3DXMatrixScaling(&m_mtxScaling, COSTER_SCALE, COSTER_SCALE, COSTER_SCALE);
		D3DXMatrixRotationY(&m_mtxRotation, D3DXToRadian(u + v));
		m_mtxWorld = m_mtxScaling * m_mtxRotation * m_mtxTranslation;
	}
	else if(m_FrameCount - m_TimeKeep > COSTERON_ENDTIME)
	{
		C3DObj_delete();
	}

}

void CoasterON::Draw(void)
{
	//DebugFont_Draw(600, 30, "Coaster  = %d\n,", *coaster);
	//DebugFont_Draw(600, 400, "m_FrameCount - m_TimeKeep = %d\n,", m_FrameCount - m_TimeKeep);
	//DebugFont_Draw(600, 0, "U = %f\n,", u);
	if (m_Enable)
	{
		Thing_Normal_model->vPosition = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);

		DrawDX_Normal(m_mtxWorld, MODELL_COASTER, Thing_Normal_model);
	}
}

void CoasterON::Finalize(void)
{
	Attraction_Finalize(m_AttractionIndex);
}

void CoasterON::Coaster_Create(void)
{

}

C3DObj *CoasterON::Get_Coaster(void)
{
	for (int i = 0; i < MAX_GAMEOBJ; i++)
	{
		C3DObj *Coaster = C3DObj::Get(i);
		if (Coaster)
		{
			if (Coaster->Get_3DObjType() == AT_COASTER_ON)
			{
				return Coaster;
			}
		}
	}
	return NULL;
}
