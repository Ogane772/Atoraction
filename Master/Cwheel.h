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


private:
	void Initialize();
	int m_AttractionIndex;

	bool  ferris_flg;				 //移動と壁激突のチェンジ
	int   ferris_counter;				 //観覧車停止
	float rotate_ferris;			//観覧車の角度
	float kakudoXFerris;
	D3DXVECTOR3 Ferris_position;	 //観覧車座標
	D3DXMATRIX m_mtxRotation2;
	D3DXVECTOR3 Wheel_position;
	bool  Wheel_Flg;
	float Rotate_Ferris;
	float Ferris_Angel_stock;
	D3DXVECTOR3 Wheel_position_stock;
};
#endif;