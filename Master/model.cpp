
//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================
#include <d3dx9.h>
#include "mochi_d3d.h"
#include "common.h"

#include "input.h"
#include "move.h"
//=============================================================================
//	�萔��`
//=============================================================================

#define MAX_MODEL (10)

//=============================================================================
//	�O���[�o���錾
//=============================================================================

LPD3DXMESH g_pD3DXMesh[MAX_MODEL];	//	���b�V�����󂯎��ϐ�
//LPD3DXBUFFER g_pD3DXAdjacencyBuffer;	//	�אڐ������󂯎��ϐ�
static DWORD g_dwNumMaterials[MAX_MODEL];	//	�}�e���A���̑���	�`�悷���
LPD3DXBUFFER g_pD3DXMtrBuffer[MAX_MODEL];	//	�}�e���A�������󂯎��ϐ�
/*
	����3�𕡐�������
	�����[�X
		LPD3DXMESH�@LPD3DXBUFFER
*/

//static LPDIRECT3DDEVICE9 g_pD3DDevice;

static LPDIRECT3DTEXTURE9 *g_pTexures[MAX_MODEL] = { NULL };
static D3DMATERIAL9 *g_pd3dMaterials[MAX_MODEL] = { NULL };

static D3DXMATRIX g_mtxTranslation[MAX_MODEL];
static D3DXMATRIX g_mtxRotation;
static float g_Angle = 0.0f;

//	���f���f�[�^�̍\����
typedef struct 
{
	char filename[256];
	
}MaterialFileData;

//	�g���������f���̐���������
static const MaterialFileData TEXTURE_FILES[] = {
	{ "bananaZ.x" },
	{"emi-ru2.x"},
	{"smart_emiru.x"}
};

static D3DXMATRIX g_mtxKeepTranslation;

//	���f���ǂݍ���
void Model_Load(int index)		//	������������index��߂��֐��ɂ���
{
	LPDIRECT3DDEVICE9 g_pD3DDevice = mochi_GetDevice();

	HRESULT hr;
	hr = D3DXLoadMeshFromX(TEXTURE_FILES[index].filename, D3DXMESH_MANAGED, g_pD3DDevice, NULL, &g_pD3DXMtrBuffer[index], NULL, &g_dwNumMaterials[index], &g_pD3DXMesh[index]);
	if (FAILED(hr))
	{
		MessageBox(NULL, "���f���f�[�^��ǂݍ��߂܂���ł���", "�m�F", MB_OK);
	}
		/*
			��1�����@�t�@�C����
			��2�����@65535�ȏ�̒��_���K�v�Ȃ�
					 D3DXMESH_MANAGED | D3DXMESH_WRITEONLY | D3DXMESH_32BIT �ɂ���
			��3�����@�f�o�C�X
			��4�����@NULL�@g_pD3DXAdjacencyBuffer
			��5�����@g_pD3DXMtrBuffer
			��6�����@dwNumMaterials
			��7�����@g_pD3DXMesh
		*/

	//	�}�e���A���ۑ��p�z��̊m��
	g_pd3dMaterials[index] = new D3DMATERIAL9[g_dwNumMaterials[index]];
	g_pTexures[index] = new LPDIRECT3DTEXTURE9[g_dwNumMaterials[index]];
	
	//	�}�e���A�����o�b�t�@�̃|�C���^�擾
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)g_pD3DXMtrBuffer[index]->GetBufferPointer();

	//	�e�}�e���A������ۑ�
	for (int i = 0;i < g_dwNumMaterials[index];i++)
	{
		g_pd3dMaterials[index][i] = d3dxMaterials[i].MatD3D;	//	X�t�@�C���̃}�e���A���J���[�̃R�s�[
		/*
			�f�B�t�[�Y		
			�A���r�G���g	
			�G�~�b�V�u		���C�g�֌W�Ȃ��@���Ȕ���
			�X�y�L����
		*/
		g_pd3dMaterials[index][i].Ambient = g_pd3dMaterials[index][i].Diffuse;

		//	�e�N�X�`���̓ǂݍ���
		if (d3dxMaterials[i].pTextureFilename == NULL)	//	�e�N�X�`�����Ȃ��}�e���A���̓t�@�C�����Ȃ�
		{
			g_pTexures[index][i] = NULL;
		}
		else
		{
			hr = D3DXCreateTextureFromFile(g_pD3DDevice, d3dxMaterials[i].pTextureFilename, &g_pTexures[index][i]);
			if (FAILED(hr))
			{
				g_pTexures[index][i] = NULL;
				MessageBox(NULL, "�e�N�X�`���f�[�^��ǂݍ��߂܂���ł���", "�m�F", MB_OK);
			}
		}
	}

	//	X�t�@�C������ǂݍ��񂾃}�e���A�����̃o�b�t�@�����
	if (g_pD3DXMtrBuffer)
	{
		g_pD3DXMtrBuffer[index]->Release();
	}


	D3DXMatrixTranslation(&g_mtxTranslation[index],0,1,0);
	D3DXMatrixIdentity(&g_mtxRotation);
	g_mtxKeepTranslation = g_mtxTranslation[index];
}

//	�`�揈��
void Model_Draw(int index)		//	�����������������ς���@�s��
{
	LPDIRECT3DDEVICE9 g_pD3DDevice = mochi_GetDevice();

	g_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	g_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);

	//	���[���h�ϊ��s��
	D3DXMATRIX mtxWorld;		// 4*4�s��@d3dx9.h�K�v
	D3DXMATRIX mtxScaling;
	D3DXMATRIX mtxTranslation;
	//D3DXMatrixTranslation(&mtxTranslation, 0, 1.5, 0);
	D3DXMatrixIdentity(&mtxWorld);	// �A�h���X����ƒP�ʍs�������Ă����
	D3DXMatrixScaling(&mtxScaling, 0.5f, 1.0f, 0.5f);
	mtxWorld = mtxScaling * g_mtxRotation * g_mtxTranslation[index];
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	for (int i = 0;i < g_dwNumMaterials[index];i++)
	{
		g_pD3DDevice->SetMaterial(&g_pd3dMaterials[index][i]);
		g_pD3DDevice->SetTexture(0, g_pTexures[index][i]);
		g_pD3DXMesh[index]->DrawSubset(i);
	}
}

// �`�揈��
void Model_Draw(int index, D3DXMATRIX mtxWorld)		//	�����������������ς���@�s��
{
	LPDIRECT3DDEVICE9 g_pD3DDevice = mochi_GetDevice();

	g_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	g_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	for (int i = 0;i < g_dwNumMaterials[index];i++)
	{
		g_pD3DDevice->SetMaterial(&g_pd3dMaterials[index][i]);
		g_pD3DDevice->SetTexture(0, g_pTexures[index][i]);
		g_pD3DXMesh[index]->DrawSubset(i);
	}
}

//	�I������
void Model_Finalize(void)	//	���f���f�[�^�̊J���@������������S���������ǂꂩ������
{
	for (int i = 0;i < MAX_MODEL;i++)
	{
		if (g_pTexures[i] != NULL)
		{
			delete[]g_pTexures[i];
		}
		if (g_pd3dMaterials[i] != NULL)
		{
			delete[]g_pd3dMaterials[i];
			
		}
		if (g_pD3DXMesh[i] != NULL)
		{
			g_pD3DXMesh[i]->Release();
		}
	}
}

void Model_Finalize(int index)	//	���f���f�[�^�̊J���@������������S���������ǂꂩ������
{
	if (g_pTexures[index] != NULL)
	{
		delete[]g_pTexures[index];
	}
	if (g_pd3dMaterials[index] != NULL)
	{
		delete[]g_pd3dMaterials[index];
	}
	if (g_pD3DXMesh[index] != NULL)
	{
		g_pD3DXMesh[index]->Release();
	}
}

void Model_Updata(int index)
{
	if (Keyboard_IsPress(DIK_W))
	{
		g_mtxTranslation[index] *= Move(FLONT);

	}
	if (Keyboard_IsPress(DIK_S))
	{
		g_mtxTranslation[index] *= Move(BACK);
	}
	if (Keyboard_IsPress(DIK_D))
	{
		g_mtxTranslation[index] *= Move(RIGHT);
	}
	if (Keyboard_IsPress(DIK_A))
	{
		g_mtxTranslation[index] *= Move(LEFT);
	}

	if (Keyboard_IsPress(DIK_L) && (Keyboard_IsPress(DIK_LALT)))
	{
		g_Angle--;
		D3DXMatrixRotationY(&g_mtxRotation, D3DXToRadian(g_Angle));
	}
	if (Keyboard_IsPress(DIK_J) && (Keyboard_IsPress(DIK_LALT)))
	{
		g_Angle++;
		D3DXMatrixRotationY(&g_mtxRotation, D3DXToRadian(g_Angle));
	}

	if (45.0*45.0 < (g_mtxTranslation[index]._41*g_mtxTranslation[index]._41) + (g_mtxTranslation[index]._43 * g_mtxTranslation[index]._43))
	{
		g_mtxTranslation[index] = g_mtxKeepTranslation;
	}
	else
	{
		g_mtxKeepTranslation = g_mtxTranslation[index];
	}

}

D3DXMATRIX get_modelPos(int index)
{
	return g_mtxTranslation[index];
}