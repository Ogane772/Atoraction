//////////////////////////////////////////////////
////
////	�A�g���N�V����(�R�[�q�[�J�b�v)�N���X
////
//////////////////////////////////////////////////

#ifndef _CCOFFEE_CUP_H_
#define _CCOFFEE_CUP_H_

#include "CAttraction.h"

class CCoffeeCup : public CAttraction
{
public:
	CCoffeeCup();
	~CCoffeeCup();

	void Update(void);
	void Draw(void);
	void Finalize(void);
	void CoffeeCup_Create(void);

	NxActor* Get_Actor(void) { return NxA_pCoffee; }
private:
	void Initialize();
	
	float angCup = 0.0f;				//�J�b�v�̉�]
	int CoolTime = 0;					//�N�[���^�C��
	bool B_CoolTime;					//�N�[���^�C���̃u�[��
	
	D3DXMATRIX m_mtxWorld2;				//	���[���h�ϊ��p�s��2
	D3DXMATRIX m_mtxTranslation2;		//	�ړ��s��2
	NxActor *NxA_pCoffee, *NxA_pCoffeeTable;
};
#endif;