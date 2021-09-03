//=============================================================================
//
// ���U���g��ʏ��� [result.h]
// Author : 
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

//*****************************************************************************
// �}�N����`
//****************************************************************************
#define NUM_RESULT				(2)						// �|���S����

#define TEXTURE_RESULT_BG				("data/TEXTURE/resultbg.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_RESULT_CLEAR			("data/TEXTURE/clear.png")				// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RESULT_GAMEOVER			("data/TEXTURE/gameover.png")			// �ǂݍ��ރe�N�X�`���t�@�C����

#define	RESULT_BG_POS_X			(0)							// ���U���g�w�i�̕\���ʒu
#define	RESULT_BG_POS_Y			(0)							// ���U���g�w�i�̕\���ʒu
#define	RESULT_BG_SIZE_X		(640)						// ���U���g�w�i�̕�
#define	RESULT_BG_SIZE_Y		(480)						// ���U���g�w�i�̍���

#define	RESULT_POS_X			(20)						// ���U���g�̕\���ʒu
#define	RESULT_POS_Y			(75)						// ���U���g�̕\���ʒu
#define	RESULT_SIZE_X			(300)						// ���U���g�̕�
#define	RESULT_SIZE_Y			(70)						// ���U���g�̍���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitResult(int type);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);

void SetTextureNo(int no);

#endif
