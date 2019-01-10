//////////////////////////////////////////////////
////
////	�t�B�W�b�N�X�N���X(�������Z)
////
//////////////////////////////////////////////////

//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================

#define NOMINMAX
#include <windows.h>
#undef min
#undef max
#include "Cphysx.h"
#include "input.h"
#include <mmsystem.h>
#include <d3dx9.h>
#pragma warning( disable : 4996 ) 
#include <strsafe.h>
#pragma warning( default : 4996 )
#include "ErrorStream.h"
#include "CAttraction.h"
#include "debug_font.h"
#include "BSphere.h"
#include "CSkinAnimation.h"
#include "Cplayer.h"
#include "CEnemy.h"
#include "CEnemy_Small.h"
//=============================================================================
//	�萔��`
//=============================================================================


//=============================================================================
//	�ÓI�ϐ�
//=============================================================================

//	�g�������m�[�}�����f���̐���������
CPhysx::ModelFileData CPhysx::m_NormalModelFileData[] = {
	{},
	{ "asset/model/emi-ru2.x" },
	{ "asset/model/zako.x" },
	{ "asset/model/boss.x" },
	{ "asset/model/CoffeeCup.blend.x" },
	{ "asset/model/dish.blend.x" },
	{ "asset/model/enban.x" },
	{ "asset/model/hasira.x" },
	{ "asset/model/ferris.x" },
	{ "asset/model/jet.x" },
	{ "asset/model/cup_blue.x" },
	{ "asset/model/cup_kiiro.x" },
	{ "asset/model/cup_midori.x" },
	{ "asset/model/popcorn.x" },
};
//	�g�������A�j�����f���̐���������
CPhysx::ModelFileData CPhysx::m_AnimeModelFileData[] = {
	{ "asset/anime_model/small_enemy.x" },
};
int CPhysx::m_NORMALMODELFAIL_MAX = sizeof(CPhysx::m_NormalModelFileData) / sizeof(m_NormalModelFileData[0]);
int CPhysx::m_ANIMEMODELFAIL_MAX = sizeof(CPhysx::m_AnimeModelFileData) / sizeof(m_AnimeModelFileData[0]);
// PhysX�N���X
NxPhysicsSDK* CPhysx::gPhysicsSDK = NULL;
NxScene* CPhysx::gScene = NULL;

LPD3DXMESH CPhysx::g_pMesh[numMesh] = {};
D3DMATERIAL9* CPhysx::g_pMeshMaterials[numMesh] = {};
LPDIRECT3DTEXTURE9* CPhysx::g_pMeshTextures[numMesh] = {};
DWORD CPhysx::g_dwNumMaterials[numMesh] = {};
LPDIRECT3DVERTEXBUFFER9 CPhysx::g_pVB = {};

//NxActor* CPhysx::NxA_pPlayer = {};
//NxActor* CPhysx::NxA_pBoss = {};
//NxActor* CPhysx::NxA_pSmall = {};
bool CPhysx::hit = false;
bool g_hit = false;

/*NxActor* CPhysx::NxA_pCoffee = {};
NxActor* CPhysx::NxA_pCoffeeTable = {};

NxActor* CPhysx::NxA_pEnban = {};
NxActor* CPhysx::NxA_pHasira = {};
NxActor* CPhysx::NxA_pWheel = {};*/
bool boRenderSphere = true;
//���f���A�j���[�V�����֌W�ϐ�
#define MODEL_MAX (13)
SKIN_MESH SkinMesh;
THING2 Thing2[MODEL_MAX - 1];//�ǂݍ��ރ��f���̍ő吔+1
THING Thing[THING_AMOUNT + 1];//�ǂݍ��ރ��f���̍ő吔+1
LPD3DXANIMATIONSET pAnimSet[THING_AMOUNT][10] = { 0 };//�I���������f����10�܂ł̃A�j���[�V�������Z�b�g
FLOAT fAnimTime = 0.0f;
BOOL boPlayAnim = true;
D3DXTRACK_DESC TrackDesc;
//=============================================================================
//	����
//=============================================================================

CPhysx::CPhysx()
{

}

//=============================================================================
//	�j��
//=============================================================================
CPhysx::~CPhysx()
{

}

//	�������Z�����̏�����
void CPhysx::CPhysX_Initialize(void)
{
	InitGeometry();
	InitNx();
}


// Geometry�̏������i���f���̓ǂݍ��݁j
HRESULT CPhysx::InitGeometry()
{
	/*if (FAILED(LoadMesh("asset/model/boss.x", BOSS)))
	return E_FAIL;
	if (FAILED(LoadMesh("asset/model/emi-ru2.x", PLAYER)))
	return E_FAIL;
	if (FAILED(LoadMesh("asset/model/slime.x", SMALL)))
	return E_FAIL;
	*/
	/*
	for (int i = 1; i < m_NORMALMODELFAIL_MAX - 1; i++)
	{
		InitThing(&Thing2[i], m_NormalModelFileData[i].filename);
	}*/
	InitThing(&Thing2[0], m_NormalModelFileData[1].filename);
	InitSphere(m_pD3DDevice, &Thing2[0]);

//	InitThing(&Thing2[1], m_NormalModelFileData[2].filename);
//	InitSphere(m_pD3DDevice, &Thing2[1]);
	/*
	// ���b�V�����Ƃ̃o�E���f�B���O�X�t�B�A�i���E���j�̍쐬
	for (int i = 0; i < m_NORMALMODELFAIL_MAX - 1; i++)
	{
		InitSphere(m_pD3DDevice, &Thing2[i]);
	}*/
	/*
	for (int i = 0;i < m_NORMALMODELFAIL_MAX - 1;i++)
	{
		if (FAILED(LoadMesh(m_NormalModelFileData[i+1].filename, i+1)))
			return E_FAIL;
	}*/
	//�A�j���[�V�������f���ǂݍ���
	//THING��x�t�@�C����ǂݍ���
	for (int i = 0; i < ANIME_MODEL_MAX; i++)
	{
		SkinMesh.InitThing(m_pD3DDevice, &Thing[i], m_AnimeModelFileData[i].filename);
	}
	SkinMesh.InitSphere(m_pD3DDevice, &Thing[0]);
	if (FAILED(CreateDebugBase()))
		return E_FAIL;
	return S_OK;
}

// PhysX�̏�����
bool CPhysx::InitNx(void)
{
	NxPhysicsSDKDesc desc;
	NxSDKCreateError errorCode = NXCE_NO_ERROR;
	gPhysicsSDK = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION, NULL, new ErrorStream(), desc, &errorCode);
	if (gPhysicsSDK == NULL) return false;

	gPhysicsSDK->setParameter(NX_SKIN_WIDTH, 0.05f);

	// �V�[���̐���
	NxSceneDesc sceneDesc;
	sceneDesc.gravity = NxVec3(0.0f, -9.81f, 0.0f);
	gScene = gPhysicsSDK->createScene(sceneDesc);
	if (gScene == NULL) return false;

	// �f�t�H���g�̃}�e���A����ݒ�
	NxMaterial* defaultMaterial = gScene->getMaterialFromIndex(0);
	defaultMaterial->setRestitution(0.0f);
	defaultMaterial->setStaticFriction(0.5f);
	defaultMaterial->setDynamicFriction(0.5f);

	// PhysX�O�����h�̐���
	NxPlaneShapeDesc planeDesc;
	NxActorDesc actorDesc;
	actorDesc.shapes.pushBack(&planeDesc);
	gScene->createActor(actorDesc);

	return true;
}

// ���b�V���̓ǂݍ���
HRESULT CPhysx::LoadMesh(LPCSTR filename, int n)
{
	LPD3DXBUFFER pD3DXMtrlBuffer;

	// �t�@�C���̃��[�h
	if (FAILED(D3DXLoadMeshFromX(filename, D3DXMESH_SYSTEMMEM,
		m_pD3DDevice, NULL,
		&pD3DXMtrlBuffer, NULL, &g_dwNumMaterials[n],
		&g_pMesh[n])))
	{
		// �e�f�B���N�g���̃T�[�`
		if (FAILED(D3DXLoadMeshFromX(filename, D3DXMESH_SYSTEMMEM,
			m_pD3DDevice, NULL,
			&pD3DXMtrlBuffer, NULL, &g_dwNumMaterials[n],
			&g_pMesh[n])))
		{
			MessageBox(NULL, "Could not find xFile", "Meshes.exe", MB_OK);
			return E_FAIL;
		}
	}

	// �}�e���A���̃v���p�e�B�ƃe�N�X�`���t�@�C�����̎擾 
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	g_pMeshMaterials[n] = new D3DMATERIAL9[g_dwNumMaterials[n]];
	if (g_pMeshMaterials[n] == NULL)
		return E_OUTOFMEMORY;
	g_pMeshTextures[n] = new LPDIRECT3DTEXTURE9[g_dwNumMaterials[n]];
	if (g_pMeshTextures[n] == NULL)
		return E_OUTOFMEMORY;

	for (DWORD i = 0; i < g_dwNumMaterials[n]; i++)
	{
		// �}�e���A���̃R�s�[
		g_pMeshMaterials[n][i] = d3dxMaterials[i].MatD3D;

		// �}�e���A���̃A���r�G���g�J���[�̐ݒ�
		g_pMeshMaterials[n][i].Ambient = g_pMeshMaterials[n][i].Diffuse;

		g_pMeshTextures[n][i] = NULL;
		if (d3dxMaterials[i].pTextureFilename != NULL &&
			lstrlenA(d3dxMaterials[i].pTextureFilename) > 0)
		{
			// �e�N�X�`���̐���
			if (FAILED(D3DXCreateTextureFromFileA(m_pD3DDevice,
				d3dxMaterials[i].pTextureFilename,
				&g_pMeshTextures[n][i])))
			{
				// �f�B���N�g���̃T�[�`
				const CHAR* strPrefix = "asset\\model\\";
				CHAR strTexture[MAX_PATH];
				StringCchCopyA(strTexture, MAX_PATH, strPrefix);
				StringCchCatA(strTexture, MAX_PATH, d3dxMaterials[i].pTextureFilename);
				// �e�̃f�B���N�g���̃T�[�`
				if (FAILED(D3DXCreateTextureFromFileA(m_pD3DDevice,
					strTexture,
					&g_pMeshTextures[n][i])))
				{
					MessageBox(NULL, "Could not find texture map", "Meshes.exe", MB_OK);
				}
			}
		}
	}
	// �}�e���A���o�b�t�@�̉��
	pD3DXMtrlBuffer->Release();

	return S_OK;
}

HRESULT CPhysx::InitThing(THING2 *pThing, LPSTR szXFileName)
{
	/////////
	// X�t�@�C�����烁�b�V�������[�h����	
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

	if (FAILED(D3DXLoadMeshFromX(szXFileName, D3DXMESH_SYSTEMMEM,
		m_pD3DDevice, NULL, &pD3DXMtrlBuffer, NULL,
		&pThing->dwNumMaterials, &pThing->pMesh)))
	{
		MessageBox(NULL, "X�t�@�C���̓ǂݍ��݂Ɏ��s���܂���", szXFileName, MB_OK);
		return E_FAIL;
	}
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	pThing->pMeshMaterials = new D3DMATERIAL9[pThing->dwNumMaterials];
	pThing->pMeshTextures = new LPDIRECT3DTEXTURE9[pThing->dwNumMaterials];

	for (DWORD i = 0; i<pThing->dwNumMaterials; i++)
	{
		pThing->pMeshMaterials[i] = d3dxMaterials[i].MatD3D;
		pThing->pMeshMaterials[i].Ambient = pThing->pMeshMaterials[i].Diffuse;
		pThing->pMeshTextures[i] = NULL;
		if (d3dxMaterials[i].pTextureFilename != NULL &&
			lstrlen(d3dxMaterials[i].pTextureFilename) > 0)
		{
			if (FAILED(D3DXCreateTextureFromFile(m_pD3DDevice,
				d3dxMaterials[i].pTextureFilename,
				&pThing->pMeshTextures[i])))
			{
				MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", NULL, MB_OK);
			}
		}
	}
	pD3DXMtrlBuffer->Release();

	return S_OK;
}

// �A�N�^�[�̃Z�b�g�A�b�v
void CPhysx::SetupActors(void)
{
	float skin = 0.1f;
	// Dwarf
	NxMat33 mat1;
	mat1.rotY(-NxPiF32 / 2);
	NxVec3 scaleDwarf = NxVec3(1, 1, 1);//���f���̑傫��
	NxVec3 BBDwarf = NxVec3(2.6f, 2.7f, 2.3f);//�{�b�N�X�R���W�����̑傫��
	float d = scaleDwarf.y * BBDwarf.y - skin;
	//NxA_pPlayer = CreateMeshAsBox(NxVec3(-8, d, 0), mat1, scaleDwarf, BBDwarf, MODELL_PLAYER);
}


// �I������
void CPhysx::Cleanup(void)
{
	// PhysX
	ExitNx();

	for (int k = 0; k < 2; k++)
	{
		if (g_pMeshMaterials[k] != NULL)
			delete[] g_pMeshMaterials[k];

		if (g_pMeshTextures[k])
		{
			for (DWORD i = 0; i < g_dwNumMaterials[k]; i++)
			{
				if (g_pMeshTextures[k][i])
					g_pMeshTextures[k][i]->Release();
			}
			delete[] g_pMeshTextures[k];
		}
		if (g_pMesh[k] != NULL)
			g_pMesh[k]->Release();
	}
}

// PhysX�̏I������
void CPhysx::ExitNx(void)
{
	if (gPhysicsSDK != NULL)
	{
		if (gScene != NULL) gPhysicsSDK->releaseScene(*gScene);
		gScene = NULL;
		NxReleasePhysicsSDK(gPhysicsSDK);
		gPhysicsSDK = NULL;
	}
}

//	�V�[���擾
NxScene* CPhysx::Get_PhysX_Scene(void)
{
	return gScene;
}


// �`��
void CPhysx::PhysXRender(D3DXMATRIX mtxWorld)
{
	DebugFont_Draw(8, 58, "8�L�[�@���f���̔�\��");
	DebugFont_Draw(8, 108, "9�L�[�@�����蔻��\��");
	DebugFont_Draw(8, 158, "�����������@%d", hit);
	//DebugFont_Draw(8, 208, "�O�ꂽ�� %d");

	// PhysX�̃V�[�����`�F�b�N
	if (gScene == NULL) return;
	// PhysX���ԃX�e�b�v
	gScene->simulate(1.0f / 60.0f);

	// �J�����Ǝˉe�̃Z�b�g�A�b�v
	//Camera_Move();
	// �`��
	if (physx)//�����蔻��\���t���O��true�̎�
	{
		RenderPhysX();//�����蔻��R���W�����\��
	}
	if (directx)//���f���\��
	{
		RenderDirectX(mtxWorld);//���f���`��
	}
	/*if (NxA_pCoffee && NxA_pEnban)
	{
		gScene->setActorPairFlags(*NxA_pCoffee,
			*NxA_pEnban,
			NX_NOTIFY_ON_START_TOUCH | NX_NOTIFY_ON_END_TOUCH);
	}*/
}

// PhysX�̕`�� PhysXRender
void CPhysx::RenderPhysX(void)
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	// ���[���h�}�g���b�N�X���Z�b�g
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	m_pD3DDevice->SetStreamSource(0, g_pVB, 0, sizeof(CUSTOMVERTEX));
	m_pD3DDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	// ���W���ƃ}�b�g
	//DrawMeshDummy(0, 0);
	DrawMat();
	DrawAxis();
	//DrawMeshDummy(0, 1);
	// PhysX�A�N�^�[�̕`��
	int nbActors = gScene->getNbActors();
	NxActor** actors = gScene->getActors();

	while (nbActors--)
	{
		NxActor* actor = *actors++;
		if (!actor->userData) continue;
		float glMat[16];
		actor->getGlobalPose().getColumnMajor44(glMat);
		// �}�g���b�N�X�̓]�u
		ConvertMatrix(matWorld, glMat);
		myData* mydata = (myData*)actor->userData;

		char c = mydata->type;
		switch (c)
		{
		case 'B':
			DrawBox(actor, matWorld);
			break;
		case 'S':
			DrawSphere(actor, matWorld);
			break;
		case 'C':
			DrawCapsule(actor, matWorld);
			break;
		}
	/*	if (NxA_pCoffee && NxA_pEnban)
		{
			gScene->setActorPairFlags(*NxA_pCoffee,
				*NxA_pEnban,
				NX_NOTIFY_ON_START_TOUCH | NX_NOTIFY_ON_END_TOUCH);
		}*/
	}
}

// �n�ʂ̃}�b�g RenderPhysX
void CPhysx::DrawMat(void)
{
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 0, 18);
}

// XYZ�̍��W�� RenderPhysX
void CPhysx::DrawAxis()
{
	m_pD3DDevice->DrawPrimitive(D3DPT_LINELIST, 19, 1);
}

// �R���W������t���Ȃ����f���̕`�� RenderPhysX
void CPhysx::DrawNoHitMesh(int n)
{
	for (DWORD i = 0; i < g_dwNumMaterials[n]; i++)
	{
		// �}�e���A���ƃe�N�X�`��
		m_pD3DDevice->SetMaterial(&g_pMeshMaterials[n][i]);
		m_pD3DDevice->SetTexture(0, g_pMeshTextures[n][i]);

		// �`��
		g_pMesh[n]->DrawSubset(i);
	}
}

// ���b�V���̕`�� RenderPhysX
void CPhysx::DrawMeshDummy(int n, int m)
{
	// �}�e���A���ƃe�N�X�`��
	m_pD3DDevice->SetMaterial(&g_pMeshMaterials[n][m]);
	m_pD3DDevice->SetTexture(0, g_pMeshTextures[n][m]);
}

// DirectX�̕`�� PhysXRender
void CPhysx::RenderDirectX(D3DXMATRIX mtxWorld)
{
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	m_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
	//D3DXMATRIXA16 matWorld;
	//D3DXMatrixIdentity(&mtxWorld);
	// ���[���h�}�g���b�N�X���Z�b�g
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	// DirectX�̎Ő�
	//DrawNoHitMesh(DirectXBase);

	// �A�N�^�[�̕`��
	int nbActors = gScene->getNbActors();
	NxActor** actors = gScene->getActors();
	while (nbActors--)
	{
		NxActor* actor = *actors++;
		if (!actor->userData) continue;

		myData* mydata = (myData*)actor->userData;
		if ((mydata->type == 'B') || (mydata->type == 'S') || (mydata->type == 'C'))
		{
			DrawDirectXMesh(actor);
		}
	/*	if (NxA_pCoffee && NxA_pEnban)
		{
			gScene->setActorPairFlags(*NxA_pCoffee,
				*NxA_pEnban,
				NX_NOTIFY_ON_START_TOUCH | NX_NOTIFY_ON_END_TOUCH);
		}*/
		// �Q�̃A�N�^�[���֘A�Â��ďՓˊJ�n�ƏՓˏI���C�x���g��L���ɂ���
		//�����蔻�菈���@�������Ƒ������ɓ����蔻����s���A�N�^�[���w�肷��
		/*if (MODELL_PLAYER)
		{
		gScene->setActorPairFlags(*NxA_pPlayer,
		*NxA_pBoss,
		NX_NOTIFY_ON_START_TOUCH | NX_NOTIFY_ON_END_TOUCH);
		}*/
	}
}

// ���b�V���̕`�� RenderDirectX
void CPhysx::DrawDirectXMesh(NxActor* actor)
{
	if (actor)
	{
		int nbActors = gScene->getNbActors();
		NxActor** actors = gScene->getActors();
		myData* mydata = (myData*)actor->userData;
		for (int i = nbActors;i > 0;i--)
		{
			NxActor* act = *actors++;
			if (!act->userData) continue;
			myData* data = (myData*)act->userData;
			if (data->ID == mydata->ID)
			{

				D3DXMATRIXA16 matWorld;

				//myData* mydata = (myData*)actor->userData;
				NxVec3 s = mydata->meshScale;
				NxVec3 t = mydata->meshTranslation;

				D3DXMATRIXA16 mat;

				// PhysX�p���̎擾
				float glMat[16];
				act->getGlobalPose().getColumnMajor44(glMat);
				ConvertMatrix(matWorld, glMat);

				// ���b�V���̊g��k��
				D3DXMatrixScaling(&mat, s.x, s.y, s.z);
				D3DXMatrixMultiply(&matWorld, &mat, &matWorld);

				// ���b�V���̉�]
				mat = mydata->meshRotation;
				D3DXMatrixMultiply(&matWorld, &mat, &matWorld);

				// ���b�V���̌��_����
				D3DXMatrixTranslation(&mat, t.x, t.y + 1, t.z);
				D3DXMatrixMultiply(&matWorld, &mat, &matWorld);

				// �}�g���b�N�X�̃Z�b�g
				m_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
				// ���b�V���̕`��
				int n = mydata->ID;
				for (DWORD i = 0; i < g_dwNumMaterials[n]; i++)
				{
					// �}�e���A���ƃe�N�X�`��
					m_pD3DDevice->SetMaterial(&g_pMeshMaterials[n][i]);
					m_pD3DDevice->SetTexture(0, g_pMeshTextures[n][i]);

					// �`��
					g_pMesh[n]->DrawSubset(i);
				}

			}
		/*	if (NxA_pCoffee && NxA_pEnban)
			{
				gScene->setActorPairFlags(*NxA_pCoffee,
					*NxA_pEnban,
					NX_NOTIFY_ON_START_TOUCH | NX_NOTIFY_ON_END_TOUCH);
			}*/
		}
	}
}

void CPhysx::DrawDX2(D3DXMATRIX mtxWorld, NxActor* actor, int type)
{
	if (actor)
	{
		/*DebugFont_Draw(8, 58, "8�L�[�@���f���̔�\��");
		DebugFont_Draw(8, 108, "9�L�[�@�����蔻��\��");
		DebugFont_Draw(8, 158, "�����������@%d", hit);*/

		// PhysX�̃V�[�����`�F�b�N
		if (gScene == NULL) return;
		// PhysX���ԃX�e�b�v
		gScene->simulate(1.0f / 60.0f);

		m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		m_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
		m_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);

		myData* mydata = (myData*)actor->userData;

		mydata->meshTranslation.x = mtxWorld._41;
		mydata->meshTranslation.y = mtxWorld._42;
		mydata->meshTranslation.z = mtxWorld._43;
		actor->setGlobalPosition(mydata->meshTranslation);

		D3DXMATRIXA16 mat;
		D3DXMATRIXA16 mtxWorld2;
		// PhysX�p���̎擾
		float glMat[16];
		actor->getGlobalPose().getColumnMajor44(glMat);
		ConvertMatrix(mtxWorld2, glMat);

		NxVec3 s = mydata->meshScale;
		NxVec3 t = mydata->meshTranslation;
		// ���b�V���̊g��k��
		D3DXMatrixScaling(&mat, s.x, s.y, s.z);
		D3DXMatrixMultiply(&mtxWorld, &mat, &mtxWorld);

		// ���b�V���̉�]
		mat = mydata->meshRotation;
		//D3DXMatrixMultiply(&mtxWorld2, &mat, &mtxWorld2);
		D3DXMatrixMultiply(&mtxWorld, &mat, &mtxWorld);

		D3DXMatrixTranslation(&mat, 0, 0, 0);
		D3DXMatrixMultiply(&mtxWorld, &mat, &mtxWorld);
		// �}�g���b�N�X�̃Z�b�g
		m_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
		// ���b�V���̕`��
		int n = mydata->ID;
		for (DWORD i = 0; i < g_dwNumMaterials[n]; i++)
		{
			// �}�e���A���ƃe�N�X�`��
			m_pD3DDevice->SetMaterial(&g_pMeshMaterials[n][i]);
			m_pD3DDevice->SetTexture(0, g_pMeshTextures[n][i]);

			// �`��
			g_pMesh[n]->DrawSubset(i);
		}

	}
}

void CPhysx::DrawDX_Anime(D3DXMATRIX mtxWorld, NxActor* actor, int type,THING* pThing)
{
	static float fAnimTimeHold = fAnimTime;
	if (actor)
	{
		SKIN_MESH::UpdateSphere(m_pD3DDevice, pThing);
		/*DebugFont_Draw(8, 58, "8�L�[�@���f���̔�\��");
		DebugFont_Draw(8, 108, "9�L�[�@�����蔻��\��");
		DebugFont_Draw(8, 158, "�����������@%d", hit);*/

		// PhysX�̃V�[�����`�F�b�N
		if (gScene == NULL) return;
		// PhysX���ԃX�e�b�v
		gScene->simulate(1.0f / 60.0f);

		m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		m_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
		m_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);

		myData* mydata = (myData*)actor->userData;

		mydata->meshTranslation.x = mtxWorld._41;
		mydata->meshTranslation.y = mtxWorld._42;
		mydata->meshTranslation.z = mtxWorld._43;
		actor->setGlobalPosition(mydata->meshTranslation);

		D3DXMATRIXA16 mat;
		D3DXMATRIXA16 mtxWorld2;
		// PhysX�p���̎擾
		float glMat[16];
		actor->getGlobalPose().getColumnMajor44(glMat);
		ConvertMatrix(mtxWorld2, glMat);

		NxVec3 s = mydata->meshScale;
		NxVec3 t = mydata->meshTranslation;
		// ���b�V���̊g��k��
		D3DXMatrixScaling(&mat, s.x, s.y, s.z);
		D3DXMatrixMultiply(&mtxWorld, &mat, &mtxWorld);

		// ���b�V���̉�]
		mat = mydata->meshRotation;
		//D3DXMatrixMultiply(&mtxWorld2, &mat, &mtxWorld2);
		D3DXMatrixMultiply(&mtxWorld, &mat, &mtxWorld);

		D3DXMatrixTranslation(&mat, 0, 0, 0);
		D3DXMatrixMultiply(&mtxWorld, &mat, &mtxWorld);
		// �}�g���b�N�X�̃Z�b�g
		m_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
		// ���b�V���̕`��
		int n = mydata->ID;
		for (DWORD i = 0; i < g_dwNumMaterials[n]; i++)
		{
			// �}�e���A���ƃe�N�X�`��
			m_pD3DDevice->SetMaterial(&g_pMeshMaterials[n][i]);
			m_pD3DDevice->SetTexture(0, g_pMeshTextures[n][i]);

			// �`��
			g_pMesh[n]->DrawSubset(i);
		}

		//�����_�����O
		SkinMesh.UpdateFrameMatrices(pThing->pFrameRoot, &mtxWorld);
		SkinMesh.DrawFrame(m_pD3DDevice, pThing->pFrameRoot);
		pThing->pAnimController->AdvanceTime(fAnimTime - fAnimTimeHold, NULL);
		//�@�o�E���f�B���O�X�t�B�A�̃����_�����O	
		D3DXMatrixTranslation(&mat, pThing->vPosition.x, pThing->vPosition.y,
			pThing->vPosition.z);
		D3DXMatrixTranslation(&mtxWorld, pThing->Sphere.vCenter.x, pThing->Sphere.vCenter.y,
			pThing->Sphere.vCenter.z);
		mtxWorld *= mat;

		m_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		if (boRenderSphere)
		{
			m_pD3DDevice->SetTexture(0, NULL);
			m_pD3DDevice->SetMaterial(pThing->pSphereMeshMaterials);
			pThing->pSphereMesh->DrawSubset(0);
		}
		//�A�j���Đ����Ԃ�+
		fAnimTimeHold = fAnimTime;
		if (boPlayAnim)
		{
			fAnimTime += 0.01f;
		}
	}
}
void CPhysx::DrawDX(D3DXMATRIX mtxWorld, NxActor* actor)
{
	if (actor)
	{
		DebugFont_Draw(8, 58, "8�L�[�@���f���̔�\��");
		DebugFont_Draw(8, 108, "9�L�[�@�����蔻��\��");
		DebugFont_Draw(8, 158, "�����������@%d", hit);

		// PhysX�̃V�[�����`�F�b�N
		if (gScene == NULL) return;
		// PhysX���ԃX�e�b�v
		gScene->simulate(1.0f / 60.0f);

		m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		m_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
		m_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
		//D3DXMATRIXA16 matWorld;
		//D3DXMatrixIdentity(&mtxWorld);
		// ���[���h�}�g���b�N�X���Z�b�g
		//	m_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
		// DirectX�̎Ő�
		//DrawNoHitMesh(DirectXBase);

		myData* mydata = (myData*)actor->userData;
		mydata->meshTranslation.x = mtxWorld._41;
		mydata->meshTranslation.y = mtxWorld._42;
		mydata->meshTranslation.z = mtxWorld._43;
		NxVec3 s = mydata->meshScale;
		NxVec3 t = mydata->meshTranslation;

		D3DXMATRIXA16 mat;

		// PhysX�p���̎擾
		float glMat[16];
		actor->getGlobalPose().getColumnMajor44(glMat);
		//ConvertMatrix(mtxWorld, glMat);

		// ���b�V���̊g��k��
		D3DXMatrixScaling(&mat, s.x, s.y, s.z);
		D3DXMatrixMultiply(&mtxWorld, &mat, &mtxWorld);

		// ���b�V���̉�]
		mat = mydata->meshRotation;
		D3DXMatrixMultiply(&mtxWorld, &mat, &mtxWorld);

		// ���b�V���̌��_����
		D3DXMatrixTranslation(&mat, t.x, t.y, t.z);
		D3DXMatrixMultiply(&mtxWorld, &mat, &mtxWorld);

		// �}�g���b�N�X�̃Z�b�g
		m_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
		// ���b�V���̕`��
		int n = mydata->ID;
		for (DWORD i = 0; i < g_dwNumMaterials[n]; i++)
		{
			// �}�e���A���ƃe�N�X�`��
			m_pD3DDevice->SetMaterial(&g_pMeshMaterials[n][i]);
			m_pD3DDevice->SetTexture(0, g_pMeshTextures[n][i]);

			// �`��
			g_pMesh[n]->DrawSubset(i);
		}
		/*if (NxA_pCoffee && NxA_pEnban)
		{
			gScene->setActorPairFlags(*NxA_pCoffee,
				*NxA_pEnban,
				NX_NOTIFY_ON_START_TOUCH | NX_NOTIFY_ON_END_TOUCH);
		}*/
		// �Q�̃A�N�^�[���֘A�Â��ďՓˊJ�n�ƏՓˏI���C�x���g��L���ɂ���
		//�����蔻�菈���@�������Ƒ������ɓ����蔻����s���A�N�^�[���w�肷��
		/*	if (MODELL_PLAYER)
		{
		gScene->setActorPairFlags(*NxA_pPlayer,
		*NxA_pBoss,
		NX_NOTIFY_ON_START_TOUCH | NX_NOTIFY_ON_END_TOUCH);
		}*/
	}
}

void CPhysx::RenderThing(D3DXMATRIX mtxWorld, NxActor* actor, int type, THING2* pThing)
{
	// PhysX�̃V�[�����`�F�b�N
	if (gScene == NULL) return;
	// PhysX���ԃX�e�b�v
	gScene->simulate(1.0f / 60.0f);

	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	m_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);

	myData* mydata = (myData*)actor->userData;

	mydata->meshTranslation.x = mtxWorld._41;
	mydata->meshTranslation.y = mtxWorld._42;
	mydata->meshTranslation.z = mtxWorld._43;
	actor->setGlobalPosition(mydata->meshTranslation);

	D3DXMATRIXA16 mat;
	D3DXMATRIXA16 mtxWorld2;
	// PhysX�p���̎擾
	float glMat[16];
	actor->getGlobalPose().getColumnMajor44(glMat);
	ConvertMatrix(mtxWorld2, glMat);

	NxVec3 s = mydata->meshScale;
	NxVec3 t = mydata->meshTranslation;
	// ���b�V���̊g��k��
	D3DXMatrixScaling(&mat, s.x, s.y, s.z);
	D3DXMatrixMultiply(&mtxWorld, &mat, &mtxWorld);

	// ���b�V���̉�]
	mat = mydata->meshRotation;
	//D3DXMatrixMultiply(&mtxWorld2, &mat, &mtxWorld2);
	D3DXMatrixMultiply(&mtxWorld, &mat, &mtxWorld);

	D3DXMatrixTranslation(&mat, 0, 0, 0);
	D3DXMatrixMultiply(&mtxWorld, &mat, &mtxWorld);
	// �}�g���b�N�X�̃Z�b�g
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);


	for (DWORD i = 0; i<pThing->dwNumMaterials; i++)
	{
		m_pD3DDevice->SetMaterial(&pThing->pMeshMaterials[i]);
		m_pD3DDevice->SetTexture(0, pThing->pMeshTextures[i]);
		pThing->pMesh->DrawSubset(i);
	}
	//�@�o�E���f�B���O�X�t�B�A�̃����_�����O	
	if (boRenderSphere)
	{
		m_pD3DDevice->SetTexture(0, NULL);
		m_pD3DDevice->SetMaterial(pThing->pSphereMeshMaterials);
		pThing->pSphereMesh->DrawSubset(0);
	}
	//�����蔻��
	if (Collision(&Thing2[0], &Thing2[1]))
	{
		DebugFont_Draw(500, 300, "�����������I�I�I�I�I�I�I�I�I�I�I");
		C3DObj *pplayer = CPlayer::Get_Player();
		NxActor *pactor = pplayer->Get_Actor();
			//C3DObj *penemy = CEnemy_Small::Get_EnemySmall();
			if (actor != pactor)
			{
				//NxActor *actor = penemy->Get_Actor();
				actor->addForce(NxVec3(500000000, -2000000, 0));
				actor->setLinearVelocity(NxVec3(20, 0, 0));
				actor->addLocalTorque(NxVec3(100000, 0, 0), NX_FORCE);
			}
		
	}
	else
	{
		DebugFont_Draw(500, 500, "�������ĂȂ����I�I�I�I�I�I�I�I�I�I�I");
	}
}

// �}�g���b�N�X�̕ϊ� RenderPhysX�@DrawDirectXMesh
void CPhysx::ConvertMatrix(D3DXMATRIXA16 &matWorld, float *glMat) //(D3DXMATRIXA16 &matWorld, float *glMat)
{
	matWorld._11 = *glMat++;
	matWorld._12 = *glMat++;
	matWorld._13 = *glMat++;
	matWorld._14 = *glMat++;
	matWorld._21 = *glMat++;
	matWorld._22 = *glMat++;
	matWorld._23 = *glMat++;
	matWorld._24 = *glMat++;
	matWorld._31 = *glMat++;
	matWorld._32 = *glMat++;
	matWorld._33 = *glMat++;
	matWorld._34 = *glMat++;
	matWorld._41 = *glMat++;
	matWorld._42 = *glMat++;
	matWorld._43 = *glMat++;
	matWorld._44 = *glMat++;
}


//	�����蔻��

// �{�b�N�X�^�̃��b�V���̐���
NxActor* CPhysx::CreateMeshAsBox(NxVec3 position, NxMat33 rotation, NxVec3 scale, NxVec3 boundingbox, int ID)
{
	myData mydata;
	mydata.meshScale = scale;
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	mydata.meshTranslation = NxVec3(0, -boundingbox.y, 0);
	mydata.meshRotation = mat;
	// PhysX�̃{�b�N�X
	mydata.dimension = NxVec3(boundingbox.x * scale.x, boundingbox.y * scale.y, boundingbox.z * scale.z);
	mydata.ID = ID;
	mydata.type = 'B';
	mydata.rotation = rotation;
	mydata.position = position;
	mydata.hit = false;
	return CreateBox(mydata, &NxVec3(1.0f, 1.0f, 1.0f));
}

// �{�b�N�X�^�̃��b�V���̐���2
NxActor* CPhysx::CreateMeshAsBox(NxVec3 position, NxMat33 rotation, NxVec3 scale, NxVec3 boundingbox, int ID, bool type)
{
	myData mydata;
	mydata.meshScale = scale;
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	mydata.meshTranslation = NxVec3(0, -boundingbox.y, 0);
	mydata.meshRotation = mat;
	// PhysX�̃{�b�N�X
	mydata.dimension = NxVec3(boundingbox.x * scale.x, boundingbox.y * scale.y, boundingbox.z * scale.z);
	mydata.ID = ID;
	mydata.type = 'B';
	mydata.rotation = rotation;
	mydata.position = position;
	mydata.hit = false;
	return CreateBox(mydata, &NxVec3(1.0f, 1.0f, 1.0f), type);
}

// ���^�̃��b�V���̐���
NxActor* CPhysx::CreateMeshAsSphere(NxVec3 position, float r, int ID)
{
	myData mydata;
	// ���b�V���̊g��k��
	mydata.meshScale = NxVec3(1, 1, 1);
	mydata.meshTranslation = NxVec3(0, 0, 0);
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	mydata.meshRotation = mat;
	// PhysX�̋�
	mydata.radius = r;
	mydata.dimension = NxVec3(r, r, r);
	mydata.ID = ID;
	NxMat33 mat2;
	mat2.rotX(0);
	mydata.rotation = mat2;
	mydata.position = position;
	mydata.hit = false;
	return CreateSphere(mydata, &NxVec3(1.0f, 1.0f, 1.0f));
}

//�J�v�Z���^�̃��b�V���̐���
NxActor* CPhysx::CreateMeshAsCapsule(NxVec3 position, NxMat33 rotation, NxVec3 scale, float r, float h, int ID)
{
	myData mydata;
	// ���b�V���̊g��k��
	mydata.meshScale = scale;
	float Radius = r * scale.x;
	float Height = h * scale.y;
	mydata.meshTranslation = NxVec3(0, -h / 2 - r + 0.01f, 0);
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	mydata.meshRotation = mat;
	// PhysX�̋�
	mydata.radius = Radius;
	mydata.height = Height;
	mydata.dimension = NxVec3(Radius, Height, Radius);
	mydata.ID = ID;
	mydata.rotation = rotation;
	mydata.position = position;
	return CreateCapsule(mydata, &NxVec3(1.0f, 1.0f, 1.0f));
}

// �{�b�N�X�̐���
NxActor* CPhysx::CreateBox(myData mydata, const NxVec3* initialVelocity)
{
	if (gScene == NULL) return NULL;

	myData* data = new myData;
	*data = mydata;
	data->type = 'B';
	// �f�X�N���v�^
	NxBodyDesc bodyDesc;
	bodyDesc.angularDamping = 0.5f;
	if (initialVelocity) bodyDesc.linearVelocity = *initialVelocity;

	NxBoxShapeDesc boxDesc;
	boxDesc.dimensions = data->dimension;

	NxActorDesc actorDesc;
	actorDesc.shapes.pushBack(&boxDesc);//�����ŃA�N�^�[�Ƀ{�b�N�X�R���W������o�^
	actorDesc.body = &bodyDesc;//�����œ��I�����擾
	actorDesc.density = 10.0f;//����
	actorDesc.globalPose.t = data->position;//���[���h��Ԃ̈ʒu�ɒu��
	actorDesc.globalPose.M = data->rotation;//PhysX���ł͉E����W�n�Ȃ̂œ]�u�s����Z�b�g����
	actorDesc.userData = data;

	return gScene->createActor(actorDesc);//�V�[���ɑ΂��āA�w��̃A�N�^�[��ǉ�
}

// �{�b�N�X�̐���
NxActor* CPhysx::CreateBox(myData mydata, const NxVec3* initialVelocity, bool type)
{
	if (gScene == NULL) return NULL;

	myData* data = new myData;
	*data = mydata;
	data->type = 'B';
	// �f�X�N���v�^
	NxBodyDesc bodyDesc;
	bodyDesc.angularDamping = 0.5f;
	if (initialVelocity) bodyDesc.linearVelocity = *initialVelocity;

	NxBoxShapeDesc boxDesc;
	boxDesc.dimensions = data->dimension;

	NxActorDesc actorDesc;
	actorDesc.shapes.pushBack(&boxDesc);//�����ŃA�N�^�[�Ƀ{�b�N�X�R���W������o�^
	if (!type)
	{
		actorDesc.body = NULL;//������NULL�ɂ���ƐÓI�A�N�^�[�ɂȂ�
	}
	else
	{
		actorDesc.body = &bodyDesc;//�����œ��I�����擾
	}
	actorDesc.density = 10.0f;//����
	actorDesc.globalPose.t = data->position;//���[���h��Ԃ̈ʒu�ɒu��
	actorDesc.globalPose.M = data->rotation;//PhysX���ł͉E����W�n�Ȃ̂œ]�u�s����Z�b�g����
	actorDesc.userData = data;

	return gScene->createActor(actorDesc);//�V�[���ɑ΂��āA�w��̃A�N�^�[��ǉ�
}

// ���̐���
NxActor* CPhysx::CreateSphere(myData mydata, const NxVec3* initialVelocity)
{
	if (gScene == NULL) return NULL;

	myData* data = new myData;
	*data = mydata;
	data->type = 'S';
	// �f�X�N���v�^
	NxBodyDesc bodyDesc;
	bodyDesc.angularDamping = 0.5f;
	if (initialVelocity) bodyDesc.linearVelocity = *initialVelocity;

	NxSphereShapeDesc sphereDesc;
	sphereDesc.radius = data->radius;

	NxActorDesc actorDesc;
	actorDesc.shapes.pushBack(&sphereDesc); // �����ŃA�N�^�[�ɃX�t�B�A�R���W������o�^
	actorDesc.body = NULL;//�����œ��I�����擾
	actorDesc.density = 10.0f;//����
	actorDesc.globalPose.t = data->position;//���[���h��Ԃ̈ʒu�ɒu��
	actorDesc.globalPose.M = data->rotation;//PhysX���ł͉E����W�n�Ȃ̂œ]�u�s����Z�b�g����
	actorDesc.userData = data;

	return gScene->createActor(actorDesc);
}

// �J�v�Z���̐���
NxActor* CPhysx::CreateCapsule(myData mydata, const NxVec3* initialVelocity)
{
	if (gScene == NULL) return NULL;

	myData* data = new myData;
	*data = mydata;
	data->type = 'C';
	// �f�X�N���v�^
	NxBodyDesc bodyDesc;
	bodyDesc.angularDamping = 0.5f;
	if (initialVelocity) bodyDesc.linearVelocity = *initialVelocity;

	NxCapsuleShapeDesc capsuleDesc;
	capsuleDesc.radius = data->radius;
	capsuleDesc.height = data->height;

	NxActorDesc actorDesc;
	actorDesc.shapes.pushBack(&capsuleDesc);// �����ŃA�N�^�[�ɃJ�v�Z���R���W������o�^
	actorDesc.body = &bodyDesc;//�����œ��I�����擾;
	actorDesc.density = 10.0f;//����
	actorDesc.globalPose.t = data->position;//���[���h��Ԃ̈ʒu�ɒu��
	actorDesc.globalPose.M = data->rotation;//PhysX���ł͉E����W�n�Ȃ̂œ]�u�s����Z�b�g����
	actorDesc.userData = data;

	return gScene->createActor(actorDesc);
}


//�f�o�b�O�`��

// �f�o�b�O�f�[�^�̃Z�b�g�i�f�o�b�N�R���W�����s��j
HRESULT CPhysx::CreateDebugBase()
{
	float a = 4.0f;	// ���W���̒���
	float b = 2.0f; // �}�b�g�̒���
	float c = b / 2;
	float d = 1.0f; // �{�b�N�X�̐��@
	float r = 1.0f; // ���̔��a
	float r1 = r * 1.41421356f / 2;
	float h = r / 2;

	// ���_
	CUSTOMVERTEX g_Vertices[] =
	{
		// ���W��
		{ b, 0, b, },		// 0
		{ b, 0, -b, },
		{ c, 0, -b, },
		{ c, 0,  b, },
		{ 0, 0, b, },
		{ 0, 0, -b, },
		{ -c, 0, -b, },
		{ -c, 0,  b, },
		{ -b, 0, b, },
		{ -b, 0,  -b, },
		{ b, 0, -b, },
		{ b, 0, -c, },
		{ -b, 0, -c, },
		{ -b, 0,  0, },
		{ b, 0, 0, },
		{ b, 0, c, },
		{ -b, 0, c, },
		{ -b, 0, b, },
		{ b, 0, b, },
		// 
		{ 0, 0, 0, },		// 19
		{ 0, a, 0, },
		{ 0, 0, 0, },
		// �{�b�N�X
		{ -d, -d, -d, },	// 22
		{ -d, -d,  d, },
		{ -d,  d,  d, },
		{ -d,  d, -d, },

		{ d, -d, -d, },	// 26
		{ -d, -d, -d, },
		{ -d,  d, -d, },
		{ d,  d, -d, },

		{ d, -d,  d, },	// 30
		{ d, -d, -d, },
		{ d,  d, -d, },
		{ d,  d,  d, },

		{ -d, -d,  d, },	// 34
		{ d, -d,  d, },
		{ d,  d,  d, },
		{ -d,  d,  d, },
		// ��
		{ r, 0,   0, },	// 38
		{ r1, 0,  r1, },
		{ 0, 0,   r, },
		{ -r1, 0,  r1, },
		{ -r, 0,   0, },
		{ -r1, 0, -r1, },
		{ 0, 0,  -r, },
		{ r1, 0, -r1, },
		{ r, 0,   0, },

		{ r,   0, 0, },	// 47
		{ r1,  r1, 0, },
		{ 0,   r, 0, },
		{ -r1,  r1, 0, },
		{ -r,   0, 0, },
		{ -r1, -r1, 0, },
		{ 0,  -r, 0, },
		{ r1, -r1, 0, },
		{ r,   0, 0, },

		{ 0,   0,   r, },	// 56
		{ 0,  r1,  r1, },
		{ 0,   r,   0, },
		{ 0,  r1, -r1, },
		{ 0,   0,  -r, },
		{ 0, -r1, -r1, },
		{ 0,  -r,   0, },
		{ 0, -r1,  r1, },
		{ 0,   0,   r, },
		// �J�v�Z��
		{ -r,  h, 0, },		// 65
		{ -r, -h, 0, },
		{ r,  h, 0, },		// 67
		{ r, -h, 0, },
		{ 0, h,   -r, },	// 69
		{ 0, -h,  -r, },
		{ 0, h,   r, },		// 71
		{ 0, -h,  r, },
	};

	// ���_�o�b�t�@�̐���
	if (FAILED(m_pD3DDevice->CreateVertexBuffer(100 * sizeof(CUSTOMVERTEX),
		0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &g_pVB, NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�ւ̓]��
	VOID* pVertices;
	if (FAILED(g_pVB->Lock(0, sizeof(g_Vertices), (void**)&pVertices, 0)))
		return E_FAIL;
	memcpy(pVertices, g_Vertices, sizeof(g_Vertices));
	g_pVB->Unlock();
	return S_OK;
}

// �{�b�N�X�̕`��
void CPhysx::DrawBox(NxActor* actor, D3DXMATRIXA16 &matWorld)
{
	D3DXMATRIXA16 mat;
	myData* mydata = (myData*)actor->userData;
	NxVec3 v = mydata->dimension;
	D3DXMatrixScaling(&mat, v.x, v.y, v.z);
	// ���[���h�֏�Z
	D3DXMatrixMultiply(&matWorld, &mat, &matWorld);
	// �o�b�t�@�֓]��
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 22, 3);
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 26, 3);
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 30, 3);
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 34, 3);
}

// ���̕`��
void CPhysx::DrawSphere(NxActor* actor, D3DXMATRIXA16 &matWorld)
{
	D3DXMATRIXA16 mat;
	myData* mydata = (myData*)actor->userData;
	// ���@�̎擾
	NxVec3 v = mydata->dimension;
	float r = mydata->radius;
	D3DXMatrixScaling(&mat, r, r, r);
	// ���[���h�֏�Z
	D3DXMatrixMultiply(&matWorld, &mat, &matWorld);
	// �o�b�t�@�֓]��
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 38, 8);
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 47, 8);
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 56, 8);
}

// �J�v�Z���̕`��
void CPhysx::DrawCapsule(NxActor* actor, D3DXMATRIXA16 &matWorld)
{
	D3DXMATRIXA16 mat, matold;
	matold = matWorld;
	myData* mydata = (myData*)actor->userData;
	float r = mydata->radius;
	float h = mydata->height;
	D3DXMatrixScaling(&mat, r, h, r);
	// ���[���h�֏�Z
	D3DXMatrixMultiply(&matWorld, &mat, &matWorld);
	// �o�b�t�@�֓]��
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	// �����̕`��
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 65, 1);
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 67, 1);
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 69, 1);
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 71, 1);
	//
	matWorld = matold;
	D3DXMatrixTranslation(&mat, 0, h / 2, 0);
	D3DXMatrixMultiply(&matWorld, &mat, &matWorld);
	D3DXMatrixScaling(&mat, r, r, r);
	D3DXMatrixMultiply(&matWorld, &mat, &matWorld);

	m_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	// �㕔�̔����̕`��
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 47, 4);
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 56, 4);
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 38, 8);

	matWorld = matold;
	D3DXMatrixTranslation(&mat, 0, -h / 2, 0);
	D3DXMatrixMultiply(&matWorld, &mat, &matWorld);
	D3DXMatrixScaling(&mat, r, r, r);
	D3DXMatrixMultiply(&matWorld, &mat, &matWorld);
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	// �����̔����̕`��
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 51, 4);
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 60, 4);
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 38, 8);
}



//�����蔻��C�x���g�ʒm�N���X  �@hit���k
void CPhysx::ContactCallBack::onContactNotify(NxContactPair& pair, NxU32 events)
{
	// �A�N�^�[�Ŏg�p���郆�[�U�[�f�[�^
	USERDATA* pUserData1 = NULL;
	USERDATA* pUserData2 = NULL;
	myData* mydata = (myData*)pair.actors[0]->userData;
	myData* mydata2 = (myData*)pair.actors[0]->userData;
	switch (events)
	{
		// �ՓˊJ�n�C�x���g�ʒm
	case NX_NOTIFY_ON_START_TOUCH:

		// �ՓˑΏۂ̂Q�̃A�N�^�[�̃��[�U�[�f�[�^�̃|�C���^���擾����B
		pUserData1 = (USERDATA*)pair.actors[0]->userData;
		pUserData2 = (USERDATA*)pair.actors[1]->userData;
		pair.actors[1]->addForce(NxVec3(500000, -2000000, 0));
		pair.actors[1]->setLinearVelocity(NxVec3(20, 0, 0));
		pair.actors[1]->addLocalTorque(NxVec3(100000, 0, 0), NX_FORCE);
		// ���[�U�[�f�[�^�ɃC�x���g����ݒ肷��
		//pUserData1->ContactPairFlag = events;
		//pUserData2->ContactPairFlag = events;
		
		mydata->hit = true;
		mydata2->hit = true;
		break;

		// �ՓˏI���C�x���g�ʒm
	case NX_NOTIFY_ON_END_TOUCH:

	//	myData* mydata2 = (myData*)pair.actors[0]->userData;
		mydata->hit = false;
		mydata2->hit = false;
		// �ՓˑΏۂ̂Q�̃A�N�^�[�̃��[�U�[�f�[�^�̃|�C���^���擾����B
		//pUserData1 = (USERDATA*)pair.actors[0]->userData;
		//pUserData2 = (USERDATA*)pair.actors[1]->userData;

		// ���[�U�[�f�[�^�� 0 �ɏ���������
		//pUserData1->ContactPairFlag = 0;
		//pUserData2->ContactPairFlag = 0;

		break;
	}
}


void CPhysx::Debug_Collision(SphereCollision sc, D3DXMATRIX mtx)
{
	//DebugFont_Draw(700, 300, "%f\n,%f\n,%f\n,", sc.CenterPos.x, sc.CenterPos.y, sc.CenterPos.z);

	D3DXMATRIX mtxS;
	D3DXMatrixScaling(&mtxS, sc.radius, sc.radius, sc.radius);
	// ���[���h�֏�Z
	//D3DXMatrixMultiply(&mtx, &mtxR, &mtx);
	mtx = mtxS * mtx;
	// �o�b�t�@�֓]��
	m_pD3DDevice->SetStreamSource(0, g_pVB, 0, sizeof(CUSTOMVERTEX));
	m_pD3DDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &mtx);
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 38, 8);
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 47, 8);
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 56, 8);
}

THING* CPhysx::GetAnimeModel(int index)
{
	return &Thing[index];
}

THING2* CPhysx::GetNormalModel(int index)
{
	return &Thing2[index];
}