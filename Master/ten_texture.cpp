//=============================================================================
//	インクルードファイル
//=============================================================================

#include <d3dx9.h>
#include "mochi_d3d.h"

//=============================================================================
//	定数定義
//=============================================================================

#define TEXTURE_FILENAME_MAX (64)

//=============================================================================
//	グローバル変数宣言
//=============================================================================

//	テクスチャデータの構造体
typedef struct TextureFile_tag
{
	char filename[TEXTURE_FILENAME_MAX];
	int width;
	int height;
}TextureFileData;

//	使いたいテクスチャの数だけ書く
static const TextureFileData TEXTURE_FILES[] = {
	{"tex.png",1024,1024},
	{"floor.jpg",1600,1066},
	{"bullet000.png",80,80},
	{ "3031.JPG",4000,992},
	{"301.2.JPG",4000,996}
};

// 構造体の数を調べる
static const int TEXTURE_MAX = sizeof(TEXTURE_FILES) / sizeof(TEXTURE_FILES[0]);
//static const int TEXTURE_MAX = ARRAYSIZE(TEXTURE_FILES);

static LPDIRECT3DTEXTURE9 g_pTextures[TEXTURE_MAX];


//	テクスチャ読み込み
int Texture_Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = mochi_GetDevice();

	HRESULT hr;
	int failed_count = 0;
	for (int i = 0;i < TEXTURE_MAX;i++)
	{
		hr = D3DXCreateTextureFromFile(pDevice, TEXTURE_FILES[i].filename, &g_pTextures[i] );
		if (FAILED(hr))
		{
			failed_count++;
			MessageBox(NULL, "テクスチャデータを読み込めませんでした", "確認", MB_OK);
		}
	}

	return failed_count;
}

// テクスチャの開放
void Texture_Release(void)
{
	for (int i = 0;i < TEXTURE_MAX;i++)
	{
		if (g_pTextures[i] != NULL)
		{
			g_pTextures[i]->Release();
			g_pTextures[i] = NULL;
		}
	}
}



//=============================================================================
// ゲッタ関数
//=============================================================================

LPDIRECT3DTEXTURE9 Texture_GetTexture(int index)
{
	return g_pTextures[index];
}


//	テクスチャ幅
int Texture_GetWidth(int index)
{
	return TEXTURE_FILES[index].width;
}
//	テクスチャ幅分割
int Texture_GetWidth(int index,int cut)
{
	return TEXTURE_FILES[index].width / cut;
}
//	テクスチャ高さ
int Texture_GetHeight(int index)
{
	return TEXTURE_FILES[index].height;
}
//	テクスチャ高さ分割
int Texture_GetHeight(int index, int cut)
{
	return TEXTURE_FILES[index].height / cut;
}
