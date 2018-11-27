#ifndef _TEN_TEXTURE_H_
#define _TEN_TEXTURE_H_



int Texture_Load(void);

void Texture_Release(void);

LPDIRECT3DTEXTURE9 Texture_GetTexture(int index);

int Texture_GetWidth(int index);
int Texture_GetHeight(int index);
int Texture_GetWidth(int index, int cut);
int Texture_GetHeight(int index, int cut);
#endif //_COMMON_H_
