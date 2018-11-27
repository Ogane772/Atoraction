#ifndef _CAMERA_H_
#define _CAMERA_H_

#include<d3dx9.h>

void Camera_Initialize(void);
void Camera_Updata(void);
D3DXVECTOR3 Get_Rvec(void);
const D3DXMATRIX Get_ViewMtx(void);

void  Camera_Draw(void);
#endif //_CAMERA_H_

