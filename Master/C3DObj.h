//////////////////////////////////////////////////
////
////	3D�I�u�W�F�N�g�N���X
////
//////////////////////////////////////////////////

#ifndef _3DOBJ_H_
#define _3DOBJ_H_

#include "CGameObj.h"
#include <d3dx9.h>

class C3DObj :virtual public CGameObj
{
public:
	C3DObj();
	~C3DObj();

	C3DObj(int type);
	typedef enum
	{
		TYPE_PLAYER,	// �v���C���[
		TYPE_ENEMY,		// �G�l�~�[
		TYPE_ATTRACTION,// �A�g���N�V����
		TYPE_COASTER,	// �W�F�b�g�R�[�X�^�[
		TYPE_ORNAMENT,	// ��Q��
		TYPE_etc,		// ���̑�

		TYPE_MAX

	} OBJTYPE;

	virtual void Update(void) = 0;	//	�X�V
	virtual void Draw(void) = 0;	//	�`��

	D3DXMATRIX Get_mtxWorld(void) { return m_mtxWorld; }				//	���[���h�ϊ��p�s��擾
	D3DXMATRIX Get_mtxTranslation(void) { return m_mtxTranslation; }	//	�ړ��p�s��擾

	static void UpdateAll();	// �S�I�u�W�F�N�g�X�V
	static void DrawAll();		// �S�I�u�W�F�N�g�`��
	static void DeleteAll();	// �S�I�u�W�F�N�g�폜
	void C3DObj_delete(void);	// �I�u�W�F�N�g�폜	
	static C3DObj *Get(int nIdx);				// �C���X�^���X�擾
	int Get_3DObjIndex() { return m_3DObjIndex; }	// ���[�N�C���f�b�N�X�擾
	int Get_3DObjType() { return m_3DObjType; }		// ��ގ擾

	int Get_Angle(void) { return m_Angle; }			//	�p�x�擾
	D3DXVECTOR3 Get_Front(void) { return m_front; }	//	�O�x�N�g���擾
	
	int Get_Hp(void) { return m_Hp; }				//	HP�擾
	int Get_Mp(void) { return m_Mp; }				//	MP�擾
	int Get_MpStock(void) { return m_MpStock; }		//	MP�X�g�b�N�擾
	virtual bool Get_DrawCheck(void) = 0;
protected:
	D3DXMATRIX m_mtxWorld;			//	���[���h�ϊ��p�s��
	D3DXMATRIX m_mtxTranslation;	//	�ړ��s��
	D3DXMATRIX m_mtxRotation;		//	�ړ��s��
	D3DXMATRIX m_mtxScaling;		//	�ړ��s��

	
	float m_Angle;			//	�p�x
	D3DXVECTOR3 m_front;	//	�O�x�N�g��
	D3DXVECTOR3 m_right;	//	�E�x�N�g��
	D3DXVECTOR3 m_up;		//	��x�N�g��
	int m_MpStock;			//	MP�X�g�b�N
	int m_Hp;				//	HP
	int m_Mp;				//	MP
	int m_Attack;			//	�U��
private:
	
	
	int m_3DObjIndex;		//	3D�I�u�W�F�N�g�C���f�b�N�X
	int m_3DObjType;		//	3D�I�u�W�F�N�g�^�C�v
	static int m_3DObjNum;	//	�Q�[���I�u�W�F�N�g����
	static C3DObj *p3DObj[MAX_GAMEOBJ];
};

#endif // !1
