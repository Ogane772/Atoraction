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
#include "exp.h"
#include "CEnemy.h"
#include "CTexture.h"
//=============================================================================
//	�萔��`
//=============================================================================

#define BENCH_SIZE (1.0f)
#define BENCH_ATTACK (3)
#define BENCH_HP (1)
#define BENCH_SCORE (1)
#define BENCH_ATK (1)

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

COrnament_BENCH::COrnament_BENCH(ORNAMENT_EMITTER *Emitter) :COrnament(MODELL_BENCH), C3DObj(C3DObj::TYPE_ORNAMENT)
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
	m_DrawCount = 0;
	m_OrnamentIndex = Get_OrnamentIndex(TYPE_ALL);
	m_Enable = true;
	m_DrawCheck = true;
	m_Hp = BENCH_HP;
	m_Attack = BENCH_ATK;

	Thing_Normal_model = GetNormalModel(MODELL_BENCH);

	//InitThing(&Thing_Normal_model, NORMAL_MODEL_FILES[MODELL_BENCH].filename);
	//InitSphere(m_pD3DDevice, &Thing_Normal_model);//�����蔻��̕\��
	m_Direction = Emitter->InitDirection;

	D3DXMatrixRotationY(&m_mtxRotation, D3DXToRadian(m_Direction));
	D3DXMatrixTranslation(&m_mtxTranslation, Emitter->InitPos.x, Emitter->InitPos.y, Emitter->InitPos.z);
	D3DXMatrixScaling(&m_mtxScaling, Emitter->scale.x, Emitter->scale.y, Emitter->scale.z);
	m_mtxWorld = m_mtxRotation * m_mtxScaling * m_mtxTranslation;

	InitSphere(m_pD3DDevice, &Thing_Normal_model, D3DXVECTOR3(0, 0.0, 0), 2.0f);//�����蔻��̕ύX

	Thing_Normal_model.vPosition = D3DXVECTOR3(m_mtxTranslation._41, m_mtxTranslation._42, m_mtxTranslation._43);
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
		Death();
	}

}



void COrnament_BENCH::Draw(void)
{
	if (m_Enable)
	{
		Thing_Normal_model.vPosition = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);
		m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		DrawDX_Normal(m_mtxWorld, MODELL_BENCH, &Thing_Normal_model);
		if (!m_DrawCheck)
		{
			if (m_FrameCount % 2 == 0)
			{
				DrawDX_Normal(m_mtxWorld, MODELL_BENCH, &Thing_Normal_model);

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
			DrawDX_Normal(m_mtxWorld, MODELL_BENCH, &Thing_Normal_model);
		}
	}
}


void COrnament_BENCH::Damage(void)
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
						//Exp_Create(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43, 1.0f, 0.0f, CTexture::TEX_EFFECT_HIT1, 14, 1, 3360 / 7, 960 / 2, 7);
						//C3DObj_delete();
					}
					break;
				}
			}
		}
	}
}