//////////////////////////////////////////////////
////
////	アトラクション(フリーフォール)クラス
////
//////////////////////////////////////////////////

#ifndef _CFREEFALL_H_
#define _CFREEFALL_H_

#include "CAttraction.h"

class Cfreefall : public CAttraction
{
public:
	Cfreefall();
	~Cfreefall();

	void Update(void);
	void Draw(void);
	void Finalize(void);
	bool Get_DrawCheck(void) { return m_DrawCheck; }
private:
	void Initialize();
	int m_AttractionIndex;
	float ugoki;
	bool Bugoki = false;
	float moveY = 0.0f;
	int CoolTime = 0;
	bool m_DrawCheck;			//	描画フラグ
	D3DXMATRIX m_mtxWorld2;				//	ワールド変換用行列2
	D3DXMATRIX m_mtxTranslation2;		//	移動行列2
	
};
#endif;