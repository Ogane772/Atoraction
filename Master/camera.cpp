//=============================================================================
//	インクルードファイル
//=============================================================================
#include <d3dx9.h>
//#include "mochi_d3d.h"
#include "common.h"
#include "input.h"

//#include "model.h"
#include "Cplayer.h"

#include "debug_font.h"
//#include "move.h"

#include "CGameObj.h"
//=============================================================================
//	定数定義
//=============================================================================

#define NYAA (0.1f)
#define FUAA (150.0f)
#define ASPECT ((float)WINDOW_WIDTH / WINDOW_HIGHT)
#define ATLENGTH (10.0f)
#define CAMERA_SPEED (0.00f)

//=============================================================================
//	グローバル宣言
//=============================================================================

static D3DXVECTOR3 g_CameraPos;	//	カメラ座標
static D3DXVECTOR3 g_at(0.0,0.0,0.0);		//	見てる場所	注視点
static float g_AtLength = 0.0; // atまでの長さ

static D3DXVECTOR3 g_Front;
static D3DXVECTOR3 g_Right;
static D3DXVECTOR3 g_Up;
//static D3DXVECTOR3 g_Speed(0.0f, 0.0f, 0.0f);
//static float g_Speed = 0.0f;
static float g_Angle = 0.0f;

// ビュー座標変換行列 
static D3DXMATRIX g_mtxView;
//=============================================================================
//	初期化処理
//=============================================================================

void Camera_Initialize(void)
{
	g_CameraPos = D3DXVECTOR3(0.0f, 3.0f, -9.0f);
	g_AtLength = ATLENGTH;
	
	g_Front = D3DXVECTOR3(0.0f, -0.5f, 1.0f);
	D3DXVec3Normalize(&g_Front, &g_Front); //　長さを1にする　正規化
	g_Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVec3Cross(&g_Right, &g_Front, &g_Up);	// 外積
	D3DXVec3Normalize(&g_Right, &g_Right); //　長さを1にする　正規化
	D3DXVec3Cross(&g_Up, &g_Right, &g_Front);
	D3DXVec3Normalize(&g_Up, &g_Up); //　長さを1にする　正規化

	
	g_Angle = 2.0;
}



//=============================================================================
//	更新処理
//=============================================================================

void Camera_Updata(void)
{
	
	/*if (Keyboard_IsPress(DIK_RIGHT))
	{
		//g_Angle += 0.2;
		//	Y軸回転
		D3DXMATRIX mtxRotation;
		D3DXMatrixRotationY(&mtxRotation, D3DXToRadian(g_Angle));
		//D3DXMatrixRotationAxis(&mtxRotation, &g_Up, D3DXToRadian(2));
		D3DXVec3TransformNormal(&g_Front, &g_Front, &mtxRotation); // 第2引数を第3引数で行列変換し第1引数に入れる
		D3DXVec3TransformNormal(&g_Right, &g_Right, &mtxRotation);
		D3DXVec3TransformNormal(&g_Up, &g_Up, &mtxRotation);
		
	}
	if (Keyboard_IsPress(DIK_LEFT))
	{
		//g_Angle += 0.2;
		//	Y軸回転
		D3DXMATRIX mtxRotation;
		D3DXMatrixRotationY(&mtxRotation, D3DXToRadian(-g_Angle));
		//D3DXMatrixRotationAxis(&mtxRotation, &g_Up, D3DXToRadian(2));
		D3DXVec3TransformNormal(&g_Front, &g_Front, &mtxRotation); // 第2引数を第3引数で行列変換し第1引数に入れる
		D3DXVec3TransformNormal(&g_Right, &g_Right, &mtxRotation);
		D3DXVec3TransformNormal(&g_Up, &g_Up, &mtxRotation);
	}*/
	if (Keyboard_IsPress(DIK_UP))
	{
		//g_Angle += 0.2;
		//	上回転
		D3DXMATRIX mtxRotation;
		D3DXMatrixRotationAxis(&mtxRotation, &g_Right, D3DXToRadian(g_Angle));
		D3DXVec3TransformNormal(&g_Front, &g_Front, &mtxRotation); // 第2引数を第3引数で行列変換し第1引数に入れる
		D3DXVec3TransformNormal(&g_Up, &g_Up, &mtxRotation);
	}
	if (Keyboard_IsPress(DIK_DOWN))
	{
		//g_Angle += 0.2;
		//	下回転
		D3DXMATRIX mtxRotation;
		D3DXMatrixRotationAxis(&mtxRotation, &g_Right, D3DXToRadian(-g_Angle));
		D3DXVec3TransformNormal(&g_Front, &g_Front, &mtxRotation); // 第2引数を第3引数で行列変換し第1引数に入れる
		D3DXVec3TransformNormal(&g_Up, &g_Up, &mtxRotation);
	}

	

	//	atを作る式
//	g_at = g_Front * g_AtLength + g_CameraPos;
	D3DXMATRIX at;
	CPlayer *pPlayer = CPlayer::Get_Player(0);
	//at = pPlayer->Get_mtxWorld();
	at = pPlayer->Get_mtxkeep();

	g_at.x = at._41;
	g_at.y = at._42;
	g_at.z = at._43;

	if (Keyboard_IsPress(DIK_RIGHT))
	{
		//	注視点回転
		D3DXMATRIX mtxRotation;
		D3DXMatrixRotationY(&mtxRotation, D3DXToRadian(g_Angle));
		//D3DXMatrixRotationAxis(&mtxRotation, &g_Up, D3DXToRadian(2));
		D3DXVec3TransformNormal(&g_Front, &g_Front, &mtxRotation); // 第2引数を第3引数で行列変換し第1引数に入れる
		D3DXVec3TransformNormal(&g_Right, &g_Right, &mtxRotation);
		D3DXVec3TransformNormal(&g_Up, &g_Up, &mtxRotation);
	}
	if (Keyboard_IsPress(DIK_LEFT))
	{
		//	注視点回転
		D3DXMATRIX mtxRotation;
		D3DXMatrixRotationY(&mtxRotation, D3DXToRadian(-g_Angle));
		//D3DXMatrixRotationAxis(&mtxRotation, &g_Up, D3DXToRadian(2));
		D3DXVec3TransformNormal(&g_Front, &g_Front, &mtxRotation); // 第2引数を第3引数で行列変換し第1引数に入れる
		D3DXVec3TransformNormal(&g_Right, &g_Right, &mtxRotation);
		D3DXVec3TransformNormal(&g_Up, &g_Up, &mtxRotation);
	}
	
	g_CameraPos = g_at - g_Front * g_AtLength;

	/*D3DXMATRIX mtxpos = pPlayer->Get_mtxkeep();
	D3DXVECTOR3 pos(mtxpos._41/2, mtxpos._42+3.0f, mtxpos._43-9.0f);
	g_CameraPos += pos;*/
	if (Keyboard_IsPress(DIK_W))
	{
		//　まっすぐ進む　速度は落ちる
		//D3DXVECTOR3 f(g_Front);
		//f.y = 0.0f;
		//g_CameraPos += f*0.05f;
		D3DXVECTOR3 f(g_Front);
		f.y = 0.0f;
		g_CameraPos += f*CAMERA_SPEED;
		//g_Speed += f * CAMERA_SPEED;
		//	速度 ＝ 速度*0.99f
	}
	if (Keyboard_IsPress(DIK_S))
	{
		D3DXVECTOR3 f(g_Front);
		f.y = 0.0f;
		g_CameraPos -= f*CAMERA_SPEED;
		//g_Speed -= f * CAMERA_SPEED;
	}
	if (Keyboard_IsPress(DIK_A))
	{
		D3DXVECTOR3 f(g_Right);
		f.y = 0.0f;
		g_CameraPos += f*CAMERA_SPEED;
		//g_Speed += g_Right * CAMERA_SPEED;

	}
	if (Keyboard_IsPress(DIK_D))
	{
		D3DXVECTOR3 f(g_Right);
		f.y = 0.0f;
		g_CameraPos -= f*CAMERA_SPEED;
		//g_Speed -= g_Right * CAMERA_SPEED;
	}
/*	if ((Keyboard_IsPress(DIK_W)) && (Keyboard_IsPress(DIK_LSHIFT)))
	{
		g_Speed += g_Up * CAMERA_SPEED;
	}
	if ((Keyboard_IsPress(DIK_S)) && (Keyboard_IsPress(DIK_LSHIFT)))
	{
		g_Speed -= g_Up * CAMERA_SPEED;
	}*/
	/*
		D3DXVECTOR3 speed (0.0f,0.0f,0.0f);
		キー入力 → speed += front * 速度;
		
		position += speed;
		speed *= 0.98f;
	*/

	//g_CameraPos += g_Speed;
	//g_Speed *= 0.98f;

	


	//LPDIRECT3DDEVICE9 pD3DDevice = mochi_GetDevice();	
	
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);		//  上方向

											// ビュー座標変換
	D3DXMatrixLookAtLH(&g_mtxView, &g_CameraPos, &g_at, &g_Up);

	// ビュー座標変換行列設定
	CGameObj::m_pD3DDevice->SetTransform(D3DTS_VIEW, &g_mtxView);


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

void  Camera_Draw(void)
{
	DebugFont_Draw(400, 10, "%f\n,%f\n,%f\n,", g_CameraPos.x, g_CameraPos.y, g_CameraPos.z);
}

D3DXVECTOR3 Get_Rvec(void)
{
	return g_Right;
}

const D3DXMATRIX Get_ViewMtx(void)
{
	return g_mtxView;
}