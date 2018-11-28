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


private:
	void Initialize();
	int m_AttractionIndex;

	bool  ferris_flg;				 //�ړ��ƕǌ��˂̃`�F���W
	int   ferris_counter;				 //�ϗ��Ԓ�~
	float rotate_ferris;			//�ϗ��Ԃ̊p�x
	float kakudoXFerris;
	D3DXVECTOR3 Ferris_position;	 //�ϗ��ԍ��W
	D3DXMATRIX m_mtxRotation2;
	D3DXVECTOR3 Wheel_position;
	bool  Wheel_Flg;
	float Rotate_Ferris;
	float Ferris_Angel_stock;
	D3DXVECTOR3 Wheel_position_stock;
};
#endif;