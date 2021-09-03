//=============================================================================
//
// スコア処理 [timer.cpp]
//
//=============================================================================
#include "main.h"
#include "timer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexTimer(void);
void SetTextureTimer(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureTimer = NULL;		// テクスチャへのポリゴン
VERTEX_2D				g_vertexWkTimer[TIMER_DIGIT][NUM_VERTEX];	// 頂点情報格納ワーク

D3DXVECTOR3				g_posTimer;						// ポリゴンの移動量

int						g_nTimer;						// 残り時間
int						countTime;						// カウントダウン時間

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTimer(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_TIMER,				// ファイルの名前
			&g_pD3DTextureTimer);				// 読み込むメモリのポインタ
	}

	g_posTimer = D3DXVECTOR3((float)TIMER_POS_X, (float)TIMER_POS_Y, 0.0f);
	g_nTimer = TIMER_MAX;

	// 頂点情報の作成
	MakeVertexTimer();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTimer(void)
{
	if (g_pD3DTextureTimer != NULL)
	{	// テクスチャの開放
		g_pD3DTextureTimer->Release();
		g_pD3DTextureTimer = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTimer(void)
{
	// 毎フレーム実行される処理を記述する
	SetTextureTimer();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureTimer);

	// スコア
	for (int i = 0; i < TIMER_DIGIT; i++)
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTimer[i], sizeof(VERTEX_2D));
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexTimer(void)
{
	int i;
	float habaX = TEXTURE_TIMER_SIZE_X;	// 数字の横幅

	// 桁数分処理する
	for (i = 0; i < TIMER_DIGIT; i++)
	{
		// 頂点座標の設定
		g_vertexWkTimer[i][0].vtx.x = -habaX * i + g_posTimer.x;
		g_vertexWkTimer[i][0].vtx.y = g_posTimer.y;
		g_vertexWkTimer[i][0].vtx.z = 0.0f;
		g_vertexWkTimer[i][1].vtx.x = -habaX * i + g_posTimer.x + TEXTURE_TIMER_SIZE_X;
		g_vertexWkTimer[i][1].vtx.y = g_posTimer.y;
		g_vertexWkTimer[i][1].vtx.z = 0.0f;
		g_vertexWkTimer[i][2].vtx.x = -habaX * i + g_posTimer.x;
		g_vertexWkTimer[i][2].vtx.y = g_posTimer.y + TEXTURE_TIMER_SIZE_Y;
		g_vertexWkTimer[i][2].vtx.z = 0.0f;
		g_vertexWkTimer[i][3].vtx.x = -habaX * i + g_posTimer.x + TEXTURE_TIMER_SIZE_X;
		g_vertexWkTimer[i][3].vtx.y = g_posTimer.y + TEXTURE_TIMER_SIZE_Y;
		g_vertexWkTimer[i][3].vtx.z = 0.0f;

		// rhwの設定
		g_vertexWkTimer[i][0].rhw =
		g_vertexWkTimer[i][1].rhw =
		g_vertexWkTimer[i][2].rhw =
		g_vertexWkTimer[i][3].rhw = 1.0f;

		// 反射光の設定
		g_vertexWkTimer[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkTimer[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkTimer[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkTimer[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		g_vertexWkTimer[i][0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_vertexWkTimer[i][1].tex = D3DXVECTOR2(1.0f, 0.0f);
		g_vertexWkTimer[i][2].tex = D3DXVECTOR2(0.0f, 1.0f);
		g_vertexWkTimer[i][3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	return S_OK;
}
//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetTextureTimer(void)
{
	int i;
	int number = g_nTimer;

	for (i = 0; i < TIMER_DIGIT; i++)
	{
		// テクスチャ座標の設定
		float x = (float)(number % 10);
		g_vertexWkTimer[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		g_vertexWkTimer[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		g_vertexWkTimer[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		g_vertexWkTimer[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		number /= 10;
	}
}
//=============================================================================
// HPデータをセットする
// 引数:add :追加する点数。マイナスも可能、初期化などに。
//=============================================================================
void RedTimer(int red)
{
	g_nTimer = TIMER_MAX - red;

	if (g_nTimer < 0)
	{
		g_nTimer = TIMER_MIN;
	}
}

//=============================================================================
// タイム取得関数
//=============================================================================
int GetTimer(void)
{
	return g_nTimer;
}