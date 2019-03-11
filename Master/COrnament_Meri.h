//////////////////////////////////////////////////
////
////	オブジェクト(メリーゴーランド)クラス
////
//////////////////////////////////////////////////

#ifndef _CORNAMENT_MERI_H_
#define _CORNAMENT_MERI_H_

#include "COrnament.h"

class COrnament_MERI : public COrnament
{
public:
	COrnament_MERI(ORNAMENT_EMITTER *Emitter);
	~COrnament_MERI();

	void Update(void);
	void Draw(void);
	void Finalize(void);
	void Damage(void);
	bool Get_DrawCheck(void) { return false; }
private:
	void MERI_Create(void);
	void Initialize(ORNAMENT_EMITTER *Emitter);
	bool m_playercheck;
	float angle;
	THING_NORMAL uma;
	D3DXMATRIX m_mtxWorld2;
	D3DXMATRIX trans2;
	D3DXMATRIX rotation2;
	D3DXMATRIX rotation3;
	D3DXMATRIX scale2;
};
#endif;#pragma once
#pragma once
