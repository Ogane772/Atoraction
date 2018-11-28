//////////////////////////////////////////////////
////
////	アトラクション(ジェットコースター)クラス
////
//////////////////////////////////////////////////

#ifndef _COASTER_H_
#define _COASTER_H_

#include "CAttraction.h"

class Coaster : public CAttraction
{
public:
	Coaster();
	~Coaster();

	void Update(void);
	void Draw(void);
	void Finalize(void);
	void Coaster_Create(void);


private:
	void Initialize();
	int u;	//モデルの角度
	bool *coaster = NULL;//コースターフラグ（ゲットで受け取る）
#define J_TIME (8000)	//使用時間
	int endfream = 0;
	int keepfream = 0;
	D3DXVECTOR3 position;
};
#endif;