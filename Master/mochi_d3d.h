#ifndef _MOCHI_D3D_H_
#define _MOCHI_D3D_H_





// Direct3D�̏�����
// �߂�l�F�������Ɏ��s������false
// �����FhWnd...�E�B���h�E�n���h��

bool mochi_Init(HWND hWnd);

// Direct3D�̏C������
void mochi_end(void);

// Direct3D�f�o�C�X�|�C���^�̎擾
LPDIRECT3DDEVICE9 mochi_GetDevice(void);

#endif //_MOCHI_H_
