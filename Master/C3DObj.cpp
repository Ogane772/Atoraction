//////////////////////////////////////////////////
////
////	3D�I�u�W�F�N�g�N���X
////
//////////////////////////////////////////////////

#include "C3DObj.h"
#include "debug_font.h"
#include "CTexture.h"

//=============================================================================
//	�ÓI�ϐ�
//===========================================================================
C3DObj *C3DObj::p3DObj[MAX_GAMEOBJ];
int C3DObj::m_3DObjNum = 0;

C3DObj::MaterialFileData C3DObj::MODEL_FILES[] = {
	{ "asset/model/emi-ru2.x" },
	{ "asset/model/zako.x" },
	{ "asset/model/boss.x" },
	{ "asset/model/CoffeeCup.blend.x" },
	{ "asset/model/dish.blend.x" },
	{ "asset/model/enban.x" },
	{ "asset/model/hasira.x" },
	{ "asset/model/ferris.x" },
	{ "asset/model/coaster.x" },
};

int C3DObj::MODEL_FILES_MAX = sizeof(C3DObj::MODEL_FILES) / sizeof(MODEL_FILES[0]);


LPD3DXMESH C3DObj::m_pD3DXMesh[sizeof(C3DObj::MODEL_FILES) / sizeof(MODEL_FILES[0])] = {};
DWORD C3DObj::m_dwNumMaterials[sizeof(C3DObj::MODEL_FILES) / sizeof(MODEL_FILES[0])] = {};
LPD3DXBUFFER C3DObj::m_pD3DXMtrBuffer[sizeof(C3DObj::MODEL_FILES) / sizeof(MODEL_FILES[0])] = {};
LPDIRECT3DTEXTURE9 *C3DObj::m_pTexures[sizeof(C3DObj::MODEL_FILES) / sizeof(MODEL_FILES[0])] = {};
D3DMATERIAL9 *C3DObj::m_pd3dMaterials[sizeof(C3DObj::MODEL_FILES) / sizeof(MODEL_FILES[0])] = {};

//=============================================================================
//	����
//=============================================================================
C3DObj::C3DObj()
{
	for (m_3DObjIndex = 0; m_3DObjIndex < MAX_GAMEOBJ; m_3DObjIndex++)
	{
		if (p3DObj[m_3DObjIndex] == NULL)
		{
			p3DObj[m_3DObjIndex] = this;
			m_3DObjType = TYPE_etc;
			m_3DObjNum++;
			break;
		}
	}
	// ���[�N�i�[���s
	if (m_3DObjIndex >= MAX_GAMEOBJ)
	{
		m_3DObjIndex = -1;
	}

	
}

C3DObj::C3DObj(int type)
{
	// ���[�N�Ɏ������g(this)���i�[
	for (m_3DObjIndex = 0; m_3DObjIndex < MAX_GAMEOBJ; m_3DObjIndex++)
	{
		if (p3DObj[m_3DObjIndex] == NULL)
		{
			p3DObj[m_3DObjIndex] = this;
			m_3DObjType = type;
			m_3DObjNum++;
			break;
		}
	}
	// ���[�N�i�[���s
	if (m_3DObjIndex >= MAX_GAMEOBJ)
	{
		m_3DObjIndex = -1;
	}

	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixIdentity(&m_mtxTranslation);
	D3DXMatrixIdentity(&m_mtxRotation);
	D3DXMatrixIdentity(&m_mtxScaling);
	m_Enable = false;
}
//=============================================================================
//	�j��
//=============================================================================
C3DObj::~C3DObj()
{
	m_3DObjNum--;
	p3DObj[m_3DObjIndex] = NULL;
}





//=============================================================================
// �S�I�u�W�F�N�g�X�V
//=============================================================================
void C3DObj::UpdateAll()
{
	for (int i = 0; i < MAX_GAMEOBJ; i++)
	{
		// �|�����[�t�B�Y���ɂ���Ĕh���N���X��Update()���Ă΂��
		if (p3DObj[i])
		{
			p3DObj[i]->Update();
		}
	}
}

//=============================================================================
// �S�I�u�W�F�N�g�`��
//=============================================================================
void C3DObj::DrawAll()
{
	for (int i = 0; i < MAX_GAMEOBJ; i++)
	{
		// �|�����[�t�B�Y���ɂ���Ĕh���N���X��Draw()���Ă΂��
		if (p3DObj[i])
		{
			p3DObj[i]->Draw();
		}
	}
}



//=============================================================================
// �S�I�u�W�F�N�g�폜
//=============================================================================
void C3DObj::DeleteAll()
{
	for (int i = 0; i < MAX_GAMEOBJ; i++)
	{
		if (p3DObj[i])
		{
			delete p3DObj[i];
			//p3DObj[i] = NULL;
		}
	}
}


//=============================================================================
// �C���X�^���X�擾
//=============================================================================
C3DObj *C3DObj::Get(int nIdx)
{
	// �C���f�b�N�X���͈͊O
	if (p3DObj[nIdx])
	{
		return p3DObj[nIdx];
	}
	return NULL;
}


//=============================================================================
// �I�u�W�F�N�g�폜
//=============================================================================
void C3DObj::C3DObj_delete(void)
{
	C3DObj *pobj = Get(Get_3DObjIndex());
	delete pobj;
}



//=============================================================================
// ���f���ǂݍ���
//=============================================================================
void C3DObj::Model_Load(void)
{


	HRESULT hr;
	for (int index = 0;index < MODEL_FILES_MAX;index++)
	{
		hr = D3DXLoadMeshFromX(MODEL_FILES[index].filename, D3DXMESH_MANAGED, m_pD3DDevice, NULL, &m_pD3DXMtrBuffer[index], NULL, &m_dwNumMaterials[index], &m_pD3DXMesh[index]);
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
		m_pd3dMaterials[index] = new D3DMATERIAL9[m_dwNumMaterials[index]];
		m_pTexures[index] = new LPDIRECT3DTEXTURE9[m_dwNumMaterials[index]];

		//	�}�e���A�����o�b�t�@�̃|�C���^�擾
		D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)m_pD3DXMtrBuffer[index]->GetBufferPointer();

		//	�e�}�e���A������ۑ�
		for (int i = 0;i < m_dwNumMaterials[index];i++)
		{
			m_pd3dMaterials[index][i] = d3dxMaterials[i].MatD3D;	//	X�t�@�C���̃}�e���A���J���[�̃R�s�[
																	/*
																	�f�B�t�[�Y
																	�A���r�G���g
																	�G�~�b�V�u		���C�g�֌W�Ȃ��@���Ȕ���
																	�X�y�L����
																	*/
			m_pd3dMaterials[index][i].Ambient = m_pd3dMaterials[index][i].Diffuse;

			//	�e�N�X�`���̓ǂݍ���
			if (d3dxMaterials[i].pTextureFilename == NULL)	//	�e�N�X�`�����Ȃ��}�e���A���̓t�@�C�����Ȃ�
			{
				m_pTexures[index][i] = NULL;
			}
			else
			{
				hr = D3DXCreateTextureFromFile(m_pD3DDevice, d3dxMaterials[i].pTextureFilename, &m_pTexures[index][i]);
				if (FAILED(hr))
				{
					m_pTexures[index][i] = NULL;
					MessageBox(NULL, "�e�N�X�`���f�[�^��ǂݍ��߂܂���ł���", "�m�F", MB_OK);
				}
			}
		}

		//	X�t�@�C������ǂݍ��񂾃}�e���A�����̃o�b�t�@�����
		if (m_pD3DXMtrBuffer)
		{
			m_pD3DXMtrBuffer[index]->Release();
		}
	}
}


//=============================================================================
// ���f���j��
//=============================================================================
void C3DObj::Model_Finalize(void)	//	���f���f�[�^�̊J���@������������S���������ǂꂩ������
{
	for (int i = 0;i < MODEL_FILES_MAX;i++)
	{
		if (m_pTexures[i] != NULL)
		{
			delete[]m_pTexures[i];
		}
		if (m_pd3dMaterials[i] != NULL)
		{
			delete[]m_pd3dMaterials[i];
		}
		if (m_pD3DXMesh[i] != NULL)
		{
			m_pD3DXMesh[i]->Release();
		}
	}
}

void C3DObj::Model_Finalize(int index)	//	���f���f�[�^�̊J���@������������S���������ǂꂩ������
{
	if (m_pTexures[index] != NULL)
	{
		delete[]m_pTexures[index];
	}
	if (m_pd3dMaterials[index] != NULL)
	{
		delete[]m_pd3dMaterials[index];

	}
	if (m_pD3DXMesh[index] != NULL)
	{
		m_pD3DXMesh[index]->Release();
	}
}



//=============================================================================
// ���f���`��
//=============================================================================
void C3DObj::Model_Draw(int index, D3DXMATRIX mtxWorld)		//	�����������������ς���@�s��
{
	//m_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	//m_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);

	m_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
	m_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	for (int i = 0;i < m_dwNumMaterials[index];i++)
	{
		m_pD3DDevice->SetMaterial(&m_pd3dMaterials[index][i]);
		m_pD3DDevice->SetTexture(0, m_pTexures[index][i]);
		m_pD3DXMesh[index]->DrawSubset(i);
	}
}

void C3DObj::Model_Draw(int index, D3DXMATRIX mtxWorld, int texIndex)		//	�����������������ς���@�s��
{
	//m_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	//m_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);

	m_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
	m_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	m_pD3DDevice->SetTexture(0, CTexture::Texture_GetTexture(texIndex));
	for (int i = 0;i < m_dwNumMaterials[index];i++)
	{
		m_pD3DDevice->SetMaterial(&m_pd3dMaterials[index][i]);
		//m_pD3DDevice->SetTexture(0, m_pTexures[index][i]);
		m_pD3DXMesh[index]->DrawSubset(i);
	}
}




