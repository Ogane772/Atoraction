//////////////////////////////////////////////////
////
////	フィジックスクラス(物理演算)
////
//////////////////////////////////////////////////

#ifndef PHYSX_H_
#define PHYSX_H_

#define NOMINMAX
#include <windows.h>
#undef min
#undef max

#include "CGameObj.h"
#include <d3dx9.h>
#include "NxPhysics.h"
#include "CSkinAnimation.h"
#include "BSphere.h"
#define numMesh 20

class CPhysx : virtual public CGameObj
{
public:
	CPhysx();
	~CPhysx();
	enum ANIME_MODEL
	{
		MODELL_ANIME_SMALL,
		ANIME_MODEL_MAX,//アニメモデル最大数
	};
	// void Update(void);
	// void Draw(void);

	static void CPhysX_Initialize(void);	//	初期化													
	static void Cleanup(void);   // 終了処理	
	static NxScene* Get_PhysX_Scene(void);	//	シーン取得

											// PhysXの終了処理　Cleanup
	static void ExitNx(void);

	//	当たり範囲
	typedef struct SphereCollision_tag {
		D3DXVECTOR3 CenterPos;
		float radius;
	}SphereCollision;
	
	SphereCollision* Get_Collision(void) { return &m_SphereCollision; }

	static THING* GetAnimeModel(int index);//取得したいモデル情報取得
	static void HitCheck(void);//当たり判定確認
protected:

	enum NORMAL_MODEL{
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
	};

	//ModelFileData
	  //static NxActor *NxA_pPlayer,*NxA_pBoss;//物理エンジンを適用するモンスターを宣言する
	  //NxActor *NxA_pPlayer, *NxA_pSmall;
	  //static NxActor* Get_PhysxData(int Index) { return m_ModelFileData[Index].Physx; }
	
	// ユーザーデータ
	struct myData
	{
		char type;				// アクターの型(B,S,C)
		int ID;					// ID
		NxVec3 dimension;		// ボックスの寸法
		float radius;			// 半径
		float height;			// カプセルの胴長

		NxVec3 position;		// アクターの初期位置
		NxMat33 rotation;		// アクターの初期姿勢

		NxVec3 meshScale;		// メッシュの拡大縮小
		NxVec3 meshTranslation;	// メッシュの平行移動
		D3DXMATRIX meshRotation;	// メッシュの回転
		bool hit;
	};

	// アクターで使用するユーザーデータの構造体
	typedef struct _USERDATA
	{
		NxU32 ContactPairFlag;
	}USERDATA;

	//当たり判定イベント通知クラス
	class ContactCallBack : public NxUserContactReport//衝撃変更
	{
		void onContactNotify(NxContactPair& pair, NxU32 events);
	};

	//void UpdatePhysX(void); //入力処理 Update関数の最初に書く

	void SetupActors(void);		// モデルの初期配置

	void PhysXRender(D3DXMATRIX mtxWorld);// PhysXとDirectXの描画			

										  //	当たり判定

										  // ボックス型のメッシュの生成
	NxActor* CreateMeshAsBox(NxVec3 position, NxMat33 rotation, NxVec3 scale, NxVec3 boundingbox, int ID);

	// ボックス型のメッシュの生成
	NxActor* CreateMeshAsBox(NxVec3 position, NxMat33 rotation, NxVec3 scale, NxVec3 boundingbox, int ID, bool type);
	//	NxActor* CreateMeshAsBox(myData mydata);
	// 球型のメッシュの生成
	NxActor* CreateMeshAsSphere(NxVec3 position, float r, int ID);
	//カプセル型のメッシュの生成
	NxActor* CreateMeshAsCapsule(NxVec3 position, NxMat33 rotation, NxVec3 scale, float r, float h, int ID);


	//デバック用変数
	bool physx = false;	//フィジックスフラグ　trueの時フィジックス当たり判定表示
	bool directx = true;	//directX描画フラグ　falseの時モデルの非表示					
	static bool hit;	//当たり判定で当たったか表示するフラグ

	//モデル描画
	void DrawDX2(D3DXMATRIX mtxWorld, NxActor* actor, int type);
	//アニメーションモデル描画
	void DrawDX_Anime(D3DXMATRIX mtxWorld, NxActor* actor, int type, THING* pThing);
	void DrawDX(D3DXMATRIX mtxWorld, NxActor* actor);

	void RenderThing(D3DXMATRIX mtxWorld, NxActor* actor, int type, THING2* pThing);
	// メッシュの描画　RenderDirectX
	void DrawDirectXMesh(NxActor* actor);
	// PhysXの描画　PhysXRender
	void RenderPhysX(void);


	

	// 頂点の構造体
	struct CUSTOMVERTEX
	{
		FLOAT x, y, z;
	};
	#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)
	static LPDIRECT3DVERTEXBUFFER9 g_pVB;

	SphereCollision m_SphereCollision;
	//	当たり範囲描画
	void Debug_Collision(SphereCollision sc, D3DXMATRIX mtx);

	
	THING2* GetNormalModel(int index);//取得したいモデル情報取得
private:





	// PhysXクラス
	static NxPhysicsSDK* gPhysicsSDK;
	static NxScene*	gScene;

	static LPD3DXMESH          g_pMesh[numMesh];
	static D3DMATERIAL9*       g_pMeshMaterials[numMesh];
	static LPDIRECT3DTEXTURE9* g_pMeshTextures[numMesh];
	static DWORD               g_dwNumMaterials[numMesh];


	//	初期化処理

	static HRESULT InitGeometry(void);	// Geometryの初期化（モデルの読み込み）
	static bool InitNx(void);			// PhysXの初期化
	static HRESULT LoadMesh(LPCSTR filename, int n); // メッシュの読み込み　InitGeometry
	static HRESULT InitThing(THING2 *pThing, LPSTR szXFileName);//モデルの読み込み


													 //	当たり判定

													 // ボックスの生成
	NxActor* CreateBox(myData mydata, const NxVec3* initialVelocity);

	// ボックスの生成
	NxActor* CreateBox(myData mydata, const NxVec3* initialVelocity, bool type);

	// 球の生成
	NxActor* CreateSphere(myData mydata, const NxVec3* initialVelocity);
	// カプセルの生成
	NxActor* CreateCapsule(myData mydata, const NxVec3* initialVelocity);


	//	描画処理

	// 地面のマット　RenderPhysX
	void DrawMat(void);
	// XYZの座標軸　RenderPhysX
	void DrawAxis(void);
	// コリジョンを付けないモデルの描画　RenderPhysX
	void DrawNoHitMesh(int n);
	// メッシュの描画　RenderPhysX
	void DrawMeshDummy(int n, int m);

	// DirectXの描画　PhysXRender
	void RenderDirectX(D3DXMATRIX mtxWorld);

	// マトリックスの変換　RenderPhysX　DrawDirectXMesh
	void ConvertMatrix(D3DXMATRIXA16 &matWorld, float *glMat);

	//デバッグ描画

	// デバッグデータのセット（デバックコリジョン行列）
	static HRESULT CreateDebugBase(void);
	// ボックスの描画
	void DrawBox(NxActor* actor, D3DXMATRIXA16 &matWorld);
	// 球の描画
	void DrawSphere(NxActor* actor, D3DXMATRIXA16 &matWorld);
	// カプセルの描画
	void DrawCapsule(NxActor* actor, D3DXMATRIXA16 &matWorld);


	//	モデルデータの構造体
	typedef struct
	{
		char filename[256];
		//NxActor* Physx;

	}ModelFileData;


	static ModelFileData m_NormalModelFileData[];
	static ModelFileData m_AnimeModelFileData[];
	static int m_NORMALMODELFAIL_MAX;
	static int m_ANIMEMODELFAIL_MAX;
};



#endif //PHYSX_H_