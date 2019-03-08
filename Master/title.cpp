//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================

#include "input.h"
#include "fade.h"
#include "C2DObj.h"
#include "scene.h"
#include "gamepad.h"
#include "sound.h"
#include "C3DObj.h"
#include "common.h"
#include "COrnament.h"
#include "CMeshField.h"
#include "CMeshField_Cylinder.h"
#include "CMesh_SkyDome.h"
#include "Cplayer.h"
#include "debug_font.h"
#include "CLight.h"
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

#define new  ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
//=============================================================================
//	�O���[�o���ϐ��錾
//=============================================================================

static bool g_bend = false;	//	�t�F�[�h�C���A�E�g�t���O
							//�R���g���[���[�Ɏg���ϐ�
static float f;
static float f2;

static int a;
static int b;

static D3DXVECTOR3 g_Camera_Eye;
static D3DXVECTOR3 g_Camera_At;
static D3DXVECTOR3 g_Camera_Up;

static D3DXVECTOR3 front;		//�J�����̑O�����x�N�g���A�K������1�A�P�ʃx�N�g��
static D3DXVECTOR3 right;
static D3DXVECTOR3 up;

static D3DXMATRIX mtxR;

static D3DXMATRIX mtxView;

static float at_lenght;	//at�܂ł̋���
static float speed;

static DIJOYSTATE2 js;
static LPDIRECTINPUTDEVICE8 pJoyDevice;
static HRESULT hr;
C2DObj *ptitle;
//=============================================================================
//	����������
//=============================================================================

void Title_Initialize(void)
{
	ptitle = new C2DObj;
	g_bend = false;
	//�R���g���[���[���擾
	js = { 0 };
	pJoyDevice = *JoyDevice_Get();
	if (pJoyDevice)
	{
		hr = pJoyDevice->Acquire();
	}
	PlaySound(TITLE_BGM);
	g_Camera_Eye = D3DXVECTOR3(0.0f, 30.0f, -50.0f); //eye �J�������W
	g_Camera_At = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	 //at  �����_�E�E�E���������ڂ��Ă��鎋�_
	g_Camera_Up = D3DXVECTOR3(0.0f, -1.0f, 0.0f);	 //up  �J�����̏�����x�N�g��

	front = D3DXVECTOR3(0.0f, -1.0f, 1.0f);
	D3DXVec3Normalize(&front, &front);

	//front�ł�������
	up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXVec3Cross(&right, &up, &front);	//�O�ς͏��Ԃ��̐S
	D3DXVec3Normalize(&right, &right);	//���K��,�ۂߌ덷�h�~

	D3DXVec3Cross(&up, &front, &right);
	D3DXVec3Normalize(&up, &up);

	at_lenght = 40.0f;
	speed = 0.001f;

	a = 0;
	b = 0;
	C3DObj::InitModelLoad();
	CPlayer::PlayerCreate();				//	�v���C���[����		
	CLight::Light_Create();					//	���C�g����
	CMeshField::MeshField_Create(CTexture::TEX_KUSA_RENGA, 120.0f, 2, 2);							//	�n�ʐ���																									//CMeshField_Cylinder::MeshField_Cylinder_Create(CTexture::TEX_FLORR, 10.0f, SYLINDERSIZE, 20, 1,true);	//	���J�x����
	CMeshField_Cylinder::MeshField_Cylinder_Create(CTexture::TEX_MOUNTAIN, 10.0f, FIELDSIZE, 20, 1, false);	//	�O�J�x����
	CMesh_SkyDome::Mesh_SkyDome_Create(CTexture::TEX_SKY, 2.0f, SKYSIZE, 40, 20);
	COrnament::Create();

	CPlayer::TitleFlag_Change(true);

}

//=============================================================================
//	�I������
//=============================================================================

void Title_Finalize(void)
{
	delete ptitle;
	C3DObj::DeleteAll();			//	3D�I�u�W�F�N�g�S����
	CGameObj::DeleteAll2D();
	C3DObj::Model_Finalize();
	CPlayer::TitleFlag_Change(false);
	CPlayer::Reset_KoCount();
	_CrtDumpMemoryLeaks();
	
}

//=============================================================================
//	�X�V����
//=============================================================================

void Title_Update(void)
{
	//�R���g���[���[��񂪂���Ƃ��̂ݎ擾
	if (pJoyDevice)
	{
		pJoyDevice->GetDeviceState(sizeof(DIJOYSTATE2), &js);
	}
	//	�X�y�[�X�܂���A�{�^���ŃQ�[����ʂ�
	if (!g_bend)
	{
		if (Keyboard_IsTrigger(DIK_SPACE) || js.rgbButtons[0] & 0x80)
		{
			PlaySound(START_SE);
			Fade_Start(true, 3, 0, 0, 0);
			g_bend = true;
		}
	}
	else
	{
		if (!Fade_IsFade())
		{
			StopSound(TITLE_BGM);
			Fade_Start(false, 3, 0, 0, 0);
			Scene_Change(SCENE_INDEX_CHUTO);
		}
	}
	if (Keyboard_IsPress(DIK_T))//�X�N���[���V���b�g
	{													   // �o�b�N�o�t�@�̎擾
		LPDIRECT3DSURFACE9 pBackBuf;
		C3DObj::m_pD3DDevice->GetRenderTarget(0, &pBackBuf);

		// スクショ出劁E
		D3DXSaveSurfaceToFile("asset/screenshot.bmp", D3DXIFF_BMP, pBackBuf, NULL, NULL);

		// Get�n�Ŏ擾�����T�[�t�F�C�X��AddRef���Ă΂�Ă���̂ŖY�ꂸ�ɉ������
		pBackBuf->Release();
	}
	g_Camera_At = (front * at_lenght) + g_Camera_Eye;

	D3DXMatrixLookAtLH(&mtxView, &g_Camera_Eye, &g_Camera_At, &up);

	D3DXMATRIX mtxProjection;

	D3DXMatrixPerspectiveFovLH(&mtxProjection, D3DXToRadian(60), (float)WINDOW_WIDTH / WINDOW_HIGHT, 0.1f, 200.0f);	//Fov = ��p(����p),Aspect = �A�X�y�N�g��, near, far

	C3DObj::m_pD3DDevice->SetTransform(D3DTS_VIEW, &mtxView);
	C3DObj::m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);

	b++;

	f = (float)(speed * cos(D3DXToRadian(a)));
	f2 = (float)(speed * sin(D3DXToRadian(a)));
	if (b > 5)
	{
		a += 1;
		g_Camera_Eye.x += f;
		g_Camera_Eye.z += f2;
		g_Camera_Eye -= g_Camera_At;

		D3DXMatrixRotationY(&mtxR, D3DXToRadian(-0.1f));//�J�������񑬓x
		D3DXVec3TransformNormal(&right, &right, &mtxR);		//���̂Ƃ���K�v�Ȃ�
		D3DXVec3TransformNormal(&front, &front, &mtxR);
		D3DXVec3TransformNormal(&up, &up, &mtxR);
	}
	C3DObj::UpdateAll();	//	3D�I�u�W�F�N�g�X�V
	CGameObj::UpdateAll();	//	2D�I�u�W�F�N�g�X�V
}

//=============================================================================
//	�`�揈��
//=============================================================================

void Title_Draw(void)
{

	C3DObj::DrawAll();		//	3D�I�u�W�F�N�g�`��
	CGameObj::DrawAll();	//	2D�I�u�W�F�N�g�`��
	//ptitle->Sprite_Draw(CTexture::TEX_PUSHBUTTON, 400, 700, 0, 0, ptitle->Texture_GetWidth(CTexture::TEX_PUSHBUTTON, 1), ptitle->Texture_GetHeight(CTexture::TEX_PUSHBUTTON, 1));
	ptitle->Sprite_Draw(CTexture::TEX_TITLELOGO, 400, 30, 0, 0, ptitle->Texture_GetWidth(CTexture::TEX_TITLELOGO, 1), ptitle->Texture_GetHeight(CTexture::TEX_TITLELOGO, 1));
	//�e�N�X�`�����o�Ȃ����J������]�����������H
//	DebugFont_Draw(300, 50, "X = %ld , Y= %ld", js.lX, js.lY);
}


