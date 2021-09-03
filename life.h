//=============================================================================
//
// タイトル画面処理 [life.h]
// Author : 
//
//=============================================================================
#ifndef _LIFE_H_
#define _LIFE_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_LIFE			_T("data/TEXTURE/gauge11.png")			// 読み込むテクスチャファイル名

#define	LIFE_POS_X			(20.15f)					// ライフの表示位置
#define	LIFE_POS_Y			(20.0f)					// ライフの表示位置
#define	LIFE_SIZE_X			(490.0f)				// ライフの幅
#define	LIFE_SIZE_Y			(4.0f)					// ライフの高さ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitLife(int type);
void UninitLife(void);
void UpdateLife(void);
void DrawLife(void);

void CalLife(int val);

#endif
