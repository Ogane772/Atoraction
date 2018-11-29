//////////////////////////////////////////////////
////
////	�A�g���N�V����(�ϗ���)�N���X
////
//////////////////////////////////////////////////

#ifndef _CWHEEL_H_
#define _CWHEEL_H_

#include "CAttraction.h"

class Cwheel : public CAttraction
{
public:
	Cwheel();
	~Cwheel();

	void Update(void);
	void Draw(void);
	void Finalize(void);
	NxActor* Get_Actor(void) { return NxA_pWheel; }

private:
	void Initialize();
	int m_AttractionIndex;
	NxActor *NxA_pWheel;

	bool ferris_flg;				 //�ړ��ƕǌ��˂̃`�F���W
	int ferris_counter;				 //�ϗ��Ԓ�~
	float rotate_ferris;			//�ϗ��Ԃ̊p�x
	float angle;
	D3DXMATRIX mtxR;
	D3DXVECTOR3 move;
	D3DXVECTOR3 Wheel_position;
};
#endif;