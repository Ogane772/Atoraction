/*
#include "shadow.h"
#include "CTexture.h"

#define SHADOW_MAX (90)
#define FVF_VERTEX3D (D3DFVF_XYZ |D3DFVF_DIFFUSE|D3DFVF_TEX1)

typedef struct Vertex3D_tag
{
	D3DXVECTOR3 potision;//D3DXVECTOR3��X,Y,Z
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
}Vertex3D;

static const Vertex3D v[] = {
	//�O                             //���@���x�N�g��(�����͕K��1�ɂ���)
	{ D3DXVECTOR3(-0.5f,0.0f,0.5f) ,D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.0f,0.0f) },//�Ō�̓��UV���W
	{ D3DXVECTOR3(0.5f,0.0f,0.5f)  ,D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(1.0f,0.0f) },
	{ D3DXVECTOR3(-0.5f,0.0f,-0.5f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,1.0f) },
	{ D3DXVECTOR3(0.5f,0.0f,-0.5f) ,D3DCOLOR_RGBA(255,255,255,255),  D3DXVECTOR2(1.0f,1.0f) },

}; typedef struct Shadow_tag
{
	float *cx, *cz;//���W �����N������K�v������̂Ń|�C���^�ɂ���
	float sx, sz;//�g�嗦
	bool create;//�t���O
}Shadow;

static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer2 = NULL;
static Shadow shadow[SHADOW_MAX] = { 0 };//�e�̍ő吔���쐬
static Vertex3D *g_pVertex;

void Shadow_Initialize(void)
{
	//�Ƃɂ����O���[�o���ϐ��������ŏ�����
	for (int i = 0; i < SHADOW_MAX; i++)
	{
		shadow[i].cx = NULL;
		shadow[i].cz = NULL;
		shadow[i].sx = 0.0f;
		shadow[i].sz = 0.0f;
		shadow[i].create = false;
	}

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice) return;

	// ���_�o�b�t�@�̊m�ہi���_�S���j
	pDevice->CreateVertexBuffer(sizeof(v), D3DUSAGE_WRITEONLY, FVF_VERTEX3D, D3DPOOL_MANAGED, &g_pVertexBuffer, NULL);
	// �C���f�b�N�X�o�b�t�@�̊m�ہi�C���f�b�N�X�U���j
	pDevice->CreateIndexBuffer(sizeof(WORD) * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer2, NULL);

	// ���_�C���f�b�N�X�o�b�t�@�֒��_�C���f�b�N�X�̏�������

	g_pVertexBuffer->Lock(0, 0, (void**)&g_pVertex, 0);
	memcpy(g_pVertex, v, sizeof(v));
	g_pVertexBuffer->Unlock();

	WORD index[] = {//1��
		0,1,2,
		1,3,2,
	};
	WORD* pIndex;
	g_pIndexBuffer2->Lock(0, 0, (void**)&pIndex, 0);
	memcpy(pIndex, index, sizeof(index));
	g_pIndexBuffer2->Unlock();
}

void Shadow_Create(float* x, float* y, float scaleX, float scaleY, int* shadow_number)
{
	for (int i = 0; i < SHADOW_MAX; i++)
	{
		if (!shadow[i].create)
		{
			shadow[i].cx = x;
			shadow[i].cz = y;
			shadow[i].sx = scaleX;
			shadow[i].sz = scaleY;
			shadow[i].create = true;
			*shadow_number = i;
			break;
		}
	}
}

void Shadow_Finalize(void)
{

}

void Shadow_Update(void)
{

}

void Shadow_Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();//�Q�b�^�[
	/*4�~4�s��*//*D3DXMATRIX mtx;
	/*4�~4�s��*///D3DXMATRIX mtx2;
	/*4�~4�s��*///D3DXMATRIX mtx3;
	/*4�~4�s��*///D3DXMATRIX mtx4;
	//D3DXMatrixTranslation(&mtx, 1, 1, 1);//���s�ړ� x y z
	//D3DXMatrixRotationYawPitchRoll(&mtx2, D3DXToRadian(radian), D3DXToRadian(radian), D3DXToRadian(radian));
	//D3DXMatrixRotationX(&mtx2, D3DXToRadian(radian));
	
	/*4�~4�s��*//*D3DXMATRIX mtxworld;
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);//���C�gOFF
	for (int i = 0; i < SHADOW_MAX; i++)
	{
		if (shadow[i].create)
		{
			//���Z����(�ݒ肵�ā��e����������߂�(�A���t�@�u�����h���s��))
			//D3DXMatrixRotationY(mtx2, D3DXToRadian(radian));
			D3DXMatrixIdentity(&mtxworld);//�P�ʍs������B�P�ʍs������֐��ɂ͑��Identity���t���Ă�
			D3DXMatrixTranslation(&mtx, *shadow[i].cx, 0.001f, *shadow[i].cz);//���s�ړ� x y z
			D3DXMatrixScaling(&mtx2, shadow[i].sx, 0.1f, shadow[i].sz);//�g��@x y z�̊g��
			D3DXMatrixRotationY(&mtx3, D3DXToRadian(0));

			mtxworld = mtx3 * mtx2 * mtx;//���_�����S�I
			pDevice->SetTransform(D3DTS_WORLD, &mtxworld);//�Z�b�g�����s������[���h���W�ɂ���

			pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_EFF));

			pDevice->SetFVF(FVF_VERTEX3D);

			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);//�����Z����ʂ�SRCALPHA�Œ���

			pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(Vertex3D)); // ���_�o�b�t�@�̐ݒ�
			pDevice->SetIndices(g_pIndexBuffer2);

			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 12);

			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);			
		}
	}
}

void Shadow_Destroy(int number)
{
	shadow[number].cx = NULL;
	shadow[number].cz = NULL;
	shadow[number].sx = 0.0f;
	shadow[number].sz = 0.0f;
	shadow[number].create = false;
}*/