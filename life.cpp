//=============================================================================
//
// タイトル画面処理 [life.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "life.h"
#include "score.h"
#include "result.h"
#include "input.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexLife(void);
void SetVertexLife(void);
void SetTextureLife(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureLife = NULL;		// テクスチャへのポインタ

VERTEX_2D				g_vertexWkLife[NUM_VERTEX];			// 頂点情報格納ワーク

static int g_Life;
static int g_LifeMax;
static float g_per;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitLife(int type)
{
	if (type == 0)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_LIFE,				// ファイルの名前
			&g_pD3DTextureLife);		// 読み込むメモリー
	}

	g_Life = 100;
	g_LifeMax = 100;
	g_per = 1.0f;

	// 頂点情報の作成
	MakeVertexLife();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitLife(void)
{
	if (g_pD3DTextureLife != NULL)
	{// テクスチャの開放
		g_pD3DTextureLife->Release();
		g_pD3DTextureLife = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateLife()
{
	if (g_Life == 0)
	{
		SetTextureNo(1);
		SetVertexScore();
		SetStage(STAGE_RESULT);
	}

	SetVertexLife();
	SetTextureLife();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureLife);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkLife, sizeof(VERTEX_2D));
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexLife(void)
{
	// 頂点座標の設定
	g_vertexWkLife[0].vtx = D3DXVECTOR3(LIFE_POS_X, LIFE_POS_Y, 0.0f);
	g_vertexWkLife[1].vtx = D3DXVECTOR3(LIFE_POS_X + LIFE_SIZE_X, LIFE_POS_Y, 0.0f);
	g_vertexWkLife[2].vtx = D3DXVECTOR3(LIFE_POS_X, LIFE_POS_Y + LIFE_SIZE_Y, 0.0f);
	g_vertexWkLife[3].vtx = D3DXVECTOR3(LIFE_POS_X + LIFE_SIZE_X, LIFE_POS_Y + LIFE_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkLife[0].rhw =
	g_vertexWkLife[1].rhw =
	g_vertexWkLife[2].rhw =
	g_vertexWkLife[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkLife[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkLife[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkLife[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkLife[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkLife[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkLife[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkLife[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkLife[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexLife(void)
{
	// 頂点座標の設定
	g_vertexWkLife[0].vtx = D3DXVECTOR3(LIFE_POS_X, LIFE_POS_Y, 0.0f);
	g_vertexWkLife[1].vtx = D3DXVECTOR3(LIFE_POS_X + LIFE_SIZE_X * g_per, LIFE_POS_Y, 0.0f);
	g_vertexWkLife[2].vtx = D3DXVECTOR3(LIFE_POS_X, LIFE_POS_Y + LIFE_SIZE_Y, 0.0f);
	g_vertexWkLife[3].vtx = D3DXVECTOR3(LIFE_POS_X + LIFE_SIZE_X * g_per, LIFE_POS_Y + LIFE_SIZE_Y, 0.0f);
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureLife(void)
{
	// テクスチャ座標の設定
	g_vertexWkLife[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkLife[1].tex = D3DXVECTOR2(g_per, 0.0f);
	g_vertexWkLife[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkLife[3].tex = D3DXVECTOR2(g_per, 1.0f);
}

//=============================================================================
// ライフの加算減算処理
//=============================================================================
void CalLife(int val)
{
	g_Life += val;

	if (g_Life > g_LifeMax)
	{
		g_Life = g_LifeMax;
	}
	else if (g_Life < 0)
	{
		g_Life = 0;
	}

	g_per = (float)g_Life / g_LifeMax;
}