//////////////////////////////////////////////////
////
////	フィジックスクラス(物理演算)
////
//////////////////////////////////////////////////

//=============================================================================
//	インクルードファイル
//=============================================================================

#define NOMINMAX
#include <windows.h>
#undef min
#undef max
#include "Cphysx.h"
#include "input.h"
#include <mmsystem.h>
#include <d3dx9.h>
#pragma warning( disable : 4996 ) 
#include <strsafe.h>
#pragma warning( default : 4996 )
#include "ErrorStream.h"
#include "CAttraction.h"
#include "debug_font.h"
#include "BSphere.h"
#include "CSkinAnimation.h"
#include "Cplayer.h"
#include "CEnemy.h"
#include "CEnemy_Small.h"
//=============================================================================
//	定数定義
//=============================================================================


//=============================================================================
//	静的変数
//=============================================================================

//	使いたいノーマルモデルの数だけ書く
CPhysx::ModelFileData CPhysx::m_NormalModelFileData[] = {
	{},
	{ "asset/model/emi-ru2.x" },
	{ "asset/model/zako.x" },
	{ "asset/model/boss.x" },
	{ "asset/model/CoffeeCup.blend.x" },
	{ "asset/model/dish.blend.x" },
	{ "asset/model/enban.x" },
	{ "asset/model/hasira.x" },
	{ "asset/model/ferris.x" },
	{ "asset/model/jet.x" },
	{ "asset/model/cup_blue.x" },
	{ "asset/model/cup_kiiro.x" },
	{ "asset/model/cup_midori.x" },
	{ "asset/model/popcorn.x" },
};
//	使いたいアニメモデルの数だけ書く
CPhysx::ModelFileData CPhysx::m_AnimeModelFileData[] = {
	{ "asset/anime_model/small_enemy.x" },
};
int CPhysx::m_NORMALMODELFAIL_MAX = sizeof(CPhysx::m_NormalModelFileData) / sizeof(m_NormalModelFileData[0]);
int CPhysx::m_ANIMEMODELFAIL_MAX = sizeof(CPhysx::m_AnimeModelFileData) / sizeof(m_AnimeModelFileData[0]);
// PhysXクラス
NxPhysicsSDK* CPhysx::gPhysicsSDK = NULL;
NxScene* CPhysx::gScene = NULL;

LPD3DXMESH CPhysx::g_pMesh[numMesh] = {};
D3DMATERIAL9* CPhysx::g_pMeshMaterials[numMesh] = {};
LPDIRECT3DTEXTURE9* CPhysx::g_pMeshTextures[numMesh] = {};
DWORD CPhysx::g_dwNumMaterials[numMesh] = {};
LPDIRECT3DVERTEXBUFFER9 CPhysx::g_pVB = {};

//NxActor* CPhysx::NxA_pPlayer = {};
//NxActor* CPhysx::NxA_pBoss = {};
//NxActor* CPhysx::NxA_pSmall = {};
bool CPhysx::hit = false;
bool g_hit = false;

/*NxActor* CPhysx::NxA_pCoffee = {};
NxActor* CPhysx::NxA_pCoffeeTable = {};

NxActor* CPhysx::NxA_pEnban = {};
NxActor* CPhysx::NxA_pHasira = {};
NxActor* CPhysx::NxA_pWheel = {};*/
bool boRenderSphere = true;
//モデルアニメーション関係変数
#define MODEL_MAX (13)
SKIN_MESH SkinMesh;
THING2 Thing2[MODEL_MAX - 1];//読み込むモデルの最大数+1
THING Thing[THING_AMOUNT + 1];//読み込むモデルの最大数+1
LPD3DXANIMATIONSET pAnimSet[THING_AMOUNT][10] = { 0 };//選択したモデルに10個までのアニメーションをセット
FLOAT fAnimTime = 0.0f;
BOOL boPlayAnim = true;
D3DXTRACK_DESC TrackDesc;
//=============================================================================
//	生成
//=============================================================================

CPhysx::CPhysx()
{

}

//=============================================================================
//	破棄
//=============================================================================
CPhysx::~CPhysx()
{

}

//	物理演算処理の初期化
void CPhysx::CPhysX_Initialize(void)
{
	InitGeometry();
	InitNx();
}


// Geometryの初期化（モデルの読み込み）
HRESULT CPhysx::InitGeometry()
{
	/*if (FAILED(LoadMesh("asset/model/boss.x", BOSS)))
	return E_FAIL;
	if (FAILED(LoadMesh("asset/model/emi-ru2.x", PLAYER)))
	return E_FAIL;
	if (FAILED(LoadMesh("asset/model/slime.x", SMALL)))
	return E_FAIL;
	*/
	/*
	for (int i = 1; i < m_NORMALMODELFAIL_MAX - 1; i++)
	{
		InitThing(&Thing2[i], m_NormalModelFileData[i].filename);
	}*/
	InitThing(&Thing2[0], m_NormalModelFileData[1].filename);
	InitSphere(m_pD3DDevice, &Thing2[0]);

//	InitThing(&Thing2[1], m_NormalModelFileData[2].filename);
//	InitSphere(m_pD3DDevice, &Thing2[1]);
	/*
	// メッシュごとのバウンディングスフィア（境界球）の作成
	for (int i = 0; i < m_NORMALMODELFAIL_MAX - 1; i++)
	{
		InitSphere(m_pD3DDevice, &Thing2[i]);
	}*/
	/*
	for (int i = 0;i < m_NORMALMODELFAIL_MAX - 1;i++)
	{
		if (FAILED(LoadMesh(m_NormalModelFileData[i+1].filename, i+1)))
			return E_FAIL;
	}*/
	//アニメーションモデル読み込み
	//THINGにxファイルを読み込む
	for (int i = 0; i < ANIME_MODEL_MAX; i++)
	{
		SkinMesh.InitThing(m_pD3DDevice, &Thing[i], m_AnimeModelFileData[i].filename);
	}
	SkinMesh.InitSphere(m_pD3DDevice, &Thing[0]);
	if (FAILED(CreateDebugBase()))
		return E_FAIL;
	return S_OK;
}

// PhysXの初期化
bool CPhysx::InitNx(void)
{
	NxPhysicsSDKDesc desc;
	NxSDKCreateError errorCode = NXCE_NO_ERROR;
	gPhysicsSDK = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION, NULL, new ErrorStream(), desc, &errorCode);
	if (gPhysicsSDK == NULL) return false;

	gPhysicsSDK->setParameter(NX_SKIN_WIDTH, 0.05f);

	// シーンの生成
	NxSceneDesc sceneDesc;
	sceneDesc.gravity = NxVec3(0.0f, -9.81f, 0.0f);
	gScene = gPhysicsSDK->createScene(sceneDesc);
	if (gScene == NULL) return false;

	// デフォルトのマテリアルを設定
	NxMaterial* defaultMaterial = gScene->getMaterialFromIndex(0);
	defaultMaterial->setRestitution(0.0f);
	defaultMaterial->setStaticFriction(0.5f);
	defaultMaterial->setDynamicFriction(0.5f);

	// PhysXグランドの生成
	NxPlaneShapeDesc planeDesc;
	NxActorDesc actorDesc;
	actorDesc.shapes.pushBack(&planeDesc);
	gScene->createActor(actorDesc);

	return true;
}

// メッシュの読み込み
HRESULT CPhysx::LoadMesh(LPCSTR filename, int n)
{
	LPD3DXBUFFER pD3DXMtrlBuffer;

	// ファイルのロード
	if (FAILED(D3DXLoadMeshFromX(filename, D3DXMESH_SYSTEMMEM,
		m_pD3DDevice, NULL,
		&pD3DXMtrlBuffer, NULL, &g_dwNumMaterials[n],
		&g_pMesh[n])))
	{
		// 親ディレクトリのサーチ
		if (FAILED(D3DXLoadMeshFromX(filename, D3DXMESH_SYSTEMMEM,
			m_pD3DDevice, NULL,
			&pD3DXMtrlBuffer, NULL, &g_dwNumMaterials[n],
			&g_pMesh[n])))
		{
			MessageBox(NULL, "Could not find xFile", "Meshes.exe", MB_OK);
			return E_FAIL;
		}
	}

	// マテリアルのプロパティとテクスチャファイル名の取得 
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	g_pMeshMaterials[n] = new D3DMATERIAL9[g_dwNumMaterials[n]];
	if (g_pMeshMaterials[n] == NULL)
		return E_OUTOFMEMORY;
	g_pMeshTextures[n] = new LPDIRECT3DTEXTURE9[g_dwNumMaterials[n]];
	if (g_pMeshTextures[n] == NULL)
		return E_OUTOFMEMORY;

	for (DWORD i = 0; i < g_dwNumMaterials[n]; i++)
	{
		// マテリアルのコピー
		g_pMeshMaterials[n][i] = d3dxMaterials[i].MatD3D;

		// マテリアルのアンビエントカラーの設定
		g_pMeshMaterials[n][i].Ambient = g_pMeshMaterials[n][i].Diffuse;

		g_pMeshTextures[n][i] = NULL;
		if (d3dxMaterials[i].pTextureFilename != NULL &&
			lstrlenA(d3dxMaterials[i].pTextureFilename) > 0)
		{
			// テクスチャの生成
			if (FAILED(D3DXCreateTextureFromFileA(m_pD3DDevice,
				d3dxMaterials[i].pTextureFilename,
				&g_pMeshTextures[n][i])))
			{
				// ディレクトリのサーチ
				const CHAR* strPrefix = "asset\\model\\";
				CHAR strTexture[MAX_PATH];
				StringCchCopyA(strTexture, MAX_PATH, strPrefix);
				StringCchCatA(strTexture, MAX_PATH, d3dxMaterials[i].pTextureFilename);
				// 親のディレクトリのサーチ
				if (FAILED(D3DXCreateTextureFromFileA(m_pD3DDevice,
					strTexture,
					&g_pMeshTextures[n][i])))
				{
					MessageBox(NULL, "Could not find texture map", "Meshes.exe", MB_OK);
				}
			}
		}
	}
	// マテリアルバッファの解放
	pD3DXMtrlBuffer->Release();

	return S_OK;
}

HRESULT CPhysx::InitThing(THING2 *pThing, LPSTR szXFileName)
{
	/////////
	// Xファイルからメッシュをロードする	
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

	if (FAILED(D3DXLoadMeshFromX(szXFileName, D3DXMESH_SYSTEMMEM,
		m_pD3DDevice, NULL, &pD3DXMtrlBuffer, NULL,
		&pThing->dwNumMaterials, &pThing->pMesh)))
	{
		MessageBox(NULL, "Xファイルの読み込みに失敗しました", szXFileName, MB_OK);
		return E_FAIL;
	}
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	pThing->pMeshMaterials = new D3DMATERIAL9[pThing->dwNumMaterials];
	pThing->pMeshTextures = new LPDIRECT3DTEXTURE9[pThing->dwNumMaterials];

	for (DWORD i = 0; i<pThing->dwNumMaterials; i++)
	{
		pThing->pMeshMaterials[i] = d3dxMaterials[i].MatD3D;
		pThing->pMeshMaterials[i].Ambient = pThing->pMeshMaterials[i].Diffuse;
		pThing->pMeshTextures[i] = NULL;
		if (d3dxMaterials[i].pTextureFilename != NULL &&
			lstrlen(d3dxMaterials[i].pTextureFilename) > 0)
		{
			if (FAILED(D3DXCreateTextureFromFile(m_pD3DDevice,
				d3dxMaterials[i].pTextureFilename,
				&pThing->pMeshTextures[i])))
			{
				MessageBox(NULL, "テクスチャの読み込みに失敗しました", NULL, MB_OK);
			}
		}
	}
	pD3DXMtrlBuffer->Release();

	return S_OK;
}

// アクターのセットアップ
void CPhysx::SetupActors(void)
{
	float skin = 0.1f;
	// Dwarf
	NxMat33 mat1;
	mat1.rotY(-NxPiF32 / 2);
	NxVec3 scaleDwarf = NxVec3(1, 1, 1);//モデルの大きさ
	NxVec3 BBDwarf = NxVec3(2.6f, 2.7f, 2.3f);//ボックスコリジョンの大きさ
	float d = scaleDwarf.y * BBDwarf.y - skin;
	//NxA_pPlayer = CreateMeshAsBox(NxVec3(-8, d, 0), mat1, scaleDwarf, BBDwarf, MODELL_PLAYER);
}


// 終了処理
void CPhysx::Cleanup(void)
{
	// PhysX
	ExitNx();

	for (int k = 0; k < 2; k++)
	{
		if (g_pMeshMaterials[k] != NULL)
			delete[] g_pMeshMaterials[k];

		if (g_pMeshTextures[k])
		{
			for (DWORD i = 0; i < g_dwNumMaterials[k]; i++)
			{
				if (g_pMeshTextures[k][i])
					g_pMeshTextures[k][i]->Release();
			}
			delete[] g_pMeshTextures[k];
		}
		if (g_pMesh[k] != NULL)
			g_pMesh[k]->Release();
	}
}

// PhysXの終了処理
void CPhysx::ExitNx(void)
{
	if (gPhysicsSDK != NULL)
	{
		if (gScene != NULL) gPhysicsSDK->releaseScene(*gScene);
		gScene = NULL;
		NxReleasePhysicsSDK(gPhysicsSDK);
		gPhysicsSDK = NULL;
	}
}

//	シーン取得
NxScene* CPhysx::Get_PhysX_Scene(void)
{
	return gScene;
}


// 描画
void CPhysx::PhysXRender(D3DXMATRIX mtxWorld)
{
	DebugFont_Draw(8, 58, "8キー　モデルの非表示");
	DebugFont_Draw(8, 108, "9キー　当たり判定表示");
	DebugFont_Draw(8, 158, "当たったか　%d", hit);
	//DebugFont_Draw(8, 208, "外れたか %d");

	// PhysXのシーンをチェック
	if (gScene == NULL) return;
	// PhysX時間ステップ
	gScene->simulate(1.0f / 60.0f);

	// カメラと射影のセットアップ
	//Camera_Move();
	// 描画
	if (physx)//当たり判定表示フラグがtrueの時
	{
		RenderPhysX();//当たり判定コリジョン表示
	}
	if (directx)//モデル表示
	{
		RenderDirectX(mtxWorld);//モデル描画
	}
	/*if (NxA_pCoffee && NxA_pEnban)
	{
		gScene->setActorPairFlags(*NxA_pCoffee,
			*NxA_pEnban,
			NX_NOTIFY_ON_START_TOUCH | NX_NOTIFY_ON_END_TOUCH);
	}*/
}

// PhysXの描画 PhysXRender
void CPhysx::RenderPhysX(void)
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	// ワールドマトリックスをセット
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	m_pD3DDevice->SetStreamSource(0, g_pVB, 0, sizeof(CUSTOMVERTEX));
	m_pD3DDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	// 座標軸とマット
	//DrawMeshDummy(0, 0);
	DrawMat();
	DrawAxis();
	//DrawMeshDummy(0, 1);
	// PhysXアクターの描画
	int nbActors = gScene->getNbActors();
	NxActor** actors = gScene->getActors();

	while (nbActors--)
	{
		NxActor* actor = *actors++;
		if (!actor->userData) continue;
		float glMat[16];
		actor->getGlobalPose().getColumnMajor44(glMat);
		// マトリックスの転置
		ConvertMatrix(matWorld, glMat);
		myData* mydata = (myData*)actor->userData;

		char c = mydata->type;
		switch (c)
		{
		case 'B':
			DrawBox(actor, matWorld);
			break;
		case 'S':
			DrawSphere(actor, matWorld);
			break;
		case 'C':
			DrawCapsule(actor, matWorld);
			break;
		}
	/*	if (NxA_pCoffee && NxA_pEnban)
		{
			gScene->setActorPairFlags(*NxA_pCoffee,
				*NxA_pEnban,
				NX_NOTIFY_ON_START_TOUCH | NX_NOTIFY_ON_END_TOUCH);
		}*/
	}
}

// 地面のマット RenderPhysX
void CPhysx::DrawMat(void)
{
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 0, 18);
}

// XYZの座標軸 RenderPhysX
void CPhysx::DrawAxis()
{
	m_pD3DDevice->DrawPrimitive(D3DPT_LINELIST, 19, 1);
}

// コリジョンを付けないモデルの描画 RenderPhysX
void CPhysx::DrawNoHitMesh(int n)
{
	for (DWORD i = 0; i < g_dwNumMaterials[n]; i++)
	{
		// マテリアルとテクスチャ
		m_pD3DDevice->SetMaterial(&g_pMeshMaterials[n][i]);
		m_pD3DDevice->SetTexture(0, g_pMeshTextures[n][i]);

		// 描画
		g_pMesh[n]->DrawSubset(i);
	}
}

// メッシュの描画 RenderPhysX
void CPhysx::DrawMeshDummy(int n, int m)
{
	// マテリアルとテクスチャ
	m_pD3DDevice->SetMaterial(&g_pMeshMaterials[n][m]);
	m_pD3DDevice->SetTexture(0, g_pMeshTextures[n][m]);
}

// DirectXの描画 PhysXRender
void CPhysx::RenderDirectX(D3DXMATRIX mtxWorld)
{
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	m_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
	//D3DXMATRIXA16 matWorld;
	//D3DXMatrixIdentity(&mtxWorld);
	// ワールドマトリックスをセット
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	// DirectXの芝生
	//DrawNoHitMesh(DirectXBase);

	// アクターの描画
	int nbActors = gScene->getNbActors();
	NxActor** actors = gScene->getActors();
	while (nbActors--)
	{
		NxActor* actor = *actors++;
		if (!actor->userData) continue;

		myData* mydata = (myData*)actor->userData;
		if ((mydata->type == 'B') || (mydata->type == 'S') || (mydata->type == 'C'))
		{
			DrawDirectXMesh(actor);
		}
	/*	if (NxA_pCoffee && NxA_pEnban)
		{
			gScene->setActorPairFlags(*NxA_pCoffee,
				*NxA_pEnban,
				NX_NOTIFY_ON_START_TOUCH | NX_NOTIFY_ON_END_TOUCH);
		}*/
		// ２つのアクターを関連づけて衝突開始と衝突終了イベントを有効にする
		//当たり判定処理　第一引数と第二引数に当たり判定を行うアクターを指定する
		/*if (MODELL_PLAYER)
		{
		gScene->setActorPairFlags(*NxA_pPlayer,
		*NxA_pBoss,
		NX_NOTIFY_ON_START_TOUCH | NX_NOTIFY_ON_END_TOUCH);
		}*/
	}
}

// メッシュの描画 RenderDirectX
void CPhysx::DrawDirectXMesh(NxActor* actor)
{
	if (actor)
	{
		int nbActors = gScene->getNbActors();
		NxActor** actors = gScene->getActors();
		myData* mydata = (myData*)actor->userData;
		for (int i = nbActors;i > 0;i--)
		{
			NxActor* act = *actors++;
			if (!act->userData) continue;
			myData* data = (myData*)act->userData;
			if (data->ID == mydata->ID)
			{

				D3DXMATRIXA16 matWorld;

				//myData* mydata = (myData*)actor->userData;
				NxVec3 s = mydata->meshScale;
				NxVec3 t = mydata->meshTranslation;

				D3DXMATRIXA16 mat;

				// PhysX姿勢の取得
				float glMat[16];
				act->getGlobalPose().getColumnMajor44(glMat);
				ConvertMatrix(matWorld, glMat);

				// メッシュの拡大縮小
				D3DXMatrixScaling(&mat, s.x, s.y, s.z);
				D3DXMatrixMultiply(&matWorld, &mat, &matWorld);

				// メッシュの回転
				mat = mydata->meshRotation;
				D3DXMatrixMultiply(&matWorld, &mat, &matWorld);

				// メッシュの原点調整
				D3DXMatrixTranslation(&mat, t.x, t.y + 1, t.z);
				D3DXMatrixMultiply(&matWorld, &mat, &matWorld);

				// マトリックスのセット
				m_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
				// メッシュの描画
				int n = mydata->ID;
				for (DWORD i = 0; i < g_dwNumMaterials[n]; i++)
				{
					// マテリアルとテクスチャ
					m_pD3DDevice->SetMaterial(&g_pMeshMaterials[n][i]);
					m_pD3DDevice->SetTexture(0, g_pMeshTextures[n][i]);

					// 描画
					g_pMesh[n]->DrawSubset(i);
				}

			}
		/*	if (NxA_pCoffee && NxA_pEnban)
			{
				gScene->setActorPairFlags(*NxA_pCoffee,
					*NxA_pEnban,
					NX_NOTIFY_ON_START_TOUCH | NX_NOTIFY_ON_END_TOUCH);
			}*/
		}
	}
}

void CPhysx::DrawDX2(D3DXMATRIX mtxWorld, NxActor* actor, int type)
{
	if (actor)
	{
		/*DebugFont_Draw(8, 58, "8キー　モデルの非表示");
		DebugFont_Draw(8, 108, "9キー　当たり判定表示");
		DebugFont_Draw(8, 158, "当たったか　%d", hit);*/

		// PhysXのシーンをチェック
		if (gScene == NULL) return;
		// PhysX時間ステップ
		gScene->simulate(1.0f / 60.0f);

		m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		m_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
		m_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);

		myData* mydata = (myData*)actor->userData;

		mydata->meshTranslation.x = mtxWorld._41;
		mydata->meshTranslation.y = mtxWorld._42;
		mydata->meshTranslation.z = mtxWorld._43;
		actor->setGlobalPosition(mydata->meshTranslation);

		D3DXMATRIXA16 mat;
		D3DXMATRIXA16 mtxWorld2;
		// PhysX姿勢の取得
		float glMat[16];
		actor->getGlobalPose().getColumnMajor44(glMat);
		ConvertMatrix(mtxWorld2, glMat);

		NxVec3 s = mydata->meshScale;
		NxVec3 t = mydata->meshTranslation;
		// メッシュの拡大縮小
		D3DXMatrixScaling(&mat, s.x, s.y, s.z);
		D3DXMatrixMultiply(&mtxWorld, &mat, &mtxWorld);

		// メッシュの回転
		mat = mydata->meshRotation;
		//D3DXMatrixMultiply(&mtxWorld2, &mat, &mtxWorld2);
		D3DXMatrixMultiply(&mtxWorld, &mat, &mtxWorld);

		D3DXMatrixTranslation(&mat, 0, 0, 0);
		D3DXMatrixMultiply(&mtxWorld, &mat, &mtxWorld);
		// マトリックスのセット
		m_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
		// メッシュの描画
		int n = mydata->ID;
		for (DWORD i = 0; i < g_dwNumMaterials[n]; i++)
		{
			// マテリアルとテクスチャ
			m_pD3DDevice->SetMaterial(&g_pMeshMaterials[n][i]);
			m_pD3DDevice->SetTexture(0, g_pMeshTextures[n][i]);

			// 描画
			g_pMesh[n]->DrawSubset(i);
		}

	}
}

void CPhysx::DrawDX_Anime(D3DXMATRIX mtxWorld, NxActor* actor, int type,THING* pThing)
{
	static float fAnimTimeHold = fAnimTime;
	if (actor)
	{
		SKIN_MESH::UpdateSphere(m_pD3DDevice, pThing);
		/*DebugFont_Draw(8, 58, "8キー　モデルの非表示");
		DebugFont_Draw(8, 108, "9キー　当たり判定表示");
		DebugFont_Draw(8, 158, "当たったか　%d", hit);*/

		// PhysXのシーンをチェック
		if (gScene == NULL) return;
		// PhysX時間ステップ
		gScene->simulate(1.0f / 60.0f);

		m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		m_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
		m_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);

		myData* mydata = (myData*)actor->userData;

		mydata->meshTranslation.x = mtxWorld._41;
		mydata->meshTranslation.y = mtxWorld._42;
		mydata->meshTranslation.z = mtxWorld._43;
		actor->setGlobalPosition(mydata->meshTranslation);

		D3DXMATRIXA16 mat;
		D3DXMATRIXA16 mtxWorld2;
		// PhysX姿勢の取得
		float glMat[16];
		actor->getGlobalPose().getColumnMajor44(glMat);
		ConvertMatrix(mtxWorld2, glMat);

		NxVec3 s = mydata->meshScale;
		NxVec3 t = mydata->meshTranslation;
		// メッシュの拡大縮小
		D3DXMatrixScaling(&mat, s.x, s.y, s.z);
		D3DXMatrixMultiply(&mtxWorld, &mat, &mtxWorld);

		// メッシュの回転
		mat = mydata->meshRotation;
		//D3DXMatrixMultiply(&mtxWorld2, &mat, &mtxWorld2);
		D3DXMatrixMultiply(&mtxWorld, &mat, &mtxWorld);

		D3DXMatrixTranslation(&mat, 0, 0, 0);
		D3DXMatrixMultiply(&mtxWorld, &mat, &mtxWorld);
		// マトリックスのセット
		m_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
		// メッシュの描画
		int n = mydata->ID;
		for (DWORD i = 0; i < g_dwNumMaterials[n]; i++)
		{
			// マテリアルとテクスチャ
			m_pD3DDevice->SetMaterial(&g_pMeshMaterials[n][i]);
			m_pD3DDevice->SetTexture(0, g_pMeshTextures[n][i]);

			// 描画
			g_pMesh[n]->DrawSubset(i);
		}

		//レンダリング
		SkinMesh.UpdateFrameMatrices(pThing->pFrameRoot, &mtxWorld);
		SkinMesh.DrawFrame(m_pD3DDevice, pThing->pFrameRoot);
		pThing->pAnimController->AdvanceTime(fAnimTime - fAnimTimeHold, NULL);
		//　バウンディングスフィアのレンダリング	
		D3DXMatrixTranslation(&mat, pThing->vPosition.x, pThing->vPosition.y,
			pThing->vPosition.z);
		D3DXMatrixTranslation(&mtxWorld, pThing->Sphere.vCenter.x, pThing->Sphere.vCenter.y,
			pThing->Sphere.vCenter.z);
		mtxWorld *= mat;

		m_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		if (boRenderSphere)
		{
			m_pD3DDevice->SetTexture(0, NULL);
			m_pD3DDevice->SetMaterial(pThing->pSphereMeshMaterials);
			pThing->pSphereMesh->DrawSubset(0);
		}
		//アニメ再生時間を+
		fAnimTimeHold = fAnimTime;
		if (boPlayAnim)
		{
			fAnimTime += 0.01f;
		}
	}
}
void CPhysx::DrawDX(D3DXMATRIX mtxWorld, NxActor* actor)
{
	if (actor)
	{
		DebugFont_Draw(8, 58, "8キー　モデルの非表示");
		DebugFont_Draw(8, 108, "9キー　当たり判定表示");
		DebugFont_Draw(8, 158, "当たったか　%d", hit);

		// PhysXのシーンをチェック
		if (gScene == NULL) return;
		// PhysX時間ステップ
		gScene->simulate(1.0f / 60.0f);

		m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		m_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
		m_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
		//D3DXMATRIXA16 matWorld;
		//D3DXMatrixIdentity(&mtxWorld);
		// ワールドマトリックスをセット
		//	m_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
		// DirectXの芝生
		//DrawNoHitMesh(DirectXBase);

		myData* mydata = (myData*)actor->userData;
		mydata->meshTranslation.x = mtxWorld._41;
		mydata->meshTranslation.y = mtxWorld._42;
		mydata->meshTranslation.z = mtxWorld._43;
		NxVec3 s = mydata->meshScale;
		NxVec3 t = mydata->meshTranslation;

		D3DXMATRIXA16 mat;

		// PhysX姿勢の取得
		float glMat[16];
		actor->getGlobalPose().getColumnMajor44(glMat);
		//ConvertMatrix(mtxWorld, glMat);

		// メッシュの拡大縮小
		D3DXMatrixScaling(&mat, s.x, s.y, s.z);
		D3DXMatrixMultiply(&mtxWorld, &mat, &mtxWorld);

		// メッシュの回転
		mat = mydata->meshRotation;
		D3DXMatrixMultiply(&mtxWorld, &mat, &mtxWorld);

		// メッシュの原点調整
		D3DXMatrixTranslation(&mat, t.x, t.y, t.z);
		D3DXMatrixMultiply(&mtxWorld, &mat, &mtxWorld);

		// マトリックスのセット
		m_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
		// メッシュの描画
		int n = mydata->ID;
		for (DWORD i = 0; i < g_dwNumMaterials[n]; i++)
		{
			// マテリアルとテクスチャ
			m_pD3DDevice->SetMaterial(&g_pMeshMaterials[n][i]);
			m_pD3DDevice->SetTexture(0, g_pMeshTextures[n][i]);

			// 描画
			g_pMesh[n]->DrawSubset(i);
		}
		/*if (NxA_pCoffee && NxA_pEnban)
		{
			gScene->setActorPairFlags(*NxA_pCoffee,
				*NxA_pEnban,
				NX_NOTIFY_ON_START_TOUCH | NX_NOTIFY_ON_END_TOUCH);
		}*/
		// ２つのアクターを関連づけて衝突開始と衝突終了イベントを有効にする
		//当たり判定処理　第一引数と第二引数に当たり判定を行うアクターを指定する
		/*	if (MODELL_PLAYER)
		{
		gScene->setActorPairFlags(*NxA_pPlayer,
		*NxA_pBoss,
		NX_NOTIFY_ON_START_TOUCH | NX_NOTIFY_ON_END_TOUCH);
		}*/
	}
}

void CPhysx::RenderThing(D3DXMATRIX mtxWorld, NxActor* actor, int type, THING2* pThing)
{
	// PhysXのシーンをチェック
	if (gScene == NULL) return;
	// PhysX時間ステップ
	gScene->simulate(1.0f / 60.0f);

	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	m_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);

	myData* mydata = (myData*)actor->userData;

	mydata->meshTranslation.x = mtxWorld._41;
	mydata->meshTranslation.y = mtxWorld._42;
	mydata->meshTranslation.z = mtxWorld._43;
	actor->setGlobalPosition(mydata->meshTranslation);

	D3DXMATRIXA16 mat;
	D3DXMATRIXA16 mtxWorld2;
	// PhysX姿勢の取得
	float glMat[16];
	actor->getGlobalPose().getColumnMajor44(glMat);
	ConvertMatrix(mtxWorld2, glMat);

	NxVec3 s = mydata->meshScale;
	NxVec3 t = mydata->meshTranslation;
	// メッシュの拡大縮小
	D3DXMatrixScaling(&mat, s.x, s.y, s.z);
	D3DXMatrixMultiply(&mtxWorld, &mat, &mtxWorld);

	// メッシュの回転
	mat = mydata->meshRotation;
	//D3DXMatrixMultiply(&mtxWorld2, &mat, &mtxWorld2);
	D3DXMatrixMultiply(&mtxWorld, &mat, &mtxWorld);

	D3DXMatrixTranslation(&mat, 0, 0, 0);
	D3DXMatrixMultiply(&mtxWorld, &mat, &mtxWorld);
	// マトリックスのセット
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);


	for (DWORD i = 0; i<pThing->dwNumMaterials; i++)
	{
		m_pD3DDevice->SetMaterial(&pThing->pMeshMaterials[i]);
		m_pD3DDevice->SetTexture(0, pThing->pMeshTextures[i]);
		pThing->pMesh->DrawSubset(i);
	}
	//　バウンディングスフィアのレンダリング	
	if (boRenderSphere)
	{
		m_pD3DDevice->SetTexture(0, NULL);
		m_pD3DDevice->SetMaterial(pThing->pSphereMeshMaterials);
		pThing->pSphereMesh->DrawSubset(0);
	}
	//当たり判定
	if (Collision(&Thing2[0], &Thing2[1]))
	{
		DebugFont_Draw(500, 300, "当たったぞ！！！！！！！！！！！");
		C3DObj *pplayer = CPlayer::Get_Player();
		NxActor *pactor = pplayer->Get_Actor();
			//C3DObj *penemy = CEnemy_Small::Get_EnemySmall();
			if (actor != pactor)
			{
				//NxActor *actor = penemy->Get_Actor();
				actor->addForce(NxVec3(500000000, -2000000, 0));
				actor->setLinearVelocity(NxVec3(20, 0, 0));
				actor->addLocalTorque(NxVec3(100000, 0, 0), NX_FORCE);
			}
		
	}
	else
	{
		DebugFont_Draw(500, 500, "当たってないぞ！！！！！！！！！！！");
	}
}

// マトリックスの変換 RenderPhysX　DrawDirectXMesh
void CPhysx::ConvertMatrix(D3DXMATRIXA16 &matWorld, float *glMat) //(D3DXMATRIXA16 &matWorld, float *glMat)
{
	matWorld._11 = *glMat++;
	matWorld._12 = *glMat++;
	matWorld._13 = *glMat++;
	matWorld._14 = *glMat++;
	matWorld._21 = *glMat++;
	matWorld._22 = *glMat++;
	matWorld._23 = *glMat++;
	matWorld._24 = *glMat++;
	matWorld._31 = *glMat++;
	matWorld._32 = *glMat++;
	matWorld._33 = *glMat++;
	matWorld._34 = *glMat++;
	matWorld._41 = *glMat++;
	matWorld._42 = *glMat++;
	matWorld._43 = *glMat++;
	matWorld._44 = *glMat++;
}


//	当たり判定

// ボックス型のメッシュの生成
NxActor* CPhysx::CreateMeshAsBox(NxVec3 position, NxMat33 rotation, NxVec3 scale, NxVec3 boundingbox, int ID)
{
	myData mydata;
	mydata.meshScale = scale;
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	mydata.meshTranslation = NxVec3(0, -boundingbox.y, 0);
	mydata.meshRotation = mat;
	// PhysXのボックス
	mydata.dimension = NxVec3(boundingbox.x * scale.x, boundingbox.y * scale.y, boundingbox.z * scale.z);
	mydata.ID = ID;
	mydata.type = 'B';
	mydata.rotation = rotation;
	mydata.position = position;
	mydata.hit = false;
	return CreateBox(mydata, &NxVec3(1.0f, 1.0f, 1.0f));
}

// ボックス型のメッシュの生成2
NxActor* CPhysx::CreateMeshAsBox(NxVec3 position, NxMat33 rotation, NxVec3 scale, NxVec3 boundingbox, int ID, bool type)
{
	myData mydata;
	mydata.meshScale = scale;
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	mydata.meshTranslation = NxVec3(0, -boundingbox.y, 0);
	mydata.meshRotation = mat;
	// PhysXのボックス
	mydata.dimension = NxVec3(boundingbox.x * scale.x, boundingbox.y * scale.y, boundingbox.z * scale.z);
	mydata.ID = ID;
	mydata.type = 'B';
	mydata.rotation = rotation;
	mydata.position = position;
	mydata.hit = false;
	return CreateBox(mydata, &NxVec3(1.0f, 1.0f, 1.0f), type);
}

// 球型のメッシュの生成
NxActor* CPhysx::CreateMeshAsSphere(NxVec3 position, float r, int ID)
{
	myData mydata;
	// メッシュの拡大縮小
	mydata.meshScale = NxVec3(1, 1, 1);
	mydata.meshTranslation = NxVec3(0, 0, 0);
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	mydata.meshRotation = mat;
	// PhysXの球
	mydata.radius = r;
	mydata.dimension = NxVec3(r, r, r);
	mydata.ID = ID;
	NxMat33 mat2;
	mat2.rotX(0);
	mydata.rotation = mat2;
	mydata.position = position;
	mydata.hit = false;
	return CreateSphere(mydata, &NxVec3(1.0f, 1.0f, 1.0f));
}

//カプセル型のメッシュの生成
NxActor* CPhysx::CreateMeshAsCapsule(NxVec3 position, NxMat33 rotation, NxVec3 scale, float r, float h, int ID)
{
	myData mydata;
	// メッシュの拡大縮小
	mydata.meshScale = scale;
	float Radius = r * scale.x;
	float Height = h * scale.y;
	mydata.meshTranslation = NxVec3(0, -h / 2 - r + 0.01f, 0);
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	mydata.meshRotation = mat;
	// PhysXの球
	mydata.radius = Radius;
	mydata.height = Height;
	mydata.dimension = NxVec3(Radius, Height, Radius);
	mydata.ID = ID;
	mydata.rotation = rotation;
	mydata.position = position;
	return CreateCapsule(mydata, &NxVec3(1.0f, 1.0f, 1.0f));
}

// ボックスの生成
NxActor* CPhysx::CreateBox(myData mydata, const NxVec3* initialVelocity)
{
	if (gScene == NULL) return NULL;

	myData* data = new myData;
	*data = mydata;
	data->type = 'B';
	// デスクリプタ
	NxBodyDesc bodyDesc;
	bodyDesc.angularDamping = 0.5f;
	if (initialVelocity) bodyDesc.linearVelocity = *initialVelocity;

	NxBoxShapeDesc boxDesc;
	boxDesc.dimensions = data->dimension;

	NxActorDesc actorDesc;
	actorDesc.shapes.pushBack(&boxDesc);//ここでアクターにボックスコリジョンを登録
	actorDesc.body = &bodyDesc;//ここで動的情報を取得
	actorDesc.density = 10.0f;//質量
	actorDesc.globalPose.t = data->position;//ワールド空間の位置に置く
	actorDesc.globalPose.M = data->rotation;//PhysX内では右手座標系なので転置行列をセットする
	actorDesc.userData = data;

	return gScene->createActor(actorDesc);//シーンに対して、指定のアクターを追加
}

// ボックスの生成
NxActor* CPhysx::CreateBox(myData mydata, const NxVec3* initialVelocity, bool type)
{
	if (gScene == NULL) return NULL;

	myData* data = new myData;
	*data = mydata;
	data->type = 'B';
	// デスクリプタ
	NxBodyDesc bodyDesc;
	bodyDesc.angularDamping = 0.5f;
	if (initialVelocity) bodyDesc.linearVelocity = *initialVelocity;

	NxBoxShapeDesc boxDesc;
	boxDesc.dimensions = data->dimension;

	NxActorDesc actorDesc;
	actorDesc.shapes.pushBack(&boxDesc);//ここでアクターにボックスコリジョンを登録
	if (!type)
	{
		actorDesc.body = NULL;//ここをNULLにすると静的アクターになる
	}
	else
	{
		actorDesc.body = &bodyDesc;//ここで動的情報を取得
	}
	actorDesc.density = 10.0f;//質量
	actorDesc.globalPose.t = data->position;//ワールド空間の位置に置く
	actorDesc.globalPose.M = data->rotation;//PhysX内では右手座標系なので転置行列をセットする
	actorDesc.userData = data;

	return gScene->createActor(actorDesc);//シーンに対して、指定のアクターを追加
}

// 球の生成
NxActor* CPhysx::CreateSphere(myData mydata, const NxVec3* initialVelocity)
{
	if (gScene == NULL) return NULL;

	myData* data = new myData;
	*data = mydata;
	data->type = 'S';
	// デスクリプタ
	NxBodyDesc bodyDesc;
	bodyDesc.angularDamping = 0.5f;
	if (initialVelocity) bodyDesc.linearVelocity = *initialVelocity;

	NxSphereShapeDesc sphereDesc;
	sphereDesc.radius = data->radius;

	NxActorDesc actorDesc;
	actorDesc.shapes.pushBack(&sphereDesc); // ここでアクターにスフィアコリジョンを登録
	actorDesc.body = NULL;//ここで動的情報を取得
	actorDesc.density = 10.0f;//質量
	actorDesc.globalPose.t = data->position;//ワールド空間の位置に置く
	actorDesc.globalPose.M = data->rotation;//PhysX内では右手座標系なので転置行列をセットする
	actorDesc.userData = data;

	return gScene->createActor(actorDesc);
}

// カプセルの生成
NxActor* CPhysx::CreateCapsule(myData mydata, const NxVec3* initialVelocity)
{
	if (gScene == NULL) return NULL;

	myData* data = new myData;
	*data = mydata;
	data->type = 'C';
	// デスクリプタ
	NxBodyDesc bodyDesc;
	bodyDesc.angularDamping = 0.5f;
	if (initialVelocity) bodyDesc.linearVelocity = *initialVelocity;

	NxCapsuleShapeDesc capsuleDesc;
	capsuleDesc.radius = data->radius;
	capsuleDesc.height = data->height;

	NxActorDesc actorDesc;
	actorDesc.shapes.pushBack(&capsuleDesc);// ここでアクターにカプセルコリジョンを登録
	actorDesc.body = &bodyDesc;//ここで動的情報を取得;
	actorDesc.density = 10.0f;//質量
	actorDesc.globalPose.t = data->position;//ワールド空間の位置に置く
	actorDesc.globalPose.M = data->rotation;//PhysX内では右手座標系なので転置行列をセットする
	actorDesc.userData = data;

	return gScene->createActor(actorDesc);
}


//デバッグ描画

// デバッグデータのセット（デバックコリジョン行列）
HRESULT CPhysx::CreateDebugBase()
{
	float a = 4.0f;	// 座標軸の長さ
	float b = 2.0f; // マットの長さ
	float c = b / 2;
	float d = 1.0f; // ボックスの寸法
	float r = 1.0f; // 球の半径
	float r1 = r * 1.41421356f / 2;
	float h = r / 2;

	// 頂点
	CUSTOMVERTEX g_Vertices[] =
	{
		// 座標軸
		{ b, 0, b, },		// 0
		{ b, 0, -b, },
		{ c, 0, -b, },
		{ c, 0,  b, },
		{ 0, 0, b, },
		{ 0, 0, -b, },
		{ -c, 0, -b, },
		{ -c, 0,  b, },
		{ -b, 0, b, },
		{ -b, 0,  -b, },
		{ b, 0, -b, },
		{ b, 0, -c, },
		{ -b, 0, -c, },
		{ -b, 0,  0, },
		{ b, 0, 0, },
		{ b, 0, c, },
		{ -b, 0, c, },
		{ -b, 0, b, },
		{ b, 0, b, },
		// 
		{ 0, 0, 0, },		// 19
		{ 0, a, 0, },
		{ 0, 0, 0, },
		// ボックス
		{ -d, -d, -d, },	// 22
		{ -d, -d,  d, },
		{ -d,  d,  d, },
		{ -d,  d, -d, },

		{ d, -d, -d, },	// 26
		{ -d, -d, -d, },
		{ -d,  d, -d, },
		{ d,  d, -d, },

		{ d, -d,  d, },	// 30
		{ d, -d, -d, },
		{ d,  d, -d, },
		{ d,  d,  d, },

		{ -d, -d,  d, },	// 34
		{ d, -d,  d, },
		{ d,  d,  d, },
		{ -d,  d,  d, },
		// 球
		{ r, 0,   0, },	// 38
		{ r1, 0,  r1, },
		{ 0, 0,   r, },
		{ -r1, 0,  r1, },
		{ -r, 0,   0, },
		{ -r1, 0, -r1, },
		{ 0, 0,  -r, },
		{ r1, 0, -r1, },
		{ r, 0,   0, },

		{ r,   0, 0, },	// 47
		{ r1,  r1, 0, },
		{ 0,   r, 0, },
		{ -r1,  r1, 0, },
		{ -r,   0, 0, },
		{ -r1, -r1, 0, },
		{ 0,  -r, 0, },
		{ r1, -r1, 0, },
		{ r,   0, 0, },

		{ 0,   0,   r, },	// 56
		{ 0,  r1,  r1, },
		{ 0,   r,   0, },
		{ 0,  r1, -r1, },
		{ 0,   0,  -r, },
		{ 0, -r1, -r1, },
		{ 0,  -r,   0, },
		{ 0, -r1,  r1, },
		{ 0,   0,   r, },
		// カプセル
		{ -r,  h, 0, },		// 65
		{ -r, -h, 0, },
		{ r,  h, 0, },		// 67
		{ r, -h, 0, },
		{ 0, h,   -r, },	// 69
		{ 0, -h,  -r, },
		{ 0, h,   r, },		// 71
		{ 0, -h,  r, },
	};

	// 頂点バッファの生成
	if (FAILED(m_pD3DDevice->CreateVertexBuffer(100 * sizeof(CUSTOMVERTEX),
		0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &g_pVB, NULL)))
	{
		return E_FAIL;
	}

	// 頂点バッファへの転送
	VOID* pVertices;
	if (FAILED(g_pVB->Lock(0, sizeof(g_Vertices), (void**)&pVertices, 0)))
		return E_FAIL;
	memcpy(pVertices, g_Vertices, sizeof(g_Vertices));
	g_pVB->Unlock();
	return S_OK;
}

// ボックスの描画
void CPhysx::DrawBox(NxActor* actor, D3DXMATRIXA16 &matWorld)
{
	D3DXMATRIXA16 mat;
	myData* mydata = (myData*)actor->userData;
	NxVec3 v = mydata->dimension;
	D3DXMatrixScaling(&mat, v.x, v.y, v.z);
	// ワールドへ乗算
	D3DXMatrixMultiply(&matWorld, &mat, &matWorld);
	// バッファへ転送
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 22, 3);
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 26, 3);
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 30, 3);
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 34, 3);
}

// 球の描画
void CPhysx::DrawSphere(NxActor* actor, D3DXMATRIXA16 &matWorld)
{
	D3DXMATRIXA16 mat;
	myData* mydata = (myData*)actor->userData;
	// 寸法の取得
	NxVec3 v = mydata->dimension;
	float r = mydata->radius;
	D3DXMatrixScaling(&mat, r, r, r);
	// ワールドへ乗算
	D3DXMatrixMultiply(&matWorld, &mat, &matWorld);
	// バッファへ転送
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 38, 8);
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 47, 8);
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 56, 8);
}

// カプセルの描画
void CPhysx::DrawCapsule(NxActor* actor, D3DXMATRIXA16 &matWorld)
{
	D3DXMATRIXA16 mat, matold;
	matold = matWorld;
	myData* mydata = (myData*)actor->userData;
	float r = mydata->radius;
	float h = mydata->height;
	D3DXMatrixScaling(&mat, r, h, r);
	// ワールドへ乗算
	D3DXMatrixMultiply(&matWorld, &mat, &matWorld);
	// バッファへ転送
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	// 胴部の描画
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 65, 1);
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 67, 1);
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 69, 1);
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 71, 1);
	//
	matWorld = matold;
	D3DXMatrixTranslation(&mat, 0, h / 2, 0);
	D3DXMatrixMultiply(&matWorld, &mat, &matWorld);
	D3DXMatrixScaling(&mat, r, r, r);
	D3DXMatrixMultiply(&matWorld, &mat, &matWorld);

	m_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	// 上部の半球の描画
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 47, 4);
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 56, 4);
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 38, 8);

	matWorld = matold;
	D3DXMatrixTranslation(&mat, 0, -h / 2, 0);
	D3DXMatrixMultiply(&matWorld, &mat, &matWorld);
	D3DXMatrixScaling(&mat, r, r, r);
	D3DXMatrixMultiply(&matWorld, &mat, &matWorld);
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	// 下部の半球の描画
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 51, 4);
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 60, 4);
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 38, 8);
}



//当たり判定イベント通知クラス  　hit相談
void CPhysx::ContactCallBack::onContactNotify(NxContactPair& pair, NxU32 events)
{
	// アクターで使用するユーザーデータ
	USERDATA* pUserData1 = NULL;
	USERDATA* pUserData2 = NULL;
	myData* mydata = (myData*)pair.actors[0]->userData;
	myData* mydata2 = (myData*)pair.actors[0]->userData;
	switch (events)
	{
		// 衝突開始イベント通知
	case NX_NOTIFY_ON_START_TOUCH:

		// 衝突対象の２つのアクターのユーザーデータのポインタを取得する。
		pUserData1 = (USERDATA*)pair.actors[0]->userData;
		pUserData2 = (USERDATA*)pair.actors[1]->userData;
		pair.actors[1]->addForce(NxVec3(500000, -2000000, 0));
		pair.actors[1]->setLinearVelocity(NxVec3(20, 0, 0));
		pair.actors[1]->addLocalTorque(NxVec3(100000, 0, 0), NX_FORCE);
		// ユーザーデータにイベント情報を設定する
		//pUserData1->ContactPairFlag = events;
		//pUserData2->ContactPairFlag = events;
		
		mydata->hit = true;
		mydata2->hit = true;
		break;

		// 衝突終了イベント通知
	case NX_NOTIFY_ON_END_TOUCH:

	//	myData* mydata2 = (myData*)pair.actors[0]->userData;
		mydata->hit = false;
		mydata2->hit = false;
		// 衝突対象の２つのアクターのユーザーデータのポインタを取得する。
		//pUserData1 = (USERDATA*)pair.actors[0]->userData;
		//pUserData2 = (USERDATA*)pair.actors[1]->userData;

		// ユーザーデータを 0 に初期化する
		//pUserData1->ContactPairFlag = 0;
		//pUserData2->ContactPairFlag = 0;

		break;
	}
}


void CPhysx::Debug_Collision(SphereCollision sc, D3DXMATRIX mtx)
{
	//DebugFont_Draw(700, 300, "%f\n,%f\n,%f\n,", sc.CenterPos.x, sc.CenterPos.y, sc.CenterPos.z);

	D3DXMATRIX mtxS;
	D3DXMatrixScaling(&mtxS, sc.radius, sc.radius, sc.radius);
	// ワールドへ乗算
	//D3DXMatrixMultiply(&mtx, &mtxR, &mtx);
	mtx = mtxS * mtx;
	// バッファへ転送
	m_pD3DDevice->SetStreamSource(0, g_pVB, 0, sizeof(CUSTOMVERTEX));
	m_pD3DDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &mtx);
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 38, 8);
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 47, 8);
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 56, 8);
}

THING* CPhysx::GetAnimeModel(int index)
{
	return &Thing[index];
}

THING2* CPhysx::GetNormalModel(int index)
{
	return &Thing2[index];
}