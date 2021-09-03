//=============================================================================
//
// �X�R�A���� [timer.h]
// Author : 
//
//=============================================================================
#ifndef _TIMER_H_
#define _TIMER_H_

// �}�N����`
#define TEXTURE_GAME_TIMER	_T("data/TEXTURE/number16x32.png")	// �T���v���p�摜
#define TEXTURE_TIMER_SIZE_X	(20.0f)	// �e�N�X�`���T�C�Y
#define TEXTURE_TIMER_SIZE_Y	(50.0f)	// ����
#define TIMER_POS_X			(SCREEN_WIDTH / 2 - TEXTURE_TIMER_SIZE_X / 2)		// �|���S���̏����ʒuX
#define TIMER_POS_Y			(0)		// ����
#define TIMER_MAX			(60)		// �^�C���̍ő�l
#define TIMER_MIN			(0)		// �^�C���̍ŏ��l
#define TIMER_DIGIT			(2)		// ����


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTimer(int type);
void UninitTimer(void);
void UpdateTimer(void);
void DrawTimer(void);

void RedTimer(int red);
int GetTimer(void);

#endif