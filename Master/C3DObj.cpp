//////////////////////////////////////////////////
////
////	3Dオブジェクトクラス
////
//////////////////////////////////////////////////

#include "C3DObj.h"
#include "debug_font.h"

C3DObj::C3DObj()
{
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixIdentity(&m_mtxTranslation);
	D3DXMatrixIdentity(&m_mtxRotation);
	D3DXMatrixIdentity(&m_mtxScaling);
	m_Enable = false;
}

C3DObj::~C3DObj()
{

}






















