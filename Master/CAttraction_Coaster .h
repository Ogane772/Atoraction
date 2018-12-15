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
	NxActor* Get_Actor(void) { return NxA_Coaster; }
	static C3DObj *Get_Coaster(void);
	bool Get_DrawCheck(void) { return false; }
private:
	void Initialize();
	int u;	//���f���̊p�x
	NxActor *NxA_Coaster;
};
#endif;