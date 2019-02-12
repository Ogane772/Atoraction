//////////////////////////////////////////////////
////
////	オブジェクト(噴水)クラス
////
//////////////////////////////////////////////////

//=============================================================================
//	インクルードファイル
//=============================================================================

#include "COrnament_Fountain.h"
#include "debug_font.h"
#include "exp.h"
#include "CEnemy.h"
#include "CTexture.h"
//=============================================================================
//	定数定義
//=============================================================================

#define FOUNTAIN_SIZE (2.0f)
#define FOUNTAIN_ATTACK (3)
#define FOUNTAIN_HP (1)
#define FOUNTAIN_SCORE (1)
#define FOUNTAIN_ATK (1)
//=============================================================================
//	静的変数
//=============================================================================

//=============================================================================
//	グローバル変数
//=============================================================================

//=============================================================================
//	生成
//=============================================================================

COrnament_Fountain::COrnament_Fountain(ORNAMENT_EMITTER *Emitter) :COrnament(MODELL_HUNSUI), C3DObj(C3DObj::TYPE_ORNAMENT)
{
	Initialize(Emitter);
}

//=============================================================================
//	破棄
//=============================================================================
COrnament_Fountain::~COrnament_Fountain()
{

}


void COrnament_Fountain::Fountain_Create(void)
{

}

void COrnament_Fountain::Initialize(ORNAMENT_EMITTER *Emitter)
{
	m_DrawCount = 0;
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

	Thing_Normal_model.vPosition = D3DXVECTOR3(m_mtxTranslation._41, m_mtxTranslation._42, m_mtxTranslation._43);
	InitSphere(m_pD3DDevice, &Thing_Normal_model, D3DXVECTOR3(0, 0.0, 0), 4.6f);//当たり判定の変更
}


void COrnament_Fountain::Finalize(void)
{

	Ornament_Finalize(m_OrnamentIndex);

}


void COrnament_Fountain::Update(void)
{
	if (m_Enable)
	{
		//エフェクト処理を行う
		if (m_DrawCheck)
		{
			if (m_DamageFlag)
			{
				Damage();
				Ornament_Damage(0.1);
				Ornament_Flying(0.05);
			}
		}
	}
	m_mtxWorld = m_mtxRotation * m_mtxScaling * m_mtxTranslation;
}



void COrnament_Fountain::Draw(void)
{
	if (m_Enable)
	{
		Thing_Normal_model.vPosition = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);
		m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		if (!m_DrawCheck)
		{
			if (m_FrameCount % 2 == 0)
			{
				DrawDX_Normal(m_mtxWorld, MODELL_HUNSUI, &Thing_Normal_model);

				m_DrawCount++;
				if (m_DrawCount >= ORNAMENT_WAIT_TIME)
				{
					m_DrawCount = 0;
					m_DrawCheck = true;
				}
			}
		}
		else
		{
			DrawDX_Normal(m_mtxWorld, MODELL_HUNSUI, &Thing_Normal_model);
		}
	}
}


void COrnament_Fountain::Damage(void)
{
	for (int i = 0; i < MAX_GAMEOBJ; i++)
	{
		C3DObj *enemy = CEnemy::Get_Enemy(i);

		if (enemy && m_DrawCheck)
		{
			if (enemy->Get_AttacFlag())
			{
				Thing_Normal_model.vPosition = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);
				THING *thingenemy = enemy->GetAnimeModel();
				int attack = enemy->Get_Attck();
				if (C3DObj::Collision_AnimeVSNormal(thingenemy, &Thing_Normal_model))
				{
					m_Hp -= attack;
					m_DrawCheck = false;
					if (m_Hp <= 0)
					{
						Exp_Create(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43, 1.0f, 0.0f, CTexture::TEX_EFFECT_HIT1, 14, 1, 3360 / 7, 960 / 2, 7);
						C3DObj_delete();
					}
					break;
				}
			}
		}
	}
}