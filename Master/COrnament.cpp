//////////////////////////////////////////////////
////
////	障害物クラス
////
//////////////////////////////////////////////////

//=============================================================================
//	インクルードファイル
//=============================================================================

#include "COrnament.h"
#include "COrnament_Lamp.h"
#include "COrnament_DustBox.h"
#include "COrnament_Bench.h"
#include "COrnament_Fountain.h"
#include"COrnament_Kanransya.h"
#include"COrnament_Husen.h"
#include"COrnament_Meri.h"
#include "exp.h"
#include "sound.h"
//=============================================================================
//	定数定義
//=============================================================================


//=============================================================================
//	静的変数
//=============================================================================

COrnament *COrnament::m_pOrnament[ORNAMENT_MAX] = {};

COrnament::ORNAMENT_EMITTER COrnament::m_OrnamentEmitter[]
{
	{ 0	  , TYPE_HUSEN, D3DXVECTOR3(0.0f, 0.0f , -15.5f),270     ,false, D3DXVECTOR3(1.0f, 1.0f , 1.0f), },

	{ 0	  , TYPE_DUSTBOX, D3DXVECTOR3(-31.0f, 0.0f , -4.5f),270     ,false, D3DXVECTOR3(1.0f, 1.0f , 1.0f), },
	{ 0	  , TYPE_DUSTBOX, D3DXVECTOR3(-34.0f, 0.0f , -4.5f),270     ,false, D3DXVECTOR3(1.0f, 1.0f , 1.0f), },

	{ 0	  , TYPE_DUSTBOX, D3DXVECTOR3(31.0f, 0.0f , -4.5f),270     ,false, D3DXVECTOR3(1.0f, 1.0f , 1.0f), },
	{ 0	  , TYPE_DUSTBOX, D3DXVECTOR3(34.0f, 0.0f , -4.5f),270     ,false, D3DXVECTOR3(1.0f, 1.0f , 1.0f), },

	{ 0	  , TYPE_LAMP, D3DXVECTOR3(-6.0f, 1.0f , -60.0f), 90	   ,false, D3DXVECTOR3(1.0f, 1.5f , 1.0f), },
	{ 0	  , TYPE_LAMP, D3DXVECTOR3(6.0f, 1.0f , -60.0f), 90	   ,false, D3DXVECTOR3(1.0f, 1.5f , 1.0f), },

	{ 0	  , TYPE_LAMP, D3DXVECTOR3(-6.0f, 1.0f , 60.0f), 90	   ,false, D3DXVECTOR3(1.0f, 1.5f , 1.0f), },
	{ 0	  , TYPE_LAMP, D3DXVECTOR3(6.0f, 1.0f , 60.0f), 90	   ,false, D3DXVECTOR3(1.0f, 1.5f , 1.0f), },


	{ 0	  , TYPE_FOUNTAIN, D3DXVECTOR3(0.0f , 0.0f , 0.0f),  0 ,false, D3DXVECTOR3(2.0f, 2.0f , 2.0f), },

	{ 0	  , TYPE_BENCH, D3DXVECTOR3(-18.0f, 0.0f , 18.0f), 405	   ,false, D3DXVECTOR3(1.0f, 1.0f , 1.0f), },
	{ 0	  , TYPE_BENCH, D3DXVECTOR3(-18.0f, 0.0f , -18.0f), 315	   ,false, D3DXVECTOR3(1.0f, 1.0f , 1.0f), },
	{ 0	  , TYPE_BENCH, D3DXVECTOR3(18.0f, 0.0f , -18.0f), 225	   ,false, D3DXVECTOR3(1.0f, 1.0f , 1.0f), },
	{ 0	  , TYPE_BENCH, D3DXVECTOR3(18.0f, 0.0f , 18.0f), 135	   ,false, D3DXVECTOR3(1.0f, 1.0f , 1.0f), },

	{ 0	  , TYPE_KANRANSYA_DODAI, D3DXVECTOR3(-65.0f, 0.0f , 35.0f), 135	   ,false, D3DXVECTOR3(2.0f, 2.0f , 2.0f), },
	{ 0	  , TYPE_MERI, D3DXVECTOR3(40.0f, 0.0f , -36.0f),270     ,false, D3DXVECTOR3(1.5f, 1.5f , 1.5f), },
};
//=============================================================================
//	生成
//=============================================================================
int COrnament::m_ORNAMENT_MAX = sizeof(m_OrnamentEmitter) / sizeof(m_OrnamentEmitter[0]);

int COrnament::m_OrnamentNum[TYPE_MAX] = {};

COrnament::COrnament()
{
	m_OrnamentNum[TYPE_ALL]++;
}

COrnament::COrnament(int OrnamentType)
{
	m_OrnamentType = OrnamentType;
	m_OrnamentIndex = m_OrnamentNum[TYPE_ALL];
	m_OrnamentNum[TYPE_ALL]++;
	m_OrnamentNum[OrnamentType]++;
	m_Attack = 0;
	m_Score = 0;
	m_Direction = 0;
	m_DirectionAngle = 0;
}

void COrnament::Create(void)
{
	for (int i = 0; i < m_ORNAMENT_MAX; i++)
	{
		if (!m_OrnamentEmitter[i].CreateCheck)
		{
			if (m_FrameCount == m_OrnamentEmitter[i].CreateFrame)
			{
				if (m_OrnamentEmitter[i].Type == TYPE_LAMP)
				{
					COrnament_Lamp *plamp = new COrnament_Lamp(&m_OrnamentEmitter[i]);
					m_OrnamentEmitter[i].CreateCheck = true;
				}
				if (m_OrnamentEmitter[i].Type == TYPE_DUSTBOX)
				{
					COrnament_DustBox *pdustlamp = new COrnament_DustBox(&m_OrnamentEmitter[i]);
					m_OrnamentEmitter[i].CreateCheck = true;
				}
				if (m_OrnamentEmitter[i].Type == TYPE_BENCH)
				{
					COrnament_BENCH *pdustlamp = new COrnament_BENCH(&m_OrnamentEmitter[i]);
					m_OrnamentEmitter[i].CreateCheck = true;
				}
				if (m_OrnamentEmitter[i].Type == TYPE_FOUNTAIN)
				{
					COrnament_Fountain *pdustlamp = new COrnament_Fountain(&m_OrnamentEmitter[i]);
					m_OrnamentEmitter[i].CreateCheck = true;
				}
				if (m_OrnamentEmitter[i].Type == TYPE_KANRANSYA_DODAI)
				{
					COrnament_KANRANSYA *pdustlamp = new COrnament_KANRANSYA(&m_OrnamentEmitter[i]);
					m_OrnamentEmitter[i].CreateCheck = true;
				}
				if (m_OrnamentEmitter[i].Type == TYPE_HUSEN)
				{
					COrnament_HUSEN *pdustlamp = new COrnament_HUSEN(&m_OrnamentEmitter[i]);
					m_OrnamentEmitter[i].CreateCheck = true;
				}
				if (m_OrnamentEmitter[i].Type == TYPE_MERI)
				{
					COrnament_MERI *pdustlamp = new COrnament_MERI(&m_OrnamentEmitter[i]);
					m_OrnamentEmitter[i].CreateCheck = true;
				}
			}
		}
	}
}

void COrnament::Ornament_Finalize(int Index)
{
	m_OrnamentEmitter[Index].CreateCheck = false;
}
//=============================================================================
//	破棄
//=============================================================================

COrnament::~COrnament()
{
	m_OrnamentEmitter[m_OrnamentIndex].CreateCheck = false;
	m_OrnamentNum[TYPE_ALL]--;
}

void COrnament::OrnamentDamage(void)
{
	m_Hp--;
	if (m_Hp <= 0)
	{
		m_TimeKeep = m_FrameCount;
	}

}

C3DObj *COrnament::Get_Ornament(int index)
{
	C3DObj *pornament = C3DObj::Get(index);
	if (pornament)
	{
		if (pornament->Get_3DObjType() == C3DObj::TYPE_ORNAMENT)
		{

			return pornament;

		}
	}
	return NULL;
}


C3DObj *COrnament::Get_AllOrnament(int Index)
{
	C3DObj *pOrnament = C3DObj::Get(Index);
	if (pOrnament)
	{
		if (pOrnament->Get_3DObjType() == C3DObj::TYPE_ORNAMENT)
		{
			
			return pOrnament;
			
		}
	}
	return NULL;
}

C3DObj *COrnament::Get_Map_Ornament(int Index)
{
	C3DObj *pOrnament = C3DObj::Get(Index);
	if (pOrnament)
	{
		if (pOrnament->Get_3DObjType() == C3DObj::TYPE_ORNAMENT)
		{
			if (pOrnament->Get_DrawCheck())
			{
				return pOrnament;
			}
		}
	}
	return NULL;
}


void COrnament::Ornament_Damage(float flyinghigh)
{
	if (!m_OrnamentFlying)
	{
		if (m_DrawCheck)
		{
			PlaySound(NORMALHIT_SE);
			m_Hp--;

			m_FlyingMove = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43) - m_PosKeep;
			m_FlyingMove.y = flyinghigh;
			if (m_Hp <= 0)
			{
				Exp_Set(SMALLSTAR, m_mtxWorld._41, m_mtxWorld._42 + 1, m_mtxWorld._43, 5.0, 0);
				//Add_Mp(m_Mp);
				//Add_Score(m_Score);
				m_OrnamentFlying = true;
			}
		}

	}
}

void COrnament::Ornament_Flying(float speed)
{
	if (m_OrnamentFlying)
	{
		if (m_Hp <= 0)
		{
			if (!m_OrnamentFlyingDown)
			{
				D3DXMatrixTranslation(&m_mtxTranslation, m_mtxWorld._41 + m_FlyingMove.x * speed, m_mtxWorld._42 + m_FlyingMove.y, m_mtxWorld._43 + m_FlyingMove.z * speed);
				m_FlyingCount++;
				if (m_FlyingCount >= 60)
				{
					m_OrnamentFlyingDown = true;
				}
			}
			else
			{

				D3DXMatrixTranslation(&m_mtxTranslation, m_mtxWorld._41 + m_FlyingMove.x * speed, m_mtxWorld._42 - m_FlyingMove.y, m_mtxWorld._43 + m_FlyingMove.z * speed);
				m_FlyingCount--;
				if (m_FlyingCount <= 0)
				{
					m_mtxTranslation._42 = 0.0f;
					m_OrnamentFlying = false;
					m_OrnamentFlyingDown = false;
					m_DamageFlag = false;

				}
			}
		}
		else
		{
			//D3DXMatrixTranslation(&m_mtxTranslation, m_mtxWorld._41 + m_FlyingMove.x * (speed * 2), m_mtxWorld._42 + m_FlyingMove.y, m_mtxWorld._43 + m_FlyingMove.z * (speed * 2));
		}
	}
}

void COrnament::Death(void)
{
	if (m_Hp <= 0)
	{
		if (!m_OrnamentFlying)
		{
			delete this;
		}
	}
}




