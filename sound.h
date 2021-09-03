#ifndef ___SOUND_H___
#define ___SOUND_H___

#include <windows.h>
#include <tchar.h>
#include <dsound.h>
#include <dmusics.h>
#include <mmsystem.h>
#include <comdef.h>
// �}�N����`

enum
{	// �T�E���h�ʂ��i���o�[
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
{	// �Đ��p�t���O
	E_DS8_FLAG_NONE,
	E_DS8_FLAG_LOOP,	// DSBPLAY_LOOPING=1
	E_DS8_FLAG_MAX
};

#define		MUSIC_STARTNO	(BGM_SUPERNOVA)

extern LPDIRECTSOUNDBUFFER8	g_pBGM[BGM_MAX];					// BGM�p�o�b�t�@
extern LPDIRECTSOUNDBUFFER8	g_pSE[SE_MAX];						// SE�p�o�b�t�@

HRESULT					InitSound(HWND hWnd);	// ������
void					UninitSound();			// ��Еt��
LPDIRECTSOUNDBUFFER8	LoadSoundBGM(int no);	// �T�E���hBGM�̃��[�h
LPDIRECTSOUNDBUFFER8	LoadSoundSE(int no);	// �T�E���hSE�̃��[�h

void					PlaySound(LPDIRECTSOUNDBUFFER8 pBuffer, int flag = 0);	// �����ƂɍĐ�
bool					IsPlaying(LPDIRECTSOUNDBUFFER8 pBuffer);					// �Đ������ǂ���
void					StopSound(LPDIRECTSOUNDBUFFER8 pBuffer, int flag);

#endif