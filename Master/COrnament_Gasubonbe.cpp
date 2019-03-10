//////////////////////////////////////////////////
////
////	�I�u�W�F�N�g(�K�X�{���x)�N���X
////
//////////////////////////////////////////////////

//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================

#include "COrnament_Gasubonbe.h"
#include "debug_font.h"
#include "exp.h"
#include "CEnemy.h"
#include "CTexture.h"
#include "sound.h"
//=============================================================================
//	�萔��`
//=============================================================================

#define GASUBONBE_SIZE (1.0f)
#define GASUBONBE_ATTACK (3)
#define GASUBONBE_HP (1)
#define GASUBONBE_SCORE (1)
#define GASUBONBE_ATK (1)

#define FRY_HEIGHT (0.1f)
#define FRY_SPEED (0.07f)
//=============================================================================
//	�ÓI�ϐ�
//=============================================================================

//=============================================================================
//	�O���[�o���ϐ�
//=============================================================================

//=============================================================================
//	����
//=============================================================================

COrnament_Gasubonbe::COrnament_Gasubonbe(ORNAMENT_EMITTER *Emitter) :COrnament(MODELL_GASUBONBE), C3DObj(C3DObj::TYPE_ORNAMENT)
{
	Initialize(Emitter);
}

//=============================================================================
//	�j��
//=============================================================================
COrnament_Gasubonbe::~COrnament_Gasubonbe()
{

}

void COrnament_Gasubonbe::Initialize(ORNAMENT_EMITTER *Emitter)
{
	m_DrawCount = 0;
	m_OrnamentIndex = Get_OrnamentIndex(TYPE_ALL);
	m_Enable = true;
	m_DrawCheck = true;
	m_Hp = GASUBONBE_HP;
	m_Attack = GASUBONBE_ATK;

	Thing_Normal_model = GetNormalModel(MODELL_GASUBONBE);

	m_Direction = Emitter->InitDirection;

	D3DXMatrixTranslation(&m_mtxTranslation, Emitter->InitPos.x, Emitter->InitPos.y, Emitter->InitPos.z);
	D3DXMatrixRotationY(&m_mtxRotation, D3DXToRadian(m_Direction));
	D3DXMatrixScaling(&m_mtxScaling, Emitter->scale.x, Emitter->scale.y, Emitter->scale.z);
	m_mtxWorld = m_mtxRotation * m_mtxScaling * m_mtxTranslation;
	m_mtxInit = m_mtxWorld;
	Thing_Normal_model.vPosition = D3DXVECTOR3(m_mtxTranslation._41, m_mtxTranslation._42, m_mtxTranslation._43);
	InitSphere(m_pD3DDevice, &Thing_Normal_model, D3DXVECTOR3(0, 0.0, 0), 1.5f);//�����蔻��̕ύX
}


void COrnament_Gasubonbe::Finalize(void)
{

	m_DrawCount = 0;
	m_OrnamentIndex = Get_OrnamentIndex(TYPE_ALL);
	m_Enable = true;
	m_DrawCheck = true;
	m_Hp = GASUBONBE_HP;
	m_Attack = GASUBONBE_ATK;



	D3DXMatrixTranslation(&m_mtxTranslation, m_mtxInit._41, m_mtxInit._42, m_mtxInit._43);

	m_mtxWorld = m_mtxRotation * m_mtxScaling * m_mtxTranslation;

	Thing_Normal_model.vPosition = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);

}


void COrnament_Gasubonbe::Update(void)
{
	if (m_Enable)
	{
		//�G�t�F�N�g�������s��
		if (m_DrawCheck)
		{
			if (m_DamageFlag)
			{
				Ornament_Damage(FRY_HEIGHT);
				Ornament_Flying(FRY_SPEED);
				Damage();
			}
		}
		m_mtxWorld = m_mtxRotation * m_mtxScaling * m_mtxTranslation;
		Thing_Normal_model.vPosition = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);

		Death();
	}
}



void COrnament_Gasubonbe::Draw(void)
{
	if (m_Enable)
	{
		D3DXVECTOR3 position = D3DXVECTOR3(0.0f, 1.2f, -1.0f);
		m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
		if (!m_DrawCheck)
		{
			if (m_FrameCount % 2 == 0)
			{
				m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
				DrawDX_NormalAdd(m_mtxWorld, MODELL_GASUBONBE, &Thing_Normal_model, position);

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
			m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
			DrawDX_NormalAdd(m_mtxWorld, MODELL_GASUBONBE, &Thing_Normal_model, position);
		}
	}
}


void COrnament_Gasubonbe::Damage(void)
{
	int i;
	C3DObj *enemy;
	THING *thingenemy;
	int attack;
	for (i = 0; i < MAX_GAMEOBJ; i++)
	{
		enemy = CEnemy::Get_Enemy(i);

		if (enemy && m_DrawCheck)
		{
			if (enemy->Get_AttacFlag())
			{
				Thing_Normal_model.vPosition = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);
				thingenemy = enemy->GetAnimeModel();
				attack = enemy->Get_Attck();
				if (C3DObj::Collision_AnimeVSNormal(thingenemy, &Thing_Normal_model))
				{
					m_Hp -= attack;
					m_DrawCheck = false;
					if (m_Hp <= 0)
					{
						//Exp_Create(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43, 1.0f, 0.0f, CTexture::TEX_EFFECT_HIT1, 14, 1, 3360 / 7, 960 / 2, 7);
						//C3DObj_delete();
					}
					break;
				}
			}
		}
	}
}