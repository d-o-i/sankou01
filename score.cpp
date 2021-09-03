//=============================================================================
//
// �^�C�g����ʏ��� [score.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "score.h"
#include "input.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexScore(void);
void SetTextureScore(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureScore = NULL;		// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_vertexWkScore[SCORE_DIGIT][NUM_VERTEX];	// ���_���i�[���[�N

int						g_Score;						// �X�R�A
D3DXVECTOR2				g_posScore;						// �X�R�A�̈ʒu

//=============================================================================
// ����������
//=============================================================================
HRESULT InitScore(int type)
{
	if (type == 0)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_SCORE,				// �t�@�C���̖��O
			&g_pD3DTextureScore);		// �ǂݍ��ރ������[
	}

	g_Score = 0;

	// ���_���̍쐬
	MakeVertexScore();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitScore(void)
{
	if (g_pD3DTextureScore != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureScore->Release();
		g_pD3DTextureScore = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateScore()
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureScore);

	// �X�R�A�̌������`��
	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkScore[i], sizeof(VERTEX_2D));
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexScore(void)
{
	float habaX = GAME_SCORE_SIZE_X;	// �����̉���
	int number = g_Score;

	// ��������������
	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		// ���_���W�̐ݒ�
		g_vertexWkScore[i][0].vtx.x = -habaX * i + GAME_SCORE_POS_X;
		g_vertexWkScore[i][0].vtx.y = GAME_SCORE_POS_Y;
		g_vertexWkScore[i][1].vtx.x = -habaX * i + GAME_SCORE_POS_X + GAME_SCORE_SIZE_X;
		g_vertexWkScore[i][1].vtx.y = GAME_SCORE_POS_Y;
		g_vertexWkScore[i][2].vtx.x = -habaX * i + GAME_SCORE_POS_X;
		g_vertexWkScore[i][2].vtx.y = GAME_SCORE_POS_Y + GAME_SCORE_SIZE_Y;
		g_vertexWkScore[i][3].vtx.x = -habaX * i + GAME_SCORE_POS_X + GAME_SCORE_SIZE_X;
		g_vertexWkScore[i][3].vtx.y = GAME_SCORE_POS_Y + GAME_SCORE_SIZE_Y;

		// rhw�̐ݒ�
		g_vertexWkScore[i][0].rhw =
		g_vertexWkScore[i][1].rhw =
		g_vertexWkScore[i][2].rhw =
		g_vertexWkScore[i][3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		g_vertexWkScore[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkScore[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkScore[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkScore[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		for (int i = 0; i < SCORE_DIGIT; i++)
		{
			// �e�N�X�`�����W�̐ݒ�
			float x = (float)(number % 10);
			g_vertexWkScore[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
			g_vertexWkScore[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
			g_vertexWkScore[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
			g_vertexWkScore[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
			number /= 10;
		}
	}

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureScore(void)
{
	int number = g_Score;

	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		// �e�N�X�`�����W�̐ݒ�
		float x = (float)(number % 10);
		g_vertexWkScore[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		g_vertexWkScore[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		g_vertexWkScore[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		g_vertexWkScore[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		number /= 10;
	}
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexScore(void)
{
	float habaX = RESULT_SCORE_SIZE_X;	// �����̉���

	// ��������������
	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		// ���_���W�̐ݒ�
		g_vertexWkScore[i][0].vtx.x = -habaX * i + RESULT_SCORE_POS_X;
		g_vertexWkScore[i][0].vtx.y = RESULT_SCORE_POS_Y;
		g_vertexWkScore[i][1].vtx.x = -habaX * i + RESULT_SCORE_POS_X + RESULT_SCORE_SIZE_X;
		g_vertexWkScore[i][1].vtx.y = RESULT_SCORE_POS_Y;
		g_vertexWkScore[i][2].vtx.x = -habaX * i + RESULT_SCORE_POS_X;
		g_vertexWkScore[i][2].vtx.y = RESULT_SCORE_POS_Y + RESULT_SCORE_SIZE_Y;
		g_vertexWkScore[i][3].vtx.x = -habaX * i + RESULT_SCORE_POS_X + RESULT_SCORE_SIZE_X;
		g_vertexWkScore[i][3].vtx.y = RESULT_SCORE_POS_Y + RESULT_SCORE_SIZE_Y;
	}
}

//=============================================================================
// �X�R�A���Z����
//=============================================================================
void AddScore(int add)
{
	g_Score += add;

	SetTextureScore();
}