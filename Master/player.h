#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <d3dx9.h>

#define PLAYER_MAX (2)

class CPlayer
{

public:
	CPlayer();
	~CPlayer();

	void Update(void);
	void Draw(void);

	int Get_Hp(void) { return m_Hp; }
	int Get_Mp(void) { return m_Mp; }
	int Get_MpStock(void) { return m_MpStock; }
	//static D3DXMATRIX Get_mtxWorld(void){ return m_mtxWorld; }
	CPlayer *Get_Player(int index) { return m_pPlayer[index]; }

protected:
	int m_Hp;
	int m_Mp;
	int m_MpStock;

	D3DXMATRIX m_mtxTranslation;		//	�ړ��s��
	D3DXMATRIX m_mtxKeepTranslation;	//	�ړ��ێ��s��
	//static D3DXMATRIX m_mtxWorld;				//	���[���h�ϊ��p�s��
	D3DXMATRIX m_mtxWorld;				//	���[���h�ϊ��p�s��
	CPlayer *m_pPlayer[PLAYER_MAX];


};



#endif // !

