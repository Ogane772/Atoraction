#pragma once
//////////////////////////
//丸影描画関数
/////////////////////////
#ifndef SHADOW_H_
#define SHADOW_H_
#include <d3dx9.h>
#include <d3d9.h>
#include <windows.h>
void Shadow_Initialize(void);
void Shadow_Create(float x, float y, float scaleX, float scaleY, int shadow_number);//影を消すときに必要な格納番号を受け取るために引数で渡す
void Shadow_Finalize(void);
void Shadow_Update(void);
void Shadow_Draw(void);
void Shadow_Destroy(int number);//指定した番号の影を消去
#endif //SHADOW_H_