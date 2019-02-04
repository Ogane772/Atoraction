//////////////////////////////////////////////////
////
////	オブジェクト(ゴミ箱)クラス
////
//////////////////////////////////////////////////

#ifndef _CORNAMENT_DUSTBOX_H_
#define _CORNAMENT_DUSTBOX_H_

#include "COrnament.h"

class COrnament_DustBox : public COrnament
{
public:
	COrnament_DustBox(ORNAMENT_EMITTER *Emitter);
	~COrnament_DustBox();

	void Update(void);
	void Draw(void);
	void Finalize(void);
	void Damage(void);
	bool Get_DrawCheck(void) { return false; }
private:
	void Dust_Create(void);
	void Initialize(ORNAMENT_EMITTER *Emitter);
	bool m_playercheck;

};
#endif;