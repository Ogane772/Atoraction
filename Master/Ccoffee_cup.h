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
	CCoffeeCup(D3DXMATRIX mtxWorld);
	~CCoffeeCup();

	void Update(void);
	void Draw(void);
	void Finalize(void);
	void CoffeeCup_Create(void);
	bool Get_DrawCheck(void) { return false; }
private:
	void Initialize(D3DXMATRIX mtxWorld);

	float angCup = 0.0f;				//�J�b�v�̉�]
	int CoolTime = 0;					//�N�[���^�C��
	bool B_CoolTime;					//�N�[���^�C���̃u�[��

	D3DXMATRIX m_mtxTranslation2;	//	�ړ��s��
	D3DXMATRIX m_mtxScaling2;	//	�g��s��

	D3DXMATRIX m_mtxWorld2;				//	���[���h�ϊ��p�s��2
	D3DXMATRIX m_mtxWorld3;				//	���[���h�ϊ��p�s��3
	D3DXMATRIX m_mtxWorld4;				//	���[���h�ϊ��p�s��4
};
#endif;