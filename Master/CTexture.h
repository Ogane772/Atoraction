//////////////////////////////////////////////////
////
////	テクスチャクラス
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


	static int Texture_Load(void);	//	テクスチャ読み込み
	static void Texture_Release(void);	//	テクスチャ破棄

	static LPDIRECT3DTEXTURE9 Texture_GetTexture(int index) { return m_pTextures[index]; }	//	テクスチャ取得
	static int Texture_GetWidth(int index, int cut) { return TEXTURE_FILES[index].width / cut; }	// テクスチャ幅分割	cut:分割数 分割しない場合は1
	static int Texture_GetHeight(int index, int cut) { return TEXTURE_FILES[index].height / cut; }	//	テクスチャ高さ分割 cut:分割数 分割しない場合は1
protected:




private:
	//	テクスチャデータの構造体
	typedef struct TextureFile_tag
	{
		char filename[TEXTURE_FILENAME_MAX];	//	ファイル名
		int width;	//	幅
		int height;	//	高さ
	}TextureFileData;
	static TextureFileData TEXTURE_FILES[];	//	テクスチャ構造体宣言
	static int TEXTURE_MAX;	//	テクスチャ構造体総数
	static LPDIRECT3DTEXTURE9 m_pTextures[];	//	テクスチャポインタ
};
#endif // !1
