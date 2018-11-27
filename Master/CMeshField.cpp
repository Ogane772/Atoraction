//////////////////////////////////////////////////
////
////	���b�V���t�B�[���h�N���X
////
//////////////////////////////////////////////////



//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================

#include "CMeshField.h"

//=============================================================================
//	�萔��`
//=============================================================================


//=============================================================================
//	�ÓI�ϐ�
//=============================================================================

CMeshField *CMeshField::m_pMeshFielde;

//=============================================================================
//	����
//=============================================================================

CMeshField::CMeshField()
{
	
}
CMeshField::CMeshField(int TexIndex, float meshW, int meshXnum, int meshZnum)
{
	m_TexIndex = TexIndex;
	m_meshW = meshW;
	m_meshWnum = meshXnum;
	m_meshHnum = meshZnum;
	m_VertexW = meshXnum + 1;
	m_VertexH = meshZnum + 1;
	m_VertexCount = m_VertexW * m_VertexH;
	m_IndexCount = (meshXnum + 2) * (meshZnum * 2) - 2;
	m_PrimitiveCount = (meshXnum * 2 + 4) * meshZnum - 4;
	Mesh_Field_Initialize();
}
//=============================================================================
//	�j��
//=============================================================================

CMeshField::~CMeshField()
{
	//Mesh_Field_Finalize();
}

//	�X�V
void CMeshField::Update(void)
{

}

//	�`��
void CMeshField::Draw(void)
{

	D3DXMATRIX mtxWorld;		// 4*4�s��@d3dx9.h�K�v
	D3DXMATRIX mtxTranslation;
	//D3DXMATRIX mtxRotation;
	//D3DXMatrixIdentity(&mtxWorld);	// �A�h���X����ƒP�ʍs�������Ă����

	//D3DXMatrixRotationZ(&mtxRotation, D3DXToRadian(0));
	D3DXMatrixTranslation(&mtxTranslation, 0, 0, 0);

	mtxWorld = mtxTranslation;
	//pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	m_pD3DDevice->SetFVF(FVF_MESH_FIELD_VERTEX);
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	m_pD3DDevice->SetTexture(0, Texture_GetTexture(m_TexIndex));


	m_pD3DDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(MeshFieldVertex));
	m_pD3DDevice->SetIndices(m_pIndexBuffer);
	m_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_VertexCount, 0, m_PrimitiveCount);

}


CMeshField *CMeshField::MeshField_Create(int TexIndex, float meshW, int meshXnum, int meshZnum)
{
	m_pMeshFielde = new CMeshField(TexIndex, meshW, meshXnum, meshZnum);
	return m_pMeshFielde;
}

void CMeshField::Finalize(void)
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
	if (m_pMeshFielde != NULL)
	{
		delete m_pMeshFielde;
	}
}


void CMeshField::Buffer_Write(void)
{
	// ���z�A�h���X�@
	MeshFieldVertex *pv;
	// ���_�o�b�t�@�̃��b�N
	m_pVertexBuffer->Lock(0, 0, (void**)&pv, 0);

	//memcpy(pv, g_Mfield, sizeof(g_Mfield[MAX_MESH_FIELD]));
	for (int i = 0;i < m_VertexCount;i++)
	{
		pv[i] = m_Mfield[i];
	}
	m_pVertexBuffer->Unlock();

	// ���z�A�h���X�@
	WORD *Ipv;
	// �C���f�b�N�X�o�b�t�@�̃��b�N
	m_pIndexBuffer->Lock(0, 0, (void**)&Ipv, 0);

	for (int h = 0;h < m_meshHnum * 2 - 1;h++)
	{
		if (h < m_meshHnum)
		{
			for (int w = 0;w < m_VertexW * 2;w++)
			{
				if (w % 2 == 0)
				{
					Ipv[(m_VertexW + 1) * (2 * h) + w] = m_VertexW + (m_VertexW * h) + (w * 0.5);
				}
				else
				{
					Ipv[(m_VertexW + 1) * (2 * h) + w] = (m_VertexW * h) + ((w - 1) * 0.5);
				}
			}
		}
		else
		{
			Ipv[(m_VertexW * 2)*(h - m_meshHnum + 1) + (2 * (h - m_meshHnum))] = m_VertexW * (h - m_meshHnum + 1) - 1;
			Ipv[(m_VertexW * 2)*(h - m_meshHnum + 1) + (2 * (h - m_meshHnum)) + 1] = m_VertexW * (h - m_meshHnum + 2);
		}
	}

	m_pIndexBuffer->Unlock();
}


void CMeshField::Mesh_Field_Initialize(void)
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
			m_Mfield[n].pos = D3DXVECTOR3(((float)m_meshWnum * 0.5f * -m_meshW) + (m_meshW * w), 0, ((float)m_meshHnum * 0.5 * m_meshW) + (-m_meshW * h));
			m_Mfield[n].color = D3DCOLOR(0xffffffff);
			m_Mfield[n].uv = D3DXVECTOR2(w * (1.0f / m_meshWnum), h * (1.0f / m_meshHnum));
		}

	}

	Buffer_Write();
}





