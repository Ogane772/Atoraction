//////////////////////////////////////////////////
////
////	�A�g���N�V����(�|�b�v�R�[��)�N���X
////
//////////////////////////////////////////////////

#ifndef _POPCORN_H_
#define _POPCORN_H_

#include "CAttraction.h"

class Popcorn : public CAttraction
{
public:
	Popcorn(D3DXMATRIX mtxWorld);
	~Popcorn();

	void Update(void);
	void Draw(void);
	void Finalize(void);

	bool Get_DrawCheck(void) { return false; }
private:
	void Initialize(D3DXMATRIX mtxWorld);

	int CoolTime = 0;					//�N�[���^�C��
	bool B_CoolTime;					//�N�[���^�C���̃u�[��

};
#endif;