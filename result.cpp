//=============================================================================
//
// リザルト画面処理 [result.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "result.h"
#include "input.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexResult(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureResultBG = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureResultClear = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureResultGameOver = NULL;		// テクスチャへのポインタ

VERTEX_2D				g_vertexWkResultBG[NUM_VERTEX];			// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkResult[NUM_VERTEX];			// 頂点情報格納ワーク

static int g_Num;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitResult(int type)
{
	if (type == 0)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_RESULT_BG,				// ファイルの名前
		&g_pD3DTextureResultBG);					// 読み込むメモリー

		D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
			TEXTURE_RESULT_CLEAR,				// ファイルの名前
			&g_pD3DTextureResultClear);					// 読み込むメモリー

		D3DXCreateTextureFromFile(pDevice,							// デバイスへのポインタ
			TEXTURE_RESULT_GAMEOVER,				// ファイルの名前
			&g_pD3DTextureResultGameOver);		// 読み込むメモリー
	}

	// 頂点情報の作成
	MakeVertexResult();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitResult(void)
{
	if (g_pD3DTextureResultBG != NULL)
	{// テクスチャの開放
		g_pD3DTextureResultBG->Release();
		g_pD3DTextureResultBG = NULL;
	}
	if(g_pD3DTextureResultClear != NULL)
	{// テクスチャの開放
		g_pD3DTextureResultClear->Release();
		g_pD3DTextureResultClear = NULL;
	}
	if (g_pD3DTextureResultGameOver != NULL)
	{// テクスチャの開放
		g_pD3DTextureResultGameOver->Release();
		g_pD3DTextureResultGameOver = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateResult(void)
{
	if(GetKeyboardTrigger(DIK_RETURN))
	{// Enter押したら、ステージを切り替える
		InitGame();
		SetStage( STAGE_TITLE );
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureResultBG);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkResultBG, sizeof(VERTEX_2D));


	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_Num == 0)
	{
		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureResultClear);
	}
	else
	{
		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureResultGameOver);
	}

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_RESULT, g_vertexWkResult, sizeof(VERTEX_2D));
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexResult(void)
{	
	// 頂点座標の設定
	g_vertexWkResultBG[0].vtx = D3DXVECTOR3(RESULT_BG_POS_X, RESULT_BG_POS_Y, 0.0f);
	g_vertexWkResultBG[1].vtx = D3DXVECTOR3(RESULT_BG_POS_X + RESULT_BG_SIZE_X, RESULT_BG_POS_Y, 0.0f);
	g_vertexWkResultBG[2].vtx = D3DXVECTOR3(RESULT_BG_POS_X, RESULT_BG_POS_Y + RESULT_BG_SIZE_Y, 0.0f);
	g_vertexWkResultBG[3].vtx = D3DXVECTOR3(RESULT_BG_POS_X + RESULT_BG_SIZE_X, RESULT_BG_POS_Y + RESULT_BG_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkResultBG[0].rhw =
	g_vertexWkResultBG[1].rhw =
	g_vertexWkResultBG[2].rhw =
	g_vertexWkResultBG[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkResultBG[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkResultBG[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkResultBG[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkResultBG[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkResultBG[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkResultBG[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkResultBG[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkResultBG[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	// 頂点座標の設定
	g_vertexWkResult[0].vtx = D3DXVECTOR3(RESULT_POS_X, RESULT_POS_Y, 0.0f);
	g_vertexWkResult[1].vtx = D3DXVECTOR3(RESULT_POS_X + RESULT_SIZE_X, RESULT_POS_Y, 0.0f);
	g_vertexWkResult[2].vtx = D3DXVECTOR3(RESULT_POS_X, RESULT_POS_Y + RESULT_SIZE_Y, 0.0f);
	g_vertexWkResult[3].vtx = D3DXVECTOR3(RESULT_POS_X + RESULT_SIZE_X, RESULT_POS_Y + RESULT_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkResult[0].rhw =
	g_vertexWkResult[1].rhw =
	g_vertexWkResult[2].rhw =
	g_vertexWkResult[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkResult[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkResult[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkResult[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkResult[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkResult[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkResult[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkResult[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkResult[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// テクスチャの設定
//=============================================================================
void SetTextureNo(int no)
{
	g_Num = no;
}