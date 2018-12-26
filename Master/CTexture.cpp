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
	{ "asset/floor.jpg",1600,1066 },
	{ "asset/bullet000.png",80,80 },
	{ "asset/3031.JPG",4000,992 },
	{ "asset/title.png",1024,576},
	{ "asset/gameover.png",1024,576 },
	{ "asset/HP_Gage.png",200,50},
	{ "asset/HP_Gage_2.png",200,50 },
	{ "asset/MP_Gage.png",200,50 },
	{ "asset/stock.png",60,60 },
	{ "asset/number2.png",320,32 },
	{ "asset/score.png",1500,300},
	{ "asset/map.png",150,150 },			//11
	{ "asset/player_icon.png",60,30 },		//12
	{ "asset/Enemy_mark.png",6,6 },		
	{ "asset/screenshot.bmp",1024,576 },
	{ "asset/score_result01.png",210, 70 },			
	{ "asset/score_result02.png",210, 70 },			
	{ "asset/Score_result03.png",924, 2 },			
	{ "asset/Score_result04png.png",140, 70 },		
	{ "asset/a.png", 40,72 },						
	{ "asset/GameClear.png", 912,250 },				
	{ "asset/Clear_bonus03.png", 300, 200 },		
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


















