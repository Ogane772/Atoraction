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
#include "CAttraction_Standby.h"
#include "CAttraction_Popcorn.h"
#include "CGauge.h"
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
	m_AttractionNum[AT_ALL]++;
}

CAttraction::CAttraction(int nType)
{
	m_Type = nType;

	m_AttractionNum[AT_ALL]++;
	m_AttractionNum[nType]++;
}
//=============================================================================
//	破棄
//=============================================================================

CAttraction::~CAttraction()
{
	m_AttractionNum[AT_ALL]--;
	m_AttractionNum[m_Type]--;
}

void CAttraction::Create(int nType)
{
	if (nType == AT_COASTER)
	{
		Coaster *m_pAttraction = new Coaster;
		createchack = true;
	}
	if (nType == AT_COFFEE)
	{
		Standby *m_pAttraction = new Standby(nType);
		//CCoffeeCup *m_pAttraction = new CCoffeeCup;
		createchack = true;
	}
	if (nType == AT_FALL)
	{
		Cfreefall *m_pAttraction = new Cfreefall;
		createchack = true;
	}
	if (nType == AT_WHEEL)
	{
		Cwheel *m_pAttraction = new Cwheel;
		createchack = true;
	}
	if (nType == AT_COASTER)
	{
		Coaster *m_pAttraction = new Coaster;
		createchack = true;
	}
	if (nType == AT_POPCORN)
	{
		Popcorn *m_pAttraction = new Popcorn;
		createchack = true;
	}
	if (nType == AT_STANDBY)
	{
		Standby *m_pAttraction = new Standby(nType);
		createchack = true;
	}
}

CAttraction* CAttraction::Get_Attraction(int index)
{
	createchack = false;
	return m_pAttraction[index];
}
CAttraction* CAttraction::Get_Attraction(int index, int type)
{
	if (m_pAttraction[index])
	{
		if (m_pAttraction[index]->m_Type == type)
		{
			return m_pAttraction[index];
		}
	}
	return NULL;
}

void CAttraction::Attraction_Finalize(int index)
{
	if (m_pAttraction[index])
	{
		delete m_pAttraction[index];
		m_pAttraction[index] = NULL;
	}
}


