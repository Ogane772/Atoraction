//=============================================================================
//	インクルードファイル
//=============================================================================

#include <d3dx9.h>
#include "mochi_d3d.h"
#include "common.h"
#include "ten_texture.h"

#include "CGameObj.h"
//=============================================================================
//	定数定義
//=============================================================================

#define MAX_MESH_FIELD (5000)

//=============================================================================
//	グローバル宣言
//=============================================================================

//3Dポリゴン頂点　構造体
typedef struct
{
	D3DXVECTOR3 pos;	//	座標x,y,z
	D3DXVECTOR3 normal;
	D3DCOLOR color;
	D3DXVECTOR2 uv;		//  テクスチャ

}MeshFieldVertex;

#define FVF_MESH_FIELD_VERTEX (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)	//	構造体のすぐ下に書く

static MeshFieldVertex g_Mfield[MAX_MESH_FIELD];

static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer[3] = { NULL };
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer[3] = { NULL };

static int g_VertexCount[3] = { 0 };
static int g_PrimitiveCount[3] = { 0 };

void Mesh_Field_Initialize(float meshW, int meshXnum, int meshZnum)
{
	int meshXX = meshXnum + 1;	//	最大頂点X
	int meshZZ = meshZnum + 1;	//	最大頂点Z
	
	g_VertexCount[0] = (meshXX) * (meshZZ);
	int IndexCount = (meshXnum + 2) * (meshZnum * 2) - 2;
	g_PrimitiveCount[0] = (meshXnum * 2 + 4) * meshZnum - 4;


	LPDIRECT3DDEVICE9 pD3DDevice = mochi_GetDevice();
	// 頂点バッファの確保
	pD3DDevice->CreateVertexBuffer(sizeof(MeshFieldVertex) * g_VertexCount[0], D3DUSAGE_WRITEONLY, FVF_MESH_FIELD_VERTEX, D3DPOOL_MANAGED, &g_pVertexBuffer[0], NULL);
	// インデックスバッファの確保
	pD3DDevice->CreateIndexBuffer(sizeof(WORD) * IndexCount, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer[0], NULL);

	for (int z = 0;z < meshZZ;z++)
	{
		for (int x = 0;x < meshXX;x++)
		{
			int n = x + meshXX * z;
			g_Mfield[n].pos = D3DXVECTOR3(((float)meshXnum * 0.5f * -meshW) + (meshW * x), 0, ((float)meshZnum * 0.5 * meshW) + (-meshW * z));
			g_Mfield[n].normal = D3DXVECTOR3(0.0, 1.0, 0.0);
			g_Mfield[n].color = D3DCOLOR(0xffffffff);
			g_Mfield[n].uv = D3DXVECTOR2(x * (1.0f/ meshXnum), z * (1.0f / meshZnum));
		}
		
	}

	// 仮想アドレス　
	MeshFieldVertex *pv;
	// 頂点バッファのロック
	g_pVertexBuffer[0]->Lock(0, 0, (void**)&pv, 0);

	//memcpy(pv, g_Mfield, sizeof(g_Mfield[MAX_MESH_FIELD]));
	for (int i = 0;i < g_VertexCount[0];i++)
	{
		pv[i] = g_Mfield[i];
	}
	g_pVertexBuffer[0]->Unlock();

	// 仮想アドレス　
	WORD *Ipv;
	// インデックスバッファのロック
	g_pIndexBuffer[0]->Lock(0, 0, (void**)&Ipv, 0);

	for (int z = 0;z < meshZnum * 2 - 1;z++)
	{
		if (z < meshZnum)
		{
			for (int x = 0;x < meshXX * 2;x++)
			{
				if (x % 2 == 0)
				{
					Ipv[(meshXX + 1) * (2 * z) + x] = meshXX + (meshXX * z) + (x * 0.5);
				}
				else
				{
					Ipv[(meshXX + 1) * (2 * z) + x] = (meshXX * z) + ((x - 1) * 0.5);
				}
			}
		}
		else
		{
			Ipv[(meshXX * 2)*(z - meshZnum + 1) + (2 * (z - meshZnum))] = meshXX * (z - meshZnum + 1) - 1;
			Ipv[(meshXX * 2)*(z - meshZnum + 1) + (2 * (z - meshZnum)) + 1] = meshXX * (z - meshZnum + 2);
		}
	}

	g_pIndexBuffer[0]->Unlock();
}

void Mesh_Cylinder_Initialize(float meshH, float radius, int meshXnum, int meshYnum)
{
	int VertexX = meshXnum + 1;	//	最大頂点X
	int VertexY = meshYnum + 1;	//	最大頂点Z

	g_VertexCount[1] = (VertexX)* (VertexY);
	int IndexCount = (meshXnum + 2) * (meshYnum * 2) - 2;
	g_PrimitiveCount[1] = (meshXnum * 2 + 4) * meshYnum - 4;


	LPDIRECT3DDEVICE9 pD3DDevice = mochi_GetDevice();
	// 頂点バッファの確保
	pD3DDevice->CreateVertexBuffer(sizeof(MeshFieldVertex) * g_VertexCount[1], D3DUSAGE_WRITEONLY, FVF_MESH_FIELD_VERTEX, D3DPOOL_MANAGED, &g_pVertexBuffer[1], NULL);
	// インデックスバッファの確保
	pD3DDevice->CreateIndexBuffer(sizeof(WORD) * IndexCount, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer[1], NULL);



	for (int y = 0;y < VertexY;y++)
	{
		for (int x = 0;x < VertexX;x++)
		{
			int n = x + VertexX * y;
			float angle = 360 / meshXnum * x;
			g_Mfield[n].pos = D3DXVECTOR3(radius * sinf(D3DXToRadian(angle)), meshYnum * meshH - (y * meshH), radius * cosf(D3DXToRadian(angle)));
			g_Mfield[n].normal = D3DXVECTOR3(0.0, 1.0, 0.0);
			g_Mfield[n].color = D3DCOLOR(0xffff0000);
			g_Mfield[n].uv = D3DXVECTOR2(x * (1.0f / meshXnum), y * (1.0f / meshYnum));
		}
	}

	// 仮想アドレス　
	MeshFieldVertex *pv;
	// 頂点バッファのロック
	g_pVertexBuffer[1]->Lock(0, 0, (void**)&pv, 0);

	//memcpy(pv, g_Mfield, sizeof(g_Mfield[MAX_MESH_FIELD]));
	for (int i = 0;i < g_VertexCount[1];i++)
	{
		pv[i] = g_Mfield[i];
	}
	g_pVertexBuffer[1]->Unlock();

	// 仮想アドレス　
	WORD *Ipv;
	// インデックスバッファのロック
	g_pIndexBuffer[1]->Lock(0, 0, (void**)&Ipv, 0);

	for (int y = 0;y < meshYnum * 2 - 1;y++)
	{
		if (y < meshYnum)
		{
			for (int x = 0;x < VertexX * 2;x++)
			{
				if (x % 2 == 0)
				{
					Ipv[(VertexX + 1) * (2 * y) + x] = VertexX + (VertexX * y) + (x * 0.5);
				}
				else
				{
					Ipv[(VertexX + 1) * (2 * y) + x] = (VertexX * y) + ((x - 1) * 0.5);
				}
			}
		}
		else
		{
			Ipv[(VertexX * 2)*(y - meshYnum + 1) + (2 * (y - meshYnum))] = VertexX * (y - meshYnum + 1) - 1;
			Ipv[(VertexX * 2)*(y - meshYnum + 1) + (2 * (y - meshYnum)) + 1] = VertexX * (y - meshYnum + 2);
		}
	}

	g_pIndexBuffer[1]->Unlock();

}

void Mesh_Skydome_Initialize(float meshH, float radius, int meshXnum, int meshYnum)
{
	int VertexX = meshXnum + 1;	//	最大頂点X
	int VertexY = meshYnum + 1;	//	最大頂点Z

	g_VertexCount[2] = (VertexX)* (VertexY);
	int IndexCount = (meshXnum + 2) * (meshYnum * 2) - 2;
	g_PrimitiveCount[2] = (meshXnum * 2 + 4) * meshYnum - 4;


	LPDIRECT3DDEVICE9 pD3DDevice = mochi_GetDevice();
	// 頂点バッファの確保
	pD3DDevice->CreateVertexBuffer(sizeof(MeshFieldVertex) * g_VertexCount[2], D3DUSAGE_WRITEONLY, FVF_MESH_FIELD_VERTEX, D3DPOOL_MANAGED, &g_pVertexBuffer[2], NULL);
	// インデックスバッファの確保
	pD3DDevice->CreateIndexBuffer(sizeof(WORD) * IndexCount, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer[2], NULL);

	float Subtotal = 0;

	for (int y = 0;y < VertexY;y++)
	{
		if (y == 0)
		{
			for (int x = 0;x < VertexX;x++)
			{
				int n = x + VertexX * y;
				g_Mfield[n].pos = D3DXVECTOR3(0, meshYnum * meshH,0);
				g_Mfield[n].normal = D3DXVECTOR3(0.0, 1.0, 0.0);
				//g_Mfield[n].color = D3DCOLOR(0xff0000ff);
				g_Mfield[n].color = D3DCOLOR_ARGB(255,255,255,255);
				g_Mfield[n].uv = D3DXVECTOR2(x * (1.0f / meshXnum), y * (1.0f / meshYnum));
			}
		}
		else
		{

			Subtotal += (y * meshH / VertexY)*2;
			for (int x = 0;x < VertexX;x++)
			{
				int n = x + VertexX * y;
				float angle = 360 / meshXnum * x;
				
				g_Mfield[n].pos = D3DXVECTOR3(radius / VertexY * y * sinf(D3DXToRadian(angle)), (meshYnum * meshH) - Subtotal, radius / VertexY * y * cosf(D3DXToRadian(angle)));
				g_Mfield[n].normal = D3DXVECTOR3(0.0, 1.0, 0.0);
				g_Mfield[n].color = D3DCOLOR_ARGB(255, 255, 255, 255);
				//g_Mfield[n].color = D3DCOLOR_ARGB(255, (255 / (VertexY-1)) * y, (255 / (VertexY-1)) * y, (255 / (VertexY-1)) * y);
				g_Mfield[n].uv = D3DXVECTOR2(x * (1.0f / meshXnum), y * (1.0f / meshYnum));
			}
		}
		
	}

	// 仮想アドレス　
	MeshFieldVertex *pv;
	// 頂点バッファのロック
	g_pVertexBuffer[2]->Lock(0, 0, (void**)&pv, 0);

	//memcpy(pv, g_Mfield, sizeof(g_Mfield[MAX_MESH_FIELD]));
	for (int i = 0;i < g_VertexCount[2];i++)
	{
		pv[i] = g_Mfield[i];
	}
	g_pVertexBuffer[2]->Unlock();

	// 仮想アドレス　
	WORD *Ipv;
	// インデックスバッファのロック
	g_pIndexBuffer[2]->Lock(0, 0, (void**)&Ipv, 0);

	for (int y = 0;y < meshYnum * 2 - 1;y++)
	{
		if (y < meshYnum)
		{
			for (int x = 0;x < VertexX * 2;x++)
			{
				if (x % 2 == 0)
				{
					Ipv[(VertexX + 1) * (2 * y) + x] = VertexX + (VertexX * y) + (x * 0.5);
				}
				else
				{
					Ipv[(VertexX + 1) * (2 * y) + x] = (VertexX * y) + ((x - 1) * 0.5);
				}
			}
		}
		else
		{
			Ipv[(VertexX * 2)*(y - meshYnum + 1) + (2 * (y - meshYnum))] = VertexX * (y - meshYnum + 1) - 1;
			Ipv[(VertexX * 2)*(y - meshYnum + 1) + (2 * (y - meshYnum)) + 1] = VertexX * (y - meshYnum + 2);
		}
	}

	g_pIndexBuffer[2]->Unlock();

}


void Mesh_Field_Finalize(void)
{
	for (int i = 0;i < 3;i++)
	{
		// インデックスバッファの解放
		if (g_pIndexBuffer[i] != NULL)
		{
			g_pIndexBuffer[i]->Release();
			g_pIndexBuffer[i] = NULL;
		}

		// 頂点バッファの解放
		if (g_pVertexBuffer[i] != NULL)
		{
			g_pVertexBuffer[i]->Release();
			g_pVertexBuffer[i] = NULL;
		}
	}
}

void Mesh_Field_Draw(int index)
{


	//デバイス
	LPDIRECT3DDEVICE9 pD3DDevice = mochi_GetDevice();

	//]pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
	//pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);

	//pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	//pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);

	D3DXMATRIX mtxWorld;		// 4*4行列　d3dx9.h必要
	D3DXMATRIX mtxTranslation;
	D3DXMATRIX mtxRotation;
	D3DXMATRIX mtxScaling;
	//D3DXMatrixIdentity(&mtxWorld);	// アドレス送ると単位行列を作ってくれる

	D3DXMatrixRotationZ(&mtxRotation, D3DXToRadian(0));
	D3DXMatrixTranslation(&mtxTranslation, 0, 0, 0);
	
	mtxWorld = mtxRotation*mtxTranslation;
	//pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	pD3DDevice->SetFVF(FVF_MESH_FIELD_VERTEX);
	pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	if (index == 0)
	{
		pD3DDevice->SetTexture(0, Texture_GetTexture(1));
	}
	if (index == 2)
	{
		pD3DDevice->SetTexture(0, Texture_GetTexture(3));
	}

	pD3DDevice->SetStreamSource(0, g_pVertexBuffer[index], 0, sizeof(MeshFieldVertex));
	pD3DDevice->SetIndices(g_pIndexBuffer[index]);
	pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_VertexCount[index], 0, g_PrimitiveCount[index]);



}


