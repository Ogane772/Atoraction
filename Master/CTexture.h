//////////////////////////////////////////////////
////
////	�e�N�X�`���N���X
////
//////////////////////////////////////////////////

#ifndef _CTEXTURE_H_
#define _CTEXTURE_H_

#include "CGameObj.h"

#define TEXTURE_FILENAME_MAX (64)

class CTexture : virtual public CGameObj
{
public:
	CTexture();
	~CTexture();

	enum
	{
		TEX_FLORR,
		TEX_BULLET,
		TEX_SKY,
		TEX_TITLE,
		TEX_RESULT,
		TEX_HP,
		TEX_HP2,
		TEX_MP,
		TEX_STOCK,
		TEX_NUM,
		TEX_NUM2,
		TEX_MAP,
		TEX_Player_Icon,
		TEX_ENEMY_ICON,
		TEX_EFFECT_HIT1,
		TEX_SHADOW,
		TEX_GAUGE,
		TEX_WHITE_BAR,
		TEX_UI_BER,
		TEX_UI_MEMORI,
		TEX_UI_BG_NORMAL,
		TEX_UI_BG_COOLTIME,
		TEX_UI_BG_UPGAGE,
		TEX_UI_NORMAL_FUTI,
		TEX_UI_AKA_FUTI,
		TEX_UI_KIIRO_FUTI,
		TEX_UI_COFFEE,
		TEX_UI_FREEWALL,
		TEX_UI_POPCORN,
		TEX_UI_WHEEL,
		TEX_UI_COASTER,
		TEX_UI_X,
		TEX_UI_DIAMOND,
		TEX_UI_NUMBER,
		TEX_UI_TIME,
		TEX_SMALL,
		TEX_SMALL_ANOTHER,
		TEX_SMALL_END,
		TEX_MIDDLE,
		TEX_MIDDLE_ANOTHER,
		TEX_MIDDLE_END,
		TEX_SPECIAL,
		TEX_SPECIAL_ANOTHER,
		TEX_SPECIAL_END,
		TEX_BIG,
		TEX_BIG_ANOTHER,
		TEX_BIG_END,
		TEX_UI_HPWINDOW,
		TEX_UI_GRAYBAR,
		TEX_UI_HPBAR,
		TEX_UI_MPBAR,
		TEX_UI_MP,
		TEX_YELLOW_BAR,
		TEX_RANKING_NUM,
		TEX_KUSA_RENGA,
		TEX_RESULT_BREAK,
		TEX_RESULT_PER,
		TEX_RESULT_BOU,
		TEX_RESULT_TOTAL,
		TEX_BER,
		TEX_GAMECLEAR,
		TEX_CLEAR_BONUS,
		TEX_PER_GAUGE01,
		TEX_PER_GAUGE02,
		TEX_BER02,
		TEX_SCREENSHOT,
		TEX_ATTRACTION,
		TEX_HP3,
		TEX_MP3,
		TEX_MOUNTAIN,
		TEX_A_BUTTON,
		TEX_B_BUTTON,
		TEX_L_BUTTON,
		TEX_R_BUTTON,
		TEX_TOTAL,
		TEX_EFFECT_HIT2,
		TEX_EFFECT_STAR,
		TEX_EFFECT_SHINE,
		TEX_EFFECT_HEAL_17,
		TEX_EFFECT_HIT,
		TEX_EFFECT_IMPACT_13,
		TEX_EFFECT_EFFECT_P020,
		TEX_CHUTO01,
		TEX_CHUTO02,
		TEX_CHUTO03,
		TEX_PUSHBUTTON,
		TEX_TITLELOGO,
		TYPE_MAX,
		
	};


	static int Texture_Load(void);	//	�e�N�X�`���ǂݍ���
	static void Texture_Release(void);	//	�e�N�X�`���j��
	static void Texture_Load(int index);	//	�w�肵���e�N�X�`���ǂݍ���
	static void Texture_Release(int index);	//	�w�肵���e�N�X�`���j��
	static LPDIRECT3DTEXTURE9 Texture_GetTexture(int index) { return m_pTextures[index]; }	//	�e�N�X�`���擾
	static char* Texture_GetFailName(int index) { return TEXTURE_FILES[index].filename; }
	static int Texture_GetWidth(int index, int cut) { return TEXTURE_FILES[index].width / cut; }	// �e�N�X�`��������	cut:������ �������Ȃ��ꍇ��1
	static int Texture_GetHeight(int index, int cut) { return TEXTURE_FILES[index].height / cut; }	//	�e�N�X�`���������� cut:������ �������Ȃ��ꍇ��1
protected:




private:
	//	�e�N�X�`���f�[�^�̍\����
	typedef struct TextureFile_tag
	{
		char filename[TEXTURE_FILENAME_MAX];	//	�t�@�C����
		int width;	//	��
		int height;	//	����
	}TextureFileData;
	static TextureFileData TEXTURE_FILES[];	//	�e�N�X�`���\���̐錾
	static int TEXTURE_MAX;	//	�e�N�X�`���\���̑���
	static LPDIRECT3DTEXTURE9 m_pTextures[];	//	�e�N�X�`���|�C���^
};
#endif // !1
