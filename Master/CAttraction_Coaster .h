//////////////////////////////////////////////////
////
////	�A�g���N�V����(�W�F�b�g�R�[�X�^�[)�N���X
////
//////////////////////////////////////////////////

#ifndef _COASTER_H_
#define _COASTER_H_

#include "CAttraction.h"

class Coaster : public CAttraction
{
public:
	Coaster();
	~Coaster();

	void Update(void);
	void Draw(void);
	void Finalize(void);
	void Coaster_Create(void);


private:
	void Initialize();
	int u;	//���f���̊p�x
	bool *coaster = NULL;//�R�[�X�^�[�t���O�i�Q�b�g�Ŏ󂯎��j
#define J_TIME (8000)	//�g�p����
	int endfream = 0;
	int keepfream = 0;
	D3DXVECTOR3 position;
};
#endif;