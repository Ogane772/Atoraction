//=============================================================================
//	インクルードファイル
//=============================================================================

#include <d3dx9.h>
//#include <math.h>
#include "mochi_d3d.h"

//=============================================================================
//	定数定義
//=============================================================================

#define CIRCLE_VERTEX_COUNT (8)
#define CIRCLE_DRAW_MAX (2048)

//=============================================================================
//	グローバル変数宣言
//=============================================================================

typedef struct DebugVertex_tag
{
	D3DXVECTOR4 position;
	D3DCOLOR color;
} DebugVertex;
#define FVF_DEBUG_VERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;

static int g_CircleCount = 0;
static DebugVertex* g_pDebugVertex = NULL;
static WORD* g_pDebugVertexIndex = NULL;

//=============================================================================
//	初期化処理
//=============================================================================

void DebugPrimitive_Initialize(void)
{
	LPDIRECT3DDEVICE9 pDevice = mochi_GetDevice();
	pDevice->CreateVertexBuffer(sizeof(DebugVertex)*CIRCLE_VERTEX_COUNT*CIRCLE_DRAW_MAX, D3DUSAGE_WRITEONLY, FVF_DEBUG_VERTEX, D3DPOOL_MANAGED, &g_pVertexBuffer, NULL);
	pDevice->CreateIndexBuffer(sizeof(WORD) * 2 * CIRCLE_DRAW_MAX, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);

	g_CircleCount = 0;

}

//=============================================================================
//	終了処理
//=============================================================================

void DebugPrimitive_Fainalize(void)
{
	if (g_pIndexBuffer != NULL)
	{
		g_pIndexBuffer->Release();
		g_pIndexBuffer = NULL;

	}
	if (g_pVertexBuffer != NULL)
	{
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;

	}
	
}

//=============================================================================
//	メモリ確保
//=============================================================================

void DebugPrimitive_BatchBegin(void)
{
	g_CircleCount = 0;

	g_pVertexBuffer->Lock(0, 0, (void**)&g_pDebugVertex, 0);
	g_pIndexBuffer->Lock(0, 0, (void**)&g_pDebugVertexIndex, 0);
}

//=============================================================================
//	描画処理
//=============================================================================

void DebugPrimitive_BatchDrawCrircle(float x, float y, float r)
{
	int n = g_CircleCount * CIRCLE_VERTEX_COUNT;

	const float s = D3DX_PI * 2 / CIRCLE_VERTEX_COUNT;
	for (int i = 0;i < CIRCLE_VERTEX_COUNT;i++)
	{
		g_pDebugVertex[n + i].position.x = cos(i * s) * r + x;
		g_pDebugVertex[n + i].position.y = sin(i * s) * r + y;
		g_pDebugVertex[n + i].position.z = 1.0f;
		g_pDebugVertex[n + i].position.w = 1.0f;
		g_pDebugVertex[n + i].color = 0xffffffff;

		g_pDebugVertexIndex[n * 2 + i * 2] = n + i;
		g_pDebugVertexIndex[n * 2 + i * 2 + 1] = n + (i + 1) % CIRCLE_VERTEX_COUNT;

	}

	g_CircleCount++;
}

//=============================================================================
//	メモリ解放
//=============================================================================

void DebugPrimitive_BatchRun(void)
{
	LPDIRECT3DDEVICE9 pDevice = mochi_GetDevice();

	g_pVertexBuffer->Unlock();
	g_pIndexBuffer->Unlock();

	pDevice->SetStreamSource(0, g_pVertexBuffer,0, sizeof(DebugVertex));
	pDevice->SetIndices(g_pIndexBuffer);
	pDevice->SetFVF(FVF_DEBUG_VERTEX);
	pDevice->SetTexture(0, NULL);
	pDevice->DrawIndexedPrimitive(D3DPT_LINELIST, 0, 0, CIRCLE_VERTEX_COUNT*CIRCLE_DRAW_MAX, 0, g_CircleCount*CIRCLE_VERTEX_COUNT);
}
