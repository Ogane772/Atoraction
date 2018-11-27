//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================


#include"CCamera.h"
#include "move.h"

//=============================================================================
//	�萔��`
//=============================================================================
#define SPEED (0.2)
//=============================================================================
//	�O���[�o���錾
//=============================================================================


D3DXMATRIX Move(int direction)
{
	D3DXVECTOR3 right = CCamera::Get_RightVec();
	D3DXMATRIX mtxTranslation;

	right *= SPEED;

	if (direction == FLONT)
	{
		D3DXMatrixTranslation(&mtxTranslation, right.z, right.y, -right.x);
		return mtxTranslation;
	}
	if (direction == BACK)
	{
		D3DXMatrixTranslation(&mtxTranslation, -right.z, right.y, right.x);
		return mtxTranslation;
	}
	if (direction == RIGHT)
	{
		D3DXMatrixTranslation(&mtxTranslation, -right.x, right.y, -right.z);
		return mtxTranslation;
	}
	if (direction == LEFT)
	{
		D3DXMatrixTranslation(&mtxTranslation, right.x, right.y, right.z);
		return mtxTranslation;
	}
}

D3DXMATRIX Move(int direction,float speed)
{
	D3DXVECTOR3 right = CCamera::Get_RightVec();
	D3DXMATRIX mtxTranslation;

	right *= speed;

	if (direction == FLONT)
	{
		D3DXMatrixTranslation(&mtxTranslation, right.z, right.y, -right.x);
		return mtxTranslation;
	}
	if (direction == BACK)
	{
		D3DXMatrixTranslation(&mtxTranslation, -right.z, right.y, right.x);
		return mtxTranslation;
	}
	if (direction == RIGHT)
	{
		D3DXMatrixTranslation(&mtxTranslation, -right.x, right.y, -right.z);
		return mtxTranslation;
	}
	if (direction == LEFT)
	{
		D3DXMatrixTranslation(&mtxTranslation, right.x, right.y, right.z);
		return mtxTranslation;
	}
}