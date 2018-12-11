//////////////////////////////////////////////////
////
////	�A�g���N�V����(�t���[�t�H�[��)�N���X
////
//////////////////////////////////////////////////

#ifndef _CFREEFALL_H_
#define _CFREEFALL_H_

#include "CAttraction.h"

class Cfreefall : public CAttraction
{
public:
	Cfreefall();
	~Cfreefall();

	void Update(void);
	void Draw(void);
	void Finalize(void);

	NxActor* Get_Actor(void) { return NxA_pEnban; }
private:
	void Initialize();
	int m_AttractionIndex;
	float ugoki;
	bool Bugoki = false;
	float moveY = 0.0f;
	int CoolTime = 0;
	D3DXMATRIX m_mtxWorld2;				//	���[���h�ϊ��p�s��2
	D3DXMATRIX m_mtxTranslation2;		//	�ړ��s��2
	NxActor *NxA_pEnban, *NxA_pHasira;
};
#endif;