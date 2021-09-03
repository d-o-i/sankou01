//=============================================================================
//
// �^�C�g����ʏ��� [combo.h]
// Author : 
//
//=============================================================================
#ifndef _COMBO_H_
#define _COMBO_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_COMBO				_T("data/TEXTURE/number16x32.png")					// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RESULT_SUPERNOVA_JACKET	_T("data/TEXTURE/result super nova jake.png")		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RESULT_SUPERNOVA_LOGO		_T("data/TEXTURE/result super nova logo.png")		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RESULT_DEEPER_JACKET		_T("data/TEXTURE/result deeper jake.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RESULT_DEEPER_LOGO			_T("data/TEXTURE/result deeper logo.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RESULT_DAYDREAM_JACKET		_T("data/TEXTURE/result daydream jake.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RESULT_DAYDREAM_LOGO		_T("data/TEXTURE/result daydream logo.png")			// �ǂݍ��ރe�N�X�`���t�@�C����

#define COMBO_SIZE_X				(30.0f)			// �R���{����̃e�N�X�`���T�C�Y
#define COMBO_SIZE_Y				(40.0f)			// �R���{����̃e�N�X�`���T�C�Y

#define COMBO_JUST_POS_X			(500.0f)		// �W���X�g����\���ʒu
#define COMBO_JUST_POS_Y			(165.0f)		// �W���X�g����\���ʒu

#define COMBO_GOOD_POS_X			(540.0f)		// �O�b�h����\���ʒu
#define COMBO_GOOD_POS_Y			(250.0f)		// �O�b�h����\���ʒu

#define COMBO_MISS_POS_X			(580.0f)		// �~�X����\���ʒu
#define COMBO_MISS_POS_Y			(335.0f)		// �~�X����\���ʒu

#define COMBO_JACKET_POS_X			(50.0f)
#define COMBO_JACKET_POS_Y			(200.0f)
#define COMBO_JACKET_SIZE_X			(150.0f)
#define COMBO_JACKET_SIZE_Y			(150.0f)

#define COMBO_LOGO_POS_X			(50.0f)
#define COMBO_LOGO_POS_Y			(200.0f)
#define COMBO_LOGO_SIZE_X			(150.0f)
#define COMBO_LOGO_SIZE_Y			(60.0f)

#define COMBO_DIGIT					(3)				// �X�R�A�̌���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitCombo(int type);
void UninitCombo(void);
void UpdateCombo(void);
void DrawCombo(void);

#endif
