//=============================================================================
//	インクルードファイル
//=============================================================================

#include <d3dx9.h>
#include "mochi_d3d.h"
#include "common.h"
//=============================================================================
//	定数定義
//=============================================================================

//=============================================================================
//	グローバル宣言
//=============================================================================

//3Dポリゴン頂点　構造体
typedef struct
{
	D3DXVECTOR3 pos;	//	座標x,y,z
	D3DCOLOR color;		//  色

}GridVertex;

#define FVF_CUBE_VERTEX3D (D3DFVF_XYZ|D3DFVF_DIFFUSE)	//	構造体のすぐ下に書く

// TRIANGLELIST 頂点座標
static GridVertex g_grid[44];


static int angle = 0;

//=============================================================================
//	初期化処理
//=============================================================================

void Grid_Initialize(void)
{
	for (int i = 0;i < 22;i++)
	{
		if (i % 2 == 0)
		{
			g_grid[i].pos = D3DXVECTOR3(-5.0 + i - (i * 0.5), 0, 5.0);
			g_grid[i].color = D3DCOLOR(0xff00ff00);
		}
		else
		{
			g_grid[i].pos = D3DXVECTOR3(-5.0 + ((i - 1) * 0.5), 0, -5.0);
			g_grid[i].color = D3DCOLOR(0xff00ff00);
		}

	}

	for (int i = 0;i < 22;i++)
	{
		if (i % 2 == 0)
		{
			g_grid[i + 22].pos = D3DXVECTOR3(-5.0, 0, -5.0 + i - (i  * 0.5));
			g_grid[i + 22].color = D3DCOLOR(0xff00ff00);
		}
		else
		{
			g_grid[i + 22].pos = D3DXVECTOR3(5.0, 0, -5.0 + ((i - 1)  * 0.5));
			g_grid[i + 22].color = D3DCOLOR(0xff00ff00);
		}

	}
	g_grid[10].color = D3DCOLOR(0xffefb864);
	g_grid[11].color = D3DCOLOR(0xffefb864);
	g_grid[32].color = D3DCOLOR(0xffefb864);
	g_grid[33].color = D3DCOLOR(0xffefb864);
}

//=============================================================================
//	終了処理
//=============================================================================

void Grid_Finalize(void)
{

}

//=============================================================================
//	更新処理
//=============================================================================

void Grid_Updata(void)
{

}

//=============================================================================
//	描画処理
//=============================================================================

void Grid_Draw(void)
{

	//デバイス
	LPDIRECT3DDEVICE9 g_pD3DDevice = mochi_GetDevice();
//	g_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
//	g_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);
	// ワールド座標変換行列
	D3DXMATRIX mtxWorld;		// 4*4行列　d3dx9.h必要
	D3DXMatrixIdentity(&mtxWorld);	// アドレス送ると単位行列を作ってくれる


									//	ワールド変換行列設定
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);




	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	g_pD3DDevice->SetFVF(FVF_CUBE_VERTEX3D);		//	FVFをデバイスに設定


	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, 22, g_grid, sizeof(GridVertex));



	/*
	第1引数　どんな形か
	第2引数　プリミティブ数　三角形をいくつだすか
	第3引数  頂点データの先頭アドレス
	第4引数　頂点データ構造体の大きさ
	*/
}