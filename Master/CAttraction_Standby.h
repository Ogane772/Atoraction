//////////////////////////////////////////////////
////
////	�A�g���N�V����(���ݒ�)�N���X
////
//////////////////////////////////////////////////

#ifndef _STANDBY_H_
#define _STANDBY_H_

#include "CAttraction.h"

class Standby : public CAttraction
{
public:
	Standby(int nType);
	~Standby();

	void Update(void);
	void Draw(void);
	void Finalize(void);
	void Standby_Create(void);
	static C3DObj *Get_Standby(void);
	bool Get_DrawCheck(void) { return m_DrawCheck; }

private:
	bool m_DrawCheck;
	void Initialize(int nType);
	int attraction_type;//�A�g���N�V�����^�C�v���i�[��������Ƃ��ɐ�������
};
#endif;