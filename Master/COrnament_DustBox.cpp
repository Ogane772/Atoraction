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
#include "exp.h"
#include "CEnemy.h"
#include "CTexture.h"
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

COrnament_DustBox::COrnament_DustBox(ORNAMENT_EMITTER *Emitter) :COrnament(MODELL_GOMIBAKO), C3DObj(C3DObj::TYPE_ORNAMENT)
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
	m_DrawCount = 0;
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

	Thing_Normal_model.vPosition = D3DXVECTOR3(m_mtxTranslation._41, m_mtxTranslation._42, m_mtxTranslation._43);
	InitSphere(m_pD3DDevice, &Thing_Normal_model, D3DXVECTOR3(0, 0.0, 0), 2.1f);//当たり判定の変更
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



void COrnament_DustBox::Draw(void)
{
	if (m_Enable)
	{
		D3DXVECTOR3 position = D3DXVECTOR3(-0.75f, 1.2f, 1.5f);
		Thing_Normal_model.vPosition = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);
		m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
		if (!m_DrawCheck)
		{
			if (m_FrameCount % 2 == 0)
			{
				DrawDX_NormalAdd(m_mtxWorld, MODELL_GOMIBAKO, &Thing_Normal_model, position);

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
			DrawDX_NormalAdd(m_mtxWorld, MODELL_GOMIBAKO, &Thing_Normal_model, position);
		}
	}
}


void COrnament_DustBox::Damage(void)
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