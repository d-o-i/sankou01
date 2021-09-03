//=============================================================================
//
// タイトル画面処理 [arrow.h]
// Author : 
//
//=============================================================================
#ifndef _ARROW_H_
#define _ARROW_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_ARROW		("data/TEXTURE/arrow.png")			// 読み込むテクスチャファイル名

#define	ARROW_POS_X			(0.0f)								// タイトルの表示位置
#define	ARROW_POS_Y			(0.0f)								// タイトルの表示位置
#define	ARROW_SIZE_X		(50.0f)							// タイトルの幅
#define	ARROW_SIZE_Y		(50.0f)							// タイトルの高さ
#define MIGISHITA			(D3DX_PI * 0.0f)
#define SHITA				(D3DX_PI * 0.25f)
#define HIDARISHITA			(D3DX_PI * 0.5f)
#define HIDARI				(D3DX_PI * 0.75f)
#define HIDARIUE			(D3DX_PI * 1.0f)
#define UE					(D3DX_PI * 1.25f)
#define MIGIUE				(D3DX_PI * 1.5f)
#define MIGI				(D3DX_PI * 1.75f)
#define HIRA				(300.0f)
#define NANAME				(200.0f)
#define HIRASPEED			(HIRA/100.0f)
#define NANAMESPEED			(NANAME/100.0f)
#define CHECKRANGE			(HIRASPEED/3.0f)

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
typedef struct	// ライン構造体
{
	bool			use;						// true:使用 false:未使用
	bool			move;
	D3DXVECTOR2		pos;						// 位置
	D3DXVECTOR3		rot;						// 位置
	float			angle;						// 角度
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク
} ARROW;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitArrow(int type);
void UninitArrow(void);
void UpdateArrow(void);
void DrawArrow(void);

void SetArrow(int no, D3DXVECTOR2 pos);
void ReleaseArrow(int no);

bool GetMove(int no);
bool GetArrow(int no);
D3DXVECTOR2 GetArrowPos(int no);



#endif