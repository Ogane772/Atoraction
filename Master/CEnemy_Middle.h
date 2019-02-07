//////////////////////////////////////////////////
////
////	エネミー(ミドル)クラス
////
//////////////////////////////////////////////////

#ifndef _CENEMY_MIDDLE_H_
#define _CENEMY_MIDDLE_H_

#include "CEnemy.h"
#define MIDDLE_SPEED (0.05f)

class CEnemy_Middle : public CEnemy
{
public:
	CEnemy_Middle(ENEMY_EMITTER *Emitter);
	~CEnemy_Middle();

	void Update(void);
	void Draw(void);
	void Finalize(void);
	void Damage(void);

private:
	void Initialize(ENEMY_EMITTER *Emitter);
	bool m_playercheck;

	int m_Movetime = 0;

	bool m_AttackCheck = false;
	int m_AttackTime = 0;

	
};
#endif;
