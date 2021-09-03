//=============================================================================
//
// スコア処理 [load.h]
// Author : 
//
//=============================================================================
#ifndef _LOAD_H_
#define _LOAD_H_

// マクロ定義
#define		NOTE_MAX		(1024)		// ノーツの最大数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitLoad(int type);
void CheakLoad(void);

void LoadCSV(const char name[20]);
void SetStartTime(void);

int GetPos(int no);
float GetTiming(int no);
float GetTime(void);
int GetData(void);
int GetCount(void);
float GetLastTim(void);

#endif
