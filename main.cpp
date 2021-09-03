//=============================================================================
//
// Main処理 [main.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "title.h"
#include "result.h"
#include "timer.h"
#include "life.h"
#include "score.h"
#include "star.h"
#include "line.h"
#include "arrow.h"
#include "bg.h"
#include "grid.h"
#include "sound.h"
#include "select.h"
#include "load.h"
#include "check.h"
#include "combo.h"
#include <time.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME			_T("AppClass")			// ウインドウのクラス名
#define WINDOW_NAME			_T("GrandCross")		// ウインドウのキャプション名

//*****************************************************************************
// 構造体定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT Init(HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

void SetNote(void);

bool Title = false;
bool Result = false;

#ifdef _DEBUG
void DrawDebugFont(void);
#endif

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3D9				g_pD3D = NULL;				// Direct3Dオブジェクト
LPDIRECT3DDEVICE9		g_pD3DDevice = NULL;		// Deviceオブジェクト(描画に必要)

#ifdef _DEBUG
LPD3DXFONT				g_pD3DXFont = NULL;			// フォントへのポインタ
int						g_nCountFPS;				// FPSカウンタ
#endif
int						g_nStage = 0;				// ステージ番号
int						Old_nSrage;

int						g_Music;
int						s_Music;

LPDIRECTSOUNDBUFFER8	g_pBGM[BGM_MAX];						// BGM用バッファ
LPDIRECTSOUNDBUFFER8	g_pSE[SE_MAX];							// SE用バッファ

//=============================================================================
// メイン関数
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);		// 無くても良いけど、警告が出る（未使用宣言）

	// 時間計測用
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	WNDCLASSEX	wcex = {
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	HWND		hWnd;
	MSG			msg;

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// ウィンドウの作成
	hWnd = CreateWindow(CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,																		// ウィンドウの左座標
		CW_USEDEFAULT,																		// ウィンドウの上座標
		SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2,									// ウィンドウ横幅
		SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),	// ウィンドウ縦幅
		NULL,
		NULL,
		hInstance,
		NULL);

	// DirectXの初期化(ウィンドウを作成してから行う)
	if (FAILED(Init(hWnd, true)))
	{
		return -1;
	}

	// 入力処理の初期化
	InitInput(hInstance, hWnd);

	// フレームカウント初期化
	timeBeginPeriod(1);	// 分解能を設定
	dwExecLastTime = dwFPSLastTime = timeGetTime();	// システム時刻をミリ秒単位で取得
	dwCurrentTime = dwFrameCount = 0;

	// ウインドウの表示(Init()の後に呼ばないと駄目)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();					// システム時刻を取得

			if ((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5秒ごとに実行
			{
#ifdef _DEBUG
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);	// FPSを測定
#endif
				dwFPSLastTime = dwCurrentTime;				// FPSを測定した時刻を保存
				dwFrameCount = 0;							// カウントをクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))	// 1/60秒ごとに実行
			{
				dwExecLastTime = dwCurrentTime;	// 処理した時刻を保存

				Update();			// 更新処理
				Draw();				// 描画処理

				dwFrameCount++;		// 処理回数のカウントを加算
			}

			SetNote();
		}
	}

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// 終了処理
	Uninit();

	return (int)msg.wParam;
}

//=============================================================================
// プロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:					// [ESC]キーが押された
			DestroyWindow(hWnd);		// ウィンドウを破棄するよう指示する
			break;
		}
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init(HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	srand((unsigned)time(NULL));

	// Direct3Dオブジェクトの作成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ワークをゼロクリア
	d3dpp.BackBufferCount = 1;						// バックバッファの数
	d3dpp.BackBufferWidth = SCREEN_WIDTH;				// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;			// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;			// バックバッファのフォーマットは現在設定されているものを使う
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// 映像信号に同期してフリップする
	d3dpp.Windowed = bWindow;					// ウィンドウモード
	d3dpp.EnableAutoDepthStencil = TRUE;						// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;				// デプスバッファとして16bitを使う
	d3dpp.BackBufferFormat = d3ddm.Format;				// カラーモードの指定

	if (bWindow)
	{// ウィンドウモード
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;					// バックバッファ
		d3dpp.FullScreen_RefreshRateInHz = 0;								// リフレッシュレート
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// インターバル
	}
	else
	{// フルスクリーンモード
		d3dpp.BackBufferFormat = D3DFMT_R5G6B5;					// バックバッファ
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// リフレッシュレート
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル
	}

	// デバイスの生成
	// ディスプレイアダプタを表すためのデバイスを作成
	// 描画と頂点処理をハードウェアで行なう
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,							// ディスプレイアダプタ
		D3DDEVTYPE_HAL,								// ディスプレイタイプ
		hWnd,										// フォーカスするウインドウへのハンドル
		D3DCREATE_HARDWARE_VERTEXPROCESSING,		// デバイス作成制御の組み合わせ
		&d3dpp,										// デバイスのプレゼンテーションパラメータ
		&g_pD3DDevice)))							// デバイスインターフェースへのポインタ
	{
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// 描画と頂点処理をCPUで行なう
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				// 初期化失敗
				return E_FAIL;
			}
		}
	}

	// レンダリングステートパラメータの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// カリングを行わない
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

																			// サンプラーステートパラメータの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャＵ値の繰り返し設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャＶ値の繰り返し設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大時の補間設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小時の補間設定

#ifdef _DEBUG
																			// 情報表示用フォントを設定
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &g_pD3DXFont);
#endif

	// サウンド初期化
	InitSound(hWnd);
	// ロードと再生
	for (int i = 0; i < BGM_MAX; i++)
	{
		g_pBGM[i] = LoadSoundBGM(i);
	}

	for (int i = 0; i < SE_MAX; i++)
	{
		g_pSE[i] = LoadSoundSE(i);
	}

	// タイトル初期化
	InitTitle(0);

	// セレクト初期化
	InitSelect(0);

	// チェックの初期化
	InitCheck();

	// リザルト初期化
	InitResult(0);

	// ライフの初期化
	InitLife(0);

	// スコアの初期化
	InitScore(0);

	// スターの初期化
	InitStar(0);

	// ラインの初期化
	InitLine(0);
	
	// アロー初期化
	InitArrow(0);

	// 背景初期化
	InitBg(0);

	// グリッド初期化
	InitGrid(0);

	// ロード初期化
	InitLoad(0);

	// コンボ初期化
	InitCombo(0);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
	// 入力処理の終了処理
	UninitInput();

	// タイトル終了処理
	UninitTitle();

	// セレクト解放
	UninitSelect();

	// リザルト終了処理
	UninitResult();

	// ライフの終了処理
	UninitLife();

	// スコアの終了処理
	UninitScore();

	// スターの終了処理
	UninitStar();

	// ラインの終了処理
	UninitLine();

	// アロー解放
	UninitArrow();

	// 背景解放
	UninitBg();

	// グリッド解放
	UninitGrid();

	// コンボの終了処理
	UninitCombo();

	if (g_pD3DDevice != NULL)
	{// デバイスの開放
		g_pD3DDevice->Release();
	}

	if (g_pD3D != NULL)
	{// Direct3Dオブジェクトの開放
		g_pD3D->Release();
	}

	// サウンド処理の終了処理
	for (int i = 0; i < BGM_MAX; i++)
	{
		if (g_pBGM[i] != NULL)
		{
			g_pBGM[i]->Release();
			g_pBGM[i] = NULL;
		}
	}
	UninitSound();

}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	// 入力の更新処理
	UpdateInput();

	// 画面遷移
	switch (g_nStage)
	{
	case STAGE_TITLE:
		// タイトルの更新処理
		UpdateTitle();
		if (Title == false)
		{
			Result = false;
			Title = true;

			// 前画面の曲を止める
			StopSound(g_pBGM[BGM_RESULT], E_DS8_FLAG_NONE);
			// 次に使う曲の再生位置を一番最初に設定
			g_pBGM[BGM_TITLE]->SetCurrentPosition(0);
			// 再生		
			PlaySound(g_pBGM[BGM_TITLE], E_DS8_FLAG_LOOP);
		}
		break;

	case STAGE_SELECT:
		if (Title == true)
		{
			Title = false;

			// 前画面の曲を止める
			StopSound(g_pBGM[BGM_TITLE], E_DS8_FLAG_NONE);

			StartMusic();
		}

		// セレクト更新
		UpdateSelect();

		break;

	case STAGE_GAME:
		// チェックの更新処理
		UpdateCheck();

		// ライフの更新処理
		UpdateLife();

		// スコアの更新処理
		UpdateScore();

		// スターの更新処理
		UpdateStar();

		// ラインの更新処理
		UpdateLine();

		// アロー更新
		UpdateArrow();

		// 背景更新
		UpdateBg();

		// グリッド更新
		UpdateGrid();

		// ライフがなくならないでゲーム終了(仮)
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			SetVertexScore();
			SetTextureNo(0);
			SetStage(STAGE_RESULT);
		}

		break;

	case STAGE_RESULT:
		if (!Result)
		{
			// 前画面の曲を止める
			StopSound(g_pBGM[g_Music], E_DS8_FLAG_NONE);
			// 次に使う曲の再生位置を一番最初に設定
			g_pBGM[BGM_RESULT]->SetCurrentPosition(0);
			// 再生	
			PlaySound(g_pBGM[BGM_RESULT], E_DS8_FLAG_LOOP);

			Result = true;
		}

		// コンボの更新処理
		UpdateCombo();

		// リザルトの更新処理
		UpdateResult();	

		break;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	// バックバッファ＆Ｚバッファのクリア
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(128, 128, 255, 0), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		// 画面遷移
		switch (g_nStage)
		{
		case STAGE_TITLE:
			// タイトルの描画処理
			DrawTitle();
			break;
		case STAGE_SELECT:
			// セレクト描画
			DrawSelect();

			break;
		case STAGE_GAME:
			// 背景描画
			DrawBg();

			// ラインの描画処理
			DrawLine();

			// スターの描画処理
			DrawStar();

			// アロー描画
			DrawArrow();

			// グリッド描画
			DrawGrid();

			// ライフの描画処理
			DrawLife();

			// スコアの描画処理
			DrawScore();

			break;

		case STAGE_RESULT:
			// リザルトの描画処理
			DrawResult();

			// スコアの描画処理
			DrawScore();

			// コンボの描画処理
			DrawCombo();

			break;
		}

#ifdef _DEBUG
		// デバッグ表示
		DrawDebugFont();
#endif

		// Direct3Dによる描画の終了
		g_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void SetNote(void)
{
	switch (g_nStage)
	{
	case STAGE_GAME:
		CheakLoad();
		break;
	}
}

//=============================================================================
// デバイス取得関数
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return(g_pD3DDevice);
}


#ifdef _DEBUG
//=============================================================================
// デバッグ表示処理
//=============================================================================
void DrawDebugFont(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];

	// テキスト描画
	sprintf(str, _T("FPS:%d"), g_nCountFPS);
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	rect.top += 20;
	sprintf(str, _T("位置:%d"), GetPos(0));
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	rect.top += 20;
	sprintf(str, _T("タイミング:%f, %f, %f, %f, %f"), GetTiming(0), GetTiming(1), GetTiming(2), GetTiming(3), GetTiming(4));
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	rect.top += 20;
	sprintf(str, _T("時間:%f"), GetTime());
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	rect.top += 20;
	sprintf(str, _T("カウント:%d"), GetCount());
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	rect.top += 20;
	sprintf(str, _T("データ:%d"), GetData());
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	rect.top += 20;
	sprintf(str, _T("タイム:%d"), timeGetTime());
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	rect.top += 20;
	sprintf(str, _T("ラスト:%f"), GetLastTim());
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	rect.top += 20;
	sprintf(str, _T("テスター位置 X:%f テスター位置 Y:%f"), GetPosTest(0), GetPosTest(1));
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	rect.top += 20;
	sprintf(str, _T("スパノバ位置 X:%f"), GetSuperPos());
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	rect.top += 20;
	sprintf(str, _T("真ん中位置 X:%f"), GetSelectSuperPos());
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	rect.top += 20;
	sprintf(str, _T("ジャスト:%d"), GetJust());
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	rect.top += 20;
	sprintf(str, _T("グッド:%d"), GetGood());
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	rect.top += 20;
	sprintf(str, _T("ミス:%d"), GetMiss());
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif

//=============================================================================
// 画面遷移
//=============================================================================
void SetStage(int stage
)
{
	if( stage < 0 || stage >= STAGE_MAX ) return;

	g_nStage = stage;
}

//=============================================================================
// 再生する音楽
//=============================================================================
void SetMusic(int no)
{
	s_Music = no;
	g_Music = no;
}
//=============================================================================
// 再生する音楽の番号取得
//=============================================================================
int GetMusic()
{
	return g_Music;
}


//=============================================================================
// ゲームの再初期化処理処理
// 戻り値：無し
//=============================================================================
void InitGame(void)
{
	InitTitle(1);	// タイトルの再初期化
	InitResult(1);	// リザルトの再初期化
	InitCheck();	// チェックの再初期化
	InitLife(1);	// ライフの再初期化
	InitScore(1);	// スコアの再初期化
	InitStar(1);	// スターの再初期化
	InitLine(1);	// ラインの再初期化
	InitArrow(1);	// アローの再初期化
	InitSelect(1);	// セレクトの再初期化
	InitBg(1);		// 背景の再初期化
	InitGrid(1);	// グリッドの再初期化
	InitLoad(1);	// ロードの再初期化
	InitCombo(1);	// コンボの再初期化
}