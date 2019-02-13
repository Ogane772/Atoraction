//////////////////////////////////////////////////
////
////	オブジェクト(ゴミ箱)クラス
////
//////////////////////////////////////////////////

//=============================================================================
//	インクルードファイル
//=============================================================================
#include "COrnament_Husen.h"
#include "debug_font.h"
//=============================================================================
//	定数定義
//=============================================================================

#define HUSEN_SIZE (1.0f)
#define HUSEN_ATTACK (3)
#define HUSEN_HP (1)
#define HUSEN_SCORE (1)
#define HUSEN_ATK (1)
//=============================================================================
//	静的変数
//=============================================================================

//=============================================================================
//	グローバル変数
//=============================================================================

//=============================================================================
//	生成
//=============================================================================

COrnament_HUSEN::COrnament_HUSEN(ORNAMENT_EMITTER *Emitter) :COrnament(TYPE_HUSEN), C3DObj(C3DObj::TYPE_ORNAMENT)
{
	Initialize(Emitter);
}

//=============================================================================
//	破棄
//=============================================================================
COrnament_HUSEN::~COrnament_HUSEN()
{

}


void COrnament_HUSEN::Husen_Create(void)
{

}

void COrnament_HUSEN::Initialize(ORNAMENT_EMITTER *Emitter)
{
	m_OrnamentIndex = Get_OrnamentIndex(TYPE_ALL);
	m_Enable = true;
	m_DrawCheck = true;
	m_Hp = HUSEN_HP;
	m_Attack = HUSEN_ATK;

	Thing_Normal_model = GetNormalModel(MODELL_HUSEN);

	m_Direction = Emitter->InitDirection;

	D3DXMatrixRotationY(&m_mtxRotation, D3DXToRadian(m_Direction));
	D3DXMatrixTranslation(&m_mtxTranslation, Emitter->InitPos.x, Emitter->InitPos.y, Emitter->InitPos.z);
	D3DXMatrixScaling(&m_mtxScaling, Emitter->scale.x, Emitter->scale.y, Emitter->scale.z);
	m_mtxWorld = m_mtxRotation * m_mtxScaling * m_mtxTranslation;

	InitSphere(m_pD3DDevice, &Thing_Normal_model, D3DXVECTOR3(0, 0.0, 0), 3.1f);//当たり判定の変更

	Thing.vPosition = D3DXVECTOR3(m_mtxTranslation._41, m_mtxTranslation._42, m_mtxTranslation._43);
}


void COrnament_HUSEN::Finalize(void)
{

	Ornament_Finalize(m_OrnamentIndex);

}


void COrnament_HUSEN::Update(void)
{
	if (m_Enable)
	{
		//エフェクト処理を行う
	}
}



void COrnament_HUSEN::Draw(void)
{
	if (m_Enable)
	{
		Thing_Normal_model.vPosition = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);
		m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		DrawDX_Normal(m_mtxWorld, MODELL_HUSEN, &Thing_Normal_model);
	}
}


void COrnament_HUSEN::Damage(void)
{

}