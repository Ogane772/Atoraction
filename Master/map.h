//////////////////////////////////////////////////
////
////	MAP�I�u�W�F�N�g�N���X
////
//////////////////////////////////////////////////

#ifndef _MAP_H_
#define _MAP_H_

#include "C2DObj.h"
#include <d3dx9.h>

class MapObj : public C2DObj
{
public:
	MapObj();
	~MapObj();

	void Update(void);
	void Draw(void);
	void Finalize(void);

	/*
	texture_index:�e�N�X�`���ԍ�
	dx:�\���������X�v���C�g�̍�����WX
	dy:�\���������X�v���C�g�̍�����WY
	tx:�\���������e�N�X�`���̎n�_X
	ty:�\���������e�N�X�`���̎n�_Y
	tw:�\���������e�N�X�`���̕�
	th:�\���������e�N�X�`���̍���
	*/

protected:



};

#endif // !1

