//////////////////////////////////////////////////
////
////	ゲームオブジェクトクラス
////
//////////////////////////////////////////////////

#ifndef _GAMEOBJ_H_
#define _GAMEOBJ_H_

#include <d3dx9.h>

#define TEXTURE_FILENAME_MAX (64)

class CGameObj
{
public:
	CGameObj();
	virtual ~CGameObj();

	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual void Finalize(void) = 0;
	bool Get_Enable(void) { return m_Enable; }

	static void Initialize(void);
	static int Get_FraemCount(void) { return m_FrameCount; }	//	フレームカウント取得
	static int Get_GameObjNum(void) { return m_GameObjNum; }	//	総ゲームオブジェクト取得
	static int Get_GameObjIndex(void) { return m_GameObjNum - 1; }	//	ゲームオブジェクトインデックス

	static void FrameCountUp(void) { m_FrameCount++; }	//  フレームカウントアップ
	static bool Device_Initialize(HWND hWnd);	//	デバイス初期化
	static void Device_Finalize(void);	//	デバイス破棄
	static LPDIRECT3DDEVICE9 m_pD3DDevice;	//	デバイス

	static void DebugDraw(void);
protected:		

	static int m_FrameCount;	//	フレームカウント　
	static int m_GameObjNum;	//	ゲームオブジェクト総数
	int m_TimeKeep = 0;
	bool m_Enable;

private:

	

	static LPDIRECT3D9 m_pD3D;
	
};

#endif // !1


