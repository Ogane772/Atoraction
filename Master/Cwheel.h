//////////////////////////////////////////////////
////
////	アトラクション(観覧車)クラス
////
//////////////////////////////////////////////////

#ifndef _CWHEEL_H_
#define _CWHEEL_H_

#include "CAttraction.h"

class Cwheel : public CAttraction
{
public:
	Cwheel();
	~Cwheel();

	void Update(void);
	void Draw(void);
	void Finalize(void);
	NxActor* Get_Actor(void) { return NxA_pWheel; }

private:
	void Initialize();
	int m_AttractionIndex;
	NxActor *NxA_pWheel;

	bool ferris_flg;				 //移動と壁激突のチェンジ
	int ferris_counter;				 //観覧車停止
	float rotate_ferris;			//観覧車の角度
	float angle;
	D3DXMATRIX mtxR;
	D3DXVECTOR3 move;
	D3DXVECTOR3 Wheel_position;
};
#endif;