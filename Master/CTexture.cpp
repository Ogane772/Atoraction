//////////////////////////////////////////////////
////
////	テクスチャクラス
////
//////////////////////////////////////////////////

//=============================================================================
//	インクルードファイル
//=============================================================================

#include "CTexture.h"

//=============================================================================
//	静的変数
//=============================================================================

CTexture::TextureFileData CTexture::TEXTURE_FILES[] = {
	{ "asset/floor.png",600,600 },
	{ "asset/bullet000.png",80,80 },
	{ "asset/3031.JPG",4000,992 },
	{ "asset/title.png",1920,1080 },
	{ "asset/gameover.jpg",2480,3508 },
	{ "asset/HP_Gage.png",200,50 },
	{ "asset/HP_Gage_2.png",200,50 },
	{ "asset/MP_Gage.png",200,50 },
	{ "asset/stock.png",60,60 },
	{ "asset/number2.png",320,32 },
	{ "asset/score.png",2250,450 },
	{ "asset/map.png",300,300 },			//11
	{ "asset/player_icon.png",120,60 },		//12
	{ "asset/Enemy_mark.png",12,12 },
	{ "asset/hit1.png",3360,960 },
	{ "asset/eff.jpg",80,80 },
	{ "asset/gauge.png",100,20 },
	{ "asset/whitebar.png",100,20 },
	{ "asset/ui/ber.png",1024,157 },
	{ "asset/ui/memori.png",43,38 },
	{ "asset/ui/ui_bg_normal.png",600,600 },
	{ "asset/ui/ui_coldtime.png",600,600 },
	{ "asset/ui/ui_available.png",600,600 },
	{ "asset/ui/ui_futi.png",600,600 },
	{ "asset/ui/futi_aka.png",600,600 },
	{ "asset/ui/futi_kiiro.png",600,600 },
	{ "asset/ui/ui_coffee.png",600,600 },
	{ "asset/ui/ui_freefall.png",600,600 },
	{ "asset/ui/ui_popcorn.png",600,600 },
	{ "asset/ui/ui_wheel.png",600,600 },
	{ "asset/ui/ui_coaster.png",600,600 },
	{ "asset/ui/ui_x.png",81,94 },
	{ "asset/ui/ui_diamond.png",111,121 },
	{ "asset/ui/ui_mp_font.png",450,45 },
	{ "asset/ui/time.png",1500,150 },
	{ "asset/anime_model/outUV1.jpg",256, 256 },
	{ "asset/anime_model/outUV2.jpg",256, 256 },
	{ "asset/anime_model/zago1-end.jpg",256, 256 },
	{ "asset/anime_model/zago2-1.jpg",256, 256 },
	{ "asset/anime_model/zago2-1_2.jpg",256, 256 },
	{ "asset/anime_model/zago2-end.jpg",256, 256 },
	{ "asset/anime_model/zago3-1.jpg",256, 256 },
	{ "asset/anime_model/zago3-1_2.jpg",256, 256 },
	{ "asset/anime_model/zago3-end.jpg",256, 256 },
	{ "asset/anime_model/zago4-1.jpg",256, 256 },
	{ "asset/anime_model/zago4-1_2.jpg",256, 256 },
	{ "asset/anime_model/zago4-end.jpg",256, 256 },
	{ "asset/ui/ui_bar.png",1024,222 },
	{ "asset/ui/ui_graybar.png",1024,222 },
	{ "asset/ui/ui_hpbar.png",1024,222 },
	{ "asset/ui/ui_mpbar.png",1024,222 },
	{ "asset/ui/ui_mp_font.png",800,80 },
	{ "asset/Bar.png",200,50 },
	{ "asset/score2.png",1350,270 },
};

int CTexture::TEXTURE_MAX = sizeof(CTexture::TEXTURE_FILES) / sizeof(TEXTURE_FILES[0]);

LPDIRECT3DTEXTURE9 CTexture::m_pTextures[sizeof(CTexture::TEXTURE_FILES) / sizeof(TEXTURE_FILES[0])] = {};




//=============================================================================
//	生成
//=============================================================================

CTexture::CTexture()
{

}

//=============================================================================
//	破棄
//=============================================================================

CTexture::~CTexture()
{
	//CTexture::Texture_Release();

}


//	テクスチャの読み込み
int CTexture::Texture_Load(void)
{

	HRESULT hr;
	int failed_count = 0;
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		hr = D3DXCreateTextureFromFile(m_pD3DDevice, TEXTURE_FILES[i].filename, &m_pTextures[i]);
		if (FAILED(hr))
		{
			failed_count++;
			MessageBox(NULL, "テクスチャデータを読み込めませんでした", "確認", MB_OK);
		}
	}

	return failed_count;
}


// テクスチャの開放
void CTexture::Texture_Release(void)
{
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (m_pTextures[i] != NULL)
		{
			m_pTextures[i]->Release();
			m_pTextures[i] = NULL;
		}
	}
}


















