//////////////////////////////////////////////////
////
////	エネミー(スペシャル)クラス
////
//////////////////////////////////////////////////

#ifndef _CENEMY_SPECIAL_H_
#define _CENEMY_SPECIAL_H_

#include "CEnemy.h"

class CEnemy_Special : public CEnemy
{
public:
	CEnemy_Special();
	~CEnemy_Special();

	void Update(void);
	void Draw(void);
	void Finalize(void);

private:
	void Initialize(void);


};
#endif;

