#pragma once
//////////////////////////
//�ۉe�`��֐�
/////////////////////////
#ifndef SHADOW_H_
#define SHADOW_H_
#include <d3dx9.h>
#include <d3d9.h>
#include <windows.h>
void Shadow_Initialize(void);
void Shadow_Create(float* x, float* y, float scaleX, float scaleY, int* shadow_number);//�e�������Ƃ��ɕK�v�Ȋi�[�ԍ����󂯎�邽�߂Ɉ����œn��
void Shadow_Finalize(void);
void Shadow_Update(void);
void Shadow_Draw(void);
void Shadow_Destroy(int number);//�w�肵���ԍ��̉e������
#endif //SHADOW_H_