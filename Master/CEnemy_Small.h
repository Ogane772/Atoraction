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
	NxActor* Get_Actor(void) { return NxA_pSmall; }
private:
	void EnemySmall_Create(void);
	void Initialize(ENEMY_EMITTER *Emitter);
	
	NxActor* NxA_pSmall;
};
#endif;