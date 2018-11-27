//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================

#include <windows.h>
#include <d3dx9.h>
#include "common.h"

//=============================================================================
//	�O���[�o���ϐ��錾
//=============================================================================
static LPDIRECT3D9 g_pD3D = NULL;				//	
static LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;	//�@�f�o�C�X��IDirect3Device9�C���^�[�t�F�C�X

// Direct3D�̏�����
bool mochi_Init(HWND hWnd)
{
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return false;
	}

	//�@D3DPRESENT_PARAMETERS�\���̂̐ݒ�@P41-48
	D3DPRESENT_PARAMETERS d3dpp = {};
	d3dpp.BackBufferWidth = WINDOW_WIDTH;						//	�o�b�N�o�b�t�@�̕�
	d3dpp.BackBufferHeight = WINDOW_HIGHT;						//�@�o�b�N�o�b�t�@�̍���
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;					//	�o�b�N�o�b�t�@�̃t�H�[�}�b�g
	d3dpp.BackBufferCount = 1;									//	�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					//	�X���b�v�G�t�F�N�g
	d3dpp.Windowed = TRUE;										//	��ʃ��[�h	window�Ȃ�TRUE�@fullscreen�Ȃ�FALSE
	d3dpp.EnableAutoDepthStencil = TRUE;						//	�X�e���V���o�b�t�@�̗L��
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					//  �������̌^�@�X�e���V���o�b�t�@16bit		��D3DFMT_D24S8�@�o���Ƃ�
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	//	���t���b�V�����[�g�@���j�^1�b�Ԃ̏����������@�w��\(�Ή����ȓ�)	�t���X�N���[���̂݁@����59-60Hz
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;  	//	���������̐ݒ�@ONE�̕������������@IMMEDIATE�d������ɃI�X�X��
																/*
																��ʍX�V
																���[����E�[�ɓ���	���������@���ĉ���
																�X�V�I���			��������
																�e�B�A�����O�@�t���[���̃Y��	���������O�ɍX�V
																*/

	HRESULT hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice);

	if (FAILED(hr))
	{
		MessageBox(NULL, "", "", MB_OK | MB_DEFBUTTON1);
	}

	//�@�T���v���[
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	// �A���t�@�u�����h��L���ɂ���
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//�@�w�iDEST�̃u�����h�ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	// ������`���|���S��SRC�̃u�����h�ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	return true;
}

// Direct3D�̏C������
void mochi_end(void)
{
	

	// Direct3D�f�o�C�X�̊J��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	// Direct3D�C���^�[�t�F�[�X�̊J��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

// Direct3D�f�o�C�X�|�C���^�̎擾
LPDIRECT3DDEVICE9 mochi_GetDevice(void)
{
	return g_pD3DDevice;
}