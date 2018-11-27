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
#include "Cphysx.h"
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
Cfreefall::Cfreefall() :CAttraction(TYPE_FALL)
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
	hp = FREEFALL_HP;
	mp = FREEFALL_MP;
	atk = FREEFALL_ATK;
	CPlayer *playerget = CPlayer::Get_Player(0);
	D3DXMATRIX mtx = playerget->Get_mtxWorld();
	D3DXMatrixTranslation(&m_mtxTranslation, mtx._41, mtx._42, mtx._43);//X,Y,Z��n��
	D3DXMatrixScaling(&m_mtxScaling, FREEFALL_SCALE, FREEFALL_SCALE, FREEFALL_SCALE);
	m_mtxWorld = m_mtxScaling * m_mtxTranslation;

	NxMat33 mat1;
	NxMat33 mat2;
	mat1.rotZ(0);
	mat2.rotZ(0);
	NxVec3 scaleDwarf = NxVec3(FREEFALL_SCALE, FREEFALL_SCALE, FREEFALL_SCALE);	//	���f���X�P�[��
	NxVec3 BBDwarf = NxVec3(5.0, 2.0, 5.0);	//	�����蔻��̑傫��
	NxVec3 BBDwarf2 = NxVec3(0, 0, 0);
	NxA_pEnban = CreateMeshAsBox(NxVec3(mtx._41, mtx._42, mtx._43 + 5), mat1, scaleDwarf, BBDwarf, MODELL_ENBAN, false);
	NxA_pHasira = CreateMeshAsBox(NxVec3(mtx._41, mtx._42, mtx._43 + 5), mat2, scaleDwarf, BBDwarf2, MODELL_HASIRA, false);
}

void Cfreefall::Update(void)
{
	if (m_Enable)
	{//�����ňړ��v�Z���s��

		NxVec3 tr = NxA_pEnban->getGlobalPosition();
		D3DXMatrixTranslation(&m_mtxTranslation, tr.x, ugoki, tr.z);
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


		NxVec3 tr2 = NxA_pHasira->getGlobalPosition();
		D3DXMatrixTranslation(&m_mtxTranslation, tr2.x, 0, tr2.z);
		D3DXMatrixScaling(&m_mtxScaling, FREEFALL_SCALE, FREEFALL_SCALE, FREEFALL_SCALE);
		D3DXMatrixRotationY(&m_mtxRotation, D3DXToRadian(0));
		m_mtxWorld2 = m_mtxScaling * m_mtxRotation * m_mtxTranslation;

	}
}

void Cfreefall::Draw(void)
{
	DebugFont_Draw(800, 30, "ugoki = %f\n,", ugoki);
	DebugFont_Draw(800, 60, "Bugoki = %d\n,", Bugoki);
	if (m_Enable)
	{
		DrawDX2(m_mtxWorld, NxA_pEnban, MODELL_ENBAN);
		DrawDX2(m_mtxWorld2, NxA_pHasira, MODELL_HASIRA);
	}
}

void Cfreefall::Finalize(void)
{
	Attraction_Finalize(m_AttractionIndex);
	NxA_pEnban = NULL;
	NxA_pHasira = NULL;
}