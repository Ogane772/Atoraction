//////////////////////////////////////////////////
////
////	キャラクタクラス
////
//////////////////////////////////////////////////
#ifndef _CCHARACTER_H_
#define _CCHARACTER_H_



#include "C3DObj.h"
#include "Cphysx.h"

class CCharacter : virtual public C3DObj,public CPhysx
{
public:
	CCharacter();
	~CCharacter();

	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	

protected:
	
};

#endif // !1
