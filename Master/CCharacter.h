//////////////////////////////////////////////////
////
////	キャラクタクラス
////
//////////////////////////////////////////////////
#ifndef _CCHARACTER_H_
#define _CCHARACTER_H_



#include "C3DObj.h"
#include "Cphysx.h"

class CCharacter : public C3DObj,public CPhysx
{
public:
	CCharacter();
	~CCharacter();

	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	int Get_Hp(void) { return m_Hp; }
	int Get_Mp(void) { return m_Mp; }

protected:
	int  m_Hp;
	int m_Mp;
};

#endif // !1
