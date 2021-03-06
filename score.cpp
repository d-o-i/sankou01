//=============================================================================
//
// タイトル画面処理 [score.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "score.h"
#include "input.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexScore(void);
void SetTextureScore(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureScore = NULL;		// テクスチャへのポインタ

VERTEX_2D				g_vertexWkScore[SCORE_DIGIT][NUM_VERTEX];	// 頂点情報格納ワーク

int						g_Score;						// スコア
D3DXVECTOR2				g_posScore;						// スコアの位置

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitScore(int type)
{
	if (type == 0)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_SCORE,				// ファイルの名前
			&g_pD3DTextureScore);		// 読み込むメモリー
	}

	g_Score = 0;

	// 頂点情報の作成
	MakeVertexScore();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitScore(void)
{
	if (g_pD3DTextureScore != NULL)
	{// テクスチャの開放
		g_pD3DTextureScore->Release();
		g_pD3DTextureScore = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateScore()
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureScore);

	// スコアの桁数分描画
	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkScore[i], sizeof(VERTEX_2D));
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexScore(void)
{
	float habaX = GAME_SCORE_SIZE_X;	// 数字の横幅
	int number = g_Score;

	// 桁数分処理する
	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		// 頂点座標の設定
		g_vertexWkScore[i][0].vtx.x = -habaX * i + GAME_SCORE_POS_X;
		g_vertexWkScore[i][0].vtx.y = GAME_SCORE_POS_Y;
		g_vertexWkScore[i][1].vtx.x = -habaX * i + GAME_SCORE_POS_X + GAME_SCORE_SIZE_X;
		g_vertexWkScore[i][1].vtx.y = GAME_SCORE_POS_Y;
		g_vertexWkScore[i][2].vtx.x = -habaX * i + GAME_SCORE_POS_X;
		g_vertexWkScore[i][2].vtx.y = GAME_SCORE_POS_Y + GAME_SCORE_SIZE_Y;
		g_vertexWkScore[i][3].vtx.x = -habaX * i + GAME_SCORE_POS_X + GAME_SCORE_SIZE_X;
		g_vertexWkScore[i][3].vtx.y = GAME_SCORE_POS_Y + GAME_SCORE_SIZE_Y;

		// rhwの設定
		g_vertexWkScore[i][0].rhw =
		g_vertexWkScore[i][1].rhw =
		g_vertexWkScore[i][2].rhw =
		g_vertexWkScore[i][3].rhw = 1.0f;

		// 反射光の設定
		g_vertexWkScore[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkScore[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkScore[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkScore[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		for (int i = 0; i < SCORE_DIGIT; i++)
		{
			// テクスチャ座標の設定
			float x = (float)(number % 10);
			g_vertexWkScore[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
			g_vertexWkScore[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
			g_vertexWkScore[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
			g_vertexWkScore[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
			number /= 10;
		}
	}

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureScore(void)
{
	int number = g_Score;

	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		// テクスチャ座標の設定
		float x = (float)(number % 10);
		g_vertexWkScore[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		g_vertexWkScore[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		g_vertexWkScore[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		g_vertexWkScore[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		number /= 10;
	}
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexScore(void)
{
	float habaX = RESULT_SCORE_SIZE_X;	// 数字の横幅

	// 桁数分処理する
	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		// 頂点座標の設定
		g_vertexWkScore[i][0].vtx.x = -habaX * i + RESULT_SCORE_POS_X;
		g_vertexWkScore[i][0].vtx.y = RESULT_SCORE_POS_Y;
		g_vertexWkScore[i][1].vtx.x = -habaX * i + RESULT_SCORE_POS_X + RESULT_SCORE_SIZE_X;
		g_vertexWkScore[i][1].vtx.y = RESULT_SCORE_POS_Y;
		g_vertexWkScore[i][2].vtx.x = -habaX * i + RESULT_SCORE_POS_X;
		g_vertexWkScore[i][2].vtx.y = RESULT_SCORE_POS_Y + RESULT_SCORE_SIZE_Y;
		g_vertexWkScore[i][3].vtx.x = -habaX * i + RESULT_SCORE_POS_X + RESULT_SCORE_SIZE_X;
		g_vertexWkScore[i][3].vtx.y = RESULT_SCORE_POS_Y + RESULT_SCORE_SIZE_Y;
	}
}

//=============================================================================
// スコア加算処理
//=============================================================================
void AddScore(int add)
{
	g_Score += add;

	SetTextureScore();
}