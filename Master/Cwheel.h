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
};
#endif;