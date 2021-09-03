//=============================================================================
//
// タイトル画面処理 [star.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "star.h"
#include "line.h"
#include "arrow.h"
#include "input.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexStar(int no);
void SetVertexStar(int no);
D3DXVECTOR2 SetSelectPos(int pos);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureStar = NULL;		// テクスチャへのポインタ

STAR					g_Star[STAR_MAX];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitStar(int type)
{
	if (type == 0)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_STAR,				// ファイルの名前
			&g_pD3DTextureStar);		// 読み込むメモリー
	}

	D3DXVECTOR2 randpos;

	for (int i = 0; i < STAR_MAX; i++)
	{
		randpos.x = (float)(rand() % SCREEN_WIDTH);
		randpos.y = (float)(rand() % SCREEN_HEIGHT);

		g_Star[i].use = false;
		g_Star[i].no = 0;
		g_Star[i].pos = D3DXVECTOR2(0.0f, 0.0f);

		// 頂点情報の作成
		MakeVertexStar(i);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitStar(void)
{
	if (g_pD3DTextureStar != NULL)
	{// テクスチャの開放
		g_pD3DTextureStar->Release();
		g_pD3DTextureStar = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateStar()
{
	for (int i = 0; i < STAR_MAX; i++)
	{
		if (!GetMove(i) && g_Star[i].use==true)
		{
			g_Star[i].use = false;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawStar(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureStar);

	for (int i = 0; i < STAR_MAX; i++)
	{
		if (g_Star[i].use)
		{
			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_Star[i].vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexStar(int no)
{
	// 頂点座標の設定
	g_Star[no].vertexWk[0].vtx.x = g_Star[no].pos.x - STAR_SIZE_X;
	g_Star[no].vertexWk[0].vtx.y = g_Star[no].pos.y - STAR_SIZE_X;
	g_Star[no].vertexWk[0].vtx.z = 0.0f;

	g_Star[no].vertexWk[1].vtx.x = g_Star[no].pos.x + STAR_SIZE_X;
	g_Star[no].vertexWk[1].vtx.y = g_Star[no].pos.y - STAR_SIZE_X;
	g_Star[no].vertexWk[1].vtx.z = 0.0f;

	g_Star[no].vertexWk[2].vtx.x = g_Star[no].pos.x - STAR_SIZE_X;
	g_Star[no].vertexWk[2].vtx.y = g_Star[no].pos.y + STAR_SIZE_X;
	g_Star[no].vertexWk[2].vtx.z = 0.0f;

	g_Star[no].vertexWk[3].vtx.x = g_Star[no].pos.x + STAR_SIZE_X;
	g_Star[no].vertexWk[3].vtx.y = g_Star[no].pos.y + STAR_SIZE_X;
	g_Star[no].vertexWk[3].vtx.z = 0.0f;

	// テクスチャのパースペクティブコレクト用
	g_Star[no].vertexWk[0].rhw =
	g_Star[no].vertexWk[1].rhw =
	g_Star[no].vertexWk[2].rhw =
	g_Star[no].vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	g_Star[no].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_Star[no].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_Star[no].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_Star[no].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_Star[no].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_Star[no].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_Star[no].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_Star[no].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// 頂点の作成
//=============================================================================
void SetVertexStar(int no)
{
	// 頂点座標の設定
	g_Star[no].vertexWk[0].vtx.x = g_Star[no].pos.x - STAR_SIZE_X;
	g_Star[no].vertexWk[0].vtx.y = g_Star[no].pos.y - STAR_SIZE_X;
	g_Star[no].vertexWk[0].vtx.z = 0.0f;

	g_Star[no].vertexWk[1].vtx.x = g_Star[no].pos.x + STAR_SIZE_X;
	g_Star[no].vertexWk[1].vtx.y = g_Star[no].pos.y - STAR_SIZE_X;
	g_Star[no].vertexWk[1].vtx.z = 0.0f;

	g_Star[no].vertexWk[2].vtx.x = g_Star[no].pos.x - STAR_SIZE_X;
	g_Star[no].vertexWk[2].vtx.y = g_Star[no].pos.y + STAR_SIZE_X;
	g_Star[no].vertexWk[2].vtx.z = 0.0f;

	g_Star[no].vertexWk[3].vtx.x = g_Star[no].pos.x + STAR_SIZE_X;
	g_Star[no].vertexWk[3].vtx.y = g_Star[no].pos.y + STAR_SIZE_X;
	g_Star[no].vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// g_Star[no].useの状態取得関数
//=============================================================================
bool GetStar(int no)
{
	return g_Star[no].use;
}

//=============================================================================
// g_Star[no].noの状態取得関数
//=============================================================================
int GetStarPosNo(int no)
{
	return g_Star[no].no;
}

//=============================================================================
// g_Star[no].posの状態取得関数
//=============================================================================
D3DXVECTOR2 GetStarPos(int no)
{
	return g_Star[no].pos;
}

//=============================================================================
// スターのセット
//=============================================================================
void SetStar(int pos)
{
	for (int i = 0; i < STAR_MAX; i++)
	{
		if (!g_Star[i].use)
		{
			g_Star[i].use = true;
			g_Star[i].no = pos;
			g_Star[i].pos = SetSelectPos(pos);
			SetVertexStar(i);
			SetLine(i, g_Star[i].pos);
			SetArrow(i, g_Star[i].pos);
			SetArrow(i + STAR_MAX, g_Star[i].pos);

			return;
		}
	}
}

//=============================================================================
// スターの位置セット
//=============================================================================
D3DXVECTOR2 SetSelectPos(int posno)
{
	D3DXVECTOR2 pos;

	int posX = posno % 6;
	int posY = posno / 6;

	pos.x = STAR_POS_X + STAR_SPACE_X * posX;
	pos.y = STAR_POS_Y + STAR_SPACE_Y * posY;

	return pos;
}
