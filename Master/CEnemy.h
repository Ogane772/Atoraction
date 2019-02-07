//////////////////////////////////////////////////
////
////	エネミークラス
////
//////////////////////////////////////////////////

#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "C3DObj.h"

#define ENEMY_MAX (100)

class CEnemy:virtual public C3DObj
{
public:
	// 敵の種類
	enum
	{
		TYPE_ALL = 0,

		TYPE_SMALL,		//	ザコ
		TYPE_MIDDLE,	//	中ザコ
		TYPE_BIG,		//	巨大
		TYPE_SPECIAL,	//	特殊

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
		DIRE_NORTH,		//　上
		DIRE_NORTHEAST,	//　右上
		DIRE_EAST,		//	右
		DIRE_SOUTHEAST,	//　右下
		DIRE_SOUTH,		//　下
		DIRE_SOUTHWEST,	//　左下
		DIRE_WEST,		//　左
		DIRE_NORTHWEST,	//　左上
	};

	typedef struct {
		D3DXVECTOR3 Move;	//	進む方向
		float Angle;		//	モデル角度
	}ENEMY_MOVE;

	static ENEMY_MOVE m_EnemyMove[8];

	
	int m_Score;				//	スコア
	int m_Direction;			//	向き
	float m_DirectionAngle;		//	向き変更角度
	bool m_MoveCheck;			//	移動フラグ
	bool m_DrawCheck;			//	描画フラグ

	
	static C3DObj *Get_AllEnemy(void);
	typedef struct{
		int CreateFrame;		//	生成フレーム
		int Type;				//	エネミータイプ
		D3DXVECTOR3 InitPos;	//	初期位置
		int InitDirection;		//	初期向き
		bool CreateCheck;		//	生成フラグ
	}ENEMY_EMITTER;

	int m_EnemyIndex;
	void EnemyMove(int direction, float speed);		//	移動処理
	void EnemyAngleChange(int direction);			//	向き変更処理

	bool PlayerCheck(void);		//	プレイヤーが近くにいるか
	void Chase_Player(void);	//	プレイヤーに向かう処理
	bool Draw_Check(void);
	void Comeback_Move(float speed);
private:

	int m_Type;			// 種類
	static int m_EnemyNum[TYPE_MAX];

	static ENEMY_EMITTER m_EnemyEmitter[];
	static int m_ENEMY_MAX;
};

#endif // !1