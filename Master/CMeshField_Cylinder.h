//////////////////////////////////////////////////
////
////	���b�V���t�B�[���h�V�����_�[�N���X
////
//////////////////////////////////////////////////


#ifndef _CMESHFIELD_CYLINDER_H_
#define _CMESHFIELD_CYLINDER_H_

#include "CMeshField.h"


class CMeshField_Cylinder:public CMeshField
{
public:

	CMeshField_Cylinder();
	CMeshField_Cylinder(int TexIndex, float meshH, float radius, int meshXnum, int meshYnum, bool type);
	~CMeshField_Cylinder();


	void Update(void);
	void Draw(void);
	void Finalize(void);	//	�I������
	static CMeshField_Cylinder *MeshField_Cylinder_Create(int TexIndex, float meshH, float radius, int meshXnum, int meshYnum, bool type);

protected:

private:
	float m_meshH;		//	���b�V��������
	float m_radius;		//	���a
	void MeshField_Cylinder_Initialize(void);
	static CMeshField_Cylinder *m_pMeshField_Cylinder;

	bool m_Type; // true : �����@false : �����Ȃ�
};
#endif // !1












