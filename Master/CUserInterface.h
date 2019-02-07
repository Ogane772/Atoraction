
//////////////////////////////////////////////////
////
////	UIƒNƒ‰ƒX
////
//////////////////////////////////////////////////

#ifndef _CUSERINTERFACE_H_
#define _CUSERINTERFACE_H_

#include "C2DObj.h"

class CUserInterFace : public C2DObj
{
public:
	CUserInterFace();
	~CUserInterFace();

	void Update(void);
	void Draw(void);
	void Ui_Ber(void);
	void Ui_Icon(void);
	void Finalize(void);
	static void UICreate(void);
protected:

private:
	
};

#endif // !1
