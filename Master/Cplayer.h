#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "C3DObj.h"
#include <d3dx9.h>

#define PLAYER_MAX (2)
#define MP_MAX (30)
#define HP_MAX (50)

class CPlayer:public C3DObj
{

public:
	CPlayer();
	~CPlayer();

	void Update(void);
	void Draw(void);
	void Finalize(void);	//	�I������

	static CPlayer *PlayerCreate(void);	
	static CPlayer *Get_Player(int IndexPlayer) { return m_pPlayer[IndexPlayer]; }
	D3DXMATRIX Get_mtxkeep(void) { return m_mtxKeepTranslation; }
	static int Get_KoCount(void) { return m_KO_Count; }
	static void Add_KoCount(void) { m_KO_Count++; }
	static bool m_delete;
	static C3DObj *Get_Player(void);
	bool Get_DrawCheck(void) { return m_DrawCheck; }
	
protected:
	
	D3DXMATRIX m_mtxKeepTranslation;	//	�ړ��ێ��s��
	bool m_DrawCheck;			//	�`��t���O
private:
	void Summons_Attraction(void);	//	�A�g���N�V��������
	void Player_Initialize(void);	//	������
	void Player_Move(void);			//	�ړ�����
	void Angle_Change(int index);	//	�����ϊ�
	void Player_Camera(void);		//	�J��������
	void Wall_Check(void);			//	�J�x����
	void Player_Damage(void);		//	�v���C���[�_���[�W
	void Cool_Time(void);			//	�N�[���^�C������
	void Mp_Add(void);				//	MP��������

	int m_Direction;				//	����
	bool m_MoveCheck;				//	�ړ��t���O
	int m_SummonsNum;				//	��������A�g���N�V�����̔ԍ�
	
									
	//  0 coffee
	//  1 fall
	//  2 wheel
	//  3 coaster
	//  4 popcorn
	int m_CoolTime[5] = {0};

	enum
	{
		SUMMONS_COFFEE,
		SUMMONS_FALL,
		SUMMONS_WHEEL,
		SUMMONS_COASTER,
		SUMMONS_POPCORN,

		SUMMONS_MAX,
	};


	enum
	{
		DIRE_UP,		//�@��
		DIRE_RIGHT,		//	�E
		DIRE_DOWN,		//�@��
		DIRE_LEFT,		//�@��
		DIRE_UP_RIGHT,	//	�E��
		DIRE_UP_LEFT,	//	����
		DIRE_DOWN_RIGHT,//	�E��
		DIRE_DOWN_LEFT,	//	����

	};//�@����

	
	static CPlayer *m_pPlayer[PLAYER_MAX];
	static int m_PlayerNum;
	int m_PlayerIndex;
	static int m_KO_Count;
	
	bool g_CosterMode;
	int m_DrawCount;
	
	
};



#endif // !

