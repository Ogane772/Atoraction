//////////////////////////////////////////////////
////
////	MAPオブジェクトクラス
////
//////////////////////////////////////////////////

#ifndef _MAP_H_
#define _MAP_H_

#include "C2DObj.h"
#include <d3dx9.h>

class MapObj : public C2DObj
{
public:
	MapObj();
	~MapObj();

	void Update(void);
	void Draw(void);
	void Finalize(void);

	/*
	texture_index:テクスチャ番号
	dx:表示したいスプライトの左上座標X
	dy:表示したいスプライトの左上座標Y
	tx:表示したいテクスチャの始点X
	ty:表示したいテクスチャの始点Y
	tw:表示したいテクスチャの幅
	th:表示したいテクスチャの高さ
	*/

protected:



};

#endif // !1

