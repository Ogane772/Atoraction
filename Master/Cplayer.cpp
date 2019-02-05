//=============================================================================
//
//	Player�N���X
//
//=============================================================================

//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================

#include "Cplayer.h"
#include "input.h"
#include "move.h"
#include "CAttraction.h"
#include "debug_font.h"
#include "gamepad.h"
#include "CEnemy.h"
#include "Cwheel.h"
#include "CEnemy_Small.h"
#include "CAttraction_Coaster .h"
#include "CAttraction_Popcorn.h"
#include "gamepad.h"
#include "exp.h"
#include "CTexture.h"
#include "CEnemy.h"
#include "CCamera.h"
#include "common.h"
//=============================================================================
//	�萔��`
//=============================================================================
#define SPEED (0.2f)
#define PLAYER_SAIZ (0.5f)
#define MPSTOCK_INIT (5)
#define ANGLE (3)
#define SLANT (45)
//=============================================================================
//	�ÓI�ϐ�
//=============================================================================
enum PlayerAnime
{
	PLAYER_WALK,
	PLAYER_IDLE,
	PLAYER_SET,
	PLAYER_DAMAGE,
	PLAYER_JUMP,
	PLAYER_COASTER,
	PLAYER_WHEEL,
	PLAYER_DOWN,

};
//�R���g���[���[�Ɏg���ϐ�
static DIJOYSTATE2 js;
static LPDIRECTINPUTDEVICE8 pJoyDevice;
static HRESULT hr;
static int doubleflag;//�L�[��������i�[
					  //D3DXMATRIX CPlayer::m_mtxWorld;
CPlayer *CPlayer::m_pPlayer[PLAYER_MAX] = {};
int CPlayer::m_PlayerNum = 0;
int CPlayer::m_KO_Count = 0;
bool CPlayer::m_delete = false;

//=============================================================================
// ����
//=============================================================================
CPlayer::CPlayer() :C3DObj(C3DObj::TYPE_PLAYER)
{
	Player_Initialize();
	m_PlayerIndex = m_PlayerNum;
	m_PlayerNum++;
}

CPlayer *CPlayer::PlayerCreate(void)
{
	//m_pPlayer[m_PlayerNum-1] = new CPlayer;
	//return m_pPlayer[m_PlayerNum - 1];
	CPlayer *m_pPlayer = new CPlayer;
	return m_pPlayer;
}


//=============================================================================
// �j��
//=============================================================================
CPlayer::~CPlayer()
{
	//Player_Finalize();
	m_PlayerNum--;
}

//=============================================================================
// �X�V
//=============================================================================
void CPlayer::Update(void)
{
	Player_Camera();

	//�R���g���[���[��񂪂���Ƃ��̂ݎ擾
	if (pJoyDevice)
	{
		pJoyDevice->GetDeviceState(sizeof(DIJOYSTATE2), &js);
	}
	/////////////////////////////
	if (g_CosterMode)//�R�[�X�^�[�̎�
	{
		C3DObj *pcoaster = Coaster::Get_Coaster();
		if (pcoaster)
		{
			m_mtxTranslation *= Move(FLONT, SPEED);
		}
		else
		{
			g_CosterMode = false;
		}
	}
	else
	{
		//�\���L�[���邢�̓X�e�B�b�N�ɂ��ړ�
		if (Keyboard_IsPress(DIK_T))//�X�N���[���V���b�g
		{													   // �o�b�N�o�t�@�̎擾
			LPDIRECT3DSURFACE9 pBackBuf;
			m_pD3DDevice->GetRenderTarget(0, &pBackBuf);

			// �X�N�V���o��
			D3DXSaveSurfaceToFile("asset/screenshot.bmp", D3DXIFF_BMP, pBackBuf, NULL, NULL);

			// Get�n�Ŏ擾�����T�[�t�F�C�X��AddRef���Ă΂�Ă���̂ŖY�ꂸ�ɉ������
			pBackBuf->Release();
		}
		if (Keyboard_IsPress(DIK_1))
		{
			Exp_Create(m_mtxTranslation._41, m_mtxTranslation._42 + 1.0f, m_mtxTranslation._43, 1.0f, 0.0f, CTexture::TEX_EFFECT_HIT1, 14, 1, 3360 / 7, 960 / 2, 7);
		}
		

		Player_Move();

		if (Keyboard_IsTrigger(DIK_O))
		{
			CAttraction::Create(CAttraction::AT_COFFEE);
		}
		if (Keyboard_IsTrigger(DIK_I))
		{
			CAttraction::Create(CAttraction::AT_FALL);
		}
		if (Keyboard_IsTrigger(DIK_U))
		{
			CAttraction::Create(CAttraction::AT_WHEEL);
		}
		if (Keyboard_IsTrigger(DIK_P))
		{
			CAttraction::Create(CAttraction::AT_COASTER);
			g_CosterMode = true;
		}
		if (Keyboard_IsTrigger(DIK_Y))
		{
			CAttraction::Create(CAttraction::AT_POPCORN);
		}
	}
	D3DXMATRIX mtxr;
	D3DXMatrixRotationY(&m_mtxRotation, D3DXToRadian(m_Angle));
	//m_mtxRotation *= mtxr;

	if (FIELDSIZE*FIELDSIZE < (m_mtxTranslation._41*m_mtxTranslation._41) + (m_mtxTranslation._43 * m_mtxTranslation._43))
	{
		m_mtxTranslation = m_mtxKeepTranslation;
	}
	else
	{
		m_mtxKeepTranslation = m_mtxTranslation;
	}

	//	MP
	if (m_FrameCount % 60 == 0)
	{

		m_Mp++;
		if (m_Mp >= MP_MAX)
		{
			m_MpStock++;
			m_Mp = 0;
		}
	}
	/*	int atrnum = CAttraction::Get_AttractionNum(CAttraction::TYPE_ALL);
	for (int j = 0;j < atrnum;j++)
	{
	CAttraction *patr = CAttraction::Get_Attraction(j, CAttraction::TYPE_WHEEL);
	if (patr)
	{
	int enemynum = CEnemy::Get_EnemyMaxNum();
	for (int i = 0;i < enemynum;i++)
	{
	CEnemy *penemy = CEnemy_Small::Get_Enemy(i);
	if (penemy)
	{
	NxActor* act = penemy->Get_Actor();
	NxActor* act2 = patr->Get_Actor();
	myData* mydata = (myData*)act2->userData;
	if (mydata->hit)
	{
	penemy->Damage();
	mydata->hit = false;
	}
	NxScene* scene = Get_PhysX_Scene();
	scene->setUserContactReport(new ContactCallBack());
	scene->setActorPairFlags(*act2,
	*act,
	NX_NOTIFY_ON_START_TOUCH | NX_NOTIFY_ON_END_TOUCH);


	}
	}
	}
	}*/

	if (m_DrawCheck)
	{
		PlayerDamage();
	}

	//Animation_Change(PLAYER_DAMAGE, 0.05);
	//doubleflag = false;
}
//=============================================================================
// �`��
//=============================================================================

void CPlayer::Draw(void)
{

	m_mtxWorld = m_mtxScaling * m_mtxRotation * m_mtxTranslation;
	Thing.vPosition = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);
	if (!m_DrawCheck)
	{
		if (m_FrameCount % 2 == 0)
		{
			//DrawDX2(m_mtxWorld, NxA_pPlayer, MODELL_PLAYER);
			m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);	//�@���C�e�B���O�L��
			DrawDX_Anime(m_mtxWorld, MODELL_ANIME_PLAYER, &Thing);
			

			m_DrawCount++;
			if (m_DrawCount >= 20)
			{
				m_DrawCount = 0;
				m_DrawCheck = true;
			}
		}
	}
	else
	{
		m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);	//�@���C�e�B���O�L��
		DrawDX_Anime(m_mtxWorld, MODELL_ANIME_PLAYER, &Thing);
		m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
	//	�f�o�b�O
	//DebugFont_Draw(300, 50, "%f\n%f\n%f\n%f", m_front.x, m_front.y, m_front.z, m_Angle);
	//RenderPhysX();
	//�R���g���[���[�̃X�e�B�b�N�擾
	//DebugFont_Draw(300, 50, "X = %ld , Y= %ld", js.lX, js.lY);
	//Debug_Collision(m_SphereCollision, m_mtxTranslation);
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//	������
void CPlayer::Player_Initialize(void)
{
	SkinMesh.InitThing(m_pD3DDevice, &Thing, ANIME_MODEL_FILES[MODELL_ANIME_PLAYER].filename);
	Thing.Sphere.fRadius = 1.3f;
	Thing.Sphere.vCenter = D3DXVECTOR3(0, 1.2f, 0);
	SkinMesh.InitSphere(m_pD3DDevice, &Thing);
	//���f�����擾
	//Thing_Anime_model = GetAnimeModel();
	for (DWORD i = 0; i < Thing.pAnimController->GetNumAnimationSets(); i++)
	{//AnimSet�ɃA�j���[�V�������i�[
		Thing.pAnimController->GetAnimationSet(i, &pAnimSet[i]);
	}
	//�A�j���[�V������񏉊���
	TrackDesc.Weight = 1;
	TrackDesc.Enable = true;
	TrackDesc.Position = 0;//�A�j���[�V�����^�C�����Z�b�g
	TrackDesc.Speed = 0.01f;//���[�V�����X�s�[�h
	Thing.pAnimController->SetTrackDesc(0, &TrackDesc);//�A�j�����Z�b�g
	Thing.pAnimController->SetTrackAnimationSet(0, pAnimSet[PLAYER_WALK]);//�����A�j���[�V�����Z�b�g
	
	m_Hp = HP_MAX;
	m_Mp = 0;
	m_MpStock = MPSTOCK_INIT;
	m_KO_Count = 0;
	m_Enable = true;
	m_delete = false;
	g_CosterMode = false;
	m_DrawCheck = true;
	m_MoveCheck = false;
	m_Direction = DIRE_UP;
	m_DrawCount = 0;

	D3DXMatrixTranslation(&m_mtxTranslation, 0, 1, 0);
	D3DXMatrixScaling(&m_mtxScaling, PLAYER_SAIZ, PLAYER_SAIZ, PLAYER_SAIZ);
	m_mtxKeepTranslation = m_mtxTranslation;
	D3DXMatrixRotationY(&m_mtxRotation, D3DXToRadian(200));
	m_mtxWorld = m_mtxScaling * m_mtxRotation * m_mtxTranslation;

	m_Angle = 270;
	m_front = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXVec3Normalize(&m_front, &m_front);
	m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVec3Cross(&m_right, &m_front, &m_up);
	D3DXVec3Normalize(&m_right, &m_right);
	D3DXVec3Cross(&m_up, &m_right, &m_front);
	D3DXVec3Normalize(&m_up, &m_up);

	//�R���g���[���[���擾
	js = { 0 };
	pJoyDevice = *JoyDevice_Get();
	if (pJoyDevice)
	{
		hr = pJoyDevice->Acquire();
	}
	Thing.vPosition = D3DXVECTOR3(m_mtxTranslation._41, m_mtxTranslation._42, m_mtxTranslation._43);
}

//	�I������
void CPlayer::Finalize(void)
{
	for (int i = 0; i < m_PlayerNum; i++)
	{
		if (m_pPlayer[i])
		{
			delete m_pPlayer[i];
		}
	}
}



void  CPlayer::AngleChange(bool Angle_Flg)
{

	if (Angle_Flg == true)
	{
		m_Angle += ANGLE;
		D3DXMATRIX mtxR;
		if (m_Angle > 360)
		{
			m_Angle = m_Angle - 360;
		}
		//����(&, ��, angle)
		D3DXMatrixRotationAxis(&mtxR, &m_up, D3DXToRadian(ANGLE));
		D3DXVec3TransformNormal(&m_front, &m_front, &mtxR);
		D3DXVec3TransformNormal(&m_right, &m_right, &mtxR);
	}
	else
	{
		m_Angle += -ANGLE;
		D3DXMATRIX mtxR;
		if (m_Angle < 0)
		{
			m_Angle = 360 - m_Angle;
		}
		//����(&, ��, angle)
		D3DXMatrixRotationAxis(&mtxR, &m_up, D3DXToRadian(-ANGLE));
		D3DXVec3TransformNormal(&m_front, &m_front, &mtxR);
		D3DXVec3TransformNormal(&m_right, &m_right, &mtxR);
	}
}


C3DObj *CPlayer::Get_Player(void)
{
	for (int i = 0; i < MAX_GAMEOBJ; i++)
	{
		C3DObj *pplayer = C3DObj::Get(i);
		if (pplayer->Get_3DObjType() == C3DObj::TYPE_PLAYER)
		{
			return pplayer;
		}
	}
	return 0;
}




void CPlayer::PlayerDamage(void)
{
	for (int i = 0;i < MAX_GAMEOBJ;i++)
	{
		C3DObj *enemy = CEnemy::Get_Enemy(i);
		if (enemy)
		{
			Thing.vPosition = D3DXVECTOR3(m_mtxTranslation._41, m_mtxTranslation._42, m_mtxTranslation._43);
			THING *thingenemy = enemy->GetAnimeModel();
			if (C3DObj::Collision_AnimeVSAnime(&Thing, thingenemy))
			{
				m_Hp--;
				Animation_Change(PLAYER_WALK, 0.05f);
				m_DrawCheck = false;
				break;
			}

		}
	}
}


//=============================================================================
// �ړ�����
//=============================================================================

void CPlayer::Player_Move(void)
{
	//	�΂ߌ����ύX
	if( ((Keyboard_IsPress(DIK_D)) && (Keyboard_IsTrigger(DIK_W)))|| ((Keyboard_IsTrigger(DIK_D)) && (Keyboard_IsPress(DIK_W))) || ((Keyboard_IsTrigger(DIK_D)) && (Keyboard_IsTrigger(DIK_W))))
	{
		if (!doubleflag)
		{
			AngleChange(DIRE_UP_RIGHT);
			m_Direction = DIRE_UP_RIGHT;
			m_MoveCheck = true;
			doubleflag = true;
		}
	}
	if (((Keyboard_IsPress(DIK_A)) && (Keyboard_IsTrigger(DIK_W))) || ((Keyboard_IsTrigger(DIK_A)) && (Keyboard_IsPress(DIK_W))) || ((Keyboard_IsTrigger(DIK_A)) && (Keyboard_IsTrigger(DIK_W))))
	{
		if (!doubleflag)
		{
			AngleChange(DIRE_UP_LEFT);
			m_Direction = DIRE_UP_LEFT;
			m_MoveCheck = true;
			doubleflag = true;
		}
	}
	if (((Keyboard_IsPress(DIK_D)) && (Keyboard_IsTrigger(DIK_S))) || ((Keyboard_IsTrigger(DIK_D)) && (Keyboard_IsPress(DIK_S))) || ((Keyboard_IsTrigger(DIK_D)) && (Keyboard_IsTrigger(DIK_S))))
	{
		if (!doubleflag)
		{
			AngleChange(DIRE_DOWN_RIGHT);
			m_Direction = DIRE_DOWN_RIGHT;
			m_MoveCheck = true;
			doubleflag = true;
		}
	}
	if (((Keyboard_IsPress(DIK_A)) && (Keyboard_IsTrigger(DIK_S))) || ((Keyboard_IsTrigger(DIK_A)) && (Keyboard_IsPress(DIK_S))) || ((Keyboard_IsTrigger(DIK_A)) && (Keyboard_IsTrigger(DIK_S))))
	{
		if (!doubleflag)
		{
			AngleChange(DIRE_DOWN_LEFT);
			m_Direction = DIRE_DOWN_LEFT;
			m_MoveCheck = true;
			doubleflag = true;
		}
	}


	//	�΂߈ړ��I��
	if ((Keyboard_IsRelease(DIK_D)) && (Keyboard_IsPress(DIK_W)))
	{
		if (doubleflag)
		{
			m_Angle -= SLANT;
			m_Direction = DIRE_UP;
			AngleChange(m_Direction);
			doubleflag = false;
		}
	}
	if ((Keyboard_IsPress(DIK_D)) && (Keyboard_IsRelease(DIK_W)))
	{
		if (doubleflag)
		{
			m_Angle += SLANT;
			m_Direction = DIRE_RIGHT;
			AngleChange(m_Direction);
			doubleflag = false;
		}
	}
	if ((Keyboard_IsRelease(DIK_A)) && (Keyboard_IsPress(DIK_W)))
	{
		if (doubleflag)
		{
			m_Angle += SLANT;
			m_Direction = DIRE_UP;
			AngleChange(m_Direction);
			doubleflag = false;
		}
	}
	if ((Keyboard_IsPress(DIK_A)) && (Keyboard_IsRelease(DIK_W)))
	{
		if (doubleflag)
		{
			m_Angle -= SLANT;
			m_Direction = DIRE_LEFT;
			AngleChange(m_Direction);
			doubleflag = false;
		}
	}
	if ((Keyboard_IsRelease(DIK_D)) && (Keyboard_IsPress(DIK_S)))
	{
		if (doubleflag)
		{
			m_Angle += SLANT;
			m_Direction = DIRE_DOWN;
			AngleChange(m_Direction);
			doubleflag = false;
		}
	}
	if ((Keyboard_IsPress(DIK_D)) && (Keyboard_IsRelease(DIK_S)))
	{
		if (doubleflag)
		{
			m_Angle -= SLANT;
			m_Direction = DIRE_RIGHT;
			AngleChange(m_Direction);
			doubleflag = false;
		}
	}
	if ((Keyboard_IsRelease(DIK_A)) && (Keyboard_IsPress(DIK_S)))
	{
		if (doubleflag)
		{
			m_Angle -= SLANT;
			m_Direction = DIRE_DOWN;
			AngleChange(m_Direction);
			doubleflag = false;
		}
	}
	if ((Keyboard_IsPress(DIK_A)) && (Keyboard_IsRelease(DIK_S)))
	{
		if (doubleflag)
		{
			m_Angle += SLANT;
			m_Direction = DIRE_LEFT;
			AngleChange(m_Direction);
			doubleflag = false;
		}
	}
	

	//	�΂߈ړ�
	if (Keyboard_IsPress(DIK_D) && (Keyboard_IsPress(DIK_W)))
	{
		m_mtxTranslation *= Move(FLONT, SPEED);
		m_mtxTranslation *= Move(RIGHT, SPEED / 2);
		AngleChange(DIRE_UP_RIGHT);
		m_Direction = DIRE_UP_RIGHT;
		doubleflag = true;
	}
	if (Keyboard_IsPress(DIK_W) && (Keyboard_IsPress(DIK_A)))
	{
		m_mtxTranslation *= Move(FLONT, SPEED);
		m_mtxTranslation *= Move(LEFT, SPEED / 2);
		AngleChange(DIRE_UP_LEFT);
		m_Direction = DIRE_UP_LEFT;
		doubleflag = true;
	}
	if (Keyboard_IsPress(DIK_S) && (Keyboard_IsPress(DIK_A)))
	{
		m_mtxTranslation *= Move(BACK, SPEED);
		m_mtxTranslation *= Move(LEFT, SPEED / 2);
		AngleChange(DIRE_DOWN_LEFT);
		m_Direction = DIRE_DOWN_LEFT;
		doubleflag = true;
	}
	if (Keyboard_IsPress(DIK_S) && (Keyboard_IsPress(DIK_D)))
	{
		m_mtxTranslation *= Move(BACK, SPEED);
		m_mtxTranslation *= Move(RIGHT, SPEED / 2);
		AngleChange(DIRE_DOWN_RIGHT);
		m_Direction = DIRE_DOWN_RIGHT;
		doubleflag = true;
	}
	if (doubleflag == false)
	{
		//	�\���ړ��@�����ύX
		if (Keyboard_IsTrigger(DIK_W) && (m_Direction != DIRE_UP) && (!m_MoveCheck))
		{
			AngleChange(DIRE_UP);
			m_MoveCheck = true;
		}
		if (Keyboard_IsTrigger(DIK_S) && (m_Direction != DIRE_DOWN) && (!m_MoveCheck))
		{
			AngleChange(DIRE_DOWN);
			m_MoveCheck = true;
		}
		if (Keyboard_IsTrigger(DIK_D) && (m_Direction != DIRE_RIGHT) && (!m_MoveCheck))
		{
			AngleChange(DIRE_RIGHT);
			m_MoveCheck = true;
		}
		if (Keyboard_IsTrigger(DIK_A) && (m_Direction != DIRE_LEFT) && (!m_MoveCheck))
		{
			AngleChange(DIRE_LEFT);
			m_MoveCheck = true;
		}

		//	�ړ��I���@�ҋ@�A�j���[�V����
		if ((Keyboard_IsRelease(DIK_W)) || (Keyboard_IsRelease(DIK_S)) || (Keyboard_IsRelease(DIK_D)) || (Keyboard_IsRelease(DIK_A)))
		{
			m_MoveCheck = false;
			Animation_Change(PLAYER_IDLE, 0.005f);
		}

		//	�\���ړ�
		if (Keyboard_IsPress(DIK_W))
		{
			Animation_Change(PLAYER_WALK, 0.01f);
			if ((Keyboard_IsRelease(DIK_D)) || (Keyboard_IsRelease(DIK_A)))
			{
				AngleChange(DIRE_UP);
			}
			if (!Keyboard_IsPress(DIK_S))
			{
				m_Direction = DIRE_UP;
				AngleChange(DIRE_UP);
				m_mtxTranslation *= Move(FLONT, SPEED);
				m_MoveCheck = true;
			}
		}
		if (Keyboard_IsPress(DIK_S))
		{
			Animation_Change(PLAYER_WALK, 0.01f);
			if ((Keyboard_IsRelease(DIK_D)) || (Keyboard_IsRelease(DIK_A)))
			{
				AngleChange(DIRE_DOWN);
			}
			if (!Keyboard_IsPress(DIK_W))
			{
				m_Direction = DIRE_DOWN;
				AngleChange(DIRE_DOWN);
				m_mtxTranslation *= Move(BACK, SPEED);
				m_MoveCheck = true;
			}
		}
		if (Keyboard_IsPress(DIK_D))
		{
			Animation_Change(PLAYER_WALK, 0.01f);
			if ((Keyboard_IsRelease(DIK_W)) || (Keyboard_IsRelease(DIK_S)) || (Keyboard_IsRelease(DIK_A)))
			{
				AngleChange(DIRE_RIGHT);
			}
			if (!Keyboard_IsPress(DIK_A))
			{
				m_Direction = DIRE_RIGHT;
				AngleChange(DIRE_RIGHT);
				m_mtxTranslation *= Move(RIGHT, SPEED);
				m_MoveCheck = true;
			}
		}
		if (Keyboard_IsPress(DIK_A))
		{
			Animation_Change(PLAYER_WALK, 0.01f);
			if ((Keyboard_IsRelease(DIK_W)) || (Keyboard_IsRelease(DIK_S)) || (Keyboard_IsRelease(DIK_D)))
			{
				AngleChange(DIRE_LEFT);
			}
			if (!Keyboard_IsPress(DIK_D))
			{
				m_Direction = DIRE_LEFT;
				AngleChange(DIRE_LEFT);
				m_mtxTranslation *= Move(LEFT, SPEED);
				m_MoveCheck = true;
			}
		}
	}
	//doubleflag = false;
}


//=============================================================================
// �����ύX
//=============================================================================

void CPlayer::AngleChange(int index)
{

	if (index == DIRE_UP)
	{
		if (m_Direction == DIRE_RIGHT)
		{
			m_Angle -= 90;
		}
		if (m_Direction == DIRE_LEFT)
		{
			m_Angle += 90;
		}
		if (m_Direction == DIRE_DOWN)
		{
			m_Angle += 180;
		}
	}

	if (index == DIRE_DOWN)
	{
		if (m_Direction == DIRE_RIGHT)
		{
			m_Angle += 90;
		}
		if (m_Direction == DIRE_LEFT)
		{
			m_Angle -= 90;
		}
		if (m_Direction == DIRE_UP)
		{
			m_Angle -= 180;
		}
	}

	if (index == DIRE_RIGHT)
	{
		if (m_Direction == DIRE_DOWN)
		{
			m_Angle -= 90;
		}
		if (m_Direction == DIRE_LEFT)
		{
			m_Angle += 180;
		}
		if (m_Direction == DIRE_UP)
		{
			m_Angle += 90;
		}
	}

	if (index == DIRE_LEFT)
	{
		if (m_Direction == DIRE_DOWN)
		{
			m_Angle += 90;
		}
		if (m_Direction == DIRE_RIGHT)
		{
			m_Angle += 180;
		}
		if (m_Direction == DIRE_UP)
		{
			m_Angle -= 90;
		}
	}

	if (index == DIRE_UP_RIGHT)
	{
		if (m_Direction == DIRE_UP)
		{
			m_Angle += SLANT;
		}
		if (m_Direction == DIRE_RIGHT)
		{
			m_Angle -= SLANT;
		}
		
	}

	if (index == DIRE_UP_LEFT)
	{
		if (m_Direction == DIRE_UP)
		{
			m_Angle -= SLANT;
		}
		if (m_Direction == DIRE_LEFT)
		{
			m_Angle += SLANT;
		}
	}

	if (index == DIRE_DOWN_RIGHT)
	{
		if (m_Direction == DIRE_DOWN)
		{
			m_Angle -= SLANT;
		}
		if (m_Direction == DIRE_RIGHT)
		{
			m_Angle += SLANT;
		}
	}

	if (index == DIRE_DOWN_LEFT)
	{
		if (m_Direction == DIRE_DOWN)
		{
			m_Angle += SLANT;
		}
		if (m_Direction == DIRE_LEFT)
		{
			m_Angle -= SLANT;
		}
	}
}

//=============================================================================
// �v���C���[�J��������
//=============================================================================

void CPlayer::Player_Camera(void)
{
	//	�J���������ύX
	if (CCamera::Get_CameraAngleCheck())
	{
		m_Angle = CCamera::Get_Angle();
	}
	//	�J�������Z�b�g
	if ((Keyboard_IsRelease(DIK_RIGHT)) || (Keyboard_IsRelease(DIK_LEFT)))
	{
		if (m_Direction % 2 == 0)
		{
			AngleChange(DIRE_UP);
		}
		else
		{
			if (m_Direction == DIRE_RIGHT)
			{
				AngleChange(DIRE_DOWN);
			}
			else
			{
				AngleChange(DIRE_DOWN);
			}
		}
	}
}

