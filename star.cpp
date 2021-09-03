//=============================================================================
//
// �^�C�g����ʏ��� [star.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "star.h"
#include "line.h"
#include "arrow.h"
#include "input.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexStar(int no);
void SetVertexStar(int no);
D3DXVECTOR2 SetSelectPos(int pos);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureStar = NULL;		// �e�N�X�`���ւ̃|�C���^

STAR					g_Star[STAR_MAX];

//=============================================================================
// ����������
//=============================================================================
HRESULT InitStar(int type)
{
	if (type == 0)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_STAR,				// �t�@�C���̖��O
			&g_pD3DTextureStar);		// �ǂݍ��ރ������[
	}

	D3DXVECTOR2 randpos;

	for (int i = 0; i < STAR_MAX; i++)
	{
		randpos.x = (float)(rand() % SCREEN_WIDTH);
		randpos.y = (float)(rand() % SCREEN_HEIGHT);

		g_Star[i].use = false;
		g_Star[i].no = 0;
		g_Star[i].pos = D3DXVECTOR2(0.0f, 0.0f);

		// ���_���̍쐬
		MakeVertexStar(i);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitStar(void)
{
	if (g_pD3DTextureStar != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureStar->Release();
		g_pD3DTextureStar = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateStar()
{
	for (int i = 0; i < STAR_MAX; i++)
	{
		if (!GetMove(i) && g_Star[i].use==true)
		{
			g_Star[i].use = false;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawStar(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureStar);

	for (int i = 0; i < STAR_MAX; i++)
	{
		if (g_Star[i].use)
		{
			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_Star[i].vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexStar(int no)
{
	// ���_���W�̐ݒ�
	g_Star[no].vertexWk[0].vtx.x = g_Star[no].pos.x - STAR_SIZE_X;
	g_Star[no].vertexWk[0].vtx.y = g_Star[no].pos.y - STAR_SIZE_X;
	g_Star[no].vertexWk[0].vtx.z = 0.0f;

	g_Star[no].vertexWk[1].vtx.x = g_Star[no].pos.x + STAR_SIZE_X;
	g_Star[no].vertexWk[1].vtx.y = g_Star[no].pos.y - STAR_SIZE_X;
	g_Star[no].vertexWk[1].vtx.z = 0.0f;

	g_Star[no].vertexWk[2].vtx.x = g_Star[no].pos.x - STAR_SIZE_X;
	g_Star[no].vertexWk[2].vtx.y = g_Star[no].pos.y + STAR_SIZE_X;
	g_Star[no].vertexWk[2].vtx.z = 0.0f;

	g_Star[no].vertexWk[3].vtx.x = g_Star[no].pos.x + STAR_SIZE_X;
	g_Star[no].vertexWk[3].vtx.y = g_Star[no].pos.y + STAR_SIZE_X;
	g_Star[no].vertexWk[3].vtx.z = 0.0f;

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_Star[no].vertexWk[0].rhw =
	g_Star[no].vertexWk[1].rhw =
	g_Star[no].vertexWk[2].rhw =
	g_Star[no].vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_Star[no].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_Star[no].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_Star[no].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_Star[no].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_Star[no].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_Star[no].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_Star[no].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_Star[no].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
void SetVertexStar(int no)
{
	// ���_���W�̐ݒ�
	g_Star[no].vertexWk[0].vtx.x = g_Star[no].pos.x - STAR_SIZE_X;
	g_Star[no].vertexWk[0].vtx.y = g_Star[no].pos.y - STAR_SIZE_X;
	g_Star[no].vertexWk[0].vtx.z = 0.0f;

	g_Star[no].vertexWk[1].vtx.x = g_Star[no].pos.x + STAR_SIZE_X;
	g_Star[no].vertexWk[1].vtx.y = g_Star[no].pos.y - STAR_SIZE_X;
	g_Star[no].vertexWk[1].vtx.z = 0.0f;

	g_Star[no].vertexWk[2].vtx.x = g_Star[no].pos.x - STAR_SIZE_X;
	g_Star[no].vertexWk[2].vtx.y = g_Star[no].pos.y + STAR_SIZE_X;
	g_Star[no].vertexWk[2].vtx.z = 0.0f;

	g_Star[no].vertexWk[3].vtx.x = g_Star[no].pos.x + STAR_SIZE_X;
	g_Star[no].vertexWk[3].vtx.y = g_Star[no].pos.y + STAR_SIZE_X;
	g_Star[no].vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// g_Star[no].use�̏�Ԏ擾�֐�
//=============================================================================
bool GetStar(int no)
{
	return g_Star[no].use;
}

//=============================================================================
// g_Star[no].no�̏�Ԏ擾�֐�
//=============================================================================
int GetStarPosNo(int no)
{
	return g_Star[no].no;
}

//=============================================================================
// g_Star[no].pos�̏�Ԏ擾�֐�
//=============================================================================
D3DXVECTOR2 GetStarPos(int no)
{
	return g_Star[no].pos;
}

//=============================================================================
// �X�^�[�̃Z�b�g
//=============================================================================
void SetStar(int pos)
{
	for (int i = 0; i < STAR_MAX; i++)
	{
		if (!g_Star[i].use)
		{
			g_Star[i].use = true;
			g_Star[i].no = pos;
			g_Star[i].pos = SetSelectPos(pos);
			SetVertexStar(i);
			SetLine(i, g_Star[i].pos);
			SetArrow(i, g_Star[i].pos);
			SetArrow(i + STAR_MAX, g_Star[i].pos);

			return;
		}
	}
}

//=============================================================================
// �X�^�[�̈ʒu�Z�b�g
//=============================================================================
D3DXVECTOR2 SetSelectPos(int posno)
{
	D3DXVECTOR2 pos;

	int posX = posno % 6;
	int posY = posno / 6;

	pos.x = STAR_POS_X + STAR_SPACE_X * posX;
	pos.y = STAR_POS_Y + STAR_SPACE_Y * posY;

	return pos;
}
