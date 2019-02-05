//////////////////////////////////////////////////
////
////	�X�J�C�h�[���N���X
////
//////////////////////////////////////////////////


#ifndef _CMESH_SKYDOME_H_
#define _CMESH_SKYDOME_H_

#include "CMeshField.h"


class CMesh_SkyDome :public CMeshField
{
public:

	CMesh_SkyDome();
	CMesh_SkyDome(int TexIndex,float meshH, float radius, int meshXnum, int meshYnum);
	~CMesh_SkyDome();


	void Update(void);
	void Draw(void);
	void Finalize(void);	//	�I������
	static CMesh_SkyDome *Mesh_SkyDome_Create(int TexIndex,float meshH, float radius, int meshXnum, int meshYnum);

protected:

private:
	float m_meshH;		//	���b�V��������
	float m_radius;		//	���a
	void Mesh_SkyDome_Initialize(void);
	static CMesh_SkyDome *m_pMesh_SkyDome;

	
};
#endif // !1



