//////////////////////////////////////////////////
////
////	�I�u�W�F�N�g(�����v)�N���X
////
//////////////////////////////////////////////////

#ifndef _CORNAMENT_LAMP_H_
#define _CORNAMENT_LAMP_H_

#include "COrnament.h"

class COrnament_Lamp : public COrnament
{
public:
	COrnament_Lamp(ORNAMENT_EMITTER *Emitter);
	~COrnament_Lamp();

	void Update(void);
	void Draw(void);
	void Finalize(void);
	void Damage(void);
	bool Get_DrawCheck(void) { return false; }
private:
	void Lamp_Create(void);
	void Initialize(ORNAMENT_EMITTER *Emitter);
	bool m_playercheck;
	int m_DrawCount;
};
#endif;