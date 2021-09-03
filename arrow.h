//=============================================================================
//
// �^�C�g����ʏ��� [arrow.h]
// Author : 
//
//=============================================================================
#ifndef _ARROW_H_
#define _ARROW_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_ARROW		("data/TEXTURE/arrow.png")			// �ǂݍ��ރe�N�X�`���t�@�C����

#define	ARROW_POS_X			(0.0f)								// �^�C�g���̕\���ʒu
#define	ARROW_POS_Y			(0.0f)								// �^�C�g���̕\���ʒu
#define	ARROW_SIZE_X		(50.0f)							// �^�C�g���̕�
#define	ARROW_SIZE_Y		(50.0f)							// �^�C�g���̍���
#define MIGISHITA			(D3DX_PI * 0.0f)
#define SHITA				(D3DX_PI * 0.25f)
#define HIDARISHITA			(D3DX_PI * 0.5f)
#define HIDARI				(D3DX_PI * 0.75f)
#define HIDARIUE			(D3DX_PI * 1.0f)
#define UE					(D3DX_PI * 1.25f)
#define MIGIUE				(D3DX_PI * 1.5f)
#define MIGI				(D3DX_PI * 1.75f)
#define HIRA				(300.0f)
#define NANAME				(200.0f)
#define HIRASPEED			(HIRA/100.0f)
#define NANAMESPEED			(NANAME/100.0f)
#define CHECKRANGE			(HIRASPEED/3.0f)

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
typedef struct	// ���C���\����
{
	bool			use;						// true:�g�p false:���g�p
	bool			move;
	D3DXVECTOR2		pos;						// �ʒu
	D3DXVECTOR3		rot;						// �ʒu
	float			angle;						// �p�x
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N
} ARROW;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitArrow(int type);
void UninitArrow(void);
void UpdateArrow(void);
void DrawArrow(void);

void SetArrow(int no, D3DXVECTOR2 pos);
void ReleaseArrow(int no);

bool GetMove(int no);
bool GetArrow(int no);
D3DXVECTOR2 GetArrowPos(int no);



#endif