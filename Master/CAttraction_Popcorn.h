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
	Popcorn();
	~Popcorn();

	void Update(void);
	void Draw(void);
	void Finalize(void);

	bool Get_DrawCheck(void) { return false; }
	NxActor* Get_Actor(void) { return NxA_pPopcorn; }
private:
	void Initialize();

	int CoolTime = 0;					//�N�[���^�C��
	bool B_CoolTime;					//�N�[���^�C���̃u�[��

	NxActor *NxA_pPopcorn;
};
#endif;