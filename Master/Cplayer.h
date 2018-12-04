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
	int Get_MpStock(void) { return m_MpStock; }
	
	static CPlayer *Get_Player(int IndexPlayer) { return m_pPlayer[IndexPlayer]; }
	D3DXMATRIX Get_mtxkeep(void) { return m_mtxKeepTranslation; }
	static int Get_KoCount(void) { return m_KO_Count; }
	static void Add_KoCount(void) { m_KO_Count++; }
	int Get_Angle(void) { return m_Angle; }
	D3DXVECTOR3 Get_Front(void) { return m_front; }
	//static bool Check_delete(void) { return m_delete; }
	static bool m_delete;
	
	bool *Get_Coaster(void) { return &g_CosterMode; }

	D3DXMATRIX Get_Player_position(void) { return m_mtxTranslation; }
protected:
	//int m_Hp;
	//int m_Mp;
	int m_MpStock;
	
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
	float m_Angle;
	D3DXVECTOR3 m_front;
	D3DXVECTOR3 m_right;
	D3DXVECTOR3 m_up;
	bool g_CosterMode;
};



#endif // !

