//=============================================================================
//
// �^�C�g����ʏ��� [arrow.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "arrow.h"
#include "input.h"
#include "line.h"
#include "star.h"
#include "check.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ARROW_MAX			(STAR_MAX * 2)
#define KEY_MAX				(18)
#define KEY_YOKO			(7)
#define KEY_TATE			(4)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexArrow(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureArrow = NULL;		// �e�N�X�`���ւ̃|�C���^

ARROW					g_Arrow[ARROW_MAX];				// ���C���̍\���̔z��

int						a, b;

int						key[KEY_TATE][KEY_YOKO]
= {DIK_1,DIK_2,DIK_3,DIK_4,DIK_5,DIK_6,DIK_7,
DIK_Q,DIK_W,DIK_E,DIK_R,DIK_T,DIK_Y,DIK_U,
DIK_A,DIK_S,DIK_D,DIK_F,DIK_G,DIK_H,DIK_J,
DIK_Z,DIK_X,DIK_C,DIK_V,DIK_B,DIK_N,DIK_M,
};

D3DXVECTOR2 starpos = D3DXVECTOR2(0.0f, 0.0f);
//=============================================================================
// ����������
//=============================================================================
HRESULT InitArrow(int type)
{
	if (type == 0)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_ARROW,				// �t�@�C���̖��O
			&g_pD3DTextureArrow);		// �ǂݍ��ރ������[
	}

	for (int i = 0; i < ARROW_MAX; i++)
	{
		g_Arrow[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Arrow[i].use = false;
		g_Arrow[i].move = false;
		g_Arrow[i].pos = D3DXVECTOR2(0.0f, 0.0f);
		g_Arrow[i].angle = atan2f(ARROW_SIZE_Y, ARROW_SIZE_X);	// �v���C���[�̊p�x��������

		// ���_���̍쐬
		MakeVertexArrow(i);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitArrow(void)
{
	if (g_pD3DTextureArrow != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureArrow->Release();
		g_pD3DTextureArrow = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateArrow()
{
	for(int i = 0; i < ARROW_MAX; i++)
	{ 
		for (int j = 0; j < STAR_MAX; j++)
		{
			GetStarPos(j) = starpos;
			if (g_Arrow[j].vertexWk[3].vtx.x > starpos.x-3.0f)
			{
				for (int k = 0; k < KEY_MAX; k++)
				{
					if (GetStarPosNo(j) == k)
					{
						switch (k)
						{
						case 0:
							for (int a = 0; a < 2; a++)
							{
								for (int b = 0; b < 2; b++)
								{
									if (GetKeyboardTrigger(key[a][b]))
									{
										ReleaseArrow(j);
									}
								}
							}
							break;
						case 1:
							for (int a = 0; a < 2; a++)
							{
								for (int b = 1; b < 3; b++)
								{
									if (GetKeyboardTrigger(key[a][b]))
									{
										ReleaseArrow(j);
									}
								}
							}
							break;
						case 2:
							for (int a = 0; a < 2; a++)
							{
								for (int b = 2; b < 4; b++)
								{
									if (GetKeyboardTrigger(key[a][b]))
									{
										ReleaseArrow(j);
									}
								}
							}
							break;
						case 3:
							for (int a = 0; a < 2; a++)
							{
								for (int b = 3; b < 5; b++)
								{
									if (GetKeyboardTrigger(key[a][b]))
									{
										ReleaseArrow(j);
									}
								}
							}
							break;
						case 4:
							for (int a = 0; a < 2; a++)
							{
								for (int b = 4; b < 6; b++)
								{
									if (GetKeyboardTrigger(key[a][b]))
									{
										ReleaseArrow(j);
									}
								}
							}
							break;
						case 5:
							for (int a = 0; a < 2; a++)
							{
								for (int b = 5; b < 7; b++)
								{
									if (GetKeyboardTrigger(key[a][b]))
									{
										ReleaseArrow(j);
									}
								}
							}
							break;
						case 6:
							for (int a = 1; a < 3; a++)
							{
								for (int b = 0; b < 2; b++)
								{
									if (GetKeyboardTrigger(key[a][b]))
									{
										ReleaseArrow(j);
									}
								}
							}
							break;
						case 7:
							for (int a = 1; a < 3; a++)
							{
								for (int b = 1; b < 3; b++)
								{
									if (GetKeyboardTrigger(key[a][b]))
									{
										ReleaseArrow(j);
									}
								}
							}
							break;
						case 8:
							for (int a = 1; a < 3; a++)
							{
								for (int b = 2; b < 4; b++)
								{
									if (GetKeyboardTrigger(key[a][b]))
									{
										ReleaseArrow(j);
									}
								}
							}
							break;
						case 9:
							for (int a = 1; a < 3; a++)
							{
								for (int b = 3; b < 5; b++)
								{
									if (GetKeyboardTrigger(key[a][b]))
									{
										ReleaseArrow(j);
									}
								}
							}
							break;
						case 10:
							for (int a = 1; a < 3; a++)
							{
								for (int b = 4; b < 6; b++)
								{
									if (GetKeyboardTrigger(key[a][b]))
									{
										ReleaseArrow(j);
									}
								}
							}
							break;
						case 11:
							for (int a = 1; a < 3; a++)
							{
								for (int b = 5; b < 7; b++)
								{
									if (GetKeyboardTrigger(key[a][b]))
									{
										ReleaseArrow(j);
									}
								}
							}
							break;
						case 12:
							for (int a = 2; a < 4; a++)
							{
								for (int b = 0; b < 2; b++)
								{
									if (GetKeyboardTrigger(key[a][b]))
									{
										ReleaseArrow(j);
									}
								}
							}
							break;
						case 13:
							for (int a = 2; a < 4; a++)
							{
								for (int b = 1; b < 3; b++)
								{
									if (GetKeyboardTrigger(key[a][b]))
									{
										ReleaseArrow(j);
									}
								}
							}
							break;
						case 14:
							for (int a = 2; a < 4; a++)
							{
								for (int b = 2; b < 4; b++)
								{
									if (GetKeyboardTrigger(key[a][b]))
									{
										ReleaseArrow(j);
									}
								}
							}
							break;
						case 15:
							for (int a = 2; a < 4; a++)
							{
								for (int b = 3; b < 5; b++)
								{
									if (GetKeyboardTrigger(key[a][b]))
									{
										ReleaseArrow(j);
									}
								}
							}
							break;
						case 16:
							for (int a = 2; a < 4; a++)
							{
								for (int b = 4; b < 6; b++)
								{
									if (GetKeyboardTrigger(key[a][b]))
									{
										ReleaseArrow(j);
									}
								}
							}
							break;
						case 17:
							for (int a = 2; a < 4; a++)
							{
								for (int b = 5; b < 7; b++)
								{
									if (GetKeyboardTrigger(key[a][b]))
									{
										ReleaseArrow(j);
									}
								}
							}
							break;
						}
					}
					//else if (GetStarPosNo(j) == 1)
					//{
					//	for (int a = 0; a < 2; a++)
					//	{
					//		for (int b = 1; b < 2; b++)
					//		{
					//			if (GetKeyboardTrigger(key[a][b]))
					//			{
					//			}
					//		}
					//	}
					//}
				}
			}
		}
		if (g_Arrow[i].move)
		{
			if (i > ARROW_MAX / 2 - 1)
			{
				if (g_Arrow[i].vertexWk[3].vtx.x + CHECKRANGE > g_Arrow[i - ARROW_MAX / 2].vertexWk[3].vtx.x - CHECKRANGE
					&& g_Arrow[i - ARROW_MAX / 2].vertexWk[3].vtx.x + CHECKRANGE > g_Arrow[i].vertexWk[3].vtx.x - CHECKRANGE
					&& g_Arrow[i].vertexWk[3].vtx.y + CHECKRANGE > g_Arrow[i - ARROW_MAX / 2].vertexWk[3].vtx.y - CHECKRANGE
					&& g_Arrow[i - ARROW_MAX / 2].vertexWk[3].vtx.y + CHECKRANGE > g_Arrow[i].vertexWk[3].vtx.y - CHECKRANGE)
				{
					if (g_Arrow[i].use)
					{
						MissScore();	
						g_Arrow[i].use = false;
					}
					g_Arrow[i].move = false;
					g_Arrow[i % STAR_MAX].use = false;
				}
			}
			else
			{
				if (g_Arrow[i].vertexWk[3].vtx.x + CHECKRANGE > g_Arrow[i + ARROW_MAX / 2].vertexWk[3].vtx.x - CHECKRANGE
					&& g_Arrow[i + ARROW_MAX / 2].vertexWk[3].vtx.x + CHECKRANGE > g_Arrow[i].vertexWk[3].vtx.x - CHECKRANGE
					&& g_Arrow[i].vertexWk[3].vtx.y + CHECKRANGE > g_Arrow[i + ARROW_MAX / 2].vertexWk[3].vtx.y - CHECKRANGE
					&& g_Arrow[i + ARROW_MAX / 2].vertexWk[3].vtx.y + CHECKRANGE > g_Arrow[i].vertexWk[3].vtx.y - CHECKRANGE)
				{
					if (g_Arrow[i].use)
					{
						MissScore();
						g_Arrow[i].use = false;
					}
					g_Arrow[i].move = false;
					g_Arrow[i + STAR_MAX].use = false;
				}
			}

			if (g_Arrow[i].rot.z == SHITA)
			{
				g_Arrow[i].vertexWk[0].vtx.y += HIRASPEED;
				g_Arrow[i].vertexWk[1].vtx.y += HIRASPEED;
				g_Arrow[i].vertexWk[2].vtx.y += HIRASPEED;
				g_Arrow[i].vertexWk[3].vtx.y += HIRASPEED;
			}
			if (g_Arrow[i].rot.z == HIDARI)
			{
				g_Arrow[i].vertexWk[0].vtx.x -= HIRASPEED;
				g_Arrow[i].vertexWk[1].vtx.x -= HIRASPEED;
				g_Arrow[i].vertexWk[2].vtx.x -= HIRASPEED;
				g_Arrow[i].vertexWk[3].vtx.x -= HIRASPEED;
			}
			if (g_Arrow[i].rot.z == HIDARISHITA)
			{
				g_Arrow[i].vertexWk[0].vtx.y += NANAMESPEED;
				g_Arrow[i].vertexWk[1].vtx.y += NANAMESPEED;
				g_Arrow[i].vertexWk[2].vtx.y += NANAMESPEED;
				g_Arrow[i].vertexWk[3].vtx.y += NANAMESPEED;
				g_Arrow[i].vertexWk[0].vtx.x -= NANAMESPEED;
				g_Arrow[i].vertexWk[1].vtx.x -= NANAMESPEED;
				g_Arrow[i].vertexWk[2].vtx.x -= NANAMESPEED;
				g_Arrow[i].vertexWk[3].vtx.x -= NANAMESPEED;
			}
			if (g_Arrow[i].rot.z == HIDARIUE)
			{
				g_Arrow[i].vertexWk[0].vtx.y -= NANAMESPEED;
				g_Arrow[i].vertexWk[1].vtx.y -= NANAMESPEED;
				g_Arrow[i].vertexWk[2].vtx.y -= NANAMESPEED;
				g_Arrow[i].vertexWk[3].vtx.y -= NANAMESPEED;
				g_Arrow[i].vertexWk[0].vtx.x -= NANAMESPEED;
				g_Arrow[i].vertexWk[1].vtx.x -= NANAMESPEED;
				g_Arrow[i].vertexWk[2].vtx.x -= NANAMESPEED;
				g_Arrow[i].vertexWk[3].vtx.x -= NANAMESPEED;
			}
			if (g_Arrow[i].rot.z == UE)
			{
				g_Arrow[i].vertexWk[0].vtx.y -= HIRASPEED;
				g_Arrow[i].vertexWk[1].vtx.y -= HIRASPEED;
				g_Arrow[i].vertexWk[2].vtx.y -= HIRASPEED;
				g_Arrow[i].vertexWk[3].vtx.y -= HIRASPEED;
			}
			if (g_Arrow[i].rot.z == MIGIUE)
			{
				g_Arrow[i].vertexWk[0].vtx.y -= NANAMESPEED;
				g_Arrow[i].vertexWk[1].vtx.y -= NANAMESPEED;
				g_Arrow[i].vertexWk[2].vtx.y -= NANAMESPEED;
				g_Arrow[i].vertexWk[3].vtx.y -= NANAMESPEED;
				g_Arrow[i].vertexWk[0].vtx.x += NANAMESPEED;
				g_Arrow[i].vertexWk[1].vtx.x += NANAMESPEED;
				g_Arrow[i].vertexWk[2].vtx.x += NANAMESPEED;
				g_Arrow[i].vertexWk[3].vtx.x += NANAMESPEED;
			}
			if (g_Arrow[i].rot.z == MIGI)
			{
				g_Arrow[i].vertexWk[0].vtx.x += HIRASPEED;
				g_Arrow[i].vertexWk[1].vtx.x += HIRASPEED;
				g_Arrow[i].vertexWk[2].vtx.x += HIRASPEED;
				g_Arrow[i].vertexWk[3].vtx.x += HIRASPEED;
			}
			if (g_Arrow[i].rot.z == MIGISHITA)
			{
				g_Arrow[i].vertexWk[0].vtx.y += NANAMESPEED;
				g_Arrow[i].vertexWk[1].vtx.y += NANAMESPEED;
				g_Arrow[i].vertexWk[2].vtx.y += NANAMESPEED;
				g_Arrow[i].vertexWk[3].vtx.y += NANAMESPEED;
				g_Arrow[i].vertexWk[0].vtx.x += NANAMESPEED;
				g_Arrow[i].vertexWk[1].vtx.x += NANAMESPEED;
				g_Arrow[i].vertexWk[2].vtx.x += NANAMESPEED;
				g_Arrow[i].vertexWk[3].vtx.x += NANAMESPEED;
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawArrow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < ARROW_MAX; i++)
	{
		if (g_Arrow[i].use)
		{
			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTextureArrow);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_Arrow[i].vertexWk, sizeof(VERTEX_2D));
		}
	}
}
//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexArrow(int no)
{
	// ���_���W�̐ݒ�
	g_Arrow[no].vertexWk[0].vtx = D3DXVECTOR3(g_Arrow[no].pos.x, g_Arrow[no].pos.y, 0.0f);
	g_Arrow[no].vertexWk[1].vtx = D3DXVECTOR3(g_Arrow[no].pos.x + ARROW_SIZE_X, g_Arrow[no].pos.y, 0.0f);
	g_Arrow[no].vertexWk[2].vtx = D3DXVECTOR3(g_Arrow[no].pos.x, g_Arrow[no].pos.y + ARROW_SIZE_Y, 0.0f);
	g_Arrow[no].vertexWk[3].vtx = D3DXVECTOR3(g_Arrow[no].pos.x + ARROW_SIZE_X, g_Arrow[no].pos.y + ARROW_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_Arrow[no].vertexWk[0].rhw =
	g_Arrow[no].vertexWk[1].rhw =
	g_Arrow[no].vertexWk[2].rhw =
	g_Arrow[no].vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_Arrow[no].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_Arrow[no].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_Arrow[no].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_Arrow[no].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_Arrow[no].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_Arrow[no].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_Arrow[no].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_Arrow[no].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �A���[�̐ݒ�
//=============================================================================
void SetArrow(int no, D3DXVECTOR2 pos)
{
	g_Arrow[no].use = true;
	g_Arrow[no].move = true;

	float rot;

	if ((ARROW_MAX / 2) - 1 < no)
	{
		rot = GetRot(no - ARROW_MAX / 2);
	}
	else
	{
		rot = GetRot(no);
	}

	if (rot == LEFTDOWN)
	{
		if (ARROW_MAX / 2 - 1 < no)
		{
			g_Arrow[no].rot.z = SHITA;
		}
		else
		{
			g_Arrow[no].rot.z = HIDARI;
		}
	}
	else if (rot == LEFT)
	{
		if (ARROW_MAX / 2 - 1 < no)
		{
			g_Arrow[no].rot.z = HIDARISHITA;
		}
		else
		{
			g_Arrow[no].rot.z = HIDARIUE;
		}
	}
	else if (rot == LEFTUP)
	{
		if (ARROW_MAX / 2 - 1 < no)
		{
			g_Arrow[no].rot.z = HIDARI;
		}
		else
		{
			g_Arrow[no].rot.z = UE;
		}
	}
	else if (rot == UP)
	{
		if (ARROW_MAX / 2 - 1 < no)
		{
			g_Arrow[no].rot.z = HIDARIUE;
		}
		else
		{
			g_Arrow[no].rot.z = MIGIUE;
		}
	}
	else if (rot == RIGHTUP)
	{
		if (ARROW_MAX / 2 - 1 < no)
		{
			g_Arrow[no].rot.z = UE;
		}
		else
		{
			g_Arrow[no].rot.z = MIGI;
		}

	}
	else if (rot == RIGHT)
	{
		if (ARROW_MAX / 2 - 1 < no)
		{
			g_Arrow[no].rot.z = MIGIUE;
		}
		else
		{
			g_Arrow[no].rot.z = MIGISHITA;
		}
	}
	else if (rot == RIGHTDOWN)
	{
		if (ARROW_MAX / 2 - 1 < no)
		{
			g_Arrow[no].rot.z = MIGI;
		}
		else
		{
			g_Arrow[no].rot.z = SHITA;
		}
	}
	else if (rot == DOWN)
	{
		if (ARROW_MAX / 2 - 1 < no)
		{
			g_Arrow[no].rot.z = MIGISHITA;
		}
		else
		{
			g_Arrow[no].rot.z = HIDARISHITA;
		}
	}

	// ���_���W�̐ݒ�
	g_Arrow[no].vertexWk[0].vtx.x = pos.x - cosf(g_Arrow[no].angle + g_Arrow[no].rot.z) * ARROW_SIZE_X;
	g_Arrow[no].vertexWk[0].vtx.y = pos.y - sinf(g_Arrow[no].angle + g_Arrow[no].rot.z) * ARROW_SIZE_Y;
	g_Arrow[no].vertexWk[0].vtx.z = 0.0f;

	g_Arrow[no].vertexWk[1].vtx.x = pos.x + cosf(g_Arrow[no].angle - g_Arrow[no].rot.z) * ARROW_SIZE_X;
	g_Arrow[no].vertexWk[1].vtx.y = pos.y - sinf(g_Arrow[no].angle - g_Arrow[no].rot.z) * ARROW_SIZE_Y;
	g_Arrow[no].vertexWk[1].vtx.z = 0.0f;

	g_Arrow[no].vertexWk[2].vtx.x = pos.x - cosf(g_Arrow[no].angle - g_Arrow[no].rot.z) * ARROW_SIZE_X;
	g_Arrow[no].vertexWk[2].vtx.y = pos.y + sinf(g_Arrow[no].angle - g_Arrow[no].rot.z) * ARROW_SIZE_Y;
	g_Arrow[no].vertexWk[2].vtx.z = 0.0f;

	g_Arrow[no].vertexWk[3].vtx.x = pos.x + cosf(g_Arrow[no].angle + g_Arrow[no].rot.z) * ARROW_SIZE_X;
	g_Arrow[no].vertexWk[3].vtx.y = pos.y + sinf(g_Arrow[no].angle + g_Arrow[no].rot.z) * ARROW_SIZE_Y;
	g_Arrow[no].vertexWk[3].vtx.z = 0.0f;

	if (g_Arrow[no].rot.z == SHITA)
	{
		g_Arrow[no].vertexWk[0].vtx.y -= HIRA;
		g_Arrow[no].vertexWk[1].vtx.y -= HIRA;
		g_Arrow[no].vertexWk[2].vtx.y -= HIRA;
		g_Arrow[no].vertexWk[3].vtx.y -= HIRA;
	}

	if (g_Arrow[no].rot.z == HIDARI)
	{
		g_Arrow[no].vertexWk[0].vtx.x += HIRA;
		g_Arrow[no].vertexWk[1].vtx.x += HIRA;
		g_Arrow[no].vertexWk[2].vtx.x += HIRA;
		g_Arrow[no].vertexWk[3].vtx.x += HIRA;
	}
	
	if (g_Arrow[no].rot.z == HIDARISHITA)
	{
		g_Arrow[no].vertexWk[0].vtx.y -= NANAME;
		g_Arrow[no].vertexWk[1].vtx.y -= NANAME;
		g_Arrow[no].vertexWk[2].vtx.y -= NANAME;
		g_Arrow[no].vertexWk[3].vtx.y -= NANAME;
		g_Arrow[no].vertexWk[0].vtx.x += NANAME;
		g_Arrow[no].vertexWk[1].vtx.x += NANAME;
		g_Arrow[no].vertexWk[2].vtx.x += NANAME;
		g_Arrow[no].vertexWk[3].vtx.x += NANAME;
	}

	if (g_Arrow[no].rot.z == HIDARIUE)
	{
		g_Arrow[no].vertexWk[0].vtx.y += NANAME;
		g_Arrow[no].vertexWk[1].vtx.y += NANAME;
		g_Arrow[no].vertexWk[2].vtx.y += NANAME;
		g_Arrow[no].vertexWk[3].vtx.y += NANAME;
		g_Arrow[no].vertexWk[0].vtx.x += NANAME;
		g_Arrow[no].vertexWk[1].vtx.x += NANAME;
		g_Arrow[no].vertexWk[2].vtx.x += NANAME;
		g_Arrow[no].vertexWk[3].vtx.x += NANAME;
	}
	
	if (g_Arrow[no].rot.z == UE)
	{
		g_Arrow[no].vertexWk[0].vtx.y += HIRA;
		g_Arrow[no].vertexWk[1].vtx.y += HIRA;
		g_Arrow[no].vertexWk[2].vtx.y += HIRA;
		g_Arrow[no].vertexWk[3].vtx.y += HIRA;
	}

	if (g_Arrow[no].rot.z == MIGIUE)
	{
		g_Arrow[no].vertexWk[0].vtx.y += NANAME;
		g_Arrow[no].vertexWk[1].vtx.y += NANAME;
		g_Arrow[no].vertexWk[2].vtx.y += NANAME;
		g_Arrow[no].vertexWk[3].vtx.y += NANAME;
		g_Arrow[no].vertexWk[0].vtx.x -= NANAME;
		g_Arrow[no].vertexWk[1].vtx.x -= NANAME;
		g_Arrow[no].vertexWk[2].vtx.x -= NANAME;
		g_Arrow[no].vertexWk[3].vtx.x -= NANAME;
	}
	
	if (g_Arrow[no].rot.z == MIGI)
	{
		g_Arrow[no].vertexWk[0].vtx.x -= HIRA;
		g_Arrow[no].vertexWk[1].vtx.x -= HIRA;
		g_Arrow[no].vertexWk[2].vtx.x -= HIRA;
		g_Arrow[no].vertexWk[3].vtx.x -= HIRA;
	}
			
	if (g_Arrow[no].rot.z == MIGISHITA)
	{
		g_Arrow[no].vertexWk[0].vtx.y -= NANAME;
		g_Arrow[no].vertexWk[1].vtx.y -= NANAME;
		g_Arrow[no].vertexWk[2].vtx.y -= NANAME;
		g_Arrow[no].vertexWk[3].vtx.y -= NANAME;
		g_Arrow[no].vertexWk[0].vtx.x -= NANAME;
		g_Arrow[no].vertexWk[1].vtx.x -= NANAME;
		g_Arrow[no].vertexWk[2].vtx.x -= NANAME;
		g_Arrow[no].vertexWk[3].vtx.x -= NANAME;
	}
}

//=============================================================================
// �A���[�̉��
//=============================================================================
void ReleaseArrow(int no)
{
	g_Arrow[no].use = false;
	g_Arrow[no + STAR_MAX].use = false;
}

//=============================================================================
// g_Arrow[no].move�̏�Ԏ擾�֐�
//=============================================================================
bool GetMove(int no)
{
	return g_Arrow[no].move;
}

//=============================================================================
// g_Arrow[no].use�̏�Ԏ擾�֐�
//=============================================================================
bool GetArrow(int no)
{
	return g_Arrow[no].use;
}


//=============================================================================
// Arrow�̒��_�擾
//=============================================================================
D3DXVECTOR2 GetArrowPos(int no)
{
	D3DXVECTOR2 Arrow = D3DXVECTOR2(g_Arrow[no].vertexWk[3].vtx.x, g_Arrow[no].vertexWk[3].vtx.y);
	return Arrow;
}
