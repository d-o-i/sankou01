//=============================================================================
//
// ���U���g��ʏ��� [result.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "result.h"
#include "input.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexResult(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureResultBG = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureResultClear = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureResultGameOver = NULL;		// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_vertexWkResultBG[NUM_VERTEX];			// ���_���i�[���[�N
VERTEX_2D				g_vertexWkResult[NUM_VERTEX];			// ���_���i�[���[�N

static int g_Num;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitResult(int type)
{
	if (type == 0)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_RESULT_BG,				// �t�@�C���̖��O
		&g_pD3DTextureResultBG);					// �ǂݍ��ރ������[

		D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
			TEXTURE_RESULT_CLEAR,				// �t�@�C���̖��O
			&g_pD3DTextureResultClear);					// �ǂݍ��ރ������[

		D3DXCreateTextureFromFile(pDevice,							// �f�o�C�X�ւ̃|�C���^
			TEXTURE_RESULT_GAMEOVER,				// �t�@�C���̖��O
			&g_pD3DTextureResultGameOver);		// �ǂݍ��ރ������[
	}

	// ���_���̍쐬
	MakeVertexResult();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitResult(void)
{
	if (g_pD3DTextureResultBG != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureResultBG->Release();
		g_pD3DTextureResultBG = NULL;
	}
	if(g_pD3DTextureResultClear != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureResultClear->Release();
		g_pD3DTextureResultClear = NULL;
	}
	if (g_pD3DTextureResultGameOver != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureResultGameOver->Release();
		g_pD3DTextureResultGameOver = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateResult(void)
{
	if(GetKeyboardTrigger(DIK_RETURN))
	{// Enter��������A�X�e�[�W��؂�ւ���
		InitGame();
		SetStage( STAGE_TITLE );
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureResultBG);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkResultBG, sizeof(VERTEX_2D));


	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_Num == 0)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureResultClear);
	}
	else
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureResultGameOver);
	}

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_RESULT, g_vertexWkResult, sizeof(VERTEX_2D));
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexResult(void)
{	
	// ���_���W�̐ݒ�
	g_vertexWkResultBG[0].vtx = D3DXVECTOR3(RESULT_BG_POS_X, RESULT_BG_POS_Y, 0.0f);
	g_vertexWkResultBG[1].vtx = D3DXVECTOR3(RESULT_BG_POS_X + RESULT_BG_SIZE_X, RESULT_BG_POS_Y, 0.0f);
	g_vertexWkResultBG[2].vtx = D3DXVECTOR3(RESULT_BG_POS_X, RESULT_BG_POS_Y + RESULT_BG_SIZE_Y, 0.0f);
	g_vertexWkResultBG[3].vtx = D3DXVECTOR3(RESULT_BG_POS_X + RESULT_BG_SIZE_X, RESULT_BG_POS_Y + RESULT_BG_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkResultBG[0].rhw =
	g_vertexWkResultBG[1].rhw =
	g_vertexWkResultBG[2].rhw =
	g_vertexWkResultBG[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkResultBG[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkResultBG[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkResultBG[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkResultBG[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkResultBG[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkResultBG[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkResultBG[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkResultBG[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	// ���_���W�̐ݒ�
	g_vertexWkResult[0].vtx = D3DXVECTOR3(RESULT_POS_X, RESULT_POS_Y, 0.0f);
	g_vertexWkResult[1].vtx = D3DXVECTOR3(RESULT_POS_X + RESULT_SIZE_X, RESULT_POS_Y, 0.0f);
	g_vertexWkResult[2].vtx = D3DXVECTOR3(RESULT_POS_X, RESULT_POS_Y + RESULT_SIZE_Y, 0.0f);
	g_vertexWkResult[3].vtx = D3DXVECTOR3(RESULT_POS_X + RESULT_SIZE_X, RESULT_POS_Y + RESULT_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkResult[0].rhw =
	g_vertexWkResult[1].rhw =
	g_vertexWkResult[2].rhw =
	g_vertexWkResult[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkResult[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkResult[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkResult[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkResult[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkResult[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkResult[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkResult[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkResult[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̐ݒ�
//=============================================================================
void SetTextureNo(int no)
{
	g_Num = no;
}