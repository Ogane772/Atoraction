//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================

#include "input.h"
#include "fade.h"
#include "C2DObj.h"
#include "scene.h"
#include "gamepad.h"
#include "sound.h"
//=============================================================================
//	�O���[�o���ϐ��錾
//=============================================================================

static bool g_bend = false;	//	�t�F�[�h�C���A�E�g�t���O
							//�R���g���[���[�Ɏg���ϐ�
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
}

//=============================================================================
//	�I������
//=============================================================================

void Title_Finalize(void)
{
	delete ptitle;
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
			Scene_Change(SCENE_INDEX_GAME);
		}
	}
}

//=============================================================================
//	�`�揈��
//=============================================================================

void Title_Draw(void)
{


	ptitle->m_Sprite_Draw(3, 0, 0, 0, 0, ptitle->Texture_GetWidth(3, 1), ptitle->Texture_GetHeight(3, 1));

}


