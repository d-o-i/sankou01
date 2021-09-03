//=============================================================================
//
// スコア処理 [timer.h]
// Author : 
//
//=============================================================================
#ifndef _TIMER_H_
#define _TIMER_H_

// マクロ定義
#define TEXTURE_GAME_TIMER	_T("data/TEXTURE/number16x32.png")	// サンプル用画像
#define TEXTURE_TIMER_SIZE_X	(20.0f)	// テクスチャサイズ
#define TEXTURE_TIMER_SIZE_Y	(50.0f)	// 同上
#define TIMER_POS_X			(SCREEN_WIDTH / 2 - TEXTURE_TIMER_SIZE_X / 2)		// ポリゴンの初期位置X
#define TIMER_POS_Y			(0)		// 同上
#define TIMER_MAX			(60)		// タイムの最大値
#define TIMER_MIN			(0)		// タイムの最小値
#define TIMER_DIGIT			(2)		// 桁数


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTimer(int type);
void UninitTimer(void);
void UpdateTimer(void);
void DrawTimer(void);

void RedTimer(int red);
int GetTimer(void);

#endif