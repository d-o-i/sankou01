//=============================================================================
//
// �^�C�g����ʏ��� [line.h]
// Author : 
//
//=============================================================================
#ifndef _LINE_H_
#define _LINE_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_LINE		("data/TEXTURE/line.png")			// �ǂݍ��ރe�N�X�`���t�@�C����

#define	LINE_POS_X			(0.0f)								// �^�C�g���̕\���ʒu
#define	LINE_POS_Y			(0.0f)								// �^�C�g���̕\���ʒu
#define	LINE_SIZE_X			(480.0f / 2)						// �^�C�g���̕�
#define	LINE_SIZE_Y			(480.0f / 2)						// �^�C�g���̍���
#define LEFTDOWN			(D3DX_PI * 0.0f)
#define LEFT				(D3DX_PI * 0.25f)
#define LEFTUP				(D3DX_PI * 0.5f)
#define UP					(D3DX_PI * 0.75f)
#define RIGHTUP				(D3DX_PI * 1.0f)
#define RIGHT				(D3DX_PI * 1.25f)
#define RIGHTDOWN			(D3DX_PI * 1.5f)
#define DOWN				(D3DX_PI * 1.75f)
#define LD					(153.0f)
//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// ���C���\����
{
	bool			use;						// true:�g�p false:���g�p
	float			rot;						// ��]
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N
} LINE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitLine(int type);
void UninitLine(void);
void UpdateLine(void);
void DrawLine(void);

void SetLine(int no, D3DXVECTOR2 pos);
float GetRot(int no);
#endif