//////////////////////////////////////////////////
////
////	3D�I�u�W�F�N�g�N���X
////
//////////////////////////////////////////////////

#ifndef _3DOBJ_H_
#define _3DOBJ_H_
#include <crtdbg.h>

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
		A_BUTTON,
		B_BUTTON,
		X_BUTTON,
		Y_BUTTON,
		L_BUTTON,
		R_BUTTON,
		BACK_BUTTON,
		START_BUTTON,
	} CONTROLLER;
	typedef enum
	{
		TYPE_PLAYER,	// �v���C���[
		TYPE_ENEMY,		// �G�l�~�[
		TYPE_ATTRACTION,// �A�g���N�V����
		TYPE_COASTER,	// �W�F�b�g�R�[�X�^�[
		TYPE_POPCORN,	// �|�b�v�R�[��
		TYPE_STADBY,    // ���ݒ�
		TYPE_ORNAMENT,	// ��Q��
		TYPE_etc,		// ���̑�

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
		MODELL_STANDBY,
		MODELL_LAMP,
		MODELL_GOMIBAKO,
		MODELL_BENCH,
		MODELL_HUNSUI,
		MODELL_KANRANSYA_DODAI,
		MODELL_HUSEN,
		MODELL_MERI_DODAI,
		MODELL_MERI_UMA,
		MODELL_KANRANSYA,
		MODELL_GASUBONBE,
		MODELL_POTETO,
	}ModelFileData;
	enum ANIME_MODEL
	{
		MODELL_ANIME_PLAYER,
		MODELL_ANIME_SMALL,
		MODELL_ANIME_MIDDLE,
		MODELL_ANIME_SPECIAL,
		MODELL_ANIME_BIG,
		ANIME_MODEL_MAX,//�A�j�����f���ő吔
	}AnimeModelFileData;;

	virtual void Finalize(void) ;
	virtual void Update(void) = 0;	//	�X�V
	virtual void Draw(void) = 0;	//	�`��

	

	D3DXMATRIX Get_mtxWorld(void) { return m_mtxWorld; }				//	���[���h�ϊ��p�s��擾
	D3DXMATRIX Get_mtxTranslation(void) { return m_mtxTranslation; }	//	�ړ��p�s��擾

	static void FinalizeAll();	// �S�I�u�W�F�N�g������
	static void UpdateAll();	// �S�I�u�W�F�N�g�X�V
	static void DrawAll();		// �S�I�u�W�F�N�g�`��
	static void DeleteAll();	// �S�I�u�W�F�N�g�폜
	void C3DObj_delete(void);	// �I�u�W�F�N�g�폜	
	static C3DObj *Get(int nIdx);					// �C���X�^���X�擾
	int Get_3DObjIndex() { return m_3DObjIndex; }	// ���[�N�C���f�b�N�X�擾
	int Get_3DObjType() { return m_3DObjType; }		// ��ގ擾
	int Get_Angle(void) { return (int)m_Angle; }	//	�p�x�擾	
	int Get_Hp(void) { return m_Hp; }				//	HP�擾
	int Get_Mp(void) { return m_Mp; }				//	MP�擾
	int Get_Attck(void) { return m_Attack; }		//	MP�擾
	int Get_MpStock(void) { return m_MpStock; }		//	MP�X�g�b�N�擾
	int Get_SummonsNum(void) { return m_SummonsNum; } // �I�𒆃A�g���N�V�����擾 
	int Get_CoolTime(int summonstype) { return m_CoolTime[summonstype]; }
	bool Get_AttacFlag(void) { return m_AttakFlag; }
	int Get_OrnamentType(void) { return m_OrnamentType; }
	bool Get_DamageFlag(void) { return m_DamageFlag; }
	static char* Get_AnimeFileName(int index) { return ANIME_MODEL_FILES[index].filename; }
	static void TitleFlag_Change(bool change) { m_TitleFlag = change; }

	static bool boRenderSphere;//�����蔻����������邩�ǂ����H true ����
	//	���f���ǂݍ���
	static HRESULT InitModelLoad();
	//���f�����擾
	THING* C3DObj::GetAnimeModel(void);
	//THING GetAnimeModel(int index);
	THING_NORMAL GetNormalModel(int index);
	//THING_NORMAL GetNormal(int index);
	THING_NORMAL GetNormalModel(void);
	//	�I������
	static void Model_Finalize(void);
	static void Model_Finalize(int index);
	//�����蔻��
	//static void HitCheck(void);
	//�Փˌ��o �m�[�}�����f���΃m�[�}�����f��
	static bool Collision_NomalVSNormal(THING_NORMAL*, THING_NORMAL*);
	//�Փˌ��o �A�j�����f���΃m�[�}�����f��
	static bool Collision_AnimeVSNormal(THING*, THING_NORMAL*);
	//�Փˌ��o �A�j�����f���΃A�j�����f��
	static bool Collision_AnimeVSAnime(THING*, THING*);

	bool C3DObj::Collision_AnimeVSNormalCapsule(THING*, THING_NORMAL*);
	float C3DObj::GetSqDistancePoint2Segment(THING* pThingA, THING_NORMAL* pThingB);
	void HitCheck(void);

	virtual bool Get_DrawCheck(void) = 0;
	void DamageFlag_Change(void);	//	�_���[�W�t���O�`�F���W
	void Position_Keep(D3DXMATRIX mtxT);
	
	static int Get_Score(void) { return m_TotalScore; }	//	�X�R�A�擾
	static void Reset_Score(void) { m_TotalScore = 0; }	//�@�X�R�A���Z�b�g
	static bool GetW_coaster(void) { return GetWCos; }
	static bool *GetCosterModeStandby(void) { return &g_CosterModeStandby; }//�R�[�X�^�[���Ă�ł�Ƃ�; }//�R�[�X�^�[���Ă�ł�Ƃ�
protected:
	//THING *Thing_Anime_model;//�A�j�����f�����
	//static THING Thing_Anime[];//�ǂݍ��ރ��f���̍ő吔+1

	THING_NORMAL Thing_Normal_model;//�ʏ탂�f�����

	D3DXMATRIX m_mtxWorld;			//	���[���h�ϊ��p�s��
	D3DXMATRIX m_mtxTranslation;	//	�ړ��s��
	D3DXMATRIX m_mtxRotation;		//	�ړ��s��
	D3DXMATRIX m_mtxScaling;		//	�ړ��s��
	D3DXMATRIX m_mtxKeepTranslation;	//	�ړ��ێ��s��
	D3DXMATRIX m_mtxInit;			//	�����ʒu�s��
	float m_Angle;			//	�p�x
	
	int m_MpStock;			//	MP�X�g�b�N
	int m_Hp;				//	HP
	int m_Mp;				//	MP
	int m_Attack;			//	�U��
	int shadow_number;      //  �e�̔ԍ�
	bool m_DamageFlag;		//	�_���[�W�t���O
	bool m_AttakFlag;		//	�A�^�b�N�t���O
	int m_SummonsNum;				//	��������A�g���N�V�����̔ԍ�

	D3DXVECTOR3 m_PosKeep;	//	�|�W�V�����ێ�
	//  0 coffee
	//  1 fall
	//  2 wheel
	//  3 coaster
	//  4 popcorn
	int m_CoolTime[5] = {0};	//	�N�[���^�C��
	// �`�揈��
	void DrawDX_Anime(D3DXMATRIX mtxWorld, int type, THING* pThing);
	void C3DObj::DrawDX_Normal(D3DXMATRIX mtxWorld, int type, THING_NORMAL* pThing);
	void C3DObj::DrawDX_NormalAdd(D3DXMATRIX mtxWorld, int type, THING_NORMAL* pThing, D3DXVECTOR3 position);
	void C3DObj::DrawDX_NormalAddScale(D3DXMATRIX mtxWorld, int type, THING_NORMAL* pThing, D3DXVECTOR3 position, D3DXVECTOR3 scale);
	void C3DObj::DrawDX_NormalCapsule(D3DXMATRIX mtxWorld, int type, THING_NORMAL* pThing, D3DXVECTOR3 position,float rotation);
	
	void Animation_Change(int index, float speed);
	LPD3DXANIMATIONSET pAnimSet[10];//�I���������f����10�܂ł̃A�j���[�V�������Z�b�g
	D3DXTRACK_DESC TrackDesc;
	SKIN_MESH SkinMesh;



	
	//static THING Thing[];//�ǂݍ��ރ��f���̍ő吔+1
	THING Thing;//�ǂݍ��ރ��f���̍ő吔+1

	

	void Add_Mp(int mp);	//	MP���Z
	void Add_Hp(void);
	void Add_Score(int score) { m_TotalScore += score; }	//	�X�R�A���Z
	void Attraction_Delete(void);
	int m_OrnamentType;
	
	int m_AnimationType;
	static bool m_TitleFlag;
private:
	
	//	���f���f�[�^�̍\����
	typedef struct
	{
		char filename[256];

	}MaterialFileData;
	//	���f���f�[�^�̍\����
	typedef struct
	{
		char filename[256];

	}MaterialFileData2;
	//	�g���������f���̐���������
	static MaterialFileData NORMAL_MODEL_FILES[];
	static MaterialFileData2 ANIME_MODEL_FILES[];
	static int MODEL_FILES_MAX;	//	�e�N�X�`���\���̑���
	static int ANIME_MODEL_FILES_MAX;	//	�e�N�X�`���\���̑���
	static THING_NORMAL Thing_Normal[];//�ǂݍ��ރ��f���̍ő吔+1
	static HRESULT InitThing(THING_NORMAL *pThing, LPSTR szXFileName);//�m�[�}�����f���̓ǂݍ���
	int m_3DObjIndex;		//	3D�I�u�W�F�N�g�C���f�b�N�X
	int m_3DObjType;		//	3D�I�u�W�F�N�g�^�C�v
	static int m_3DObjNum;	//	�Q�[���I�u�W�F�N�g����
	static int m_TotalScore;

	static C3DObj *p3DObj[MAX_GAMEOBJ];


	static bool VFCulling(D3DXVECTOR3* pPosition);
	

	static LPD3DXMESH m_pD3DXMesh[];			//	���b�V�����󂯎��ϐ�
	static DWORD m_dwNumMaterials[];			//	�}�e���A���̑���	�`�悷���
	static LPD3DXBUFFER m_pD3DXMtrBuffer[];		//	�}�e���A�������󂯎��ϐ�
	static LPDIRECT3DTEXTURE9 *m_pTexures[];	//�@
	static D3DMATERIAL9 *m_pd3dMaterials[];		//�@


	static bool GetWCos;
	static bool g_CosterModeStandby;
	#define MODEL_MAX (9)

	
	
	
	
	FLOAT fAnimTime = 0.0f;
	BOOL boPlayAnim = true;
	//float fAnimTimeHold;
};

#endif // !1
