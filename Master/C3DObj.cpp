//////////////////////////////////////////////////
////
////	3Dオブジェクトクラス
////
//////////////////////////////////////////////////

#include "C3DObj.h"
#include "debug_font.h"


//=============================================================================
//	静的変数
//===========================================================================
C3DObj *C3DObj::p3DObj[MAX_GAMEOBJ];
int C3DObj::m_3DObjNum = 0;

//=============================================================================
//	生成
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
	// ワーク格納失敗
	if (m_3DObjIndex >= MAX_GAMEOBJ)
	{
		m_3DObjIndex = -1;
	}

	
}

C3DObj::C3DObj(int type)
{
	// ワークに自分自身(this)を格納
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
	// ワーク格納失敗
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
//	破棄
//=============================================================================
C3DObj::~C3DObj()
{
	m_3DObjNum--;
	p3DObj[m_3DObjIndex] = NULL;
}





//=============================================================================
// 全オブジェクト更新
//=============================================================================
void C3DObj::UpdateAll()
{
	for (int i = 0; i < MAX_GAMEOBJ; i++)
	{
		// ポリモーフィズムによって派生クラスのUpdate()が呼ばれる
		if (p3DObj[i])
		{
			p3DObj[i]->Update();
		}
	}
}

//=============================================================================
// 全オブジェクト描画
//=============================================================================
void C3DObj::DrawAll()
{
	for (int i = 0; i < MAX_GAMEOBJ; i++)
	{
		// ポリモーフィズムによって派生クラスのDraw()が呼ばれる
		if (p3DObj[i])
		{
			p3DObj[i]->Draw();
		}
	}
}



//=============================================================================
// 全オブジェクト削除
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
// インスタンス取得
//=============================================================================
C3DObj *C3DObj::Get(int nIdx)
{
	// インデックスが範囲外
	if (p3DObj[nIdx])
	{
		return p3DObj[nIdx];
	}
	return NULL;
}


//=============================================================================
// オブジェクト削除
//=============================================================================
void C3DObj::C3DObj_delete(void)
{
	C3DObj *pobj = Get(Get_3DObjIndex());
	delete pobj;
}











