//=============================================================================
//	インクルードファイル
//=============================================================================

#include <d3dx9.h>
#include "mochi_d3d.h"
#include "common.h"
#include "input.h"
#include "ten_texture.h"
#include "move.h"
//=============================================================================
//	定数定義
//============================-=================================================

#define MAX_CUBE (8)
#define ADJUST (0.005f)
#define SAI_ROT (4.5f)
#define SAI_MOVE (0.05f)

//=============================================================================
//	グローバル宣言
//=============================================================================

//3Dポリゴン頂点　構造体
typedef struct
{
	D3DXVECTOR3 pos;	//	座標x,y,z
	D3DXVECTOR3 normal; //	法線ベクトル 座標の後 長さは1.0
	D3DCOLOR color;		//  色
	D3DXVECTOR2 uv;		//  テクスチャ

}CubeVertex3D;

#define FVF_CUBE_VERTEX3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)	//	構造体のすぐ下に書く

// 頂点バッファの確保
static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;

// TRIANGLELIST 頂点座標
static CubeVertex3D g_cube[] = {
	// 手前
	{ D3DXVECTOR3(-0.5, 0.5,-0.5),D3DXVECTOR3(0.0,0.0,-1.0),D3DCOLOR(0xffff0000),D3DXVECTOR2(0.0,0.0) },
	{ D3DXVECTOR3(0.5, 0.5,-0.5),D3DXVECTOR3(0.0,0.0,-1.0),D3DCOLOR(0xffff0000),D3DXVECTOR2(0.25,0.0) },
	{ D3DXVECTOR3(-0.5,-0.5,-0.5),D3DXVECTOR3(0.0,0.0,-1.0),D3DCOLOR(0xffff0000),D3DXVECTOR2(0.0,0.25) },

	//{ D3DXVECTOR3(0.5, 0.5,-0.5),D3DXVECTOR3(0.0,0.0,-1.0),D3DCOLOR(0xffff0000),D3DXVECTOR2(0.25,0.0) },
	{ D3DXVECTOR3(0.5,-0.5,-0.5),D3DXVECTOR3(0.0,0.0,-1.0),D3DCOLOR(0xffff0000),D3DXVECTOR2(0.25,0.25) },
	//{ D3DXVECTOR3(-0.5,-0.5,-0.5),D3DXVECTOR3(0.0,0.0,-1.0),D3DCOLOR(0xffff0000),D3DXVECTOR2(0.0,0.25) },

	//　右
	{ D3DXVECTOR3(0.5, 0.5,-0.5),D3DXVECTOR3(1.0,0.0,0.0),D3DCOLOR(0xff00ff00),D3DXVECTOR2(0.25,0.0) },
	{ D3DXVECTOR3(0.5, 0.5, 0.5),D3DXVECTOR3(1.0,0.0,0.0),D3DCOLOR(0xff00ff00),D3DXVECTOR2(0.5,0.0) },
	{ D3DXVECTOR3(0.5,-0.5,-0.5),D3DXVECTOR3(1.0,0.0,0.0),D3DCOLOR(0xff00ff00),D3DXVECTOR2(0.25,0.25) },

	//{ D3DXVECTOR3(0.5, 0.5, 0.5),D3DXVECTOR3(1.0,0.0,0.0),D3DCOLOR(0xff00ff00),D3DXVECTOR2(0.5,0.0) },
	{ D3DXVECTOR3(0.5,-0.5, 0.5),D3DXVECTOR3(1.0,0.0,0.0),D3DCOLOR(0xff00ff00),D3DXVECTOR2(0.5,0.25) },
	//{ D3DXVECTOR3(0.5,-0.5,-0.5),D3DXVECTOR3(1.0,0.0,0.0),D3DCOLOR(0xff00ff00),D3DXVECTOR2(0.25,0.25) },

	//　上
	{ D3DXVECTOR3(-0.5, 0.5, 0.5),D3DXVECTOR3(0.0,1.0,0.0),D3DCOLOR(0xff0000ff),D3DXVECTOR2(0.5,0.0) },
	{ D3DXVECTOR3(0.5, 0.5, 0.5),D3DXVECTOR3(0.0,1.0,0.0),D3DCOLOR(0xff0000ff),D3DXVECTOR2(0.75,0.0) },
	{ D3DXVECTOR3(-0.5, 0.5,-0.5),D3DXVECTOR3(0.0,1.0,0.0),D3DCOLOR(0xff0000ff),D3DXVECTOR2(0.5,0.25) },

	//{ D3DXVECTOR3(0.5, 0.5, 0.5),D3DXVECTOR3(0.0,1.0,0.0),D3DCOLOR(0xff0000ff),D3DXVECTOR2(0.75,0.0) },
	{ D3DXVECTOR3(0.5 ,0.5,-0.5),D3DXVECTOR3(0.0,1.0,0.0),D3DCOLOR(0xff0000ff),D3DXVECTOR2(0.75,0.25) },
	//{ D3DXVECTOR3(-0.5, 0.5,-0.5),D3DXVECTOR3(0.0,1.0,0.0),D3DCOLOR(0xff0000ff),D3DXVECTOR2(0.5,0.25) },

	//　奥
	{ D3DXVECTOR3(0.5, 0.5, 0.5),D3DXVECTOR3(0.0,0.0,1.0),D3DCOLOR(0xffffff00),D3DXVECTOR2(0.75,0.0) },
	{ D3DXVECTOR3(-0.5, 0.5, 0.5),D3DXVECTOR3(0.0,0.0,1.0),D3DCOLOR(0xffffff00),D3DXVECTOR2(1.0,0.0) },
	{ D3DXVECTOR3(0.5,-0.5, 0.5),D3DXVECTOR3(0.0,0.0,1.0),D3DCOLOR(0xffffff00),D3DXVECTOR2(0.75,0.25) },

	//{ D3DXVECTOR3(-0.5, 0.5, 0.5),D3DXVECTOR3(0.0,0.0,1.0),D3DCOLOR(0xffffff00),D3DXVECTOR2(1.0,0.0) },
	{ D3DXVECTOR3(-0.5,-0.5, 0.5),D3DXVECTOR3(0.0,0.0,1.0),D3DCOLOR(0xffffff00),D3DXVECTOR2(1.0,0.25) },
	//{ D3DXVECTOR3(0.5,-0.5, 0.5),D3DXVECTOR3(0.0,0.0,1.0),D3DCOLOR(0xffffff00),D3DXVECTOR2(0.75,0.25) },

	//　左
	{ D3DXVECTOR3(-0.5, 0.5, 0.5),D3DXVECTOR3(-1.0,0.0,0.0),D3DCOLOR(0xffff00ff),D3DXVECTOR2(0.0,0.25) },
	{ D3DXVECTOR3(-0.5, 0.5,-0.5),D3DXVECTOR3(-1.0,0.0,0.0),D3DCOLOR(0xffff00ff),D3DXVECTOR2(0.25,0.25) },
	{ D3DXVECTOR3(-0.5,-0.5, 0.5),D3DXVECTOR3(-1.0,0.0,0.0),D3DCOLOR(0xffff00ff),D3DXVECTOR2(0.0,0.5) },

	//{ D3DXVECTOR3(-0.5, 0.5,-0.5),D3DXVECTOR3(-1.0,0.0,0.0),D3DCOLOR(0xffff00ff),D3DXVECTOR2(0.25,0.25) },
	{ D3DXVECTOR3(-0.5,-0.5,-0.5),D3DXVECTOR3(-1.0,0.0,0.0),D3DCOLOR(0xffff00ff),D3DXVECTOR2(0.25,0.5) },
	//{ D3DXVECTOR3(-0.5,-0.5, 0.5),D3DXVECTOR3(-1.0,0.0,0.0),D3DCOLOR(0xffff00ff),D3DXVECTOR2(0.0,0.5) },

	//　下
	{ D3DXVECTOR3(-0.5,-0.5,-0.5),D3DXVECTOR3(0.0,-1.0,0.0),D3DCOLOR(0xff00ffff),D3DXVECTOR2(0.25,0.25) },
	{ D3DXVECTOR3(0.5 ,-0.5,-0.5),D3DXVECTOR3(0.0,-1.0,0.0),D3DCOLOR(0xff00ffff),D3DXVECTOR2(0.5,0.25) },
	{ D3DXVECTOR3(-0.5,-0.5, 0.5),D3DXVECTOR3(0.0,-1.0,0.0),D3DCOLOR(0xff00ffff),D3DXVECTOR2(0.25,0.5) },

	//{ D3DXVECTOR3(0.5,-0.5,-0.5),D3DXVECTOR3(0.0,-1.0,0.0),D3DCOLOR(0xff00ffff),D3DXVECTOR2(0.5,0.25) },
	{ D3DXVECTOR3(0.5,-0.5, 0.5),D3DXVECTOR3(0.0,-1.0,0.0),D3DCOLOR(0xff00ffff),D3DXVECTOR2(0.5,0.5) },
	//{ D3DXVECTOR3(-0.5,-0.5, 0.5),D3DXVECTOR3(0.0,-1.0,0.0),D3DCOLOR(0xff00ffff),D3DXVECTOR2(0.25,0.5) },
};



static float angle = 0;
static float anglex = 0.0f;
static float anglez = 0.0f;

static int count = 0;

static float x = 0.0f;
static float z = 0.0f;
static float y = 0.0f;

static float movex = 0.0f;
static float movez = 0.0f;
static float movey = 0.0f;


static bool MovecheckW = false;
static bool MovecheckS = false;
static bool MovecheckA = false;
static bool MovecheckD = false;

static bool MoveCheck = false;

static D3DCOLOR g_Color = 0xffffffff;

static D3DXMATRIX g_mtxWorldSai;
static D3DXMATRIX g_mtxRotationSai;
static D3DXMATRIX g_mtxTotalRotation;
static D3DXMATRIX g_mtxTranslation;
//=============================================================================
//	初期化処理
//=============================================================================

void Cube_Initialize(void)
{
	

	for (int i = 0;i < 36;i++)
	{
		g_cube[i].color = g_Color;
	}
	x = 0.5f;
	y = 0.5f;
	z = -3.5f;
	
	D3DXMatrixTranslation(&g_mtxWorldSai, x, y, z);
	D3DXMatrixIdentity(&g_mtxTotalRotation);
	D3DXMatrixIdentity(&g_mtxRotationSai);
	D3DXMatrixIdentity(&g_mtxTranslation);
	LPDIRECT3DDEVICE9 g_pD3DDevice = mochi_GetDevice();
	// 頂点バッファの確保
	g_pD3DDevice->CreateVertexBuffer(sizeof(CubeVertex3D) * 24, D3DUSAGE_WRITEONLY, FVF_CUBE_VERTEX3D, D3DPOOL_MANAGED, &g_pVertexBuffer, NULL);
	/*
	1 頂点のサイズ
	2 用途
	3 FVF
	4 VRAM上のメモリの管理
	5 メモ帳の場所
	6 NULL(分かんないときはNULLを入れる)
	*/

	// インデックスバッファの確保
	g_pD3DDevice->CreateIndexBuffer(sizeof(WORD) * 36, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);
	/*
	1 インデックスのサイズ
	2 用途
	3 インデックスのフォーマット(16ビットか32ビット)
	4 VRAM上のメモリの管理
	5 メモ帳の場所
	6 NULL(分かんないときはNULLを入れる)
	*/




	// 仮想アドレス　
	CubeVertex3D *pv;
	// 頂点バッファのロック
	g_pVertexBuffer->Lock(0, 0, (void**)&pv, 0);
	/*
	1 どこから
	2 0でいい
	3 仮想アドレスを入れる
	4 0でいい
	*/
	memcpy(pv, g_cube, sizeof(g_cube));
	g_pVertexBuffer->Unlock();

	// 仮想アドレス　
	WORD *Ipv;
	// インデックスバッファのロック
	g_pIndexBuffer->Lock(0, 0, (void**)&Ipv, 0);
	/*
	1 どこから
	2 0でいい
	3 仮想アドレスを入れる
	4 0でいい
	*/
	for (int i = 0;i < 6;i++) 
	{
		Ipv[(i * 6)] = (i * 4) + 0;
		Ipv[(i * 6) + 1] = (i * 4) + 1;
		Ipv[(i * 6) + 2] = (i * 4) + 2;
		Ipv[(i * 6) + 3] = (i * 4) + 1;
		Ipv[(i * 6) + 4] = (i * 4) + 3;
		Ipv[(i * 6) + 5] = (i * 4) + 2;
	}



	g_pIndexBuffer->Unlock();
}

//=============================================================================
//	終了処理
//=============================================================================

void Cube_Finalize(void)
{
	// インデックスバッファの解放
	if (g_pIndexBuffer != NULL)
	{
		g_pIndexBuffer->Release();
		g_pIndexBuffer = NULL;
	}

	// 頂点バッファの解放
	if (g_pVertexBuffer != NULL)
	{
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}

}

//=============================================================================
//	更新処理
//=============================================================================

void Cube_Updata(void)
{


	//　さいころ
	if (Keyboard_IsTrigger(DIK_T))
	{
		MovecheckW = true;
	}
	if (Keyboard_IsTrigger(DIK_G))
	{
		MovecheckS = true;	
	}
	if (Keyboard_IsTrigger(DIK_F))
	{
		MovecheckA = true;
	}
	if (Keyboard_IsTrigger(DIK_H))
	{
		MovecheckD = true;
	}

	if (Keyboard_IsPress(DIK_I) && (Keyboard_IsPress(DIK_LSHIFT)))
	{
		g_mtxTranslation *= Move(FLONT);
	}
	if (Keyboard_IsPress(DIK_K) && (Keyboard_IsPress(DIK_LSHIFT)))
	{
		g_mtxTranslation *= Move(BACK);
	}
	if (Keyboard_IsPress(DIK_L) && (Keyboard_IsPress(DIK_LSHIFT)))
	{
		g_mtxTranslation *= Move(RIGHT);
	}
	if (Keyboard_IsPress(DIK_J) && (Keyboard_IsPress(DIK_LSHIFT)))
	{
		g_mtxTranslation *= Move(LEFT);
	}

	if (MovecheckW)
	{
		count++;

		if (count <= 20)
		{
			movez = SAI_MOVE*count;
			angle = SAI_ROT * count;
			movey = sin(D3DXToRadian(angle)) - movez + ADJUST;
			D3DXMatrixRotationX(&g_mtxRotationSai, D3DXToRadian(angle));
		}
		else
		{
			count = 0;
			MovecheckW = false;
			z += 1.0;
			angle = 0;
			movez = 0;
		}
	}

	if (MovecheckS)
	{
		count++;

		if (count <= 20)
		{
			movez = -SAI_MOVE*count;
			angle = -SAI_ROT * count;
			movey = sin(D3DXToRadian(-angle)) + movez + ADJUST;
			D3DXMatrixRotationX(&g_mtxRotationSai, D3DXToRadian(angle));
		}
		else
		{
			count = 0;
			MovecheckS = false;
			z -= 1.0;
			angle = 0;
			movez = 0;
		}
	}
	if (MovecheckA)
	{
		count++;

		if (count <= 20)
		{
			movex = -SAI_MOVE*count;
			angle = SAI_ROT * count;
			movey = sin(D3DXToRadian(angle)) + movex + ADJUST;
			D3DXMatrixRotationZ(&g_mtxRotationSai, D3DXToRadian(angle));
		}
		else
		{
			count = 0;
			MovecheckA = false;
			x -= 1.0;
			angle = 0;
			movex = 0;
		}
	}
	if (MovecheckD)
	{
		count++;

		if (count <= 20)
		{
			movex = SAI_MOVE*count;
			angle = -SAI_ROT * count;
			movey = sin(D3DXToRadian(-angle)) - movex + ADJUST;
			D3DXMatrixRotationZ(&g_mtxRotationSai, D3DXToRadian(angle));
		}
		else
		{
			count = 0;
			MovecheckD = false;
			x += 1.0;
			angle = 0;
			movex = 0;
		}
	}
	
}

//=============================================================================
//	描画処理
//=============================================================================

void Cube_Draw(void)
{

	//デバイス
	LPDIRECT3DDEVICE9 g_pD3DDevice = mochi_GetDevice();

	g_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
	g_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);

	// ワールド座標変換行列
	D3DXMATRIX mtxWorld;		// 4*4行列　d3dx9.h必要
	
	
	// 平行
	D3DXMATRIX mtxTranslation;
	D3DXMATRIX mtxTranslation2;

	// 回転
	D3DXMATRIX mtxRotation;
	D3DXMATRIX mtxRotation2;
	/*
	D3DXMatrixRotationX(アドレス, アングル);   縦ロール
	D3DXMatrixRotationY(アドレス, アングル);   横ロール
	D3DXMatrixRotationZ(アドレス, アングル);   
	D3DXMatrixRotationYawPitchRoll(アドレス,y,x,z)
	D3DXMatrixRotationAxis(アドレス,軸ベクトルのアドレス,アングル);
	*/


	if ((MovecheckW)|| (MovecheckA) || (MovecheckS) || (MovecheckD))
	{
		D3DXMatrixTranslation(&mtxTranslation, x + movex, y + movey, z + movez);
		g_mtxWorldSai = g_mtxTotalRotation*g_mtxRotationSai*mtxTranslation;
		if (count >= 20)
		{
			g_mtxTotalRotation *= g_mtxRotationSai;
		}
	}
	
	D3DXMatrixTranslation(&mtxTranslation2, 0, 0.5,0);
	mtxWorld = mtxTranslation2*g_mtxTranslation;

	//	ワールド変換行列設定
	

	g_pD3DDevice->SetFVF(FVF_CUBE_VERTEX3D);		//	FVFをデバイスに設定
	g_pD3DDevice->SetTexture(0, Texture_GetTexture(0));
	
	/*g_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	g_pD3DDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(CubeVertex3D));
	g_pD3DDevice->SetIndices(g_pIndexBuffer);
	g_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);*/

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldSai);
	g_pD3DDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(CubeVertex3D));
	g_pD3DDevice->SetIndices(g_pIndexBuffer);
	g_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);

	/*g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 12, g_cube, sizeof(CubeVertex3D));


	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld[1]);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 12, g_cube, sizeof(CubeVertex3D));*/
	/*
	第1引数　どんな形か
	第2引数　プリミティブ数　三角形をいくつだすか
	第3引数  頂点データの先頭アドレス
	第4引数　頂点データ構造体の大きさ
	*/

	

}