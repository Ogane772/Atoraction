//////////////////////////////////////////////////
////
////	アトラクション(コーヒーカップ)クラス
////
//////////////////////////////////////////////////

#ifndef _CCOFFEE_CUP_H_
#define _CCOFFEE_CUP_H_

#include "CAttraction.h"

class CCoffeeCup : public CAttraction
{
public:
	CCoffeeCup(D3DXMATRIX mtxWorld);
	~CCoffeeCup();

	void Update(void);
	void Draw(void);
	void Finalize(void);
	void CoffeeCup_Create(void);
	bool Get_DrawCheck(void) { return false; }
private:
	void Initialize(D3DXMATRIX mtxWorld);

	float angCup = 0.0f;				//カップの回転
	int CoolTime = 0;					//クールタイム
	bool B_CoolTime;					//クールタイムのブール

	D3DXMATRIX m_mtxTranslation2;	//	移動行列
	D3DXMATRIX m_mtxScaling2;	//	拡大行列

	D3DXMATRIX m_mtxWorld2;				//	ワールド変換用行列2
	D3DXMATRIX m_mtxWorld3;				//	ワールド変換用行列3
	D3DXMATRIX m_mtxWorld4;				//	ワールド変換用行列4
};
#endif;