/*#define NOMINMAX
#include <windows.h>
#undef min
#undef max*/

// �A�j���[�V�������[�vX
int Animation_UpdateX(int FrameCount, int WaitFrame, int MaxPattern, int tw, int WidthMaxPattern)
{
	int DrawPattern = (FrameCount / WaitFrame) % MaxPattern;

	int BiginX;

	return BiginX = tw * (DrawPattern % WidthMaxPattern);

}
// �A�j���[�V�������[�vY
int Animation_UpdateY(int FrameCount, int WaitFrame, int MaxPattern, int th, int WidthMaxPattern)
{
	int DrawPattern = (FrameCount / WaitFrame) % MaxPattern;

	int BiginY;

	return BiginY = th * (DrawPattern / WidthMaxPattern);

}
// �A�j���[�V�������[�v����X
/*int Animation_UpdateX2(int FrameCount, int WaitFrame, int MaxPattern, int tw, int WidthMaxPattern)
{
	int DrawPattern = min((FrameCount / WaitFrame) , MaxPattern-1);

	int BiginX;

	return BiginX = tw * (DrawPattern % WidthMaxPattern);

}
// �A�j���[�V�������[�v����Y
int Animation_UpdateY2(int FrameCount, int WaitFrame, int MaxPattern, int th, int WidthMaxPattern)
{
	int DrawPattern = min((FrameCount / WaitFrame) , MaxPattern-1);

	int BiginY;

	return BiginY = th * (DrawPattern / WidthMaxPattern);

}*/
//	���p�^�[���ڂ��Đ����邩

//	(�T�C�N���̏ꍇ)
//	�\���p�^�[�� = (�t���[���J�E���^ / �҂��t���[����) % �ő�p�^�[����

//	(�T�C�N�����Ȃ��ꍇ)
//	�\���p�^�[�� = MIN((�t���[���J�E���^ / �҂��t���[����), �ő�p�^�[���� - 1)


//	�e�N�X�`���\�̐؂�����Wx = �p�^�[���̕� * (�\���p�^�[���� % ���ő�p�^�[����)
//	�e�N�X�`���\�̐؂�����Wy = �p�^�[���̍��� * (�\���p�^�[���� / ���ő�p�^�[����)