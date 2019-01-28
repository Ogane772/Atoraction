//////////////////////////////////////////////////
////
////	アトラクション(建設中)クラス
////
//////////////////////////////////////////////////

#ifndef _STANDBY_H_
#define _STANDBY_H_

#include "CAttraction.h"

class Standby : public CAttraction
{
public:
	Standby();
	~Standby();

	void Update(void);
	void Draw(void);
	void Finalize(void);
	void Standby_Create(void);
	static C3DObj *Get_Standby(void);
	bool Get_DrawCheck(void) { return m_DrawCheck; }
private:
	bool m_DrawCheck;
	void Initialize();

	int CoolTime = 0;					//クールタイム

	bool B_CoolTime;					//クールタイムのブール
};
#endif;