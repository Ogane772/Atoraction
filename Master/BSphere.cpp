#include "BSphere.h"
//
//HRESULT InitSphere(LPDIRECT3DDEVICE9 pDevice,THING* pThing)
//スフィアの計算およびスフィアを視認可能にするためにスフィアメッシュを作成する
HRESULT InitSphere(LPDIRECT3DDEVICE9 pDevice,THING2* pThing)
{
	HRESULT hr = NULL;
	LPDIRECT3DVERTEXBUFFER9 pVB = NULL;
    VOID* pVertices = NULL;
	D3DXVECTOR3 vCenter;
	FLOAT fRadius;

	//メッシュの頂点バッファーをロックする
	if(FAILED(pThing->pMesh->GetVertexBuffer( &pVB )))
	{
		return E_FAIL;
	}
    if(FAILED(pVB->Lock( 0, 0, &pVertices, 0 )))
    {
        SAFE_RELEASE( pVB );
        return E_FAIL;
    }
	// メッシュの外接円の中心と半径を計算する
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

	//これ以降の行は本質ではない。確認のためスフィア自体をレンダリングするための準備に過ぎない

	// 得られた中心と半径を基にメッシュとしてのスフィアを作成する
	hr=D3DXCreateSphere(pDevice,fRadius,24,24,&pThing->pSphereMesh,NULL);
	if(FAILED( hr ))
	{
		return hr;
	}	
	//スフィアメッシュのマテリアル　白色、半透明、光沢強 
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

	//メッシュの頂点バッファーをロックする
	if (FAILED(pThing->pMesh->GetVertexBuffer(&pVB)))
	{
		return E_FAIL;
	}
	if (FAILED(pVB->Lock(0, 0, &pVertices, 0)))
	{
		SAFE_RELEASE(pVB);
		return E_FAIL;
	}
	// メッシュの外接円の中心と半径を計算する
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

	//これ以降の行は本質ではない。確認のためスフィア自体をレンダリングするための準備に過ぎない

	// 得られた中心と半径を基にメッシュとしてのスフィアを作成する
	hr = D3DXCreateSphere(pDevice, fRadius, 24, 24, &pThing->pSphereMesh, NULL);
	if (FAILED(hr))
	{
		return hr;
	}
	//スフィアメッシュのマテリアル　白色、半透明、光沢強 
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
//衝突検出
BOOL Collision(THING2* pThingA,THING2* pThingB)
{
	//２つの物体の中心間の距離を求める
	D3DXVECTOR3 vLength=pThingB->vPosition-pThingA->vPosition;
	FLOAT fLength=D3DXVec3Length(&vLength);
	// その距離が、2物体の半径を足したものより小さいということは、
	//境界球同士が重なっている（衝突している）ということ
	if(fLength <= pThingA->Sphere.fRadius+pThingB->Sphere.fRadius)
	{
		return true;
	}
	return false;
}