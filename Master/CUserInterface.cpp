
//////////////////////////////////////////////////
////
////	UI�N���X
////
//////////////////////////////////////////////////

//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================
#include "CAttraction.h"
#include "CUserInterface.h"
#include "Cplayer.h"
#include "CCamera.h"
#include "common.h"
#include "CEnemy.h"
#include "score_draw.h"
#include "game.h"
//=============================================================================
//	�萔��`
//=============================================================================
#define HP_GAGE_WIDTH (300)	//HP�Q�[�W�̕�
#define HP_GAGE_HEIGHT (40)	//�Q�[�W�̍���
//HP�̈ʒu
#define HP_X (20.0f) 
#define HP_Y (10.0f)
#define MP_GAGE_WIDTH (350)	//MP�Q�[�W�̕�
#define COOLTIME_MAX (0) //�N�[���^�C���̊����l
#define ENEMY_MAX (100)
#define ADD_X (100)//�A�g���N�V�����A�C�R���̕\����
#define ADD_Y (240)//�A�g���N�V�����A�C�R���̕\������
//=============================================================================
//	�ÓI�ϐ�
//=============================================================================



//=============================================================================
//	�O���[�o���ϐ�
//=============================================================================

//=============================================================================
//	����
//=============================================================================

CUserInterFace::CUserInterFace() :CGameObj(CGameObj::TYPE_UI)
{

}

//=============================================================================
//	�j��
//=============================================================================

CUserInterFace::~CUserInterFace()
{

}




void CUserInterFace::Update(void)
{

}

void CUserInterFace::Draw(void)
{
	C3DObj *playerget = CPlayer::Get_Player();
	int i;
	int hp = playerget->Get_Hp();
	Sprite_Draw(TEX_UI_GRAYBAR, HP_X, HP_Y, 0, 0, 1024, 222, 0.0f, 0.0f, 0.45f, 0.4f, 0.0f);
	Sprite_Draw(TEX_UI_HPWINDOW, HP_X, HP_Y, 0, 0, 1024, 222, 0.0f, 0.0f, 0.45f, 0.4f, 0.0f);
	Sprite_Draw(TEX_UI_HPBAR, HP_X, HP_Y, 0, 0, 1024.0f * hp / HP_MAX, 222.0f, 0.0f, 0.0f, 0.45f, 0.4f, 0.0f);
	//Sprite_Draw(TEX_UI_HPWINDOW, 20, 10, 0, 0, HP_GAGE_WIDTH, HP_GAGE_HEIGHT);
	//Sprite_Draw(TEX_UI_HPBAR, 20, 10, 0, 0, HP_GAGE_WIDTH * hp / HP_MAX, HP_GAGE_HEIGHT);

	//MP
	int mp = playerget->Get_Mp();
	Sprite_Draw(TEX_UI_GRAYBAR, HP_X, HP_Y + 95, 0, 0, 1024, 222, 0.0f, 0.0f, 0.3f, 0.4f, 0.0f);
	Sprite_Draw(TEX_UI_HPWINDOW, HP_X, HP_Y + 95, 0, 0, 1024, 222, 0.0f, 0.0f, 0.3f, 0.4f, 0.0f);
	Sprite_Draw(TEX_UI_MPBAR, HP_X, HP_Y + 95, 0, 0, mp * 35.0f, 222, 0.0f, 0.0f, 0.3f, 0.4f, 0.0f);
	//	Sprite_Draw(TEX_HP, 20, 100, 0, 0, MP_MAX * 5, HP_GAGE_HEIGHT);
	//	Sprite_Draw(TEX_MP, 20, 100, 0, 0, mp * 5, HP_GAGE_HEIGHT);

	//MP�X�g�b�N
	int stock = playerget->Get_MpStock();
	Sprite_Draw(TEX_UI_DIAMOND, 325.0f, HP_Y + 95, 0, 0, 111, 121, 0.0f, 0.0f, 0.7f, 0.7f, 0.0f);
	Sprite_Draw(TEX_UI_X, 385.0f, HP_Y + 115, 0, 0, 81.0f, 94.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f);
	Num_Draw3(170.0f, HP_Y + 100, stock, 2, 0, false);
	//Sprite_Draw(TEX_STOCK, MP_MAX * 6, 60, 0, 0, CTexture::Texture_GetWidth(TEX_STOCK, 1), CTexture::Texture_GetHeight(TEX_STOCK, 1));
	//Mp_Draw(MP_MAX * 6, 80, stock, 2, 0);

	//��������
	int t = CGameObj::m_FrameCount / 60;
	Time_Draw(WINDOW_WIDTH / 2 - 120, +70, GAMEEND / 60 - t, 2, 0, true);
	int tt = (int)(CGameObj::m_FrameCount % 61 * 1.7);
	if (CGameObj::m_FrameCount >= GAMEEND)
	{
		tt = 100;
	}
	//�E���̃^�C��
	Mp_Draw(WINDOW_WIDTH / 2 + 80, 165, 100 - tt, 2, true);

	//	���j��
	int ko = CPlayer::Get_KoCount();
	Num_Draw(WINDOW_WIDTH / 3 + 500, WINDOW_HIGHT / 2 + 290, ko, 3, 1, false);

	//�~�j�}�b�v
	D3DXMATRIX playermatrix = playerget->Get_mtxTranslation();
	Sprite_Draw(TEX_MAP, 1550.0f, 0.0f, 0, 0, 300, 300);

	User_angle = (int)(playerget->Get_Angle());
	//�L�����N�^�[
	Sprite_Draw(TEX_Player_Icon, 1685.0f + (playermatrix._41 * 1.5f), 140.0f - (playermatrix._43 * 1.5f), 0, 0, 20, 20, 10, 10, 1, 1, D3DXToRadian(User_angle) + D3DXToRadian(90));
	//�A�g���N�V����
	for (i = 0; i < ATTRACTION_MAX; i++)
	{
		C3DObj *attraction_get = CAttraction::Get_Attraction(i);
		if (attraction_get)
		{

			D3DXMATRIX Attraction_matrix = attraction_get->Get_mtxWorld();
			Sprite_Draw(TEX_ATTRACTION, 1688.5f + (Attraction_matrix._41 * 1.56f), 140.0f - (Attraction_matrix._43 * 1.56f), 0, 0, 14, 14, 7, 7, 1, 1, 0);

		}
	}
	//�G�l�~�[
	for (i = 0; i < ENEMY_MAX; i++)
	{
		C3DObj *enemyget = CEnemy::Get_Map_Enemy(i);
		if (enemyget)
		{
			if (enemyget->Get_Enable())
			{
				D3DXMATRIX enemymatrix = enemyget->Get_mtxTranslation();

				Sprite_Draw(TEX_ENEMY_ICON, 1690.0f + (enemymatrix._41 * 1.5f), 150.0f - (enemymatrix._43 * 1.56f), 0, 0, 12, 12, 6, 6, 1, 1, 0);

			}
		}
	}
	Ui_Ber();
	Ui_Icon();
}

void CUserInterFace::Ui_Ber(void)
{
	Sprite_Draw(TEX_MP3, 631, 38, 0, 0, 762, 40, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	Sprite_Draw(TEX_HP3, 631, 38, 0, 0, 762 * Get_EnemyPer(), 40, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	Sprite_Draw(TEX_UI_BER, 500, 10, 0, 0, 1024, 157, 0.0f, 0.0f, 1.0f, 0.6f, 0.0f);
	Sprite_Draw(TEX_UI_MEMORI, 614 + 532, 10, 0, 0, 43, 38, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	Sprite_Draw(TEX_UI_MEMORI, 614 + 532, 70, 0, 0, 43, 38, 43 / 2, 38 / 2, 1.0f, 1.0f, D3DXToRadian(180));
}

void CUserInterFace::Ui_Icon(void)
{
	int i;
	C3DObj *playerget = CPlayer::Get_Player();
	int cooltime[5] = { 0 };
	int at_number = playerget->Get_SummonsNum();
	for (i = 0; i < 5; i++)
	{
		cooltime[i] = playerget->Get_CoolTime(i);
	}
	//�R�[�q�[�J�b�v
	Sprite_Draw(TEX_UI_BG_COOLTIME, 30, ADD_Y, 0, 0, 80, 80, 0.0f, 0.0f, 1.0f, 1.36f, 0.0f);
	Sprite_Draw(TEX_UI_BG_UPGAGE, 30, ADD_Y, 0, 0, 80, ((COOLTIME_COFFEE - cooltime[0]) / COOLTIME_COFFEE) * 80, 40.0f, 47.0f, 1.0f, 1.28f, D3DXToRadian(180));
	Sprite_Draw(TEX_UI_COFFEE, 24, ADD_Y + 27, 0, 0, 600, 600, 0.0f, 0.0f, 0.15f, 0.15f, 0.0f);

	if (cooltime[0] == COOLTIME_MAX)
	{
		Sprite_Draw(TEX_UI_KIIRO_FUTI, 27, ADD_Y, 0, 0, 600, 600, 0.0f, 0.0f, 0.14f, 0.18f, 0.0f);
	}
	else
	{
		Sprite_Draw(TEX_UI_NORMAL_FUTI, 27, ADD_Y, 0, 0, 600, 600, 0.0f, 0.0f, 0.14f, 0.18f, 0.0f);
	}
	if (at_number == SUMMONS_COFFEE)
	{
		Sprite_Draw(TEX_UI_AKA_FUTI, 24, ADD_Y - 3, 0, 0, 600, 600, 0.0f, 0.0f, 0.15f, 0.19f, 0.0f);
		Sprite_Draw(TEX_A_BUTTON, 70, ADD_Y + 80, 0, 0, 200, 200, 0.0f, 0.0f, 0.25f, 0.25f, 0.0f);
	}
	Sprite_Draw(TEX_UI_DIAMOND, 28, ADD_Y + 5, 0, 0, 111, 121, 0.0f, 0.0f, 0.28f, 0.28f, 0.0f);
	Sprite_Draw(TEX_UI_X, 57, ADD_Y + 13, 0, 0, 81, 94, 0.0f, 0.0f, 0.2f, 0.2f, 0.0f);
	Num_Draw2(-20, ADD_Y + 1, COFFEE_MP, 1, 1, false);
	//�t���[�t�H�[��
	Sprite_Draw(TEX_UI_BG_COOLTIME, 30 + ADD_X, ADD_Y, 0, 0, 80, 80, 0.0f, 0.0f, 1.0f, 1.36f, 0.0f);
	Sprite_Draw(TEX_UI_BG_UPGAGE, 30 + ADD_X, ADD_Y, 0, 0, 80, ((COOLTIME_FALL - cooltime[1]) / COOLTIME_FALL) * 80, 40.0f, 47.0f, 1.0f, 1.28f, D3DXToRadian(180));
	Sprite_Draw(TEX_UI_FREEWALL, 24 + ADD_X, ADD_Y + 23, 0, 0, 600, 600, 0.0f, 0.0f, 0.15f, 0.15f, 0.0f);
	//Sprite_Draw(TEX_UI_NORMAL_FUTI, 27, 198, 0, 0, 600, 600, 0.0f, 0.0f, 0.14f, 0.14f, 0.0f);
	if (cooltime[1] == COOLTIME_MAX)
	{
		Sprite_Draw(TEX_UI_KIIRO_FUTI, 27 + ADD_X, ADD_Y, 0, 0, 600, 600, 0.0f, 0.0f, 0.14f, 0.18f, 0.0f);
	}
	else
	{
		Sprite_Draw(TEX_UI_NORMAL_FUTI, 27 + ADD_X, ADD_Y, 0, 0, 600, 600, 0.0f, 0.0f, 0.14f, 0.18f, 0.0f);
	}
	if (at_number == SUMMONS_FALL)
	{
		Sprite_Draw(TEX_UI_AKA_FUTI, 24 + ADD_X, ADD_Y - 3, 0, 0, 600, 600, 0.0f, 0.0f, 0.15f, 0.19f, 0.0f);
		Sprite_Draw(TEX_A_BUTTON, 70 + ADD_X, ADD_Y + 80, 0, 0, 200, 200, 0.0f, 0.0f, 0.25f, 0.25f, 0.0f);
	}
	Sprite_Draw(TEX_UI_DIAMOND, 28 + ADD_X, ADD_Y + 5, 0, 0, 111, 121, 0.0f, 0.0f, 0.28f, 0.28f, 0.0f);
	Sprite_Draw(TEX_UI_X, 57 + ADD_X, ADD_Y + 13, 0, 0, 81, 94, 0.0f, 0.0f, 0.2f, 0.2f, 0.0f);
	Num_Draw2(-20 + ADD_X, ADD_Y + 1, FALL_MP, 1, 1, false);
	//�|�b�v�R�[��
	Sprite_Draw(TEX_UI_BG_COOLTIME, 30 + ADD_X * 2, ADD_Y, 0, 0, 80, 80, 0.0f, 0.0f, 1.0f, 1.36f, 0.0f);
	Sprite_Draw(TEX_UI_BG_UPGAGE, 30 + ADD_X * 2, ADD_Y, 0, 0, 80, ((COOLTIME_POPCORN - cooltime[2]) / COOLTIME_POPCORN) * 80, 40.0f, 47.0f, 1.0f, 1.28f, D3DXToRadian(180));
	Sprite_Draw(TEX_UI_POPCORN, 24 + ADD_X * 2, ADD_Y + 23, 0, 0, 600, 600, 0.0f, 0.0f, 0.15f, 0.15f, 0.0f);
	//Sprite_Draw(TEX_UI_NORMAL_FUTI, 27, 198, 0, 0, 600, 600, 0.0f, 0.0f, 0.14f, 0.14f, 0.0f);
	if (cooltime[2] == COOLTIME_MAX)
	{
		Sprite_Draw(TEX_UI_KIIRO_FUTI, 27 + ADD_X * 2, ADD_Y, 0, 0, 600, 600, 0.0f, 0.0f, 0.14f, 0.18f, 0.0f);
	}
	else
	{
		Sprite_Draw(TEX_UI_NORMAL_FUTI, 27 + ADD_X * 2, ADD_Y, 0, 0, 600, 600, 0.0f, 0.0f, 0.14f, 0.18f, 0.0f);
	}
	if (at_number == SUMMONS_POPCORN)
	{
		Sprite_Draw(TEX_UI_AKA_FUTI, 24 + ADD_X * 2, ADD_Y - 3, 0, 0, 600, 600, 0.0f, 0.0f, 0.15f, 0.19f, 0.0f);
		Sprite_Draw(TEX_A_BUTTON, 70 + ADD_X * 2, ADD_Y + 80, 0, 0, 200, 200, 0.0f, 0.0f, 0.25f, 0.25f, 0.0f);
	}
	Sprite_Draw(TEX_UI_DIAMOND, 28 + ADD_X * 2, ADD_Y + 5, 0, 0, 111, 121, 0.0f, 0.0f, 0.28f, 0.28f, 0.0f);
	Sprite_Draw(TEX_UI_X, 57 + ADD_X * 2, ADD_Y + 13, 0, 0, 81, 94, 0.0f, 0.0f, 0.2f, 0.2f, 0.0f);
	Num_Draw2(-20 + ADD_X * 2, ADD_Y + 1, POPCORN_MP, 1, 1, false);
	//�z�C�[��
	Sprite_Draw(TEX_UI_BG_COOLTIME, 30 + ADD_X * 3, ADD_Y, 0, 0, 80, 80, 0.0f, 0.0f, 1.0f, 1.36f, 0.0f);
	Sprite_Draw(TEX_UI_BG_UPGAGE, 30 + ADD_X * 3, ADD_Y, 0, 0, 80, ((COOLTIME_WHEEL - cooltime[3]) / COOLTIME_WHEEL) * 80, 40.0f, 47.0f, 1.0f, 1.28f, D3DXToRadian(180));
	Sprite_Draw(TEX_UI_WHEEL, 24 + ADD_X * 3, ADD_Y + 23, 0, 0, 600, 600, 0.0f, 0.0f, 0.15f, 0.15f, 0.0f);
	//Sprite_Draw(TEX_UI_NORMAL_FUTI, 27, 198, 0, 0, 600, 600, 0.0f, 0.0f, 0.14f, 0.14f, 0.0f);
	if (cooltime[3] == COOLTIME_MAX)
	{
		Sprite_Draw(TEX_UI_KIIRO_FUTI, 27 + ADD_X * 3, ADD_Y, 0, 0, 600, 600, 0.0f, 0.0f, 0.14f, 0.18f, 0.0f);
	}
	else
	{
		Sprite_Draw(TEX_UI_NORMAL_FUTI, 27 + ADD_X * 3, ADD_Y, 0, 0, 600, 600, 0.0f, 0.0f, 0.14f, 0.18f, 0.0f);
	}
	if (at_number == SUMMONS_WHEEL)
	{
		Sprite_Draw(TEX_UI_AKA_FUTI, 24 + ADD_X * 3, ADD_Y - 3, 0, 0, 600, 600, 0.0f, 0.0f, 0.15f, 0.19f, 0.0f);
		Sprite_Draw(TEX_A_BUTTON, 70 + ADD_X * 3, ADD_Y + 80, 0, 0, 200, 200, 0.0f, 0.0f, 0.25f, 0.25f, 0.0f);
	}
	Sprite_Draw(TEX_UI_DIAMOND, 28 + ADD_X * 3, ADD_Y + 5, 0, 0, 111, 121, 0.0f, 0.0f, 0.28f, 0.28f, 0.0f);
	Sprite_Draw(TEX_UI_X, 57 + ADD_X * 3, ADD_Y + 13, 0, 0, 81, 94, 0.0f, 0.0f, 0.2f, 0.2f, 0.0f);
	Num_Draw2(-20 + ADD_X * 3, ADD_Y + 1, WHEEL_MP, 1, 1, false);
	//�R�[�X�^�[
	Sprite_Draw(TEX_UI_BG_COOLTIME, 30 + ADD_X * 4, ADD_Y, 0, 0, 80, 80, 0.0f, 0.0f, 1.0f, 1.36f, 0.0f);
	Sprite_Draw(TEX_UI_BG_UPGAGE, 30 + ADD_X * 4, ADD_Y, 0, 0, 80, ((COOLTIME_COASTER - cooltime[4]) / COOLTIME_COASTER) * 80, 40.0f, 47.0f, 1.0f, 1.28f, D3DXToRadian(180));
	Sprite_Draw(TEX_UI_COASTER, 24 + ADD_X * 4, ADD_Y + 23, 0, 0, 600, 600, 0.0f, 0.0f, 0.15f, 0.15f, 0.0f);
	//Sprite_Draw(TEX_UI_NORMAL_FUTI, 27, 198, 0, 0, 600, 600, 0.0f, 0.0f, 0.14f, 0.14f, 0.0f);
	if (cooltime[4] == COOLTIME_MAX)
	{
		Sprite_Draw(TEX_UI_KIIRO_FUTI, 27 + ADD_X * 4, ADD_Y, 0, 0, 600, 600, 0.0f, 0.0f, 0.14f, 0.18f, 0.0f);
	}
	else
	{
		Sprite_Draw(TEX_UI_NORMAL_FUTI, 27 + ADD_X * 4, ADD_Y, 0, 0, 600, 600, 0.0f, 0.0f, 0.14f, 0.18f, 0.0f);
	}
	if (at_number == SUMMONS_COASTER)
	{
		Sprite_Draw(TEX_UI_AKA_FUTI, 24 + ADD_X * 4, ADD_Y - 3, 0, 0, 600, 600, 0.0f, 0.0f, 0.15f, 0.19f, 0.0f);
		Sprite_Draw(TEX_A_BUTTON, 70 + ADD_X * 4, ADD_Y + 80, 0, 0, 200, 200, 0.0f, 0.0f, 0.25f, 0.25f, 0.0f);
	}
	Sprite_Draw(TEX_UI_DIAMOND, 28 + ADD_X * 4, ADD_Y + 5, 0, 0, 111, 121, 0.0f, 0.0f, 0.28f, 0.28f, 0.0f);
	Sprite_Draw(TEX_UI_X, 57 + ADD_X * 4, ADD_Y + 13, 0, 0, 81, 94, 0.0f, 0.0f, 0.2f, 0.2f, 0.0f);
	Num_Draw2(-20 + ADD_X * 4, ADD_Y + 1, COASTER_MP, 1, 1, false);

	Sprite_Draw(TEX_L_BUTTON, 0, ADD_Y - 45, 0, 0, 200, 200, 0.0f, 0.0f, 0.4f, 0.2f, 0.0f);
	Sprite_Draw(TEX_R_BUTTON, 450, ADD_Y - 45, 0, 0, 200, 200, 0.0f, 0.0f, 0.4f, 0.2f, 0.0f);
}

void CUserInterFace::Finalize(void)
{

}

void CUserInterFace::UICreate(void)
{
	CUserInterFace *pui = new CUserInterFace;

}