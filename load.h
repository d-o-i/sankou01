//=============================================================================
//
// �X�R�A���� [load.h]
// Author : 
//
//=============================================================================
#ifndef _LOAD_H_
#define _LOAD_H_

// �}�N����`
#define		NOTE_MAX		(1024)		// �m�[�c�̍ő吔

//*****************************************************************************
// �v���g�^�C�v�錾
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
