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
	{ "asset/title.png",1920,1080},
	{ "asset/gameover.png",1024,576 },
	{ "asset/HP_Gage.png",200,50},
	{ "asset/HP_Gage_2.png",200,50 },
	{ "asset/MP_Gage.png",200,50 },
	{ "asset/stock.png",60,60 },
	{ "asset/number2.png",320,32 },
	{ "asset/score.png",2250,450},
	{ "asset/map.png",300,300 },			//11
	{ "asset/player_icon.png",120,60 },		//12
	{ "asset/Enemy_mark.png",12,12 },
	{ "asset/hit1.png",3360,960 },
	{ "asset/eff.jpg",80,80 },
	{ "asset/gauge.png",100,20 },
	{ "asset/whitebar.png",100,20 },
	{ "asset/anime_model/outUV2.jpg",256, 256}
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
	for (int i = 0;i < TEXTURE_MAX;i++)
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
	for (int i = 0;i < TEXTURE_MAX;i++)
	{
		if (m_pTextures[i] != NULL)
		{
			m_pTextures[i]->Release();
			m_pTextures[i] = NULL;
		}
	}
}


















