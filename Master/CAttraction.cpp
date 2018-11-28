//////////////////////////////////////////////////
////
////	アトラクションクラス
////
//////////////////////////////////////////////////


//=============================================================================
//	インクルードファイル
//=============================================================================

#include "CAttraction.h"
#include "Cwheel.h"
#include "Ccoffee_cup.h"
#include "Cfreefall.h"
#include "CGameObj.h"
#include "CAttraction_Coaster .h"
//=============================================================================
//	定数定義
//=============================================================================

//=============================================================================
//	静的変数
//=============================================================================

CAttraction *CAttraction::m_pAttraction[ATTRACTION_MAX] = {};
int CAttraction::m_AttractionNum[TYPE_MAX] = {};
bool CAttraction::createchack;
//=============================================================================
//	生成
//=============================================================================

CAttraction::CAttraction()
{
	m_AttractionNum[TYPE_ALL]++;
}

CAttraction::CAttraction(int nType)
{
	m_Type = nType;
	m_AttractionNum[TYPE_ALL]++;
	m_AttractionNum[nType]++;
}
//=============================================================================
//	破棄
//=============================================================================

CAttraction::~CAttraction()
{
	m_AttractionNum[TYPE_ALL]--;
}

void CAttraction::Create(int nType)
{
	if (nType == TYPE_COFFEE)
	{
		m_pAttraction[m_AttractionNum[TYPE_ALL] - 1] = new CCoffeeCup;
		createchack = true;
	}
	if (nType == TYPE_FALL)
	{
		m_pAttraction[m_AttractionNum[TYPE_ALL] - 1] = new Cfreefall;
		createchack = true;
	}
	if (nType == TYPE_WHEEL)
	{
		m_pAttraction[m_AttractionNum[TYPE_ALL] - 1] = new Cwheel;
		createchack = true;
	}
	if (nType == TYPE_COASTER)
	{
		m_pAttraction[m_AttractionNum[TYPE_ALL] - 1] = new Coaster;
		createchack = true;
	}
}

CAttraction* CAttraction::Get_Attraction(int index)
{
	createchack = false;
	return m_pAttraction[index];
}


void CAttraction::Attraction_Finalize(int index)
{
	if (m_pAttraction[index])
	{
		delete[]m_pAttraction[index];
	}
}


