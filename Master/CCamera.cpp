//////////////////////////////////////////////////
////
////	�J�����N���X
////
//////////////////////////////////////////////////

//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================

#include "CCamera.h"
#include "Cplayer.h"
#include "common.h"
#include "input.h"
#include "gamepad.h"
#include "debug_font.h"
#include "CCoaster_ON.h"
#define _CRTDBG_MAP_ALLOC

#define new  ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
//=============================================================================
//	�萔��`
//=============================================================================


#define ASPECT ((float)WINDOW_WIDTH / WINDOW_HIGHT)
#define ATLENGTH (14.0f)
#define COSLENGTH (0.5f)
#define CAMERA_SPEED (0.00f)


//=============================================================================
//	�ÓI�ϐ�
//=============================================================================

D3DXVECTOR3 CCamera::m_Right;
D3DXMATRIX CCamera::m_mtxView;
CCamera *CCamera::m_pCamera;
bool CCamera::m_Vibration;
int CCamera::m_VibCount;
float CCamera::angle = 0.0;
bool CCamera::m_AngleCheck = false;

static DIJOYSTATE2 js;
static LPDIRECTINPUTDEVICE8 pJoyDevice;
static HRESULT hr;

bool r = false;
bool l = false;
//=============================================================================
//	����
//=============================================================================
CCamera::CCamera() :CGameObj(CGameObj::TYPE_CAMERA)
{
	Camera_Initialize();
}



//=============================================================================
//	�j��
//=============================================================================
CCamera::~CCamera()
{
	//Camera_Finalize();
}



//	������
void CCamera::Camera_Initialize(void)
{
	m_CameraPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_AtLength = ATLENGTH;
	Cos_AtLength = COSLENGTH;
	Cos_angle = D3DXVECTOR3(0.0f, 0.0f, 3.0f);

	m_Front = D3DXVECTOR3(0.0f, -0.4f, 1.0f);
	D3DXVec3Normalize(&m_Front, &m_Front); //�@������1�ɂ���@���K��
	m_Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVec3Cross(&m_Right, &m_Front, &m_Up);	// �O��
	D3DXVec3Normalize(&m_Right, &m_Right); //�@������1�ɂ���@���K��
	D3DXVec3Cross(&m_Up, &m_Right, &m_Front);
	D3DXVec3Normalize(&m_Up, &m_Up); //�@������1�ɂ���@���K��
	m_AngleCheck = false;
	angle = -90.0;
	m_Angle = 2.0;
	js = { 0 };
	pJoyDevice = *JoyDevice_Get();
	if (pJoyDevice)
	{
		hr = pJoyDevice->Acquire();
	}
	m_Vibration = false;
	m_VibCount = 0;
}

//	�I������
void CCamera::Finalize(void)
{
	if (m_pCamera != NULL)
	{
		delete m_pCamera;
	}
}



//	�J�����N���X�쐬
CCamera* CCamera::Camera_Create(void)
{
	m_pCamera = new CCamera;
	return m_pCamera;
}

//	�X�V
void CCamera::Update(void)
{
	C3DObj *playerget = CPlayer::Get_Player();	//	�v���C���[�擾
	float u;
	u = (int)(playerget->Get_Angle());
	//�R���g���[���[��񂪂���Ƃ��̂ݎ擾
	if (pJoyDevice)
	{
		pJoyDevice->GetDeviceState(sizeof(DIJOYSTATE2), &js);
	}
	D3DXMATRIX at;

	C3DObj *pPlayer = CPlayer::Get_Player();
	bool *standby = C3DObj::GetCosterModeStandby();
	at = pPlayer->Get_mtxWorld();
	
	m_at.x = at._41;
	m_at.y = at._42 + 2.3f;
	m_at.z = at._43;

	m_AngleCheck = false;
	if (!*standby)
	{
		if ((Keyboard_IsPress(DIK_RIGHT)) && !r || js.lRx >= 6)
		{
			//	�����_��]
			D3DXMATRIX mtxRotation;
			D3DXMatrixRotationY(&mtxRotation, D3DXToRadian(m_Angle));
			//D3DXMatrixRotationAxis(&mtxRotation, &m_Up, D3DXToRadian(2));
			D3DXVec3TransformNormal(&m_Front, &m_Front, &mtxRotation); // ��2�������3�����ōs��ϊ�����1�����ɓ����
			D3DXVec3TransformNormal(&m_Right, &m_Right, &mtxRotation);
			D3DXVec3TransformNormal(&m_Up, &m_Up, &mtxRotation);
			m_AngleCheck = true;
			angle += m_Angle;

		}
		if (Keyboard_IsRelease(DIK_RIGHT))
		{
			m_AngleCheck = false;
		}

		if ((Keyboard_IsPress(DIK_LEFT)) && !l || js.lRx <= -6)
		{
			//	�����_��]
			D3DXMATRIX mtxRotation;
			D3DXMatrixRotationY(&mtxRotation, D3DXToRadian(-m_Angle));
			//D3DXMatrixRotationAxis(&mtxRotation, &m_Up, D3DXToRadian(2));
			D3DXVec3TransformNormal(&m_Front, &m_Front, &mtxRotation); // ��2�������3�����ōs��ϊ�����1�����ɓ����
			D3DXVec3TransformNormal(&m_Right, &m_Right, &mtxRotation);
			D3DXVec3TransformNormal(&m_Up, &m_Up, &mtxRotation);
			m_AngleCheck = true;
			angle -= m_Angle;

		}
		if (Keyboard_IsRelease(DIK_RIGHT))
		{
			m_AngleCheck = false;
		}
	}
	if ((Keyboard_IsTrigger(DIK_J)))
	{
		m_Vibration = true;
	}
	/*if ((Keyboard_IsRelease(DIK_J)))
	{
		m_Vibration = false;
		m_VibCount = 0;
	}*/
	//m_CameraPos = m_at - m_Front * m_AtLength;
	if (C3DObj::GetW_coaster() == false)
	{
		//VibrationCtrl();
		m_CameraPos = m_at - m_Front * m_AtLength;
	}
	if (C3DObj::GetW_coaster() == true)
	{

		m_CameraPos = m_at - m_Front * Cos_AtLength;
	}

	//WallCheck();

	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);		//  �����

											// �r���[���W�ϊ�
	D3DXMatrixLookAtLH(&m_mtxView, &m_CameraPos, &m_at, &m_Up);

	// �r���[���W�ϊ��s��ݒ�
	CGameObj::m_pD3DDevice->SetTransform(D3DTS_VIEW, &m_mtxView);


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

//	�`��
void CCamera::Draw(void)
{

}

//	�f�o�b�O�`��
void  CCamera::DebugDraw(void)
{
	DebugFont_Draw(400, 10, "%f\n,%f\n,%f\n,", m_CameraPos.x, m_CameraPos.y, m_CameraPos.z);
}

void CCamera::VibrationCtrl(void)
{
	m_VibCount++;
	if (m_VibCount < 40)
	{
		static int coss = 300;
		if (!m_Vibration)
		{
			m_CameraPos = m_at - m_Front * m_AtLength;
		}
		else
		{
			//m_at.x = (float)((3 ^ (-coss / 100))*cos(coss / 50)*cos(coss / 1));
			m_at.y = (float)((3 ^ (-coss / 100))*cos(coss / 50)*cos(coss / 1));
			m_at.z = (float)((3 ^ (-coss / 100))*cos(coss / 50)*cos(coss / 1));
			//battle_windowY += (float)((3 ^ (-coss / 100))*cos(coss / 50)*cos(coss / 1));
			coss -= 1;
		}
		if (coss < 100)
		{
			coss = 300;
		}
	}
	if (m_VibCount >= 40)
	{
		m_Vibration = false;
		m_VibCount = 0;
	}
}


void CCamera::Dalete_Camera(void)
{
	CGameObj *pcamera = CGameObj::Get(CGameObj::TYPE_CAMERA);
	if (pcamera)
	{
		delete pcamera;
	}
}









