//=============================================================================
//
// タイトル画面処理 [star.h]
// Author : 
//
//=============================================================================
#ifndef _STAR_H_
#define _STAR_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_STAR			("data/TEXTURE/cross_star.png")			// 読み込むテクスチャファイル名
#define STAR_MAX			(20)

#define	STAR_POS_X			(65.0f)								// タイトルの表示位置
#define	STAR_POS_Y			(100.0f)							// タイトルの表示位置

#define STAR_SPACE_X		(100.0f)
#define STAR_SPACE_Y		(145.0f)

#define	STAR_SIZE_X		(50.0f / 2)								// タイトルの幅
#define	STAR_SIZE_Y		(50.0f / 2)								// タイトルの高さ

//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// スター構造体
{
	bool			use;						// true:使用 false:未使用
	int				no;
	D3DXVECTOR2		pos;						// 位置
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク
} STAR;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitStar(int type);
void UninitStar(void);
void UpdateStar(void);
void DrawStar(void);

bool GetStar(int no);
int GetStarPosNo(int no);
D3DXVECTOR2 GetStarPos(int no);

void SetStar(int pos);

#endif