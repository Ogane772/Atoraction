#ifndef _SCORE_DRAW_H_
#define _SCORE_DRAW_H_

#include "number.h"
#include "fade.h"
#include "scene.h"
#include "player.h"

void Score_Draw(float x, float y, int score, int fig, bool bLeft, bool bZero);
void Score_Draw(float x, float y, int cache, int fig);
void Score_Initialize(void);
void ResultScore_Draw(float x, float y, int score, int fig, int colornum);
void Mp_Draw(float x, float y, int score, int fig, bool zero);
int Get_TotalScore(void);

void Num_Draw(float x, float y, int score, int fig, int color);
#endif
