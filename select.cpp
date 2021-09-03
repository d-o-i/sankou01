//=============================================================================
//
// �^�C�g����ʏ��� [select.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "select.h"
#include "sound.h"
#include "load.h"
#include "input.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexSelect(void);
void SetVertexSelect(void);
void UpdateVertexSelect(void);
void SetTextureSelect(void);
void SetSelectWk(void);
void SetMusicWk(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureSelect = NULL;				// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_vertexWkSelect[NUM_VERTEX];			// ���_���i�[���[�N

VERTEX_2D				g_vertexWkLogo[NUM_VERTEX];				// ���_���i�[���[�N

#define		SELECT_MAX		(5)

#define		SECOND_MAX		(20)
#define		FRAME_MAX		(20)
#define		UPDATE_FRAME	(SECOND_MAX / FRAME_MAX)

// ��ʑJ�ڒ萔
enum E_MUSIC
{
	MUSIC_SUPERNOVA,
	MUSIC_DEEPER,
	MUSIC_DAYDREAM,
	MUSIC_MAX
};

const char *g_aMusicName[MUSIC_MAX] =
{
	"supernova",
	"deeper",
	"daydream"
};

const char *g_nMusicTexture[MUSIC_MAX * 2] =
{
	TEXTURE_SELECT_SUPERNOVA,
	TEXTURE_SELECT_SUPERNOVA_LOGO,
	TEXTURE_SELECT_DEEPER,
	TEXTURE_SELECT_DEEPER_LOGO,
	TEXTURE_SELECT_DAYDREAM,
	TEXTURE_SELECT_DAYDREAM_LOGO
};

const float g_fSelectInfo[SELECT_MAX * 3] =
{
	JACKET_SIZE0,
	JACKET_POS_X0,
	JACKET_POS_Y0,
	JACKET_SIZE1,
	JACKET_POS_X1,
	JACKET_POS_Y1,
	JACKET_SIZE2,
	JACKET_POS_X2,
	JACKET_POS_Y2,
	JACKET_SIZE3,
	JACKET_POS_X3,
	JACKET_POS_Y3,
	JACKET_SIZE4,
	JACKET_POS_X4,
	JACKET_POS_Y4
};

struct MUSIC
{
	D3DXVECTOR2 Pos;
	D3DXVECTOR2 DestPos;
	D3DXVECTOR2 DifPos;
	D3DXVECTOR2 FramePos;

	float		Size;
	float		DestSize;
	float		DifSize;
	float		FrameSize;

	LPDIRECT3DTEXTURE9		pD3DTextureMusic = NULL;				// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DTEXTURE9		pD3DTextureMusicLogo = NULL;			// �e�N�X�`���ւ̃|�C���^

	VERTEX_2D				vertexWkMusic[NUM_VERTEX];			// ���_���i�[���[�N
};

struct SELECT
{
	D3DXVECTOR2 pos;
	float		size;
};

MUSIC	g_MusicWk[MUSIC_MAX];

SELECT	g_SelectWk[SELECT_MAX];

int			g_mNum;
int			g_mOld;
int			g_sNum = -1;
int			g_nSelect;
int			g_nCountFrame;
int			g_nCount;
bool		g_Change;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitSelect(int type)
{
	if (type == 0)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
			TEXTURE_SELECT,								// �t�@�C���̖��O
			&g_pD3DTextureSelect);						// �ǂݍ��ރ������[

		for (int i = 0; i < MUSIC_MAX; i++)
		{
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
				g_nMusicTexture[i * 2],								// �t�@�C���̖��O
				&g_MusicWk[i].pD3DTextureMusic);						// �ǂݍ��ރ������[

			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
				g_nMusicTexture[i * 2 + 1],						// �t�@�C���̖��O
				&g_MusicWk[i].pD3DTextureMusicLogo);					// �ǂݍ��ރ������[
		}
	}
	// ������
	g_mOld = g_mNum = MUSIC_STARTNO;
	g_nSelect = 2;
	g_nCountFrame = 0;
	g_nCount = 0;
	g_Change = false;

	// SELECT�\���̂̏�����
	SetSelectWk();

	// �~���[�W�b�N�\���̂̐ݒ�
	SetMusicWk();

	// ���_���̍쐬
	MakeVertexSelect();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitSelect(void)
{
	if (g_pD3DTextureSelect != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureSelect->Release();
		g_pD3DTextureSelect = NULL;
	}

	for (int i = 0; i < MUSIC_MAX; i++)
	{
		if (g_MusicWk[i].pD3DTextureMusic != NULL)
		{// �e�N�X�`���̊J��
			g_MusicWk[i].pD3DTextureMusic->Release();
			g_MusicWk[i].pD3DTextureMusic = NULL;
		}
		if (g_MusicWk[i].pD3DTextureMusicLogo != NULL)
		{// �e�N�X�`���̊J��
			g_MusicWk[i].pD3DTextureMusicLogo->Release();
			g_MusicWk[i].pD3DTextureMusicLogo = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateSelect(void)
{
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		// �O��ʂ̋Ȃ��~�߂�
		StopSound(g_pBGM[g_mNum], E_DS8_FLAG_NONE);
		// ���Ɏg���Ȃ̍Đ��ʒu����ԍŏ��ɐݒ�
		g_pBGM[g_mNum]->SetCurrentPosition(0);
		// �Đ�		
		PlaySound(g_pBGM[g_mNum], E_DS8_FLAG_NONE);

		// BGM�J�n���Ԃ̕ۑ�
		SetStartTime();

		// ���y�ԍ��̐ݒ�
		SetMusic(g_mNum);

		if (g_sNum != g_mNum)
		{
			InitLoad(0);

			// CSV�t�@�C���̓ǂݍ���
			LoadCSV(g_aMusicName[g_mNum - MUSIC_STARTNO]);

			g_sNum = g_mNum;
		}

		SetStage(STAGE_GAME);
	}
	
	if (!g_Change)
	{
		if (GetKeyboardTrigger(DIK_LEFT))
		{
			// ���ݍĐ�����BGM���~
			StopSound(g_pBGM[g_mNum], E_DS8_FLAG_NONE);

			g_mNum--;
			g_nSelect++;
			if (g_mNum < MUSIC_STARTNO)
			{
				//g_mNum = (MUSIC_MAX + MUSIC_STARTNO) - 1;
				g_mNum = MUSIC_STARTNO;
				g_nSelect = 2;
			}
			//if (g_nSelect < 0)
			//{

			//}
			g_Change = true;
		}
		else if (GetKeyboardTrigger(DIK_RIGHT))
		{
			// ���ݍĐ�����BGM���~
			StopSound(g_pBGM[g_mNum], E_DS8_FLAG_NONE);

			g_mNum++;
			g_nSelect--;
			if (g_mNum > (MUSIC_MAX + MUSIC_STARTNO) - 1)
			{
				//g_mNum = MUSIC_STARTNO;
				g_mNum = (MUSIC_MAX + MUSIC_STARTNO) - 1;
				g_nSelect = 0;
			}

			//if (g_nSelect > SELECT_MAX - 1)
			//{

			//}
			g_Change = true;
		}
	}

	if (g_mOld != g_mNum)
	{
		// ���Ɏg���Ȃ̍Đ��ʒu����ԍŏ��ɐݒ�
		g_pBGM[g_mNum]->SetCurrentPosition(0);
		// �Đ�		
		PlaySound(g_pBGM[g_mNum], E_DS8_FLAG_NONE);

		SetVertexSelect();
		g_mOld = g_mNum;
	}

	UpdateVertexSelect();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawSelect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureSelect);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkSelect, sizeof(VERTEX_2D));

	for (int i = 0; i < MUSIC_MAX; i++)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_MusicWk[i].pD3DTextureMusic);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_MusicWk[i].vertexWkMusic, sizeof(VERTEX_2D));
	}

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_MusicWk[g_mNum - MUSIC_STARTNO].pD3DTextureMusicLogo);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkLogo, sizeof(VERTEX_2D));
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexSelect(void)
{
	//=======================
	// �w�i
	//=======================

	// ���_���W�̐ݒ�
	g_vertexWkSelect[0].vtx = D3DXVECTOR3(SELECT_POS_X, SELECT_POS_Y, 0.0f);
	g_vertexWkSelect[1].vtx = D3DXVECTOR3(SELECT_POS_X + SELECT_SIZE_X, SELECT_POS_Y, 0.0f);
	g_vertexWkSelect[2].vtx = D3DXVECTOR3(SELECT_POS_X, SELECT_POS_Y + SELECT_SIZE_Y, 0.0f);
	g_vertexWkSelect[3].vtx = D3DXVECTOR3(SELECT_POS_X + SELECT_SIZE_X, SELECT_POS_Y + SELECT_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkSelect[0].rhw =
	g_vertexWkSelect[1].rhw =
	g_vertexWkSelect[2].rhw =
	g_vertexWkSelect[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkSelect[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkSelect[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkSelect[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkSelect[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkSelect[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkSelect[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkSelect[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkSelect[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	//=======================
	// MusicJacket
	//=======================

	for (int i = 0; i < MUSIC_MAX; i++)
	{
		// ���_���W�̐ݒ�
		g_MusicWk[i].vertexWkMusic[0].vtx = D3DXVECTOR3(g_MusicWk[i].Pos.x - g_MusicWk[i].Size, g_MusicWk[i].Pos.y - g_MusicWk[i].Size, 0.0f);
		g_MusicWk[i].vertexWkMusic[1].vtx = D3DXVECTOR3(g_MusicWk[i].Pos.x + g_MusicWk[i].Size, g_MusicWk[i].Pos.y - g_MusicWk[i].Size, 0.0f);
		g_MusicWk[i].vertexWkMusic[2].vtx = D3DXVECTOR3(g_MusicWk[i].Pos.x - g_MusicWk[i].Size, g_MusicWk[i].Pos.y + g_MusicWk[i].Size, 0.0f);
		g_MusicWk[i].vertexWkMusic[3].vtx = D3DXVECTOR3(g_MusicWk[i].Pos.x + g_MusicWk[i].Size, g_MusicWk[i].Pos.y + g_MusicWk[i].Size, 0.0f);

		// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
		g_MusicWk[i].vertexWkMusic[0].rhw =
		g_MusicWk[i].vertexWkMusic[1].rhw =
		g_MusicWk[i].vertexWkMusic[2].rhw =
		g_MusicWk[i].vertexWkMusic[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		g_MusicWk[i].vertexWkMusic[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_MusicWk[i].vertexWkMusic[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_MusicWk[i].vertexWkMusic[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_MusicWk[i].vertexWkMusic[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		g_MusicWk[i].vertexWkMusic[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_MusicWk[i].vertexWkMusic[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		g_MusicWk[i].vertexWkMusic[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		g_MusicWk[i].vertexWkMusic[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}


	//=======================
	// Logo
	//=======================

	// ���_���W�̐ݒ�
	g_vertexWkLogo[0].vtx = D3DXVECTOR3(LOGO_POS_X - LOGO_SIZE_X, LOGO_POS_Y - LOGO_SIZE_Y, 0.0f);
	g_vertexWkLogo[1].vtx = D3DXVECTOR3(LOGO_POS_X + LOGO_SIZE_X, LOGO_POS_Y - LOGO_SIZE_Y, 0.0f);
	g_vertexWkLogo[2].vtx = D3DXVECTOR3(LOGO_POS_X - LOGO_SIZE_X, LOGO_POS_Y + LOGO_SIZE_Y, 0.0f);
	g_vertexWkLogo[3].vtx = D3DXVECTOR3(LOGO_POS_X + LOGO_SIZE_X, LOGO_POS_Y + LOGO_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkLogo[0].rhw =
	g_vertexWkLogo[1].rhw =
	g_vertexWkLogo[2].rhw =
	g_vertexWkLogo[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkLogo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkLogo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkLogo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkLogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkLogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkLogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkLogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkLogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexSelect(void)
{
	// �ړI�̈ʒu�E�T�C�Y�̐ݒ�
	for (int i = 0; i < MUSIC_MAX; i++)
	{
		g_MusicWk[i].DestPos = g_SelectWk[g_nSelect + i].pos;
		g_MusicWk[i].DestSize = g_SelectWk[g_nSelect + i].size;
	}

	// ���݂̈ʒu�E�T�C�Y�ƖړI�̈ʒu�E�T�C�Y�̍��̐ݒ�
	for (int i = 0; i < MUSIC_MAX; i++)
	{
		g_MusicWk[i].DifPos = g_MusicWk[i].DestPos - g_MusicWk[i].Pos;
		g_MusicWk[i].DifSize = g_MusicWk[i].DestSize - g_MusicWk[i].Size;
	}

	// �t���[�����̈ړ��ʐݒ�
	for (int i = 0; i < MUSIC_MAX; i++)
	{
		g_MusicWk[i].FramePos = g_MusicWk[i].DifPos / FRAME_MAX;
		g_MusicWk[i].FrameSize = g_MusicWk[i].DifSize / FRAME_MAX;
	}
}

//=============================================================================
// ���_���W�̍X�V
//=============================================================================
void UpdateVertexSelect(void)
{
	if (g_Change)
	{
		if (g_nCountFrame != UPDATE_FRAME)
		{
			g_nCountFrame++;
		}
		else
		{
			if (g_nCount != FRAME_MAX)
			{
				// UPDATE_FRAME���Ɉړ�
				for (int i = 0; i < MUSIC_MAX; i++)
				{
					g_MusicWk[i].Pos += g_MusicWk[i].FramePos;
					g_MusicWk[i].Size += g_MusicWk[i].FrameSize;
				}

				// �ړ��𔽉f
				for (int i = 0; i < MUSIC_MAX; i++)
				{
					// ���_���W�̐ݒ�
					g_MusicWk[i].vertexWkMusic[0].vtx = D3DXVECTOR3(g_MusicWk[i].Pos.x - g_MusicWk[i].Size, g_MusicWk[i].Pos.y - g_MusicWk[i].Size, 0.0f);
					g_MusicWk[i].vertexWkMusic[1].vtx = D3DXVECTOR3(g_MusicWk[i].Pos.x + g_MusicWk[i].Size, g_MusicWk[i].Pos.y - g_MusicWk[i].Size, 0.0f);
					g_MusicWk[i].vertexWkMusic[2].vtx = D3DXVECTOR3(g_MusicWk[i].Pos.x - g_MusicWk[i].Size, g_MusicWk[i].Pos.y + g_MusicWk[i].Size, 0.0f);
					g_MusicWk[i].vertexWkMusic[3].vtx = D3DXVECTOR3(g_MusicWk[i].Pos.x + g_MusicWk[i].Size, g_MusicWk[i].Pos.y + g_MusicWk[i].Size, 0.0f);
				}

				g_nCount++;
			}
			else
			{
				g_Change = false;

				g_nCount = 0;
			}

			g_nCountFrame = 0;
		}
	}
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureSelect(void)
{
	
}

//=============================================================================
// �~���[�W�b�N�\���̂̐ݒ�
//=============================================================================
void SetMusicWk(void)
{
	for (int i = 0; i < MUSIC_MAX; i++)
	{
		g_MusicWk[i].Pos = g_SelectWk[g_nSelect + i].pos;
		g_MusicWk[i].Size = g_SelectWk[g_nSelect + i].size;
	}
}

//=============================================================================
// �Z���N�g�\���̂̐ݒ�
//=============================================================================
void SetSelectWk(void)
{
	for (int i = 0; i < SELECT_MAX; i++)
	{
		g_SelectWk[i].pos = D3DXVECTOR2(g_fSelectInfo[3 * i + 1], g_fSelectInfo[3 * i + 2]);
		g_SelectWk[i].size = g_fSelectInfo[3 * i];
	}
}

//=============================================================================
// �ŏ��ɗ������y�̐ݒ�
//=============================================================================
void StartMusic(void)
{
	// ���Ɏg���Ȃ̍Đ��ʒu����ԍŏ��ɐݒ�
	g_pBGM[g_mNum]->SetCurrentPosition(0);
	// �Đ�		
	PlaySound(g_pBGM[g_mNum], E_DS8_FLAG_NONE);
}

int GetSelectNo(void)
{
	return g_mNum - MUSIC_STARTNO;
}


float GetSuperPos(void)
{
	return g_MusicWk[0].Pos.x;
}

float GetSelectSuperPos(void)
{
	return g_SelectWk[2].pos.x;
}

int GetSelectno(void)
{
	return g_nSelect;
}