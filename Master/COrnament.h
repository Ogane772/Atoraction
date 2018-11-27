//////////////////////////////////////////////////
////
////	��Q���N���X
////
//////////////////////////////////////////////////

#ifndef _CORNAMENT_H_
#define _CORNAMENT_H_

#include "C3DObj.h"

#define ORNAMENT_MAX (100)

class COrnament : public C3DObj
{
public:
	
	enum
	{
		TYPE_ALL = 0,

		TYPE_LAMP,		//	�X��
		TYPE_DUSTBOX,	//	�S�~��
		TYPE_BENCH,		//	�x���`
		TYPE_FOUNTAIN,	//	����
		
		TYPE_MAX
	};
	
	COrnament();
	~COrnament();

	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	static int Get_OrnamentNum(int OrnamType){ return m_OrnamentNum[OrnamType]; }
	
protected:
	static COrnament *m_pOrnament[ORNAMENT_MAX];
	static int m_OrnamentNum[TYPE_MAX];
	

};

#endif // !1
#pragma once
