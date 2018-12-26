
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
	void Finalize(void);
	static void UICreate(void);

	static int Get_UIScore(void) { return score; }
protected:

private:
	static int score;
};

#endif // !1
