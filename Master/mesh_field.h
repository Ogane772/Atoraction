#ifndef _MESH_FIELD_H_ 
#define	_MESH_FIELD_H_

void Mesh_Field_Initialize(float meshW, int meshXnum, int meshZnum);
void Mesh_Cylinder_Initialize(float meshH, float radius, int meshXnum, int meshYnum);
void Mesh_Skydome_Initialize(float meshH, float radius, int meshXnum, int meshYnum);
void Mesh_Field_Finalize(void);
void Mesh_Field_Draw(int index);



#endif // !

