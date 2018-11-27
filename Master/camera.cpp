//=============================================================================
//	�C���N���[�h�t�@�C��
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
//	�萔��`
//=============================================================================

#define NYAA (0.1f)
#define FUAA (150.0f)
#define ASPECT ((float)WINDOW_WIDTH / WINDOW_HIGHT)
#define ATLENGTH (10.0f)
#define CAMERA_SPEED (0.00f)

//=============================================================================
//	�O���[�o���錾
//=============================================================================

static D3DXVECTOR3 g_CameraPos;	//	�J�������W
static D3DXVECTOR3 g_at(0.0,0.0,0.0);		//	���Ă�ꏊ	�����_
static float g_AtLength = 0.0; // at�܂ł̒���

static D3DXVECTOR3 g_Front;
static D3DXVECTOR3 g_Right;
static D3DXVECTOR3 g_Up;
//static D3DXVECTOR3 g_Speed(0.0f, 0.0f, 0.0f);
//static float g_Speed = 0.0f;
static float g_Angle = 0.0f;

// �r���[���W�ϊ��s�� 
static D3DXMATRIX g_mtxView;
//=============================================================================
//	����������
//=============================================================================

void Camera_Initialize(void)
{
	g_CameraPos = D3DXVECTOR3(0.0f, 3.0f, -9.0f);
	g_AtLength = ATLENGTH;
	
	g_Front = D3DXVECTOR3(0.0f, -0.5f, 1.0f);
	D3DXVec3Normalize(&g_Front, &g_Front); //�@������1�ɂ���@���K��
	g_Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVec3Cross(&g_Right, &g_Front, &g_Up);	// �O��
	D3DXVec3Normalize(&g_Right, &g_Right); //�@������1�ɂ���@���K��
	D3DXVec3Cross(&g_Up, &g_Right, &g_Front);
	D3DXVec3Normalize(&g_Up, &g_Up); //�@������1�ɂ���@���K��

	
	g_Angle = 2.0;
}



//=============================================================================
//	�X�V����
//=============================================================================

void Camera_Updata(void)
{
	
	/*if (Keyboard_IsPress(DIK_RIGHT))
	{
		//g_Angle += 0.2;
		//	Y����]
		D3DXMATRIX mtxRotation;
		D3DXMatrixRotationY(&mtxRotation, D3DXToRadian(g_Angle));
		//D3DXMatrixRotationAxis(&mtxRotation, &g_Up, D3DXToRadian(2));
		D3DXVec3TransformNormal(&g_Front, &g_Front, &mtxRotation); // ��2�������3�����ōs��ϊ�����1�����ɓ����
		D3DXVec3TransformNormal(&g_Right, &g_Right, &mtxRotation);
		D3DXVec3TransformNormal(&g_Up, &g_Up, &mtxRotation);
		
	}
	if (Keyboard_IsPress(DIK_LEFT))
	{
		//g_Angle += 0.2;
		//	Y����]
		D3DXMATRIX mtxRotation;
		D3DXMatrixRotationY(&mtxRotation, D3DXToRadian(-g_Angle));
		//D3DXMatrixRotationAxis(&mtxRotation, &g_Up, D3DXToRadian(2));
		D3DXVec3TransformNormal(&g_Front, &g_Front, &mtxRotation); // ��2�������3�����ōs��ϊ�����1�����ɓ����
		D3DXVec3TransformNormal(&g_Right, &g_Right, &mtxRotation);
		D3DXVec3TransformNormal(&g_Up, &g_Up, &mtxRotation);
	}*/
	if (Keyboard_IsPress(DIK_UP))
	{
		//g_Angle += 0.2;
		//	���]
		D3DXMATRIX mtxRotation;
		D3DXMatrixRotationAxis(&mtxRotation, &g_Right, D3DXToRadian(g_Angle));
		D3DXVec3TransformNormal(&g_Front, &g_Front, &mtxRotation); // ��2�������3�����ōs��ϊ�����1�����ɓ����
		D3DXVec3TransformNormal(&g_Up, &g_Up, &mtxRotation);
	}
	if (Keyboard_IsPress(DIK_DOWN))
	{
		//g_Angle += 0.2;
		//	����]
		D3DXMATRIX mtxRotation;
		D3DXMatrixRotationAxis(&mtxRotation, &g_Right, D3DXToRadian(-g_Angle));
		D3DXVec3TransformNormal(&g_Front, &g_Front, &mtxRotation); // ��2�������3�����ōs��ϊ�����1�����ɓ����
		D3DXVec3TransformNormal(&g_Up, &g_Up, &mtxRotation);
	}

	

	//	at����鎮
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
		//	�����_��]
		D3DXMATRIX mtxRotation;
		D3DXMatrixRotationY(&mtxRotation, D3DXToRadian(g_Angle));
		//D3DXMatrixRotationAxis(&mtxRotation, &g_Up, D3DXToRadian(2));
		D3DXVec3TransformNormal(&g_Front, &g_Front, &mtxRotation); // ��2�������3�����ōs��ϊ�����1�����ɓ����
		D3DXVec3TransformNormal(&g_Right, &g_Right, &mtxRotation);
		D3DXVec3TransformNormal(&g_Up, &g_Up, &mtxRotation);
	}
	if (Keyboard_IsPress(DIK_LEFT))
	{
		//	�����_��]
		D3DXMATRIX mtxRotation;
		D3DXMatrixRotationY(&mtxRotation, D3DXToRadian(-g_Angle));
		//D3DXMatrixRotationAxis(&mtxRotation, &g_Up, D3DXToRadian(2));
		D3DXVec3TransformNormal(&g_Front, &g_Front, &mtxRotation); // ��2�������3�����ōs��ϊ�����1�����ɓ����
		D3DXVec3TransformNormal(&g_Right, &g_Right, &mtxRotation);
		D3DXVec3TransformNormal(&g_Up, &g_Up, &mtxRotation);
	}
	
	g_CameraPos = g_at - g_Front * g_AtLength;

	/*D3DXMATRIX mtxpos = pPlayer->Get_mtxkeep();
	D3DXVECTOR3 pos(mtxpos._41/2, mtxpos._42+3.0f, mtxpos._43-9.0f);
	g_CameraPos += pos;*/
	if (Keyboard_IsPress(DIK_W))
	{
		//�@�܂������i�ށ@���x�͗�����
		//D3DXVECTOR3 f(g_Front);
		//f.y = 0.0f;
		//g_CameraPos += f*0.05f;
		D3DXVECTOR3 f(g_Front);
		f.y = 0.0f;
		g_CameraPos += f*CAMERA_SPEED;
		//g_Speed += f * CAMERA_SPEED;
		//	���x �� ���x*0.99f
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
		�L�[���� �� speed += front * ���x;
		
		position += speed;
		speed *= 0.98f;
	*/

	//g_CameraPos += g_Speed;
	//g_Speed *= 0.98f;

	


	//LPDIRECT3DDEVICE9 pD3DDevice = mochi_GetDevice();	
	
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);		//  �����

											// �r���[���W�ϊ�
	D3DXMatrixLookAtLH(&g_mtxView, &g_CameraPos, &g_at, &g_Up);

	// �r���[���W�ϊ��s��ݒ�
	CGameObj::m_pD3DDevice->SetTransform(D3DTS_VIEW, &g_mtxView);


	// �v���W�F�N�V�������W�ϊ��s��
	D3DXMATRIX mtxProjection;
	// �v���W�F�N�V�������W�ϊ�
	D3DXMatrixPerspectiveFovLH(&mtxProjection, D3DXToRadian(60), ASPECT, NYAA, FUAA);
	/*
	1�F�s��A�h���X
	2�F��p ����p�̔���
	3�F�A�X�y�N�g��
	4�Fnear
	5�Ffar
	*/
	// �v���W�F�N�V�������W�ϊ��s��ݒ�
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