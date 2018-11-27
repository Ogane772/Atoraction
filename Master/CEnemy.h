//////////////////////////////////////////////////
////
////	�G�l�~�[�N���X
////
//////////////////////////////////////////////////

#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "CCharacter.h"

#define ENEMY_MAX (100)

class CEnemy:public CCharacter
{
public:
	// �G�̎��
	enum
	{
		TYPE_ALL = 0,

		TYPE_SMALL,		//	�U�R
		TYPE_MIDDLE,		//	���U�R
		TYPE_BIG,			//	����
		TYPE_SPECIAL,		//	����

		TYPE_MAX
	};

	CEnemy();
	CEnemy(int nType);
	~CEnemy();

	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	void Enemy_Finalize(int Index);

	static CEnemy *Create(int Index);
	static CEnemy *Get_Enemy(int IdxEnemy) { return m_pEnemy[IdxEnemy]; }
	static int Get_EnemyNum(int EnemyType) { return m_EnemyNum[EnemyType]; }
	static int Get_EnemyIndex(int EnemyType) { return m_EnemyNum[EnemyType] - 1; }
	int Get_Score(void) { return m_Score; }
	int Get_Type(void) { return m_Type; }
	void EnemyDamage(void);
	
	static int Get_EnemyMaxNum(void) { return m_ENEMY_MAX; }
protected:

	enum
	{
		NORTH,		//�@��
		NORTHEAST,	//�@�E��
		EAST,		//	�E
		SOUTHEAST,	//�@�E��
		SOUTH,		//�@��
		SOUTHWEST,	//�@����
		WEST,		//�@��
		NORTHWEST,	//�@����
	};

	typedef struct {
		D3DXVECTOR3 Move;	//	�i�ޕ���
		float Angle;		//	���f���p�x
	}ENEMY_MOVE;

	static ENEMY_MOVE m_EnemyMove[8];

	int m_Attack;	//	�U��
	int m_Score;	//	�X�R�A
	int m_Direction;//	����
	float m_DirectionAngle;	//	�����ύX�p�x
	bool m_MoveCheck;	//	�ړ��t���O
	bool m_DrawCheck;	//	�`��t���O
	//bool m_Enable;		//	
	
	typedef struct{
		int CreateFrame;		//	�����t���[��
		int Type;				//	�G�l�~�[�^�C�v
		D3DXVECTOR3 InitPos;	//	�����ʒu
		int InitDirection;		//	��������
		bool CreateCheck;		//	�����t���O
	}ENEMY_EMITTER;

	int m_EnemyIndex;
	void EnemyMove(NxActor *actor, int direction, float speed);
	void EnemyAngleChange(NxActor *actor, int direction);
private:

	int m_Type;			// ���
	static CEnemy *m_pEnemy[];
	static int m_EnemyNum[TYPE_MAX];

	static ENEMY_EMITTER m_EnemyEmitter[];
	static int m_ENEMY_MAX;
};

#endif // !1