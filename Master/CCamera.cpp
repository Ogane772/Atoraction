//////////////////////////////////////////////////
////
////	カメラクラス
////
//////////////////////////////////////////////////


//=============================================================================
//	インクルードファイル
//=============================================================================

#include "CCamera.h"
#include "Cplayer.h"
#include "common.h"
#include "input.h"

#include "debug_font.h"


//=============================================================================
//	定数定義
//=============================================================================


#define ASPECT ((float)WINDOW_WIDTH / WINDOW_HIGHT)
#define ATLENGTH (14.0f)
#define CAMERA_SPEED (0.00f)


//=============================================================================
//	静的変数
//=============================================================================

D3DXVECTOR3 CCamera::m_Right;
D3DXMATRIX CCamera::m_mtxView;
CCamera *CCamera::m_pCamera;
float CCamera::angle = 0.0;
bool CCamera::m_AngleCheck = false;

bool r = false;
bool l = false;
//=============================================================================
//	生成
//=============================================================================
CCamera::CCamera() :CGameObj(CGameObj::TYPE_CAMERA)
{
	Camera_Initialize();
}



//=============================================================================
//	破棄
//=============================================================================
CCamera::~CCamera()
{
	//Camera_Finalize();
}



//	初期化
void CCamera::Camera_Initialize(void)
{
	m_CameraPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_AtLength = ATLENGTH;

	m_Front = D3DXVECTOR3(0.0f, -0.4f, 1.0f);
	D3DXVec3Normalize(&m_Front, &m_Front); //　長さを1にする　正規化
	m_Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVec3Cross(&m_Right, &m_Front, &m_Up);	// 外積
	D3DXVec3Normalize(&m_Right, &m_Right); //　長さを1にする　正規化
	D3DXVec3Cross(&m_Up, &m_Right, &m_Front);
	D3DXVec3Normalize(&m_Up, &m_Up); //　長さを1にする　正規化
	m_AngleCheck = false;
	angle = -90.0;
	m_Angle = 2.0;
}

//	終了処理
void CCamera::Finalize(void)
{
	if (m_pCamera != NULL)
	{
		delete m_pCamera;
	}
}



//	カメラクラス作成
CCamera* CCamera::Camera_Create(void)
{
	m_pCamera = new CCamera;
	return m_pCamera;
}

//	更新
void CCamera::Update(void)
{
	/*if (Keyboard_IsPress(DIK_UP))
	{
	//	上回転
	D3DXMATRIX mtxRotation;
	D3DXMatrixRotationAxis(&mtxRotation, &m_Right, D3DXToRadian(m_Angle));
	D3DXVec3TransformNormal(&m_Front, &m_Front, &mtxRotation); // 第2引数を第3引数で行列変換し第1引数に入れる
	D3DXVec3TransformNormal(&m_Up, &m_Up, &mtxRotation);
	}
	if (Keyboard_IsPress(DIK_DOWN))
	{
	//	下回転
	D3DXMATRIX mtxRotation;
	D3DXMatrixRotationAxis(&mtxRotation, &m_Right, D3DXToRadian(-m_Angle));
	D3DXVec3TransformNormal(&m_Front, &m_Front, &mtxRotation); // 第2引数を第3引数で行列変換し第1引数に入れる
	D3DXVec3TransformNormal(&m_Up, &m_Up, &mtxRotation);
	}*/

	D3DXMATRIX at;

	C3DObj *pPlayer = CPlayer::Get_Player();
	at = pPlayer->Get_mtxWorld();

	m_at.x = at._41;
	m_at.y = at._42 + 2.3;
	m_at.z = at._43;

	m_AngleCheck = false;

	if ((Keyboard_IsPress(DIK_RIGHT)) && !r)
	{
		//	注視点回転
		D3DXMATRIX mtxRotation;
		D3DXMatrixRotationY(&mtxRotation, D3DXToRadian(m_Angle));
		//D3DXMatrixRotationAxis(&mtxRotation, &m_Up, D3DXToRadian(2));
		D3DXVec3TransformNormal(&m_Front, &m_Front, &mtxRotation); // 第2引数を第3引数で行列変換し第1引数に入れる
		D3DXVec3TransformNormal(&m_Right, &m_Right, &mtxRotation);
		D3DXVec3TransformNormal(&m_Up, &m_Up, &mtxRotation);
		m_AngleCheck = true;
		angle += m_Angle;

	}
	if (Keyboard_IsRelease(DIK_RIGHT))
	{
		m_AngleCheck = false;
	}
	if ((Keyboard_IsPress(DIK_LEFT)) && !l)
	{
		//	注視点回転
		D3DXMATRIX mtxRotation;
		D3DXMatrixRotationY(&mtxRotation, D3DXToRadian(-m_Angle));
		//D3DXMatrixRotationAxis(&mtxRotation, &m_Up, D3DXToRadian(2));
		D3DXVec3TransformNormal(&m_Front, &m_Front, &mtxRotation); // 第2引数を第3引数で行列変換し第1引数に入れる
		D3DXVec3TransformNormal(&m_Right, &m_Right, &mtxRotation);
		D3DXVec3TransformNormal(&m_Up, &m_Up, &mtxRotation);
		m_AngleCheck = true;
		angle -= m_Angle;

	}
	if (Keyboard_IsRelease(DIK_RIGHT))
	{
		m_AngleCheck = false;
	}
	m_CameraPos = m_at - m_Front * m_AtLength;

	//WallCheck();

	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);		//  上方向

											// ビュー座標変換
	D3DXMatrixLookAtLH(&m_mtxView, &m_CameraPos, &m_at, &m_Up);

	// ビュー座標変換行列設定
	CGameObj::m_pD3DDevice->SetTransform(D3DTS_VIEW, &m_mtxView);


	// プロジェクション座標変換行列
	D3DXMATRIX mtxProjection;
	// プロジェクション座標変換
	D3DXMatrixPerspectiveFovLH(&mtxProjection, D3DXToRadian(60), ASPECT, NYAA, FUAA);

	/*
	1：行列アドレス
	2：画角 視野角の半分
	3：アスペクト比
	4：near
	5：far
	*/
	// プロジェクション座標変換行列設定
	CGameObj::m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);



}

//	描画
void CCamera::Draw(void)
{

}

//	デバッグ描画
void  CCamera::DebugDraw(void)
{
	DebugFont_Draw(400, 10, "%f\n,%f\n,%f\n,", m_CameraPos.x, m_CameraPos.y, m_CameraPos.z);
}














