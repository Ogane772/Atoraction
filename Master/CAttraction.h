//////////////////////////////////////////////////
////
////	アトラクションクラス
////
//////////////////////////////////////////////////

#ifndef _ATTRACTION_H_
#define _ATTRACTION_H_

#include "C3DObj.h"
#define ATTRACTION_MAX (100)

class CAttraction : virtual public C3DObj
{
public:

	enum
	{
		AT_ALL = 1,

		AT_COASTER = 2,	//	ジェットコースター
		AT_WHEEL = 3,		//	観覧車
		AT_COFFEE = 4,	//	コーヒーカップ
		AT_FALL = 5,		//	フリーフォール
		AT_POPCORN = 6,	//	ポップコーン
		AT_STANDBY = 7,   //  建設中


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
	static CAttraction * Get_Attraction(int index,int type);
	static int Get_AttractionNum(int AttractionType) { return m_AttractionNum[AttractionType]; }
	static int Get_AttractionIndex(int AttractionType) { return m_AttractionNum[AttractionType] - 1; }
	static bool Get_CreateCheck(void) { return createchack; }
	
protected:
	static CAttraction *Attraction[ATTRACTION_MAX];
	static int m_AttractionNum[TYPE_MAX];
	int m_AttractionIndex;
	
	
	bool create;
private:

	int m_Type;			// 種類
	static bool createchack;//作成かどうか true=作成済み
	static CAttraction *m_pAttraction[ATTRACTION_MAX];
};

#endif // !1