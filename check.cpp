//=============================================================================
//
// スコア処理 [load.cpp]
//
//=============================================================================
#include "main.h"
#include "sound.h"
#include "check.h"
#include "star.h"
#include "arrow.h"
#include "grid.h"
#include "score.h"
#include "life.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define		KEYBOARD_MAX		(18)
#define		SCORE_JUST			(0.0f)
#define		SCORE_GOOD			(10.0f)
#define		SCORE_MISS			(80.0f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
bool	CheckHit(D3DXVECTOR2 HitPos, D3DXVECTOR2 HitSize, D3DXVECTOR2 ArrowPos);
void	CheckScore(D3DXVECTOR2 StarPos, D3DXVECTOR2 ArrowPos);
bool	CheckHitBC(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
int g_aHitKeyboard[KEYBOARD_MAX] =
{
	DIK_W,
	DIK_E,
	DIK_R,
	DIK_T,
	DIK_Y,
	DIK_U,
	DIK_S,
	DIK_D,
	DIK_F,
	DIK_G,
	DIK_H,
	DIK_J,
	DIK_X,
	DIK_C,
	DIK_V,
	DIK_B,
	DIK_N,
	DIK_M,
};

int		g_nJust;
int		g_nGood;
int		g_nMiss;

//=============================================================================
// 初期化処理
//=============================================================================
void InitCheck(void)
{
	g_nJust = 0;
	g_nGood = 0;
	g_nMiss = 0;
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateCheck(void)
{
	for (int i = 0; i < KEYBOARD_MAX; i++)
	{
		if (GetKeyboardTrigger(g_aHitKeyboard[i]))
		{
			// 次に使う曲の再生位置を一番最初に設定
			g_pSE[SE_TAP]->SetCurrentPosition(0);
			// 再生		
			PlaySound(g_pSE[SE_TAP], E_DS8_FLAG_NONE);

			for (int j = 0; j < STAR_MAX; j++)
			{
				if (GetArrow(j))
				{
					if (i == GetStarPosNo(j))
					{
						//D3DXVECTOR2 pos = D3DXVECTOR2(HIT_POS_X, HIT_POS_Y);
						//D3DXVECTOR2 size = D3DXVECTOR2(HIT_SIZE_X + HIT_SIZE_X * i, HIT_SIZE_Y + HIT_SIZE_Y * i);

						//if (CheckHit(pos, size, GetArrowPos(j)))
						//{
							CheckScore(GetStarPos(j), GetArrowPos(j));
							ReleaseArrow(j);
						//}

						break;
					}
				}
			}
		}
	}
}

//=============================================================================
// 当たり判定
//=============================================================================
bool CheckHit(D3DXVECTOR2 HitPos, D3DXVECTOR2 HitSize, D3DXVECTOR2 ArrowPos)
{
	if (ArrowPos.x > HitPos.x && ArrowPos.y > HitPos.y && ArrowPos.x < HitPos.x + HitSize.x && ArrowPos.y < HitPos.y + HitSize.y)
	{
		return true;
	}
	return false;
}

//=============================================================================
// スコア加算判定
//=============================================================================
void CheckScore(D3DXVECTOR2 StarPos, D3DXVECTOR2 ArrowPos)
{
	if (!CheckHitBC(StarPos, ArrowPos, SCORE_MISS, 0.0f))
	{
	//	CalLife(-10);

		g_nMiss++;
	}
	else if (!CheckHitBC(StarPos, ArrowPos, SCORE_GOOD, 0.0f))
	{
		// 現在再生中のSEを停止
		StopSound(g_pSE[SE_TAP], E_DS8_FLAG_NONE);
		// 次に使う曲の再生位置を一番最初に設定
		g_pSE[SE_GOOD]->SetCurrentPosition(0);
		// 再生		
		PlaySound(g_pSE[SE_GOOD], E_DS8_FLAG_NONE);

		AddScore(10);

		g_nGood++;
	}
	else if (!CheckHitBC(StarPos, ArrowPos, SCORE_JUST, 0.0f))
	{
		// 現在再生中のSEを停止
		StopSound(g_pSE[SE_TAP], E_DS8_FLAG_NONE);
		// 次に使う曲の再生位置を一番最初に設定
		g_pSE[SE_JUST]->SetCurrentPosition(0);
		// 再生		
		PlaySound(g_pSE[SE_JUST], E_DS8_FLAG_NONE);

		AddScore(100);
		CalLife(1);

		g_nJust++;
	}
}

//=============================================================================
// タッチしないで消滅したとき
//=============================================================================
void MissScore(void)
{
//	CalLife(-10);

	g_nMiss++;
}

//=============================================================================
// ジャスト判定数取得関数
//=============================================================================
int GetJust(void)
{
	return g_nJust;
}

//=============================================================================
// グッド判定数取得関数
//=============================================================================
int GetGood(void)
{
	return g_nGood;
}

//=============================================================================
// ミス判定数取得関数
//=============================================================================
int GetMiss(void)
{
	return g_nMiss;
}

//=============================================================================
// BCによる当たり判定処理
// サイズは半径
// 戻り値：当たってたらtrue
//=============================================================================
bool CheckHitBC(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2)
{
	if ((size1 + size2) * (size1 + size2) >
		(pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y))
	{
		return true;
	}

	return false;
}
