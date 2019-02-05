//////////////////////////////////////////////////
////
////	�I�u�W�F�N�g(����)�N���X
////
//////////////////////////////////////////////////

//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================

#include "COrnament_Fountain.h"
#include "debug_font.h"
//=============================================================================
//	�萔��`
//=============================================================================

#define FOUNTAIN_SIZE (2.0f)
#define FOUNTAIN_ATTACK (3)
#define FOUNTAIN_HP (1)
#define FOUNTAIN_SCORE (1)
#define FOUNTAIN_ATK (1)
//=============================================================================
//	�ÓI�ϐ�
//=============================================================================

//=============================================================================
//	�O���[�o���ϐ�
//=============================================================================

//=============================================================================
//	����
//=============================================================================

COrnament_Fountain::COrnament_Fountain(ORNAMENT_EMITTER *Emitter) :COrnament(TYPE_FOUNTAIN), C3DObj(C3DObj::TYPE_ORNAMENT)
{
	Initialize(Emitter);
}

//=============================================================================
//	�j��
//=============================================================================
COrnament_Fountain::~COrnament_Fountain()
{

}


void COrnament_Fountain::Fountain_Create(void)
{

}

void COrnament_Fountain::Initialize(ORNAMENT_EMITTER *Emitter)
{
	m_OrnamentIndex = Get_OrnamentIndex(TYPE_ALL);
	m_Enable = true;
	m_DrawCheck = true;
	m_Hp = FOUNTAIN_HP;
	m_Attack = FOUNTAIN_ATK;

	Thing_Normal_model = GetNormalModel(MODELL_HUNSUI);

	m_Direction = Emitter->InitDirection;

	D3DXMatrixRotationY(&m_mtxRotation, D3DXToRadian(m_Direction));
	D3DXMatrixTranslation(&m_mtxTranslation, Emitter->InitPos.x, Emitter->InitPos.y, Emitter->InitPos.z);
	D3DXMatrixScaling(&m_mtxScaling, FOUNTAIN_SIZE, FOUNTAIN_SIZE, FOUNTAIN_SIZE);
	m_mtxWorld = m_mtxRotation * m_mtxScaling * m_mtxTranslation;

	Thing.vPosition = D3DXVECTOR3(m_mtxTranslation._41, m_mtxTranslation._42, m_mtxTranslation._43);
	InitSphere(m_pD3DDevice, Thing_Normal_model, D3DXVECTOR3(0, 0.0, 0), 4.6f);//�����蔻��̕ύX
}


void COrnament_Fountain::Finalize(void)
{

	Ornament_Finalize(m_OrnamentIndex);

}


void COrnament_Fountain::Update(void)
{
	if (m_Enable)
	{
		//�G�t�F�N�g�������s��
	}
}



void COrnament_Fountain::Draw(void)
{
	if (m_Enable)
	{
		Thing_Normal_model->vPosition = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);
		m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		DrawDX_Normal(m_mtxWorld, MODELL_HUNSUI, Thing_Normal_model);
	}
}


void COrnament_Fountain::Damage(void)
{

}