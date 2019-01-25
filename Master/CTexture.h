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
		TYPE_MAX,
	};


	static int Texture_Load(void);	//	�e�N�X�`���ǂݍ���
	static void Texture_Release(void);	//	�e�N�X�`���j��

	static LPDIRECT3DTEXTURE9 Texture_GetTexture(int index) { return m_pTextures[index]; }	//	�e�N�X�`���擾
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
