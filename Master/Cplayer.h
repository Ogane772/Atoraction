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

	static CPlayer *PlayerCreate(void);
	NxActor *Get_Actor(void) { return NxA_pPlayer; }
	//int Get_Mp(void) { return m_Mp; }
	
	
	static CPlayer *Get_Player(int IndexPlayer) { return m_pPlayer[IndexPlayer]; }
	D3DXMATRIX Get_mtxkeep(void) { return m_mtxKeepTranslation; }
	static int Get_KoCount(void) { return m_KO_Count; }
	static void Add_KoCount(void) { m_KO_Count++; }
	
	//static bool Check_delete(void) { return m_delete; }
	static bool m_delete;
	static C3DObj *Get_Player(void);
	//bool *Get_Coaster(void) { return &g_CosterMode; }
	bool Get_DrawCheck(void) { return false; }
protected:
	//int m_Hp;
	//int m_Mp;
	
	
	D3DXMATRIX m_mtxKeepTranslation;	//	à⁄ìÆï€éùçsóÒ
	
private:
	void  AngleChange(bool Angle_Flg);
	void Player_Initialize(void);	//	èâä˙âª
	//myData m_PlayerData;
	static CPlayer *m_pPlayer[PLAYER_MAX];
	static int m_PlayerNum;
	int m_PlayerIndex;
	NxActor *NxA_pPlayer;
	static int m_KO_Count;
	
	bool g_CosterMode;
};



#endif // !

