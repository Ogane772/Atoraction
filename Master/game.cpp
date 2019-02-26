
//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================
#define NOMINMAX

#include "CLight.h"
#include "CCamera.h"
#include "CMeshField.h"
#include "CMeshField_Cylinder.h"
#include "CMesh_SkyDome.h"
#include "Cplayer.h"
#include "billboard.h"
#include "CEnemy.h"
#include "fade.h"
#include "scene.h"
#include "CUserInterface.h"
#include "CAttraction.h"
#include "common.h"
#include "exp.h"
#include "shadow.h"
#include "COrnament.h"
#include "sound.h"
//=============================================================================
//	�萔��`
//=============================================================================


//=============================================================================
//	�O���[�o���錾
//=============================================================================
static bool g_bend;				//	�t�F�[�h�C���A�E�g�t���O
static bool g_gameend;
static float EnemyPer;
//=============================================================================
//	����������
//=============================================================================
void Game_Initialize(void)
{
	g_bend = false;
	g_gameend = false;
	/*	CPhysx::CPhysX_Initialize();			//	�������Z�����̏�����
	gScene = CPhysx::Get_PhysX_Scene();		//	�V�[��������*/

	C3DObj::InitModelLoad();

	CPlayer::PlayerCreate();				//	�v���C���[����		
	CLight::Light_Create();					//	���C�g����
	CCamera::Camera_Create();				//	�J��������

	CMeshField::MeshField_Create(CTexture::TEX_KUSA_RENGA, 120.0f, 2, 2);							//	�n�ʐ���
	//CMeshField_Cylinder::MeshField_Cylinder_Create(CTexture::TEX_FLORR, 10.0f, SYLINDERSIZE, 20, 1,true);	//	���J�x����
	CMeshField_Cylinder::MeshField_Cylinder_Create(CTexture::TEX_MOUNTAIN, 10.0f, FIELDSIZE, 20, 1, false);	//	�O�J�x����
	CMesh_SkyDome::Mesh_SkyDome_Create(CTexture::TEX_SKY, 2.0f, SKYSIZE, 40, 20);					//	�󐶐�
	CUserInterFace::UICreate();				//	UI����
	CEnemy::Create();						//	�G����
	COrnament::Create();						//	�I�u�W�F�N�g����
	Shadow_Initialize();
	PlaySound(MAIN_BGM);
}

//=============================================================================
//	�I������
//=============================================================================

void Game_Finalize(void)
{
	C3DObj::DeleteAll();			//	3D�I�u�W�F�N�g�S����
	CGameObj::DeleteAll2D();			//	2D�I�u�W�F�N�g�S����
	C3DObj::Model_Finalize();
	CGameObj::FrameCountReset();	//	�t���[���J�E���g���Z�b�g
}

//=============================================================================
//	�X�V����
//=============================================================================

void Game_Updata(void)
{
	C3DObj::UpdateAll();	//	3D�I�u�W�F�N�g�X�V
	CGameObj::UpdateAll();	//	2D�I�u�W�F�N�g�X�V
	//COrnament::Create();    //  �I�u�W�F�N�g����
	EnemyPer = 1.0f - (float)CEnemy::Get_EnemyNum(0) / CEnemy::Get_EnemyMaxNum(); //�G�̐����擾
	if (g_gameend)		//	FraemCount��GAMEEND�ɂȂ�܂ŃJ�E���gUP�@�Ȃ�����I��
	{
		if (!g_bend)
		{
			Fade_Start(true, 1, 0, 0, 0);
			g_bend = true;
		}
		else
		{
			if (!Fade_IsFade())
			{
				Fade_Start(false, 1, 0, 0, 0);
				StopSound(MAIN_BGM);
				Scene_Change(SCTNE_INDEX_SCORE);
				PlaySound(GAME_END_SE);
			}
		}
	}
	else
	{
		CGameObj::FrameCountUp();
		if (GAMEEND <= CGameObj::Get_FraemCount())
		{
			g_gameend = true;
		}
	}
	Exp_Update();

	
}

//=============================================================================
//	�`�揈��
//=============================================================================

void Game_Draw(void)
{
	C3DObj::DrawAll();		//	3D�I�u�W�F�N�g�`��
	CGameObj::DrawAll();	//	2D�I�u�W�F�N�g�`��
	Exp_Draw();
	Shadow_Draw();
	//C3DObj::HitCheck();
}


void Game_End(void)
{
	g_gameend = true;
}

float Get_EnemyPer(void)
{
	return EnemyPer;
}