//////////////////////////////////////////////////
////
////	�I�u�W�F�N�g(�S�~��)�N���X
////
//////////////////////////////////////////////////

//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================
#include "COrnament_Bench.h"
#include "debug_font.h"
//=============================================================================
//	�萔��`
//=============================================================================

#define BENCH_SIZE (1.0f)
#define BENCH_ATTACK (3)
#define BENCH_HP (1)
#define BENCH_SCORE (1)
#define BENCH_ATK (1)
//=============================================================================
//	�ÓI�ϐ�
//=============================================================================

//=============================================================================
//	�O���[�o���ϐ�
//=============================================================================

//=============================================================================
//	����
//=============================================================================

COrnament_BENCH::COrnament_BENCH(ORNAMENT_EMITTER *Emitter) :COrnament(TYPE_BENCH), C3DObj(C3DObj::TYPE_ORNAMENT)
{
	Initialize(Emitter);
}

//=============================================================================
//	�j��
//=============================================================================
COrnament_BENCH::~COrnament_BENCH()
{

}


void COrnament_BENCH::Bench_Create(void)
{

}

void COrnament_BENCH::Initialize(ORNAMENT_EMITTER *Emitter)
{
	m_OrnamentIndex = Get_OrnamentIndex(TYPE_ALL);
	m_Enable = true;
	m_DrawCheck = true;
	m_Hp = BENCH_HP;
	m_Attack = BENCH_ATK;

	Thing_Normal_model = GetNormalModel(MODELL_BENCH);

	m_Direction = Emitter->InitDirection;

	D3DXMatrixRotationY(&m_mtxRotation, D3DXToRadian(m_Direction));
	D3DXMatrixTranslation(&m_mtxTranslation, Emitter->InitPos.x, Emitter->InitPos.y, Emitter->InitPos.z);
	D3DXMatrixScaling(&m_mtxScaling, BENCH_SIZE, BENCH_SIZE, BENCH_SIZE);
	m_mtxWorld = m_mtxRotation * m_mtxScaling * m_mtxTranslation;

	InitSphere(m_pD3DDevice, Thing_Normal_model, D3DXVECTOR3(0, 0.0, 0), 3.1f);//�����蔻��̕ύX

	Thing.vPosition = D3DXVECTOR3(m_mtxTranslation._41, m_mtxTranslation._42, m_mtxTranslation._43);
}


void COrnament_BENCH::Finalize(void)
{

	Ornament_Finalize(m_OrnamentIndex);

}


void COrnament_BENCH::Update(void)
{
	if (m_Enable)
	{
		//�G�t�F�N�g�������s��
	}
}



void COrnament_BENCH::Draw(void)
{
	if (m_Enable)
	{
		Thing_Normal_model->vPosition = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);
		m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		DrawDX_Normal(m_mtxWorld, MODELL_BENCH, Thing_Normal_model);
	}
}


void COrnament_BENCH::Damage(void)
{

}