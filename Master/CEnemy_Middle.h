//////////////////////////////////////////////////
////
////	エネミー(ミドル)クラス
////
//////////////////////////////////////////////////

#ifndef _CENEMY_MIDDLE_H_
#define _CENEMY_MIDDLE_H_

#include "CEnemy.h"

class CEnemy_Middle : public CEnemy
{
public:
	CEnemy_Middle();
	~CEnemy_Middle();

	void Update(void);
	void Draw(void);
	void Finalize(void);

private:
	void Initialize(void);


};
#endif;
