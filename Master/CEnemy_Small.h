//////////////////////////////////////////////////
////
////	エネミー(スモール)クラス
////
//////////////////////////////////////////////////

#ifndef _CENEMY_SMALL_H_
#define _CENEMY_SMALL_H_

#include "CEnemy.h"
#define SMALL_SPEED (0.05f)

class CEnemy_Small: public CEnemy
{
public:
	CEnemy_Small(ENEMY_EMITTER *Emitter);
	~CEnemy_Small();

	void Update(void);
	void Draw(void);
	void Finalize(void);
	void Damage(void);
private:
	void EnemySmall_Create(void);
	void Initialize(ENEMY_EMITTER *Emitter);
	bool m_playercheck;
	bool PlayerCheck(void);
	int m_Movetime = 0;

	bool m_AttackCheck = false;
	int m_AttackTime = 0;
};
#endif;