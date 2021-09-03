//=============================================================================
//
// �X�R�A���� [timer.cpp]
//
//=============================================================================
#include "main.h"
#include "timer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexTimer(void);
void SetTextureTimer(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureTimer = NULL;		// �e�N�X�`���ւ̃|���S��
VERTEX_2D				g_vertexWkTimer[TIMER_DIGIT][NUM_VERTEX];	// ���_���i�[���[�N

D3DXVECTOR3				g_posTimer;						// �|���S���̈ړ���

int						g_nTimer;						// �c�莞��
int						countTime;						// �J�E���g�_�E������

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTimer(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_TIMER,				// �t�@�C���̖��O
			&g_pD3DTextureTimer);				// �ǂݍ��ރ������̃|�C���^
	}

	g_posTimer = D3DXVECTOR3((float)TIMER_POS_X, (float)TIMER_POS_Y, 0.0f);
	g_nTimer = TIMER_MAX;

	// ���_���̍쐬
	MakeVertexTimer();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTimer(void)
{
	if (g_pD3DTextureTimer != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureTimer->Release();
		g_pD3DTextureTimer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTimer(void)
{
	// ���t���[�����s����鏈�����L�q����
	SetTextureTimer();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureTimer);

	// �X�R�A
	for (int i = 0; i < TIMER_DIGIT; i++)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTimer[i], sizeof(VERTEX_2D));
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexTimer(void)
{
	int i;
	float habaX = TEXTURE_TIMER_SIZE_X;	// �����̉���

	// ��������������
	for (i = 0; i < TIMER_DIGIT; i++)
	{
		// ���_���W�̐ݒ�
		g_vertexWkTimer[i][0].vtx.x = -habaX * i + g_posTimer.x;
		g_vertexWkTimer[i][0].vtx.y = g_posTimer.y;
		g_vertexWkTimer[i][0].vtx.z = 0.0f;
		g_vertexWkTimer[i][1].vtx.x = -habaX * i + g_posTimer.x + TEXTURE_TIMER_SIZE_X;
		g_vertexWkTimer[i][1].vtx.y = g_posTimer.y;
		g_vertexWkTimer[i][1].vtx.z = 0.0f;
		g_vertexWkTimer[i][2].vtx.x = -habaX * i + g_posTimer.x;
		g_vertexWkTimer[i][2].vtx.y = g_posTimer.y + TEXTURE_TIMER_SIZE_Y;
		g_vertexWkTimer[i][2].vtx.z = 0.0f;
		g_vertexWkTimer[i][3].vtx.x = -habaX * i + g_posTimer.x + TEXTURE_TIMER_SIZE_X;
		g_vertexWkTimer[i][3].vtx.y = g_posTimer.y + TEXTURE_TIMER_SIZE_Y;
		g_vertexWkTimer[i][3].vtx.z = 0.0f;

		// rhw�̐ݒ�
		g_vertexWkTimer[i][0].rhw =
		g_vertexWkTimer[i][1].rhw =
		g_vertexWkTimer[i][2].rhw =
		g_vertexWkTimer[i][3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		g_vertexWkTimer[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkTimer[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkTimer[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkTimer[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		g_vertexWkTimer[i][0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_vertexWkTimer[i][1].tex = D3DXVECTOR2(1.0f, 0.0f);
		g_vertexWkTimer[i][2].tex = D3DXVECTOR2(0.0f, 1.0f);
		g_vertexWkTimer[i][3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	return S_OK;
}
//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetTextureTimer(void)
{
	int i;
	int number = g_nTimer;

	for (i = 0; i < TIMER_DIGIT; i++)
	{
		// �e�N�X�`�����W�̐ݒ�
		float x = (float)(number % 10);
		g_vertexWkTimer[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		g_vertexWkTimer[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		g_vertexWkTimer[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		g_vertexWkTimer[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		number /= 10;
	}
}
//=============================================================================
// HP�f�[�^���Z�b�g����
// ����:add :�ǉ�����_���B�}�C�i�X���\�A�������ȂǂɁB
//=============================================================================
void RedTimer(int red)
{
	g_nTimer = TIMER_MAX - red;

	if (g_nTimer < 0)
	{
		g_nTimer = TIMER_MIN;
	}
}

//=============================================================================
// �^�C���擾�֐�
//=============================================================================
int GetTimer(void)
{
	return g_nTimer;
}