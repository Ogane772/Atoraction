//////////////////////////////////////////////////
////
////	���b�V���t�B�[���h�N���X
////
//////////////////////////////////////////////////

#ifndef _CMESHFIELD_H_
#define _CMESHFIELD_H_

#include "CTexture.h"

#define MAX_MESH_FIELD (5000)

class CMeshField :public CTexture
{
public:

	CMeshField();
	CMeshField(int TexIndex, float meshW, int meshXnum, int meshZnum);
	~CMeshField();


	void Update(void);
	void Draw(void);
	void Finalize(void);	//	�I������
	static CMeshField *MeshField_Create(int TexIndex, float meshW, int meshXnum, int meshZnum);

protected:
	//���b�V���t�B�[���h���_�@�\����
	typedef struct
	{
		D3DXVECTOR3 pos;	//	���Wx,y,z
		D3DCOLOR color;		//	�J���[
		D3DXVECTOR2 uv;		//  �e�N�X�`��

	}MeshFieldVertex;

	#define FVF_MESH_FIELD_VERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)	//	�\���̂̂������ɏ���

	MeshFieldVertex m_Mfield[MAX_MESH_FIELD];	//	�\���̐錾

	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;	//	�o�[�e�b�N�X�o�b�t�@
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;		//	�C���f�b�N�X�o�b�t�@

	int m_VertexCount;		//	���_��
	int m_IndexCount;		//	�C���f�b�N�X��
	int m_PrimitiveCount;	//	�v���~�e�B�u��
	int m_VertexW;			//	�����̒��_��
	int m_VertexH;			//	�c���̒��_��
	int m_meshWnum;			//	�����̃��b�V����
	int m_meshHnum;			//	�c���̃��b�V����
	int m_TexIndex;			//	�e�N�X�`���C���f�b�N�X

	void Buffer_Write(void);	//	�o�b�t�@��������

	void DrawSky(D3DXMATRIX mtxw);
	D3DXMATRIX m_mtxWorld;
private:

	float m_meshW;		//	���b�V����
	void Mesh_Field_Initialize(void);	//	���b�V���t�B�[���h������(���_�ݒ�)
	void Mesh_Field_Initialize2(void);	//	���b�V���t�B�[���h������(���_�ݒ�)UV�l�ύX

	static CMeshField *m_pMeshFielde;
};
#endif // !1
