//////////////////////////////////////////////////
////
////	�Q�[���I�u�W�F�N�g�N���X
////
//////////////////////////////////////////////////

#ifndef _GAMEOBJ_H_
#define _GAMEOBJ_H_

#include <d3dx9.h>

#define TEXTURE_FILENAME_MAX (64)

class CGameObj
{
public:
	CGameObj();
	virtual ~CGameObj();

	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual void Finalize(void) = 0;
	bool Get_Enable(void) { return m_Enable; }

	static void Initialize(void);
	static int Get_FraemCount(void) { return m_FrameCount; }	//	�t���[���J�E���g�擾
	static int Get_GameObjNum(void) { return m_GameObjNum; }	//	���Q�[���I�u�W�F�N�g�擾
	static int Get_GameObjIndex(void) { return m_GameObjNum - 1; }	//	�Q�[���I�u�W�F�N�g�C���f�b�N�X

	static void FrameCountUp(void) { m_FrameCount++; }	//  �t���[���J�E���g�A�b�v
	static bool Device_Initialize(HWND hWnd);	//	�f�o�C�X������
	static void Device_Finalize(void);	//	�f�o�C�X�j��
	static LPDIRECT3DDEVICE9 m_pD3DDevice;	//	�f�o�C�X

	static void DebugDraw(void);
protected:		

	static int m_FrameCount;	//	�t���[���J�E���g�@
	static int m_GameObjNum;	//	�Q�[���I�u�W�F�N�g����
	int m_TimeKeep = 0;
	bool m_Enable;

private:

	

	static LPDIRECT3D9 m_pD3D;
	
};

#endif // !1


