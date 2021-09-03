//=============================================================================
//
// �^�C�g����ʏ��� [combo.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "combo.h"
#include "select.h"
#include "check.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexCombo(void);
void SetTextureCombo(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureCombo = NULL;				// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureSupernova = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureSupernovaLogo = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureDeeper = NULL;				// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureDeeperLogo = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureDaydream = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureDaydreamLogo = NULL;		// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_vertexWkJust[COMBO_DIGIT][NUM_VERTEX];		// ���_���i�[���[�N
VERTEX_2D				g_vertexWkGood[COMBO_DIGIT][NUM_VERTEX];		// ���_���i�[���[�N
VERTEX_2D				g_vertexWkMiss[COMBO_DIGIT][NUM_VERTEX];		// ���_���i�[���[�N
VERTEX_2D				g_vertexWkJacket[NUM_VERTEX];						// ���_���i�[���[�N
VERTEX_2D				g_vertexWkJacketLogo[NUM_VERTEX];					// ���_���i�[���[�N

static bool Flag;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitCombo(int type)
{
	if (type == 0)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_COMBO,				// �t�@�C���̖��O
			&g_pD3DTextureCombo);		// �ǂݍ��ރ������[

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_RESULT_SUPERNOVA_JACKET,				// �t�@�C���̖��O
			&g_pD3DTextureSupernova);		// �ǂݍ��ރ������[

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_RESULT_SUPERNOVA_LOGO,				// �t�@�C���̖��O
			&g_pD3DTextureSupernovaLogo);		// �ǂݍ��ރ������[

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_RESULT_DEEPER_JACKET,				// �t�@�C���̖��O
			&g_pD3DTextureDeeper);		// �ǂݍ��ރ������[

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_RESULT_DEEPER_LOGO,				// �t�@�C���̖��O
			&g_pD3DTextureDeeperLogo);		// �ǂݍ��ރ������[
										
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_RESULT_DAYDREAM_JACKET,				// �t�@�C���̖��O
			&g_pD3DTextureDaydream);		// �ǂݍ��ރ������[

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_RESULT_DAYDREAM_LOGO,				// �t�@�C���̖��O
			&g_pD3DTextureDaydreamLogo);		// �ǂݍ��ރ������[
	}

	// ���_���̍쐬
	MakeVertexCombo();

	Flag = false;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitCombo(void)
{
	if (g_pD3DTextureCombo != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureCombo->Release();
		g_pD3DTextureCombo = NULL;
	}

	if (g_pD3DTextureSupernova != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureSupernova->Release();
		g_pD3DTextureSupernova = NULL;
	}

	if (g_pD3DTextureSupernovaLogo != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureSupernovaLogo->Release();
		g_pD3DTextureSupernovaLogo = NULL;
	}

	if (g_pD3DTextureDeeper != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureDeeper->Release();
		g_pD3DTextureDeeper = NULL;
	}

	if (g_pD3DTextureDeeperLogo != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureDeeperLogo->Release();
		g_pD3DTextureDeeperLogo = NULL;
	}

	if (g_pD3DTextureDaydream != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureDaydream->Release();
		g_pD3DTextureDaydream = NULL;
	}

	if (g_pD3DTextureDaydreamLogo != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureDaydreamLogo->Release();
		g_pD3DTextureDaydreamLogo = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateCombo()
{
	if (!Flag)
	{
		SetTextureCombo();
		Flag = true;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawCombo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureCombo);

	// �W���X�g����̌������`��
	for (int i = 0; i < COMBO_DIGIT; i++)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkJust[i], sizeof(VERTEX_2D));
	}

	// �O�b�h����̌������`��
	for (int i = 0; i < COMBO_DIGIT; i++)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkGood[i], sizeof(VERTEX_2D));
	}

	// �~�X����̌������`��
	for (int i = 0; i < COMBO_DIGIT; i++)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkMiss[i], sizeof(VERTEX_2D));
	}

	// ���y�̃W���P�b�g�E���S�̕`��

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	switch (GetSelectNo())
	{
	case 0:
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureSupernova);
		break;
	case 1:
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureDeeper);
		break;
	case 2:
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureDaydream);
		break;
	}

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkJacket, sizeof(VERTEX_2D));


	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	switch (GetSelectNo())
	{
	case 0:
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureSupernovaLogo);
		break;
	case 1:
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureDeeperLogo);
		break;
	case 2:
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureDaydreamLogo);
		break;
	}

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkJacketLogo, sizeof(VERTEX_2D));
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexCombo(void)
{
	float habaX = COMBO_SIZE_X;	// �����̉���
	int number;

	// �W���X�g���萔����������������

	// �W���X�g���萔�\��
	number = GetJust();

	for (int i = 0; i < COMBO_DIGIT; i++)
	{
		// ���_���W�̐ݒ�
		g_vertexWkJust[i][0].vtx.x = -habaX * i + COMBO_JUST_POS_X;
		g_vertexWkJust[i][0].vtx.y = COMBO_JUST_POS_Y;
		g_vertexWkJust[i][1].vtx.x = -habaX * i + COMBO_JUST_POS_X + COMBO_SIZE_X;
		g_vertexWkJust[i][1].vtx.y = COMBO_JUST_POS_Y;
		g_vertexWkJust[i][2].vtx.x = -habaX * i + COMBO_JUST_POS_X;
		g_vertexWkJust[i][2].vtx.y = COMBO_JUST_POS_Y + COMBO_SIZE_Y;
		g_vertexWkJust[i][3].vtx.x = -habaX * i + COMBO_JUST_POS_X + COMBO_SIZE_X;
		g_vertexWkJust[i][3].vtx.y = COMBO_JUST_POS_Y + COMBO_SIZE_Y;

		// rhw�̐ݒ�
		g_vertexWkJust[i][0].rhw =
		g_vertexWkJust[i][1].rhw =
		g_vertexWkJust[i][2].rhw =
		g_vertexWkJust[i][3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		g_vertexWkJust[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkJust[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkJust[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkJust[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		float x = (float)(number % 10);
		g_vertexWkJust[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		g_vertexWkJust[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		g_vertexWkJust[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		g_vertexWkJust[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		number /= 10;
	}

	// �O�b�h���萔����������������

	// �O�b�h���萔�\��
	number = GetGood();

	for (int i = 0; i < COMBO_DIGIT; i++)
	{
		// ���_���W�̐ݒ�
		g_vertexWkGood[i][0].vtx.x = -habaX * i + COMBO_GOOD_POS_X;
		g_vertexWkGood[i][0].vtx.y = COMBO_GOOD_POS_Y;
		g_vertexWkGood[i][1].vtx.x = -habaX * i + COMBO_GOOD_POS_X + COMBO_SIZE_X;
		g_vertexWkGood[i][1].vtx.y = COMBO_GOOD_POS_Y;
		g_vertexWkGood[i][2].vtx.x = -habaX * i + COMBO_GOOD_POS_X;
		g_vertexWkGood[i][2].vtx.y = COMBO_GOOD_POS_Y + COMBO_SIZE_Y;
		g_vertexWkGood[i][3].vtx.x = -habaX * i + COMBO_GOOD_POS_X + COMBO_SIZE_X;
		g_vertexWkGood[i][3].vtx.y = COMBO_GOOD_POS_Y + COMBO_SIZE_Y;

		// rhw�̐ݒ�
		g_vertexWkGood[i][0].rhw =
		g_vertexWkGood[i][1].rhw =
		g_vertexWkGood[i][2].rhw =
		g_vertexWkGood[i][3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		g_vertexWkGood[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkGood[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkGood[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkGood[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		float x = (float)(number % 10);
		g_vertexWkGood[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		g_vertexWkGood[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		g_vertexWkGood[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		g_vertexWkGood[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		number /= 10;
	}

	// �~�X���萔����������������

	// �~�X���萔�\��
	number = GetMiss();

	for (int i = 0; i < COMBO_DIGIT; i++)
	{
		// ���_���W�̐ݒ�
		g_vertexWkMiss[i][0].vtx.x = -habaX * i + COMBO_MISS_POS_X;
		g_vertexWkMiss[i][0].vtx.y = COMBO_MISS_POS_Y;
		g_vertexWkMiss[i][1].vtx.x = -habaX * i + COMBO_MISS_POS_X + COMBO_SIZE_X;
		g_vertexWkMiss[i][1].vtx.y = COMBO_MISS_POS_Y;
		g_vertexWkMiss[i][2].vtx.x = -habaX * i + COMBO_MISS_POS_X;
		g_vertexWkMiss[i][2].vtx.y = COMBO_MISS_POS_Y + COMBO_SIZE_Y;
		g_vertexWkMiss[i][3].vtx.x = -habaX * i + COMBO_MISS_POS_X + COMBO_SIZE_X;
		g_vertexWkMiss[i][3].vtx.y = COMBO_MISS_POS_Y + COMBO_SIZE_Y;

		// rhw�̐ݒ�
		g_vertexWkMiss[i][0].rhw =
		g_vertexWkMiss[i][1].rhw =
		g_vertexWkMiss[i][2].rhw =
		g_vertexWkMiss[i][3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		g_vertexWkMiss[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkMiss[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkMiss[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkMiss[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		float x = (float)(number % 10);
		g_vertexWkMiss[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		g_vertexWkMiss[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		g_vertexWkMiss[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		g_vertexWkMiss[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		number /= 10;
	}

	// ���_���W�̐ݒ�
	g_vertexWkJacket[0].vtx = D3DXVECTOR3(COMBO_JACKET_POS_X, COMBO_JACKET_POS_Y, 0.0f);
	g_vertexWkJacket[1].vtx = D3DXVECTOR3(COMBO_JACKET_POS_X + COMBO_JACKET_SIZE_X, COMBO_JACKET_POS_Y, 0.0f);
	g_vertexWkJacket[2].vtx = D3DXVECTOR3(COMBO_JACKET_POS_X, COMBO_JACKET_POS_Y + COMBO_JACKET_SIZE_Y, 0.0f);
	g_vertexWkJacket[3].vtx = D3DXVECTOR3(COMBO_JACKET_POS_X + COMBO_JACKET_SIZE_X, COMBO_JACKET_POS_Y + COMBO_JACKET_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkJacket[0].rhw =
	g_vertexWkJacket[1].rhw =
	g_vertexWkJacket[2].rhw =
	g_vertexWkJacket[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkJacket[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkJacket[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkJacket[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkJacket[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkJacket[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkJacket[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkJacket[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkJacket[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	// ���_���W�̐ݒ�
	g_vertexWkJacketLogo[0].vtx = D3DXVECTOR3(COMBO_LOGO_POS_X, COMBO_LOGO_POS_Y, 0.0f);
	g_vertexWkJacketLogo[1].vtx = D3DXVECTOR3(COMBO_LOGO_POS_X + COMBO_LOGO_SIZE_X, COMBO_LOGO_POS_Y, 0.0f);
	g_vertexWkJacketLogo[2].vtx = D3DXVECTOR3(COMBO_LOGO_POS_X, COMBO_LOGO_POS_Y + COMBO_LOGO_SIZE_Y, 0.0f);
	g_vertexWkJacketLogo[3].vtx = D3DXVECTOR3(COMBO_LOGO_POS_X + COMBO_LOGO_SIZE_X, COMBO_LOGO_POS_Y + COMBO_LOGO_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkJacketLogo[0].rhw =
	g_vertexWkJacketLogo[1].rhw =
	g_vertexWkJacketLogo[2].rhw =
	g_vertexWkJacketLogo[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkJacketLogo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkJacketLogo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkJacketLogo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkJacketLogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkJacketLogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkJacketLogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkJacketLogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkJacketLogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureCombo(void)
{
	int number;

	// �W���X�g���萔����������������

	// �W���X�g���萔�\��
	number = GetJust();

	for (int i = 0; i < COMBO_DIGIT; i++)
	{
		// �e�N�X�`�����W�̐ݒ�
		float x = (float)(number % 10);
		g_vertexWkJust[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		g_vertexWkJust[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		g_vertexWkJust[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		g_vertexWkJust[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		number /= 10;
	}

	// �O�b�h���萔����������������

	// �O�b�h���萔�\��
	number = GetGood();

	for (int i = 0; i < COMBO_DIGIT; i++)
	{
		// �e�N�X�`�����W�̐ݒ�
		float x = (float)(number % 10);
		g_vertexWkGood[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		g_vertexWkGood[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		g_vertexWkGood[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		g_vertexWkGood[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		number /= 10;
	}

	// �~�X���萔����������������

	// �~�X���萔�\��
	number = GetMiss();

	for (int i = 0; i < COMBO_DIGIT; i++)
	{
		// �e�N�X�`�����W�̐ݒ�
		float x = (float)(number % 10);
		g_vertexWkMiss[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		g_vertexWkMiss[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		g_vertexWkMiss[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		g_vertexWkMiss[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		number /= 10;
	}
}