//////////////////////////////////////////////////
////
////	3D�I�u�W�F�N�g�N���X
////
//////////////////////////////////////////////////

#include "C3DObj.h"
#include "debug_font.h"
#include "CTexture.h"
#include "Cplayer.h"
#include "exp.h"
//=============================================================================
//	�ÓI�ϐ�
//===========================================================================
C3DObj *C3DObj::p3DObj[MAX_GAMEOBJ];
int C3DObj::m_3DObjNum = 0;
int C3DObj::m_TotalScore = 0;
THING C3DObj::Thing_Anime[5];//�ǂݍ��ރ��f���̍ő吔+1
bool C3DObj::GetWCos = false;

C3DObj::MaterialFileData C3DObj::NORMAL_MODEL_FILES[] = {
	{ "asset/model/emi-ru2.x" },
	{ "asset/model/dish.blend.x" },
	{ "asset/model/enban.x" },
	{ "asset/model/hasira.x" },
	{ "asset/model/ferris.x" },
	{ "asset/model/jet_new.blend.x" },
	{ "asset/model/cup_blue.x" },
	{ "asset/model/cup_kiiro.x" },
	{ "asset/model/cup_midori.x" },
	{ "asset/model/pop.blend.x" },
	{ "asset/model/kensetutyuu.x" },
	{ "asset/model/ornament/lamp.x" },
	{ "asset/model/ornament/gomibako.x" },
	{ "asset/model/ornament/bench.x" },
	{ "asset/model/ornament/hunsui.x" },
	{ "asset/model/ornament/kanransya_Obj.blend.x" },
	{ "asset/model/ornament/husen.blend.x" },
	{ "asset/model/ornament/meri_dodai.blend.x" },
	{ "asset/model/ornament/Uma.blend.x" },
	{ "asset/model/ornament/kanransya_ornament.x" },
};
//	�g�������A�j�����f���̐���������
C3DObj::MaterialFileData2 C3DObj::ANIME_MODEL_FILES[] = {
	{ "asset/anime_model/hewplayer.x" },
	{ "asset/anime_model/small_enemy.x" },
	{ "asset/anime_model/middle_enemy.x" },
	{ "asset/anime_model/special_enemy.x" },
	{ "asset/anime_model/big_enemy.x" },
};
int C3DObj::MODEL_FILES_MAX = sizeof(C3DObj::NORMAL_MODEL_FILES) / sizeof(NORMAL_MODEL_FILES[0]);
int C3DObj::ANIME_MODEL_FILES_MAX = sizeof(C3DObj::ANIME_MODEL_FILES) / sizeof(ANIME_MODEL_FILES[0]);

bool C3DObj::boRenderSphere = true;
//���f���A�j���[�V�����֌W�ϐ�
/*
#define MODEL_MAX (9)

SKIN_MESH SkinMesh;
THING_NORMAL Thing_Normal[MODEL_MAX+1];//�ǂݍ��ރ��f���̍ő吔+1
THING Thing[THING_AMOUNT + 1];//�ǂݍ��ރ��f���̍ő吔+1
LPD3DXANIMATIONSET pAnimSet[THING_AMOUNT][10] = { 0 };//�I���������f����10�܂ł̃A�j���[�V�������Z�b�g
FLOAT fAnimTime = 0.0f;
BOOL boPlayAnim = true;
D3DXTRACK_DESC TrackDesc;
*/

//SKIN_MESH C3DObj::SkinMesh;
THING_NORMAL C3DObj::Thing_Normal[(sizeof(C3DObj::NORMAL_MODEL_FILES) / sizeof(NORMAL_MODEL_FILES[0]))];//�ǂݍ��ރ��f���̍ő吔+1
//THING C3DObj::Thing[sizeof(C3DObj::ANIME_MODEL_FILES) / sizeof(ANIME_MODEL_FILES[0])];//�ǂݍ��ރ��f���̍ő吔+1


LPD3DXMESH C3DObj::m_pD3DXMesh[sizeof(C3DObj::NORMAL_MODEL_FILES) / sizeof(NORMAL_MODEL_FILES[0])] = {};
DWORD C3DObj::m_dwNumMaterials[sizeof(C3DObj::NORMAL_MODEL_FILES) / sizeof(NORMAL_MODEL_FILES[0])] = {};
LPD3DXBUFFER C3DObj::m_pD3DXMtrBuffer[sizeof(C3DObj::NORMAL_MODEL_FILES) / sizeof(NORMAL_MODEL_FILES[0])] = {};
LPDIRECT3DTEXTURE9 *C3DObj::m_pTexures[sizeof(C3DObj::NORMAL_MODEL_FILES) / sizeof(NORMAL_MODEL_FILES[0])] = {};
D3DMATERIAL9 *C3DObj::m_pd3dMaterials[sizeof(C3DObj::NORMAL_MODEL_FILES) / sizeof(NORMAL_MODEL_FILES[0])] = {};

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
	m_DamageFlag = false;
	m_AttakFlag = false;
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
		GetWCos = CPlayer::GetCoaster_Enable();
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
// Geometry�̏������i���f���̓ǂݍ��݁j
HRESULT C3DObj::InitModelLoad()
{
	//�ʏ탂�f���ǂݍ���	
	for (int i = 0; i < MODEL_FILES_MAX; i++)
	{
		InitThing(&Thing_Normal[i], NORMAL_MODEL_FILES[i].filename);
		InitSphere(m_pD3DDevice, &Thing_Normal[i]);//�����蔻��̕\��
	}

	//�A�j���[�V�������f���ǂݍ���
	//THING��x�t�@�C����ǂݍ���
	/*for (int i = 0; i < ANIME_MODEL_FILES_MAX; i++)
	{
		SkinMesh.InitThing(m_pD3DDevice, &Thing[i], ANIME_MODEL_FILES[i].filename);
		SkinMesh.InitSphere(m_pD3DDevice, &Thing[i]);
	}*/
	return S_OK;
}

HRESULT C3DObj::InitThing(THING_NORMAL *pThing, LPSTR szXFileName)
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
// ���f���`��  �A�j���[�V�����L
//=============================================================================
void C3DObj::DrawDX_Anime(D3DXMATRIX mtxWorld, int type, THING* pThing)
{
	//static float fAnimTimeHold = fAnimTime;
	float fAnimTimeHold = fAnimTime;
	if (boPlayAnim)
	{
		fAnimTime += 0.01f;
	}

	SKIN_MESH::UpdateSphere(m_pD3DDevice, pThing);

	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
//	m_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
//	m_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);
	//m_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	//m_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);


	D3DXMATRIXA16 mat;

	m_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//���f�������_�����O
	SkinMesh.UpdateFrameMatrices(pThing->pFrameRoot, &mtxWorld);
	SkinMesh.DrawFrame(m_pD3DDevice, pThing->pFrameRoot, pThing, true);
	pThing->pAnimController->AdvanceTime(fAnimTime - fAnimTimeHold, NULL);
	//�@�o�E���f�B���O�X�t�B�A�̃����_�����O////////	
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
	////////////////////////////////
	//�A�j���Đ����Ԃ�+
/*	fAnimTimeHold = fAnimTime;
	if (boPlayAnim)
	{
		fAnimTime += 0.01f;
	}*/
}



//=============================================================================
// ���f���`��  �A�j���[�V������
//=============================================================================
void C3DObj::DrawDX_Normal(D3DXMATRIX mtxWorld, int type, THING_NORMAL* pThing)
{
	
	//m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	m_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);


	// �}�g���b�N�X�̃Z�b�g
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//���f���̃����_�����O
	for (DWORD i = 0; i<pThing->dwNumMaterials; i++)
	{
		m_pD3DDevice->SetMaterial(&pThing->pMeshMaterials[i]);
		m_pD3DDevice->SetTexture(0, pThing->pMeshTextures[i]);
		pThing->pMesh->DrawSubset(i);
	}
	//�@�o�E���f�B���O�X�t�B�A�̃����_�����O	
	if (boRenderSphere && pThing->pSphereMeshMaterials)
	{
		m_pD3DDevice->SetTexture(0, NULL);
		m_pD3DDevice->SetMaterial(pThing->pSphereMeshMaterials);
		pThing->pSphereMesh->DrawSubset(0);
	}

}

// ���f���`��  �A�j���[�V������ �R���W�����ʒu�ύX
void C3DObj::DrawDX_NormalAdd(D3DXMATRIX mtxWorld, int type, THING_NORMAL* pThing, D3DXVECTOR3 position)
{

	//m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	m_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);


	// �}�g���b�N�X�̃Z�b�g
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//���f���̃����_�����O
	for (DWORD i = 0; i<pThing->dwNumMaterials; i++)
	{
		m_pD3DDevice->SetMaterial(&pThing->pMeshMaterials[i]);
		m_pD3DDevice->SetTexture(0, pThing->pMeshTextures[i]);
		pThing->pMesh->DrawSubset(i);
	}
	D3DXMATRIX mtx;
	D3DXMatrixTranslation(&mtx, mtxWorld._41 + position.x, mtxWorld._42 + position.y, mtxWorld._43 + position.z);
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &mtx);
	//�@�o�E���f�B���O�X�t�B�A�̃����_�����O	
	if (boRenderSphere && pThing->pSphereMeshMaterials)
	{
		m_pD3DDevice->SetTexture(0, NULL);
		m_pD3DDevice->SetMaterial(pThing->pSphereMeshMaterials);
		pThing->pSphereMesh->DrawSubset(0);
	}

}

void C3DObj::DrawDX_NormalAddScale(D3DXMATRIX mtxWorld, int type, THING_NORMAL* pThing, D3DXVECTOR3 position, D3DXVECTOR3 scale)
{

	//m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	m_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);


	// �}�g���b�N�X�̃Z�b�g
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//���f���̃����_�����O
	for (DWORD i = 0; i<pThing->dwNumMaterials; i++)
	{
		m_pD3DDevice->SetMaterial(&pThing->pMeshMaterials[i]);
		m_pD3DDevice->SetTexture(0, pThing->pMeshTextures[i]);
		pThing->pMesh->DrawSubset(i);
	}
	D3DXMATRIX mtxworld;
	D3DXMATRIX mtxScale;
	D3DXMATRIX mtxrotation;
	D3DXMATRIX mtx;
	D3DXMatrixTranslation(&mtx, mtxWorld._41 + position.x, mtxWorld._42 + position.y, mtxWorld._43 + position.z);
	D3DXMatrixRotationX(&mtxrotation, D3DXToRadian(0));
	D3DXMatrixScaling(&mtxScale, scale.x, scale.y, scale.z);
	mtxworld = mtxScale * mtxrotation * mtx;
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxworld);
	//�@�o�E���f�B���O�X�t�B�A�̃����_�����O	
	if (boRenderSphere && pThing->pSphereMeshMaterials)
	{
		m_pD3DDevice->SetTexture(0, NULL);
		m_pD3DDevice->SetMaterial(pThing->pSphereMeshMaterials);
		pThing->pSphereMesh->DrawSubset(0);
	}

}
void C3DObj::DrawDX_NormalCapsule(D3DXMATRIX mtxWorld, int type, THING_NORMAL* pThing, D3DXVECTOR3 position, float rotation)
{
	//m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	m_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);


	// �}�g���b�N�X�̃Z�b�g
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//���f���̃����_�����O
	for (DWORD i = 0; i<pThing->dwNumMaterials; i++)
	{
		m_pD3DDevice->SetMaterial(&pThing->pMeshMaterials[i]);
		m_pD3DDevice->SetTexture(0, pThing->pMeshTextures[i]);
		pThing->pMesh->DrawSubset(i);
	}
	D3DXMATRIX mtxworld;
	D3DXMATRIX mtx;
	D3DXMATRIX mtxRotation;
	D3DXMatrixTranslation(&mtx, mtxWorld._41 + position.x, mtxWorld._42 + position.y, mtxWorld._43 + position.z);
	D3DXMatrixRotationX(&mtxRotation, D3DXToRadian(rotation));
	mtxworld = mtxRotation * mtx;
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &mtxworld);
	//�@�o�E���f�B���O�X�t�B�A�̃����_�����O	
	if (boRenderSphere && pThing->pSphereMeshMaterials)
	{
		m_pD3DDevice->SetTexture(0, NULL);
		m_pD3DDevice->SetMaterial(pThing->pSphereMeshMaterials);
		pThing->pSphereMesh->DrawSubset(0);
	}
}

//=============================================================================
// �����蔻��
//=============================================================================

void C3DObj::HitCheck(void)
{
	//�m�[�}�����f���΃m�[�}�����f��
	/*
	if (Collision_NomalVSNormal(&Thing_Normal[0], &Thing_Normal[1]))
	{
		DebugFont_Draw(500, 300, "�����������I�I�I�I�I�I�I�I�I�I�I");
	}
	else
	{
		DebugFont_Draw(500, 500, "�������ĂȂ����I�I�I�I�I�I�I�I�I�I�I");
	}*/
	//DebugFont_Draw(200, 50, "�G�l�~�[�|�W�V����= X= %f Y= %f Z = %f", Thing[0].vPosition.x, Thing[0].vPosition.y, Thing[0].vPosition.z);
	//DebugFont_Draw(200, 80, "�v���C���[�|�W�V����= X= %f Y= %f Z = %f", Thing_Normal[0].vPosition.x, Thing_Normal[0].vPosition.y, Thing_Normal[0].vPosition.z);
	//�A�j���΃m�[�}��
	/*if (Collision_AnimeVSNormal(&Thing[0], &Thing_Normal[0]))
	{
		DebugFont_Draw(500, 300, "�����������I�I");
	}
	else
	{
		DebugFont_Draw(500, 500, "�������ĂȂ����I�I�I�I�I�I�I�I�I�I�I");
	}*/
	if (Collision_AnimeVSNormal(&Thing, &Thing_Normal[0]))
	{
	DebugFont_Draw(500, 300, "�����������I�I");
	}
	else
	{
	DebugFont_Draw(500, 500, "�������ĂȂ����I�I�I�I�I�I�I�I�I�I�I");
	}
	/*
	//�A�j���΃A�j��
	if (Collision_AnimeVSAnime(&Thing[0], &Thing[0]))
	{
		DebugFont_Draw(500, 300, "�����������I�I");
	}
	else
	{
		DebugFont_Draw(500, 500, "�������ĂȂ����I�I�I�I�I�I�I�I�I�I�I");
	}*/
}

bool C3DObj::Collision_NomalVSNormal(THING_NORMAL* pThingA, THING_NORMAL* pThingB)
{
	//�Q�̕��̂̒��S�Ԃ̋��������߂�
	D3DXVECTOR3 vLength = pThingB->vPosition - pThingA->vPosition;
	FLOAT fLength = D3DXVec3Length(&vLength);
	// ���̋������A2���̂̔��a�𑫂������̂�菬�����Ƃ������Ƃ́A
	//���E�����m���d�Ȃ��Ă���i�Փ˂��Ă���j�Ƃ�������
	if (fLength <= pThingA->Sphere.fRadius + pThingB->Sphere.fRadius)
	{
		return true;
	}
	return false;
}

bool C3DObj::Collision_AnimeVSNormal(THING* pThingA, THING_NORMAL* pThingB)
{
	//�Q�̕��̂̒��S�Ԃ̋��������߂�
	D3DXVECTOR3 vLength = pThingB->vPosition - pThingA->vPosition;
	FLOAT fLength = D3DXVec3Length(&vLength);
	// ���̋������A2���̂̔��a�𑫂������̂�菬�����Ƃ������Ƃ́A
	//���E�����m���d�Ȃ��Ă���i�Փ˂��Ă���j�Ƃ�������
	if (fLength <= pThingA->Sphere.fRadius + pThingB->Sphere.fRadius)
	{
		return true;
	}
	return false;
}

bool C3DObj::Collision_AnimeVSNormalCapsule(THING* pThingA, THING_NORMAL* pThingB)
{
	//�Q�̕��̂̒��S�Ԃ̋��������߂�
	D3DXVECTOR3 vLength = pThingB->vPosition - pThingA->vPosition;
	FLOAT fLength = D3DXVec3Length(&vLength);
	// ���̋������A2���̂̔��a�𑫂������̂�菬�����Ƃ������Ƃ́A
	//���E�����m���d�Ȃ��Ă���i�Փ˂��Ă���j�Ƃ�������
	if (fLength <= pThingA->Sphere.fRadius + ((pThingB->Capsule.fRadius + pThingB->Capsule.fRadius2 + pThingB->Capsule.fLength) / 2))
	{
		return true;
	}
	return false;
}

float C3DObj::GetSqDistancePoint2Segment(THING* pThingA, THING_NORMAL* pThingB)
{
	/*
	const float epsilon = 1.0e-5f;	// �덷�z���p�̔����Ȓl
	D3DXVECTOR3 SegmentSub;
	D3DXVECTOR3 SegmentPoint;
	D3DXVECTOR3 CP;

	// �����̎n�_����I�_�ւ̃x�N�g��
	SegmentSub = pThingB->Capsule.fRadius2 - pThingB->Capsule.fRadius;

	// �����̎n�_����_�ւ̃x�N�g��
	SegmentPoint = _point - _segment.start;
	if (SegmentSub.dot(SegmentPoint) < epsilon)
	{// �Q�x�N�g���̓��ς����Ȃ�A�����̎n�_���ŋߖT
		return SegmentPoint.dot(SegmentPoint);
	}

	// �_��������̏I�_�ւ̃x�N�g��
	SegmentPoint = _segment.end - _point;
	if (SegmentSub.dot(SegmentPoint) < epsilon)
	{// �Q�x�N�g���̓��ς����Ȃ�A�����̏I�_���ŋߖT
		return SegmentPoint.dot(SegmentPoint);
	}

	// ��L�̂ǂ���ɂ��Y�����Ȃ��ꍇ�A������ɗ��Ƃ����ˉe���ŋߖT
	// (�{���Ȃ�T�C���ŋ��߂邪�A�O�ς̑傫��/�����̃x�N�g���̑傫���ŋ��܂�)
	Vec3::cross(SegmentSub, SegmentPoint, &CP);

	return CP.dot(CP) / SegmentSub.dot(SegmentSub);*/
	return 0;
}


bool C3DObj::Collision_AnimeVSAnime(THING* pThingA, THING* pThingB)
{
	//�Q�̕��̂̒��S�Ԃ̋��������߂�
	D3DXVECTOR3 vLength = pThingB->vPosition - pThingA->vPosition;
	FLOAT fLength = D3DXVec3Length(&vLength);
	// ���̋������A2���̂̔��a�𑫂������̂�菬�����Ƃ������Ƃ́A
	//���E�����m���d�Ȃ��Ă���i�Փ˂��Ă���j�Ƃ�������
	if (fLength <= pThingA->Sphere.fRadius + pThingB->Sphere.fRadius)
	{
		return true;
	}
	return false;
}

THING* C3DObj::GetAnimeModel(void)
{
	return &Thing;
}

THING C3DObj::GetAnimeModel(int index)
{
	return Thing_Anime[index];
}

THING_NORMAL C3DObj::GetNormalModel(int index)
{
	return Thing_Normal[index];
}

THING_NORMAL C3DObj::GetNormal(int index)
{
	return Thing_Normal[index];
}

THING_NORMAL C3DObj::GetNormalModel(void)
{
	return Thing_Normal_model;
}

//=============================================================================
// �A�j���[�V�����ύX
//=============================================================================

void C3DObj::Animation_Change(int index, float speed)
{
	if (TrackDesc.Speed != speed)
	{
		TrackDesc.Speed = speed;//���[�V�����X�s�[�h
		Thing.pAnimController->SetTrackDesc(0, &TrackDesc);//�A�j�����Z�b�g
	}
	Thing.pAnimController->SetTrackAnimationSet(0, pAnimSet[index]);

}

void C3DObj::DamageFlag_Change(void)
{
	m_DamageFlag = true;
}

void C3DObj::Position_Keep(D3DXMATRIX mtxT)
{
	m_PosKeep = D3DXVECTOR3(mtxT._41, mtxT._42, mtxT._43);
}

void C3DObj::Add_Mp(int mp)
{
	C3DObj *pplayer = CPlayer::Get_Player();
	pplayer->m_Mp += mp;

	while (pplayer->m_Mp >= MP_MAX)
	{
		pplayer->m_Mp -= MP_MAX;
		pplayer->m_MpStock++;
	}

}

void C3DObj::Attraction_Delete(void)
{
	for (int i = 0; i < MAX_GAMEOBJ; i++)
	{
		if (p3DObj[i])
		{
			if ((p3DObj[i]->m_3DObjType == TYPE_ATTRACTION)|| (p3DObj[i]->m_3DObjType == TYPE_POPCORN)|| (p3DObj[i]->m_3DObjType == TYPE_STADBY)|| (p3DObj[i]->m_3DObjType == TYPE_COASTER))
			{
				delete p3DObj[i];
			}
		}
	}
}

void C3DObj::Add_Hp(void)
{
	C3DObj *pplayer = CPlayer::Get_Player();
	pplayer->m_Hp++;
	Exp_Set(SHINE, pplayer->m_mtxTranslation._41, pplayer->m_mtxTranslation._42 , pplayer->m_mtxTranslation._43, 3.0, 0);
	if (pplayer->m_Hp > HP_MAX)
	{
		pplayer->m_Hp = HP_MAX;
	}
}