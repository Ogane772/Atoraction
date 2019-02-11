//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================

#include "score_draw.h"

//=============================================================================
//	�萔��`
//=============================================================================

#define NUMBER_SIZE (32)
#define SCORE_NUMBER_SIZE (130)
#define MP_NUMBER_SIZE (45)
#define MP_NUMBER_SIZE2 (80) //MP�̉��̐���
//=============================================================================
//	�O���[�o���ϐ��錾
//=============================================================================

static int score = 0;			//	�\���X�R�A
static int scorecache = 0;		//	�ǉ��X�R�A�L���b�V��
static int totalscore = 0;		//	�g�[�^���X�R�A
static bool g_bend = false;


void Score_Initialize(void)
{
	score = 0;
	scorecache = 0;
	totalscore = 0;
	g_bend = false;
}

void Score_Draw(float x, float y, int score, int fig, bool bLeft, bool bZero)
{

	int count_stop_score = 1;
	for (int i = 0; i < fig; i++)
	{
		count_stop_score *= 10;
	}
	if (score >= count_stop_score)
	{
		score = count_stop_score - 1;
	}
	if (bZero)
	{
		for (int i = 0; i < fig; i++)
		{

			int number = score % 10;
			score /= 10;
			Number_Draw(x + NUMBER_SIZE*(fig - (i + 1)), y, number);

		}
	}



}


void Score_Draw(float x, float y, int cache, int fig)
{

	int count_stop_score = 1;
	if (cache < 2100)
	{
		scorecache += cache;	//	�ǉ��_���L���b�V���Ƀv���X
		score = totalscore;		//	�\������X�R�A����

		if (scorecache > 0)		//	�L���b�V���ɓ_�������Ă���
		{
			score += 10;			//	�\�����P�v���X����
			scorecache -= 10;		//	�L���b�V�����P�}�C�i�X
		}
		totalscore = score;		//	�X�R�A���g�[�^���ɕۊ�
	}
	else
	{
		score = cache;
		totalscore += score;
		//Fade_Start(true, 1, 0, 0, 0);
		//g_bend = true;

	}
	if (g_bend)
	{
		if (!Fade_IsFade())
		{
			Fade_Start(false, 1, 0, 0, 0);
			Scene_Change(SCENE_INDEX_RESULT);
		}
	}

	//	�J���X�g�p
	for (int i = 0; i < fig; i++)
	{
		count_stop_score *= 10;
	}
	if (score >= count_stop_score)
	{
		score = count_stop_score - 1;
	}

	//	�X�R�A�\��	�E�l��	�O����
	for (int j = 0; j < fig; j++)
	{
		int number = score % 10;
		score /= 10;
		Number_Draw(x + NUMBER_SIZE*(fig - (j + 1)), y, number);
	}
}


void Mp_Draw(float x, float y, int score, int fig, bool zero)
{

	int count_stop_score = 1;
	for (int i = 0; i < fig; i++)
	{
		count_stop_score *= 10;
	}
	if (score >= count_stop_score)
	{
		score = count_stop_score - 1;
	}

	if (!zero)
	{
		int number = score % 10;
		score /= 10;
		Number_Draw(x + NUMBER_SIZE*(fig + 1), y, number);
		if (score != 0)
		{
			Number_Draw(x + NUMBER_SIZE*fig, y, score);
		}
	}
	else
	{
		for (int i = 0; i < fig; i++)
		{
			int number = score % 10;
			score /= 10;
			Number_Draw(x + NUMBER_SIZE*(fig - (i + 1)), y, number);
		}
	}
}

void Time_Draw(float x, float y, int score, int fig, int color, bool zero)
{

	int count_stop_score = 1;
	for (int i = 0; i < fig; i++)
	{
		count_stop_score *= 10;
	}
	if (score >= count_stop_score)
	{
		score = count_stop_score - 1;
	}


	if (!zero)
	{
		int number = score % 10;
		score /= 10;
		Number_Draw4(x + SCORE_NUMBER_SIZE*(fig + 1), y, number, color);
		for (int i = 0; i < fig - 1; i++)
		{
			if (score > 0)
			{
				int number = score % 10;
				score /= 10;
				Number_Draw4(x + SCORE_NUMBER_SIZE*(fig - i), y, number, color);
			}
		}
	}
	else
	{
		for (int i = 0; i < fig; i++)
		{
			int number = score % 10;
			score /= 10;
			Number_Draw4(x + SCORE_NUMBER_SIZE*(fig - (i + 1)), y, number, color);
		}
	}
}


void Num_Draw(float x, float y, int score, int fig, int color, bool zero)
{

	int count_stop_score = 1;
	for (int i = 0; i < fig; i++)
	{
		count_stop_score *= 10;
	}
	if (score >= count_stop_score)
	{
		score = count_stop_score - 1;
	}


	if (!zero)
	{
		int number = score % 10;
		score /= 10;
		Number_Draw2(x + SCORE_NUMBER_SIZE*(fig + 1), y, number, color);
		for (int i = 0; i < fig - 1; i++)
		{
			if (score > 0)
			{
				int number = score % 10;
				score /= 10;
				Number_Draw2(x + SCORE_NUMBER_SIZE*(fig - i), y, number, color);
			}
		}
	}
	else
	{
		for (int i = 0; i < fig; i++)
		{
			int number = score % 10;
			score /= 10;
			Number_Draw2(x + SCORE_NUMBER_SIZE*(fig - (i + 1)), y, number, color);
		}
	}
}

void Num_Draw2(float x, float y, int score, int fig, int color, bool zero)
{

	int count_stop_score = 1;
	for (int i = 0; i < fig; i++)
	{
		count_stop_score *= 10;
	}
	if (score >= count_stop_score)
	{
		score = count_stop_score - 1;
	}


	if (!zero)
	{
		int number = score % 10;
		score /= 10;
		Number_Draw3(x + MP_NUMBER_SIZE*(fig + 1), y, number, color);
		for (int i = 0; i < fig - 1; i++)
		{
			if (score > 0)
			{
				int number = score % 10;
				score /= 10;
				Number_Draw3(x + MP_NUMBER_SIZE*(fig - i), y, number, color);
			}
		}
	}
	else
	{
		for (int i = 0; i < fig; i++)
		{
			int number = score % 10;
			score /= 10;
			Number_Draw3(x + SCORE_NUMBER_SIZE*(fig - (i + 1)), y, number, color);
		}
	}
}

void Num_Draw3(float x, float y, int score, int fig, int color, bool zero)
{

	int count_stop_score = 1;
	for (int i = 0; i < fig; i++)
	{
		count_stop_score *= 10;
	}
	if (score >= count_stop_score)
	{
		score = count_stop_score - 1;
	}


	if (!zero)
	{
		int number = score % 10;
		score /= 10;
		Number_Draw5(x + MP_NUMBER_SIZE2*(fig + 1), y, number, color);
		for (int i = 0; i < fig - 1; i++)
		{
			if (score > 0)
			{
				int number = score % 10;
				score /= 10;
				Number_Draw5(x + MP_NUMBER_SIZE2*(fig - i), y, number, color);
			}
		}
	}
	else
	{
		for (int i = 0; i < fig; i++)
		{
			int number = score % 10;
			score /= 10;
			Number_Draw5(x + MP_NUMBER_SIZE2*(fig - (i + 1)), y, number, color);
		}
	}
}

void ResultScore_Draw(float x, float y, int score, int fig, int colornum)
{
	for (int i = 0; i < fig; i++)
	{

		int number = score % 10;
		score /= 10;
		Number_Draw2(x + SCORE_NUMBER_SIZE*(fig - (i + 1)), y, number, colornum);

	}

}

int Get_TotalScore(void)
{
	return totalscore;
}