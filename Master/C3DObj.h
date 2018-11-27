//////////////////////////////////////////////////
////
////	3Dオブジェクトクラス
////
//////////////////////////////////////////////////

#ifndef _3DOBJ_H_
#define _3DOBJ_H_

#include "CGameObj.h"
#include <d3dx9.h>

class C3DObj :virtual public CGameObj
{
public:
	C3DObj();
	~C3DObj();

	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	D3DXMATRIX Get_mtxWorld(void) { return m_mtxWorld; }	


protected:
	D3DXMATRIX m_mtxWorld;  //	ワールド変換用行列
	D3DXMATRIX m_mtxTranslation;		//	移動行列
	D3DXMATRIX m_mtxRotation;		//	移動行列
	D3DXMATRIX m_mtxScaling;		//	移動行列
	bool m_Enable;
private:

};

#endif // !1
