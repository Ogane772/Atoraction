//////////////////////////////////////////////////
////
////	2Dオブジェクトクラス
////
//////////////////////////////////////////////////

//=============================================================================
//	インクルードファイル
//=============================================================================

#include "C2DObj.h"
#include "ten_texture.h"
#include "CCamera.h"
#include "common.h"
//=============================================================================
//	定数定義
//=============================================================================


//=============================================================================
//	静的変数
//=============================================================================

LPDIRECT3DVERTEXBUFFER9 C2DObj::m_p2DVertexBuffer = NULL;
LPDIRECT3DINDEXBUFFER9 C2DObj::m_p2DIndexBuffer = NULL;

//=============================================================================
//	生成
//=============================================================================

C2DObj::C2DObj()
{
	//m_GameObjNum--;
}

//=============================================================================
//	破棄
//=============================================================================

C2DObj::~C2DObj()
{
	
}

//=============================================================================
//	スプライト初期化
//=============================================================================

void C2DObj::Sprite_Initialize(void)
{
	C2DObj::m_pD3DDevice->CreateVertexBuffer(sizeof(Vertex2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX2D, D3DPOOL_MANAGED, &m_p2DVertexBuffer, NULL);
	/*
	1 頂点のサイズ
	2 用途
	3 FVF
	4 VRAM上のメモリの管理
	5 メモ帳の場所
	6 NULL(分かんないときはNULLを入れる)
	*/

	// インデックスバッファの確保
	C2DObj::m_pD3DDevice->CreateIndexBuffer(sizeof(WORD) * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_p2DIndexBuffer, NULL);
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
//	スプライト描画
//=============================================================================

void C2DObj::Sprite_Draw(int texture_index, float dx, float dy, int tx, int ty, int tw, int th)
{
	float w = (float)Texture_GetWidth(texture_index,1);
	float h = (float)Texture_GetHeight(texture_index,1);

	float u0 = (float)tx / w;
	float v0 = (float)ty / h;
	float u1 = (float)tw / w;
	float v1 = (float)th / h;


	Vertex2D v[] = {
		{ D3DXVECTOR4(dx - 0.5f,dy - 0.5f,0.0f,1.0f),D3DCOLOR(0xffffffff),D3DXVECTOR2(u0	  ,v0) },	//	第4引数は絶対1.0ｆ
		{ D3DXVECTOR4(dx + tw - 0.5f,dy - 0.5f,0.0f,1.0f),D3DCOLOR(0xffffffff),D3DXVECTOR2(u0 + u1,v0) },
		{ D3DXVECTOR4(dx - 0.5f,dy + th - 0.5f,0.0f,1.0f),D3DCOLOR(0xffffffff),D3DXVECTOR2(u0	  ,v0 + v1) },
		{ D3DXVECTOR4(dx + tw - 0.5f,dy + th - 0.5f,0.0f,1.0f),D3DCOLOR(0xffffffff),D3DXVECTOR2(u0 + u1,v0 + v1) },

	};

	// 頂点インデックス
	WORD index[] = { 0, 1, 2, 1, 3, 2 };
	// window.h　必用　unsigned short

	// 仮想アドレス　
	Vertex2D *pv;
	// 頂点バッファのロック
	m_p2DVertexBuffer->Lock(0, 0, (void**)&pv, 0);
	/*
	1 どこから
	2 0でいい
	3 仮想アドレスを入れる
	4 0でいい
	*/
	memcpy(pv, v, sizeof(v));
	m_p2DVertexBuffer->Unlock();

	// 仮想アドレス　
	WORD *Ipv;
	// インデックスバッファのロック
	m_p2DIndexBuffer->Lock(0, 0, (void**)&Ipv, 0);
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
	m_p2DIndexBuffer->Unlock();

	/*D3DXMATRIX mtxWorld;		// 4*4行列　d3dx9.h必要
	D3DXMatrixIdentity(&mtxWorld);	// アドレス送ると単位行列を作ってくれる
	C2DObj::m_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	D3DXMATRIX mtxv = CCamera::Get_ViewMtx();
	C2DObj::m_pD3DDevice->SetTransform(D3DTS_VIEW, &mtxv);

	// プロジェクション座標変換行列
	D3DXMATRIX mtxProjection;
	// プロジェクション座標変換
	D3DXMatrixOrthoLH(&mtxProjection, WINDOW_WIDTH, WINDOW_HIGHT, NYAA, FUAA);
	CGameObj::m_pD3DDevice->SetTransform(D3DTS_TEXTURE0, &mtxProjection);
	*/
	m_pD3DDevice->SetFVF(FVF_VERTEX2D);		//	FVFをデバイスに設定

	m_pD3DDevice->SetTexture(0, Texture_GetTexture(texture_index));

	m_pD3DDevice->SetStreamSource(0, m_p2DVertexBuffer, 0, sizeof(Vertex2D));
	m_pD3DDevice->SetIndices(m_p2DIndexBuffer);



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
	m_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}


void C2DObj::m_Sprite_Draw(int texture_index, float dx, float dy, int tx, int ty, int tw, int th)
{
	float w = (float)Texture_GetWidth(texture_index, 1);
	float h = (float)Texture_GetHeight(texture_index, 1);

	float u0 = (float)tx / w;
	float v0 = (float)ty / h;
	float u1 = (float)tw / w;
	float v1 = (float)th / h;


	Vertex2D v[] = {
		{ D3DXVECTOR4(dx - 0.5f,dy - 0.5f,1.0f,1.0f),D3DCOLOR(0xffffffff),D3DXVECTOR2(u0	  ,v0) },	//	第4引数は絶対1.0ｆ
		{ D3DXVECTOR4(dx + tw - 0.5f,dy - 0.5f,1.0f,1.0f),D3DCOLOR(0xffffffff),D3DXVECTOR2(u0 + u1,v0) },
		{ D3DXVECTOR4(dx - 0.5f,dy + th - 0.5f,1.0f,1.0f),D3DCOLOR(0xffffffff),D3DXVECTOR2(u0	  ,v0 + v1) },
		{ D3DXVECTOR4(dx + tw - 0.5f,dy + th - 0.5f,1.0f,1.0f),D3DCOLOR(0xffffffff),D3DXVECTOR2(u0 + u1,v0 + v1) },

	};

	// 頂点インデックス
	WORD index[] = { 0, 1, 2, 1, 3, 2 };
	// window.h　必用　unsigned short

	// 仮想アドレス　
	Vertex2D *pv;
	// 頂点バッファのロック
	m_p2DVertexBuffer->Lock(0, 0, (void**)&pv, 0);
	/*
	1 どこから
	2 0でいい
	3 仮想アドレスを入れる
	4 0でいい
	*/
	memcpy(pv, v, sizeof(v));
	m_p2DVertexBuffer->Unlock();

	// 仮想アドレス　
	WORD *Ipv;
	// インデックスバッファのロック
	m_p2DIndexBuffer->Lock(0, 0, (void**)&Ipv, 0);
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
	m_p2DIndexBuffer->Unlock();

	m_pD3DDevice->SetFVF(FVF_VERTEX2D);		//	FVFをデバイスに設定

	m_pD3DDevice->SetTexture(0, Texture_GetTexture(texture_index));

	m_pD3DDevice->SetStreamSource(0, m_p2DVertexBuffer, 0, sizeof(Vertex2D));
	m_pD3DDevice->SetIndices(m_p2DIndexBuffer);

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
	m_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}
//=============================================================================
//	スプライト破棄
//=============================================================================

void C2DObj::Sprite_Finalize(void)
{
	// インデックスバッファの解放
	if (m_p2DIndexBuffer != NULL)
	{
		m_p2DIndexBuffer->Release();
		m_p2DIndexBuffer = NULL;
	}

	// 頂点バッファの解放
	if (m_p2DVertexBuffer != NULL)
	{
		m_p2DVertexBuffer->Release();
		m_p2DVertexBuffer = NULL;
	}
}




void C2DObj::Update(void)
{

}
void C2DObj::Draw(void)
{

}
void C2DObj::Finalize(void)
{

}