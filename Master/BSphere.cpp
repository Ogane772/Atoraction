#include "BSphere.h"
#include <crtdbg.h>
//#define _CRTDBG_MAP_ALLOC

#define new  ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
//�X�t�B�A�̌v�Z����уX�t�B�A�����F�\�ɂ��邽�߂ɃX�t�B�A���b�V�����쐬����
HRESULT InitSphere(LPDIRECT3DDEVICE9 pDevice,THING_NORMAL* pThing)
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
	//// ���b�V���̊O�ډ~�̒��S�Ɣ��a���v�Z����
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

	// ����ꂽ���S�Ɣ��a����Ƀ��b�V���Ƃ��ẴX�t�B�A���쐬����
	hr=D3DXCreateSphere(pDevice,fRadius, 16, 8,&pThing->pSphereMesh,NULL);
	
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
	delete pThing->pSphereMeshMaterials;
	return S_OK;
}

HRESULT InitSphere(LPDIRECT3DDEVICE9 pDevice, THING_NORMAL* pThing, D3DXVECTOR3 vCenter, FLOAT fRadius)
{
	HRESULT hr = NULL;
	LPDIRECT3DVERTEXBUFFER9 pVB = NULL;
	VOID* pVertices = NULL;

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
	/*hr = D3DXComputeBoundingSphere((D3DXVECTOR3*)pVertices, pThing->pMesh->GetNumVertices(),
		D3DXGetFVFVertexSize(pThing->pMesh->GetFVF()), &vCenter,
		&fRadius);*/
	pVB->Unlock();
	SAFE_RELEASE(pVB);

	if (FAILED(hr))
	{
		return hr;
	}
	pThing->Sphere.vCenter = vCenter;
	pThing->Sphere.fRadius = fRadius;

	// ����ꂽ���S�Ɣ��a����Ƀ��b�V���Ƃ��ẴX�t�B�A���쐬����
	hr = D3DXCreateSphere(pDevice, pThing->Sphere.fRadius, 16, 8, &pThing->pSphereMesh, NULL);

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
	delete pThing->pSphereMeshMaterials;
	return S_OK;
}

HRESULT InitCapsule(LPDIRECT3DDEVICE9 pDevice, THING_NORMAL* pThing, D3DXVECTOR3 vCenter, FLOAT fRadius,FLOAT length)
{
	HRESULT hr = NULL;
	LPDIRECT3DVERTEXBUFFER9 pVB = NULL;
	VOID* pVertices = NULL;

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
	/*hr = D3DXComputeBoundingSphere((D3DXVECTOR3*)pVertices, pThing->pMesh->GetNumVertices(),
	D3DXGetFVFVertexSize(pThing->pMesh->GetFVF()), &vCenter,
	&fRadius);*/
	pVB->Unlock();
	SAFE_RELEASE(pVB);

	if (FAILED(hr))
	{
		return hr;
	}
	pThing->Sphere.vCenter = vCenter;
	pThing->Capsule.fRadius = fRadius;
	pThing->Capsule.fRadius2 = fRadius + 1;
	pThing->Capsule.fLength = length;
	// ����ꂽ���S�Ɣ��a����Ƀ��b�V���Ƃ��ẴX�t�B�A���쐬����
	//hr = D3DXCreateSphere(pDevice, pThing->Sphere.fRadius, 16, 8, &pThing->pSphereMesh, NULL);
	hr = D3DXCreateCylinder(pDevice, pThing->Capsule.fRadius, pThing->Capsule.fRadius2, pThing->Capsule.fLength, 16, 8, &pThing->pSphereMesh, NULL);
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
	delete pThing->pSphereMeshMaterials;
	return S_OK;
}

HRESULT InitCapsule(LPDIRECT3DDEVICE9 pDevice, THING_NORMAL* pThing, D3DXVECTOR3 vCenter, FLOAT fRadius)
{
	HRESULT hr = NULL;
	LPDIRECT3DVERTEXBUFFER9 pVB = NULL;
	VOID* pVertices = NULL;

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
	/*hr = D3DXComputeBoundingSphere((D3DXVECTOR3*)pVertices, pThing->pMesh->GetNumVertices(),
	D3DXGetFVFVertexSize(pThing->pMesh->GetFVF()), &vCenter,
	&fRadius);*/
	pVB->Unlock();
	SAFE_RELEASE(pVB);

	if (FAILED(hr))
	{
		return hr;
	}
	pThing->Sphere.vCenter = vCenter;
	pThing->Sphere.fRadius = fRadius;

	// ����ꂽ���S�Ɣ��a����Ƀ��b�V���Ƃ��ẴX�t�B�A���쐬����
	//hr = D3DXCreateSphere(pDevice, pThing->Sphere.fRadius, 16, 8, &pThing->pSphereMesh, NULL);
	hr = D3DXCreateCylinder(pDevice, pThing->Sphere.fRadius, pThing->Sphere.fRadius + 1, 10, 16, 8, &pThing->pSphereMesh, NULL);
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
	delete pThing->pSphereMeshMaterials;
	return S_OK;
}

