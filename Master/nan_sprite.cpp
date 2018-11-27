//=============================================================================
//	インクルードファイル
//=============================================================================

#include <d3dx9.h>
#include "ten_texture.h"
#include "mochi_d3d.h"
#include "common.h"

//=============================================================================
//	グローバル変数宣言
//=============================================================================

//2Dポリゴン頂点　構造体
typedef struct
{
	D3DXVECTOR4 pos;	//	flootにして4つ目1.0f(RHW)　座標変換済み頂点
	D3DCOLOR color;		//  色
	D3DXVECTOR2 texcoord;	//　テクスチャ
}Vertex2D;

#define FVF_VERTEX2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	//	構造体のすぐ下に書く



static D3DCOLOR g_Color = 0xffffffff;
// static D3DCOLOR g_Color = D3DCOLOR_RGBA(255,255,255,255)

static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;
// 頂点バッファの確保

//=============================================================================
//	初期化処理
//=============================================================================

void Sprite_Initialize(void)
{
	LPDIRECT3DDEVICE9 pDevice = mochi_GetDevice();
	// 頂点バッファの確保
	pDevice->CreateVertexBuffer(sizeof(Vertex2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX2D, D3DPOOL_MANAGED, &g_pVertexBuffer, NULL);
	/*
	1 頂点のサイズ
	2 用途
	3 FVF
	4 VRAM上のメモリの管理
	5 メモ帳の場所
	6 NULL(分かんないときはNULLを入れる)
	*/

	// インデックスバッファの確保
	pDevice->CreateIndexBuffer(sizeof(WORD) * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);
	/*
	1 インデックスのサイズ
	2 用途
	3 インデックスのフォーマット(16ビットか32ビット)
	4 VRAM上のメモリの管理
	5 メモ帳の場所
	6 NULL(分かんないときはNULLを入れる)
	*/
}


//=============================================================================
//	終了処理
//=============================================================================
void Sprite_Finalize(void)
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



// スプライトポリゴンの頂点カラー設定
void Sprite_SetColor(D3DCOLOR color)
{
	g_Color = color;
}

// アニメーション無し
void Sprite_Draw(int texture_index, float dx, float dy)
{
	float w = (float)Texture_GetWidth(texture_index);
	float h = (float)Texture_GetHeight(texture_index);

	Vertex2D v[] = {
		{ D3DXVECTOR4(dx	 - 0.5f,dy	   - 0.5f,1.0f,1.0f),g_Color,D3DXVECTOR2(0.0f, 0.0f) },	//	第4引数は絶対1.0ｆ
		{ D3DXVECTOR4(dx + w - 0.5f,dy	   - 0.5f,1.0f,1.0f),g_Color,D3DXVECTOR2(1.0f, 0.0f) },
		{ D3DXVECTOR4(dx	 - 0.5f,dy + h - 0.5f,1.0f,1.0f),g_Color,D3DXVECTOR2(0.0f, 1.0f) },
		{ D3DXVECTOR4(dx + w - 0.5f,dy + h - 0.5f,1.0f,1.0f),g_Color,D3DXVECTOR2(1.0f, 1.0f) },
	};

	// 頂点インデックス
	WORD index[] = { 0, 1, 2, 1, 3, 2 };
	// window.h　必用　unsigned short

	LPDIRECT3DDEVICE9 g_pD3DDevice = mochi_GetDevice();

	// 仮想アドレス　
	Vertex2D *pv;
	// 頂点バッファのロック
	g_pVertexBuffer->Lock(0, 0, (void**)&pv, 0);
	/*
	1 どこから
	2 0でいい
	3 仮想アドレスを入れる
	4 0でいい
	*/
	memcpy(pv, v, sizeof(v));
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
	Ipv[0] = 0;
	Ipv[1] = 1;
	Ipv[2] = 2;
	Ipv[3] = 1;
	Ipv[4] = 3;
	Ipv[5] = 2;
	g_pIndexBuffer->Unlock();

	g_pD3DDevice->SetFVF(FVF_VERTEX2D);		//	FVFをデバイスに設定

	g_pD3DDevice->SetTexture(0, Texture_GetTexture(texture_index));

	g_pD3DDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(Vertex2D));
	g_pD3DDevice->SetIndices(g_pIndexBuffer);

	// g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, v, sizeof(Vertex2D));		
	/*
	第1引数　どんな形か
	第2引数　プリミティブ数　三角形をいくつだすか
	第3引数  頂点データの先頭アドレス
	第4引数　頂点データ構造体の大きさ
	*/
	//g_pD3DDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 4, 2, index, D3DFMT_INDEX16, v, sizeof(Vertex2D));
	/*
	第1引数　どんな形か
	第2引数　index の一番小さい数
	第3引数　頂点の数
	第4引数　プリミティブ数
	第5引数　indexの先頭アドレス
	第6引数　ビット数(16or32)
	第7引数　頂点データの先頭アドレス
	第8引数　頂点データ構造体の大きさ
	*/
	//g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	g_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}

//　アニメーション有り
void Sprite_Draw(int texture_index, float dx, float dy, int tx, int ty, int tw, int th)
{
	float w = (float)Texture_GetWidth(texture_index);
	float h = (float)Texture_GetHeight(texture_index);

	float u0 = (float)tx / w;
	float v0 = (float)ty / h;
	float u1 = (float)tw / w;
	float v1 = (float)th / h;


	Vertex2D v[] = {
		{ D3DXVECTOR4(dx	  - 0.5f,dy		 - 0.5f,1.0f,1.0f),g_Color,D3DXVECTOR2(u0	  ,v0) },	//	第4引数は絶対1.0ｆ
		{ D3DXVECTOR4(dx + tw - 0.5f,dy		 - 0.5f,1.0f,1.0f),g_Color,D3DXVECTOR2(u0 + u1,v0) },
		{ D3DXVECTOR4(dx	  - 0.5f,dy + th - 0.5f,1.0f,1.0f),g_Color,D3DXVECTOR2(u0	  ,v0 + v1) },
		{ D3DXVECTOR4(dx + tw - 0.5f,dy + th - 0.5f,1.0f,1.0f),g_Color,D3DXVECTOR2(u0 + u1,v0 + v1) },

	};

	// 頂点インデックス
	WORD index[] = { 0, 1, 2, 1, 3, 2 };
	// window.h　必用　unsigned short

	LPDIRECT3DDEVICE9 g_pD3DDevice = mochi_GetDevice();

	// 仮想アドレス　
	Vertex2D *pv;
	// 頂点バッファのロック
	g_pVertexBuffer->Lock(0, 0, (void**)&pv, 0);
	/*
	1 どこから
	2 0でいい
	3 仮想アドレスを入れる
	4 0でいい
	*/
	memcpy(pv, v, sizeof(v));
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
	Ipv[0] = 0;
	Ipv[1] = 1;
	Ipv[2] = 2;
	Ipv[3] = 1;
	Ipv[4] = 3;
	Ipv[5] = 2;
	g_pIndexBuffer->Unlock();

	g_pD3DDevice->SetFVF(FVF_VERTEX2D);		//	FVFをデバイスに設定

	g_pD3DDevice->SetTexture(0, Texture_GetTexture(texture_index));

	g_pD3DDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(Vertex2D));
	g_pD3DDevice->SetIndices(g_pIndexBuffer);

	// g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, v, sizeof(Vertex2D));		
	/*
	第1引数　どんな形か
	第2引数　プリミティブ数　三角形をいくつだすか
	第3引数  頂点データの先頭アドレス
	第4引数　頂点データ構造体の大きさ
	*/
	//g_pD3DDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 4, 2, index, D3DFMT_INDEX16, v, sizeof(Vertex2D));
	/*
	第1引数　どんな形か
	第2引数　index の一番小さい数
	第3引数　頂点の数
	第4引数　プリミティブ数
	第5引数　indexの先頭アドレス
	第6引数　ビット数(16or32)
	第7引数　頂点データの先頭アドレス
	第8引数　頂点データ構造体の大きさ
	*/
	//g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	g_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}

//　アニメーション有り　反転
void Sprite_ReturnDraw(int texture_index, float dx, float dy, int tx, int ty, int tw, int th, float movex, float movey)
{
	float w = (float)Texture_GetWidth(texture_index);
	float h = (float)Texture_GetHeight(texture_index);

	float u0 = (float)tx / w;
	float v0 = (float)ty / h;
	float u1 = (float)tw / w;
	float v1 = (float)th / h;


	Vertex2D v[] = {
		{ D3DXVECTOR4(dx - 0.5f + movex,dy - 0.5f + movey,1.0f,1.0f),g_Color,D3DXVECTOR2(u0 + u1,v0) },	//	第4引数は絶対1.0ｆ
		{ D3DXVECTOR4(dx + tw - 0.5f + movex,dy - 0.5f + movey,1.0f,1.0f),g_Color,D3DXVECTOR2(u0	  ,v0) },
		{ D3DXVECTOR4(dx - 0.5f + movex,dy + th - 0.5f + movey,1.0f,1.0f),g_Color,D3DXVECTOR2(u0 + u1,v0 + v1) },
		{ D3DXVECTOR4(dx + tw - 0.5f + movex,dy + th - 0.5f + movey,1.0f,1.0f),g_Color,D3DXVECTOR2(u0	  ,v0 + v1) },

	};

	// 頂点インデックス
	WORD index[] = { 0, 1, 2, 1, 3, 2 };
	// window.h　必用　unsigned short

	LPDIRECT3DDEVICE9 g_pD3DDevice = mochi_GetDevice();

	// 仮想アドレス　
	Vertex2D *pv;
	// 頂点バッファのロック
	g_pVertexBuffer->Lock(0, 0, (void**)&pv, 0);
	/*
	1 どこから
	2 0でいい
	3 仮想アドレスを入れる
	4 0でいい
	*/
	memcpy(pv, v, sizeof(v));
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
	Ipv[0] = 0;
	Ipv[1] = 1;
	Ipv[2] = 2;
	Ipv[3] = 1;
	Ipv[4] = 3;
	Ipv[5] = 2;
	g_pIndexBuffer->Unlock();

	g_pD3DDevice->SetFVF(FVF_VERTEX2D);		//	FVFをデバイスに設定

	g_pD3DDevice->SetTexture(0, Texture_GetTexture(texture_index));

	g_pD3DDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(Vertex2D));
	g_pD3DDevice->SetIndices(g_pIndexBuffer);

	// g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, v, sizeof(Vertex2D));		
	/*
	第1引数　どんな形か
	第2引数　プリミティブ数　三角形をいくつだすか
	第3引数  頂点データの先頭アドレス
	第4引数　頂点データ構造体の大きさ
	*/
	//g_pD3DDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 4, 2, index, D3DFMT_INDEX16, v, sizeof(Vertex2D));
	/*
	第1引数　どんな形か
	第2引数　index の一番小さい数
	第3引数　頂点の数
	第4引数　プリミティブ数
	第5引数　indexの先頭アドレス
	第6引数　ビット数(16or32)
	第7引数　頂点データの先頭アドレス
	第8引数　頂点データ構造体の大きさ
	*/
	//g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	g_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}

// 背景
void Sprite_Draw(int texture_index)
{
	Vertex2D v[] = {
		{ D3DXVECTOR4(0.0f - 0.5f, 0.0f - 0.5f,1.0f,1.0f),g_Color,D3DXVECTOR2(0.0f, 0.0f) },	//	第4引数は絶対1.0ｆ
		{ D3DXVECTOR4(WINDOW_WIDTH - 0.5f, 0.0f - 0.5f,1.0f,1.0f),g_Color,D3DXVECTOR2(1.0f, 0.0f) },
		{ D3DXVECTOR4(0.0f - 0.5f, WINDOW_HIGHT - 0.5f,1.0f,1.0f),g_Color,D3DXVECTOR2(0.0f, 1.0f) },
		{ D3DXVECTOR4(WINDOW_WIDTH - 0.5f, WINDOW_HIGHT - 0.5f,1.0f,1.0f),g_Color,D3DXVECTOR2(1.0f, 1.0f) },
	};

	// 頂点インデックス
	WORD index[] = { 0, 1, 2, 1, 3, 2 };
	// window.h　必用　unsigned short

	LPDIRECT3DDEVICE9 g_pD3DDevice = mochi_GetDevice();

	// 仮想アドレス　
	Vertex2D *pv;
	// 頂点バッファのロック
	g_pVertexBuffer->Lock(0, 0, (void**)&pv, 0);
	/*
	1 どこから
	2 0でいい
	3 仮想アドレスを入れる
	4 0でいい
	*/
	memcpy(pv, v, sizeof(v));
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
	Ipv[0] = 0;
	Ipv[1] = 1;
	Ipv[2] = 2;
	Ipv[3] = 1;
	Ipv[4] = 3;
	Ipv[5] = 2;
	g_pIndexBuffer->Unlock();

	g_pD3DDevice->SetFVF(FVF_VERTEX2D);		//	FVFをデバイスに設定

	g_pD3DDevice->SetTexture(0, Texture_GetTexture(texture_index));

	g_pD3DDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(Vertex2D));
	g_pD3DDevice->SetIndices(g_pIndexBuffer);

	// g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, v, sizeof(Vertex2D));		
	/*
	第1引数　どんな形か
	第2引数　プリミティブ数　三角形をいくつだすか
	第3引数  頂点データの先頭アドレス
	第4引数　頂点データ構造体の大きさ
	*/
	//g_pD3DDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 4, 2, index, D3DFMT_INDEX16, v, sizeof(Vertex2D));
	/*
	第1引数　どんな形か
	第2引数　index の一番小さい数
	第3引数　頂点の数
	第4引数　プリミティブ数
	第5引数　indexの先頭アドレス
	第6引数　ビット数(16or32)
	第7引数　頂点データの先頭アドレス
	第8引数　頂点データ構造体の大きさ
	*/
	//g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	g_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}

//　アニメーション有り　回転
void Sprite_Draw(int texture_index, float dx, float dy, int tx, int ty, int tw, int th, float movex, float movey, float rotation)
{
	float w = (float)Texture_GetWidth(texture_index);
	float h = (float)Texture_GetHeight(texture_index);

	float u0 = (float)tx / w;
	float v0 = (float)ty / h;
	float u1 = (float)tw / w;
	float v1 = (float)th / h;

	float px[4], py[4];
	px[0] = dx		  * cos(rotation) - dy * sin(rotation);
	py[0] = dx		  * sin(rotation) + dy * cos(rotation);
	px[1] = (dx + tw) * cos(rotation) - dy * sin(rotation);
	py[1] = (dx + tw) * sin(rotation) + dy * cos(rotation);
	px[2] = dx		  * cos(rotation) - (dy + th) * sin(rotation);
	py[2] = dx		  * sin(rotation) + (dy + th) * cos(rotation);
	px[3] = (dx + tw) * cos(rotation) - (dy + th) * sin(rotation);
	py[3] = (dx + tw) * sin(rotation) + (dy + th) * cos(rotation);


	Vertex2D v[] = {
		{ D3DXVECTOR4(px[0] - 0.5f + movex,py[0] - 0.5f + movey,1.0f,1.0f),g_Color,D3DXVECTOR2(u0	  ,v0) },	//	第4引数は絶対1.0ｆ
		{ D3DXVECTOR4(px[1] - 0.5f + movex,py[1] - 0.5f + movey,1.0f,1.0f),g_Color,D3DXVECTOR2(u0 + u1,v0) },
		{ D3DXVECTOR4(px[2] - 0.5f + movex,py[2] - 0.5f + movey,1.0f,1.0f),g_Color,D3DXVECTOR2(u0	  ,v0 + v1) },
		{ D3DXVECTOR4(px[3] - 0.5f + movex,py[3] - 0.5f + movey,1.0f,1.0f),g_Color,D3DXVECTOR2(u0 + u1,v0 + v1) },

	};

	// 頂点インデックス
	WORD index[] = { 0, 1, 2, 1, 3, 2 };
	// window.h　必用　unsigned short

	LPDIRECT3DDEVICE9 g_pD3DDevice = mochi_GetDevice();

	// 仮想アドレス　
	Vertex2D *pv;
	// 頂点バッファのロック
	g_pVertexBuffer->Lock(0, 0, (void**)&pv, 0);
	/*
	1 どこから
	2 0でいい
	3 仮想アドレスを入れる
	4 0でいい
	*/
	memcpy(pv, v, sizeof(v));
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
	Ipv[0] = 0;
	Ipv[1] = 1;
	Ipv[2] = 2;
	Ipv[3] = 1;
	Ipv[4] = 3;
	Ipv[5] = 2;
	g_pIndexBuffer->Unlock();

	g_pD3DDevice->SetFVF(FVF_VERTEX2D);		//	FVFをデバイスに設定

	g_pD3DDevice->SetTexture(0, Texture_GetTexture(texture_index));

	g_pD3DDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(Vertex2D));
	g_pD3DDevice->SetIndices(g_pIndexBuffer);

	// g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, v, sizeof(Vertex2D));		
	/*
	第1引数　どんな形か
	第2引数　プリミティブ数　三角形をいくつだすか
	第3引数  頂点データの先頭アドレス
	第4引数　頂点データ構造体の大きさ
	*/
	//g_pD3DDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 4, 2, index, D3DFMT_INDEX16, v, sizeof(Vertex2D));
	/*
	第1引数　どんな形か
	第2引数　index の一番小さい数
	第3引数　頂点の数
	第4引数　プリミティブ数
	第5引数　indexの先頭アドレス
	第6引数　ビット数(16or32)
	第7引数　頂点データの先頭アドレス
	第8引数　頂点データ構造体の大きさ
	*/
	//g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	g_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}

//　アニメーション有り　その場で回転
void Sprite_Draw(int texture_index, float dx, float dy, int tx, int ty, int tw, int th, float movex, float movey, float rotation, float cx, float cy)
{
	float w = (float)Texture_GetWidth(texture_index);
	float h = (float)Texture_GetHeight(texture_index);

	float u0 = (float)tx / w;
	float v0 = (float)ty / h;
	float u1 = (float)tw / w;
	float v1 = (float)th / h;

	float px[4], py[4];
	px[0] = -cx		   * cos(rotation) - (-cy 		 * sin(rotation));
	py[0] = -cx		   * sin(rotation) + (-cy 		 * cos(rotation));
	px[1] = (-cx + tw) * cos(rotation) - (-cy 		 * sin(rotation));
	py[1] = (-cx + tw) * sin(rotation) + (-cy 	 	 * cos(rotation));
	px[2] = -cx		   * cos(rotation) - (-cy + th) * sin(rotation);
	py[2] = -cx		   * sin(rotation) + (-cy + th) * cos(rotation);
	px[3] = (-cx + tw) * cos(rotation) - (-cy + th) * sin(rotation);
	py[3] = (-cx + tw) * sin(rotation) + (-cy + th) * cos(rotation);


	Vertex2D v[] = {
		{ D3DXVECTOR4(px[0] + dx + cx - 0.5f + movex,py[0] + dy + cy - 0.5f + movey,1.0f,1.0f),g_Color,D3DXVECTOR2(u0	  ,v0) },	//	第4引数は絶対1.0ｆ
		{ D3DXVECTOR4(px[1] + dx + cx - 0.5f + movex,py[1] + dy + cy - 0.5f + movey,1.0f,1.0f),g_Color,D3DXVECTOR2(u0 + u1,v0) },
		{ D3DXVECTOR4(px[2] + dx + cx - 0.5f + movex,py[2] + dy + cy - 0.5f + movey,1.0f,1.0f),g_Color,D3DXVECTOR2(u0	  ,v0 + v1) },
		{ D3DXVECTOR4(px[3] + dx + cx - 0.5f + movex,py[3] + dy + cy - 0.5f + movey,1.0f,1.0f),g_Color,D3DXVECTOR2(u0 + u1,v0 + v1) },

	};

	// 頂点インデックス
	WORD index[] = { 0, 1, 2, 1, 3, 2 };
	// window.h　必用　unsigned short

	LPDIRECT3DDEVICE9 g_pD3DDevice = mochi_GetDevice();

	// 仮想アドレス　
	Vertex2D *pv;
	// 頂点バッファのロック
	g_pVertexBuffer->Lock(0, 0, (void**)&pv, 0);
	/*
	1 どこから
	2 0でいい
	3 仮想アドレスを入れる
	4 0でいい
	*/
	memcpy(pv, v, sizeof(v));
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
	Ipv[0] = 0;
	Ipv[1] = 1;
	Ipv[2] = 2;
	Ipv[3] = 1;
	Ipv[4] = 3;
	Ipv[5] = 2;
	g_pIndexBuffer->Unlock();

	g_pD3DDevice->SetFVF(FVF_VERTEX2D);		//	FVFをデバイスに設定

	g_pD3DDevice->SetTexture(0, Texture_GetTexture(texture_index));

	g_pD3DDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(Vertex2D));
	g_pD3DDevice->SetIndices(g_pIndexBuffer);

	// g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, v, sizeof(Vertex2D));		
	/*
	第1引数　どんな形か
	第2引数　プリミティブ数　三角形をいくつだすか
	第3引数  頂点データの先頭アドレス
	第4引数　頂点データ構造体の大きさ
	*/
	//g_pD3DDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 4, 2, index, D3DFMT_INDEX16, v, sizeof(Vertex2D));
	/*
	第1引数　どんな形か
	第2引数　index の一番小さい数
	第3引数　頂点の数
	第4引数　プリミティブ数
	第5引数　indexの先頭アドレス
	第6引数　ビット数(16or32)
	第7引数　頂点データの先頭アドレス
	第8引数　頂点データ構造体の大きさ
	*/
	//g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	g_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}

//　アニメーション有り　その場で回転　拡大縮小
void Sprite_Draw(int texture_index, float dx, float dy, int tx, int ty, int tw, int th, float movex, float movey, float rotation, float cx, float cy, float sx, float sy)
{
	float w = (float)Texture_GetWidth(texture_index);
	float h = (float)Texture_GetHeight(texture_index);

	float u0 = (float)tx / w;
	float v0 = (float)ty / h;
	float u1 = (float)tw / w;
	float v1 = (float)th / h;

	float px[4], py[4];

	px[0] = -cx		   *sx * cos(rotation) + cy *sy * sin(rotation);
	py[0] = -cx		   *sx * sin(rotation) - cy *sy * cos(rotation);
	px[1] = (-cx + tw) *sx * cos(rotation) + cy *sy * sin(rotation);
	py[1] = (-cx + tw) *sx * sin(rotation) - cy *sy * cos(rotation);
	px[2] = -cx		   *sx * cos(rotation) - (-cy + th) *sy * sin(rotation);
	py[2] = -cx		   *sx * sin(rotation) + (-cy + th) *sy * cos(rotation);
	px[3] = (-cx + tw) *sx * cos(rotation) - (-cy + th) *sy * sin(rotation);
	py[3] = (-cx + tw) *sx * sin(rotation) + (-cy + th) *sy * cos(rotation);


	Vertex2D v[] = {
		{ D3DXVECTOR4(px[0] + dx + cx - 0.5f + movex,py[0] + dy + cy - 0.5f + movey,1.0f,1.0f),g_Color,D3DXVECTOR2(u0	  ,v0) },	//	第4引数は絶対1.0ｆ
		{ D3DXVECTOR4(px[1] + dx + cx - 0.5f + movex,py[1] + dy + cy - 0.5f + movey,1.0f,1.0f),g_Color,D3DXVECTOR2(u0 + u1,v0) },
		{ D3DXVECTOR4(px[2] + dx + cx - 0.5f + movex,py[2] + dy + cy - 0.5f + movey,1.0f,1.0f),g_Color,D3DXVECTOR2(u0	  ,v0 + v1) },
		{ D3DXVECTOR4(px[3] + dx + cx - 0.5f + movex,py[3] + dy + cy - 0.5f + movey,1.0f,1.0f),g_Color,D3DXVECTOR2(u0 + u1,v0 + v1) },

	};

	// 頂点インデックス
	WORD index[] = { 0, 1, 2, 1, 3, 2 };
	// window.h　必用　unsigned short

	LPDIRECT3DDEVICE9 g_pD3DDevice = mochi_GetDevice();

	// 仮想アドレス　
	Vertex2D *pv;
	// 頂点バッファのロック
	g_pVertexBuffer->Lock(0, 0, (void**)&pv, 0);
	/*
	1 どこから
	2 0でいい
	3 仮想アドレスを入れる
	4 0でいい
	*/
	memcpy(pv, v, sizeof(v));
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
	Ipv[0] = 0;
	Ipv[1] = 1;
	Ipv[2] = 2;
	Ipv[3] = 1;
	Ipv[4] = 3;
	Ipv[5] = 2;
	g_pIndexBuffer->Unlock();

	g_pD3DDevice->SetFVF(FVF_VERTEX2D);		//	FVFをデバイスに設定

	g_pD3DDevice->SetTexture(0, Texture_GetTexture(texture_index));

	g_pD3DDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(Vertex2D));
	g_pD3DDevice->SetIndices(g_pIndexBuffer);

	// g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, v, sizeof(Vertex2D));		
	/*
	第1引数　どんな形か
	第2引数　プリミティブ数　三角形をいくつだすか
	第3引数  頂点データの先頭アドレス
	第4引数　頂点データ構造体の大きさ
	*/
	//g_pD3DDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 4, 2, index, D3DFMT_INDEX16, v, sizeof(Vertex2D));
	/*
	第1引数　どんな形か
	第2引数　index の一番小さい数
	第3引数　頂点の数
	第4引数　プリミティブ数
	第5引数　indexの先頭アドレス
	第6引数　ビット数(16or32)
	第7引数　頂点データの先頭アドレス
	第8引数　頂点データ構造体の大きさ
	*/
	//g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	g_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}



//　アニメーション有り　拡大縮小
void Sprite_BIGDraw(int texture_index, float dx, float dy, int tx, int ty, int tw, int th, float cx, float cy, float sx, float sy)
{
	float w = (float)Texture_GetWidth(texture_index);
	float h = (float)Texture_GetHeight(texture_index);

	float u0 = (float)tx / w;
	float v0 = (float)ty / h;
	float u1 = (float)tw / w;
	float v1 = (float)th / h;

	float px[4], py[4];

	px[0] = -cx * sx;
	py[0] = -cy * sy;

	px[1] = (-cx + tw) * sx;
	py[1] = - cy * sy;

	px[2] = - cx * sx;
	py[2] = (-cy + th) * sy;

	px[3] = (-cx + tw) * sx;
	py[3] = (-cy + th) * sy;


	Vertex2D v[] = {
		{ D3DXVECTOR4(px[0] + dx + cx - 0.5f ,py[0] + dy + cy - 0.5f ,1.0f,1.0f),g_Color,D3DXVECTOR2(u0	  ,v0) },	//	第4引数は絶対1.0ｆ
		{ D3DXVECTOR4(px[1] + dx + cx - 0.5f ,py[1] + dy + cy - 0.5f ,1.0f,1.0f),g_Color,D3DXVECTOR2(u0 + u1,v0) },
		{ D3DXVECTOR4(px[2] + dx + cx - 0.5f ,py[2] + dy + cy - 0.5f ,1.0f,1.0f),g_Color,D3DXVECTOR2(u0	  ,v0 + v1) },
		{ D3DXVECTOR4(px[3] + dx + cx - 0.5f ,py[3] + dy + cy - 0.5f ,1.0f,1.0f),g_Color,D3DXVECTOR2(u0 + u1,v0 + v1) },

	};

	// 頂点インデックス
	WORD index[] = { 0, 1, 2, 1, 3, 2 };
	// window.h　必用　unsigned short

	LPDIRECT3DDEVICE9 g_pD3DDevice = mochi_GetDevice();

	// 仮想アドレス　
	Vertex2D *pv;
	// 頂点バッファのロック
	g_pVertexBuffer->Lock(0, 0, (void**)&pv, 0);
	/*
	1 どこから
	2 0でいい
	3 仮想アドレスを入れる
	4 0でいい
	*/
	memcpy(pv, v, sizeof(v));
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
	Ipv[0] = 0;
	Ipv[1] = 1;
	Ipv[2] = 2;
	Ipv[3] = 1;
	Ipv[4] = 3;
	Ipv[5] = 2;
	g_pIndexBuffer->Unlock();

	g_pD3DDevice->SetFVF(FVF_VERTEX2D);		//	FVFをデバイスに設定

	g_pD3DDevice->SetTexture(0, Texture_GetTexture(texture_index));

	g_pD3DDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(Vertex2D));
	g_pD3DDevice->SetIndices(g_pIndexBuffer);

	// g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, v, sizeof(Vertex2D));		
	/*
	第1引数　どんな形か
	第2引数　プリミティブ数　三角形をいくつだすか
	第3引数  頂点データの先頭アドレス
	第4引数　頂点データ構造体の大きさ
	*/
	//g_pD3DDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 4, 2, index, D3DFMT_INDEX16, v, sizeof(Vertex2D));
	/*
	第1引数　どんな形か
	第2引数　index の一番小さい数
	第3引数　頂点の数
	第4引数　プリミティブ数
	第5引数　indexの先頭アドレス
	第6引数　ビット数(16or32)
	第7引数　頂点データの先頭アドレス
	第8引数　頂点データ構造体の大きさ
	*/
	//g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	g_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}

