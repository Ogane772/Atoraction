//////////////////////////////////////////////////
////
////	�A�g���N�V�����N���X
////
//////////////////////////////////////////////////

#ifndef _ATTRACTION_H_
#define _ATTRACTION_H_

#include "C3DObj.h"
#define ATTRACTION_MAX (100)
#define ATTRACITION_WAIT_TIME (15)//���G����
class CAttraction : virtual public C3DObj
{
public:

	enum
	{
		AT_ALL = 1,

		AT_COASTER = 2,	//	�W�F�b�g�R�[�X�^�[
		AT_WHEEL = 3,		//	�ϗ���
		AT_COFFEE = 4,	//	�R�[�q�[�J�b�v
		AT_FALL = 5,		//	�t���[�t�H�[��
		AT_POPCORN = 6,	//	�|�b�v�R�[��
		AT_STANDBY = 7,   //  ���ݒ�
		AT_GAUGE,        //���ݒ��̐i�s�Q�[�W
		AT_COASTER_ON,	//	�W�F�b�g�R�[�X�^�[����

		TYPE_MAX
	};

	CAttraction();
	CAttraction(int nType);
	~CAttraction();

	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	void Attraction_Finalize(int index);

	static void Create(int nType);
	static C3DObj* Get_Attraction(int index);
	static CAttraction * Get_Attraction(int index,int type);
	static int Get_AttractionNum(int AttractionType) { return m_AttractionNum[AttractionType]; }
	static int Get_AttractionIndex(int AttractionType) { return m_AttractionNum[AttractionType] - 1; }
	static bool Get_CreateCheck(void) { return createchack; }
	
protected:
	static CAttraction *Attraction[ATTRACTION_MAX];
	static int m_AttractionNum[TYPE_MAX];
	int m_AttractionIndex;
	
	void OrnamentDamage(void);
	void CAttraction::OrnamentDamage(THING_NORMAL nomal);
	bool create;


private:

	int m_Type;			// ���
	static bool createchack;//�쐬���ǂ��� true=�쐬�ς�
	//static CAttraction *m_pAttraction[ATTRACTION_MAX];
};

#endif // !1