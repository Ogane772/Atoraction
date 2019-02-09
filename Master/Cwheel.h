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
	bool Get_DrawCheck(void) { return m_DrawCheck; }

private:
	void Initialize();
	void EnemyDamage();
	int m_AttractionIndex;


	bool ferris_flg;				 //�ړ��ƕǌ��˂̃`�F���W
	int ferris_counter;				 //�ϗ��Ԓ�~
	float rotate_ferris;			//�ϗ��Ԃ̊p�x
	float angle;
	bool m_DrawCheck;
	D3DXMATRIX mtxR;
	D3DXMATRIX m_mtxRotationY;		//	�ړ��s��
	D3DXMATRIX m_mtxRotationYY;
	D3DXVECTOR3 move;
	D3DXVECTOR3 Wheel_position;
};
#endif;