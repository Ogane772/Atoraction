//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================
#include"scene.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "Score_total.h"
#include "manual.h"
//=============================================================================
//	�O���[�o���ϐ��錾
//=============================================================================

static SCENE_INDEX g_SceneIndex;
static SCENE_INDEX g_SceneNextIndex;

typedef void(*SceneFunc)(void);	//����

static const SceneFunc Initialize[] = {
	Title_Initialize,
	Manual_Init,
	Game_Initialize,
	Score_total_Initialize,
	Result_Initialize
	//	�֐��̃|�C���^�͊֐����̂�
};

static const SceneFunc Finalize[] = {
	Title_Finalize,
	Manual_Fainalize,
	Game_Finalize,
	Score_total_Finalize,
	Result_Finalize
};

static const SceneFunc Update[] = {
	Title_Update,
	Manual_Update,
	Game_Updata,
	Score_total_Update,
	Result_Update
};

static const SceneFunc Draw[] = {
	Title_Draw,
	Manual_Draw,
	Game_Draw,
	Score_total_Draw,
	Result_Draw
};

//=============================================================================
//	����������
//=============================================================================

void Scene_Initialize(SCENE_INDEX index)
{
	g_SceneNextIndex = g_SceneIndex = index;

	Initialize[g_SceneIndex]();
	//	Initialize��g_SceneIndex�Ԗڂ����s

}

//=============================================================================
//	�I������
//=============================================================================

void Scene_Finalize(void)
{
	Finalize[g_SceneIndex]();
}

//=============================================================================
//	�X�V����
//=============================================================================

void Scene_Update(void)
{
	Update[g_SceneIndex]();
}

//=============================================================================
//	�`�揈��
//=============================================================================

void Scene_Draw(void)
{
	Draw[g_SceneIndex]();
}

//=============================================================================
//	�֐���`
//=============================================================================

// �V�[���`�F�b�N
void Scene_check(void)
{
	if (g_SceneIndex != g_SceneNextIndex)
	{
		Scene_Finalize();
		Scene_Initialize(g_SceneNextIndex);
	}
}

// �V�[���`�F���W
void Scene_Change(SCENE_INDEX index)
{
	g_SceneNextIndex = index;
}


