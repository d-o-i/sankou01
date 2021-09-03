//=============================================================================
//
// タイトル画面処理 [score.h]
// Author : 
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_SCORE			_T("data/TEXTURE/number16x32.png")			// 読み込むテクスチャファイル名
#define GAME_SCORE_SIZE_X			(20.0f)			// ゲーム中のテクスチャサイズ
#define GAME_SCORE_SIZE_Y			(25.0f)			// ゲーム中のテクスチャサイズ

#define RESULT_SCORE_SIZE_X			(30.0f)			// リザルト中のテクスチャサイズ
#define RESULT_SCORE_SIZE_Y			(50.0f)			// リザルト中のテクスチャサイズ

#define	GAME_SCORE_POS_X			(618.0f)		// ゲーム中のスコア表示位置
#define	GAME_SCORE_POS_Y			(0.0f)		// ゲーム中のスコア表示位

#define RESULT_SCORE_POS_X			(500.0f)		// リザルト中のスコア表示位置
#define RESULT_SCORE_POS_Y			(420.0f)		// リザルト中のスコア表示位置


#define SCORE_DIGIT					(5)				// スコアの桁数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitScore(int type);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);

void AddScore(int add);
void SetVertexScore(void);

#endif
