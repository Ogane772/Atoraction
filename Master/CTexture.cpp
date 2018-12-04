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
	{ "asset/floor.jpg",1600,1066 },		//0
	{ "asset/bullet000.png",80,80 },		//1
	{ "asset/3031.JPG",4000,992 },			//2
	{ "asset/title.png",1024,576},			//3
	{ "asset/gameover.png",1024,576 },		//4
	{ "asset/HP_Gage.png",200,50},			//5
	{ "asset/HP_Gage_2.png",200,50 },		//6
	{ "asset/MP_Gage.png",200,50 },			//7
	{ "asset/stock.png",60,60 },			//8
	{ "asset/number2.png",320,32 },			//9
	{ "asset/score.png",1500,300},			//10
	{ "asset/map.png",150,150 },			//11
	{ "asset/player_icon.png",60,30 },		//12
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


















