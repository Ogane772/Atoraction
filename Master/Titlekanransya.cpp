//////////////////////////////////////////////////
////
////	�^�C�g���ϗ��ԃN���X
////
//////////////////////////////////////////////////

//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================

#include "Titlekanransya.h"
#include "Cplayer.h"
#include "debug_font.h"
#include "CEnemy.h"
#include "CEnemy_Small.h"
#include "sound.h"
//=============================================================================
//	�萔��`
//=============================================================================
#define SPEED (0.5f)
#define SIZE (0.8f)
#define WHEEL_HP (40)
#define WHEEL_ATK (1)
#define SCORE (1)
#define WHEEL_SCALE (2)
//=============================================================================
//	�ÓI�ϐ�
//=============================================================================

//=============================================================================
//	�O���[�o���ϐ�
//=============================================================================

//=============================================================================
//	����
//===========
CTitleKanransya::CTitleKanransya(D3DXVECTOR3 posisiton) :CAttraction(AT_WHEEL), C3DObj(TYPE_ATTRACTION)
{
	Initialize(posisiton);
}

CTitleKanransya::~CTitleKanransya()
{

}

void CTitleKanransya::Initialize(D3DXVECTOR3 posisiton)
{
	m_AttractionIndex = Get_AttractionIndex(AT_ALL);
	PlaySound(WHEEL_SE);
	m_Enable = true;
	ferris_flg = true;
	ferris_counter = 0;
	rotate_ferris = 0;
	m_Hp = WHEEL_HP;
	m_Mp = WHEEL_MP;
	m_Attack = WHEEL_ATK;

	m_front = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXVec3Normalize(&m_front, &m_front);
	m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVec3Cross(&m_right, &m_front, &m_up);
	D3DXVec3Normalize(&m_right, &m_right);
	D3DXVec3Cross(&m_up, &m_right, &m_front);
	D3DXVec3Normalize(&m_up, &m_up);


	C3DObj *playerget = CPlayer::Get_Player();	//	�v���C���[�擾

	D3DXMATRIX mtx = playerget->Get_mtxWorld();
	D3DXMatrixTranslation(&m_mtxTranslation, posisiton.x , posisiton.y, posisiton.z);
	angle = (float)(playerget->Get_Angle());
	D3DXMatrixRotationAxis(&mtxR, &m_up, D3DXToRadian(angle + 90));
	D3DXVec3TransformNormal(&m_front, &m_front, &mtxR);
	D3DXVec3TransformNormal(&m_right, &m_right, &mtxR);
	m_mtxWorld = m_mtxTranslation;
	//	m_mtxWorld = mtxR * m_mtxTranslation;


	D3DXMatrixTranslation(&m_mtxTranslation, mtx._41, mtx._42, mtx._43);//X,Y,Z��n��
	D3DXMatrixScaling(&m_mtxScaling, WHEEL_SCALE, WHEEL_SCALE, WHEEL_SCALE * 2);

	m_mtxWorld = m_mtxScaling * m_mtxWorld * mtxR * m_mtxTranslation;
	//m_mtxWorld = m_mtxScaling  * m_mtxWorld * m_mtxTranslation ;
	Thing_Normal_model = GetNormalModel(MODELL_WHEEL);
	Wheel_position = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42 * 3, m_mtxWorld._43);

}

void CTitleKanransya::Update(void)
{
	/*
	//�����Ă���
	if (ferris_flg == true)
	{


	}
	//�Î~
	else
	{

	}
	*/
	if (m_Enable)
	{//�����ŉ�]�v�Z���s��

		rotate_ferris += 4;
		//D3DXMatrixRotationX(&m_mtxRotationYY, D3DXToRadian(-rotate_ferris));

		D3DXMatrixRotationAxis(&m_mtxRotationYY, &m_right, D3DXToRadian(-rotate_ferris));
		D3DXVec3TransformNormal(&m_up, &m_up, &m_mtxRotationYY);
		//D3DXVec3TransformNormal(&m_front, &m_front, &m_mtxRotationYY);
		D3DXMatrixRotationY(&m_mtxRotationY, D3DXToRadian(angle));
		Wheel_position += m_front*SPEED;

		D3DXMatrixScaling(&m_mtxScaling, WHEEL_SCALE, WHEEL_SCALE, WHEEL_SCALE * 2);
		D3DXMATRIX mtxT;
		D3DXMatrixTranslation(&mtxT, move.x, move.y, move.z);
		D3DXMatrixTranslation(&m_mtxTranslation, Wheel_position.x, Wheel_position.y, Wheel_position.z);

		m_mtxWorld = m_mtxScaling * m_mtxRotationY * m_mtxRotationYY * m_mtxTranslation;

		Thing_Normal_model.vPosition = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);

		if (m_DrawCheck)
		{
			OrnamentDamage();
			//EnemyDamage();
		}
		if (90.0*90.0 < (m_mtxWorld._41*m_mtxWorld._41) + (m_mtxWorld._43 * m_mtxWorld._43))
		{
			StopSound(WHEEL_SE);
			m_Enable = false;
			C3DObj_delete();
		}
	}

}

void CTitleKanransya::Draw(void)
{
	//DebugFont_Draw(900, 30, "ugoki = %f\n,", ugoki);
	//DebugFont_Draw(900, 60, "Bugoki = %d\n,", Bugoki);
	if (m_Enable)
	{
		m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		DrawDX_Normal(m_mtxWorld, MODELL_WHEEL, &Thing_Normal_model);
	}
}

void CTitleKanransya::Finalize(void)
{
	//Attraction_Finalize(m_AttractionIndex);
	delete this;
}

void CTitleKanransya::EnemyDamage(void)
{
	int i;
	C3DObj *enemy;
	THING *thingenemy;
	for (i = 0; i < MAX_GAMEOBJ; i++)
	{
		enemy = CEnemy::Get_Enemy(i);
		if (enemy)
		{
			if (enemy->Get_DrawCheck())
			{
				Thing_Normal_model.vPosition = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);
				thingenemy = enemy->GetAnimeModel();
				if (C3DObj::Collision_AnimeVSNormal(thingenemy, &Thing_Normal_model))
				{
					enemy->DamageFlag_Change();
					enemy->Position_Keep(m_mtxWorld);
				}
			}
		}
	}
}