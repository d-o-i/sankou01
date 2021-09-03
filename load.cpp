//=============================================================================
//
// スコア処理 [load.cpp]
//
//=============================================================================
#include "main.h"
#include "load.h"
#include "star.h"
#include <time.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int					g_StartTime;						// 音楽の開始時間
static float				g_Time;								// 音楽の時間
static float				g_Timing[NOTE_MAX];					// ノーツのタイミング
static int					g_Pos[NOTE_MAX];					// ノーツの位置
static int					g_count;							// カウント
static int					g_Data;								// CSVファイルのデータ数

//=============================================================================
// 初期化処理
//=============================================================================
void InitLoad(int type)
{
	if (type == 0)
	{
		for (int i = 0; i < NOTE_MAX; i++)
		{
			g_Timing[i] = 0.0f;
			g_Pos[i] = -1;
		}
		g_Data = 0;
	}
	g_count = 0;
}

//=============================================================================
// 更新処理
//=============================================================================
void CheakLoad(void)
{
	if (g_count < g_Data)
	{
		g_Time = (float)(timeGetTime() - g_StartTime) / 1000;

		for (int i = 0; i < STAR_MAX; i++)
		{
			if (g_Timing[g_count] <= g_Time)
			{
				if (g_count < g_Data)
				{
					SetStar(g_Pos[g_count]);
					g_count++;
				}
			}
		}
	}
}

//=============================================================================
// csvファイルの読み込み
//=============================================================================
void LoadCSV(const char name[20])
{
	FILE *fp;
	char fname[30];
	sprintf(fname, "data/CSV/%s.csv", name);

	fp = fopen(fname, "r");

	if (fp != NULL)
	{
		for (int i = 0; i < NOTE_MAX; i++)
		{
			fscanf(fp, "%f,%d\n", &g_Timing[i], &g_Pos[i]);

			if (g_Pos[i] == EOF)
			{
				g_Data = i;

				fclose(fp);
				return;
			}
		}
	}

	fclose(fp);
}

//=============================================================================
// 音楽の開始時間の保存
//=============================================================================
void SetStartTime(void)
{
	g_StartTime = timeGetTime();
}

int GetPos(int no)
{
	return g_Pos[no];
}

float GetTiming(int no)
{
	return g_Timing[no];
}

float GetTime(void)
{
	return g_Time;
}

int GetData(void)
{
	return g_Data;
}

int GetCount(void)
{
	return g_count;
}
float GetLastTim(void)
{
	return g_Timing[g_Data];
}