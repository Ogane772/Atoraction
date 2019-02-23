///////////////////////////////////////////////////////////////////////////////////////
//
//			�������������� manual
//
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
//
//		�w�b�_�ǂݍ���
//
///////////////////////////////////////////////////////////////////////////////////////

#include "manual.h"
#include "C2DObj.h"
#include "input.h"
#include "gamepad.h"
#include "CTexture.h"
#include "fade.h"
#include "sound.h"
#include "scene.h"

/////////////////////////////////////////////////////////////////
//
//				�}�N��
//
/////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//
//				�O���[�o���ϐ�
//
/////////////////////////////////////////////////////////////////
static bool g_bend = false;	//	�t�F�[�h�C���A�E�g�t���O
int ManualPage;		// ���݂̃y�[�W
int M_alpha;
int FPS_mCounter;
static DIJOYSTATE2 js;
static LPDIRECTINPUTDEVICE8 pJoyDevice;
static HRESULT hr;

void Manual_Init(void)
{
	g_bend = false;
	ManualPage = 1;
	FPS_mCounter = 0;
	js = { 0 };
	pJoyDevice = *JoyDevice_Get();
	if (pJoyDevice)
	{
		hr = pJoyDevice->Acquire();
	}
}

void Manual_Update(void)
{
	//�R���g���[���[��񂪂���Ƃ��̂ݎ擾
	if (pJoyDevice)
	{
		pJoyDevice->GetDeviceState(sizeof(DIJOYSTATE2), &js);
	}
	// ���̃y�[�W�� ���R���̑����������
	if (!g_bend)
	{
		if (ManualPage == 1)
		{
			if (Keyboard_IsTrigger(DIK_D) && FPS_mCounter >= 30 || Keyboard_IsTrigger(DIK_SPACE) && FPS_mCounter >= 30 || js.lY >= -2 && js.lY <= 2 && js.lX == 6 && FPS_mCounter >= 30) // �������玟�̃y�[�W��
			{
				ManualPage = 2;
				FPS_mCounter = 0;
			}
		}
		if (ManualPage == 2)
		{
			// �O�̃y�[�W�ɂ��ǂ� ���R���̑����������
			if (Keyboard_IsTrigger(DIK_A) && FPS_mCounter >= 30 || js.lY >= -2 && js.lY <= 2 && js.lX == -6 && FPS_mCounter >= 30)
			{
				ManualPage = 1;
				FPS_mCounter = 0;
			}
			// ���̃y�[�W�� ���R���̑����������
			if (Keyboard_IsTrigger(DIK_D) && FPS_mCounter >= 30 || Keyboard_IsTrigger(DIK_SPACE) && FPS_mCounter >= 30 || js.lY >= -2 && js.lY <= 2 && js.lX == 6 && FPS_mCounter >= 30)
			{
				ManualPage = 3;
				FPS_mCounter = 0;
			}
		}
	}
	if (ManualPage == 3)
	{
		// �O�̃y�[�W�ɂ��ǂ� ���R���̑����������
		if (!g_bend)
		{
			if (Keyboard_IsTrigger(DIK_A) && FPS_mCounter >= 30 || js.lY >= -2 && js.lY <= 2 && js.lX == -6 && FPS_mCounter >= 30)
			{
				ManualPage = 2;
				FPS_mCounter = 0;
			}
		}
		if (!g_bend)
		{
			if (Keyboard_IsTrigger(DIK_D) && FPS_mCounter >= 30 || Keyboard_IsTrigger(DIK_SPACE) && FPS_mCounter >= 30 || js.lY >= -2 && js.lY <= 2 && js.lX == 6 && FPS_mCounter >= 30)
			{
				PlaySound(START_SE);
				Fade_Start(true, 1, 0, 0, 0);
				g_bend = true;
			}
		}
		else
		{
			if (!Fade_IsFade())
			{
				StopSound(TITLE_BGM);
				Fade_Start(false, 1, 0, 0, 0);
				Scene_Change(SCENE_INDEX::SCENE_INDEX_GAME);
			}
		}
	}
}

void Manual_Draw(void)
{

	FPS_mCounter += 1;

	// 1�y�[�W��
	if (ManualPage == 1)
	{
		C2DObj::SpriteDraw(CTexture::TEX_CHUTO01, 0, 0);
	}
	// 2�y�[�W��
	if (ManualPage == 2)
	{
		C2DObj::SpriteDraw(CTexture::TEX_CHUTO02,0, 0);
	}
	// 3�y�[�W��
	if (ManualPage == 3)
	{
		C2DObj::SpriteDraw(CTexture::TEX_CHUTO03, 0, 0);
	}

}

void Manual_Fainalize(void)
{

}