//////////////////////////////////////////////////
////
////	3Dオブジェクトクラス
////
//////////////////////////////////////////////////

#ifndef _3DOBJ_H_
#define _3DOBJ_H_

#include "CGameObj.h"
#include <d3dx9.h>

class C3DObj :virtual public CGameObj
{
public:
	C3DObj();
	~C3DObj();

	C3DObj(int type);
	typedef enum
	{
		TYPE_PLAYER,	// プレイヤー
		TYPE_ENEMY,		// エネミー
		TYPE_ATTRACTION,// アトラクション
		TYPE_COASTER,	// ジェットコースター
		TYPE_ORNAMENT,	// 障害物
		TYPE_etc,		// その他

		TYPE_MAX

	} OBJTYPE;

	virtual void Update(void) = 0;	//	更新
	virtual void Draw(void) = 0;	//	描画

	D3DXMATRIX Get_mtxWorld(void) { return m_mtxWorld; }				//	ワールド変換用行列取得
	D3DXMATRIX Get_mtxTranslation(void) { return m_mtxTranslation; }	//	移動用行列取得

	static void UpdateAll();	// 全オブジェクト更新
	static void DrawAll();		// 全オブジェクト描画
	static void DeleteAll();	// 全オブジェクト削除
	void C3DObj_delete(void);	// オブジェクト削除	
	static C3DObj *Get(int nIdx);				// インスタンス取得
	int Get_3DObjIndex() { return m_3DObjIndex; }	// ワークインデックス取得
	int Get_3DObjType() { return m_3DObjType; }		// 種類取得

	int Get_Angle(void) { return m_Angle; }			//	角度取得
	D3DXVECTOR3 Get_Front(void) { return m_front; }	//	前ベクトル取得
	
	int Get_Hp(void) { return m_Hp; }				//	HP取得
	int Get_Mp(void) { return m_Mp; }				//	MP取得
	int Get_MpStock(void) { return m_MpStock; }		//	MPストック取得
	virtual bool Get_DrawCheck(void) = 0;
protected:
	D3DXMATRIX m_mtxWorld;			//	ワールド変換用行列
	D3DXMATRIX m_mtxTranslation;	//	移動行列
	D3DXMATRIX m_mtxRotation;		//	移動行列
	D3DXMATRIX m_mtxScaling;		//	移動行列

	
	float m_Angle;			//	角度
	D3DXVECTOR3 m_front;	//	前ベクトル
	D3DXVECTOR3 m_right;	//	右ベクトル
	D3DXVECTOR3 m_up;		//	上ベクトル
	int m_MpStock;			//	MPストック
	int m_Hp;				//	HP
	int m_Mp;				//	MP
	int m_Attack;			//	攻撃
private:
	
	
	int m_3DObjIndex;		//	3Dオブジェクトインデックス
	int m_3DObjType;		//	3Dオブジェクトタイプ
	static int m_3DObjNum;	//	ゲームオブジェクト総数
	static C3DObj *p3DObj[MAX_GAMEOBJ];
};

#endif // !1
