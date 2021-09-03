//=============================================================================
//
// タイトル画面処理 [grid.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "grid.h"
#include "input.h"
#include "sound.h"
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexGrid(void);

#ifdef _DEBUG
void SetVertexGrid(void);
#endif

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureGrid = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureUi_NV = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureUi_DE = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureUi_DR = NULL;		// テクスチャへのポインタ

#ifdef _DEBUG
LPDIRECT3DTEXTURE9		g_pD3DTextureTest = NULL;		// テクスチャへのポインタ
#endif

VERTEX_2D				g_vertexWkGrid[NUM_VERTEX];			// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkUi_NV[NUM_VERTEX];			// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkUi_DE[NUM_VERTEX];			// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkUi_DR[NUM_VERTEX];			// 頂点情報格納ワーク

#ifdef _DEBUG
VERTEX_2D				g_vertexWkTest[NUM_VERTEX];			// 頂点情報格納ワーク

static D3DXVECTOR2 g_pos;
#endif
int						DrawMusicName = NULL;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitGrid(int type)
{
	if (type == 0)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
			TEXTURE_GRID,						// ファイルの名前
			&g_pD3DTextureGrid);				// 読み込むメモリー

		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
			TEXTURE_UI_NOVA,						// ファイルの名前
			&g_pD3DTextureUi_NV);				// 読み込むメモリー
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
			TEXTURE_UI_DEEP,						// ファイルの名前
			&g_pD3DTextureUi_DE);				// 読み込むメモリー
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
			TEXTURE_UI_DRAM,						// ファイルの名前
			&g_pD3DTextureUi_DR);				// 読み込むメモリー

#ifdef _DEBUG
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
			TEXTURE_TEST,						// ファイルの名前
			&g_pD3DTextureTest);				// 読み込むメモリー
#endif
	}

	// 頂点情報の作成
	MakeVertexGrid();

#ifdef _DEBUG
	g_pos = D3DXVECTOR2(HIT_POS_X, HIT_POS_Y);
#endif

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGrid(void)
{
	if (g_pD3DTextureGrid != NULL)
	{// テクスチャの開放
		g_pD3DTextureGrid->Release();
		g_pD3DTextureGrid = NULL;
	}
	if (g_pD3DTextureUi_NV != NULL)
	{// テクスチャの開放
		g_pD3DTextureUi_NV->Release();
		g_pD3DTextureUi_NV = NULL;
	}
	if (g_pD3DTextureUi_DE != NULL)
	{// テクスチャの開放
		g_pD3DTextureUi_DE->Release();
		g_pD3DTextureUi_DE = NULL;
	}
	if (g_pD3DTextureUi_DR != NULL)
	{// テクスチャの開放
		g_pD3DTextureUi_DR->Release();
		g_pD3DTextureUi_DR = NULL;
	}
#ifdef _DEBUG
	if (g_pD3DTextureTest != NULL)
	{// テクスチャの開放
		g_pD3DTextureTest->Release();
		g_pD3DTextureTest = NULL;
	}
#endif
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGrid(void)
{
#ifdef _DEBUG
	if (GetKeyboardPress(DIK_UP))
	{
		g_pos.y -= 0.5f;
	}
	else if (GetKeyboardPress(DIK_DOWN))
	{
		g_pos.y += 0.5f;
	}

	if (GetKeyboardPress(DIK_LEFT))
	{
		g_pos.x -= 0.5f;
	}
	else if (GetKeyboardPress(DIK_RIGHT))
	{
		g_pos.x += 0.5f;
	}
	SetVertexGrid();
#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGrid(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//	int mno;
//	GetMusic(mno);
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureGrid);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkGrid, sizeof(VERTEX_2D));
	
	if (GetMusic() == BGM_SUPERNOVA)
	{
		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureUi_NV);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkUi_NV, sizeof(VERTEX_2D));
	}

	if (GetMusic() == BGM_DEEPER)
	{
		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureUi_DE);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkUi_DE, sizeof(VERTEX_2D));
	}
	if (GetMusic() == BGM_DAYDRAEM)
	{
		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureUi_DR);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkUi_DR, sizeof(VERTEX_2D));
	}

#ifdef _DEBUG
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureTest);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTest, sizeof(VERTEX_2D));
#endif
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexGrid(void)
{
	// 頂点座標の設定
	g_vertexWkGrid[0].vtx = D3DXVECTOR3(GRID_POS_X, GRID_POS_Y, 0.0f);
	g_vertexWkGrid[1].vtx = D3DXVECTOR3(GRID_POS_X + GRID_SIZE_X, GRID_POS_Y, 0.0f);
	g_vertexWkGrid[2].vtx = D3DXVECTOR3(GRID_POS_X, GRID_POS_Y + GRID_SIZE_Y, 0.0f);
	g_vertexWkGrid[3].vtx = D3DXVECTOR3(GRID_POS_X + GRID_SIZE_X, GRID_POS_Y + GRID_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkGrid[0].rhw =
	g_vertexWkGrid[1].rhw =
	g_vertexWkGrid[2].rhw =
	g_vertexWkGrid[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkGrid[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkGrid[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkGrid[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkGrid[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkGrid[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkGrid[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkGrid[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkGrid[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点座標の設定
	g_vertexWkUi_NV[0].vtx = D3DXVECTOR3(UI_NOVA_POS_X, UI_NOVA_POS_Y, 0.0f);
	g_vertexWkUi_NV[1].vtx = D3DXVECTOR3(UI_NOVA_POS_X + UI_NOVA_SIZE_X, UI_NOVA_POS_Y, 0.0f);
	g_vertexWkUi_NV[2].vtx = D3DXVECTOR3(UI_NOVA_POS_X, UI_NOVA_POS_Y + UI_NOVA_SIZE_Y, 0.0f);
	g_vertexWkUi_NV[3].vtx = D3DXVECTOR3(UI_NOVA_POS_X + UI_NOVA_SIZE_X, UI_NOVA_POS_Y + UI_NOVA_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkUi_NV[0].rhw =
	g_vertexWkUi_NV[1].rhw =
	g_vertexWkUi_NV[2].rhw =
	g_vertexWkUi_NV[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkUi_NV[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkUi_NV[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkUi_NV[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkUi_NV[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkUi_NV[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkUi_NV[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkUi_NV[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkUi_NV[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点座標の設定
	g_vertexWkUi_DE[0].vtx = D3DXVECTOR3(UI_DEEP_POS_X, UI_DEEP_POS_Y, 0.0f);
	g_vertexWkUi_DE[1].vtx = D3DXVECTOR3(UI_DEEP_POS_X + UI_DEEP_SIZE_X, UI_DEEP_POS_Y, 0.0f);
	g_vertexWkUi_DE[2].vtx = D3DXVECTOR3(UI_DEEP_POS_X, UI_DEEP_POS_Y + UI_DEEP_SIZE_Y, 0.0f);
	g_vertexWkUi_DE[3].vtx = D3DXVECTOR3(UI_DEEP_POS_X + UI_DEEP_SIZE_X, UI_DEEP_POS_Y + UI_DEEP_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkUi_DE[0].rhw =
	g_vertexWkUi_DE[1].rhw =
	g_vertexWkUi_DE[2].rhw =
	g_vertexWkUi_DE[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkUi_DE[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkUi_DE[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkUi_DE[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkUi_DE[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkUi_DE[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkUi_DE[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkUi_DE[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkUi_DE[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点座標の設定
	g_vertexWkUi_DR[0].vtx = D3DXVECTOR3(UI_DEEP_POS_X, UI_DEEP_POS_Y, 0.0f);
	g_vertexWkUi_DR[1].vtx = D3DXVECTOR3(UI_DEEP_POS_X + UI_DEEP_SIZE_X, UI_DEEP_POS_Y, 0.0f);
	g_vertexWkUi_DR[2].vtx = D3DXVECTOR3(UI_DEEP_POS_X, UI_DEEP_POS_Y + UI_DEEP_SIZE_Y, 0.0f);
	g_vertexWkUi_DR[3].vtx = D3DXVECTOR3(UI_DEEP_POS_X + UI_DEEP_SIZE_X, UI_DEEP_POS_Y + UI_DEEP_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkUi_DR[0].rhw =
	g_vertexWkUi_DR[1].rhw =
	g_vertexWkUi_DR[2].rhw =
	g_vertexWkUi_DR[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkUi_DR[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkUi_DR[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkUi_DR[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkUi_DR[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkUi_DR[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkUi_DR[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkUi_DR[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkUi_DR[3].tex = D3DXVECTOR2(1.0f, 1.0f);

#ifdef _DEBUG
	// 頂点座標の設定
	g_vertexWkTest[0].vtx = D3DXVECTOR3(HIT_POS_X, HIT_POS_Y, 0.0f);
	g_vertexWkTest[1].vtx = D3DXVECTOR3(HIT_POS_X + HIT_SIZE_X, HIT_POS_Y, 0.0f);
	g_vertexWkTest[2].vtx = D3DXVECTOR3(HIT_POS_X, HIT_POS_Y + HIT_SIZE_Y, 0.0f);
	g_vertexWkTest[3].vtx = D3DXVECTOR3(HIT_POS_X + HIT_SIZE_X, HIT_POS_Y + HIT_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkTest[0].rhw =
	g_vertexWkTest[1].rhw =
	g_vertexWkTest[2].rhw =
	g_vertexWkTest[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkTest[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTest[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTest[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTest[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkTest[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkTest[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkTest[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkTest[3].tex = D3DXVECTOR2(1.0f, 1.0f);
#endif

	return S_OK;
}

#ifdef _DEBUG
//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexGrid(void)
{
	// 頂点座標の設定
	g_vertexWkTest[0].vtx = D3DXVECTOR3(g_pos.x, g_pos.y, 0.0f);
	g_vertexWkTest[1].vtx = D3DXVECTOR3(g_pos.x + HIT_SIZE_X, g_pos.y, 0.0f);
	g_vertexWkTest[2].vtx = D3DXVECTOR3(g_pos.x, g_pos.y + HIT_SIZE_Y, 0.0f);
	g_vertexWkTest[3].vtx = D3DXVECTOR3(g_pos.x + HIT_SIZE_X, g_pos.y + HIT_SIZE_Y, 0.0f);
}

//=============================================================================
// 頂点座標の取得
//=============================================================================
float GetPosTest(int type)
{
	if (type == 0)
	{
		return g_pos.x;
	}
	else
	{
		return g_pos.y;
	}
}
#endif