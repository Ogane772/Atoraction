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
		TEX_RANKING_NUM,

		TYPE_MAX,
	};


	static int Texture_Load(void);	//	テクスチャ読み込み
	static void Texture_Release(void);	//	テクスチャ破棄
	static LPDIRECT3DTEXTURE9 Texture_GetTexture(int index) { return m_pTextures[index]; }	//	テクスチャ取得
	static char* Texture_GetFailName(int index) { return TEXTURE_FILES[index].filename; }
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
