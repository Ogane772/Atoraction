#ifndef _COMMON_H_
#define _COMMON_H_

#define WINDOW_TOP		(40.0f)	// �X�N���[�����
#define WINDOW_WIDTH	(1920.0f)	// �X�N���[����
#define WINDOW_HIGHT	(1016.0f)	// �X�N���[������
#define WINDOW_UNDER	(WINDOW_HIGHT - 50.0f)	//	�n�ʂ̍���
#define WINDOW_PLAYER_UNDER (WINDOW_HIGHT - 97.0f)	//	�v���C���[���猩���n�ʂ̍���
#define GAMEEND (5400)
#define FIELDSIZE (90.0f)
#define SYLINDERSIZE (55.0f)
#define SKYSIZE (80.0f)

void Game_End(void);
#endif //_COMMON_H_