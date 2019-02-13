//////////////////////////////////////////////////
////
////	オブジェクト(観覧車	)クラス
////
//////////////////////////////////////////////////

#ifndef _CORNAMENT_KANRANSYA_H_
#define _CORNAMENT_KANRANSYA_H_

#include "COrnament.h"

class COrnament_KANRANSYA : public COrnament
{
public:
	COrnament_KANRANSYA(ORNAMENT_EMITTER *Emitter);
	~COrnament_KANRANSYA();

	void Update(void);
	void Draw(void);
	void Finalize(void);
	void Damage(void);
	bool Get_DrawCheck(void) { return false; }
private:
	void Kanransya_Create(void);
	void Initialize(ORNAMENT_EMITTER *Emitter);
	bool m_playercheck;

};
#endif;#pragma once
