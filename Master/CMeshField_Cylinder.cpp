//////////////////////////////////////////////////
////
////	���b�V���t�B�[���h�V�����_�[�N���X
////
//////////////////////////////////////////////////



//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================

#include "CMeshField_Cylinder.h"

//=============================================================================
//	�萔��`
//=============================================================================


//=============================================================================
//	�ÓI�ϐ�
//=============================================================================

CMeshField_Cylinder *CMeshField_Cylinder::m_pMeshField_Cylinder;

//=============================================================================
//	����
//=============================================================================

CMeshField_Cylinder::CMeshField_Cylinder()
{

}
CMeshField_Cylinder::CMeshField_Cylinder(int TexIndex, float meshH, float radius, int meshXnum, int meshYnum)
{
	m_TexIndex = TexIndex;
	m_meshH = meshH;
	m_meshWnum = meshXnum;
	m_meshHnum = meshYnum;
	m_radius = radius;
	m_VertexW = meshXnum + 1;
	m_VertexH = meshYnum + 1;
	m_VertexCount = m_VertexW * m_VertexH;
	m_IndexCount = (meshXnum + 2) * (meshYnum * 2) - 2;
	m_PrimitiveCount = (meshXnum * 2 + 4) * meshYnum - 4;
	MeshField_Cylinder_Initialize();
}
//=============================================================================
//	�j��
//=============================================================================

CMeshField_Cylinder::~CMeshField_Cylinder()
{
	
}

//	�X�V
void CMeshField_Cylinder::Update(void)
{

}

//	�`��
void CMeshField_Cylinder::Draw(void)
{
	CMeshField::Draw();
}


//	���b�V���t�B�[���h�V�����_�[�쐬
CMeshField_Cylinder *CMeshField_Cylinder::MeshField_Cylinder_Create(int TexIndex, float meshH, float radius, int meshXnum, int meshYnum)
{
	m_pMeshField_Cylinder = new CMeshField_Cylinder(TexIndex, meshH, radius, meshXnum, meshYnum);
	return m_pMeshField_Cylinder;
}

//	�I������
void CMeshField_Cylinder::Finalize(void)
{

	// �C���f�b�N�X�o�b�t�@�̉��
	if (m_pIndexBuffer != NULL)
	{
		m_pIndexBuffer->Release();
		m_pIndexBuffer = NULL;
	}

	// ���_�o�b�t�@�̉��
	if (m_pVertexBuffer != NULL)
	{
		m_pVertexBuffer->Release();
		m_pVertexBuffer = NULL;
	}
	if (m_pMeshField_Cylinder != NULL)
	{
		delete m_pMeshField_Cylinder;
	}
}



//	���b�V���t�B�[���h�V�����_�[������(���_�ݒ�)
void CMeshField_Cylinder::MeshField_Cylinder_Initialize(void)
{
	// ���_�o�b�t�@�̊m��
	m_pD3DDevice->CreateVertexBuffer(sizeof(MeshFieldVertex) * m_VertexCount, D3DUSAGE_WRITEONLY, FVF_MESH_FIELD_VERTEX, D3DPOOL_MANAGED, &m_pVertexBuffer, NULL);
	// �C���f�b�N�X�o�b�t�@�̊m��
	m_pD3DDevice->CreateIndexBuffer(sizeof(WORD) * m_IndexCount, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIndexBuffer, NULL);


	for (int h = 0;h < m_VertexH;h++)
	{
		for (int w = 0;w < m_VertexW;w++)
		{
			int n = w + m_VertexW * h;
			float angle = 360 / m_meshWnum * w;
			m_Mfield[n].pos = D3DXVECTOR3(m_radius * sinf(D3DXToRadian(angle)), m_meshHnum * m_meshH - (h * m_meshH), m_radius * cosf(D3DXToRadian(angle)));
			m_Mfield[n].color = D3DCOLOR(0xffff0000);
			m_Mfield[n].uv = D3DXVECTOR2(w * (1.0f / m_meshWnum), h * (1.0f / m_meshHnum));
		}
	}

	Buffer_Write();
}





