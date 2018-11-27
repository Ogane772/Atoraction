//////////////////////////////////////////////////
////
////	2D�I�u�W�F�N�g�N���X
////
//////////////////////////////////////////////////

//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================

#include "C2DObj.h"
#include "ten_texture.h"
#include "CCamera.h"
#include "common.h"
//=============================================================================
//	�萔��`
//=============================================================================


//=============================================================================
//	�ÓI�ϐ�
//=============================================================================

LPDIRECT3DVERTEXBUFFER9 C2DObj::m_p2DVertexBuffer = NULL;
LPDIRECT3DINDEXBUFFER9 C2DObj::m_p2DIndexBuffer = NULL;

//=============================================================================
//	����
//=============================================================================

C2DObj::C2DObj()
{
	//m_GameObjNum--;
}

//=============================================================================
//	�j��
//=============================================================================

C2DObj::~C2DObj()
{
	
}

//=============================================================================
//	�X�v���C�g������
//=============================================================================

void C2DObj::Sprite_Initialize(void)
{
	C2DObj::m_pD3DDevice->CreateVertexBuffer(sizeof(Vertex2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX2D, D3DPOOL_MANAGED, &m_p2DVertexBuffer, NULL);
	/*
	1 ���_�̃T�C�Y
	2 �p�r
	3 FVF
	4 VRAM��̃������̊Ǘ�
	5 �������̏ꏊ
	6 NULL(������Ȃ��Ƃ���NULL������)
	*/

	// �C���f�b�N�X�o�b�t�@�̊m��
	C2DObj::m_pD3DDevice->CreateIndexBuffer(sizeof(WORD) * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_p2DIndexBuffer, NULL);
	/*
	1 �C���f�b�N�X�̃T�C�Y
	2 �p�r
	3 �C���f�b�N�X�̃t�H�[�}�b�g(16�r�b�g��32�r�b�g)
	4 VRAM��̃������̊Ǘ�
	5 �������̏ꏊ
	6 NULL(������Ȃ��Ƃ���NULL������)
	*/
}

//=============================================================================
//	�X�v���C�g�`��
//=============================================================================

void C2DObj::Sprite_Draw(int texture_index, float dx, float dy, int tx, int ty, int tw, int th)
{
	float w = (float)Texture_GetWidth(texture_index,1);
	float h = (float)Texture_GetHeight(texture_index,1);

	float u0 = (float)tx / w;
	float v0 = (float)ty / h;
	float u1 = (float)tw / w;
	float v1 = (float)th / h;


	Vertex2D v[] = {
		{ D3DXVECTOR4(dx - 0.5f,dy - 0.5f,0.0f,1.0f),D3DCOLOR(0xffffffff),D3DXVECTOR2(u0	  ,v0) },	//	��4�����͐��1.0��
		{ D3DXVECTOR4(dx + tw - 0.5f,dy - 0.5f,0.0f,1.0f),D3DCOLOR(0xffffffff),D3DXVECTOR2(u0 + u1,v0) },
		{ D3DXVECTOR4(dx - 0.5f,dy + th - 0.5f,0.0f,1.0f),D3DCOLOR(0xffffffff),D3DXVECTOR2(u0	  ,v0 + v1) },
		{ D3DXVECTOR4(dx + tw - 0.5f,dy + th - 0.5f,0.0f,1.0f),D3DCOLOR(0xffffffff),D3DXVECTOR2(u0 + u1,v0 + v1) },

	};

	// ���_�C���f�b�N�X
	WORD index[] = { 0, 1, 2, 1, 3, 2 };
	// window.h�@�K�p�@unsigned short

	// ���z�A�h���X�@
	Vertex2D *pv;
	// ���_�o�b�t�@�̃��b�N
	m_p2DVertexBuffer->Lock(0, 0, (void**)&pv, 0);
	/*
	1 �ǂ�����
	2 0�ł���
	3 ���z�A�h���X������
	4 0�ł���
	*/
	memcpy(pv, v, sizeof(v));
	m_p2DVertexBuffer->Unlock();

	// ���z�A�h���X�@
	WORD *Ipv;
	// �C���f�b�N�X�o�b�t�@�̃��b�N
	m_p2DIndexBuffer->Lock(0, 0, (void**)&Ipv, 0);
	/*
	1 �ǂ�����
	2 0�ł���
	3 ���z�A�h���X������
	4 0�ł���
	*/
	Ipv[0] = 0;
	Ipv[1] = 1;
	Ipv[2] = 2;
	Ipv[3] = 1;
	Ipv[4] = 3;
	Ipv[5] = 2;
	m_p2DIndexBuffer->Unlock();

	/*D3DXMATRIX mtxWorld;		// 4*4�s��@d3dx9.h�K�v
	D3DXMatrixIdentity(&mtxWorld);	// �A�h���X����ƒP�ʍs�������Ă����
	C2DObj::m_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	D3DXMATRIX mtxv = CCamera::Get_ViewMtx();
	C2DObj::m_pD3DDevice->SetTransform(D3DTS_VIEW, &mtxv);

	// �v���W�F�N�V�������W�ϊ��s��
	D3DXMATRIX mtxProjection;
	// �v���W�F�N�V�������W�ϊ�
	D3DXMatrixOrthoLH(&mtxProjection, WINDOW_WIDTH, WINDOW_HIGHT, NYAA, FUAA);
	CGameObj::m_pD3DDevice->SetTransform(D3DTS_TEXTURE0, &mtxProjection);
	*/
	m_pD3DDevice->SetFVF(FVF_VERTEX2D);		//	FVF���f�o�C�X�ɐݒ�

	m_pD3DDevice->SetTexture(0, Texture_GetTexture(texture_index));

	m_pD3DDevice->SetStreamSource(0, m_p2DVertexBuffer, 0, sizeof(Vertex2D));
	m_pD3DDevice->SetIndices(m_p2DIndexBuffer);



	// g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, v, sizeof(Vertex2D));		
	/*
	��1�����@�ǂ�Ȍ`��
	��2�����@�v���~�e�B�u���@�O�p�`������������
	��3����  ���_�f�[�^�̐擪�A�h���X
	��4�����@���_�f�[�^�\���̂̑傫��
	*/
	//g_pD3DDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 4, 2, index, D3DFMT_INDEX16, v, sizeof(Vertex2D));
	/*
	��1�����@�ǂ�Ȍ`��
	��2�����@index �̈�ԏ�������
	��3�����@���_�̐�
	��4�����@�v���~�e�B�u��
	��5�����@index�̐擪�A�h���X
	��6�����@�r�b�g��(16or32)
	��7�����@���_�f�[�^�̐擪�A�h���X
	��8�����@���_�f�[�^�\���̂̑傫��
	*/
	//g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	m_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}


void C2DObj::m_Sprite_Draw(int texture_index, float dx, float dy, int tx, int ty, int tw, int th)
{
	float w = (float)Texture_GetWidth(texture_index, 1);
	float h = (float)Texture_GetHeight(texture_index, 1);

	float u0 = (float)tx / w;
	float v0 = (float)ty / h;
	float u1 = (float)tw / w;
	float v1 = (float)th / h;


	Vertex2D v[] = {
		{ D3DXVECTOR4(dx - 0.5f,dy - 0.5f,1.0f,1.0f),D3DCOLOR(0xffffffff),D3DXVECTOR2(u0	  ,v0) },	//	��4�����͐��1.0��
		{ D3DXVECTOR4(dx + tw - 0.5f,dy - 0.5f,1.0f,1.0f),D3DCOLOR(0xffffffff),D3DXVECTOR2(u0 + u1,v0) },
		{ D3DXVECTOR4(dx - 0.5f,dy + th - 0.5f,1.0f,1.0f),D3DCOLOR(0xffffffff),D3DXVECTOR2(u0	  ,v0 + v1) },
		{ D3DXVECTOR4(dx + tw - 0.5f,dy + th - 0.5f,1.0f,1.0f),D3DCOLOR(0xffffffff),D3DXVECTOR2(u0 + u1,v0 + v1) },

	};

	// ���_�C���f�b�N�X
	WORD index[] = { 0, 1, 2, 1, 3, 2 };
	// window.h�@�K�p�@unsigned short

	// ���z�A�h���X�@
	Vertex2D *pv;
	// ���_�o�b�t�@�̃��b�N
	m_p2DVertexBuffer->Lock(0, 0, (void**)&pv, 0);
	/*
	1 �ǂ�����
	2 0�ł���
	3 ���z�A�h���X������
	4 0�ł���
	*/
	memcpy(pv, v, sizeof(v));
	m_p2DVertexBuffer->Unlock();

	// ���z�A�h���X�@
	WORD *Ipv;
	// �C���f�b�N�X�o�b�t�@�̃��b�N
	m_p2DIndexBuffer->Lock(0, 0, (void**)&Ipv, 0);
	/*
	1 �ǂ�����
	2 0�ł���
	3 ���z�A�h���X������
	4 0�ł���
	*/
	Ipv[0] = 0;
	Ipv[1] = 1;
	Ipv[2] = 2;
	Ipv[3] = 1;
	Ipv[4] = 3;
	Ipv[5] = 2;
	m_p2DIndexBuffer->Unlock();

	m_pD3DDevice->SetFVF(FVF_VERTEX2D);		//	FVF���f�o�C�X�ɐݒ�

	m_pD3DDevice->SetTexture(0, Texture_GetTexture(texture_index));

	m_pD3DDevice->SetStreamSource(0, m_p2DVertexBuffer, 0, sizeof(Vertex2D));
	m_pD3DDevice->SetIndices(m_p2DIndexBuffer);

	// g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, v, sizeof(Vertex2D));		
	/*
	��1�����@�ǂ�Ȍ`��
	��2�����@�v���~�e�B�u���@�O�p�`������������
	��3����  ���_�f�[�^�̐擪�A�h���X
	��4�����@���_�f�[�^�\���̂̑傫��
	*/
	//g_pD3DDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 4, 2, index, D3DFMT_INDEX16, v, sizeof(Vertex2D));
	/*
	��1�����@�ǂ�Ȍ`��
	��2�����@index �̈�ԏ�������
	��3�����@���_�̐�
	��4�����@�v���~�e�B�u��
	��5�����@index�̐擪�A�h���X
	��6�����@�r�b�g��(16or32)
	��7�����@���_�f�[�^�̐擪�A�h���X
	��8�����@���_�f�[�^�\���̂̑傫��
	*/
	//g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	m_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}
//=============================================================================
//	�X�v���C�g�j��
//=============================================================================

void C2DObj::Sprite_Finalize(void)
{
	// �C���f�b�N�X�o�b�t�@�̉��
	if (m_p2DIndexBuffer != NULL)
	{
		m_p2DIndexBuffer->Release();
		m_p2DIndexBuffer = NULL;
	}

	// ���_�o�b�t�@�̉��
	if (m_p2DVertexBuffer != NULL)
	{
		m_p2DVertexBuffer->Release();
		m_p2DVertexBuffer = NULL;
	}
}




void C2DObj::Update(void)
{

}
void C2DObj::Draw(void)
{

}
void C2DObj::Finalize(void)
{

}