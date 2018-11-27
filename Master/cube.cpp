//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================

#include <d3dx9.h>
#include "mochi_d3d.h"
#include "common.h"
#include "input.h"
#include "ten_texture.h"
#include "move.h"
//=============================================================================
//	�萔��`
//============================-=================================================

#define MAX_CUBE (8)
#define ADJUST (0.005f)
#define SAI_ROT (4.5f)
#define SAI_MOVE (0.05f)

//=============================================================================
//	�O���[�o���錾
//=============================================================================

//3D�|���S�����_�@�\����
typedef struct
{
	D3DXVECTOR3 pos;	//	���Wx,y,z
	D3DXVECTOR3 normal; //	�@���x�N�g�� ���W�̌� ������1.0
	D3DCOLOR color;		//  �F
	D3DXVECTOR2 uv;		//  �e�N�X�`��

}CubeVertex3D;

#define FVF_CUBE_VERTEX3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)	//	�\���̂̂������ɏ���

// ���_�o�b�t�@�̊m��
static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;

// TRIANGLELIST ���_���W
static CubeVertex3D g_cube[] = {
	// ��O
	{ D3DXVECTOR3(-0.5, 0.5,-0.5),D3DXVECTOR3(0.0,0.0,-1.0),D3DCOLOR(0xffff0000),D3DXVECTOR2(0.0,0.0) },
	{ D3DXVECTOR3(0.5, 0.5,-0.5),D3DXVECTOR3(0.0,0.0,-1.0),D3DCOLOR(0xffff0000),D3DXVECTOR2(0.25,0.0) },
	{ D3DXVECTOR3(-0.5,-0.5,-0.5),D3DXVECTOR3(0.0,0.0,-1.0),D3DCOLOR(0xffff0000),D3DXVECTOR2(0.0,0.25) },

	//{ D3DXVECTOR3(0.5, 0.5,-0.5),D3DXVECTOR3(0.0,0.0,-1.0),D3DCOLOR(0xffff0000),D3DXVECTOR2(0.25,0.0) },
	{ D3DXVECTOR3(0.5,-0.5,-0.5),D3DXVECTOR3(0.0,0.0,-1.0),D3DCOLOR(0xffff0000),D3DXVECTOR2(0.25,0.25) },
	//{ D3DXVECTOR3(-0.5,-0.5,-0.5),D3DXVECTOR3(0.0,0.0,-1.0),D3DCOLOR(0xffff0000),D3DXVECTOR2(0.0,0.25) },

	//�@�E
	{ D3DXVECTOR3(0.5, 0.5,-0.5),D3DXVECTOR3(1.0,0.0,0.0),D3DCOLOR(0xff00ff00),D3DXVECTOR2(0.25,0.0) },
	{ D3DXVECTOR3(0.5, 0.5, 0.5),D3DXVECTOR3(1.0,0.0,0.0),D3DCOLOR(0xff00ff00),D3DXVECTOR2(0.5,0.0) },
	{ D3DXVECTOR3(0.5,-0.5,-0.5),D3DXVECTOR3(1.0,0.0,0.0),D3DCOLOR(0xff00ff00),D3DXVECTOR2(0.25,0.25) },

	//{ D3DXVECTOR3(0.5, 0.5, 0.5),D3DXVECTOR3(1.0,0.0,0.0),D3DCOLOR(0xff00ff00),D3DXVECTOR2(0.5,0.0) },
	{ D3DXVECTOR3(0.5,-0.5, 0.5),D3DXVECTOR3(1.0,0.0,0.0),D3DCOLOR(0xff00ff00),D3DXVECTOR2(0.5,0.25) },
	//{ D3DXVECTOR3(0.5,-0.5,-0.5),D3DXVECTOR3(1.0,0.0,0.0),D3DCOLOR(0xff00ff00),D3DXVECTOR2(0.25,0.25) },

	//�@��
	{ D3DXVECTOR3(-0.5, 0.5, 0.5),D3DXVECTOR3(0.0,1.0,0.0),D3DCOLOR(0xff0000ff),D3DXVECTOR2(0.5,0.0) },
	{ D3DXVECTOR3(0.5, 0.5, 0.5),D3DXVECTOR3(0.0,1.0,0.0),D3DCOLOR(0xff0000ff),D3DXVECTOR2(0.75,0.0) },
	{ D3DXVECTOR3(-0.5, 0.5,-0.5),D3DXVECTOR3(0.0,1.0,0.0),D3DCOLOR(0xff0000ff),D3DXVECTOR2(0.5,0.25) },

	//{ D3DXVECTOR3(0.5, 0.5, 0.5),D3DXVECTOR3(0.0,1.0,0.0),D3DCOLOR(0xff0000ff),D3DXVECTOR2(0.75,0.0) },
	{ D3DXVECTOR3(0.5 ,0.5,-0.5),D3DXVECTOR3(0.0,1.0,0.0),D3DCOLOR(0xff0000ff),D3DXVECTOR2(0.75,0.25) },
	//{ D3DXVECTOR3(-0.5, 0.5,-0.5),D3DXVECTOR3(0.0,1.0,0.0),D3DCOLOR(0xff0000ff),D3DXVECTOR2(0.5,0.25) },

	//�@��
	{ D3DXVECTOR3(0.5, 0.5, 0.5),D3DXVECTOR3(0.0,0.0,1.0),D3DCOLOR(0xffffff00),D3DXVECTOR2(0.75,0.0) },
	{ D3DXVECTOR3(-0.5, 0.5, 0.5),D3DXVECTOR3(0.0,0.0,1.0),D3DCOLOR(0xffffff00),D3DXVECTOR2(1.0,0.0) },
	{ D3DXVECTOR3(0.5,-0.5, 0.5),D3DXVECTOR3(0.0,0.0,1.0),D3DCOLOR(0xffffff00),D3DXVECTOR2(0.75,0.25) },

	//{ D3DXVECTOR3(-0.5, 0.5, 0.5),D3DXVECTOR3(0.0,0.0,1.0),D3DCOLOR(0xffffff00),D3DXVECTOR2(1.0,0.0) },
	{ D3DXVECTOR3(-0.5,-0.5, 0.5),D3DXVECTOR3(0.0,0.0,1.0),D3DCOLOR(0xffffff00),D3DXVECTOR2(1.0,0.25) },
	//{ D3DXVECTOR3(0.5,-0.5, 0.5),D3DXVECTOR3(0.0,0.0,1.0),D3DCOLOR(0xffffff00),D3DXVECTOR2(0.75,0.25) },

	//�@��
	{ D3DXVECTOR3(-0.5, 0.5, 0.5),D3DXVECTOR3(-1.0,0.0,0.0),D3DCOLOR(0xffff00ff),D3DXVECTOR2(0.0,0.25) },
	{ D3DXVECTOR3(-0.5, 0.5,-0.5),D3DXVECTOR3(-1.0,0.0,0.0),D3DCOLOR(0xffff00ff),D3DXVECTOR2(0.25,0.25) },
	{ D3DXVECTOR3(-0.5,-0.5, 0.5),D3DXVECTOR3(-1.0,0.0,0.0),D3DCOLOR(0xffff00ff),D3DXVECTOR2(0.0,0.5) },

	//{ D3DXVECTOR3(-0.5, 0.5,-0.5),D3DXVECTOR3(-1.0,0.0,0.0),D3DCOLOR(0xffff00ff),D3DXVECTOR2(0.25,0.25) },
	{ D3DXVECTOR3(-0.5,-0.5,-0.5),D3DXVECTOR3(-1.0,0.0,0.0),D3DCOLOR(0xffff00ff),D3DXVECTOR2(0.25,0.5) },
	//{ D3DXVECTOR3(-0.5,-0.5, 0.5),D3DXVECTOR3(-1.0,0.0,0.0),D3DCOLOR(0xffff00ff),D3DXVECTOR2(0.0,0.5) },

	//�@��
	{ D3DXVECTOR3(-0.5,-0.5,-0.5),D3DXVECTOR3(0.0,-1.0,0.0),D3DCOLOR(0xff00ffff),D3DXVECTOR2(0.25,0.25) },
	{ D3DXVECTOR3(0.5 ,-0.5,-0.5),D3DXVECTOR3(0.0,-1.0,0.0),D3DCOLOR(0xff00ffff),D3DXVECTOR2(0.5,0.25) },
	{ D3DXVECTOR3(-0.5,-0.5, 0.5),D3DXVECTOR3(0.0,-1.0,0.0),D3DCOLOR(0xff00ffff),D3DXVECTOR2(0.25,0.5) },

	//{ D3DXVECTOR3(0.5,-0.5,-0.5),D3DXVECTOR3(0.0,-1.0,0.0),D3DCOLOR(0xff00ffff),D3DXVECTOR2(0.5,0.25) },
	{ D3DXVECTOR3(0.5,-0.5, 0.5),D3DXVECTOR3(0.0,-1.0,0.0),D3DCOLOR(0xff00ffff),D3DXVECTOR2(0.5,0.5) },
	//{ D3DXVECTOR3(-0.5,-0.5, 0.5),D3DXVECTOR3(0.0,-1.0,0.0),D3DCOLOR(0xff00ffff),D3DXVECTOR2(0.25,0.5) },
};



static float angle = 0;
static float anglex = 0.0f;
static float anglez = 0.0f;

static int count = 0;

static float x = 0.0f;
static float z = 0.0f;
static float y = 0.0f;

static float movex = 0.0f;
static float movez = 0.0f;
static float movey = 0.0f;


static bool MovecheckW = false;
static bool MovecheckS = false;
static bool MovecheckA = false;
static bool MovecheckD = false;

static bool MoveCheck = false;

static D3DCOLOR g_Color = 0xffffffff;

static D3DXMATRIX g_mtxWorldSai;
static D3DXMATRIX g_mtxRotationSai;
static D3DXMATRIX g_mtxTotalRotation;
static D3DXMATRIX g_mtxTranslation;
//=============================================================================
//	����������
//=============================================================================

void Cube_Initialize(void)
{
	

	for (int i = 0;i < 36;i++)
	{
		g_cube[i].color = g_Color;
	}
	x = 0.5f;
	y = 0.5f;
	z = -3.5f;
	
	D3DXMatrixTranslation(&g_mtxWorldSai, x, y, z);
	D3DXMatrixIdentity(&g_mtxTotalRotation);
	D3DXMatrixIdentity(&g_mtxRotationSai);
	D3DXMatrixIdentity(&g_mtxTranslation);
	LPDIRECT3DDEVICE9 g_pD3DDevice = mochi_GetDevice();
	// ���_�o�b�t�@�̊m��
	g_pD3DDevice->CreateVertexBuffer(sizeof(CubeVertex3D) * 24, D3DUSAGE_WRITEONLY, FVF_CUBE_VERTEX3D, D3DPOOL_MANAGED, &g_pVertexBuffer, NULL);
	/*
	1 ���_�̃T�C�Y
	2 �p�r
	3 FVF
	4 VRAM��̃������̊Ǘ�
	5 �������̏ꏊ
	6 NULL(������Ȃ��Ƃ���NULL������)
	*/

	// �C���f�b�N�X�o�b�t�@�̊m��
	g_pD3DDevice->CreateIndexBuffer(sizeof(WORD) * 36, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);
	/*
	1 �C���f�b�N�X�̃T�C�Y
	2 �p�r
	3 �C���f�b�N�X�̃t�H�[�}�b�g(16�r�b�g��32�r�b�g)
	4 VRAM��̃������̊Ǘ�
	5 �������̏ꏊ
	6 NULL(������Ȃ��Ƃ���NULL������)
	*/




	// ���z�A�h���X�@
	CubeVertex3D *pv;
	// ���_�o�b�t�@�̃��b�N
	g_pVertexBuffer->Lock(0, 0, (void**)&pv, 0);
	/*
	1 �ǂ�����
	2 0�ł���
	3 ���z�A�h���X������
	4 0�ł���
	*/
	memcpy(pv, g_cube, sizeof(g_cube));
	g_pVertexBuffer->Unlock();

	// ���z�A�h���X�@
	WORD *Ipv;
	// �C���f�b�N�X�o�b�t�@�̃��b�N
	g_pIndexBuffer->Lock(0, 0, (void**)&Ipv, 0);
	/*
	1 �ǂ�����
	2 0�ł���
	3 ���z�A�h���X������
	4 0�ł���
	*/
	for (int i = 0;i < 6;i++) 
	{
		Ipv[(i * 6)] = (i * 4) + 0;
		Ipv[(i * 6) + 1] = (i * 4) + 1;
		Ipv[(i * 6) + 2] = (i * 4) + 2;
		Ipv[(i * 6) + 3] = (i * 4) + 1;
		Ipv[(i * 6) + 4] = (i * 4) + 3;
		Ipv[(i * 6) + 5] = (i * 4) + 2;
	}



	g_pIndexBuffer->Unlock();
}

//=============================================================================
//	�I������
//=============================================================================

void Cube_Finalize(void)
{
	// �C���f�b�N�X�o�b�t�@�̉��
	if (g_pIndexBuffer != NULL)
	{
		g_pIndexBuffer->Release();
		g_pIndexBuffer = NULL;
	}

	// ���_�o�b�t�@�̉��
	if (g_pVertexBuffer != NULL)
	{
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}

}

//=============================================================================
//	�X�V����
//=============================================================================

void Cube_Updata(void)
{


	//�@��������
	if (Keyboard_IsTrigger(DIK_T))
	{
		MovecheckW = true;
	}
	if (Keyboard_IsTrigger(DIK_G))
	{
		MovecheckS = true;	
	}
	if (Keyboard_IsTrigger(DIK_F))
	{
		MovecheckA = true;
	}
	if (Keyboard_IsTrigger(DIK_H))
	{
		MovecheckD = true;
	}

	if (Keyboard_IsPress(DIK_I) && (Keyboard_IsPress(DIK_LSHIFT)))
	{
		g_mtxTranslation *= Move(FLONT);
	}
	if (Keyboard_IsPress(DIK_K) && (Keyboard_IsPress(DIK_LSHIFT)))
	{
		g_mtxTranslation *= Move(BACK);
	}
	if (Keyboard_IsPress(DIK_L) && (Keyboard_IsPress(DIK_LSHIFT)))
	{
		g_mtxTranslation *= Move(RIGHT);
	}
	if (Keyboard_IsPress(DIK_J) && (Keyboard_IsPress(DIK_LSHIFT)))
	{
		g_mtxTranslation *= Move(LEFT);
	}

	if (MovecheckW)
	{
		count++;

		if (count <= 20)
		{
			movez = SAI_MOVE*count;
			angle = SAI_ROT * count;
			movey = sin(D3DXToRadian(angle)) - movez + ADJUST;
			D3DXMatrixRotationX(&g_mtxRotationSai, D3DXToRadian(angle));
		}
		else
		{
			count = 0;
			MovecheckW = false;
			z += 1.0;
			angle = 0;
			movez = 0;
		}
	}

	if (MovecheckS)
	{
		count++;

		if (count <= 20)
		{
			movez = -SAI_MOVE*count;
			angle = -SAI_ROT * count;
			movey = sin(D3DXToRadian(-angle)) + movez + ADJUST;
			D3DXMatrixRotationX(&g_mtxRotationSai, D3DXToRadian(angle));
		}
		else
		{
			count = 0;
			MovecheckS = false;
			z -= 1.0;
			angle = 0;
			movez = 0;
		}
	}
	if (MovecheckA)
	{
		count++;

		if (count <= 20)
		{
			movex = -SAI_MOVE*count;
			angle = SAI_ROT * count;
			movey = sin(D3DXToRadian(angle)) + movex + ADJUST;
			D3DXMatrixRotationZ(&g_mtxRotationSai, D3DXToRadian(angle));
		}
		else
		{
			count = 0;
			MovecheckA = false;
			x -= 1.0;
			angle = 0;
			movex = 0;
		}
	}
	if (MovecheckD)
	{
		count++;

		if (count <= 20)
		{
			movex = SAI_MOVE*count;
			angle = -SAI_ROT * count;
			movey = sin(D3DXToRadian(-angle)) - movex + ADJUST;
			D3DXMatrixRotationZ(&g_mtxRotationSai, D3DXToRadian(angle));
		}
		else
		{
			count = 0;
			MovecheckD = false;
			x += 1.0;
			angle = 0;
			movex = 0;
		}
	}
	
}

//=============================================================================
//	�`�揈��
//=============================================================================

void Cube_Draw(void)
{

	//�f�o�C�X
	LPDIRECT3DDEVICE9 g_pD3DDevice = mochi_GetDevice();

	g_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
	g_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);

	// ���[���h���W�ϊ��s��
	D3DXMATRIX mtxWorld;		// 4*4�s��@d3dx9.h�K�v
	
	
	// ���s
	D3DXMATRIX mtxTranslation;
	D3DXMATRIX mtxTranslation2;

	// ��]
	D3DXMATRIX mtxRotation;
	D3DXMATRIX mtxRotation2;
	/*
	D3DXMatrixRotationX(�A�h���X, �A���O��);   �c���[��
	D3DXMatrixRotationY(�A�h���X, �A���O��);   �����[��
	D3DXMatrixRotationZ(�A�h���X, �A���O��);   
	D3DXMatrixRotationYawPitchRoll(�A�h���X,y,x,z)
	D3DXMatrixRotationAxis(�A�h���X,���x�N�g���̃A�h���X,�A���O��);
	*/


	if ((MovecheckW)|| (MovecheckA) || (MovecheckS) || (MovecheckD))
	{
		D3DXMatrixTranslation(&mtxTranslation, x + movex, y + movey, z + movez);
		g_mtxWorldSai = g_mtxTotalRotation*g_mtxRotationSai*mtxTranslation;
		if (count >= 20)
		{
			g_mtxTotalRotation *= g_mtxRotationSai;
		}
	}
	
	D3DXMatrixTranslation(&mtxTranslation2, 0, 0.5,0);
	mtxWorld = mtxTranslation2*g_mtxTranslation;

	//	���[���h�ϊ��s��ݒ�
	

	g_pD3DDevice->SetFVF(FVF_CUBE_VERTEX3D);		//	FVF���f�o�C�X�ɐݒ�
	g_pD3DDevice->SetTexture(0, Texture_GetTexture(0));
	
	/*g_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	g_pD3DDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(CubeVertex3D));
	g_pD3DDevice->SetIndices(g_pIndexBuffer);
	g_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);*/

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldSai);
	g_pD3DDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(CubeVertex3D));
	g_pD3DDevice->SetIndices(g_pIndexBuffer);
	g_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);

	/*g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 12, g_cube, sizeof(CubeVertex3D));


	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld[1]);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 12, g_cube, sizeof(CubeVertex3D));*/
	/*
	��1�����@�ǂ�Ȍ`��
	��2�����@�v���~�e�B�u���@�O�p�`������������
	��3����  ���_�f�[�^�̐擪�A�h���X
	��4�����@���_�f�[�^�\���̂̑傫��
	*/

	

}