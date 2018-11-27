//////////////////////////////////////////////////
////
////	アトラクションクラス
////
//////////////////////////////////////////////////

#ifndef _ATTRACTION_H_
#define _ATTRACTION_H_

#include "C3DObj.h"
#include "Cphysx.h"
#define ATTRACTION_MAX (100)

class CAttraction : public C3DObj, public CPhysx
{
public:

	enum
	{
		TYPE_ALL = 0,

		TYPE_COASTER,		//	ジェットコースター
		TYPE_WHEEL,		//	観覧車
		TYPE_COFFEE,		//	コーヒーカップ
		TYPE_FALL,		//	フリーフォール
		TYPE_POPCORN,		//	ポップコーン


		TYPE_MAX
	};

	CAttraction();
	CAttraction(int nType);
	~CAttraction();

	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	void Attraction_Finalize(int index);
	static void Create(int nType);
	static CAttraction * Get_Attraction(int index);
	static int Get_AttractionNum(int AttractionType) { return m_AttractionNum[AttractionType]; }
	static int Get_AttractionIndex(int AttractionType) { return m_AttractionNum[AttractionType] - 1; }
	static bool Get_CreateCheck(void) { return createchack; }
protected:
	static CAttraction *Attraction[ATTRACTION_MAX];
	static int m_AttractionNum[TYPE_MAX];
	int m_AttractionIndex;
	int hp;
	int mp;
	int atk;
	
	bool create;
private:

	int m_Type;			// 種類
	static bool createchack;//作成かどうか true=作成済み
	static CAttraction *m_pAttraction[ATTRACTION_MAX];
};

#endif // !1