//=============================================================================
//
//	Player�N���X
//
//=============================================================================

//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================

#include "player.h"
#include "input.h"
#include "move.h"
#include "model.h"

//=============================================================================
//	�萔��`
//=============================================================================
#define SPEED (0.2)

//=============================================================================
// ����
//=============================================================================
CPlayer::CPlayer()
{
	m_Hp = 0;
	m_Mp = 0;
	m_MpStock = 0;

	Model_Load(1);
	D3DXMatrixTranslation(&m_mtxTranslation, 0, 1, 0);
	m_mtxKeepTranslation = m_mtxTranslation;
	m_mtxWorld = m_mtxTranslation;
}

//=============================================================================
// �j��
//=============================================================================
CPlayer::~CPlayer()
{
	Model_Finalize(1);
}

//=============================================================================
// �X�V
//=============================================================================
void CPlayer::Update(void)
{
	if (Keyboard_IsPress(DIK_W))
	{
		m_mtxTranslation *= Move(FLONT, SPEED);
	}
	if (Keyboard_IsPress(DIK_S))
	{
		m_mtxTranslation *= Move(BACK, SPEED);
	}
	if (Keyboard_IsPress(DIK_D))
	{
		m_mtxTranslation *= Move(RIGHT, SPEED);
	}
	if (Keyboard_IsPress(DIK_A))
	{
		m_mtxTranslation *= Move(LEFT, SPEED);
	}


	if (45.0*45.0 < (m_mtxTranslation._41*m_mtxTranslation._41) + (m_mtxTranslation._43 * m_mtxTranslation._43))
	{
		m_mtxTranslation = m_mtxKeepTranslation;
	}
	else
	{
		m_mtxKeepTranslation = m_mtxTranslation;
	}

}
//=============================================================================
// �`��
//=============================================================================

void CPlayer::Draw(void)
{
	D3DXMATRIX mtxScaling;
	
	D3DXMatrixScaling(&mtxScaling, 0.5f, 1.0f, 0.5f);
	m_mtxWorld = mtxScaling * m_mtxTranslation;
	Model_Draw(1, m_mtxWorld);

}




