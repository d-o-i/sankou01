//=============================================================================
//
// タイトル画面処理 [combo.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "combo.h"
#include "select.h"
#include "check.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexCombo(void);
void SetTextureCombo(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureCombo = NULL;				// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureSupernova = NULL;			// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureSupernovaLogo = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureDeeper = NULL;				// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureDeeperLogo = NULL;			// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureDaydream = NULL;			// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureDaydreamLogo = NULL;		// テクスチャへのポインタ

VERTEX_2D				g_vertexWkJust[COMBO_DIGIT][NUM_VERTEX];		// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkGood[COMBO_DIGIT][NUM_VERTEX];		// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkMiss[COMBO_DIGIT][NUM_VERTEX];		// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkJacket[NUM_VERTEX];						// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkJacketLogo[NUM_VERTEX];					// 頂点情報格納ワーク

static bool Flag;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitCombo(int type)
{
	if (type == 0)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_COMBO,				// ファイルの名前
			&g_pD3DTextureCombo);		// 読み込むメモリー

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_RESULT_SUPERNOVA_JACKET,				// ファイルの名前
			&g_pD3DTextureSupernova);		// 読み込むメモリー

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_RESULT_SUPERNOVA_LOGO,				// ファイルの名前
			&g_pD3DTextureSupernovaLogo);		// 読み込むメモリー

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_RESULT_DEEPER_JACKET,				// ファイルの名前
			&g_pD3DTextureDeeper);		// 読み込むメモリー

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_RESULT_DEEPER_LOGO,				// ファイルの名前
			&g_pD3DTextureDeeperLogo);		// 読み込むメモリー
										
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_RESULT_DAYDREAM_JACKET,				// ファイルの名前
			&g_pD3DTextureDaydream);		// 読み込むメモリー

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_RESULT_DAYDREAM_LOGO,				// ファイルの名前
			&g_pD3DTextureDaydreamLogo);		// 読み込むメモリー
	}

	// 頂点情報の作成
	MakeVertexCombo();

	Flag = false;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitCombo(void)
{
	if (g_pD3DTextureCombo != NULL)
	{// テクスチャの開放
		g_pD3DTextureCombo->Release();
		g_pD3DTextureCombo = NULL;
	}

	if (g_pD3DTextureSupernova != NULL)
	{// テクスチャの開放
		g_pD3DTextureSupernova->Release();
		g_pD3DTextureSupernova = NULL;
	}

	if (g_pD3DTextureSupernovaLogo != NULL)
	{// テクスチャの開放
		g_pD3DTextureSupernovaLogo->Release();
		g_pD3DTextureSupernovaLogo = NULL;
	}

	if (g_pD3DTextureDeeper != NULL)
	{// テクスチャの開放
		g_pD3DTextureDeeper->Release();
		g_pD3DTextureDeeper = NULL;
	}

	if (g_pD3DTextureDeeperLogo != NULL)
	{// テクスチャの開放
		g_pD3DTextureDeeperLogo->Release();
		g_pD3DTextureDeeperLogo = NULL;
	}

	if (g_pD3DTextureDaydream != NULL)
	{// テクスチャの開放
		g_pD3DTextureDaydream->Release();
		g_pD3DTextureDaydream = NULL;
	}

	if (g_pD3DTextureDaydreamLogo != NULL)
	{// テクスチャの開放
		g_pD3DTextureDaydreamLogo->Release();
		g_pD3DTextureDaydreamLogo = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateCombo()
{
	if (!Flag)
	{
		SetTextureCombo();
		Flag = true;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawCombo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureCombo);

	// ジャスト判定の桁数分描画
	for (int i = 0; i < COMBO_DIGIT; i++)
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkJust[i], sizeof(VERTEX_2D));
	}

	// グッド判定の桁数分描画
	for (int i = 0; i < COMBO_DIGIT; i++)
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkGood[i], sizeof(VERTEX_2D));
	}

	// ミス判定の桁数分描画
	for (int i = 0; i < COMBO_DIGIT; i++)
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkMiss[i], sizeof(VERTEX_2D));
	}

	// 音楽のジャケット・ロゴの描画

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	switch (GetSelectNo())
	{
	case 0:
		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureSupernova);
		break;
	case 1:
		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureDeeper);
		break;
	case 2:
		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureDaydream);
		break;
	}

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkJacket, sizeof(VERTEX_2D));


	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	switch (GetSelectNo())
	{
	case 0:
		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureSupernovaLogo);
		break;
	case 1:
		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureDeeperLogo);
		break;
	case 2:
		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureDaydreamLogo);
		break;
	}

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkJacketLogo, sizeof(VERTEX_2D));
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexCombo(void)
{
	float habaX = COMBO_SIZE_X;	// 数字の横幅
	int number;

	// ジャスト判定数を桁数分処理する

	// ジャスト判定数表示
	number = GetJust();

	for (int i = 0; i < COMBO_DIGIT; i++)
	{
		// 頂点座標の設定
		g_vertexWkJust[i][0].vtx.x = -habaX * i + COMBO_JUST_POS_X;
		g_vertexWkJust[i][0].vtx.y = COMBO_JUST_POS_Y;
		g_vertexWkJust[i][1].vtx.x = -habaX * i + COMBO_JUST_POS_X + COMBO_SIZE_X;
		g_vertexWkJust[i][1].vtx.y = COMBO_JUST_POS_Y;
		g_vertexWkJust[i][2].vtx.x = -habaX * i + COMBO_JUST_POS_X;
		g_vertexWkJust[i][2].vtx.y = COMBO_JUST_POS_Y + COMBO_SIZE_Y;
		g_vertexWkJust[i][3].vtx.x = -habaX * i + COMBO_JUST_POS_X + COMBO_SIZE_X;
		g_vertexWkJust[i][3].vtx.y = COMBO_JUST_POS_Y + COMBO_SIZE_Y;

		// rhwの設定
		g_vertexWkJust[i][0].rhw =
		g_vertexWkJust[i][1].rhw =
		g_vertexWkJust[i][2].rhw =
		g_vertexWkJust[i][3].rhw = 1.0f;

		// 反射光の設定
		g_vertexWkJust[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkJust[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkJust[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkJust[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		float x = (float)(number % 10);
		g_vertexWkJust[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		g_vertexWkJust[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		g_vertexWkJust[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		g_vertexWkJust[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		number /= 10;
	}

	// グッド判定数を桁数分処理する

	// グッド判定数表示
	number = GetGood();

	for (int i = 0; i < COMBO_DIGIT; i++)
	{
		// 頂点座標の設定
		g_vertexWkGood[i][0].vtx.x = -habaX * i + COMBO_GOOD_POS_X;
		g_vertexWkGood[i][0].vtx.y = COMBO_GOOD_POS_Y;
		g_vertexWkGood[i][1].vtx.x = -habaX * i + COMBO_GOOD_POS_X + COMBO_SIZE_X;
		g_vertexWkGood[i][1].vtx.y = COMBO_GOOD_POS_Y;
		g_vertexWkGood[i][2].vtx.x = -habaX * i + COMBO_GOOD_POS_X;
		g_vertexWkGood[i][2].vtx.y = COMBO_GOOD_POS_Y + COMBO_SIZE_Y;
		g_vertexWkGood[i][3].vtx.x = -habaX * i + COMBO_GOOD_POS_X + COMBO_SIZE_X;
		g_vertexWkGood[i][3].vtx.y = COMBO_GOOD_POS_Y + COMBO_SIZE_Y;

		// rhwの設定
		g_vertexWkGood[i][0].rhw =
		g_vertexWkGood[i][1].rhw =
		g_vertexWkGood[i][2].rhw =
		g_vertexWkGood[i][3].rhw = 1.0f;

		// 反射光の設定
		g_vertexWkGood[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkGood[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkGood[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkGood[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		float x = (float)(number % 10);
		g_vertexWkGood[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		g_vertexWkGood[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		g_vertexWkGood[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		g_vertexWkGood[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		number /= 10;
	}

	// ミス判定数を桁数分処理する

	// ミス判定数表示
	number = GetMiss();

	for (int i = 0; i < COMBO_DIGIT; i++)
	{
		// 頂点座標の設定
		g_vertexWkMiss[i][0].vtx.x = -habaX * i + COMBO_MISS_POS_X;
		g_vertexWkMiss[i][0].vtx.y = COMBO_MISS_POS_Y;
		g_vertexWkMiss[i][1].vtx.x = -habaX * i + COMBO_MISS_POS_X + COMBO_SIZE_X;
		g_vertexWkMiss[i][1].vtx.y = COMBO_MISS_POS_Y;
		g_vertexWkMiss[i][2].vtx.x = -habaX * i + COMBO_MISS_POS_X;
		g_vertexWkMiss[i][2].vtx.y = COMBO_MISS_POS_Y + COMBO_SIZE_Y;
		g_vertexWkMiss[i][3].vtx.x = -habaX * i + COMBO_MISS_POS_X + COMBO_SIZE_X;
		g_vertexWkMiss[i][3].vtx.y = COMBO_MISS_POS_Y + COMBO_SIZE_Y;

		// rhwの設定
		g_vertexWkMiss[i][0].rhw =
		g_vertexWkMiss[i][1].rhw =
		g_vertexWkMiss[i][2].rhw =
		g_vertexWkMiss[i][3].rhw = 1.0f;

		// 反射光の設定
		g_vertexWkMiss[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkMiss[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkMiss[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkMiss[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		float x = (float)(number % 10);
		g_vertexWkMiss[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		g_vertexWkMiss[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		g_vertexWkMiss[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		g_vertexWkMiss[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		number /= 10;
	}

	// 頂点座標の設定
	g_vertexWkJacket[0].vtx = D3DXVECTOR3(COMBO_JACKET_POS_X, COMBO_JACKET_POS_Y, 0.0f);
	g_vertexWkJacket[1].vtx = D3DXVECTOR3(COMBO_JACKET_POS_X + COMBO_JACKET_SIZE_X, COMBO_JACKET_POS_Y, 0.0f);
	g_vertexWkJacket[2].vtx = D3DXVECTOR3(COMBO_JACKET_POS_X, COMBO_JACKET_POS_Y + COMBO_JACKET_SIZE_Y, 0.0f);
	g_vertexWkJacket[3].vtx = D3DXVECTOR3(COMBO_JACKET_POS_X + COMBO_JACKET_SIZE_X, COMBO_JACKET_POS_Y + COMBO_JACKET_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkJacket[0].rhw =
	g_vertexWkJacket[1].rhw =
	g_vertexWkJacket[2].rhw =
	g_vertexWkJacket[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkJacket[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkJacket[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkJacket[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkJacket[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkJacket[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkJacket[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkJacket[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkJacket[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	// 頂点座標の設定
	g_vertexWkJacketLogo[0].vtx = D3DXVECTOR3(COMBO_LOGO_POS_X, COMBO_LOGO_POS_Y, 0.0f);
	g_vertexWkJacketLogo[1].vtx = D3DXVECTOR3(COMBO_LOGO_POS_X + COMBO_LOGO_SIZE_X, COMBO_LOGO_POS_Y, 0.0f);
	g_vertexWkJacketLogo[2].vtx = D3DXVECTOR3(COMBO_LOGO_POS_X, COMBO_LOGO_POS_Y + COMBO_LOGO_SIZE_Y, 0.0f);
	g_vertexWkJacketLogo[3].vtx = D3DXVECTOR3(COMBO_LOGO_POS_X + COMBO_LOGO_SIZE_X, COMBO_LOGO_POS_Y + COMBO_LOGO_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkJacketLogo[0].rhw =
	g_vertexWkJacketLogo[1].rhw =
	g_vertexWkJacketLogo[2].rhw =
	g_vertexWkJacketLogo[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkJacketLogo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkJacketLogo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkJacketLogo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkJacketLogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkJacketLogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkJacketLogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkJacketLogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkJacketLogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureCombo(void)
{
	int number;

	// ジャスト判定数を桁数分処理する

	// ジャスト判定数表示
	number = GetJust();

	for (int i = 0; i < COMBO_DIGIT; i++)
	{
		// テクスチャ座標の設定
		float x = (float)(number % 10);
		g_vertexWkJust[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		g_vertexWkJust[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		g_vertexWkJust[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		g_vertexWkJust[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		number /= 10;
	}

	// グッド判定数を桁数分処理する

	// グッド判定数表示
	number = GetGood();

	for (int i = 0; i < COMBO_DIGIT; i++)
	{
		// テクスチャ座標の設定
		float x = (float)(number % 10);
		g_vertexWkGood[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		g_vertexWkGood[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		g_vertexWkGood[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		g_vertexWkGood[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		number /= 10;
	}

	// ミス判定数を桁数分処理する

	// ミス判定数表示
	number = GetMiss();

	for (int i = 0; i < COMBO_DIGIT; i++)
	{
		// テクスチャ座標の設定
		float x = (float)(number % 10);
		g_vertexWkMiss[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		g_vertexWkMiss[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		g_vertexWkMiss[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		g_vertexWkMiss[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		number /= 10;
	}
}