#ifndef _MOCHI_D3D_H_
#define _MOCHI_D3D_H_





// Direct3Dの初期化
// 戻り値：初期化に失敗したらfalse
// 引数：hWnd...ウィンドウハンドル

bool mochi_Init(HWND hWnd);

// Direct3Dの修了処理
void mochi_end(void);

// Direct3Dデバイスポインタの取得
LPDIRECT3DDEVICE9 mochi_GetDevice(void);

#endif //_MOCHI_H_
