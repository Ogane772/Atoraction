//////////////////////////////////////////////////
////
////	エネミー(スモール)クラス
////
//////////////////////////////////////////////////

//=============================================================================
//	インクルードファイル
//=============================================================================

#include "CEnemy_Small.h"
#include "Cplayer.h"
#include "input.h"
#include "CSkinAnimation.h"
#include "debug_font.h"
//=============================================================================
//	定数定義
//=============================================================================

#define SMALL_SIZE (0.8f)
#define SMALL_ATTACK (1)
#define SMALL_HP (1)
#define SMALL_MP (2)
#define SMALL_SCORE (1)
//エネミースモールのアニメーション番号定義
enum ANIMATION {
	STOP,
	WALK,
	DASH,
	ATTACK,
	DEATH,

	ANIME_MAX
};
//=============================================================================
//	静的変数
//=============================================================================


//=============================================================================
//	グローバル変数
//=============================================================================

//=============================================================================
//	生成
//=============================================================================

CEnemy_Small::CEnemy_Small(ENEMY_EMITTER *Emitter):CEnemy(TYPE_SMALL),C3DObj(C3DObj::TYPE_ENEMY)
{
	Initialize(Emitter);
}

//=============================================================================
//	破棄
//=============================================================================

CEnemy_Small::~CEnemy_Small()
{

}


void CEnemy_Small::EnemySmall_Create(void)
{

}

//=============================================================================
//	初期化
//=============================================================================

void CEnemy_Small::Initialize(ENEMY_EMITTER *Emitter)
{


	SkinMesh.InitThing(m_pD3DDevice, &Thing, ANIME_MODEL_FILES[MODELL_ANIME_SMALL].filename);
	Thing.Sphere.fRadius = 1.3;
	Thing.Sphere.vCenter = D3DXVECTOR3(0, 1.2, 0);
	SkinMesh.InitSphere(m_pD3DDevice, &Thing);

	m_EnemyIndex = Get_EnemyIndex(TYPE_ALL);
	//モデル情報取得
	//アニメーショントラックを得る
	for (DWORD i = 0; i < Thing.pAnimController->GetNumAnimationSets(); i++)
	{//AnimSetにアニメーション情報格納
		Thing.pAnimController->GetAnimationSet(i, &pAnimSet[i]);
	}

	
	//アニメーション情報初期化
	TrackDesc.Weight = 1;
	TrackDesc.Enable = true;
	TrackDesc.Position = 0;//アニメーションタイムリセット
	TrackDesc.Speed = 0.001f;//モーションスピード
	Thing.pAnimController->SetTrackDesc(0, &TrackDesc);//アニメ情報セット
	Thing.pAnimController->SetTrackAnimationSet(0, pAnimSet[WALK]);//初期アニメーションセット
	m_Enable = true;
	m_MoveCheck = false;
	m_DrawCheck = true;
	m_Hp = SMALL_HP;
	m_Attack = SMALL_ATTACK;
	m_Score = SMALL_SCORE;
	m_Direction = Emitter->InitDirection;
	
	D3DXMatrixTranslation(&m_mtxTranslation, Emitter->InitPos.x, Emitter->InitPos.y, Emitter->InitPos.z);
	D3DXMatrixScaling(&m_mtxScaling, 1, 1, 1);
	m_mtxWorld = m_mtxScaling * m_mtxTranslation;

	Thing.vPosition = D3DXVECTOR3(m_mtxTranslation._41, m_mtxTranslation._42, m_mtxTranslation._43);
}

//=============================================================================
//	終了処理
//=============================================================================
void CEnemy_Small::Finalize(void)
{
	
	Enemy_Finalize(m_EnemyIndex);
	
}

//=============================================================================
//	更新処理
//=============================================================================
void CEnemy_Small::Update(void)
{
	if (m_Hp > 0)
	{
		if (Draw_Check())	//	範囲内にいるか
		{
			if (!PlayerCheck())	//	近くにプレイヤーがいるか
			{
				Small_Move();
			}
			else
			{
				Chase_Player();

				Small_Attack();

			}
		}
		else
		{
			Comeback_Move(SMALL_SPEED);
		}
	}

	m_mtxWorld = m_mtxScaling * m_mtxRotation * m_mtxTranslation;





}

	



//=============================================================================
//	描画処理
//=============================================================================
void CEnemy_Small::Draw(void)
{
	
	if (m_Enable)
	{
		if (m_DrawCheck)
		{//当たり判定位置更新
			
			Thing.vPosition = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);
			DrawDX_Anime(m_mtxWorld, MODELL_ANIME_SMALL, &Thing);
		}
	}
	
	//DebugFont_Draw(500, 400, "%d", TrackDesc.Speed);
}

//=============================================================================
//	ダメージ処理
//=============================================================================
void CEnemy_Small::Damage(void)
{
	
	if (m_Hp > 0)
	{
		m_Hp -= 1;
		if (m_Hp == 0)
		{
			CPlayer::Add_KoCount();
		}
	}
}

//=============================================================================
//	移動処理
//=============================================================================
void CEnemy_Small::Small_Move(void)
{
	if (!m_MoveCheck)
	{
		m_Direction++;
		if (m_Direction >= 9)
		{
			m_Direction = 0;
		}
		Animation_Change(WALK, 0.001);
		D3DXMatrixRotationY(&m_mtxRotation, m_EnemyMove[m_Direction].Angle);
		m_TimeKeep = m_FrameCount;
		m_Movetime = rand() % 3 + 1;
		m_MoveCheck = true;
	}
	else
	{

		D3DXMATRIX mtxtrans;
		D3DXMatrixTranslation(&mtxtrans, m_EnemyMove[m_Direction].Move.x * SMALL_SPEED, m_EnemyMove[m_Direction].Move.y * SMALL_SPEED, m_EnemyMove[m_Direction].Move.z * SMALL_SPEED);
		m_mtxTranslation *= mtxtrans;

		if (m_FrameCount - m_TimeKeep >= 60 * m_Movetime)
		{
			m_MoveCheck = false;
		}
	}
}

//=============================================================================
//	攻撃処理
//=============================================================================
void CEnemy_Small::Small_Attack(void)
{
	if (!m_AttackCheck)
	{
		m_AttackTime = m_FrameCount;
		m_AttackCheck = true;

		Animation_Change(ATTACK, 0.05);
	}
	else
	{
		if (m_FrameCount - m_AttackTime >= 350)
		{

			m_AttackCheck = false;
			m_AttackTime = 0;
		}
	}
}
