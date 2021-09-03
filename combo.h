//=============================================================================
//
// タイトル画面処理 [combo.h]
// Author : 
//
//=============================================================================
#ifndef _COMBO_H_
#define _COMBO_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_COMBO				_T("data/TEXTURE/number16x32.png")					// 読み込むテクスチャファイル名
#define	TEXTURE_RESULT_SUPERNOVA_JACKET	_T("data/TEXTURE/result super nova jake.png")		// 読み込むテクスチャファイル名
#define	TEXTURE_RESULT_SUPERNOVA_LOGO		_T("data/TEXTURE/result super nova logo.png")		// 読み込むテクスチャファイル名
#define	TEXTURE_RESULT_DEEPER_JACKET		_T("data/TEXTURE/result deeper jake.png")			// 読み込むテクスチャファイル名
#define	TEXTURE_RESULT_DEEPER_LOGO			_T("data/TEXTURE/result deeper logo.png")			// 読み込むテクスチャファイル名
#define	TEXTURE_RESULT_DAYDREAM_JACKET		_T("data/TEXTURE/result daydream jake.png")			// 読み込むテクスチャファイル名
#define	TEXTURE_RESULT_DAYDREAM_LOGO		_T("data/TEXTURE/result daydream logo.png")			// 読み込むテクスチャファイル名

#define COMBO_SIZE_X				(30.0f)			// コンボ判定のテクスチャサイズ
#define COMBO_SIZE_Y				(40.0f)			// コンボ判定のテクスチャサイズ

#define COMBO_JUST_POS_X			(500.0f)		// ジャスト判定表示位置
#define COMBO_JUST_POS_Y			(165.0f)		// ジャスト判定表示位置

#define COMBO_GOOD_POS_X			(540.0f)		// グッド判定表示位置
#define COMBO_GOOD_POS_Y			(250.0f)		// グッド判定表示位置

#define COMBO_MISS_POS_X			(580.0f)		// ミス判定表示位置
#define COMBO_MISS_POS_Y			(335.0f)		// ミス判定表示位置

#define COMBO_JACKET_POS_X			(50.0f)
#define COMBO_JACKET_POS_Y			(200.0f)
#define COMBO_JACKET_SIZE_X			(150.0f)
#define COMBO_JACKET_SIZE_Y			(150.0f)

#define COMBO_LOGO_POS_X			(50.0f)
#define COMBO_LOGO_POS_Y			(200.0f)
#define COMBO_LOGO_SIZE_X			(150.0f)
#define COMBO_LOGO_SIZE_Y			(60.0f)

#define COMBO_DIGIT					(3)				// スコアの桁数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitCombo(int type);
void UninitCombo(void);
void UpdateCombo(void);
void DrawCombo(void);

#endif
