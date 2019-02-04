//////////////////////////////////////////////////
////
////	エネミー(スモール)クラス
////
//////////////////////////////////////////////////

//=============================================================================
//	インクルードファイル
//=============================================================================

#include "COrnament_Lamp.h"
#include "debug_font.h"
//=============================================================================
//	定数定義
//=============================================================================

#define LAMP_SIZE (1.0f)
#define LAMP_ATTACK (3)
#define LAMP_HP (1)
#define LAMP_SCORE (1)
#define LAMP_ATK (1)
//=============================================================================
//	静的変数
//=============================================================================

//=============================================================================
//	グローバル変数
//=============================================================================

//=============================================================================
//	生成
//=============================================================================

COrnament_Lamp::COrnament_Lamp(ORNAMENT_EMITTER *Emitter) :COrnament(TYPE_LAMP), C3DObj(C3DObj::TYPE_ORNAMENT)
{
	Initialize(Emitter);
}

//=============================================================================
//	破棄
//=============================================================================

COrnament_Lamp::~COrnament_Lamp()
{

}


void COrnament_Lamp::Lamp_Create(void)
{

}

void COrnament_Lamp::Initialize(ORNAMENT_EMITTER *Emitter)
{
	m_OrnamentIndex = Get_OrnamentIndex(TYPE_ALL);
	m_Enable = true;
	m_DrawCheck = true;
	m_Hp = LAMP_HP;
	m_Attack = LAMP_ATK;

	Thing_Normal_model = GetNormalModel(MODELL_LAMP);

	m_Direction = Emitter->InitDirection;

	D3DXMatrixTranslation(&m_mtxTranslation, Emitter->InitPos.x, Emitter->InitPos.y, Emitter->InitPos.z);
	D3DXMatrixRotationY(&m_mtxRotation, D3DXToRadian(m_Direction));
	D3DXMatrixScaling(&m_mtxScaling, LAMP_SIZE, LAMP_SIZE, LAMP_SIZE);
	m_mtxWorld = m_mtxRotation * m_mtxScaling * m_mtxTranslation;

	Thing.vPosition = D3DXVECTOR3(m_mtxTranslation._41, m_mtxTranslation._42, m_mtxTranslation._43);
}


void COrnament_Lamp::Finalize(void)
{

	Ornament_Finalize(m_OrnamentIndex);

}


void COrnament_Lamp::Update(void)
{
	if (m_Enable)
	{
		//エフェクト処理を行う
	}
}



void COrnament_Lamp::Draw(void)
{
	if (m_Enable)
	{
		Thing_Normal_model->vPosition = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);

		DrawDX_Normal(m_mtxWorld, MODELL_LAMP, Thing_Normal_model);
	}
}


void COrnament_Lamp::Damage(void)
{


}








