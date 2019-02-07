//////////////////////////////////////////////////
////
////	エネミー(ビッグ)クラス
////
//////////////////////////////////////////////////

//=============================================================================
//	インクルードファイル
//=============================================================================

#include "CEnemy_Big.h"
#include "Cplayer.h"
#include "input.h"
#include "CSkinAnimation.h"
#include "debug_font.h"
//=============================================================================
//	定数定義
//=============================================================================

#define SPECIAL_SIZE (0.8f)
#define SPECIAL_ATTACK (1)
#define SPECIAL_HP (1)
#define SPECIAL_MP (2)
#define SPECIAL_SCORE (1)

enum ANIMATION {
	
	WALK,
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

CEnemy_Big::CEnemy_Big(ENEMY_EMITTER *Emitter) :CEnemy(TYPE_BIG), C3DObj(C3DObj::TYPE_ENEMY)
{
	Initialize(Emitter);
}

//=============================================================================
//	破棄
//=============================================================================

CEnemy_Big::~CEnemy_Big()
{

}

void CEnemy_Big::Initialize(ENEMY_EMITTER *Emitter)
{


	SkinMesh.InitThing(m_pD3DDevice, &Thing, ANIME_MODEL_FILES[MODELL_ANIME_BIG].filename);
	Thing.Sphere.fRadius = 1.3;
	Thing.Sphere.vCenter = D3DXVECTOR3(0, 1.2, 0);
	SkinMesh.InitSphere(m_pD3DDevice, &Thing);

	m_EnemyIndex = Get_EnemyIndex(TYPE_ALL);
	//モデル情報取得
	//Thing_Anime_model = GetAnimeModel();
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
	m_Hp = SPECIAL_HP;
	m_Attack = SPECIAL_ATTACK;
	m_Score = SPECIAL_SCORE;
	m_Direction = Emitter->InitDirection;

	D3DXMatrixTranslation(&m_mtxTranslation, Emitter->InitPos.x, Emitter->InitPos.y, Emitter->InitPos.z);
	D3DXMatrixScaling(&m_mtxScaling, 1, 1, 1);
	m_mtxWorld = m_mtxScaling * m_mtxTranslation;

	Thing.vPosition = D3DXVECTOR3(m_mtxTranslation._41, m_mtxTranslation._42, m_mtxTranslation._43);
}


void CEnemy_Big::Finalize(void)
{

	Enemy_Finalize(m_EnemyIndex);

}


void CEnemy_Big::Update(void)
{
	if (m_Enable)
	{
		if (m_Hp > 0)
		{
			if (m_DrawCheck)
			{
				if (!PlayerCheck())
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
						D3DXMatrixTranslation(&mtxtrans, m_EnemyMove[m_Direction].Move.x * BIG_SPEED, m_EnemyMove[m_Direction].Move.y * BIG_SPEED, m_EnemyMove[m_Direction].Move.z * BIG_SPEED);
						m_mtxTranslation *= mtxtrans;

						if (m_FrameCount - m_TimeKeep >= 60 * m_Movetime)
						{
							m_MoveCheck = false;
						}
					}
				}
				else
				{
					C3DObj *pplayer = CPlayer::Get_Player();
					D3DXMATRIX playerworld = pplayer->Get_mtxWorld();
					float x = playerworld._41 - m_mtxWorld._41;
					float z = playerworld._43 - m_mtxWorld._43;

					D3DXMATRIX mtxtrans;
					D3DXMatrixTranslation(&mtxtrans, x * 0.015f, 0.0f, z * 0.015f);
					m_mtxTranslation *= mtxtrans;

					float angle = (float)(atan2(-z, x));
					D3DXMatrixRotationY(&m_mtxRotation, angle);

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
			}
			else
			{
				if (m_MoveCheck)
				{
					D3DXMATRIX mtxtrans;
					D3DXMatrixTranslation(&mtxtrans, m_EnemyMove[m_Direction].Move.x * BIG_SPEED, m_EnemyMove[m_Direction].Move.y * BIG_SPEED, m_EnemyMove[m_Direction].Move.z * BIG_SPEED);
					m_mtxTranslation *= mtxtrans;

					if (m_FrameCount - m_TimeKeep >= 180)
					{
						m_MoveCheck = false;
						m_Direction += 2;
					}
				}
				else
				{
					float angle = (float)(atan2(-m_mtxWorld._43, -m_mtxWorld._41));
					D3DXMatrixRotationY(&m_mtxRotation, angle);
					D3DXVECTOR3 move = (D3DXVECTOR3((float)(cos(angle)), 0.0f, (float)(sin(angle))));

					D3DXMATRIX mtxtrans;
					D3DXMatrixTranslation(&m_mtxTranslation, m_mtxWorld._41 + move.x, m_mtxWorld._42, m_mtxWorld._43 + move.z);

				}
			}
		}

		m_mtxWorld = m_mtxScaling * m_mtxRotation * m_mtxTranslation;




		if (45.0*45.0 < (m_mtxWorld._41*m_mtxWorld._41) + (m_mtxWorld._43 * m_mtxWorld._43))
		{
			if (m_Hp <= 0)
			{
				m_Enable = false;
				CPlayer::m_delete = true;
			}
			else
			{
				m_DrawCheck = false;
			}
		}
		else
		{
			m_DrawCheck = true;
		}
	}


}



void CEnemy_Big::Draw(void)
{

	if (m_Enable)
	{
		if (m_DrawCheck)
		{//当たり判定位置更新
			m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);	//　ライティング有効
			Thing.vPosition = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);
			DrawDX_Anime(m_mtxWorld, MODELL_ANIME_SMALL, &Thing);
			m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);	//　ライティング有効
		}
	}
	C3DObj::HitCheck();
	DebugFont_Draw(500, 400, "%d", TrackDesc.Speed);
}


void CEnemy_Big::Damage(void)
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




