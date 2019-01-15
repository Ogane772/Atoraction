//////////////////////////////////////////////////
////
////	3D�I�u�W�F�N�g�N���X
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
		TYPE_PLAYER,	// �v���C���[
		TYPE_ENEMY,		// �G�l�~�[
		TYPE_ATTRACTION,// �A�g���N�V����
		TYPE_COASTER,	// �W�F�b�g�R�[�X�^�[
		TYPE_POPCORN,	// �W�F�b�g�R�[�X�^�[
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
	}ModelFileData;
	enum ANIME_MODEL
	{
		MODELL_ANIME_SMALL,
		ANIME_MODEL_MAX,//�A�j�����f���ő吔
	}AnimeModelFileData;;
	virtual void Update(void) = 0;	//	�X�V
	virtual void Draw(void) = 0;	//	�`��

	D3DXMATRIX Get_mtxWorld(void) { return m_mtxWorld; }				//	���[���h�ϊ��p�s��擾
	D3DXMATRIX Get_mtxTranslation(void) { return m_mtxTranslation; }	//	�ړ��p�s��擾

	static void UpdateAll();	// �S�I�u�W�F�N�g�X�V
	static void DrawAll();		// �S�I�u�W�F�N�g�`��
	static void DeleteAll();	// �S�I�u�W�F�N�g�폜
	void C3DObj_delete(void);	// �I�u�W�F�N�g�폜	
	static C3DObj *Get(int nIdx);				// �C���X�^���X�擾
	int Get_3DObjIndex() { return m_3DObjIndex; }	// ���[�N�C���f�b�N�X�擾
	int Get_3DObjType() { return m_3DObjType; }		// ��ގ擾

	int Get_Angle(void) { return (int)m_Angle; }			//	�p�x�擾
	D3DXVECTOR3 Get_Front(void) { return m_front; }	//	�O�x�N�g���擾
	
	int Get_Hp(void) { return m_Hp; }				//	HP�擾
	int Get_Mp(void) { return m_Mp; }				//	MP�擾
	int Get_MpStock(void) { return m_MpStock; }		//	MP�X�g�b�N�擾
	
	//	���f���ǂݍ���
	static HRESULT InitModelLoad();
	//���f�����擾
	static THING* C3DObj::GetAnimeModel(int index);
	static THING_NORMAL* C3DObj::GetNormalModel(int index);
	//	�I������
	static void Model_Finalize(void);
	static void Model_Finalize(int index);
	//�����蔻��
	static void HitCheck(void);

	virtual bool Get_DrawCheck(void) = 0;
protected:
	THING *Thing_Anime_model;//�A�j�����f�����
	THING_NORMAL *Thing_Normal_model;//�ʏ탂�f�����
	D3DXMATRIX m_mtxWorld;			//	���[���h�ϊ��p�s��
	D3DXMATRIX m_mtxTranslation;	//	�ړ��s��
	D3DXMATRIX m_mtxRotation;		//	�ړ��s��
	D3DXMATRIX m_mtxScaling;		//	�ړ��s��
	
	float m_Angle;			//	�p�x
	D3DXVECTOR3 m_front;	//	�O�x�N�g��
	D3DXVECTOR3 m_right;	//	�E�x�N�g��
	D3DXVECTOR3 m_up;		//	��x�N�g��
	int m_MpStock;			//	MP�X�g�b�N
	int m_Hp;				//	HP
	int m_Mp;				//	MP
	int m_Attack;			//	�U��

	// �`�揈��
	void DrawDX_Anime(D3DXMATRIX mtxWorld, int type, THING* pThing);
	void C3DObj::DrawDX_Normal(D3DXMATRIX mtxWorld, int type, THING_NORMAL* pThing);


private:
	
	static HRESULT InitThing(THING_NORMAL *pThing, LPSTR szXFileName);//�m�[�}�����f���̓ǂݍ���
	int m_3DObjIndex;		//	3D�I�u�W�F�N�g�C���f�b�N�X
	int m_3DObjType;		//	3D�I�u�W�F�N�g�^�C�v
	static int m_3DObjNum;	//	�Q�[���I�u�W�F�N�g����
	static C3DObj *p3DObj[MAX_GAMEOBJ];
	//�Փˌ��o �m�[�}�����f���΃m�[�}�����f��
	static bool Collision_NomalVSNormal(THING_NORMAL*, THING_NORMAL*);
	//�Փˌ��o �A�j�����f���΃m�[�}�����f��
	static bool Collision_AnimeVSNormal(THING*, THING_NORMAL*);
	//�Փˌ��o �A�j�����f���΃A�j�����f��
	static bool Collision_AnimeVSAnime(THING*, THING*);
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

	static LPD3DXMESH m_pD3DXMesh[];			//	���b�V�����󂯎��ϐ�
	static DWORD m_dwNumMaterials[];			//	�}�e���A���̑���	�`�悷���
	static LPD3DXBUFFER m_pD3DXMtrBuffer[];		//	�}�e���A�������󂯎��ϐ�
	static LPDIRECT3DTEXTURE9 *m_pTexures[];	//�@
	static D3DMATERIAL9 *m_pd3dMaterials[];		//�@


	static int MODEL_FILES_MAX;	//	�e�N�X�`���\���̑���
	static int ANIME_MODEL_FILES_MAX;	//	�e�N�X�`���\���̑���
};

#endif // !1
