
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
#include "Cphysx.h"
#include "CEnemy.h"
#include "fade.h"
#include "scene.h"
#include "CUserInterface.h"
#include "CAttraction.h"
#include "common.h"
#include "CSkinAnimation.h"
#include "Cphysx.h"
//=============================================================================
//	�萔��`
//=============================================================================


//=============================================================================
//	�O���[�o���錾
//=============================================================================

static NxScene*	gScene = NULL;	//	�t�B�W�b�N�X�̃V�[���o�^
static bool g_bend;//	�t�F�[�h�C���A�E�g�t���O
static float Check_per;//	�G�̊���(1�̂�1%)
					   //=============================================================================
					   //	����������
					   //=============================================================================
void Game_Initialize(void)
{
	g_bend = false;
	Check_per = 0;
	CPhysx::CPhysX_Initialize();			//	�������Z�����̏�����
	gScene = CPhysx::Get_PhysX_Scene();		//	�V�[��������



	CPlayer::PlayerCreate();				//	�v���C���[����		
	CLight::Light_Create();					//	���C�g����
	CCamera::Camera_Create();				//	�J��������

	CMeshField::MeshField_Create(CTexture::TEX_FLORR, 120.0f, 1, 1);							//	�n�ʐ���
	CMeshField_Cylinder::MeshField_Cylinder_Create(CTexture::TEX_FLORR, 6.0f, 45.0f, 20, 1);	//	�J�x����
	CMesh_SkyDome::Mesh_SkyDome_Create(CTexture::TEX_SKY, 2.0f, 60.0f, 40, 20);					//	�󐶐�
	CUserInterFace::UICreate();				//	UI����
	CEnemy::Create();						//	�G����




}

//=============================================================================
//	�I������
//=============================================================================

void Game_Finalize(void)
{
	C3DObj::DeleteAll();			//	3D�I�u�W�F�N�g�S����
	CGameObj::DeleteAll();			//	2D�I�u�W�F�N�g�S����
	CPhysx::ExitNx();				//	�������Z�I������
	CGameObj::FrameCountReset();	//	�t���[���J�E���g���Z�b�g
}

//=============================================================================
//	�X�V����
//=============================================================================

void Game_Updata(void)
{
	//�����ɃN���X�֌W�Ȃ��̊֐�������
	C3DObj::UpdateAll();	//	3D�I�u�W�F�N�g�X�V
	CGameObj::UpdateAll();	//	2D�I�u�W�F�N�g�X�V

	CEnemy::Create();		//	�G�l�~�[����

	Check_per = 1.0 - (float)CEnemy::Get_EnemyNum(0) / 100;	//������

	if (GAMEEND <= CGameObj::Get_FraemCount())		//	FraemCount��GAMEEND�ɂȂ�܂ŃJ�E���gUP�@�Ȃ�����I��
	{
		if (!g_bend)
		{
			Fade_Start(true, 3, 0, 0, 0);
			g_bend = true;
		}
		else
		{
			Fade_Start(false, 3, 0, 0, 0);
			Scene_Change(SCENE_INDEX_SCORE);
		}
	}
	else
	{
		CGameObj::FrameCountUp();
	}
}

//=============================================================================
//	�`�揈��
//=============================================================================

void Game_Draw(void)
{
	C3DObj::DrawAll();		//	3D�I�u�W�F�N�g�`��
	CGameObj::DrawAll();	//	2D�I�u�W�F�N�g�`��

	gScene->flushStream();
	gScene->fetchResults(NX_RIGID_BODY_FINISHED, true);
	CPhysx::HitCheck();
}


float Get_CheckPer(void)
{
	return Check_per;
}