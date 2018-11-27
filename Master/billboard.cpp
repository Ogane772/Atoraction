//=============================================================================
//	インクルードファイル
//=============================================================================

#include <d3dx9.h>
#include "mochi_d3d.h"
#include "camera.h"
#include "ten_texture.h"

//=============================================================================
//	定数定義
//=============================================================================



//=============================================================================
//	グローバル宣言
//=============================================================================

typedef struct
{
	D3DXVECTOR3 pos;	//	座標x,y,z
	D3DXVECTOR3 normal; //	法線ベクトル 座標の後 長さは1.0
	D3DCOLOR color;		//  色
	D3DXVECTOR2 uv;		//  テクスチャ

}BillBoardVertex3D;


#define FVF_CUBE_VERTEX3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)	//	構造体のすぐ下に書く

// 頂点バッファの確保
static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;

static BillBoardVertex3D g_bb[] = {
	{ D3DXVECTOR3(-0.5, 0.5,0.0),D3DXVECTOR3(0.0,0.0,0.0),D3DCOLOR(0xffff0000),D3DXVECTOR2(0.0,0.0) },
	{ D3DXVECTOR3(0.5, 0.5,0.),D3DXVECTOR3(0.0,0.0,0.0),D3DCOLOR(0xffff0000),D3DXVECTOR2(1.0,0.0) },
	{ D3DXVECTOR3(-0.5,-0.5,0.0),D3DXVECTOR3(0.0,0.0,0.0),D3DCOLOR(0xffff0000),D3DXVECTOR2(0.0,1.0) }, 
	{ D3DXVECTOR3(0.5,-0.5,0.0),D3DXVECTOR3(0.0,0.0,0.0),D3DCOLOR(0xffff0000),D3DXVECTOR2(1.0,1.0) },
};




void BillBoard_Initialize(void)
{
	LPDIRECT3DDEVICE9 pD3DDevice = mochi_GetDevice();
	pD3DDevice->CreateVertexBuffer(sizeof(BillBoardVertex3D) * 4, D3DUSAGE_WRITEONLY, FVF_CUBE_VERTEX3D, D3DPOOL_MANAGED, &g_pVertexBuffer, NULL);

	// 仮想アドレス　
	BillBoardVertex3D *pv;
	// 頂点バッファのロック
	g_pVertexBuffer->Lock(0, 0, (void**)&pv, 0);
	/*
	1 どこから
	2 0でいい
	3 仮想アドレスを入れる
	4 0でいい
	*/
	memcpy(pv, g_bb, sizeof(g_bb));
	g_pVertexBuffer->Unlock();


}

void BillBoard_Finalize(void)
{
	// 頂点バッファの解放
	if (g_pVertexBuffer != NULL)
	{
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}

}

void BillBoard_Updata(void)
{

}

void BillBoard_Draw(void)
{
	LPDIRECT3DDEVICE9 pD3DDevice = mochi_GetDevice();
	D3DXMATRIX mtxWorld;	//	ワールド変換用行列
	D3DXMatrixIdentity(&mtxWorld);

	D3DXMATRIX mtxInvV;	//	逆行列

	mtxInvV = Get_ViewMtx();
	mtxInvV._41 = 0.0f;
	mtxInvV._42 = 0.0f;
	mtxInvV._43 = 0.0f;

	D3DXMatrixInverse(&mtxInvV, NULL, &mtxInvV);

	mtxWorld = mtxInvV * mtxWorld;

	pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pD3DDevice->SetFVF(FVF_CUBE_VERTEX3D);		//	FVFをデバイスに設定
	pD3DDevice->SetTexture(0, Texture_GetTexture(2));
	pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	pD3DDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(BillBoardVertex3D));
	pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 4, g_bb, sizeof(BillBoardVertex3D));
}


void BillBoard_Draw(D3DXMATRIX mtx)
{
	LPDIRECT3DDEVICE9 pD3DDevice = mochi_GetDevice();
	D3DXMATRIX mtxWorld;	//	ワールド変換用行列
	D3DXMatrixIdentity(&mtxWorld);

	D3DXMATRIX mtxInvV;	//	逆行列

	mtxInvV = Get_ViewMtx();
	mtxInvV._41 = 0.0f;
	mtxInvV._42 = 0.0f;
	mtxInvV._43 = 0.0f;
	//D3DXMatrixInverse(&mtxInvV, NULL, &mtxInvV);	//	逆行列
	D3DXMatrixTranspose(&mtxInvV, &mtxInvV);		//	転置

	mtxWorld = mtx;
	mtxWorld = mtxInvV * mtxWorld;

	pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pD3DDevice->SetFVF(FVF_CUBE_VERTEX3D);		//	FVFをデバイスに設定
	pD3DDevice->SetTexture(0, Texture_GetTexture(2));
	pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	pD3DDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(BillBoardVertex3D));
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0,2);
}

void BillBoard_Draw(float x,float y,float z)
{
	LPDIRECT3DDEVICE9 pD3DDevice = mochi_GetDevice();

	D3DXMATRIX mtxWorld;	//	ワールド変換用行列
	D3DXMatrixIdentity(&mtxWorld);

	D3DXMATRIX mtxTranslation;
	D3DXMatrixTranslation(&mtxTranslation, x, y, z);

	D3DXMATRIX mtxInvV;	//	逆行列

	mtxInvV = Get_ViewMtx();
	mtxInvV._41 = 0.0f;
	mtxInvV._42 = 0.0f;
	mtxInvV._43 = 0.0f;
	//D3DXMatrixInverse(&mtxInvV, NULL, &mtxInvV);	//	逆行列
	D3DXMatrixTranspose(&mtxInvV, &mtxInvV);		//	転置

	mtxWorld = mtxTranslation;
	mtxWorld = mtxInvV * mtxWorld;


	pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);	//	αテスト有効
	pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0);	//	参照値設定
	pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER); // 比較演算式設定 D3DCMP_GRATER 大なり>
	

	pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pD3DDevice->SetFVF(FVF_CUBE_VERTEX3D);		//	FVFをデバイスに設定
	pD3DDevice->SetTexture(0, Texture_GetTexture(2));
	pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	pD3DDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(BillBoardVertex3D));
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}