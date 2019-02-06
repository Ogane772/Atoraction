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
	void Summons_Attraction(void);	//	アトラクション召喚
	void Player_Initialize(void);	//	初期化
	void Player_Move(void);			//	移動処理
	void Angle_Change(int index);	//	方向変換
	void Player_Camera(void);		//	カメラ処理
	void Wall_Check(void);			//	カベ判定
	void Player_Damage(void);		//	プレイヤーダメージ
	void Cool_Time(void);			//	クールタイム処理
	void Mp_Add(void);				//	MP増加処理

	int m_Direction;				//	方向
	bool m_MoveCheck;				//	移動フラグ
	int m_SummonsNum;				//	召喚するアトラクションの番号
	
									
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
		DIRE_UP,		//　上
		DIRE_RIGHT,		//	右
		DIRE_DOWN,		//　下
		DIRE_LEFT,		//　左
		DIRE_UP_RIGHT,	//	右上
		DIRE_UP_LEFT,	//	左上
		DIRE_DOWN_RIGHT,//	右下
		DIRE_DOWN_LEFT,	//	左下

	};//　方向

	
	static CPlayer *m_pPlayer[PLAYER_MAX];
	static int m_PlayerNum;
	int m_PlayerIndex;
	static int m_KO_Count;
	
	bool g_CosterMode;
	int m_DrawCount;
	
	
};



#endif // !

