//=============================================================================
//
// タイトル画面処理 [line.h]
// Author : 
//
//=============================================================================
#ifndef _LINE_H_
#define _LINE_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_LINE		("data/TEXTURE/line.png")			// 読み込むテクスチャファイル名

#define	LINE_POS_X			(0.0f)								// タイトルの表示位置
#define	LINE_POS_Y			(0.0f)								// タイトルの表示位置
#define	LINE_SIZE_X			(480.0f / 2)						// タイトルの幅
#define	LINE_SIZE_Y			(480.0f / 2)						// タイトルの高さ
#define LEFTDOWN			(D3DX_PI * 0.0f)
#define LEFT				(D3DX_PI * 0.25f)
#define LEFTUP				(D3DX_PI * 0.5f)
#define UP					(D3DX_PI * 0.75f)
#define RIGHTUP				(D3DX_PI * 1.0f)
#define RIGHT				(D3DX_PI * 1.25f)
#define RIGHTDOWN			(D3DX_PI * 1.5f)
#define DOWN				(D3DX_PI * 1.75f)
#define LD					(153.0f)
//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// ライン構造体
{
	bool			use;						// true:使用 false:未使用
	float			rot;						// 回転
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク
} LINE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitLine(int type);
void UninitLine(void);
void UpdateLine(void);
void DrawLine(void);

void SetLine(int no, D3DXVECTOR2 pos);
float GetRot(int no);
#endif