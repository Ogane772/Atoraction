//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================

#include <d3dx9.h>
#include "C3DObj.h"
#include "CTexture.h"
#include "CCamera.h"
#include "billboard.h"
//=============================================================================
//	�萔��`
//=============================================================================



//=============================================================================
//	�O���[�o���錾
//=============================================================================

typedef struct
{
	D3DXVECTOR3 pos;	//	���Wx,y,z
	D3DXVECTOR3 normal; //	�@���x�N�g�� ���W�̌� ������1.0
	D3DCOLOR color;		//  �F
	D3DXVECTOR2 uv;		//  �e�N�X�`��

}BillBoardVertex3D;


#define FVF_CUBE_VERTEX3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)	//	�\���̂̂������ɏ���

// ���_�o�b�t�@�̊m��
static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;

static BillBoardVertex3D g_bb[] = {
	{ D3DXVECTOR3(-0.5, 0.5,0.0),D3DXVECTOR3(0.0,0.0,0.0),D3DCOLOR(0xffff0000),D3DXVECTOR2(0.0,0.0) },
	{ D3DXVECTOR3(0.5, 0.5,0.),D3DXVECTOR3(0.0,0.0,0.0),D3DCOLOR(0xffff0000),D3DXVECTOR2(1.0,0.0) },
	{ D3DXVECTOR3(-0.5,-0.5,0.0),D3DXVECTOR3(0.0,0.0,0.0),D3DCOLOR(0xffff0000),D3DXVECTOR2(0.0,1.0) }, 
	{ D3DXVECTOR3(0.5,-0.5,0.0),D3DXVECTOR3(0.0,0.0,0.0),D3DCOLOR(0xffff0000),D3DXVECTOR2(1.0,1.0) },
};




void BillBoard_Initialize(void)
{
	/*
	LPDIRECT3DDEVICE9 pD3DDevice = mochi_GetDevice();
	pD3DDevice->CreateVertexBuffer(sizeof(BillBoardVertex3D) * 4, D3DUSAGE_WRITEONLY, FVF_CUBE_VERTEX3D, D3DPOOL_MANAGED, &g_pVertexBuffer, NULL);

	// ���z�A�h���X�@
	BillBoardVertex3D *pv;
	// ���_�o�b�t�@�̃��b�N
	g_pVertexBuffer->Lock(0, 0, (void**)&pv, 0);
	/*
	1 �ǂ�����
	2 0�ł���
	3 ���z�A�h���X������
	4 0�ł���

	memcpy(pv, g_bb, sizeof(g_bb));
	g_pVertexBuffer->Unlock();
	*/
}

void BillBoard_Finalize(void)
{
	// ���_�o�b�t�@�̉��
	if (g_pVertexBuffer != NULL)
	{
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}

}

void BillBoard_Updata(void)
{

}

void BillBoard_Draw(void)
{
	/*
	LPDIRECT3DDEVICE9 pD3DDevice = mochi_GetDevice();
	D3DXMATRIX mtxWorld;	//	���[���h�ϊ��p�s��
	D3DXMatrixIdentity(&mtxWorld);

	D3DXMATRIX mtxInvV;	//	�t�s��

	mtxInvV = Get_ViewMtx();
	mtxInvV._41 = 0.0f;
	mtxInvV._42 = 0.0f;
	mtxInvV._43 = 0.0f;

	D3DXMatrixInverse(&mtxInvV, NULL, &mtxInvV);

	mtxWorld = mtxInvV * mtxWorld;

	pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pD3DDevice->SetFVF(FVF_CUBE_VERTEX3D);		//	FVF���f�o�C�X�ɐݒ�
	pD3DDevice->SetTexture(0, Texture_GetTexture(2));
	pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	pD3DDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(BillBoardVertex3D));
	pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 4, g_bb, sizeof(BillBoardVertex3D));
	*/
}


void BillBoard_Draw(D3DXMATRIX mtx)
{
	/*
	LPDIRECT3DDEVICE9 pD3DDevice = mochi_GetDevice();
	D3DXMATRIX mtxWorld;	//	���[���h�ϊ��p�s��
	D3DXMatrixIdentity(&mtxWorld);

	D3DXMATRIX mtxInvV;	//	�t�s��

	mtxInvV = Get_ViewMtx();
	mtxInvV._41 = 0.0f;
	mtxInvV._42 = 0.0f;
	mtxInvV._43 = 0.0f;
	//D3DXMatrixInverse(&mtxInvV, NULL, &mtxInvV);	//	�t�s��
	D3DXMatrixTranspose(&mtxInvV, &mtxInvV);		//	�]�u

	mtxWorld = mtx;
	mtxWorld = mtxInvV * mtxWorld;

	pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pD3DDevice->SetFVF(FVF_CUBE_VERTEX3D);		//	FVF���f�o�C�X�ɐݒ�
	pD3DDevice->SetTexture(0, Texture_GetTexture(2));
	pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	pD3DDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(BillBoardVertex3D));
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0,2);
	*/
}

void BillBoard_Draw(float x,float y,float z)
{
	/*
	LPDIRECT3DDEVICE9 pD3DDevice = mochi_GetDevice();

	D3DXMATRIX mtxWorld;	//	���[���h�ϊ��p�s��
	D3DXMatrixIdentity(&mtxWorld);

	D3DXMATRIX mtxTranslation;
	D3DXMatrixTranslation(&mtxTranslation, x, y, z);

	D3DXMATRIX mtxInvV;	//	�t�s��

	mtxInvV = Get_ViewMtx();
	mtxInvV._41 = 0.0f;
	mtxInvV._42 = 0.0f;
	mtxInvV._43 = 0.0f;
	//D3DXMatrixInverse(&mtxInvV, NULL, &mtxInvV);	//	�t�s��
	D3DXMatrixTranspose(&mtxInvV, &mtxInvV);		//	�]�u

	mtxWorld = mtxTranslation;
	mtxWorld = mtxInvV * mtxWorld;


	pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);	//	���e�X�g�L��
	pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0);	//	�Q�ƒl�ݒ�
	pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER); // ��r���Z���ݒ� D3DCMP_GRATER ��Ȃ�>
	

	pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pD3DDevice->SetFVF(FVF_CUBE_VERTEX3D);		//	FVF���f�o�C�X�ɐݒ�
	pD3DDevice->SetTexture(0, Texture_GetTexture(2));
	pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	pD3DDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(BillBoardVertex3D));
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	*/
}

void BillBoard_Exp_Draw(float x, float y, float z, int texture_index, int anime_pattan, float size, float rotation, int tx, int ty, int width_patan, int counter, int animetime)
{
	int patan = 0;
	CGameObj::m_pD3DDevice;

	patan = (counter / animetime) % anime_pattan;

	float w = (float)CTexture::Texture_GetWidth(texture_index, 1);
	float h = (float)CTexture::Texture_GetHeight(texture_index, 1);
	int tx2 = tx;
	int ty2 = ty;
	tx = tx2 * (patan % width_patan);
	ty = ty2 * (patan / width_patan);
	//UV���W�w��
	float u0 = (float)tx / w;
	float v0 = (float)ty / h;
	float u1 = (float)tx / w + tx2 / w;
	float v1 = (float)ty / h + ty2 / h;
	BillBoardVertex3D b_pori[] = {
		//����
		{ D3DXVECTOR3(-size,  size, -size),  D3DXVECTOR3(0.0f, 0.0f, -0.0f),  D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u0,v0) },
		{ D3DXVECTOR3(size,  size, -size),  D3DXVECTOR3(0.0f, 0.0f, -0.0f),  D3DCOLOR_RGBA(255, 255, 255, 255),  D3DXVECTOR2(u1,v0) },
		{ D3DXVECTOR3(-size, -size, -size),  D3DXVECTOR3(0.0f, 0.0f, -0.0f),  D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u0,v1) },
		{ D3DXVECTOR3(size, -size, -size),  D3DXVECTOR3(0.0f, 0.0f, -0.0f),  D3DCOLOR_RGBA(255, 255, 255, 255),  D3DXVECTOR2(u1,v1) },
	};
	CGameObj::m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	CGameObj::m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, FALSE);//Z�e�X�g��L�����������@����Ɛ�ΑO�ɏ���


	CGameObj::m_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
	CGameObj::m_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);

	CGameObj::m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	CGameObj::m_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	CGameObj::m_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 70);
	CGameObj::m_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	D3DXMATRIX mtxView = CCamera::Get_ViewMtx();

	D3DXMATRIX mtxInvV;
	mtxView._41 = 0.0f;
	mtxView._42 = 0.0f;
	mtxView._43 = 0.0f;
	D3DXMatrixInverse(&mtxInvV, NULL, &mtxView);

	CGameObj::m_pD3DDevice->SetFVF(FVF_CUBE_VERTEX3D);
	CGameObj::m_pD3DDevice->SetTexture(0, CTexture::Texture_GetTexture(texture_index));

	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxTranslation;
	D3DXMATRIX mtxRotate;

	D3DXMatrixIdentity(&mtxWorld);

	D3DXMatrixTranslation(&mtxTranslation, x, y, z);//���s
	D3DXMatrixRotationZ(&mtxRotate, D3DXToRadian(rotation));

	mtxWorld = (mtxInvV * mtxWorld) * mtxTranslation;
	mtxWorld = mtxRotate * mtxWorld;
	CGameObj::m_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	CGameObj::m_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &b_pori, sizeof(BillBoardVertex3D));
	CGameObj::m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
}