//=============================================================================
//
// タイトル画面処理 [select.h]
// Author : 
//
//=============================================================================
#ifndef _SELECT_H_
#define _SELECT_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_SELECT			_T("data/TEXTURE/select.png")			// 読み込むテクスチャファイル名

#define	TEXTURE_SELECT_DEEPER			_T("data/TEXTURE/deeper2.png")			// 読み込むテクスチャファイル名
#define	TEXTURE_SELECT_DEEPER_LOGO		_T("data/TEXTURE/deeper logo.png")			// 読み込むテクスチャファイル名
#define	TEXTURE_SELECT_SUPERNOVA		_T("data/TEXTURE/super nova2.png")			// 読み込むテクスチャファイル名
#define	TEXTURE_SELECT_SUPERNOVA_LOGO	_T("data/TEXTURE/supernova logo.png")			// 読み込むテクスチャファイル名
#define	TEXTURE_SELECT_DAYDREAM		_T("data/TEXTURE/daydream2.png")			// 読み込むテクスチャファイル名
#define	TEXTURE_SELECT_DAYDREAM_LOGO	_T("data/TEXTURE/daydream logo.png")			// 読み込むテクスチャファイル名


#define	SELECT_POS_X			(0.0f)								// タイトルの表示位置
#define	SELECT_POS_Y			(0.0f)								// タイトルの表示位置
#define	SELECT_SIZE_X			(640.0f)							// タイトルの幅
#define	SELECT_SIZE_Y			(480.0f)							// タイトルの高さ
#define JACKET_SIZE				(180.0f/2)
#define JACKET_POS_X			(320.0f)
#define JACKET_POS_Y			(240.0f)
#define LOGO_SIZE_X				(150.0f/2)
#define LOGO_SIZE_Y				(60.0f/2)
#define LOGO_POS_X				(320.0f)
#define LOGO_POS_Y				(400.0f)

#define JACKET_SIZE0		(25.0f)
#define JACKET_POS_X0		(80.0f)
#define JACKET_POS_Y0		(240.0f)

#define JACKET_SIZE4		(JACKET_SIZE0)
#define JACKET_POS_X4		(560.0f)
#define JACKET_POS_Y4		(240.0f)

#define JACKET_SIZE1		(50.0f)
#define JACKET_POS_X1		(160.0f)
#define JACKET_POS_Y1		(240.0f)

#define JACKET_SIZE3		(JACKET_SIZE1)
#define JACKET_POS_X3		(480.0f)
#define JACKET_POS_Y3		(240.0f)

#define JACKET_SIZE2		(100.0f)
#define JACKET_POS_X2		(320.0f)
#define JACKET_POS_Y2		(240.0f)


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSelect(int type);
void UninitSelect(void);
void UpdateSelect(void);
void DrawSelect(void);

void StartMusic(void);
float GetSuperPos(void);
float GetSelectSuperPos(void);
int GetSelectNo(void);

#endif
