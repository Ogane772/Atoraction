
//////////////////////////////////////////////////
////
////	UI�N���X
////
//////////////////////////////////////////////////

//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================

#include "CUserInterface.h"
#include "Cplayer.h"
#include "CCamera.h"
#include "common.h"
#include "score_draw.h"
//=============================================================================
//	�萔��`
//=============================================================================
#define HP_GAGE_WIDTH (300)	//HP�Q�[�W�̕�
#define HP_GAGE_HEIGHT (40)	//�Q�[�W�̍���

#define MP_GAGE_WIDTH (350)	//MP�Q�[�W�̕�

//=============================================================================
//	�ÓI�ϐ�
//=============================================================================



//=============================================================================
//	�O���[�o���ϐ�
//=============================================================================

//=============================================================================
//	����
//=============================================================================

CUserInterFace::CUserInterFace()
{
	m_GameObjNum--;
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
	CPlayer *pp = CPlayer::Get_Player(0);
	int hp = pp->Get_Hp();
	Sprite_Draw(TEX_HP,20, 10, 0, 0, HP_GAGE_WIDTH, HP_GAGE_HEIGHT);
	Sprite_Draw(TEX_HP2, 20, 10, 0, 0, HP_GAGE_WIDTH * hp / HP_MAX, HP_GAGE_HEIGHT);

	//MP
	int mp = pp->Get_Mp();
	Sprite_Draw(TEX_HP, 20, 70, 0, 0, MP_MAX*5, HP_GAGE_HEIGHT);
	Sprite_Draw(TEX_MP, 20, 70, 0, 0, mp*5, HP_GAGE_HEIGHT);

	//MP�X�g�b�N
	int stock = pp->Get_MpStock();
	Sprite_Draw(TEX_STOCK, MP_MAX * 6, 60, 0, 0, CTexture::Texture_GetWidth(TEX_STOCK,1), CTexture::Texture_GetHeight(TEX_STOCK, 1));
	Mp_Draw(MP_MAX * 6, 80, stock, 2,0);

	//��������
	int t = CGameObj::m_FrameCount / 60;
	Num_Draw(WINDOW_WIDTH / 2-25, -25, GAMEEND/60-t,2,0,true);
	int tt = CGameObj::m_FrameCount % 61*1.7;
	if (CGameObj::m_FrameCount >= GAMEEND)
	{
		tt = 100;
	}
	Mp_Draw(WINDOW_WIDTH / 2+230, 80, 100 - tt, 2,true);

	//	���j��
	int ko = pp->Get_KoCount();
	Num_Draw(WINDOW_WIDTH / 3, WINDOW_HIGHT / 2+90, ko, 3, 1,false);
}

void CUserInterFace::Finalize(void)
{

}