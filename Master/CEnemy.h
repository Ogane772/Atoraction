//////////////////////////////////////////////////
////
////	�G�l�~�[�N���X
////
//////////////////////////////////////////////////

#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "C3DObj.h"

#define ENEMY_MAX (100)

class CEnemy:virtual public C3DObj
{
public:
	// �G�̎��
	enum
	{
		TYPE_ALL = 0,

		TYPE_SMALL,		//	�U�R
		TYPE_MIDDLE,	//	���U�R
		TYPE_BIG,		//	����
		TYPE_SPECIAL,	//	����

		TYPE_MAX
	};

	CEnemy();
	CEnemy(int nType);
	~CEnemy();

	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual void Damage(void) = 0;

	void Enemy_Finalize(int Index);

	
	static void Create(void);
	static int Get_EnemyNum(int EnemyType) { return m_EnemyNum[EnemyType]; }
	static int Get_EnemyIndex(int EnemyType) { return m_EnemyNum[EnemyType] - 1; }
	int Get_Score(void) { return m_Score; }
	int Get_Type(void) { return m_Type; }
	void EnemyDamage(void);
	static int Get_EnemyMaxNum(void) { return m_ENEMY_MAX; }
	static C3DObj *Get_Enemy(int type);
	bool Get_DrawCheck(void) { return m_DrawCheck; }

	static C3DObj *Get_Map_Enemy(int Index);
protected:

	enum
	{
		DIRE_NORTH,		//�@��
		DIRE_NORTHEAST,	//�@�E��
		DIRE_EAST,		//	�E
		DIRE_SOUTHEAST,	//�@�E��
		DIRE_SOUTH,		//�@��
		DIRE_SOUTHWEST,	//�@����
		DIRE_WEST,		//�@��
		DIRE_NORTHWEST,	//�@����
	};

	typedef struct {
		D3DXVECTOR3 Move;	//	�i�ޕ���
		float Angle;		//	���f���p�x
	}ENEMY_MOVE;

	static ENEMY_MOVE m_EnemyMove[8];

	
	int m_Score;				//	�X�R�A
	int m_Direction;			//	����
	float m_DirectionAngle;		//	�����ύX�p�x
	bool m_MoveCheck;			//	�ړ��t���O
	bool m_DrawCheck;			//	�`��t���O

	
	static C3DObj *Get_AllEnemy(void);
	typedef struct{
		int CreateFrame;		//	�����t���[��
		int Type;				//	�G�l�~�[�^�C�v
		D3DXVECTOR3 InitPos;	//	�����ʒu
		int InitDirection;		//	��������
		bool CreateCheck;		//	�����t���O
	}ENEMY_EMITTER;

	int m_EnemyIndex;
	void EnemyMove(int direction, float speed);		//	�ړ�����
	void EnemyAngleChange(int direction);			//	�����ύX����

	bool PlayerCheck(void);		//	�v���C���[���߂��ɂ��邩
	void Chase_Player(void);	//	�v���C���[�Ɍ���������
	bool Draw_Check(void);
	void Comeback_Move(float speed);
private:

	int m_Type;			// ���
	static int m_EnemyNum[TYPE_MAX];

	static ENEMY_EMITTER m_EnemyEmitter[];
	static int m_ENEMY_MAX;
};

#endif // !1