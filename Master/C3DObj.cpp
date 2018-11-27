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

void C3DObj::Debug_Collision(SphereCollision sc)
{
	DebugFont_Draw(400, 10, "%f\n,%f\n,%f\n,", sc.CenterPos.x, sc.CenterPos.y, sc.CenterPos.z);
}




















