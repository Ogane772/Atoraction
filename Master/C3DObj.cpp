//////////////////////////////////////////////////
////
////	3D�I�u�W�F�N�g�N���X
////
//////////////////////////////////////////////////

#include "C3DObj.h"
#include "debug_font.h"


//=============================================================================
//	�ÓI�ϐ�
//===========================================================================
C3DObj *C3DObj::p3DObj[MAX_GAMEOBJ];
int C3DObj::m_3DObjNum = 0;

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











