#ifndef _NAN_SPRITE_H_
#define _NAN_SPRITE_H_



void Sprite_Initialize(void);
void Sprite_Finalize(void);
void Sprite_SetColor(D3DCOLOR color);
void Sprite_Draw(int texture_index, float dx, float dy);
void Sprite_Draw(int texture_index, float dx, float dy, int tx, int ty, int tw, int th);
void Sprite_ReturnDraw(int texture_index, float dx, float dy, int tx, int ty, int tw, int th, float movex, float movey);
void Sprite_Draw(int texture_index);
void Sprite_BIGDraw(int texture_index, float dx, float dy, int tx, int ty, int tw, int th, float cx, float cy, float sx, float sy);


#endif

