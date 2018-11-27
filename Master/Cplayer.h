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
	void Finalize(void);	//	I—¹ˆ—

	static CPlayer *PlayerCreate(void);
	NxActor *Get_Actor(void) { return NxA_pPlayer; }
	//int Get_Mp(void) { return m_Mp; }
	int Get_MpStock(void) { return m_MpStock; }
	
	static CPlayer *Get_Player(int IndexPlayer) { return m_pPlayer[IndexPlayer]; }
	D3DXMATRIX Get_mtxkeep(void) { return m_mtxKeepTranslation; }

protected:
	//int m_Hp;
	//int m_Mp;
	int m_MpStock;

	D3DXMATRIX m_mtxKeepTranslation;	//	ˆÚ“®•Ûs—ñ
	
private:

	void Player_Initialize(void);	//	‰Šú‰»
	//myData m_PlayerData;
	static CPlayer *m_pPlayer[PLAYER_MAX];
	static int m_PlayerNum;
	int m_PlayerIndex;
	NxActor *NxA_pPlayer;
};



#endif // !

