//////////////////////////////////////////////////
////
////	エネミークラス
////
//////////////////////////////////////////////////

#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "CCharacter.h"

#define ENEMY_MAX (100)

class CEnemy:public CCharacter
{
public:
	// 敵の種類
	enum
	{
		TYPE_ALL = 0,

		TYPE_SMALL,		//	ザコ
		TYPE_MIDDLE,		//	中ザコ
		TYPE_BIG,			//	巨大
		TYPE_SPECIAL,		//	特殊

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
		NORTH,		//　上
		NORTHEAST,	//　右上
		EAST,		//	右
		SOUTHEAST,	//　右下
		SOUTH,		//　下
		SOUTHWEST,	//　左下
		WEST,		//　左
		NORTHWEST,	//　左上
	};

	typedef struct {
		D3DXVECTOR3 Move;	//	進む方向
		float Angle;		//	モデル角度
	}ENEMY_MOVE;

	static ENEMY_MOVE m_EnemyMove[8];

	int m_Attack;	//	攻撃
	int m_Score;	//	スコア
	int m_Direction;//	向き
	float m_DirectionAngle;	//	向き変更角度
	bool m_MoveCheck;	//	移動フラグ
	bool m_DrawCheck;	//	描画フラグ
	//bool m_Enable;		//	
	
	typedef struct{
		int CreateFrame;		//	生成フレーム
		int Type;				//	エネミータイプ
		D3DXVECTOR3 InitPos;	//	初期位置
		int InitDirection;		//	初期向き
		bool CreateCheck;		//	生成フラグ
	}ENEMY_EMITTER;

	int m_EnemyIndex;
	void EnemyMove(NxActor *actor, int direction, float speed);
	void EnemyAngleChange(NxActor *actor, int direction);
private:

	int m_Type;			// 種類
	static CEnemy *m_pEnemy[];
	static int m_EnemyNum[TYPE_MAX];

	static ENEMY_EMITTER m_EnemyEmitter[];
	static int m_ENEMY_MAX;
};

#endif // !1