//=============================================================================
//
// �^�C�g����ʏ��� [bg.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "bg.h"
#include "input.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBg(void);
void SetVertexBg(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBg = NULL;		// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_vertexWkBg[NUM_VERTEX];			// ���_���i�[���[�N

																//=============================================================================
																// ����������
																//=============================================================================
HRESULT InitBg(int type)
{
	if (type == 0)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_BG,				// �t�@�C���̖��O
			&g_pD3DTextureBg);		// �ǂݍ��ރ������[
	}

	// ���_���̍쐬
	MakeVertexBg();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBg(void)
{
	if (g_pD3DTextureBg != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureBg->Release();
		g_pD3DTextureBg = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBg()
{
	SetVertexBg();

	if (GetKeyboardTrigger(DIK_RETURN))
	{
		SetStage(STAGE_GAME);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureBg);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkBg, sizeof(VERTEX_2D));
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBg(void)
{

	// ���_���W�̐ݒ�
	g_vertexWkBg[0].vtx = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);
	g_vertexWkBg[1].vtx = D3DXVECTOR3(BG_POS_X + BG_SIZE_X, BG_POS_Y, 0.0f);
	g_vertexWkBg[2].vtx = D3DXVECTOR3(BG_POS_X, BG_POS_Y + BG_SIZE_Y, 0.0f);
	g_vertexWkBg[3].vtx = D3DXVECTOR3(BG_POS_X + BG_SIZE_X, BG_POS_Y + BG_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkBg[0].rhw =
		g_vertexWkBg[1].rhw =
		g_vertexWkBg[2].rhw =
		g_vertexWkBg[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkBg[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkBg[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkBg[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkBg[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkBg[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkBg[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkBg[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkBg[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBg(void)
{

}