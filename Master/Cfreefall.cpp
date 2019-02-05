//////////////////////////////////////////////////
////
////	アトラクション(フリーフォール)クラス
////
//////////////////////////////////////////////////

//=============================================================================
//	インクルードファイル
//=============================================================================

#include "Cfreefall.h"
#include "Cplayer.h"
#include "debug_font.h"
#include "BSphere.h"
//=============================================================================
//	定数定義
//=============================================================================
#define SPEED (0.05f)
#define SIZE (0.8f)
#define FREEFALL_HP (40)
#define FREEFALL_MP (1)
#define FREEFALL_ATK (1)
#define SCORE (1)
#define FREEFALL_SCALE (1)
//=============================================================================
//	静的変数
//=============================================================================

#define FREEFALL_UP		(25.0f)
#define FREEFALL_DOWN	(0.0f)
THING_NORMAL *fall;
/*static float ugoki;//円盤の上下の動き
static bool Bugoki = false;
static float moveY = 0.0f;//円盤の座標
static int CoolTime = 0;//クールタイム*/
//=============================================================================
//	グローバル変数
//=============================================================================

//=============================================================================
//	生成
//=============================================================================
Cfreefall::Cfreefall(D3DXMATRIX mtxWorld) :CAttraction(AT_FALL), C3DObj(AT_FALL)
{
	Initialize(mtxWorld);
}

Cfreefall::~Cfreefall()
{

}

void Cfreefall::Initialize(D3DXMATRIX mtxWorld)
{
	m_AttractionIndex = Get_AttractionIndex(AT_ALL);
	m_Enable = true;
	Bugoki = false;
	ugoki = 0.0f;
	CoolTime = 0;
	moveY = 0.0f;
	m_Hp = FREEFALL_HP;
	m_Mp = FREEFALL_MP;
	m_Attack = FREEFALL_ATK;

	C3DObj *playerget = CPlayer::Get_Player();
	D3DXMATRIX mtx = playerget->Get_mtxWorld();
	D3DXMatrixTranslation(&m_mtxTranslation, mtxWorld._41, 0, mtxWorld._43);//X,Y,Zを渡す
	D3DXMatrixScaling(&m_mtxScaling, FREEFALL_SCALE, FREEFALL_SCALE, FREEFALL_SCALE);
	m_mtxWorld = m_mtxScaling * m_mtxTranslation;
	Thing_Normal_model = GetNormalModel(MODELL_HASIRA);
	fall = GetNormalModel(MODELL_ENBAN);
	Thing_Normal_model->Sphere.vCenter = D3DXVECTOR3(0, 0.0, 0);
	InitSphere(m_pD3DDevice, Thing_Normal_model, D3DXVECTOR3(0, 0.0, 0),3.0f);//当たり判定の変更
}

void Cfreefall::Update(void)
{
	if (m_Enable)
	{//ここで移動計算を行う
		D3DXMatrixTranslation(&m_mtxTranslation, m_mtxWorld._41, ugoki, m_mtxWorld._43);
		D3DXMatrixScaling(&m_mtxScaling, FREEFALL_SCALE, FREEFALL_SCALE, FREEFALL_SCALE);
		D3DXMatrixRotationY(&m_mtxRotation, D3DXToRadian(0));
		m_mtxWorld = m_mtxScaling *m_mtxRotation * m_mtxTranslation;

		if (!Bugoki)
		{
			if (ugoki <= 25.0f)
			{
				ugoki += 0.1f;
			}
			if (ugoki >= 25.0f)
			{
				CoolTime++;
				if (CoolTime >= 120)
				{
					Bugoki = true;
					CoolTime = 0;
				}
			}
		}
		if (Bugoki)
		{
			if (ugoki >= 0.0f)
			{
				ugoki -= 0.5f;
			}
			if (ugoki <= 0.0f)
			{
				CoolTime++;
				if (CoolTime >= 120)
				{
					Bugoki = false;
					CoolTime = 0;
				}
			}
		}

		D3DXMatrixTranslation(&m_mtxTranslation, m_mtxWorld._41, 0, m_mtxWorld._43);
		D3DXMatrixScaling(&m_mtxScaling, FREEFALL_SCALE, FREEFALL_SCALE, FREEFALL_SCALE);
		D3DXMatrixRotationY(&m_mtxRotation, D3DXToRadian(0));
		m_mtxWorld2 = m_mtxScaling * m_mtxRotation * m_mtxTranslation;

	}
}

void Cfreefall::Draw(void)
{
	//	DebugFont_Draw(800, 30, "ugoki = %f\n,", ugoki);
	//	DebugFont_Draw(800, 60, "Bugoki = %d\n,", Bugoki);
	if (m_Enable)
	{

		Thing_Normal_model->vPosition = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);
		fall->vPosition = D3DXVECTOR3(m_mtxWorld2._41, m_mtxWorld2._42, m_mtxWorld2._43);
		m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		DrawDX_Normal(m_mtxWorld2, MODELL_HASIRA, Thing_Normal_model);
		DrawDX_Normal(m_mtxWorld,  MODELL_ENBAN, fall);
	}
}

void Cfreefall::Finalize(void)
{
	Attraction_Finalize(m_AttractionIndex);
}