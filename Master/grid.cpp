//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================

#include <d3dx9.h>
#include "mochi_d3d.h"
#include "common.h"
//=============================================================================
//	�萔��`
//=============================================================================

//=============================================================================
//	�O���[�o���錾
//=============================================================================

//3D�|���S�����_�@�\����
typedef struct
{
	D3DXVECTOR3 pos;	//	���Wx,y,z
	D3DCOLOR color;		//  �F

}GridVertex;

#define FVF_CUBE_VERTEX3D (D3DFVF_XYZ|D3DFVF_DIFFUSE)	//	�\���̂̂������ɏ���

// TRIANGLELIST ���_���W
static GridVertex g_grid[44];


static int angle = 0;

//=============================================================================
//	����������
//=============================================================================

void Grid_Initialize(void)
{
	for (int i = 0;i < 22;i++)
	{
		if (i % 2 == 0)
		{
			g_grid[i].pos = D3DXVECTOR3(-5.0 + i - (i * 0.5), 0, 5.0);
			g_grid[i].color = D3DCOLOR(0xff00ff00);
		}
		else
		{
			g_grid[i].pos = D3DXVECTOR3(-5.0 + ((i - 1) * 0.5), 0, -5.0);
			g_grid[i].color = D3DCOLOR(0xff00ff00);
		}

	}

	for (int i = 0;i < 22;i++)
	{
		if (i % 2 == 0)
		{
			g_grid[i + 22].pos = D3DXVECTOR3(-5.0, 0, -5.0 + i - (i  * 0.5));
			g_grid[i + 22].color = D3DCOLOR(0xff00ff00);
		}
		else
		{
			g_grid[i + 22].pos = D3DXVECTOR3(5.0, 0, -5.0 + ((i - 1)  * 0.5));
			g_grid[i + 22].color = D3DCOLOR(0xff00ff00);
		}

	}
	g_grid[10].color = D3DCOLOR(0xffefb864);
	g_grid[11].color = D3DCOLOR(0xffefb864);
	g_grid[32].color = D3DCOLOR(0xffefb864);
	g_grid[33].color = D3DCOLOR(0xffefb864);
}

//=============================================================================
//	�I������
//=============================================================================

void Grid_Finalize(void)
{

}

//=============================================================================
//	�X�V����
//=============================================================================

void Grid_Updata(void)
{

}

//=============================================================================
//	�`�揈��
//=============================================================================

void Grid_Draw(void)
{

	//�f�o�C�X
	LPDIRECT3DDEVICE9 g_pD3DDevice = mochi_GetDevice();
//	g_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
//	g_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);
	// ���[���h���W�ϊ��s��
	D3DXMATRIX mtxWorld;		// 4*4�s��@d3dx9.h�K�v
	D3DXMatrixIdentity(&mtxWorld);	// �A�h���X����ƒP�ʍs�������Ă����


									//	���[���h�ϊ��s��ݒ�
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);




	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	g_pD3DDevice->SetFVF(FVF_CUBE_VERTEX3D);		//	FVF���f�o�C�X�ɐݒ�


	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, 22, g_grid, sizeof(GridVertex));



	/*
	��1�����@�ǂ�Ȍ`��
	��2�����@�v���~�e�B�u���@�O�p�`������������
	��3����  ���_�f�[�^�̐擪�A�h���X
	��4�����@���_�f�[�^�\���̂̑傫��
	*/
}