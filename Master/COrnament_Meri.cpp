//////////////////////////////////////////////////
////
////	オブジェクト(ゴミ箱)クラス
////
//////////////////////////////////////////////////

//=============================================================================
//	インクルードファイル
//=============================================================================
#include "COrnament_MERI.h"
#include "debug_font.h"
//=============================================================================
//	定数定義
//=============================================================================

#define MERI_SIZE (1.0f)
#define MERI_ATTACK (3)
#define MERI_HP (1)
#define MERI_SCORE (1)
#define MERI_ATK (1)
//=============================================================================
//	静的変数
//=============================================================================

//=============================================================================
//	グローバル変数
//=============================================================================

//=============================================================================
//	生成
//=============================================================================

COrnament_MERI::COrnament_MERI(ORNAMENT_EMITTER *Emitter) :COrnament(TYPE_MERI), C3DObj(C3DObj::TYPE_ORNAMENT)
{
	Initialize(Emitter);
}

//=============================================================================
//	破棄
//=============================================================================
COrnament_MERI::~COrnament_MERI()
{

}


void COrnament_MERI::MERI_Create(void)
{

}

void COrnament_MERI::Initialize(ORNAMENT_EMITTER *Emitter)
{
	m_OrnamentIndex = Get_OrnamentIndex(TYPE_ALL);
	m_Enable = true;
	m_DrawCheck = true;
	m_Hp = MERI_HP;
	m_Attack = MERI_ATK;

	Thing_Normal_model = GetNormalModel(MODELL_MERI);

	m_Direction = Emitter->InitDirection;

	D3DXMatrixRotationY(&m_mtxRotation, D3DXToRadian(m_Direction));
	D3DXMatrixTranslation(&m_mtxTranslation, Emitter->InitPos.x, Emitter->InitPos.y, Emitter->InitPos.z);
	D3DXMatrixScaling(&m_mtxScaling, Emitter->scale.x, Emitter->scale.y, Emitter->scale.z);
	m_mtxWorld = m_mtxRotation * m_mtxScaling * m_mtxTranslation;

	InitSphere(m_pD3DDevice, &Thing_Normal_model, D3DXVECTOR3(0, 0.0, 0), 3.1f);//当たり判定の変更

	Thing.vPosition = D3DXVECTOR3(m_mtxTranslation._41, m_mtxTranslation._42, m_mtxTranslation._43);
}


void COrnament_MERI::Finalize(void)
{

	Ornament_Finalize(m_OrnamentIndex);

}


void COrnament_MERI::Update(void)
{
	if (m_Enable)
	{
		//エフェクト処理を行う
	}
}



void COrnament_MERI::Draw(void)
{
	if (m_Enable)
	{
		Thing_Normal_model.vPosition = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);
		m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		DrawDX_Normal(m_mtxWorld, MODELL_MERI, &Thing_Normal_model);
	}
}


void COrnament_MERI::Damage(void)
{

}