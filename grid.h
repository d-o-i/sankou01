//=============================================================================
//
// タイトル画面処理 [grid.h]
// Author : 
//
//=============================================================================
#ifndef _GRID_H_
#define _GRID_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_GRID			_T("data/TEXTURE/gridman.png")			// 読み込むテクスチャファイル名
#define	TEXTURE_UI_NOVA			_T("data/TEXTURE/super nova.png")		// 読み込むテクスチャファイル名
#define	TEXTURE_UI_DEEP			_T("data/TEXTURE/deeper.png")			// 読み込むテクスチャファイル名
#define	TEXTURE_UI_DRAM			_T("data/TEXTURE/daydream.png")			// 読み込むテクスチャファイル名

#define TEXTURE_TEST			_T("data/TEXTURE/tester.png")			// 読みこむテクスチャファイル名

#define	GRID_POS_X			(0.0f)								// タイトルの表示位置
#define	GRID_POS_Y			(0.0f)								// タイトルの表示位置
#define	GRID_SIZE_X			(640.0f)							// タイトルの幅
#define	GRID_SIZE_Y			(480.0f)							// タイトルの高さ

#define	UI_NOVA_POS_X		(80.0f)								// タイトルの表示位置
#define	UI_NOVA_POS_Y		(2.0f)								// タイトルの表示位置
#define	UI_NOVA_SIZE_X		(80.0f)							// タイトルの幅
#define	UI_NOVA_SIZE_Y		(15.0f)							// タイトルの高さ

#define	UI_DEEP_POS_X		(80.0f)								// タイトルの表示位置
#define	UI_DEEP_POS_Y		(2.0f)								// タイトルの表示位置
#define	UI_DEEP_SIZE_X		(80.0f)							// タイトルの幅
#define	UI_DEEP_SIZE_Y		(15.0f)							// タイトルの高さ

#define	UI_DRAM_POS_X		(80.0f)								// タイトルの表示位置
#define	UI_DRAM_POS_Y		(2.0f)								// タイトルの表示位置
#define	UI_DRAM_SIZE_X		(80.0f)							// タイトルの幅
#define	UI_DRAM_SIZE_Y		(15.0f)							// タイトルの高さ

#define HIT_POS_X			(20.0f)
#define HIT_POS_Y			(30.0f)
#define HIT_SIZE_X			(100.0f)
#define HIT_SIZE_Y			(140.0f)

//#define GRID_POS_X1			(0.0f)
//#define GRID_POS_Y1			(0.0f)
//#define GRID_SIZE_X1		(0.0f)
//#define GRID_SIZE_Y1		(0.0f)
//
//#define GRID_POS_X2			(0.0f)
//#define GRID_POS_Y2			(0.0f)
//#define GRID_SIZE_X2		(0.0f)
//#define GRID_SIZE_Y2		(0.0f)
//
//#define GRID_POS_X3			(0.0f)
//#define GRID_POS_Y3			(0.0f)
//#define GRID_SIZE_X3		(0.0f)
//#define GRID_SIZE_Y3		(0.0f)
//
//#define GRID_POS_X4			(0.0f)
//#define GRID_POS_Y4			(0.0f)
//#define GRID_SIZE_X4		(0.0f)
//#define GRID_SIZE_Y4		(0.0f)
//
//#define GRID_POS_X5			(0.0f)
//#define GRID_POS_Y5			(0.0f)
//#define GRID_SIZE_X5		(0.0f)
//#define GRID_SIZE_Y5		(0.0f)
//
//#define GRID_POS_X6			(0.0f)
//#define GRID_POS_Y6			(0.0f)
//#define GRID_SIZE_X6		(0.0f)
//#define GRID_SIZE_Y6		(0.0f)
//
//#define GRID_POS_X7			(0.0f)
//#define GRID_POS_Y7			(0.0f)
//#define GRID_SIZE_X7		(0.0f)
//#define GRID_SIZE_Y7		(0.0f)
//
//#define GRID_POS_X8			(0.0f)
//#define GRID_POS_Y8			(0.0f)
//#define GRID_SIZE_X8		(0.0f)
//#define GRID_SIZE_Y8		(0.0f)
//
//#define GRID_POS_X9			(0.0f)
//#define GRID_POS_Y9			(0.0f)
//#define GRID_SIZE_X9		(0.0f)
//#define GRID_SIZE_Y9		(0.0f)
//
//#define GRID_POS_X10		(0.0f)
//#define GRID_POS_Y10		(0.0f)
//#define GRID_SIZE_X10		(0.0f)
//#define GRID_SIZE_Y10		(0.0f)
//
//#define GRID_POS_X11		(0.0f)
//#define GRID_POS_Y11		(0.0f)
//#define GRID_SIZE_X11		(0.0f)
//#define GRID_SIZE_Y11		(0.0f)
//
//#define GRID_POS_X12		(0.0f)
//#define GRID_POS_Y12		(0.0f)
//#define GRID_SIZE_X12		(0.0f)
//#define GRID_SIZE_Y12		(0.0f)
//
//#define GRID_POS_X13		(0.0f)
//#define GRID_POS_Y13		(0.0f)
//#define GRID_SIZE_X13		(0.0f)
//#define GRID_SIZE_Y13		(0.0f)
//
//#define GRID_POS_X14		(0.0f)
//#define GRID_POS_Y14		(0.0f)
//#define GRID_SIZE_X14		(0.0f)
//#define GRID_SIZE_Y14		(0.0f)
//
//#define GRID_POS_X15		(0.0f)
//#define GRID_POS_Y15		(0.0f)
//#define GRID_SIZE_X15		(0.0f)
//#define GRID_SIZE_Y15		(0.0f)
//
//#define GRID_POS_X16		(0.0f)
//#define GRID_POS_Y16		(0.0f)
//#define GRID_SIZE_X16		(0.0f)
//#define GRID_SIZE_Y16		(0.0f)
//
//#define GRID_POS_X17		(0.0f)
//#define GRID_POS_Y17		(0.0f)
//#define GRID_SIZE_X17		(0.0f)
//#define GRID_SIZE_Y17		(0.0f)
//
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitGrid(int type);
void UninitGrid(void);
void UpdateGrid(void);
void DrawGrid(void);

#ifdef _DEBUG
float GetPosTest(int type);
#endif

#endif
