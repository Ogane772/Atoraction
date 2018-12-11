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
	CCoffeeCup();
	~CCoffeeCup();

	void Update(void);
	void Draw(void);
	void Finalize(void);
	void CoffeeCup_Create(void);

	NxActor* Get_Actor(void) { return NxA_pCoffee; }
private:
	void Initialize();
	
	float angCup = 0.0f;				//カップの回転
	int CoolTime = 0;					//クールタイム
	bool B_CoolTime;					//クールタイムのブール
	
	D3DXMATRIX m_mtxWorld2;				//	ワールド変換用行列2
	D3DXMATRIX m_mtxTranslation2;		//	移動行列2
	NxActor *NxA_pCoffee, *NxA_pCoffeeTable;
};
#endif;