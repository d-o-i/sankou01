//=============================================================================
//
// タイトル画面処理 [bg.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "bg.h"
#include "input.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBg(void);
void SetVertexBg(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBg = NULL;		// テクスチャへのポインタ

VERTEX_2D				g_vertexWkBg[NUM_VERTEX];			// 頂点情報格納ワーク

																//=============================================================================
																// 初期化処理
																//=============================================================================
HRESULT InitBg(int type)
{
	if (type == 0)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_BG,				// ファイルの名前
			&g_pD3DTextureBg);		// 読み込むメモリー
	}

	// 頂点情報の作成
	MakeVertexBg();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBg(void)
{
	if (g_pD3DTextureBg != NULL)
	{// テクスチャの開放
		g_pD3DTextureBg->Release();
		g_pD3DTextureBg = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBg()
{
	SetVertexBg();

	if (GetKeyboardTrigger(DIK_RETURN))
	{
		SetStage(STAGE_GAME);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureBg);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkBg, sizeof(VERTEX_2D));
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBg(void)
{

	// 頂点座標の設定
	g_vertexWkBg[0].vtx = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);
	g_vertexWkBg[1].vtx = D3DXVECTOR3(BG_POS_X + BG_SIZE_X, BG_POS_Y, 0.0f);
	g_vertexWkBg[2].vtx = D3DXVECTOR3(BG_POS_X, BG_POS_Y + BG_SIZE_Y, 0.0f);
	g_vertexWkBg[3].vtx = D3DXVECTOR3(BG_POS_X + BG_SIZE_X, BG_POS_Y + BG_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkBg[0].rhw =
		g_vertexWkBg[1].rhw =
		g_vertexWkBg[2].rhw =
		g_vertexWkBg[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkBg[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkBg[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkBg[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkBg[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkBg[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkBg[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkBg[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkBg[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexBg(void)
{

}