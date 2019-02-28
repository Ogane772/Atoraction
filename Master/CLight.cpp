//////////////////////////////////////////////////
////
////	���C�g�N���X
////
//////////////////////////////////////////////////

//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================

#include "CLight.h"
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

#define new  ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

//=============================================================================
//	�萔��`
//=============================================================================


//=============================================================================
//	�ÓI�ϐ�
//=============================================================================

CLight *CLight::m_pLight;


//=============================================================================
//	����
//=============================================================================
CLight::CLight():CGameObj(CGameObj::TYPE_LIGHT)
{
	Light_Initialize();
}

//=============================================================================
//	�j��
//=============================================================================
CLight::~CLight()
{
	//Light_Finalize();
}



void CLight::Update(void)
{
	
}

void CLight::Draw(void)
{
	Light_Set();
}

//	���C�g������
void CLight::Light_Initialize(void)
{
	m_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);	// �@���x�N�g����1�ɂ���
}

CLight* CLight::Light_Create(void)
{
	m_pLight = new CLight;
	return m_pLight;
}

void CLight::Finalize(void)
{
	if (m_pLight != NULL)
	{
		delete m_pLight;
	}
}

//	���C�g�Z�b�g
void CLight::Light_Set(void)
{
	// ���C�e�B���O
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);	//�@���C�e�B���O�L��
	m_pD3DDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_RGBA(77, 67, 65, 255));	// �A���r�G���g

	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(light));
	light.Type = D3DLIGHT_DIRECTIONAL;	//�@���s����

	D3DXVECTOR3 vecDirLight(0.0f, 0.0f, 1.0f);	//�@���C�g�x�N�g��
	D3DXVec3Normalize(&vecDirLight, &vecDirLight); //�@������1�ɂ���@���K��

	light.Direction = vecDirLight;
	light.Diffuse.r = 1.0f;	//�@���C�g�F�@�f�B�t���[�Y
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	light.Diffuse.a = 1.0f;

	m_pD3DDevice->SetLight(0, &light);	//�@�������@�\�P�b�g�ԍ�
	m_pD3DDevice->LightEnable(0, TRUE);	//�@�������@�\�P�b�g�ԍ�

	//g_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);	//	�}�e���A���ݒ�
	//g_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);
	/*
	���C�g����
	g_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
	g_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);
	������
	�L���[�u��Drow�̐擪�ŌĂ�

	���f����Drow�̐擪�ŌĂ�
	g_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	g_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);

	�O���b�h��Drow�̐擪��
	g_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
	g_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);

	*/
}









