//=============================================================================
//
// モデル処理 [model.cpp]
// Author : 
//
//=============================================================================
#include "model.h"
#include "input.h"

//*****************************************************************************

/*
1) ball.xとすたふぃー.ddsとカービー.ddsをコピーする

main.cpp
#define WINDOW_NAME		"学籍番号　クラス　出席番号　氏名"　　を変更

model.cpp
2) 適当にカメラやモデルの位置を調整
3）LPDIRECT3DTEXTURE9	g_pD3DTextureModel2;を追加

マクロ定義関連
#define	MODEL_CAR		"data/MODEL/ball.x"						// 読み込むモデル名
#define TEXTURE_FILENAME2	"data/TEXTURE/すたふぃー.dds"		// ファイルの名前
#define TEXTURE_FILENAME	"data/TEXTURE/カービー.dds"		// ファイルの名前
#define	VIEW_NEAR_Z		(1.0f)に変更

InitModel(void)内の変更
4）	D3DXCreateTextureFromFile(pDevice,					
　　　　TEXTURE_FILENAME2,		// ファイルの名前
		&g_pD3DTextureModel2);	// 読み込むメモリー　を追加

5）マルチテクスチャ設定を追加

DrawModel(void)内の変更
6）	pDevice->SetTexture(1, g_pD3DTextureModel2);を追加
7）	pDevice->SetTexture(1, NULL)を追加;

確認出来たらテクスチャを変更してみる
αテクスチャはサンプルノンノでもOK
デフューズテクスチャを適当に変更


*/





// マクロ定義
//*****************************************************************************
#define	MODEL_CAR		"data/MODEL/ball.x"						// 読み込むモデル名
#define TEXTURE_FILENAME2	"data/TEXTURE/すたふぃー.dds"		// ファイルの名前
#define TEXTURE_FILENAME	"data/TEXTURE/Rock_Normal.bmp"		// ファイルの名前


#define	POS_CAMERA_P_X	(0.0f)											// カメラ視点の初期位置(X座標)
#define	POS_CAMERA_P_Y	(15.0f)											// カメラ視点の初期位置(Y座標)
#define	POS_CAMERA_P_Z	(-3.0f)										// カメラ視点の初期位置(Z座標)

#define	VIEW_ANGLE		(D3DXToRadian(45.0f))							// ビュー平面の視野角
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比	
#define	VIEW_NEAR_Z		(1.0f)											// ビュー平面のNearZ値
#define	VIEW_FAR_Z		(1000.0f)										// ビュー平面のFarZ値

#define	VALUE_MOVE		(5.0f)											// 移動量
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)								// 回転量

#define	NUM_LIGHT		(3)												// ライトの数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitCamera(void);
void InitLight(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTextureModel;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9	g_pD3DTextureModel2;		// テクスチャへのポインタ
LPD3DXMESH			g_pD3DXMeshModel;		// メッシュ情報へのポインタ
LPD3DXBUFFER		g_pD3DXBuffMatModel;	// マテリアル情報へのポインタ
DWORD				g_nNumMatModel;			// マテリアル情報の数

D3DXVECTOR3			g_posModel;				// モデルの位置
D3DXVECTOR3			g_rotModel;				// モデルの向き(回転)
D3DXVECTOR3			g_sclModel;				// モデルの大きさ(スケール)

D3DXVECTOR3			g_posCameraP;			// カメラの視点
D3DXVECTOR3			g_posCameraR;			// カメラの注視点
D3DXVECTOR3			g_vecCameraU;			// カメラの上方向ベクトル

D3DXMATRIX			g_mtxView;				// ビューマトリックス
D3DXMATRIX			g_mtxProjection;		// プロジェクションマトリックス
D3DXMATRIX			g_mtxWorld;				// ワールドマトリックス

D3DLIGHT9			g_aLight[NUM_LIGHT];	// ライト情報


//===================================================================================
//シェーダー回りグローバル変数
//===================================================================================
LPDIRECT3DVERTEXSHADER9 g_VertexShader = nullptr;			// 頂点シェーダー
LPD3DXCONSTANTTABLE		g_VSConstantTable = nullptr;		// 定数テーブル

LPDIRECT3DPIXELSHADER9	g_PixelShader = nullptr;			// ピクセルシェーダー
LPD3DXCONSTANTTABLE		g_PSConstantTable = nullptr;		// 定数テーブル



//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// カメラの初期化
	InitCamera();

	// ライトの初期化
	InitLight();

	// 位置・回転・スケールの初期設定
	g_posModel = D3DXVECTOR3(0.0f, 15.0f, 0.0f);
	g_rotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_sclModel = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	g_pD3DTextureModel = NULL;
	g_pD3DXMeshModel = NULL;
	g_pD3DXBuffMatModel = NULL;
	g_nNumMatModel = 0;
	
	D3DVERTEXELEMENT9 decl[] =
	{
		{0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0},
		{0,12,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,0},
		{0,20,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_NORMAL,0},
		{0,32,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TANGENT,0},
		{0,44,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_BINORMAL,0},
		D3DDECL_END()
	};

	LPD3DXMESH mesh;
	 //Xファイルの読み込み
	if(FAILED(D3DXLoadMeshFromX(MODEL_CAR,				// 読み込むモデルファイル名(Xファイル)
								D3DXMESH_SYSTEMMEM,		// メッシュの作成オプションを指定
								pDevice,				// IDirect3DDevice9インターフェイスへのポインタ
								NULL,					// 隣接性データを含むバッファへのポインタ
								&g_pD3DXBuffMatModel,	// マテリアルデータを含むバッファへのポインタ
								NULL,					// エフェクトインスタンスの配列を含むバッファへのポインタ
								&g_nNumMatModel,		// D3DXMATERIAL構造体の数
								&mesh)))	// ID3DXMeshインターフェイスへのポインタのアドレス
	{
		return E_FAIL;
	}

	mesh->CloneMesh(D3DXMESH_SYSTEMMEM, decl, pDevice, &g_pD3DXMeshModel);
	mesh->Release();
	D3DXComputeTangent(g_pD3DXMeshModel, 0, 0, 0, 0, NULL);

#if 1
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
								TEXTURE_FILENAME,		// ファイルの名前
								&g_pD3DTextureModel);	// 読み込むメモリー
#endif
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
		TEXTURE_FILENAME2,		// ファイルの名前
		&g_pD3DTextureModel2);	// 読み込むメモリー




		//カリング
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//αテストの設定
	pDevice->SetRenderState(D3DRS_ALPHAREF, 255);

	//α値がalpharef以上のピクセルは描画
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

	//αブレンド設定（半透明）
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	//マルチテクスチャの設定
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);


	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);//ARG2の設定を使う
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_CURRENT);//ARG1はカレント色
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);//ARG2はテクスチャ

	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);//ARG2の設定を使う
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);//ARG2はカレント色


	pDevice->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 0);	//UV座標は0番目を使う

	pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_BLENDTEXTUREALPHA);//ARG1とARG2をαブレンドする
	pDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);//ARG1はSTAGE1からの出力色
	pDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);//ARG2はステージ1のテクスチャ

	pDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
	pDevice->SetTextureStageState(1, D3DTSS_ALPHAARG1, D3DTA_CURRENT);
	pDevice->SetTextureStageState(1, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);


//	pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);//STAGE1は未使用


	//==========================================================
	//シェーダー回り追加
	//==========================================================
	LPD3DXBUFFER err = NULL;
	LPD3DXBUFFER code = NULL;
	HRESULT hr;


	//頂点シェーダをコンパイル&作成
	hr = D3DXCompileShaderFromFile("basic2.fx",		// ファイル名
		nullptr,		// プリプロセッサ定義へのポインタ 
		nullptr,		// ID3DXInclude（#include疑似命令）
		"VS",			// 頂点シェーダー関数名 
		"vs_3_0",		// 頂点シェーダーのバージョン 
		0,				// コンパイルオプション
		&code,			// コンパイル済みのシェーダーコード（OUT）
		&err,			// コンパイルエラー情報が格納される（OUT）
		&g_VSConstantTable);	// シェーダー内のコンスタントテーブル（OUT）
	// エラー発生
	if (FAILED(hr))
	{
		if (err) {
			// コンパイルエラーあり
			MessageBox(NULL, (LPSTR)err->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
		}
		else {
			// その他のエラー
			MessageBox(NULL, "シェーダーファイルが読見み込めません", "D3DXCompileShaderFromFile", MB_OK);
		}
		return false;
	}
	// 頂点シェーダーオブジェクトを作成する
	hr = pDevice->CreateVertexShader((DWORD*)code->GetBufferPointer(), &g_VertexShader);
	if (FAILED(hr))
	{
		MessageBox(NULL, (LPSTR)err->GetBufferPointer(), "CreateVertexShader", MB_OK);
		return false;
	}

	//ピクセルシェーダをコンパイル&作成
	hr = D3DXCompileShaderFromFile("basic2.fx",		// ファイル名
		nullptr,		// プリプロセッサ定義へのポインタ 
		nullptr,		// ID3DXInclude（#include疑似命令）
		"PS",			// 頂点シェーダー関数名 
		"ps_3_0",		// 頂点シェーダーのバージョン 
		0,				// コンパイルオプション
		&code,			// コンパイル済みのシェーダーコード（OUT）
		&err,			// コンパイルエラー情報が格納される（OUT）
		&g_PSConstantTable);	// シェーダー内のコンスタントテーブル（OUT）
	// エラー発生
	if (FAILED(hr))
	{
		if (err) {
			// コンパイルエラーあり
			MessageBox(NULL, (LPSTR)err->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
		}
		else {
			// その他のエラー
			MessageBox(NULL, "シェーダーファイルが読見み込めません", "D3DXCompileShaderFromFile", MB_OK);
		}
		return false;
	}
	// コンパイル済みコードからピクセルシェーダーオブジェクトを作成する
	hr = pDevice->CreatePixelShader((DWORD*)code->GetBufferPointer(), &g_PixelShader);
	if (FAILED(hr))
	{
		MessageBox(NULL, (LPSTR)err->GetBufferPointer(), "CreatePixelShader", MB_OK);
		return false;
	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitModel(void)
{
	if(g_pD3DTextureModel != NULL)
	{// テクスチャの開放
		g_pD3DTextureModel->Release();
		g_pD3DTextureModel = NULL;
	}

	if(g_pD3DXMeshModel != NULL)
	{// メッシュの開放
		g_pD3DXMeshModel->Release();
		g_pD3DXMeshModel = NULL;
	}

	if(g_pD3DXBuffMatModel != NULL)
	{// マテリアルの開放
		g_pD3DXBuffMatModel->Release();
		g_pD3DXBuffMatModel = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateModel(void)
{

	g_rotModel.y += D3DXToRadian( 1.0f );
	g_rotModel.z += D3DXToRadian(  0.5f );

}

//=============================================================================
// 描画処理
//=============================================================================

void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxView);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_mtxView, 
						&g_posCameraP,		// カメラの視点
						&g_posCameraR,		// カメラの注視点
						&g_vecCameraU);		// カメラの上方向ベクトル

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_mtxView);


	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxProjection);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&g_mtxProjection,
								VIEW_ANGLE,			// ビュー平面の視野角
								VIEW_ASPECT,		// ビュー平面のアスペクト比
								VIEW_NEAR_Z,		// ビュー平面のNearZ値
								VIEW_FAR_Z);		// ビュー平面のFarZ値

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_mtxProjection);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorld);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, g_sclModel.x, g_sclModel.y, g_sclModel.z);
	D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotModel.y, g_rotModel.x, g_rotModel.z);
	D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, g_posModel.x, g_posModel.y, g_posModel.z);
	D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);

	//
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);


	//==================================================================
	//シェーダー回り追加
	//==================================================================
		// 頂点シェーダーとピクセルシェーダーをセット
	pDevice->SetVertexShader(g_VertexShader);
	pDevice->SetPixelShader(g_PixelShader);

	// 定数をセット
	g_VSConstantTable->SetMatrix(pDevice, "g_world", &g_mtxWorld);
	g_VSConstantTable->SetMatrix(pDevice, "g_view", &g_mtxView);
	g_VSConstantTable->SetMatrix(pDevice, "g_projection", &g_mtxProjection);

	D3DXMATRIX invMatrix;
	D3DXMatrixInverse(&invMatrix, NULL, &g_mtxWorld);

	D3DXVECTOR3 lv = D3DXVECTOR3(0.5f, 0.7f, 0.6f);
	D3DXVECTOR4 Light;
	D3DXVec3TransformNormal(&lv, &lv, &invMatrix);
	Light.x = lv.x;
	Light.y = lv.y;
	Light.z = lv.z;
	Light.w = 0;
	g_VSConstantTable->SetVector(pDevice, "g_light", &Light);

	////光のベクトル
	//D3DXVECTOR4	Light = D3DXVECTOR4(0.5f, 0.0f, 1.0f, 0.0f);
	//g_PSConstantTable->SetVector(pDevice, "g_light", &Light);
	//カメラの位置

	D3DXVECTOR3 cv = D3DXVECTOR3(g_posCameraP.x, g_posCameraP.y, g_posCameraP.z);
	D3DXVECTOR4	Camera = D3DXVECTOR4(g_posCameraP.x, g_posCameraP.y, g_posCameraP.z, 0);
	D3DXVec3Transform(&Camera, &cv, &invMatrix);
	g_VSConstantTable->SetVector(pDevice, "g_Camera", &Camera);


	//=================================================
	// サンプラーステートパラメータの設定
	int	stage = g_PSConstantTable->GetSamplerIndex("Sampler0");	//サンプラーインデックスを取得
	int	stage2 = g_PSConstantTable->GetSamplerIndex("Sampler1");	//サンプラーインデックスを取得

	pDevice->SetSamplerState(stage, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	pDevice->SetSamplerState(stage, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
	pDevice->SetSamplerState(stage, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小フィルタモードを設定
	pDevice->SetSamplerState(stage, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大フィルタモードを設定

	pDevice->SetSamplerState(stage2, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	pDevice->SetSamplerState(stage2, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
	pDevice->SetSamplerState(stage2, D3DSAMP_MINFILTER, D3DTEXF_POINT);	// テクスチャ縮小フィルタモードを設定
	pDevice->SetSamplerState(stage2, D3DSAMP_MAGFILTER, D3DTEXF_POINT);	// テクスチャ拡大フィルタモードを設定


	//=================================================


	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアル情報に対するポインタを取得
	pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatModel->GetBufferPointer();

	for(int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

		// テクスチャの設定
		pDevice->SetTexture(stage2, g_pD3DTextureModel);
		pDevice->SetTexture(stage, g_pD3DTextureModel2);

		// 描画
		g_pD3DXMeshModel->DrawSubset(nCntMat);
	}


	pDevice->SetTexture(1, NULL);


	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);

	//==================================================================
	//シェーダー回り追加
	//==================================================================
	// 頂点シェーダーとピクセルシェーダーをデフォルトへ
	pDevice->SetVertexShader(NULL);
	pDevice->SetPixelShader(NULL);



}

//=============================================================================
// カメラの初期化処理
//=============================================================================
void InitCamera(void)
{
	g_posCameraP = D3DXVECTOR3(POS_CAMERA_P_X, POS_CAMERA_P_Y, POS_CAMERA_P_Z);
	g_posCameraR = D3DXVECTOR3(POS_CAMERA_P_X, POS_CAMERA_P_Y, 0.0f);
	g_vecCameraU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}

//=============================================================================
// ライトの初期化処理
//=============================================================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 vecDir;

	// D3DLIGHT9構造体を0でクリアする
	ZeroMemory(&g_aLight[0], sizeof(D3DLIGHT9));

	// ライト0のタイプの設定
	g_aLight[0].Type = D3DLIGHT_DIRECTIONAL;

	// ライト0の拡散光の設定
	g_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ライト0の環境光の設定
	g_aLight[0].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ライト0の方向の設定
	vecDir = D3DXVECTOR3(-0.0f, -0.6f, -1.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[0].Direction, &vecDir);

	// ライト0をレンダリングパイプラインに設定
	pDevice->SetLight(0, &g_aLight[0]);

	// ライト0を使用使用状態に
	pDevice->LightEnable(0, TRUE);


	// D3DLIGHT9構造体を0でクリアする
	ZeroMemory(&g_aLight[1], sizeof(D3DLIGHT9));

	// ライト1のタイプの設定
	g_aLight[1].Type = D3DLIGHT_DIRECTIONAL;

	// ライト1の拡散光の設定
	g_aLight[1].Diffuse = D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f);

	// ライト1の環境光の設定
	g_aLight[1].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

    // ライト1の方向の設定
	vecDir = D3DXVECTOR3(-0.0f, -1.0f, 0.8f);
	D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[1].Direction, &vecDir);

	// ライト1をレンダリングパイプラインに設定
	pDevice->SetLight(1, &g_aLight[1]);

	// ライト1の設定
	pDevice->LightEnable(1, TRUE);

	// ライティングモードをON
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

