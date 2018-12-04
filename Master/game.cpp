
//=============================================================================
//	インクルードファイル
//=============================================================================
#define NOMINMAX
#include "cube.h"
#include "grid.h"
#include "CLight.h"
#include "CCamera.h"
#include "model.h"
#include "CMeshField.h"
#include "CMeshField_Cylinder.h"
#include "CMesh_SkyDome.h"
#include "Cplayer.h"
#include "billboard.h"
#include "Cphysx.h"
#include "CEnemy.h"
#include "fade.h"
#include "scene.h"
#include "CUserInterface.h"
#include "CAttraction.h"
#include "common.h"
#include "map.h"
//=============================================================================
//	定数定義
//=============================================================================

#define MAX_GAMEOBJ (100)


//=============================================================================
//	グローバル宣言
//=============================================================================

CGameObj *pGameObj[MAX_GAMEOBJ];
CUserInterFace *pUI;
MapObj *pMap;
//int ObjNum = 0;
static NxScene*	gScene = NULL;	//	フィジックスのシーン登録
static bool g_bend;
//=============================================================================
//	初期化処理
//=============================================================================
void Game_Initialize(void)
{
	g_bend = false;
	CPhysx::CPhysX_Initialize();	//	物理演算処理の初期化
	gScene = CPhysx::Get_PhysX_Scene();
	CGameObj::Initialize();
	CAttraction::Attraction_Initialize();

	pGameObj[CGameObj::Get_GameObjIndex()] = CPlayer::PlayerCreate();
	pGameObj[CGameObj::Get_GameObjIndex()] = CLight::Light_Create();
	pGameObj[CGameObj::Get_GameObjIndex()] = CCamera::Camera_Create();
	pGameObj[CGameObj::Get_GameObjIndex()] = CMeshField::MeshField_Create(CTexture::TEX_FLORR, 120.0f, 1, 1);
	pGameObj[CGameObj::Get_GameObjIndex()] = CMeshField_Cylinder::MeshField_Cylinder_Create(CTexture::TEX_FLORR, 6.0f, 45.0f, 20, 1);
	pGameObj[CGameObj::Get_GameObjIndex()] = CMesh_SkyDome::Mesh_SkyDome_Create(CTexture::TEX_SKY, 2.0f, 60.0f, 40, 20);
	pUI = new CUserInterFace();
	pMap = new MapObj();
	/*for (int i = 0; i < CEnemy::Get_EnemyMaxNum(); i++)
	{
		pGameObj[CGameObj::Get_GameObjIndex()] = CEnemy::Create(i);
	}*/
	for (int i = 0; i < CEnemy::Get_EnemyMaxNum(); i++)
	{
		if (CEnemy::Create(i))
		{
			pGameObj[CGameObj::Get_GameObjIndex()] = CEnemy::Get_Enemy(CEnemy::Get_EnemyNum(CEnemy::TYPE_ALL) - 1);
		}
	}

//	BillBoard_Initialize();

}

//=============================================================================
//	終了処理
//=============================================================================

void Game_Finalize(void) 
{
	int end = CGameObj::Get_GameObjNum();
	for (int i = 0;i < end;i++)
	{
		if (pGameObj[i])
		{
			pGameObj[i]->Finalize();
			pGameObj[i] = NULL;
		}
	}
	CPhysx::ExitNx();
}

//=============================================================================
//	更新処理
//=============================================================================

void Game_Updata(void)
{
	

	for (int i = 0;i < CGameObj::Get_GameObjNum();i++)
	{
		if (pGameObj[i])
		{
			pGameObj[i]->Update();
			if (CAttraction::Get_CreateCheck())
			{
				pGameObj[CGameObj::Get_GameObjIndex()] = CAttraction::Get_Attraction(CAttraction::Get_AttractionIndex(CAttraction::TYPE_ALL));
			}
			if (CPlayer::m_delete)
			{

				for (int i = 0;i < CGameObj::Get_GameObjNum();i++)
				{
					if (pGameObj[i])
					{
						if (!pGameObj[i]->Get_Enable())
						{
							pGameObj[i]->Finalize();
							pGameObj[i] = NULL;
						}
					}
				}
				CPlayer::m_delete = false;
			}
		}
	}

	for (int i = 0; i < CEnemy::Get_EnemyMaxNum(); i++)
	{
		if (CEnemy::Create(i))
		{
			pGameObj[CGameObj::Get_GameObjIndex()] = CEnemy::Get_Enemy(CEnemy::Get_EnemyNum(CEnemy::TYPE_ALL) - 1);
		}
	}

	if (GAMEEND <= CGameObj::Get_FraemCount())
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

	pMap->Update();
}

//=============================================================================
//	描画処理
//=============================================================================

void Game_Draw(void)
{
	
	for (int i = 0;i < CGameObj::Get_GameObjNum();i++)
	{
		if (pGameObj[i])
		{
			pGameObj[i]->Draw();
		}
	}

	/*CCamera *c = CCamera::Get_CCamera();
	c->DebugDraw();
	CGameObj::DebugDraw();


	//BillBoard_Draw();

	/*for (int i = 0;i < 4;i++)
	{
		BillBoard_Draw(i,3,0);
	}*/
	pUI->Draw();
	pMap->Draw();

	gScene->flushStream();
	gScene->fetchResults(NX_RIGID_BODY_FINISHED, true);
}
