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
	void Finalize(void);	//	終了処理

	static CPlayer *PlayerCreate(void);	
	static CPlayer *Get_Player(int IndexPlayer) { return m_pPlayer[IndexPlayer]; }
	D3DXMATRIX Get_mtxkeep(void) { return m_mtxKeepTranslation; }
	static int Get_KoCount(void) { return m_KO_Count; }
	static void Add_KoCount(void) { m_KO_Count++; }
	static bool m_delete;
	static C3DObj *Get_Player(void);
	bool Get_DrawCheck(void) { return m_DrawCheck; }
	
protected:
	
	D3DXMATRIX m_mtxKeepTranslation;	//	移動保持行列
	bool m_DrawCheck;			//	描画フラグ
private:
	void  AngleChange(bool Angle_Flg);
	void Player_Initialize(void);	//	初期化
	static CPlayer *m_pPlayer[PLAYER_MAX];
	static int m_PlayerNum;
	int m_PlayerIndex;
	static int m_KO_Count;
	
	bool g_CosterMode;
	int m_DrawCount;
	
	void PlayerDamage(void);
};



#endif // !

