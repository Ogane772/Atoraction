//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================

#include "input.h"
#include "fade.h"
#include "C2DObj.h"
#include "scene.h"
#include "game.h"
#include "score_draw.h"
#include "CUserInterface.h"
#include "Cplayer.h"
#include "CTexture.h"
#include "sound.h"
#include "CEnemy.h"
//=============================================================================
//	�O���[�o���ϐ��錾
//=============================================================================

static bool g_bend;			//	�t�F�[�h�C���A�E�g�t���O
static bool Clear_flg;		//	�N���A����
static float Percent;		//	������
static float Enemy_Percent;
static float Mark_Percent;
static int score_counter;	//	�b��
static int score_total;		//	���v
static float score_per;		//	���Z�p
static float Mark_per;
static int total;

C2DObj *pScore_total;
//=============================================================================
//	����������
//=============================================================================

void Score_total_Initialize(void)
{
	PlaySound(RESULT_BGM);
	//C2DObj::Texture_Release(CTexture::TEX_SCREENSHOT);	//	�e�N�X�`���j��
	//C2DObj::Texture_Load(CTexture::TEX_SCREENSHOT);	//	�e�N�X�`���ǂݍ���
	pScore_total = new C2DObj;
	g_bend = false;
	Clear_flg = false;
	score_per = 0;
	Mark_per = 0;
	score_counter = 0;
	score_total = 0;
	total = 0;
	Percent = 0.0f;
	Enemy_Percent = 0.0f;
	Mark_Percent = 0;
	CGameObj::m_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);	//	���e�X�g�L��
}

//=============================================================================
//	�I������
//=============================================================================

void Score_total_Finalize(void)
{
	delete pScore_total;
}

//=============================================================================
//	�X�V����
//=============================================================================

void Score_total_Update(void)
{
	//�X�R�A��ʂŃJ�E���^�[�X�^�[�g
	score_counter++;



	//�Q�[�W�̒����ɑ΂��鐧����
	Enemy_Percent = 762 * Get_EnemyPer();
	Percent = 100 * Get_EnemyPer();
	//score_total = CUserInterFace::Get_UIScore();
	
	//�Q�[���I�[�o�[
	if (Get_EnemyPer() * 100 < 70)
	{
		Clear_flg = false;
	}
	//�Q�[���N���A�[
	if (Get_EnemyPer() * 100 >= 70)
	{
		Clear_flg = true;
	}

	//	�X�y�[�X�Ń^�C�g����ʂ�
	if (!g_bend)
	{
		if (Keyboard_IsTrigger(DIK_SPACE))
		{
			Fade_Start(true, 3, 0, 0, 0);
			g_bend = true;
			score_counter = 0;
		}
	}
	else
	{
		if (!Fade_IsFade())
		{
			PlaySound(ENTER_SE);
			Fade_Start(false, 3, 0, 0, 0);
			Scene_Change(SCENE_INDEX_RESULT);
		}
	}
}

//=============================================================================
//	�`�揈��
//=============================================================================

void Score_total_Draw(void)
{
	
	pScore_total->m_Sprite_Draw(CTexture::TEX_SCREENSHOT, 0, 0, 0, 0, pScore_total->Texture_GetWidth(CTexture::TEX_SCREENSHOT, 1), pScore_total->Texture_GetHeight(CTexture::TEX_SCREENSHOT, 1));

	//���j��
		//����
		pScore_total->m_Sprite_Draw(CTexture::TEX_RESULT_BREAK, 100, 100, 0, 0, pScore_total->Texture_GetWidth(CTexture::TEX_RESULT_BREAK, 1), pScore_total->Texture_GetHeight(CTexture::TEX_RESULT_BREAK, 1));
		//�l
		if (score_counter >= 100)
		{
			ResultScore_Draw(500, 100, CPlayer::Get_KoCount(), 5,CTexture::TEX_TOTAL, 0);
		}


		// ��
			//����
			pScore_total->m_Sprite_Draw(CTexture::TEX_RESULT_BOU, 50, 600, 0, 0, pScore_total->Texture_GetWidth(CTexture::TEX_RESULT_BOU, 1), pScore_total->Texture_GetHeight(CTexture::TEX_RESULT_BOU, 1));

	//������
		//����
		pScore_total->m_Sprite_Draw(CTexture::TEX_RESULT_PER, 100, 400, 0, 0, pScore_total->Texture_GetWidth(CTexture::TEX_RESULT_PER, 1), pScore_total->Texture_GetHeight(CTexture::TEX_RESULT_PER, 1));
		if (score_counter >= 200)
		{
			////�Q�[�W
			//pScore_total->m_Sprite_Draw(CTexture::TEX_PER_GAUGE01, 530, 465, 0, 0, pScore_total->Texture_GetWidth(CTexture::TEX_PER_GAUGE01, 1), pScore_total->Texture_GetHeight(CTexture::TEX_PER_GAUGE01, 1));
			//pScore_total->m_Sprite_Draw(CTexture::TEX_PER_GAUGE02, 530, 465, 0, 0, score_per * 2, pScore_total->Texture_GetHeight(CTexture::TEX_PER_GAUGE02, 1));
			////�w�W
			//pScore_total->m_Sprite_Draw(CTexture::TEX_BER, 510 + score_per * 2, 440, 0, 0, pScore_total->Texture_GetWidth(CTexture::TEX_BER, 1), pScore_total->Texture_GetHeight(CTexture::TEX_BER, 1));
		

			//�Q�[�W
			pScore_total->Sprite_Draw(CTexture::TEX_MP3, 631, 470, 0, 0, 791, 54, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
			pScore_total->Sprite_Draw(CTexture::TEX_HP3, 631, 470, 0, 0, score_per, 54, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
			pScore_total->Sprite_Draw(CTexture::TEX_UI_BER, 500, 437, 0, 0, 1024, 172, 0.0f, 0.0f, 1.0f, 0.8f, 0.0f);
			//�w�W					
			pScore_total->Sprite_Draw(CTexture::TEX_UI_MEMORI, 614 + 532, 450, 0, 0, 43, 38, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
			pScore_total->Sprite_Draw(CTexture::TEX_UI_MEMORI, 614 + 532, 510, 0, 0, 43, 38, 43 / 2, 38 / 2, 1.0f, 1.0f, D3DXToRadian(180));

			//�l
			ResultScore_Draw(1500, 380, (int)Percent, 2, 1);

			//�w�W�ƃQ�[�W�������Ă�Ƃ�
			if (score_per <= Enemy_Percent)
			{
				score_per+= 3;
			}

			
		}
		
		


	

	//���v
		//����
		pScore_total->m_Sprite_Draw(CTexture::TEX_RESULT_TOTAL, 140, 700, 0, 0, pScore_total->Texture_GetWidth(CTexture::TEX_RESULT_TOTAL, 1), pScore_total->Texture_GetHeight(CTexture::TEX_RESULT_TOTAL, 1));
		
		if (score_counter >= 450)
		{
			if (Clear_flg == false)
			{
				//�l
				ResultScore_Draw(600, 710, score_total, 5, 1);
				//�X�R�A�܂�
				if (score_total < C3DObj::Get_Score())
				{
					score_total += 100;
				}
			}
			if (Clear_flg == true)
			{

				if (score_counter >= 500)
				{
					//�N���A�{�[�i�X�p
					pScore_total->m_Sprite_Draw(CTexture::TEX_CLEAR_BONUS, 1260, 580, 0, 0, pScore_total->Texture_GetWidth(CTexture::TEX_CLEAR_BONUS, 1), pScore_total->Texture_GetHeight(CTexture::TEX_CLEAR_BONUS, 1));
					//2�{�܂Ńv���X
					if (score_total < C3DObj::Get_Score())
					{
						score_total += 100;
					}
				}

				//�l
				ResultScore_Draw(600, 710, C3DObj::Get_Score() + score_total, 5, 0);
			}
		}

}


