//////////////////////////////////////////////////
////
////	カメラクラス
////
//////////////////////////////////////////////////

#ifndef _CCAMERA_H_
#define _CCAMERA_H_

#include "CGameObj.h"
#define NYAA (0.1f)
#define FUAA (150.0f)

class CCamera :public CGameObj
{
public:
	CCamera();
	~CCamera();


	void Update(void);
	void Draw(void);
	void Finalize(void);		//	終了処理
	static D3DXVECTOR3 Get_RightVec(void) { return m_Right; }	//	ライトベクトル取得	
	static const D3DXMATRIX Get_ViewMtx(void) { return m_mtxView; }		//	ビューマトリクス取得
	static CCamera* Camera_Create(void);	//	カメラクラス作成
	
	//	デバッグ用
	void DebugDraw(void);
	static CCamera* Get_CCamera(void) { return m_pCamera; }
protected:


private:
	void Camera_Initialize(void);	//	初期化

	D3DXVECTOR3 m_CameraPos;	//	カメラ座標
	D3DXVECTOR3 m_at;		//	見てる場所	注視点
	float m_AtLength = 0.0; // atまでの長さ

	D3DXVECTOR3 m_Front;		//	フロントベクトル
	static D3DXVECTOR3 m_Right;	//	ライトベクトル
	D3DXVECTOR3 m_Up;			//	アップベクトル

	float m_Angle = 0.0;	//	回転角度
	static D3DXMATRIX m_mtxView;	//	ビュー変換用行列

	static CCamera *m_pCamera;
};

#endif // !1
