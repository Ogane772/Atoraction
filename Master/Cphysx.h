//////////////////////////////////////////////////
////
////	�t�B�W�b�N�X�N���X(�������Z)
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
		ANIME_MODEL_MAX,//�A�j�����f���ő吔
	};
	// void Update(void);
	// void Draw(void);

	static void CPhysX_Initialize(void);	//	������													
	static void Cleanup(void);   // �I������	
	static NxScene* Get_PhysX_Scene(void);	//	�V�[���擾

											// PhysX�̏I�������@Cleanup
	static void ExitNx(void);

	//	������͈�
	typedef struct SphereCollision_tag {
		D3DXVECTOR3 CenterPos;
		float radius;
	}SphereCollision;
	
	SphereCollision* Get_Collision(void) { return &m_SphereCollision; }

	static THING* GetAnimeModel(int index);//�擾���������f�����擾
	static void HitCheck(void);//�����蔻��m�F
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
	  //static NxActor *NxA_pPlayer,*NxA_pBoss;//�����G���W����K�p���郂���X�^�[��錾����
	  //NxActor *NxA_pPlayer, *NxA_pSmall;
	  //static NxActor* Get_PhysxData(int Index) { return m_ModelFileData[Index].Physx; }
	
	// ���[�U�[�f�[�^
	struct myData
	{
		char type;				// �A�N�^�[�̌^(B,S,C)
		int ID;					// ID
		NxVec3 dimension;		// �{�b�N�X�̐��@
		float radius;			// ���a
		float height;			// �J�v�Z���̓���

		NxVec3 position;		// �A�N�^�[�̏����ʒu
		NxMat33 rotation;		// �A�N�^�[�̏����p��

		NxVec3 meshScale;		// ���b�V���̊g��k��
		NxVec3 meshTranslation;	// ���b�V���̕��s�ړ�
		D3DXMATRIX meshRotation;	// ���b�V���̉�]
		bool hit;
	};

	// �A�N�^�[�Ŏg�p���郆�[�U�[�f�[�^�̍\����
	typedef struct _USERDATA
	{
		NxU32 ContactPairFlag;
	}USERDATA;

	//�����蔻��C�x���g�ʒm�N���X
	class ContactCallBack : public NxUserContactReport//�Ռ��ύX
	{
		void onContactNotify(NxContactPair& pair, NxU32 events);
	};

	//void UpdatePhysX(void); //���͏��� Update�֐��̍ŏ��ɏ���

	void SetupActors(void);		// ���f���̏����z�u

	void PhysXRender(D3DXMATRIX mtxWorld);// PhysX��DirectX�̕`��			

										  //	�����蔻��

										  // �{�b�N�X�^�̃��b�V���̐���
	NxActor* CreateMeshAsBox(NxVec3 position, NxMat33 rotation, NxVec3 scale, NxVec3 boundingbox, int ID);

	// �{�b�N�X�^�̃��b�V���̐���
	NxActor* CreateMeshAsBox(NxVec3 position, NxMat33 rotation, NxVec3 scale, NxVec3 boundingbox, int ID, bool type);
	//	NxActor* CreateMeshAsBox(myData mydata);
	// ���^�̃��b�V���̐���
	NxActor* CreateMeshAsSphere(NxVec3 position, float r, int ID);
	//�J�v�Z���^�̃��b�V���̐���
	NxActor* CreateMeshAsCapsule(NxVec3 position, NxMat33 rotation, NxVec3 scale, float r, float h, int ID);


	//�f�o�b�N�p�ϐ�
	bool physx = false;	//�t�B�W�b�N�X�t���O�@true�̎��t�B�W�b�N�X�����蔻��\��
	bool directx = true;	//directX�`��t���O�@false�̎����f���̔�\��					
	static bool hit;	//�����蔻��œ����������\������t���O

	//���f���`��
	void DrawDX2(D3DXMATRIX mtxWorld, NxActor* actor, int type);
	//�A�j���[�V�������f���`��
	void DrawDX_Anime(D3DXMATRIX mtxWorld, NxActor* actor, int type, THING* pThing);
	void DrawDX(D3DXMATRIX mtxWorld, NxActor* actor);

	void RenderThing(D3DXMATRIX mtxWorld, NxActor* actor, int type, THING2* pThing);
	// ���b�V���̕`��@RenderDirectX
	void DrawDirectXMesh(NxActor* actor);
	// PhysX�̕`��@PhysXRender
	void RenderPhysX(void);


	

	// ���_�̍\����
	struct CUSTOMVERTEX
	{
		FLOAT x, y, z;
	};
	#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)
	static LPDIRECT3DVERTEXBUFFER9 g_pVB;

	SphereCollision m_SphereCollision;
	//	������͈͕`��
	void Debug_Collision(SphereCollision sc, D3DXMATRIX mtx);

	
	THING2* GetNormalModel(int index);//�擾���������f�����擾
private:





	// PhysX�N���X
	static NxPhysicsSDK* gPhysicsSDK;
	static NxScene*	gScene;

	static LPD3DXMESH          g_pMesh[numMesh];
	static D3DMATERIAL9*       g_pMeshMaterials[numMesh];
	static LPDIRECT3DTEXTURE9* g_pMeshTextures[numMesh];
	static DWORD               g_dwNumMaterials[numMesh];


	//	����������

	static HRESULT InitGeometry(void);	// Geometry�̏������i���f���̓ǂݍ��݁j
	static bool InitNx(void);			// PhysX�̏�����
	static HRESULT LoadMesh(LPCSTR filename, int n); // ���b�V���̓ǂݍ��݁@InitGeometry
	static HRESULT InitThing(THING2 *pThing, LPSTR szXFileName);//���f���̓ǂݍ���


													 //	�����蔻��

													 // �{�b�N�X�̐���
	NxActor* CreateBox(myData mydata, const NxVec3* initialVelocity);

	// �{�b�N�X�̐���
	NxActor* CreateBox(myData mydata, const NxVec3* initialVelocity, bool type);

	// ���̐���
	NxActor* CreateSphere(myData mydata, const NxVec3* initialVelocity);
	// �J�v�Z���̐���
	NxActor* CreateCapsule(myData mydata, const NxVec3* initialVelocity);


	//	�`�揈��

	// �n�ʂ̃}�b�g�@RenderPhysX
	void DrawMat(void);
	// XYZ�̍��W���@RenderPhysX
	void DrawAxis(void);
	// �R���W������t���Ȃ����f���̕`��@RenderPhysX
	void DrawNoHitMesh(int n);
	// ���b�V���̕`��@RenderPhysX
	void DrawMeshDummy(int n, int m);

	// DirectX�̕`��@PhysXRender
	void RenderDirectX(D3DXMATRIX mtxWorld);

	// �}�g���b�N�X�̕ϊ��@RenderPhysX�@DrawDirectXMesh
	void ConvertMatrix(D3DXMATRIXA16 &matWorld, float *glMat);

	//�f�o�b�O�`��

	// �f�o�b�O�f�[�^�̃Z�b�g�i�f�o�b�N�R���W�����s��j
	static HRESULT CreateDebugBase(void);
	// �{�b�N�X�̕`��
	void DrawBox(NxActor* actor, D3DXMATRIXA16 &matWorld);
	// ���̕`��
	void DrawSphere(NxActor* actor, D3DXMATRIXA16 &matWorld);
	// �J�v�Z���̕`��
	void DrawCapsule(NxActor* actor, D3DXMATRIXA16 &matWorld);


	//	���f���f�[�^�̍\����
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