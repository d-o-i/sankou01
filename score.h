//=============================================================================
//
// �^�C�g����ʏ��� [score.h]
// Author : 
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_SCORE			_T("data/TEXTURE/number16x32.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define GAME_SCORE_SIZE_X			(20.0f)			// �Q�[�����̃e�N�X�`���T�C�Y
#define GAME_SCORE_SIZE_Y			(25.0f)			// �Q�[�����̃e�N�X�`���T�C�Y

#define RESULT_SCORE_SIZE_X			(30.0f)			// ���U���g���̃e�N�X�`���T�C�Y
#define RESULT_SCORE_SIZE_Y			(50.0f)			// ���U���g���̃e�N�X�`���T�C�Y

#define	GAME_SCORE_POS_X			(618.0f)		// �Q�[�����̃X�R�A�\���ʒu
#define	GAME_SCORE_POS_Y			(0.0f)		// �Q�[�����̃X�R�A�\����

#define RESULT_SCORE_POS_X			(500.0f)		// ���U���g���̃X�R�A�\���ʒu
#define RESULT_SCORE_POS_Y			(420.0f)		// ���U���g���̃X�R�A�\���ʒu


#define SCORE_DIGIT					(5)				// �X�R�A�̌���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitScore(int type);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);

void AddScore(int add);
void SetVertexScore(void);

#endif
