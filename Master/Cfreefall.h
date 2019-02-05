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
	Cfreefall(D3DXMATRIX mtxWorld);
	~Cfreefall();

	void Update(void);
	void Draw(void);
	void Finalize(void);
	void EnemyDamage(void);
	void FreeFallDamage(void);
	bool Get_DrawCheck(void) { return m_DrawCheck; }
private:
	void Initialize(D3DXMATRIX mtxWorld);
	int m_AttractionIndex;
	float ugoki;
	bool Bugoki;
	bool attackon;//true�̎�������
	float moveY = 0.0f;
	int CoolTime = 0;
	bool m_DrawCheck;			//	�`��t���O
	D3DXMATRIX m_mtxWorld2;				//	���[���h�ϊ��p�s��2
	D3DXMATRIX m_mtxTranslation2;		//	�ړ��s��2
	int m_DrawCount;
};
#endif;