
//=============================================================================
//	インクルードファイル
//=============================================================================
#define NOMINMAX

#include "CLight.h"
#include "CCamera.h"
#include "CMeshField.h"
#include "CMeshField_Cylinder.h"
#include "CMesh_SkyDome.h"
#include "Cplayer.h"
#include "billboard.h"
#include "CEnemy.h"
#include "fade.h"
#include "scene.h"
#include "CUserInterface.h"
#include "CAttraction.h"
#include "common.h"
#include "exp.h"
#include "shadow.h"
#include "COrnament.h"
#include "sound.h"
//=============================================================================
//	定数定義
//=============================================================================


//=============================================================================
//	グローバル宣言
//=============================================================================
static bool g_bend;				//	フェードインアウトフラグ
static bool g_gameend;
static float EnemyPer;
//=============================================================================
//	初期化処理
//=============================================================================
void Game_Initialize(void)
{
	g_bend = false;
	g_gameend = false;
	/*	CPhysx::CPhysX_Initialize();			//	物理演算処理の初期化
	gScene = CPhysx::Get_PhysX_Scene();		//	シーン初期化*/

	C3DObj::InitModelLoad();

	CPlayer::PlayerCreate();				//	プレイヤー生成		
	CLight::Light_Create();					//	ライト生成
	CCamera::Camera_Create();				//	カメラ生成

	CMeshField::MeshField_Create(CTexture::TEX_KUSA_RENGA, 120.0f, 2, 2);							//	地面生成
	//CMeshField_Cylinder::MeshField_Cylinder_Create(CTexture::TEX_FLORR, 10.0f, SYLINDERSIZE, 20, 1,true);	//	内カベ生成
	CMeshField_Cylinder::MeshField_Cylinder_Create(CTexture::TEX_MOUNTAIN, 10.0f, FIELDSIZE, 20, 1, false);	//	外カベ生成
	CMesh_SkyDome::Mesh_SkyDome_Create(CTexture::TEX_SKY, 2.0f, SKYSIZE, 40, 20);					//	空生成
	CUserInterFace::UICreate();				//	UI生成
	CEnemy::Create();						//	敵生成
	COrnament::Create();						//	オブジェクト生成
	Shadow_Initialize();
	PlaySound(MAIN_BGM);
}

//=============================================================================
//	終了処理
//=============================================================================

void Game_Finalize(void)
{
	C3DObj::DeleteAll();			//	3Dオブジェクト全消去
	CGameObj::DeleteAll2D();			//	2Dオブジェクト全消去
	C3DObj::Model_Finalize();
	CGameObj::FrameCountReset();	//	フレームカウントリセット
}

//=============================================================================
//	更新処理
//=============================================================================

void Game_Updata(void)
{
	C3DObj::UpdateAll();	//	3Dオブジェクト更新
	CGameObj::UpdateAll();	//	2Dオブジェクト更新
	//COrnament::Create();    //  オブジェクト生成
	EnemyPer = 1.0f - (float)CEnemy::Get_EnemyNum(0) / CEnemy::Get_EnemyMaxNum(); //敵の数を取得
	if (g_gameend)		//	FraemCountがGAMEENDになるまでカウントUP　なったら終了
	{
		if (!g_bend)
		{
			Fade_Start(true, 1, 0, 0, 0);
			g_bend = true;
		}
		else
		{
			if (!Fade_IsFade())
			{
				Fade_Start(false, 1, 0, 0, 0);
				StopSound(MAIN_BGM);
				Scene_Change(SCTNE_INDEX_SCORE);
				PlaySound(GAME_END_SE);
			}
		}
	}
	else
	{
		CGameObj::FrameCountUp();
		if (GAMEEND <= CGameObj::Get_FraemCount())
		{
			g_gameend = true;
		}
	}
	Exp_Update();

	
}

//=============================================================================
//	描画処理
//=============================================================================

void Game_Draw(void)
{
	C3DObj::DrawAll();		//	3Dオブジェクト描画
	CGameObj::DrawAll();	//	2Dオブジェクト描画
	Exp_Draw();
	Shadow_Draw();
	//C3DObj::HitCheck();
}


void Game_End(void)
{
	g_gameend = true;
}

float Get_EnemyPer(void)
{
	return EnemyPer;
}