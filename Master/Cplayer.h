#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "CCharacter.h"
#include <d3dx9.h>

#define PLAYER_MAX (2)
#define MP_MAX (30)
#define HP_MAX (50)

class CPlayer:public CCharacter
{

public:
	CPlayer();
	~CPlayer();

	void Update(void);
	void Draw(void);
	void Finalize(void);	//	èIóπèàóù
	void Model_Angle(bool Angle_Flg);

	static CPlayer *PlayerCreate(void);
	NxActor *Get_Actor(void) { return NxA_pPlayer; }
	//int Get_Mp(void) { return m_Mp; }
	int Get_MpStock(void) { return m_MpStock; }
	
	static CPlayer *Get_Player(int IndexPlayer) { return m_pPlayer[IndexPlayer]; }
	D3DXMATRIX Get_mtxkeep(void) { return m_mtxKeepTranslation; }
	bool *Get_Coaster(void) { return &g_CosterMode; }

	D3DXVECTOR3 Get_PlayerFront(void) { return player_front; }

	//äœóóé‘óp
	float Get_Player_Angle(void) { return player_kakudo; }

	D3DXMATRIX Get_mtx(void) { return m_mtxTranslation; }

protected:
	//int m_Hp;
	//int m_Mp;
	int m_MpStock;

	D3DXMATRIX m_mtxKeepTranslation;	//	à⁄ìÆï€éùçsóÒ
	
private:

	void Player_Initialize(void);	//	èâä˙âª
	//myData m_PlayerData;
	static CPlayer *m_pPlayer[PLAYER_MAX];
	static int m_PlayerNum;
	int m_PlayerIndex;
	NxActor *NxA_pPlayer;
	bool g_CosterMode;
	D3DXVECTOR3 player_front;
	float player_kakudo;
	D3DXVECTOR3 player_at;
	D3DXVECTOR3 wheel_at;
	D3DXVECTOR3 player_position;
	D3DXVECTOR3 player_right;
	D3DXVECTOR3 player_up;
	float player_angleX;
	float player_angleY;
	float player_angleZ;
};



#endif // !

