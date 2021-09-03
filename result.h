//=============================================================================
//
// リザルト画面処理 [result.h]
// Author : 
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

//*****************************************************************************
// マクロ定義
//****************************************************************************
#define NUM_RESULT				(2)						// ポリゴン数

#define TEXTURE_RESULT_BG				("data/TEXTURE/resultbg.png")			// 読み込むテクスチャファイル名
#define TEXTURE_RESULT_CLEAR			("data/TEXTURE/clear.png")				// 読み込むテクスチャファイル名
#define	TEXTURE_RESULT_GAMEOVER			("data/TEXTURE/gameover.png")			// 読み込むテクスチャファイル名

#define	RESULT_BG_POS_X			(0)							// リザルト背景の表示位置
#define	RESULT_BG_POS_Y			(0)							// リザルト背景の表示位置
#define	RESULT_BG_SIZE_X		(640)						// リザルト背景の幅
#define	RESULT_BG_SIZE_Y		(480)						// リザルト背景の高さ

#define	RESULT_POS_X			(20)						// リザルトの表示位置
#define	RESULT_POS_Y			(75)						// リザルトの表示位置
#define	RESULT_SIZE_X			(300)						// リザルトの幅
#define	RESULT_SIZE_Y			(70)						// リザルトの高さ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitResult(int type);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);

void SetTextureNo(int no);

#endif
