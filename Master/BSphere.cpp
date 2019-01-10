#include "BSphere.h"
//
//HRESULT InitSphere(LPDIRECT3DDEVICE9 pDevice,THING* pThing)
//�X�t�B�A�̌v�Z����уX�t�B�A�����F�\�ɂ��邽�߂ɃX�t�B�A���b�V�����쐬����
HRESULT InitSphere(LPDIRECT3DDEVICE9 pDevice,THING2* pThing)
{
	HRESULT hr = NULL;
	LPDIRECT3DVERTEXBUFFER9 pVB = NULL;
    VOID* pVertices = NULL;
	D3DXVECTOR3 vCenter;
	FLOAT fRadius;

	//���b�V���̒��_�o�b�t�@�[�����b�N����
	if(FAILED(pThing->pMesh->GetVertexBuffer( &pVB )))
	{
		return E_FAIL;
	}
    if(FAILED(pVB->Lock( 0, 0, &pVertices, 0 )))
    {
        SAFE_RELEASE( pVB );
        return E_FAIL;
    }
	// ���b�V���̊O�ډ~�̒��S�Ɣ��a���v�Z����
	hr=D3DXComputeBoundingSphere( (D3DXVECTOR3*)pVertices, pThing->pMesh->GetNumVertices(), 
                                    D3DXGetFVFVertexSize(pThing->pMesh->GetFVF()), &vCenter, 
                                    &fRadius );
	pVB->Unlock();
    SAFE_RELEASE( pVB );

	if(FAILED( hr ))
	{
        return hr;
	}		
	pThing->Sphere.vCenter=vCenter;
	pThing->Sphere.fRadius=fRadius;

	//����ȍ~�̍s�͖{���ł͂Ȃ��B�m�F�̂��߃X�t�B�A���̂������_�����O���邽�߂̏����ɉ߂��Ȃ�

	// ����ꂽ���S�Ɣ��a����Ƀ��b�V���Ƃ��ẴX�t�B�A���쐬����
	hr=D3DXCreateSphere(pDevice,fRadius,24,24,&pThing->pSphereMesh,NULL);
	if(FAILED( hr ))
	{
		return hr;
	}	
	//�X�t�B�A���b�V���̃}�e���A���@���F�A�������A���� 
	pThing->pSphereMeshMaterials = new D3DMATERIAL9;
	pThing->pSphereMeshMaterials->Diffuse.r=1.0f;
	pThing->pSphereMeshMaterials->Diffuse.g=1.0f;
	pThing->pSphereMeshMaterials->Diffuse.b=1.0f;	
	pThing->pSphereMeshMaterials->Diffuse.a=0.3f;
	pThing->pSphereMeshMaterials->Ambient=pThing->pSphereMeshMaterials->Diffuse;	
	pThing->pSphereMeshMaterials->Specular.r=1.0f;
	pThing->pSphereMeshMaterials->Specular.g=1.0f;
	pThing->pSphereMeshMaterials->Specular.b=1.0f;
	pThing->pSphereMeshMaterials->Emissive.r=0.1f;
	pThing->pSphereMeshMaterials->Emissive.g=0.1f;
	pThing->pSphereMeshMaterials->Emissive.b=0.1f;
	pThing->pSphereMeshMaterials->Power=120.0f;	

	return S_OK;
}
//
HRESULT InitSphere(LPDIRECT3DDEVICE9 pDevice, THING* pThing)
{
	HRESULT hr = NULL;
	LPDIRECT3DVERTEXBUFFER9 pVB = NULL;
	VOID* pVertices = NULL;
	D3DXVECTOR3 vCenter;
	FLOAT fRadius;

	//���b�V���̒��_�o�b�t�@�[�����b�N����
	if (FAILED(pThing->pMesh->GetVertexBuffer(&pVB)))
	{
		return E_FAIL;
	}
	if (FAILED(pVB->Lock(0, 0, &pVertices, 0)))
	{
		SAFE_RELEASE(pVB);
		return E_FAIL;
	}
	// ���b�V���̊O�ډ~�̒��S�Ɣ��a���v�Z����
	hr = D3DXComputeBoundingSphere((D3DXVECTOR3*)pVertices, pThing->pMesh->GetNumVertices(),
		D3DXGetFVFVertexSize(pThing->pMesh->GetFVF()), &vCenter,
		&fRadius);
	pVB->Unlock();
	SAFE_RELEASE(pVB);

	if (FAILED(hr))
	{
		return hr;
	}
	pThing->Sphere.vCenter = vCenter;
	pThing->Sphere.fRadius = fRadius;

	//����ȍ~�̍s�͖{���ł͂Ȃ��B�m�F�̂��߃X�t�B�A���̂������_�����O���邽�߂̏����ɉ߂��Ȃ�

	// ����ꂽ���S�Ɣ��a����Ƀ��b�V���Ƃ��ẴX�t�B�A���쐬����
	hr = D3DXCreateSphere(pDevice, fRadius, 24, 24, &pThing->pSphereMesh, NULL);
	if (FAILED(hr))
	{
		return hr;
	}
	//�X�t�B�A���b�V���̃}�e���A���@���F�A�������A���� 
	pThing->pSphereMeshMaterials = new D3DMATERIAL9;
	pThing->pSphereMeshMaterials->Diffuse.r = 1.0f;
	pThing->pSphereMeshMaterials->Diffuse.g = 1.0f;
	pThing->pSphereMeshMaterials->Diffuse.b = 1.0f;
	pThing->pSphereMeshMaterials->Diffuse.a = 0.3f;
	pThing->pSphereMeshMaterials->Ambient = pThing->pSphereMeshMaterials->Diffuse;
	pThing->pSphereMeshMaterials->Specular.r = 1.0f;
	pThing->pSphereMeshMaterials->Specular.g = 1.0f;
	pThing->pSphereMeshMaterials->Specular.b = 1.0f;
	pThing->pSphereMeshMaterials->Emissive.r = 0.1f;
	pThing->pSphereMeshMaterials->Emissive.g = 0.1f;
	pThing->pSphereMeshMaterials->Emissive.b = 0.1f;
	pThing->pSphereMeshMaterials->Power = 120.0f;

	return S_OK;
}
//BOOL Collision(THING* pThingA,THING* pThingB)
//�Փˌ��o
BOOL Collision(THING2* pThingA,THING2* pThingB)
{
	//�Q�̕��̂̒��S�Ԃ̋��������߂�
	D3DXVECTOR3 vLength=pThingB->vPosition-pThingA->vPosition;
	FLOAT fLength=D3DXVec3Length(&vLength);
	// ���̋������A2���̂̔��a�𑫂������̂�菬�����Ƃ������Ƃ́A
	//���E�����m���d�Ȃ��Ă���i�Փ˂��Ă���j�Ƃ�������
	if(fLength <= pThingA->Sphere.fRadius+pThingB->Sphere.fRadius)
	{
		return true;
	}
	return false;
}