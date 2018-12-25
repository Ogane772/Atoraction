//=============================================================================
//
//	Playerクラス
//
//=============================================================================

//=============================================================================
//	インクルードファイル
//=============================================================================

#include "Cplayer.h"
#include "input.h"
#include "move.h"
#include "CAttraction.h"
#include "debug_font.h"

#include "CEnemy.h"
#include "Cwheel.h"
#include "CEnemy_Small.h"
#include "CAttraction_Coaster .h"
#include "CAttraction_Popcorn.h"
#include "gamepad.h"
//=============================================================================
//	定数定義
//=============================================================================
#define SPEED (0.2)
#define PLAYER_SAIZ (1)
#define MPSTOCK_INIT (5)
#define ANGLE (3)
//=============================================================================
//	静的変数
//=============================================================================
//コントローラーに使う変数
static DIJOYSTATE2 js;
static LPDIRECTINPUTDEVICE8 pJoyDevice;
static HRESULT hr;
//D3DXMATRIX CPlayer::m_mtxWorld;
CPlayer *CPlayer::m_pPlayer[PLAYER_MAX] = {};
int CPlayer::m_PlayerNum = 0;
int CPlayer::m_KO_Count = 0;
bool CPlayer::m_delete = false;
//=============================================================================
// 生成
//=============================================================================
CPlayer::CPlayer():C3DObj(C3DObj::TYPE_PLAYER)
{
	Player_Initialize();
	m_PlayerIndex = m_PlayerNum;
	m_PlayerNum++;
}

CPlayer *CPlayer::PlayerCreate(void)
{
	//m_pPlayer[m_PlayerNum-1] = new CPlayer;
	//return m_pPlayer[m_PlayerNum - 1];
	CPlayer *m_pPlayer = new CPlayer;
	return m_pPlayer;
}


//=============================================================================
// 破棄
//=============================================================================
CPlayer::~CPlayer()
{
	//Player_Finalize();
	m_PlayerNum--;
}

//=============================================================================
// 更新
//=============================================================================
void CPlayer::Update(void)
{
	//コントローラー情報があるときのみ取得
	if (pJoyDevice)
	{
		pJoyDevice->GetDeviceState(sizeof(DIJOYSTATE2), &js);
	}
	/////////////////////////////
	if (g_CosterMode)//コースターの時
	{
		C3DObj *pcoaster = Coaster::Get_Coaster();
		if (pcoaster)
		{
			m_mtxTranslation *= Move(FLONT, SPEED);
		}
		else
		{
			g_CosterMode = false;
		}
	}
	else
	{
		//十字キーあるいはスティックにより移動
		
		if (Keyboard_IsPress(DIK_W) || js.lY <= -3)
		{
			if ((m_Angle < 180) && (m_Angle >= 0))
			{
				AngleChange(true);
			}
			if ((m_Angle > 180) && (m_Angle <= 360))
			{
				AngleChange(false);
			}
			m_mtxTranslation *= Move(FLONT, SPEED);
		}
		if (Keyboard_IsPress(DIK_S) || js.lY >= 3)
		{
			if ((m_Angle > 0) && (m_Angle < 180))
			{
				AngleChange(false);
			}
			if ((m_Angle < 360) && (m_Angle >= 180))
			{
				AngleChange(true);
			}
			m_mtxTranslation *= Move(BACK, SPEED);
		}
		if (Keyboard_IsPress(DIK_D) || js.lX >= 3)
		{
			if ((m_Angle < 90) || (m_Angle > 270))
			{
				AngleChange(false);
			}
			if ((m_Angle >= 90) && (m_Angle < 270))
			{
				AngleChange(true);
			}

			m_mtxTranslation *= Move(RIGHT, SPEED);
		}
		if (Keyboard_IsPress(DIK_A) || js.lX <= -3)
		{
			if ((m_Angle > 90) && (m_Angle <= 270))
			{
				AngleChange(false);
			}
			if ((m_Angle < 90) || (m_Angle > 270))
			{
				AngleChange(true);
			}

			m_mtxTranslation *= Move(LEFT, SPEED);
		}
		if (Keyboard_IsRelease(DIK_O))
		{
			CAttraction::Create(CAttraction::TYPE_COFFEE);
		}
		if (Keyboard_IsRelease(DIK_I))
		{
			CAttraction::Create(CAttraction::TYPE_FALL);
		}
		if (Keyboard_IsRelease(DIK_U))
		{
			CAttraction::Create(CAttraction::TYPE_WHEEL);
		}
		if (Keyboard_IsTrigger(DIK_P))
		{
			CAttraction::Create(CAttraction::TYPE_COASTER);
			g_CosterMode = true;
		}
		if (Keyboard_IsTrigger(DIK_Y))
		{
			CAttraction::Create(CAttraction::TYPE_POPCORN);
		}
	}
	D3DXMATRIX mtxr;
	D3DXMatrixRotationY(&m_mtxRotation, D3DXToRadian(m_Angle));
	//m_mtxRotation *= mtxr;

	if (45.0*45.0 < (m_mtxTranslation._41*m_mtxTranslation._41) + (m_mtxTranslation._43 * m_mtxTranslation._43))
	{
		m_mtxTranslation = m_mtxKeepTranslation;
	}
	else
	{
		m_mtxKeepTranslation = m_mtxTranslation;
	}

	//	MP
	if (m_FrameCount % 60 == 0)
	{

		m_Mp++;
		if (m_Mp >= MP_MAX)
		{
			m_MpStock++;
			m_Mp = 0;
		}
	}

/*	int atrnum = CAttraction::Get_AttractionNum(CAttraction::TYPE_ALL);
	for (int j = 0;j < atrnum;j++)
	{
		CAttraction *patr = CAttraction::Get_Attraction(j, CAttraction::TYPE_WHEEL);
		if (patr)
		{
			int enemynum = CEnemy::Get_EnemyMaxNum();
			for (int i = 0;i < enemynum;i++)
			{
				CEnemy *penemy = CEnemy_Small::Get_Enemy(i);
				if (penemy)
				{
					NxActor* act = penemy->Get_Actor();
					NxActor* act2 = patr->Get_Actor();
					myData* mydata = (myData*)act2->userData;
					if (mydata->hit)
					{
						penemy->Damage();
						mydata->hit = false;
					}
					NxScene* scene = Get_PhysX_Scene();
					scene->setUserContactReport(new ContactCallBack());
					scene->setActorPairFlags(*act2,
						*act,
						NX_NOTIFY_ON_START_TOUCH | NX_NOTIFY_ON_END_TOUCH);


				}
			}
		}
	}*/
}
//=============================================================================
// 描画
//=============================================================================

void CPlayer::Draw(void)
{
	
	m_mtxWorld = m_mtxScaling * m_mtxRotation * m_mtxTranslation;
	m_SphereCollision.CenterPos = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);

	myData* mydata = (myData*)NxA_pPlayer->userData;

	DrawDX2(m_mtxWorld, NxA_pPlayer, MODELL_PLAYER);

	//	デバッグ
	//DebugFont_Draw(300, 50, "%f\n%f\n%f\n%f", m_front.x, m_front.y, m_front.z, m_Angle);
	//RenderPhysX();
	//コントローラーのスティック取得
	//DebugFont_Draw(300, 50, "X = %ld , Y= %ld", js.lX, js.lY);
	//Debug_Collision(m_SphereCollision, m_mtxTranslation);
}

//	初期化
void CPlayer::Player_Initialize(void)
{
	m_Hp = HP_MAX;
	m_Mp = 0;
	m_MpStock = MPSTOCK_INIT;
	m_KO_Count = 0;
	m_Enable = true;
	m_delete = false;
	g_CosterMode = false;
	D3DXMatrixTranslation(&m_mtxTranslation, 0, 1, 0);
	D3DXMatrixScaling(&m_mtxScaling, 0.5f, 1.0f, 0.5f);
	m_mtxKeepTranslation = m_mtxTranslation;
	D3DXMatrixRotationY(&m_mtxRotation, D3DXToRadian(200));
	m_mtxWorld = m_mtxScaling * m_mtxRotation * m_mtxTranslation;

	m_Angle = 180;
	m_front = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXVec3Normalize(&m_front, &m_front);
	m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVec3Cross(&m_right, &m_front, &m_up);
	D3DXVec3Normalize(&m_right, &m_right);
	D3DXVec3Cross(&m_up, &m_right, &m_front);
	D3DXVec3Normalize(&m_up, &m_up);

	NxMat33 mat1;
	NxVec3 scaleDwarf = NxVec3(1, 1, 1);	//	モデルスケール
	NxVec3 BBDwarf = NxVec3(1.0f, 1.0f, 1.0f);	//	当たり判定の大きさ

	
	NxA_pPlayer = CreateMeshAsSphere(NxVec3(0, 1, 0), 1.0, MODELL_PLAYER);
	/*m_SphereCollision = {
		D3DXVECTOR3(m_mtxWorld._41,m_mtxWorld._42,m_mtxWorld._43),PLAYER_SAIZ
	};*/
	//コントローラー情報取得
	js = { 0 };
	pJoyDevice = *JoyDevice_Get();
	if (pJoyDevice)
	{
		hr = pJoyDevice->Acquire();
	}
}

//	終了処理
void CPlayer::Finalize(void)
{
	for (int i = 0;i < m_PlayerNum;i++)
	{
		if (m_pPlayer[i])
		{
			delete m_pPlayer[i];
		}
	}
}



void  CPlayer::AngleChange(bool Angle_Flg)
{

	if (Angle_Flg == true)
	{
		m_Angle += ANGLE;
		D3DXMATRIX mtxR;
		if (m_Angle > 360)
		{
			m_Angle = m_Angle - 360;
		}
		//引数(&, 軸, angle)
		D3DXMatrixRotationAxis(&mtxR, &m_up, D3DXToRadian(ANGLE));
		D3DXVec3TransformNormal(&m_front, &m_front, &mtxR);
		D3DXVec3TransformNormal(&m_right, &m_right, &mtxR);
	}
	else
	{
		m_Angle += -ANGLE;
		D3DXMATRIX mtxR;
		if (m_Angle < 0)
		{
			m_Angle = 360 - m_Angle;
		}
		//引数(&, 軸, angle)
		D3DXMatrixRotationAxis(&mtxR, &m_up, D3DXToRadian(-ANGLE));
		D3DXVec3TransformNormal(&m_front, &m_front, &mtxR);
		D3DXVec3TransformNormal(&m_right, &m_right, &mtxR);
	}
}


C3DObj *CPlayer::Get_Player(void)
{
	for (int i = 0;i < MAX_GAMEOBJ;i++)
	{
		C3DObj *pplayer = C3DObj::Get(i);
		if (pplayer->Get_3DObjType() == C3DObj::TYPE_PLAYER)
		{
			return pplayer;
		}
	}
}





