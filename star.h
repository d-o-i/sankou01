//=============================================================================
//
// �^�C�g����ʏ��� [star.h]
// Author : 
//
//=============================================================================
#ifndef _STAR_H_
#define _STAR_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_STAR			("data/TEXTURE/cross_star.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define STAR_MAX			(20)

#define	STAR_POS_X			(65.0f)								// �^�C�g���̕\���ʒu
#define	STAR_POS_Y			(100.0f)							// �^�C�g���̕\���ʒu

#define STAR_SPACE_X		(100.0f)
#define STAR_SPACE_Y		(145.0f)

#define	STAR_SIZE_X		(50.0f / 2)								// �^�C�g���̕�
#define	STAR_SIZE_Y		(50.0f / 2)								// �^�C�g���̍���

//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �X�^�[�\����
{
	bool			use;						// true:�g�p false:���g�p
	int				no;
	D3DXVECTOR2		pos;						// �ʒu
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N
} STAR;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitStar(int type);
void UninitStar(void);
void UpdateStar(void);
void DrawStar(void);

bool GetStar(int no);
int GetStarPosNo(int no);
D3DXVECTOR2 GetStarPos(int no);

void SetStar(int pos);

#endif