//////////////////////////////////////////////////
////
////	�J�����N���X
////
//////////////////////////////////////////////////

#ifndef _CCAMERA_H_
#define _CCAMERA_H_

#include "CGameObj.h"
#define NYAA (0.1f)
#define FUAA (150.0f)

class CCamera :public CGameObj
{
public:
	CCamera();
	~CCamera();


	void Update(void);
	void Draw(void);
	void Finalize(void);		//	�I������
	static D3DXVECTOR3 Get_RightVec(void) { return m_Right; }	//	���C�g�x�N�g���擾	
	static const D3DXMATRIX Get_ViewMtx(void) { return m_mtxView; }		//	�r���[�}�g���N�X�擾
	static CCamera* Camera_Create(void);	//	�J�����N���X�쐬

	void VibrationCtrl(void);
											//	�f�o�b�O�p
	void DebugDraw(void);
	static CCamera* Get_CCamera(void) { return m_pCamera; }

	static bool Get_CameraAngleCheck(void) { return m_AngleCheck; }
	static float Get_Angle(void) { return angle; }
	static void Dalete_Camera(void);
protected:


private:
	void Camera_Initialize(void);	//	������

	D3DXVECTOR3 m_CameraPos;	//	�J�������W
	D3DXVECTOR3 m_at;		//	���Ă�ꏊ	�����_
	float m_AtLength = 0.0; // at�܂ł̒���
	float Cos_AtLength = 0.0;
	D3DXVECTOR3 m_Front;		//	�t�����g�x�N�g��
	static D3DXVECTOR3 m_Right;	//	���C�g�x�N�g��
	D3DXVECTOR3 m_Up;			//	�A�b�v�x�N�g��

	float m_Angle;	//	��]�p�x
	D3DXVECTOR3 Cos_angle;
	static float angle;
	static D3DXMATRIX m_mtxView;	//	�r���[�ϊ��p�s��

	static CCamera *m_pCamera;

	static bool m_AngleCheck;
	static bool m_Vibration;//��ʐU�����邩�ۂ�
	static int m_VibCount;
};

#endif // !1
