//////////////////////////////////////////////////
////
////	3Dオブジェクトクラス
////
//////////////////////////////////////////////////

#ifndef _3DOBJ_H_
#define _3DOBJ_H_

#include "CGameObj.h"
#include <d3dx9.h>
#include "CSkinAnimation.h"
#include "BSphere.h"

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
		TYPE_POPCORN,	// ジェットコースター
		TYPE_ORNAMENT,	// 障害物
		TYPE_etc,		// その他

		TYPE_MAX

	} OBJTYPE;

	typedef enum {
		MODELL_PLAYER,
		MODELL_CUP_TABLE,
		MODELL_ENBAN,
		MODELL_HASIRA,
		MODELL_WHEEL,
		MODELL_COASTER,
		MODELL_CUP_BLUE,
		MODELL_CUP_YELLOW,
		MODELL_CUP_GREEN,
		MODELL_POPCORN,
	}ModelFileData;
	enum ANIME_MODEL
	{
		MODELL_ANIME_SMALL,
		ANIME_MODEL_MAX,//アニメモデル最大数
	}AnimeModelFileData;;
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

	int Get_Angle(void) { return (int)m_Angle; }			//	角度取得
	D3DXVECTOR3 Get_Front(void) { return m_front; }	//	前ベクトル取得
	
	int Get_Hp(void) { return m_Hp; }				//	HP取得
	int Get_Mp(void) { return m_Mp; }				//	MP取得
	int Get_MpStock(void) { return m_MpStock; }		//	MPストック取得
	
	//	モデル読み込み
	static HRESULT InitModelLoad();
	//モデル情報取得
	static THING* C3DObj::GetAnimeModel(int index);
	static THING_NORMAL* C3DObj::GetNormalModel(int index);
	//	終了処理
	static void Model_Finalize(void);
	static void Model_Finalize(int index);
	//当たり判定
	static void HitCheck(void);

	virtual bool Get_DrawCheck(void) = 0;
protected:
	THING *Thing_Anime_model;//アニメモデル情報
	THING_NORMAL *Thing_Normal_model;//通常モデル情報
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

	// 描画処理
	void DrawDX_Anime(D3DXMATRIX mtxWorld, int type, THING* pThing);
	void C3DObj::DrawDX_Normal(D3DXMATRIX mtxWorld, int type, THING_NORMAL* pThing);


private:
	
	static HRESULT InitThing(THING_NORMAL *pThing, LPSTR szXFileName);//ノーマルモデルの読み込み
	int m_3DObjIndex;		//	3Dオブジェクトインデックス
	int m_3DObjType;		//	3Dオブジェクトタイプ
	static int m_3DObjNum;	//	ゲームオブジェクト総数
	static C3DObj *p3DObj[MAX_GAMEOBJ];
	//衝突検出 ノーマルモデル対ノーマルモデル
	static bool Collision_NomalVSNormal(THING_NORMAL*, THING_NORMAL*);
	//衝突検出 アニメモデル対ノーマルモデル
	static bool Collision_AnimeVSNormal(THING*, THING_NORMAL*);
	//衝突検出 アニメモデル対アニメモデル
	static bool Collision_AnimeVSAnime(THING*, THING*);
	//	モデルデータの構造体
	typedef struct
	{
		char filename[256];

	}MaterialFileData;
	//	モデルデータの構造体
	typedef struct
	{
		char filename[256];

	}MaterialFileData2;
	//	使いたいモデルの数だけ書く
	static MaterialFileData NORMAL_MODEL_FILES[];
	static MaterialFileData2 ANIME_MODEL_FILES[];

	static LPD3DXMESH m_pD3DXMesh[];			//	メッシュを受け取る変数
	static DWORD m_dwNumMaterials[];			//	マテリアルの総数	描画する回数
	static LPD3DXBUFFER m_pD3DXMtrBuffer[];		//	マテリアル情報を受け取る変数
	static LPDIRECT3DTEXTURE9 *m_pTexures[];	//　
	static D3DMATERIAL9 *m_pd3dMaterials[];		//　


	static int MODEL_FILES_MAX;	//	テクスチャ構造体総数
	static int ANIME_MODEL_FILES_MAX;	//	テクスチャ構造体総数
};

#endif // !1
