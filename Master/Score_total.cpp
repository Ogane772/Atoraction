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

//=============================================================================
//	�O���[�o���ϐ��錾
//=============================================================================

static bool g_bend;			//	�t�F�[�h�C���A�E�g�t���O
static bool Clear_flg;		//	�N���A����
static float Percent;		//	������
static int score_counter;	//	�b��
static int score_total;		//	���v
static int score_per;		//	���Z�p
static int total;
C2DObj *pScore_total;
//=============================================================================
//	����������
//=============================================================================

void Score_total_Initialize(void)
{
	pScore_total = new C2DObj;
	g_bend = false;
	Clear_flg = false;
	score_per = 0;
	score_counter = 0;
	score_total = 0;
	total = 0;
	Percent = 0;
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
	Percent = 200 * Get_CheckPer();

	//score_total = CUserInterFace::Get_UIScore();
	
	//�Q�[���I�[�o�[
	if (Get_CheckPer() * 100 < 80)
	{
		Clear_flg = false;
	}
	//�Q�[���N���A�[
	if (Get_CheckPer() * 100 >= 80)
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
	//���j��
		//����
		pScore_total->m_Sprite_Draw(14, 100, 70, 0, 0, pScore_total->Texture_GetWidth(14, 1), pScore_total->Texture_GetHeight(14, 1));
		//�l
		if (score_counter >= 100)
		{
			ResultScore_Draw(300, 30, CPlayer::Get_KoCount(), 5, 1);
		}

	//������
		//����
		pScore_total->m_Sprite_Draw(15, 100, 200, 0, 0, pScore_total->Texture_GetWidth(15, 1), pScore_total->Texture_GetHeight(15, 1));
		if (score_counter >= 200)
		{
			//�Q�[�W
			pScore_total->m_Sprite_Draw(7, 400, 215, 0, 0, pScore_total->Texture_GetWidth(7, 1), pScore_total->Texture_GetHeight(7, 1));
			pScore_total->m_Sprite_Draw(6, 400, 215, 0, 0, score_per, pScore_total->Texture_GetHeight(6, 1));
			//�w�W
			pScore_total->m_Sprite_Draw(18, 380 + score_per, 204, 0, 0, pScore_total->Texture_GetWidth(18, 1), pScore_total->Texture_GetHeight(18, 1));
		
			//�l
			ResultScore_Draw(600, 170, Percent/2, 2, 1);

			//�w�W�ƃQ�[�W�������Ă�Ƃ�
			if (score_per <= Percent)
			{
				score_per++;
			}
		}
		
		


	//��
		//����
		pScore_total->m_Sprite_Draw(16, 50, 300, 0, 0, pScore_total->Texture_GetWidth(16, 1), pScore_total->Texture_GetHeight(16, 1));
	

	//���v
		//����
		pScore_total->m_Sprite_Draw(17, 120, 400, 0, 0, pScore_total->Texture_GetWidth(17, 1), pScore_total->Texture_GetHeight(17, 1));
		
		if (score_counter >= 450)
		{
			if (Clear_flg == false)
			{
				//�l
				ResultScore_Draw(300, 360, score_total, 5, 1);
				//�X�R�A�܂�
				if (score_total < CUserInterFace::Get_UIScore())
				{
					score_total += 100;
				}
			}
			if (Clear_flg == true)
			{
				if (score_counter >= 500)
				{
					//�N���A�{�[�i�X�p
					pScore_total->m_Sprite_Draw(20, 700, 280, 0, 0, pScore_total->Texture_GetWidth(20, 1), pScore_total->Texture_GetHeight(20, 1));
					//2�{�܂Ńv���X
					if (score_total < (CUserInterFace::Get_UIScore() * 2))
					{
						score_total += 2;
					}
				}

				//�l
				ResultScore_Draw(300, 360, score_total, 5, 1);
			}
		}

}


