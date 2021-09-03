//=============================================================================
//
// �^�C�g����ʏ��� [life.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "life.h"
#include "score.h"
#include "result.h"
#include "input.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexLife(void);
void SetVertexLife(void);
void SetTextureLife(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureLife = NULL;		// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_vertexWkLife[NUM_VERTEX];			// ���_���i�[���[�N

static int g_Life;
static int g_LifeMax;
static float g_per;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitLife(int type)
{
	if (type == 0)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_LIFE,				// �t�@�C���̖��O
			&g_pD3DTextureLife);		// �ǂݍ��ރ������[
	}

	g_Life = 100;
	g_LifeMax = 100;
	g_per = 1.0f;

	// ���_���̍쐬
	MakeVertexLife();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitLife(void)
{
	if (g_pD3DTextureLife != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureLife->Release();
		g_pD3DTextureLife = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateLife()
{
	if (g_Life == 0)
	{
		SetTextureNo(1);
		SetVertexScore();
		SetStage(STAGE_RESULT);
	}

	SetVertexLife();
	SetTextureLife();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureLife);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkLife, sizeof(VERTEX_2D));
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexLife(void)
{
	// ���_���W�̐ݒ�
	g_vertexWkLife[0].vtx = D3DXVECTOR3(LIFE_POS_X, LIFE_POS_Y, 0.0f);
	g_vertexWkLife[1].vtx = D3DXVECTOR3(LIFE_POS_X + LIFE_SIZE_X, LIFE_POS_Y, 0.0f);
	g_vertexWkLife[2].vtx = D3DXVECTOR3(LIFE_POS_X, LIFE_POS_Y + LIFE_SIZE_Y, 0.0f);
	g_vertexWkLife[3].vtx = D3DXVECTOR3(LIFE_POS_X + LIFE_SIZE_X, LIFE_POS_Y + LIFE_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkLife[0].rhw =
	g_vertexWkLife[1].rhw =
	g_vertexWkLife[2].rhw =
	g_vertexWkLife[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkLife[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkLife[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkLife[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkLife[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkLife[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkLife[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkLife[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkLife[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexLife(void)
{
	// ���_���W�̐ݒ�
	g_vertexWkLife[0].vtx = D3DXVECTOR3(LIFE_POS_X, LIFE_POS_Y, 0.0f);
	g_vertexWkLife[1].vtx = D3DXVECTOR3(LIFE_POS_X + LIFE_SIZE_X * g_per, LIFE_POS_Y, 0.0f);
	g_vertexWkLife[2].vtx = D3DXVECTOR3(LIFE_POS_X, LIFE_POS_Y + LIFE_SIZE_Y, 0.0f);
	g_vertexWkLife[3].vtx = D3DXVECTOR3(LIFE_POS_X + LIFE_SIZE_X * g_per, LIFE_POS_Y + LIFE_SIZE_Y, 0.0f);
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureLife(void)
{
	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkLife[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkLife[1].tex = D3DXVECTOR2(g_per, 0.0f);
	g_vertexWkLife[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkLife[3].tex = D3DXVECTOR2(g_per, 1.0f);
}

//=============================================================================
// ���C�t�̉��Z���Z����
//=============================================================================
void CalLife(int val)
{
	g_Life += val;

	if (g_Life > g_LifeMax)
	{
		g_Life = g_LifeMax;
	}
	else if (g_Life < 0)
	{
		g_Life = 0;
	}

	g_per = (float)g_Life / g_LifeMax;
}