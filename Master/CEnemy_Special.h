//////////////////////////////////////////////////
////
////	�G�l�~�[(�X�y�V����)�N���X
////
//////////////////////////////////////////////////

#ifndef _CENEMY_SPECIAL_H_
#define _CENEMY_SPECIAL_H_

#include "CEnemy.h"
#define SPECIAL_SPEED (0.05f)

class CEnemy_Special : public CEnemy
{
public:
	CEnemy_Special(ENEMY_EMITTER *Emitter);
	~CEnemy_Special();

	void Update(void);
	void Draw(void);
	void Finalize(void);
	
private:
	
	void Initialize(ENEMY_EMITTER *Emitter);

	int m_Movetime = 0;

	bool m_AttackCheck = false;
	int m_AttackTime = 0;

	void Special_Move(void);
	void Special_Attack(void);
};
#endif;

