//////////////////////////////////////////////////
////
////	3Dオブジェクトクラス
////
//////////////////////////////////////////////////

#include "C3DObj.h"
#include "debug_font.h"
#include "CTexture.h"

//=============================================================================
//	静的変数
//===========================================================================
C3DObj *C3DObj::p3DObj[MAX_GAMEOBJ];
int C3DObj::m_3DObjNum = 0;

C3DObj::MaterialFileData C3DObj::MODEL_FILES[] = {
	{ "asset/model/emi-ru2.x" },
	{ "asset/model/zako.x" },
	{ "asset/model/boss.x" },
	{ "asset/model/CoffeeCup.blend.x" },
	{ "asset/model/dish.blend.x" },
	{ "asset/model/enban.x" },
	{ "asset/model/hasira.x" },
	{ "asset/model/ferris.x" },
	{ "asset/model/coaster.x" },
};

int C3DObj::MODEL_FILES_MAX = sizeof(C3DObj::MODEL_FILES) / sizeof(MODEL_FILES[0]);


LPD3DXMESH C3DObj::m_pD3DXMesh[sizeof(C3DObj::MODEL_FILES) / sizeof(MODEL_FILES[0])] = {};
DWORD C3DObj::m_dwNumMaterials[sizeof(C3DObj::MODEL_FILES) / sizeof(MODEL_FILES[0])] = {};
LPD3DXBUFFER C3DObj::m_pD3DXMtrBuffer[sizeof(C3DObj::MODEL_FILES) / sizeof(MODEL_FILES[0])] = {};
LPDIRECT3DTEXTURE9 *C3DObj::m_pTexures[sizeof(C3DObj::MODEL_FILES) / sizeof(MODEL_FILES[0])] = {};
D3DMATERIAL9 *C3DObj::m_pd3dMaterials[sizeof(C3DObj::MODEL_FILES) / sizeof(MODEL_FILES[0])] = {};

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
void C3DObj::Model_Load(void)
{


	HRESULT hr;
	for (int index = 0;index < MODEL_FILES_MAX;index++)
	{
		hr = D3DXLoadMeshFromX(MODEL_FILES[index].filename, D3DXMESH_MANAGED, m_pD3DDevice, NULL, &m_pD3DXMtrBuffer[index], NULL, &m_dwNumMaterials[index], &m_pD3DXMesh[index]);
		if (FAILED(hr))
		{
			MessageBox(NULL, "モデルデータを読み込めませんでした", "確認", MB_OK);
		}
		/*
		第1引数　ファイル名
		第2引数　65535以上の頂点が必要なら
		D3DXMESH_MANAGED | D3DXMESH_WRITEONLY | D3DXMESH_32BIT にする
		第3引数　デバイス
		第4引数　NULL　g_pD3DXAdjacencyBuffer
		第5引数　g_pD3DXMtrBuffer
		第6引数　dwNumMaterials
		第7引数　g_pD3DXMesh
		*/

		//	マテリアル保存用配列の確保
		m_pd3dMaterials[index] = new D3DMATERIAL9[m_dwNumMaterials[index]];
		m_pTexures[index] = new LPDIRECT3DTEXTURE9[m_dwNumMaterials[index]];

		//	マテリアル情報バッファのポインタ取得
		D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)m_pD3DXMtrBuffer[index]->GetBufferPointer();

		//	各マテリアル情報を保存
		for (int i = 0;i < m_dwNumMaterials[index];i++)
		{
			m_pd3dMaterials[index][i] = d3dxMaterials[i].MatD3D;	//	Xファイルのマテリアルカラーのコピー
																	/*
																	ディフーズ
																	アンビエント
																	エミッシブ		ライト関係なし　自己発光
																	スペキュラ
																	*/
			m_pd3dMaterials[index][i].Ambient = m_pd3dMaterials[index][i].Diffuse;

			//	テクスチャの読み込み
			if (d3dxMaterials[i].pTextureFilename == NULL)	//	テクスチャがないマテリアルはファイル名なし
			{
				m_pTexures[index][i] = NULL;
			}
			else
			{
				hr = D3DXCreateTextureFromFile(m_pD3DDevice, d3dxMaterials[i].pTextureFilename, &m_pTexures[index][i]);
				if (FAILED(hr))
				{
					m_pTexures[index][i] = NULL;
					MessageBox(NULL, "テクスチャデータを読み込めませんでした", "確認", MB_OK);
				}
			}
		}

		//	Xファイルから読み込んだマテリアル情報のバッファを解放
		if (m_pD3DXMtrBuffer)
		{
			m_pD3DXMtrBuffer[index]->Release();
		}
	}
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
// モデル描画
//=============================================================================
void C3DObj::Model_Draw(int index, D3DXMATRIX mtxWorld)		//	複数化したら引数を変える　行列
{
	//m_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	//m_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);

	m_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
	m_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	for (int i = 0;i < m_dwNumMaterials[index];i++)
	{
		m_pD3DDevice->SetMaterial(&m_pd3dMaterials[index][i]);
		m_pD3DDevice->SetTexture(0, m_pTexures[index][i]);
		m_pD3DXMesh[index]->DrawSubset(i);
	}
}

void C3DObj::Model_Draw(int index, D3DXMATRIX mtxWorld, int texIndex)		//	複数化したら引数を変える　行列
{
	//m_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	//m_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);

	m_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
	m_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	m_pD3DDevice->SetTexture(0, CTexture::Texture_GetTexture(texIndex));
	for (int i = 0;i < m_dwNumMaterials[index];i++)
	{
		m_pD3DDevice->SetMaterial(&m_pd3dMaterials[index][i]);
		//m_pD3DDevice->SetTexture(0, m_pTexures[index][i]);
		m_pD3DXMesh[index]->DrawSubset(i);
	}
}




