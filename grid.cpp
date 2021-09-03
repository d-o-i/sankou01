//=============================================================================
//
// �^�C�g����ʏ��� [grid.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "grid.h"
#include "input.h"
#include "sound.h"
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexGrid(void);

#ifdef _DEBUG
void SetVertexGrid(void);
#endif

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureGrid = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureUi_NV = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureUi_DE = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureUi_DR = NULL;		// �e�N�X�`���ւ̃|�C���^

#ifdef _DEBUG
LPDIRECT3DTEXTURE9		g_pD3DTextureTest = NULL;		// �e�N�X�`���ւ̃|�C���^
#endif

VERTEX_2D				g_vertexWkGrid[NUM_VERTEX];			// ���_���i�[���[�N
VERTEX_2D				g_vertexWkUi_NV[NUM_VERTEX];			// ���_���i�[���[�N
VERTEX_2D				g_vertexWkUi_DE[NUM_VERTEX];			// ���_���i�[���[�N
VERTEX_2D				g_vertexWkUi_DR[NUM_VERTEX];			// ���_���i�[���[�N

#ifdef _DEBUG
VERTEX_2D				g_vertexWkTest[NUM_VERTEX];			// ���_���i�[���[�N

static D3DXVECTOR2 g_pos;
#endif
int						DrawMusicName = NULL;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitGrid(int type)
{
	if (type == 0)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
			TEXTURE_GRID,						// �t�@�C���̖��O
			&g_pD3DTextureGrid);				// �ǂݍ��ރ������[

		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
			TEXTURE_UI_NOVA,						// �t�@�C���̖��O
			&g_pD3DTextureUi_NV);				// �ǂݍ��ރ������[
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
			TEXTURE_UI_DEEP,						// �t�@�C���̖��O
			&g_pD3DTextureUi_DE);				// �ǂݍ��ރ������[
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
			TEXTURE_UI_DRAM,						// �t�@�C���̖��O
			&g_pD3DTextureUi_DR);				// �ǂݍ��ރ������[

#ifdef _DEBUG
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
			TEXTURE_TEST,						// �t�@�C���̖��O
			&g_pD3DTextureTest);				// �ǂݍ��ރ������[
#endif
	}

	// ���_���̍쐬
	MakeVertexGrid();

#ifdef _DEBUG
	g_pos = D3DXVECTOR2(HIT_POS_X, HIT_POS_Y);
#endif

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitGrid(void)
{
	if (g_pD3DTextureGrid != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureGrid->Release();
		g_pD3DTextureGrid = NULL;
	}
	if (g_pD3DTextureUi_NV != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureUi_NV->Release();
		g_pD3DTextureUi_NV = NULL;
	}
	if (g_pD3DTextureUi_DE != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureUi_DE->Release();
		g_pD3DTextureUi_DE = NULL;
	}
	if (g_pD3DTextureUi_DR != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureUi_DR->Release();
		g_pD3DTextureUi_DR = NULL;
	}
#ifdef _DEBUG
	if (g_pD3DTextureTest != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureTest->Release();
		g_pD3DTextureTest = NULL;
	}
#endif
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGrid(void)
{
#ifdef _DEBUG
	if (GetKeyboardPress(DIK_UP))
	{
		g_pos.y -= 0.5f;
	}
	else if (GetKeyboardPress(DIK_DOWN))
	{
		g_pos.y += 0.5f;
	}

	if (GetKeyboardPress(DIK_LEFT))
	{
		g_pos.x -= 0.5f;
	}
	else if (GetKeyboardPress(DIK_RIGHT))
	{
		g_pos.x += 0.5f;
	}
	SetVertexGrid();
#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGrid(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//	int mno;
//	GetMusic(mno);
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureGrid);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkGrid, sizeof(VERTEX_2D));
	
	if (GetMusic() == BGM_SUPERNOVA)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureUi_NV);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkUi_NV, sizeof(VERTEX_2D));
	}

	if (GetMusic() == BGM_DEEPER)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureUi_DE);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkUi_DE, sizeof(VERTEX_2D));
	}
	if (GetMusic() == BGM_DAYDRAEM)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureUi_DR);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkUi_DR, sizeof(VERTEX_2D));
	}

#ifdef _DEBUG
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureTest);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTest, sizeof(VERTEX_2D));
#endif
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexGrid(void)
{
	// ���_���W�̐ݒ�
	g_vertexWkGrid[0].vtx = D3DXVECTOR3(GRID_POS_X, GRID_POS_Y, 0.0f);
	g_vertexWkGrid[1].vtx = D3DXVECTOR3(GRID_POS_X + GRID_SIZE_X, GRID_POS_Y, 0.0f);
	g_vertexWkGrid[2].vtx = D3DXVECTOR3(GRID_POS_X, GRID_POS_Y + GRID_SIZE_Y, 0.0f);
	g_vertexWkGrid[3].vtx = D3DXVECTOR3(GRID_POS_X + GRID_SIZE_X, GRID_POS_Y + GRID_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkGrid[0].rhw =
	g_vertexWkGrid[1].rhw =
	g_vertexWkGrid[2].rhw =
	g_vertexWkGrid[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkGrid[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkGrid[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkGrid[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkGrid[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkGrid[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkGrid[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkGrid[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkGrid[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_���W�̐ݒ�
	g_vertexWkUi_NV[0].vtx = D3DXVECTOR3(UI_NOVA_POS_X, UI_NOVA_POS_Y, 0.0f);
	g_vertexWkUi_NV[1].vtx = D3DXVECTOR3(UI_NOVA_POS_X + UI_NOVA_SIZE_X, UI_NOVA_POS_Y, 0.0f);
	g_vertexWkUi_NV[2].vtx = D3DXVECTOR3(UI_NOVA_POS_X, UI_NOVA_POS_Y + UI_NOVA_SIZE_Y, 0.0f);
	g_vertexWkUi_NV[3].vtx = D3DXVECTOR3(UI_NOVA_POS_X + UI_NOVA_SIZE_X, UI_NOVA_POS_Y + UI_NOVA_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkUi_NV[0].rhw =
	g_vertexWkUi_NV[1].rhw =
	g_vertexWkUi_NV[2].rhw =
	g_vertexWkUi_NV[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkUi_NV[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkUi_NV[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkUi_NV[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkUi_NV[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkUi_NV[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkUi_NV[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkUi_NV[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkUi_NV[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_���W�̐ݒ�
	g_vertexWkUi_DE[0].vtx = D3DXVECTOR3(UI_DEEP_POS_X, UI_DEEP_POS_Y, 0.0f);
	g_vertexWkUi_DE[1].vtx = D3DXVECTOR3(UI_DEEP_POS_X + UI_DEEP_SIZE_X, UI_DEEP_POS_Y, 0.0f);
	g_vertexWkUi_DE[2].vtx = D3DXVECTOR3(UI_DEEP_POS_X, UI_DEEP_POS_Y + UI_DEEP_SIZE_Y, 0.0f);
	g_vertexWkUi_DE[3].vtx = D3DXVECTOR3(UI_DEEP_POS_X + UI_DEEP_SIZE_X, UI_DEEP_POS_Y + UI_DEEP_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkUi_DE[0].rhw =
	g_vertexWkUi_DE[1].rhw =
	g_vertexWkUi_DE[2].rhw =
	g_vertexWkUi_DE[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkUi_DE[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkUi_DE[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkUi_DE[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkUi_DE[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkUi_DE[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkUi_DE[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkUi_DE[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkUi_DE[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_���W�̐ݒ�
	g_vertexWkUi_DR[0].vtx = D3DXVECTOR3(UI_DEEP_POS_X, UI_DEEP_POS_Y, 0.0f);
	g_vertexWkUi_DR[1].vtx = D3DXVECTOR3(UI_DEEP_POS_X + UI_DEEP_SIZE_X, UI_DEEP_POS_Y, 0.0f);
	g_vertexWkUi_DR[2].vtx = D3DXVECTOR3(UI_DEEP_POS_X, UI_DEEP_POS_Y + UI_DEEP_SIZE_Y, 0.0f);
	g_vertexWkUi_DR[3].vtx = D3DXVECTOR3(UI_DEEP_POS_X + UI_DEEP_SIZE_X, UI_DEEP_POS_Y + UI_DEEP_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkUi_DR[0].rhw =
	g_vertexWkUi_DR[1].rhw =
	g_vertexWkUi_DR[2].rhw =
	g_vertexWkUi_DR[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkUi_DR[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkUi_DR[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkUi_DR[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkUi_DR[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkUi_DR[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkUi_DR[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkUi_DR[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkUi_DR[3].tex = D3DXVECTOR2(1.0f, 1.0f);

#ifdef _DEBUG
	// ���_���W�̐ݒ�
	g_vertexWkTest[0].vtx = D3DXVECTOR3(HIT_POS_X, HIT_POS_Y, 0.0f);
	g_vertexWkTest[1].vtx = D3DXVECTOR3(HIT_POS_X + HIT_SIZE_X, HIT_POS_Y, 0.0f);
	g_vertexWkTest[2].vtx = D3DXVECTOR3(HIT_POS_X, HIT_POS_Y + HIT_SIZE_Y, 0.0f);
	g_vertexWkTest[3].vtx = D3DXVECTOR3(HIT_POS_X + HIT_SIZE_X, HIT_POS_Y + HIT_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkTest[0].rhw =
	g_vertexWkTest[1].rhw =
	g_vertexWkTest[2].rhw =
	g_vertexWkTest[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkTest[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTest[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTest[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTest[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkTest[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkTest[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkTest[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkTest[3].tex = D3DXVECTOR2(1.0f, 1.0f);
#endif

	return S_OK;
}

#ifdef _DEBUG
//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexGrid(void)
{
	// ���_���W�̐ݒ�
	g_vertexWkTest[0].vtx = D3DXVECTOR3(g_pos.x, g_pos.y, 0.0f);
	g_vertexWkTest[1].vtx = D3DXVECTOR3(g_pos.x + HIT_SIZE_X, g_pos.y, 0.0f);
	g_vertexWkTest[2].vtx = D3DXVECTOR3(g_pos.x, g_pos.y + HIT_SIZE_Y, 0.0f);
	g_vertexWkTest[3].vtx = D3DXVECTOR3(g_pos.x + HIT_SIZE_X, g_pos.y + HIT_SIZE_Y, 0.0f);
}

//=============================================================================
// ���_���W�̎擾
//=============================================================================
float GetPosTest(int type)
{
	if (type == 0)
	{
		return g_pos.x;
	}
	else
	{
		return g_pos.y;
	}
}
#endif