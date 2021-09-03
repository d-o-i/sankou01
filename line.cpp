//=============================================================================
//
// タイトル画面処理 [line.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "line.h"
#include "input.h"
#include "star.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define LINE_MAX			(STAR_MAX)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexLine(int no);
void SetLine(int no, D3DXVECTOR2 pos);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureLine = NULL;		// テクスチャへのポインタ

LINE					g_Line[LINE_MAX];				// ラインの構造体配列

float angle;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitLine(int type)
{
	if (type == 0)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_LINE,				// ファイルの名前
			&g_pD3DTextureLine);		// 読み込むメモリー
	}

	for (int i = 0; i < LINE_MAX; i++)
	{
		g_Line[i].use = false;
		g_Line[i].rot = 0.0f;

		// 頂点情報の作成
		MakeVertexLine(i);
	}

	angle = atan2f(LINE_SIZE_Y, LINE_SIZE_X);	// プレイヤーの角度を初期化

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitLine(void)
{
	if (g_pD3DTextureLine != NULL)
	{// テクスチャの開放
		g_pD3DTextureLine->Release();
		g_pD3DTextureLine = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateLine()
{
	for (int i = 0; i < LINE_MAX; i++)
	{
		if (!GetStar(i))
		{
			g_Line[i].use = false;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawLine(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureLine);

	for (int i = 0; i < LINE_MAX; i++)
	{
		if (g_Line[i].use)
		{
			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_Line[i].vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexLine(int no)
{
	// テクスチャのパースペクティブコレクト用
	g_Line[no].vertexWk[0].rhw =
	g_Line[no].vertexWk[1].rhw =
	g_Line[no].vertexWk[2].rhw =
	g_Line[no].vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	g_Line[no].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_Line[no].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_Line[no].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_Line[no].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_Line[no].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_Line[no].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_Line[no].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_Line[no].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetLine(int no, D3DXVECTOR2 pos)
{
#define LD0 (D3DXVECTOR3(pos.x + 153.0f - cosf(angle + g_Line[no].rot) * LINE_SIZE_X, pos.y - 153.0f - sinf(angle + g_Line[no].rot) * LINE_SIZE_X, 0.0f))
#define LD1 (D3DXVECTOR3(pos.x + 153.0f + cosf(angle - g_Line[no].rot) * LINE_SIZE_X, pos.y - 153.0f - sinf(angle - g_Line[no].rot) * LINE_SIZE_X, 0.0f))
#define LD2 (D3DXVECTOR3(pos.x + 153.0f - cosf(angle - g_Line[no].rot) * LINE_SIZE_X, pos.y - 153.0f + sinf(angle - g_Line[no].rot) * LINE_SIZE_X, 0.0f))
#define LD3 (D3DXVECTOR3(pos.x + 153.0f + cosf(angle + g_Line[no].rot) * LINE_SIZE_X, pos.y - 153.0f + sinf(angle + g_Line[no].rot) * LINE_SIZE_X, 0.0f))

#define L0  (D3DXVECTOR3(pos.x + 215.0f - cosf(angle + g_Line[no].rot) * LINE_SIZE_X, pos.y - sinf(angle + g_Line[no].rot) * LINE_SIZE_X, 0.0f))
#define L1  (D3DXVECTOR3(pos.x + 215.0f + cosf(angle - g_Line[no].rot) * LINE_SIZE_X, pos.y - sinf(angle - g_Line[no].rot) * LINE_SIZE_X, 0.0f))
#define L2  (D3DXVECTOR3(pos.x + 215.0f - cosf(angle - g_Line[no].rot) * LINE_SIZE_X, pos.y + sinf(angle - g_Line[no].rot) * LINE_SIZE_X, 0.0f))
#define L3  (D3DXVECTOR3(pos.x + 215.0f + cosf(angle + g_Line[no].rot) * LINE_SIZE_X, pos.y + sinf(angle + g_Line[no].rot) * LINE_SIZE_X, 0.0f))

#define LU0 (D3DXVECTOR3(pos.x + 153.0f - cosf(angle + g_Line[no].rot) * LINE_SIZE_X, pos.y + 153.0f - sinf(angle + g_Line[no].rot) * LINE_SIZE_X, 0.0f))
#define LU1 (D3DXVECTOR3(pos.x + 153.0f + cosf(angle - g_Line[no].rot) * LINE_SIZE_X, pos.y + 153.0f - sinf(angle - g_Line[no].rot) * LINE_SIZE_X, 0.0f))
#define LU2 (D3DXVECTOR3(pos.x + 153.0f - cosf(angle - g_Line[no].rot) * LINE_SIZE_X, pos.y + 153.0f + sinf(angle - g_Line[no].rot) * LINE_SIZE_X, 0.0f))
#define LU3 (D3DXVECTOR3(pos.x + 153.0f + cosf(angle + g_Line[no].rot) * LINE_SIZE_X, pos.y + 153.0f + sinf(angle + g_Line[no].rot) * LINE_SIZE_X, 0.0f))

#define U0 (D3DXVECTOR3(pos.x + 2.5f - cosf(angle + g_Line[no].rot) * LINE_SIZE_X, pos.y + 215.0f - sinf(angle + g_Line[no].rot) * LINE_SIZE_X, 0.0f))
#define U1 (D3DXVECTOR3(pos.x + 2.5f + cosf(angle - g_Line[no].rot) * LINE_SIZE_X, pos.y + 215.0f - sinf(angle - g_Line[no].rot) * LINE_SIZE_X, 0.0f))
#define U2 (D3DXVECTOR3(pos.x + 2.5f - cosf(angle - g_Line[no].rot) * LINE_SIZE_X, pos.y + 215.0f + sinf(angle - g_Line[no].rot) * LINE_SIZE_X, 0.0f))
#define U3 (D3DXVECTOR3(pos.x + 2.5f + cosf(angle + g_Line[no].rot) * LINE_SIZE_X, pos.y + 215.0f + sinf(angle + g_Line[no].rot) * LINE_SIZE_X, 0.0f))

#define RU0 (D3DXVECTOR3(pos.x - 153.0f - cosf(angle + g_Line[no].rot) * LINE_SIZE_X, pos.y + 153.0f - sinf(angle + g_Line[no].rot) * LINE_SIZE_X, 0.0f))
#define RU1 (D3DXVECTOR3(pos.x - 153.0f + cosf(angle - g_Line[no].rot) * LINE_SIZE_X, pos.y + 153.0f - sinf(angle - g_Line[no].rot) * LINE_SIZE_X, 0.0f))
#define RU2 (D3DXVECTOR3(pos.x - 153.0f - cosf(angle - g_Line[no].rot) * LINE_SIZE_X, pos.y + 153.0f + sinf(angle - g_Line[no].rot) * LINE_SIZE_X, 0.0f))
#define RU3 (D3DXVECTOR3(pos.x - 153.0f + cosf(angle + g_Line[no].rot) * LINE_SIZE_X, pos.y + 153.0f + sinf(angle + g_Line[no].rot) * LINE_SIZE_X, 0.0f))

#define R0 (D3DXVECTOR3(pos.x - 212.0f - cosf(angle + g_Line[no].rot) * LINE_SIZE_X, pos.y - sinf(angle + g_Line[no].rot) * LINE_SIZE_X, 0.0f))
#define R1 (D3DXVECTOR3(pos.x - 212.0f + cosf(angle - g_Line[no].rot) * LINE_SIZE_X, pos.y - sinf(angle - g_Line[no].rot) * LINE_SIZE_X, 0.0f))
#define R2 (D3DXVECTOR3(pos.x - 212.0f - cosf(angle - g_Line[no].rot) * LINE_SIZE_X, pos.y + sinf(angle - g_Line[no].rot) * LINE_SIZE_X, 0.0f))
#define R3 (D3DXVECTOR3(pos.x - 212.0f + cosf(angle + g_Line[no].rot) * LINE_SIZE_X, pos.y + sinf(angle + g_Line[no].rot) * LINE_SIZE_X, 0.0f))
	
#define RD0 (D3DXVECTOR3(pos.x - 151.0f - cosf(angle + g_Line[no].rot) * LINE_SIZE_X, pos.y - 153.0f - sinf(angle + g_Line[no].rot) * LINE_SIZE_X, 0.0f))
#define RD1 (D3DXVECTOR3(pos.x - 151.0f + cosf(angle - g_Line[no].rot) * LINE_SIZE_X, pos.y - 153.0f - sinf(angle - g_Line[no].rot) * LINE_SIZE_X, 0.0f))
#define RD2 (D3DXVECTOR3(pos.x - 151.0f - cosf(angle - g_Line[no].rot) * LINE_SIZE_X, pos.y - 153.0f + sinf(angle - g_Line[no].rot) * LINE_SIZE_X, 0.0f))
#define RD3 (D3DXVECTOR3(pos.x - 151.0f + cosf(angle + g_Line[no].rot) * LINE_SIZE_X, pos.y - 153.0f + sinf(angle + g_Line[no].rot) * LINE_SIZE_X, 0.0f))

#define D0 (D3DXVECTOR3(pos.x + 3.0f - cosf(angle + g_Line[no].rot) * LINE_SIZE_X, pos.y - 212.0f - sinf(angle + g_Line[no].rot) * LINE_SIZE_X, 0.0f))
#define D1 (D3DXVECTOR3(pos.x + 3.0f + cosf(angle - g_Line[no].rot) * LINE_SIZE_X, pos.y - 212.0f - sinf(angle - g_Line[no].rot) * LINE_SIZE_X, 0.0f))
#define D2 (D3DXVECTOR3(pos.x + 3.0f - cosf(angle - g_Line[no].rot) * LINE_SIZE_X, pos.y - 212.0f + sinf(angle - g_Line[no].rot) * LINE_SIZE_X, 0.0f))
#define D3 (D3DXVECTOR3(pos.x + 3.0f + cosf(angle + g_Line[no].rot) * LINE_SIZE_X, pos.y - 212.0f + sinf(angle + g_Line[no].rot) * LINE_SIZE_X, 0.0f))

	if (20.0f <= pos.x&&pos.x < 220)
	{
		if (30.0f <= pos.y && pos.y < 170.0f)
		{
			g_Line[no].rot = RIGHTDOWN;
		}
		else if (pos.y < 310.0f)
		{
			g_Line[no].rot = RIGHT;
		}
		else if (pos.y <= 450.0f)
		{
			g_Line[no].rot = RIGHTUP;
		}
	}
	else if (pos.x < 420)
	{
		if (30.0f <= pos.y && pos.y < 210.0f)
		{
			g_Line[no].rot = DOWN;
		}
		else if (270.0f <= pos.y && pos.y <= 450.0f)
		{
			g_Line[no].rot = UP;
		}
	}
	else if (pos.x <= 620.0f)
	{
		if (30.0f <= pos.y && pos.y < 170.0f)
		{
			g_Line[no].rot = LEFTDOWN;
		}
		else if (pos.y < 310.0f)
		{
			g_Line[no].rot = LEFT;
		}
		else if (pos.y <= 450.0f)
		{
			g_Line[no].rot = LEFTUP;
		}
	}

	//}
	//else
	//{
	//	if (pos.y < 240)
	//	{
	//		g_Line[no].rot = LEFTDOWN;
	//	}
	//	else
	//	{
	//		g_Line[no].rot = LEFTUP;
	//	}
	//}
	g_Line[no].use = true;
	if (g_Line[no].rot == LEFTDOWN)
	{
		// 頂点座標の設定
		g_Line[no].vertexWk[0].vtx = LD0;
		g_Line[no].vertexWk[1].vtx = LD1;
		g_Line[no].vertexWk[2].vtx = LD2;
		g_Line[no].vertexWk[3].vtx = LD3;
	}
	else if (g_Line[no].rot == LEFT)
	{
		// 頂点座標の設定
		g_Line[no].vertexWk[0].vtx = L0;
		g_Line[no].vertexWk[1].vtx = L1;
		g_Line[no].vertexWk[2].vtx = L2;
		g_Line[no].vertexWk[3].vtx = L3;
	}
	else if(g_Line[no].rot == LEFTUP)
	{
		// 頂点座標の設定
		g_Line[no].vertexWk[0].vtx = LU0;
		g_Line[no].vertexWk[1].vtx = LU1;
		g_Line[no].vertexWk[2].vtx = LU2;
		g_Line[no].vertexWk[3].vtx = LU3;
	}
	else if (g_Line[no].rot == UP)
	{
		// 頂点座標の設定
		g_Line[no].vertexWk[0].vtx = U0;
		g_Line[no].vertexWk[1].vtx = U1;
		g_Line[no].vertexWk[2].vtx = U2;
		g_Line[no].vertexWk[3].vtx = U3;
	}
	else if (g_Line[no].rot == RIGHTUP)
	{
		// 頂点座標の設定
		g_Line[no].vertexWk[0].vtx = RU0;
		g_Line[no].vertexWk[1].vtx = RU1;
		g_Line[no].vertexWk[2].vtx = RU2;
		g_Line[no].vertexWk[3].vtx = RU3;
	}
	else if (g_Line[no].rot == RIGHT)
	{
		// 頂点座標の設定
		g_Line[no].vertexWk[0].vtx = R0;
		g_Line[no].vertexWk[1].vtx = R1;
		g_Line[no].vertexWk[2].vtx = R2;
		g_Line[no].vertexWk[3].vtx = R3;
	}
	else if (g_Line[no].rot == RIGHTDOWN)
	{
		// 頂点座標の設定
		g_Line[no].vertexWk[0].vtx = RD0;
		g_Line[no].vertexWk[1].vtx = RD1;
		g_Line[no].vertexWk[2].vtx = RD2;
		g_Line[no].vertexWk[3].vtx = RD3;
	}
	else if (g_Line[no].rot == DOWN)
	{
		// 頂点座標の設定
		g_Line[no].vertexWk[0].vtx = D0;
		g_Line[no].vertexWk[1].vtx = D1;
		g_Line[no].vertexWk[2].vtx = D2;
		g_Line[no].vertexWk[3].vtx = D3;
	}
}
float GetRot(int no)
{
		return g_Line[no].rot;
}
