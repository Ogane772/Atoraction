#include <d3dx9.h>
//#include "ModelEnemy.h"
#include "model.h"
#include "CTexture.h"
#include "camera.h"
#include "C2DObj.h"
#include "CLight.h"
#include "common.h"
#include "Cplayer.h"
#include "CEnemy.h"
#include "map.h"


MapObj::MapObj()
{

}

MapObj::~MapObj()
{

}




void MapObj::Update(void)
{
	
}


void MapObj::Finalize(void)
{

}

 
void MapObj::Draw(void)
{

	CPlayer *player = CPlayer::Get_Player(0);
	D3DXMATRIX playermatrix = player->Get_Player_position();
	Sprite_Draw(TEX_MAP, 850.0f, 0.0f, 0.0f, 0.0f, 150, 150);

	

	Sprite_Draw(TEX_Player_Icon, 880.0f + playermatrix._41, 60.0f - playermatrix._43, 0.0f, 0.0f, 60, 30);

	/*for (int i = 0; i < 3; i++)
	{
		Sprite_Draw(35, (SCREEN_WIDTH - 24) / 10 * 8 + 120.0f + Get_Enemy_position(i).x, 60.0f - Get_Enemy_position(i).z, 0.0f, 0.0f, 6, 6);
	}*/
}

