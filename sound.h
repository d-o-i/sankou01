#ifndef ___SOUND_H___
#define ___SOUND_H___

#include <windows.h>
#include <tchar.h>
#include <dsound.h>
#include <dmusics.h>
#include <mmsystem.h>
#include <comdef.h>
// マクロ定義

enum
{	// サウンド通しナンバー
	BGM_TITLE,
	BGM_SUPERNOVA,
	BGM_DEEPER,
	BGM_DAYDRAEM,
	BGM_RESULT,

	BGM_MAX
};

enum
{
	SE_TAP,
	SE_JUST,
	SE_GOOD,

	SE_MAX
};

enum
{	// 再生用フラグ
	E_DS8_FLAG_NONE,
	E_DS8_FLAG_LOOP,	// DSBPLAY_LOOPING=1
	E_DS8_FLAG_MAX
};

#define		MUSIC_STARTNO	(BGM_SUPERNOVA)

extern LPDIRECTSOUNDBUFFER8	g_pBGM[BGM_MAX];					// BGM用バッファ
extern LPDIRECTSOUNDBUFFER8	g_pSE[SE_MAX];						// SE用バッファ

HRESULT					InitSound(HWND hWnd);	// 初期化
void					UninitSound();			// 後片付け
LPDIRECTSOUNDBUFFER8	LoadSoundBGM(int no);	// サウンドBGMのロード
LPDIRECTSOUNDBUFFER8	LoadSoundSE(int no);	// サウンドSEのロード

void					PlaySound(LPDIRECTSOUNDBUFFER8 pBuffer, int flag = 0);	// 音ごとに再生
bool					IsPlaying(LPDIRECTSOUNDBUFFER8 pBuffer);					// 再生中かどうか
void					StopSound(LPDIRECTSOUNDBUFFER8 pBuffer, int flag);

#endif