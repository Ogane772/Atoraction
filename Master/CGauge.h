//////////////////////////////////////////////////
////
////	�A�g���N�V�����i�s�Q�[�W�N���X
////
//////////////////////////////////////////////////

#ifndef _CGAUGE_H_
#define _CGAUGE_H_

#include "CAttraction.h"

class CGAUGE : public CAttraction
{
public:
	CGAUGE(D3DXMATRIX mtxWorld);
	~CGAUGE();

	void Update(void);
	void Draw(void);
	void GaugeDraw(void);
	void UpdateGaugeDraw(void);//�X�V�Q�[�W�\��
	void WhiteGaugeDraw(void);//�X�V�Q�[�W�\��
	void Finalize(void);
	static void CGAUGE_Create(D3DXMATRIX m_mtxWorld);
	static C3DObj *Get_CGAUGE(void);
	bool Get_DrawCheck(void) { return m_DrawCheck; }

	typedef struct
	{
		D3DXVECTOR3 pos;	//	���Wx,y,z
		D3DXVECTOR3 normal; //	�@���x�N�g�� ���W�̌� ������1.0
		D3DCOLOR color;		//  �F
		D3DXVECTOR2 uv;		//  �e�N�X�`��

	}BillBoardVertex3D;
	BillBoardVertex3D g_bb[4];
private:
	bool m_DrawCheck;
	void Initialize(D3DXMATRIX m_mtxWorld);

	float bar_width;
};
#endif;