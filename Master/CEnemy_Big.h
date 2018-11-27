//////////////////////////////////////////////////
////
////	エネミー(ビッグ)クラス
////
//////////////////////////////////////////////////

#ifndef _CENEMY_BIG_H_
#define _CENEMY_BIG_H_

#include "CEnemy.h"

class CEnemy_Big : public CEnemy
{
public:
	CEnemy_Big();
	~CEnemy_Big();

	void Update(void);
	void Draw(void);
	void Finalize(void);

private:
	void Initialize(void);


};
#endif;
