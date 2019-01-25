
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
//=============================================================================
//	定数定義
//=============================================================================


//=============================================================================
//	グローバル宣言
//=============================================================================
static bool g_bend;				//	フェードインアウトフラグ
//=============================================================================
//	初期化処理
//=============================================================================
void Game_Initialize(void)
{
	g_bend = false;
/*	CPhysx::CPhysX_Initialize();			//	物理演算処理の初期化
	gScene = CPhysx::Get_PhysX_Scene();		//	シーン初期化*/
	
	C3DObj::InitModelLoad();

	CPlayer::PlayerCreate();				//	プレイヤー生成		
	CLight::Light_Create();					//	ライト生成
	CCamera::Camera_Create();				//	カメラ生成

	CMeshField::MeshField_Create(CTexture::TEX_FLORR, 120.0f, 1, 1);							//	地面生成
	CMeshField_Cylinder::MeshField_Cylinder_Create(CTexture::TEX_FLORR, 6.0f, 45.0f, 20, 1);	//	カベ生成
	CMesh_SkyDome::Mesh_SkyDome_Create(CTexture::TEX_SKY, 2.0f, 60.0f, 40, 20);					//	空生成
	CUserInterFace::UICreate();				//	UI生成
	CEnemy::Create();						//	敵生成




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
	
	CEnemy::Create();		//	エネミー生成

	if (GAMEEND <= CGameObj::Get_FraemCount())		//	FraemCountがGAMEENDになるまでカウントUP　なったら終了
	{
		if (!g_bend)
		{
				Fade_Start(true, 3, 0, 0, 0);
				g_bend = true;
		}
		else
		{
				Fade_Start(false, 3, 0, 0, 0);
				Scene_Change(SCENE_INDEX_RESULT);
		}
	}
	else
	{
		CGameObj::FrameCountUp();
	}

}

//=============================================================================
//	描画処理
//=============================================================================

void Game_Draw(void)
{
	C3DObj::DrawAll();		//	3Dオブジェクト描画
	CGameObj::DrawAll();	//	2Dオブジェクト描画

	//C3DObj::HitCheck();
}


