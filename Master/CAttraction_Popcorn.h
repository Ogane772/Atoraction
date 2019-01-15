//////////////////////////////////////////////////
////
////	アトラクション(ポップコーン)クラス
////
//////////////////////////////////////////////////

#ifndef _POPCORN_H_
#define _POPCORN_H_

#include "CAttraction.h"

class Popcorn : public CAttraction
{
public:
	Popcorn();
	~Popcorn();

	void Update(void);
	void Draw(void);
	void Finalize(void);

	bool Get_DrawCheck(void) { return false; }
private:
	void Initialize();

	int CoolTime = 0;					//クールタイム
	bool B_CoolTime;					//クールタイムのブール

};
#endif;