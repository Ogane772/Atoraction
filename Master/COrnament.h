//////////////////////////////////////////////////
////
////	��Q���N���X
////
//////////////////////////////////////////////////

#ifndef _CORNAMENT_H_
#define _CORNAMENT_H_

#include "C3DObj.h"

#define ORNAMENT_MAX (100)
#define ORNAMENT_WAIT_TIME (15)//���G����

class COrnament :virtual public C3DObj
{
public:
	
	enum
	{
		TYPE_ALL = 0,

		TYPE_LAMP,		//	�X��
		TYPE_DUSTBOX,	//	�S�~��
		TYPE_BENCH,		//	�x���`
		TYPE_FOUNTAIN,	//	����
		TYPE_KANRANSYA_DODAI,	//�ϗ��Ԃ̓y��	
		TYPE_HUSEN,				//���D
		TYPE_MERI,				//�����[�S�[�����h
		TYPE_GASUBONBE,         //�K�X�{���x
		TYPE_POTETO,			//�����ۂĂƑ�
		TYPE_MAX
	};
	
	COrnament();
	COrnament::COrnament(int OrnamentType);
	~COrnament();
	void Ornament_Finalize(int Index);


	static void Create(void);
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual void Damage(void) = 0;

	static int Get_OrnamentNum(int OrnamType){ return m_OrnamentNum[OrnamType]; }
	static int Get_OrnamentIndex(int EnemyType) { return m_OrnamentNum[EnemyType] - 1; }
	int Get_Score(void) { return m_Score; }
	int Get_Type(void) { return m_Type; }
	void OrnamentDamage(void);
	static int Get_OrnamentMaxNum(void) { return m_ORNAMENT_MAX; }
	static C3DObj *Get_Ornament(int index);
	bool Get_DrawCheck(void) { return m_DrawCheck; }

	static C3DObj *Get_Map_Ornament(int Index);
protected:
	typedef struct {
		int CreateFrame;		//	�����t���[��
		int Type;				//	�I�u�W�F�N�g�^�C�v
		D3DXVECTOR3 InitPos;	//	�����ʒu
		int InitDirection;		//	��������
		bool CreateCheck;		//	�����t���O
		D3DXVECTOR3 scale;      //  �傫��
	}ORNAMENT_EMITTER;
	int m_OrnamentIndex;
	int m_Score;				//	�X�R�A
	int m_Direction;			//	����
	float m_DirectionAngle;		//	�����ύX�p�x
	static COrnament *m_pOrnament[ORNAMENT_MAX];
	static C3DObj *Get_AllOrnament(int index);
	bool m_DrawCheck;			//	�`��t���O

	void Ornament_Damage(float flyinghigh);
	void Ornament_Flying(float speed);
	void COrnament::Death(void);
private:
	int m_Type;			// ���
	static int m_OrnamentNum[TYPE_MAX];

	static ORNAMENT_EMITTER m_OrnamentEmitter[];
	static int m_ORNAMENT_MAX;

	bool m_OrnamentFlying = false;
	bool m_OrnamentFlyingDown = false;
	int m_FlyingCount = 0;
	D3DXVECTOR3 m_FlyingMove;
};

#endif // !1
#pragma once
