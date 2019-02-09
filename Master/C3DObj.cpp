//////////////////////////////////////////////////
////
////	3Dオブジェクトクラス
////
//////////////////////////////////////////////////

#include "C3DObj.h"
#include "debug_font.h"
#include "CTexture.h"
#include "Cplayer.h"

//=============================================================================
//	静的変数
//===========================================================================
C3DObj *C3DObj::p3DObj[MAX_GAMEOBJ];
int C3DObj::m_3DObjNum = 0;
int C3DObj::m_TotalScore = 0;

C3DObj::MaterialFileData C3DObj::NORMAL_MODEL_FILES[] = {
	{ "asset/model/emi-ru2.x" },
	{ "asset/model/dish.blend.x" },
	{ "asset/model/enban.x" },
	{ "asset/model/hasira.x" },
	{ "asset/model/ferris.x" },
	{ "asset/model/jet.x" },
	{ "asset/model/cup_blue.x" },
	{ "asset/model/cup_kiiro.x" },
	{ "asset/model/cup_midori.x" },
	{ "asset/model/popcorn.x" },
	{ "asset/model/kensetutyuu.x" },
	{ "asset/model/ornament/lamp.x" },
	{ "asset/model/ornament/gomibako.x" },
	{ "asset/model/ornament/bench.x" },
	{ "asset/model/ornament/hunsui.x" },
};
//	使いたいアニメモデルの数だけ書く
C3DObj::MaterialFileData2 C3DObj::ANIME_MODEL_FILES[] = {
	{ "asset/anime_model/hewplayer.x" },
	{ "asset/anime_model/small_enemy.x" },
	{ "asset/anime_model/middle_enemy.x" },
	{ "asset/anime_model/special_enemy.x" },
	{ "asset/anime_model/big_enemy.x" },
};
int C3DObj::MODEL_FILES_MAX = sizeof(C3DObj::NORMAL_MODEL_FILES) / sizeof(NORMAL_MODEL_FILES[0]);
int C3DObj::ANIME_MODEL_FILES_MAX = sizeof(C3DObj::ANIME_MODEL_FILES) / sizeof(ANIME_MODEL_FILES[0]);

bool C3DObj::boRenderSphere = false;
//モデルアニメーション関係変数
/*
#define MODEL_MAX (9)

SKIN_MESH SkinMesh;
THING_NORMAL Thing_Normal[MODEL_MAX+1];//読み込むモデルの最大数+1
THING Thing[THING_AMOUNT + 1];//読み込むモデルの最大数+1
LPD3DXANIMATIONSET pAnimSet[THING_AMOUNT][10] = { 0 };//選択したモデルに10個までのアニメーションをセット
FLOAT fAnimTime = 0.0f;
BOOL boPlayAnim = true;
D3DXTRACK_DESC TrackDesc;
*/

//SKIN_MESH C3DObj::SkinMesh;
THING_NORMAL C3DObj::Thing_Normal[(sizeof(C3DObj::NORMAL_MODEL_FILES) / sizeof(NORMAL_MODEL_FILES[0]))];//読み込むモデルの最大数+1
//THING C3DObj::Thing[sizeof(C3DObj::ANIME_MODEL_FILES) / sizeof(ANIME_MODEL_FILES[0])];//読み込むモデルの最大数+1


LPD3DXMESH C3DObj::m_pD3DXMesh[sizeof(C3DObj::NORMAL_MODEL_FILES) / sizeof(NORMAL_MODEL_FILES[0])] = {};
DWORD C3DObj::m_dwNumMaterials[sizeof(C3DObj::NORMAL_MODEL_FILES) / sizeof(NORMAL_MODEL_FILES[0])] = {};
LPD3DXBUFFER C3DObj::m_pD3DXMtrBuffer[sizeof(C3DObj::NORMAL_MODEL_FILES) / sizeof(NORMAL_MODEL_FILES[0])] = {};
LPDIRECT3DTEXTURE9 *C3DObj::m_pTexures[sizeof(C3DObj::NORMAL_MODEL_FILES) / sizeof(NORMAL_MODEL_FILES[0])] = {};
D3DMATERIAL9 *C3DObj::m_pd3dMaterials[sizeof(C3DObj::NORMAL_MODEL_FILES) / sizeof(NORMAL_MODEL_FILES[0])] = {};

//=============================================================================
//	生成
//=============================================================================
C3DObj::C3DObj()
{
	for (m_3DObjIndex = 0; m_3DObjIndex < MAX_GAMEOBJ; m_3DObjIndex++)
	{
		if (p3DObj[m_3DObjIndex] == NULL)
		{
			p3DObj[m_3DObjIndex] = this;
			m_3DObjType = TYPE_etc;
			m_3DObjNum++;
			break;
		}
	}
	// ワーク格納失敗
	if (m_3DObjIndex >= MAX_GAMEOBJ)
	{
		m_3DObjIndex = -1;
	}

	
}

C3DObj::C3DObj(int type)
{
	// ワークに自分自身(this)を格納
	for (m_3DObjIndex = 0; m_3DObjIndex < MAX_GAMEOBJ; m_3DObjIndex++)
	{
		if (p3DObj[m_3DObjIndex] == NULL)
		{
			p3DObj[m_3DObjIndex] = this;
			m_3DObjType = type;
			m_3DObjNum++;
			break;
		}
	}
	// ワーク格納失敗
	if (m_3DObjIndex >= MAX_GAMEOBJ)
	{
		m_3DObjIndex = -1;
	}

	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixIdentity(&m_mtxTranslation);
	D3DXMatrixIdentity(&m_mtxRotation);
	D3DXMatrixIdentity(&m_mtxScaling);
	m_Enable = false;
	m_DamageFlag = false;
	m_AttakFlag = false;
}
//=============================================================================
//	破棄
//=============================================================================
C3DObj::~C3DObj()
{
	m_3DObjNum--;
	p3DObj[m_3DObjIndex] = NULL;
}





//=============================================================================
// 全オブジェクト更新
//=============================================================================
void C3DObj::UpdateAll()
{
	for (int i = 0; i < MAX_GAMEOBJ; i++)
	{
		// ポリモーフィズムによって派生クラスのUpdate()が呼ばれる
		if (p3DObj[i])
		{
			p3DObj[i]->Update();
		}
	}
}

//=============================================================================
// 全オブジェクト描画
//=============================================================================
void C3DObj::DrawAll()
{
	for (int i = 0; i < MAX_GAMEOBJ; i++)
	{
		// ポリモーフィズムによって派生クラスのDraw()が呼ばれる
		if (p3DObj[i])
		{
			p3DObj[i]->Draw();
		}
	}
}



//=============================================================================
// 全オブジェクト削除
//=============================================================================
void C3DObj::DeleteAll()
{
	for (int i = 0; i < MAX_GAMEOBJ; i++)
	{
		if (p3DObj[i])
		{
			delete p3DObj[i];
			//p3DObj[i] = NULL;
		}
	}
}


//=============================================================================
// インスタンス取得
//=============================================================================
C3DObj *C3DObj::Get(int nIdx)
{
	// インデックスが範囲外
	if (p3DObj[nIdx])
	{
		return p3DObj[nIdx];
	}
	return NULL;
}


//=============================================================================
// オブジェクト削除
//=============================================================================
void C3DObj::C3DObj_delete(void)
{
	C3DObj *pobj = Get(Get_3DObjIndex());
	delete pobj;
}



//=============================================================================
// モデル読み込み
//=============================================================================
// Geometryの初期化（モデルの読み込み）
HRESULT C3DObj::InitModelLoad()
{
	//通常モデル読み込み	
	for (int i = 0; i < MODEL_FILES_MAX; i++)
	{
		InitThing(&Thing_Normal[i], NORMAL_MODEL_FILES[i].filename);
		InitSphere(m_pD3DDevice, &Thing_Normal[i]);//当たり判定の表示
	}

	//アニメーションモデル読み込み
	//THINGにxファイルを読み込む
	/*for (int i = 0; i < ANIME_MODEL_FILES_MAX; i++)
	{
		SkinMesh.InitThing(m_pD3DDevice, &Thing[i], ANIME_MODEL_FILES[i].filename);
		SkinMesh.InitSphere(m_pD3DDevice, &Thing[i]);
	}*/
	return S_OK;
}

HRESULT C3DObj::InitThing(THING_NORMAL *pThing, LPSTR szXFileName)
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

//=============================================================================
// モデル破棄
//=============================================================================
void C3DObj::Model_Finalize(void)	//	モデルデータの開放　複数化したら全部消すかどれかを消す
{
	for (int i = 0;i < MODEL_FILES_MAX;i++)
	{
		if (m_pTexures[i] != NULL)
		{
			delete[]m_pTexures[i];
		}
		if (m_pd3dMaterials[i] != NULL)
		{
			delete[]m_pd3dMaterials[i];
		}
		if (m_pD3DXMesh[i] != NULL)
		{
			m_pD3DXMesh[i]->Release();
		}
	}
}

void C3DObj::Model_Finalize(int index)	//	モデルデータの開放　複数化したら全部消すかどれかを消す
{
	if (m_pTexures[index] != NULL)
	{
		delete[]m_pTexures[index];
	}
	if (m_pd3dMaterials[index] != NULL)
	{
		delete[]m_pd3dMaterials[index];

	}
	if (m_pD3DXMesh[index] != NULL)
	{
		m_pD3DXMesh[index]->Release();
	}
}



//=============================================================================
// モデル描画  アニメーション有
//=============================================================================
void C3DObj::DrawDX_Anime(D3DXMATRIX mtxWorld, int type, THING* pThing)
{
	//static float fAnimTimeHold = fAnimTime;
	float fAnimTimeHold = fAnimTime;
	if (boPlayAnim)
	{
		fAnimTime += 0.01f;
	}

	SKIN_MESH::UpdateSphere(m_pD3DDevice, pThing);

	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
//	m_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
//	m_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);
	//m_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	//m_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);


	D3DXMATRIXA16 mat;

	m_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//モデルレンダリング
	SkinMesh.UpdateFrameMatrices(pThing->pFrameRoot, &mtxWorld);
	SkinMesh.DrawFrame(m_pD3DDevice, pThing->pFrameRoot, pThing, true);
	pThing->pAnimController->AdvanceTime(fAnimTime - fAnimTimeHold, NULL);
	//　バウンディングスフィアのレンダリング////////	
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
	////////////////////////////////
	//アニメ再生時間を+
/*	fAnimTimeHold = fAnimTime;
	if (boPlayAnim)
	{
		fAnimTime += 0.01f;
	}*/
}



//=============================================================================
// モデル描画  アニメーション無
//=============================================================================
void C3DObj::DrawDX_Normal(D3DXMATRIX mtxWorld, int type, THING_NORMAL* pThing)
{
	
	//m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	m_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);


	// マトリックスのセット
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//モデルのレンダリング
	for (DWORD i = 0; i<pThing->dwNumMaterials; i++)
	{
		m_pD3DDevice->SetMaterial(&pThing->pMeshMaterials[i]);
		m_pD3DDevice->SetTexture(0, pThing->pMeshTextures[i]);
		pThing->pMesh->DrawSubset(i);
	}
	//　バウンディングスフィアのレンダリング	
	if (boRenderSphere && pThing->pSphereMeshMaterials)
	{
		m_pD3DDevice->SetTexture(0, NULL);
		m_pD3DDevice->SetMaterial(pThing->pSphereMeshMaterials);
		pThing->pSphereMesh->DrawSubset(0);
	}

}

// モデル描画  アニメーション無 コリジョン位置変更
void C3DObj::DrawDX_NormalAdd(D3DXMATRIX mtxWorld, int type, THING_NORMAL* pThing, D3DXVECTOR3 position)
{

	//m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	m_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);


	// マトリックスのセット
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//モデルのレンダリング
	for (DWORD i = 0; i<pThing->dwNumMaterials; i++)
	{
		m_pD3DDevice->SetMaterial(&pThing->pMeshMaterials[i]);
		m_pD3DDevice->SetTexture(0, pThing->pMeshTextures[i]);
		pThing->pMesh->DrawSubset(i);
	}
	D3DXMATRIX mtx;
	D3DXMatrixTranslation(&mtx, mtxWorld._41 + position.x, mtxWorld._42 + position.y, mtxWorld._43 + position.z);
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &mtx);
	//　バウンディングスフィアのレンダリング	
	if (boRenderSphere && pThing->pSphereMeshMaterials)
	{
		m_pD3DDevice->SetTexture(0, NULL);
		m_pD3DDevice->SetMaterial(pThing->pSphereMeshMaterials);
		pThing->pSphereMesh->DrawSubset(0);
	}

}

//=============================================================================
// 当たり判定
//=============================================================================

void C3DObj::HitCheck(void)
{
	//ノーマルモデル対ノーマルモデル
	/*
	if (Collision_NomalVSNormal(&Thing_Normal[0], &Thing_Normal[1]))
	{
		DebugFont_Draw(500, 300, "当たったぞ！！！！！！！！！！！");
	}
	else
	{
		DebugFont_Draw(500, 500, "当たってないぞ！！！！！！！！！！！");
	}*/
	//DebugFont_Draw(200, 50, "エネミーポジション= X= %f Y= %f Z = %f", Thing[0].vPosition.x, Thing[0].vPosition.y, Thing[0].vPosition.z);
	//DebugFont_Draw(200, 80, "プレイヤーポジション= X= %f Y= %f Z = %f", Thing_Normal[0].vPosition.x, Thing_Normal[0].vPosition.y, Thing_Normal[0].vPosition.z);
	//アニメ対ノーマル
	/*if (Collision_AnimeVSNormal(&Thing[0], &Thing_Normal[0]))
	{
		DebugFont_Draw(500, 300, "当たったぞ！！");
	}
	else
	{
		DebugFont_Draw(500, 500, "当たってないぞ！！！！！！！！！！！");
	}*/
	if (Collision_AnimeVSNormal(&Thing, &Thing_Normal[0]))
	{
	DebugFont_Draw(500, 300, "当たったぞ！！");
	}
	else
	{
	DebugFont_Draw(500, 500, "当たってないぞ！！！！！！！！！！！");
	}
	/*
	//アニメ対アニメ
	if (Collision_AnimeVSAnime(&Thing[0], &Thing[0]))
	{
		DebugFont_Draw(500, 300, "当たったぞ！！");
	}
	else
	{
		DebugFont_Draw(500, 500, "当たってないぞ！！！！！！！！！！！");
	}*/
}

bool C3DObj::Collision_NomalVSNormal(THING_NORMAL* pThingA, THING_NORMAL* pThingB)
{
	//２つの物体の中心間の距離を求める
	D3DXVECTOR3 vLength = pThingB->vPosition - pThingA->vPosition;
	FLOAT fLength = D3DXVec3Length(&vLength);
	// その距離が、2物体の半径を足したものより小さいということは、
	//境界球同士が重なっている（衝突している）ということ
	if (fLength <= pThingA->Sphere.fRadius + pThingB->Sphere.fRadius)
	{
		return true;
	}
	return false;
}

bool C3DObj::Collision_AnimeVSNormal(THING* pThingA, THING_NORMAL* pThingB)
{
	//２つの物体の中心間の距離を求める
	D3DXVECTOR3 vLength = pThingB->vPosition - pThingA->vPosition;
	FLOAT fLength = D3DXVec3Length(&vLength);
	// その距離が、2物体の半径を足したものより小さいということは、
	//境界球同士が重なっている（衝突している）ということ
	if (fLength <= pThingA->Sphere.fRadius + pThingB->Sphere.fRadius)
	{
		return true;
	}
	return false;
}

bool C3DObj::Collision_AnimeVSAnime(THING* pThingA, THING* pThingB)
{
	//２つの物体の中心間の距離を求める
	D3DXVECTOR3 vLength = pThingB->vPosition - pThingA->vPosition;
	FLOAT fLength = D3DXVec3Length(&vLength);
	// その距離が、2物体の半径を足したものより小さいということは、
	//境界球同士が重なっている（衝突している）ということ
	if (fLength <= pThingA->Sphere.fRadius + pThingB->Sphere.fRadius)
	{
		return true;
	}
	return false;
}

THING* C3DObj::GetAnimeModel(void)
{
	return &Thing;
}

THING_NORMAL* C3DObj::GetNormalModel(int index)
{
	return &Thing_Normal[index];
}

//=============================================================================
// アニメーション変更
//=============================================================================

void C3DObj::Animation_Change(int index, float speed)
{
	if (TrackDesc.Speed != speed)
	{
		TrackDesc.Speed = speed;//モーションスピード
		Thing.pAnimController->SetTrackDesc(0, &TrackDesc);//アニメ情報セット
	}
	Thing.pAnimController->SetTrackAnimationSet(0, pAnimSet[index]);

}

void C3DObj::DamageFlag_Change(void)
{
	if (m_DamageFlag)
	{
		m_DamageFlag = false;
	}
	else
	{
		m_DamageFlag = true;
	}
}

void C3DObj::Position_Keep(D3DXMATRIX mtxT)
{
	m_PosKeep = D3DXVECTOR3(mtxT._41, mtxT._42, mtxT._43);
}

void C3DObj::Add_Mp(int mp)
{
	C3DObj *pplayer = CPlayer::Get_Player();
	pplayer->m_Mp += mp;

	while (pplayer->m_Mp >= MP_MAX)
	{
		pplayer->m_Mp -= MP_MAX;
		pplayer->m_MpStock++;
	}

}

void C3DObj::Attraction_Delete(void)
{
	for (int i = 0; i < MAX_GAMEOBJ; i++)
	{
		if (p3DObj[i])
		{
			if ((p3DObj[i]->m_3DObjType == TYPE_ATTRACTION)|| (p3DObj[i]->m_3DObjType == TYPE_POPCORN)|| (p3DObj[i]->m_3DObjType == TYPE_STADBY)|| (p3DObj[i]->m_3DObjType == TYPE_COASTER))
			{
				delete p3DObj[i];
			}
		}
	}
}

void C3DObj::Add_Hp(void)
{
	C3DObj *pplayer = CPlayer::Get_Player();
	pplayer->m_Hp++;
	if (pplayer->m_Hp > HP_MAX)
	{
		pplayer->m_Hp = HP_MAX;
	}
}