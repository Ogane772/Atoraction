//////////////////////////////////////////////////
////
////	オブジェクト(ゴミ箱)クラス
////
//////////////////////////////////////////////////

//=============================================================================
//	インクルードファイル
//=============================================================================

#include "COrnament_DustBox.h"
#include "debug_font.h"
//=============================================================================
//	定数定義
//=============================================================================

#define DUSTBOX_SIZE (1.0f)
#define DUSTBOX_ATTACK (3)
#define DUSTBOX_HP (1)
#define DUSTBOX_SCORE (1)
#define DUSTBOX_ATK (1)
//=============================================================================
//	静的変数
//=============================================================================

//=============================================================================
//	グローバル変数
//=============================================================================

//=============================================================================
//	生成
//=============================================================================

COrnament_DustBox::COrnament_DustBox(ORNAMENT_EMITTER *Emitter) :COrnament(TYPE_DUSTBOX), C3DObj(C3DObj::TYPE_ORNAMENT)
{
	Initialize(Emitter);
}

//=============================================================================
//	破棄
//=============================================================================
COrnament_DustBox::~COrnament_DustBox()
{

}


void COrnament_DustBox::Dust_Create(void)
{

}

void COrnament_DustBox::Initialize(ORNAMENT_EMITTER *Emitter)
{
	m_OrnamentIndex = Get_OrnamentIndex(TYPE_ALL);
	m_Enable = true;
	m_DrawCheck = true;
	m_Hp = DUSTBOX_HP;
	m_Attack = DUSTBOX_ATK;

	Thing_Normal_model = GetNormalModel(MODELL_GOMIBAKO);

	m_Direction = Emitter->InitDirection;

	D3DXMatrixTranslation(&m_mtxTranslation, Emitter->InitPos.x, Emitter->InitPos.y, Emitter->InitPos.z);
	D3DXMatrixRotationY(&m_mtxRotation, D3DXToRadian(m_Direction));
	D3DXMatrixScaling(&m_mtxScaling, DUSTBOX_SIZE, DUSTBOX_SIZE, DUSTBOX_SIZE);
	m_mtxWorld = m_mtxRotation * m_mtxScaling * m_mtxTranslation;

	Thing.vPosition = D3DXVECTOR3(m_mtxTranslation._41, m_mtxTranslation._42, m_mtxTranslation._43);
	InitSphere(m_pD3DDevice, Thing_Normal_model, D3DXVECTOR3(0, 0.0, 0), 3.1f);//当たり判定の変更
}


void COrnament_DustBox::Finalize(void)
{

	Ornament_Finalize(m_OrnamentIndex);

}


void COrnament_DustBox::Update(void)
{
	if (m_Enable)
	{
		//エフェクト処理を行う
	}
}



void COrnament_DustBox::Draw(void)
{
	if (m_Enable)
	{
		Thing_Normal_model->vPosition = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);
		m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		DrawDX_Normal(m_mtxWorld, MODELL_GOMIBAKO, Thing_Normal_model);
	}
}


void COrnament_DustBox::Damage(void)
{

}