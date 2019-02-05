//////////////////////////////////////////////////
////
////	アトラクション(観覧車)クラス
////
//////////////////////////////////////////////////

//=============================================================================
//	インクルードファイル
//=============================================================================

#include "Cwheel.h"
#include "Cplayer.h"
#include "debug_font.h"
#include "CEnemy.h"
#include "CEnemy_Small.h"
//=============================================================================
//	定数定義
//=============================================================================
#define SPEED (0.5f)
#define SIZE (0.8f)
#define WHEEL_HP (40)
#define WHEEL_MP (1)
#define WHEEL_ATK (1)
#define SCORE (1)
#define WHEEL_SCALE (2)
//=============================================================================
//	静的変数
//=============================================================================

//=============================================================================
//	グローバル変数
//=============================================================================

//=============================================================================
//	生成
//===========
Cwheel::Cwheel() :CAttraction(AT_WHEEL), C3DObj(AT_WHEEL)
{
	Initialize();
}

Cwheel::~Cwheel()
{

}

void Cwheel::Initialize()
{
	m_AttractionIndex = Get_AttractionIndex(AT_ALL);

	m_Enable = true;
	ferris_flg = true;
	ferris_counter = 0;
	rotate_ferris = 0;
	m_Hp = WHEEL_HP;
	m_Mp = WHEEL_MP;
	m_Attack = WHEEL_ATK;

	C3DObj *playerget = CPlayer::Get_Player();	//	プレイヤー取得
	move = playerget->Get_Front();

	D3DXMATRIX mtx = playerget->Get_mtxWorld();
	D3DXMatrixTranslation(&m_mtxTranslation, mtx._41, mtx._42, mtx._43);//X,Y,Zを渡す
	D3DXMatrixScaling(&m_mtxScaling, WHEEL_SCALE, WHEEL_SCALE, WHEEL_SCALE);

	angle = (float)(playerget->Get_Angle());
	D3DXMatrixRotationY(&m_mtxRotation, D3DXToRadian(-angle));

	m_mtxWorld = m_mtxScaling * m_mtxRotation * m_mtxTranslation;
	Thing_Normal_model = GetNormalModel(MODELL_WHEEL);
	Wheel_position = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42 * 3, m_mtxWorld._43);
	Thing_Normal_model->vPosition = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);
}

void Cwheel::Update(void)
{
	//動いてる状態
	if (ferris_flg == true)
	{


	}
	//静止
	else
	{

	}

	if (m_Enable)
	{//ここで回転計算を行う

		rotate_ferris += 4;
		D3DXMatrixRotationX(&mtxR, D3DXToRadian(-rotate_ferris));
		Wheel_position += move*SPEED;

		D3DXMatrixScaling(&m_mtxScaling, WHEEL_SCALE, WHEEL_SCALE, WHEEL_SCALE);
		D3DXMATRIX mtxT;
		D3DXMatrixTranslation(&mtxT, move.x, move.y, move.z);
		D3DXMatrixTranslation(&m_mtxTranslation, Wheel_position.x, Wheel_position.y, Wheel_position.z);
		m_mtxWorld = m_mtxScaling * mtxR * m_mtxRotation * m_mtxTranslation;

		if (45.0*45.0 < (m_mtxWorld._41*m_mtxWorld._41) + (m_mtxWorld._43 * m_mtxWorld._43))
		{
			m_Enable = false;
			CPlayer::m_delete = true;
		}

	}
}

void Cwheel::Draw(void)
{
	//DebugFont_Draw(900, 30, "ugoki = %f\n,", ugoki);
	//DebugFont_Draw(900, 60, "Bugoki = %d\n,", Bugoki);
	if (m_Enable)
	{
		Thing_Normal_model->vPosition = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);
		m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		DrawDX_Normal(m_mtxWorld, MODELL_WHEEL, Thing_Normal_model);
	}
}

void Cwheel::Finalize(void)
{
	Attraction_Finalize(m_AttractionIndex);
}

void Cwheel::EnemyDamage(void)
{
	for (int i = 0; i < MAX_GAMEOBJ; i++)
	{
		C3DObj *enemy = CEnemy::Get_Enemy(i);
		if (enemy)
		{
			Thing_Normal_model->vPosition = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);
			THING *thingenemy = enemy->GetAnimeModel();
			int hp = enemy->Get_Hp();
			if (C3DObj::Collision_AnimeVSNormal(thingenemy, Thing_Normal_model))
			{
				hp--;
				//Animation_Change(PLAYER_WALK, 0.05);
			}
		}
	}
}