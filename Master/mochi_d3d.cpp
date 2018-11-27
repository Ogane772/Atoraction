//=============================================================================
//	インクルードファイル
//=============================================================================

#include <windows.h>
#include <d3dx9.h>
#include "common.h"

//=============================================================================
//	グローバル変数宣言
//=============================================================================
static LPDIRECT3D9 g_pD3D = NULL;				//	
static LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;	//　デバイスのIDirect3Device9インターフェイス

// Direct3Dの初期化
bool mochi_Init(HWND hWnd)
{
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return false;
	}

	//　D3DPRESENT_PARAMETERS構造体の設定　P41-48
	D3DPRESENT_PARAMETERS d3dpp = {};
	d3dpp.BackBufferWidth = WINDOW_WIDTH;						//	バックバッファの幅
	d3dpp.BackBufferHeight = WINDOW_HIGHT;						//　バックバッファの高さ
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;					//	バックバッファのフォーマット
	d3dpp.BackBufferCount = 1;									//	バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					//	スワップエフェクト
	d3dpp.Windowed = TRUE;										//	画面モード	windowならTRUE　fullscreenならFALSE
	d3dpp.EnableAutoDepthStencil = TRUE;						//	ステンシルバッファの有無
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					//  メモリの型　ステンシルバッファ16bit		※D3DFMT_D24S8　覚えとく
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	//	リフレッシュレート　モニタ1秒間の書き換え数　指定可能(対応数以内)	フルスクリーンのみ　普通59-60Hz
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;  	//	垂直同期の設定　ONEの方がいいかも　IMMEDIATE重さ判定にオススメ
																/*
																画面更新
																左端から右端に到着	水平同期　して下へ
																更新終わり			垂直同期
																ティアリング　フレームのズレ	垂直同期前に更新
																*/

	HRESULT hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice);

	if (FAILED(hr))
	{
		MessageBox(NULL, "", "", MB_OK | MB_DEFBUTTON1);
	}

	//　サンプラー
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	// アルファブレンドを有効にする
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//　背景DESTのブレンド設定
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	// 今から描くポリゴンSRCのブレンド設定
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	return true;
}

// Direct3Dの修了処理
void mochi_end(void)
{
	

	// Direct3Dデバイスの開放
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	// Direct3Dインターフェースの開放
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

// Direct3Dデバイスポインタの取得
LPDIRECT3DDEVICE9 mochi_GetDevice(void)
{
	return g_pD3DDevice;
}