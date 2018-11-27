//////////////////////////////////////////////////
////
////	メッシュフィールドシリンダークラス
////
//////////////////////////////////////////////////



//=============================================================================
//	インクルードファイル
//=============================================================================

#include "CMeshField_Cylinder.h"

//=============================================================================
//	定数定義
//=============================================================================


//=============================================================================
//	静的変数
//=============================================================================

CMeshField_Cylinder *CMeshField_Cylinder::m_pMeshField_Cylinder;

//=============================================================================
//	生成
//=============================================================================

CMeshField_Cylinder::CMeshField_Cylinder()
{

}
CMeshField_Cylinder::CMeshField_Cylinder(int TexIndex, float meshH, float radius, int meshXnum, int meshYnum)
{
	m_TexIndex = TexIndex;
	m_meshH = meshH;
	m_meshWnum = meshXnum;
	m_meshHnum = meshYnum;
	m_radius = radius;
	m_VertexW = meshXnum + 1;
	m_VertexH = meshYnum + 1;
	m_VertexCount = m_VertexW * m_VertexH;
	m_IndexCount = (meshXnum + 2) * (meshYnum * 2) - 2;
	m_PrimitiveCount = (meshXnum * 2 + 4) * meshYnum - 4;
	MeshField_Cylinder_Initialize();
}
//=============================================================================
//	破棄
//=============================================================================

CMeshField_Cylinder::~CMeshField_Cylinder()
{
	
}

//	更新
void CMeshField_Cylinder::Update(void)
{

}

//	描画
void CMeshField_Cylinder::Draw(void)
{
	CMeshField::Draw();
}


//	メッシュフィールドシリンダー作成
CMeshField_Cylinder *CMeshField_Cylinder::MeshField_Cylinder_Create(int TexIndex, float meshH, float radius, int meshXnum, int meshYnum)
{
	m_pMeshField_Cylinder = new CMeshField_Cylinder(TexIndex, meshH, radius, meshXnum, meshYnum);
	return m_pMeshField_Cylinder;
}

//	終了処理
void CMeshField_Cylinder::Finalize(void)
{

	// インデックスバッファの解放
	if (m_pIndexBuffer != NULL)
	{
		m_pIndexBuffer->Release();
		m_pIndexBuffer = NULL;
	}

	// 頂点バッファの解放
	if (m_pVertexBuffer != NULL)
	{
		m_pVertexBuffer->Release();
		m_pVertexBuffer = NULL;
	}
	if (m_pMeshField_Cylinder != NULL)
	{
		delete m_pMeshField_Cylinder;
	}
}



//	メッシュフィールドシリンダー初期化(頂点設定)
void CMeshField_Cylinder::MeshField_Cylinder_Initialize(void)
{
	// 頂点バッファの確保
	m_pD3DDevice->CreateVertexBuffer(sizeof(MeshFieldVertex) * m_VertexCount, D3DUSAGE_WRITEONLY, FVF_MESH_FIELD_VERTEX, D3DPOOL_MANAGED, &m_pVertexBuffer, NULL);
	// インデックスバッファの確保
	m_pD3DDevice->CreateIndexBuffer(sizeof(WORD) * m_IndexCount, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIndexBuffer, NULL);


	for (int h = 0;h < m_VertexH;h++)
	{
		for (int w = 0;w < m_VertexW;w++)
		{
			int n = w + m_VertexW * h;
			float angle = 360 / m_meshWnum * w;
			m_Mfield[n].pos = D3DXVECTOR3(m_radius * sinf(D3DXToRadian(angle)), m_meshHnum * m_meshH - (h * m_meshH), m_radius * cosf(D3DXToRadian(angle)));
			m_Mfield[n].color = D3DCOLOR(0xffff0000);
			m_Mfield[n].uv = D3DXVECTOR2(w * (1.0f / m_meshWnum), h * (1.0f / m_meshHnum));
		}
	}

	Buffer_Write();
}





