#ifndef _MODEL_H_
#define _MODEL_H_



void Model_Load(int index);		//	������������index��߂��֐��ɂ���
void Model_Draw(int index);		//	�����������������ς���@�s��
void Model_Finalize(void);	//	���f���f�[�^�̊J���@������������S���������ǂꂩ������
void Model_Updata(int index);
void Model_Draw(int index, D3DXMATRIX mtxWorld);
void Model_Finalize(int index);

D3DXMATRIX get_modelPos(int index);

#endif //_MODEL_H_