//=============================================================================
//
// Main���� [main.cpp]
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
// �}�N����`
//*****************************************************************************
#define CLASS_NAME			_T("AppClass")			// �E�C���h�E�̃N���X��
#define WINDOW_NAME			_T("GrandCross")		// �E�C���h�E�̃L���v�V������

//*****************************************************************************
// �\���̒�`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
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
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3D9				g_pD3D = NULL;				// Direct3D�I�u�W�F�N�g
LPDIRECT3DDEVICE9		g_pD3DDevice = NULL;		// Device�I�u�W�F�N�g(�`��ɕK�v)

#ifdef _DEBUG
LPD3DXFONT				g_pD3DXFont = NULL;			// �t�H���g�ւ̃|�C���^
int						g_nCountFPS;				// FPS�J�E���^
#endif
int						g_nStage = 0;				// �X�e�[�W�ԍ�
int						Old_nSrage;

int						g_Music;
int						s_Music;

LPDIRECTSOUNDBUFFER8	g_pBGM[BGM_MAX];						// BGM�p�o�b�t�@
LPDIRECTSOUNDBUFFER8	g_pSE[SE_MAX];							// SE�p�o�b�t�@

//=============================================================================
// ���C���֐�
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	UNREFERENCED_PARAMETER(lpCmdLine);		// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j

	// ���Ԍv���p
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

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E�̍쐬
	hWnd = CreateWindow(CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,																		// �E�B���h�E�̍����W
		CW_USEDEFAULT,																		// �E�B���h�E�̏���W
		SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2,									// �E�B���h�E����
		SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),	// �E�B���h�E�c��
		NULL,
		NULL,
		hInstance,
		NULL);

	// DirectX�̏�����(�E�B���h�E���쐬���Ă���s��)
	if (FAILED(Init(hWnd, true)))
	{
		return -1;
	}

	// ���͏����̏�����
	InitInput(hInstance, hWnd);

	// �t���[���J�E���g������
	timeBeginPeriod(1);	// ����\��ݒ�
	dwExecLastTime = dwFPSLastTime = timeGetTime();	// �V�X�e���������~���b�P�ʂŎ擾
	dwCurrentTime = dwFrameCount = 0;

	// �E�C���h�E�̕\��(Init()�̌�ɌĂ΂Ȃ��Ƒʖ�)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();					// �V�X�e���������擾

			if ((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5�b���ƂɎ��s
			{
#ifdef _DEBUG
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);	// FPS�𑪒�
#endif
				dwFPSLastTime = dwCurrentTime;				// FPS�𑪒肵��������ۑ�
				dwFrameCount = 0;							// �J�E���g���N���A
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))	// 1/60�b���ƂɎ��s
			{
				dwExecLastTime = dwCurrentTime;	// ��������������ۑ�

				Update();			// �X�V����
				Draw();				// �`�揈��

				dwFrameCount++;		// �����񐔂̃J�E���g�����Z
			}

			SetNote();
		}
	}

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// �I������
	Uninit();

	return (int)msg.wParam;
}

//=============================================================================
// �v���V�[�W��
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
		case VK_ESCAPE:					// [ESC]�L�[�������ꂽ
			DestroyWindow(hWnd);		// �E�B���h�E��j������悤�w������
			break;
		}
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Init(HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	srand((unsigned)time(NULL));

	// Direct3D�I�u�W�F�N�g�̍쐬
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ���[�N���[���N���A
	d3dpp.BackBufferCount = 1;						// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth = SCREEN_WIDTH;				// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;			// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;			// �o�b�N�o�b�t�@�̃t�H�[�}�b�g�͌��ݐݒ肳��Ă�����̂��g��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// �f���M���ɓ������ăt���b�v����
	d3dpp.Windowed = bWindow;					// �E�B���h�E���[�h
	d3dpp.EnableAutoDepthStencil = TRUE;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;				// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.BackBufferFormat = d3ddm.Format;				// �J���[���[�h�̎w��

	if (bWindow)
	{// �E�B���h�E���[�h
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;					// �o�b�N�o�b�t�@
		d3dpp.FullScreen_RefreshRateInHz = 0;								// ���t���b�V�����[�g
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// �C���^�[�o��
	}
	else
	{// �t���X�N���[�����[�h
		d3dpp.BackBufferFormat = D3DFMT_R5G6B5;					// �o�b�N�o�b�t�@
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// ���t���b�V�����[�g
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// �C���^�[�o��
	}

	// �f�o�C�X�̐���
	// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
	// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,							// �f�B�X�v���C�A�_�v�^
		D3DDEVTYPE_HAL,								// �f�B�X�v���C�^�C�v
		hWnd,										// �t�H�[�J�X����E�C���h�E�ւ̃n���h��
		D3DCREATE_HARDWARE_VERTEXPROCESSING,		// �f�o�C�X�쐬����̑g�ݍ��킹
		&d3dpp,										// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
		&g_pD3DDevice)))							// �f�o�C�X�C���^�[�t�F�[�X�ւ̃|�C���^
	{
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// �`��ƒ��_������CPU�ōs�Ȃ�
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				// ���������s
				return E_FAIL;
			}
		}
	}

	// �����_�����O�X�e�[�g�p�����[�^�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// �J�����O���s��Ȃ�
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��

																			// �T���v���[�X�e�[�g�p�����[�^�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���t�l�̌J��Ԃ��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���u�l�̌J��Ԃ��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g�厞�̕�Ԑݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k�����̕�Ԑݒ�

#ifdef _DEBUG
																			// ���\���p�t�H���g��ݒ�
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &g_pD3DXFont);
#endif

	// �T�E���h������
	InitSound(hWnd);
	// ���[�h�ƍĐ�
	for (int i = 0; i < BGM_MAX; i++)
	{
		g_pBGM[i] = LoadSoundBGM(i);
	}

	for (int i = 0; i < SE_MAX; i++)
	{
		g_pSE[i] = LoadSoundSE(i);
	}

	// �^�C�g��������
	InitTitle(0);

	// �Z���N�g������
	InitSelect(0);

	// �`�F�b�N�̏�����
	InitCheck();

	// ���U���g������
	InitResult(0);

	// ���C�t�̏�����
	InitLife(0);

	// �X�R�A�̏�����
	InitScore(0);

	// �X�^�[�̏�����
	InitStar(0);

	// ���C���̏�����
	InitLine(0);
	
	// �A���[������
	InitArrow(0);

	// �w�i������
	InitBg(0);

	// �O���b�h������
	InitGrid(0);

	// ���[�h������
	InitLoad(0);

	// �R���{������
	InitCombo(0);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Uninit(void)
{
	// ���͏����̏I������
	UninitInput();

	// �^�C�g���I������
	UninitTitle();

	// �Z���N�g���
	UninitSelect();

	// ���U���g�I������
	UninitResult();

	// ���C�t�̏I������
	UninitLife();

	// �X�R�A�̏I������
	UninitScore();

	// �X�^�[�̏I������
	UninitStar();

	// ���C���̏I������
	UninitLine();

	// �A���[���
	UninitArrow();

	// �w�i���
	UninitBg();

	// �O���b�h���
	UninitGrid();

	// �R���{�̏I������
	UninitCombo();

	if (g_pD3DDevice != NULL)
	{// �f�o�C�X�̊J��
		g_pD3DDevice->Release();
	}

	if (g_pD3D != NULL)
	{// Direct3D�I�u�W�F�N�g�̊J��
		g_pD3D->Release();
	}

	// �T�E���h�����̏I������
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
// �X�V����
//=============================================================================
void Update(void)
{
	// ���͂̍X�V����
	UpdateInput();

	// ��ʑJ��
	switch (g_nStage)
	{
	case STAGE_TITLE:
		// �^�C�g���̍X�V����
		UpdateTitle();
		if (Title == false)
		{
			Result = false;
			Title = true;

			// �O��ʂ̋Ȃ��~�߂�
			StopSound(g_pBGM[BGM_RESULT], E_DS8_FLAG_NONE);
			// ���Ɏg���Ȃ̍Đ��ʒu����ԍŏ��ɐݒ�
			g_pBGM[BGM_TITLE]->SetCurrentPosition(0);
			// �Đ�		
			PlaySound(g_pBGM[BGM_TITLE], E_DS8_FLAG_LOOP);
		}
		break;

	case STAGE_SELECT:
		if (Title == true)
		{
			Title = false;

			// �O��ʂ̋Ȃ��~�߂�
			StopSound(g_pBGM[BGM_TITLE], E_DS8_FLAG_NONE);

			StartMusic();
		}

		// �Z���N�g�X�V
		UpdateSelect();

		break;

	case STAGE_GAME:
		// �`�F�b�N�̍X�V����
		UpdateCheck();

		// ���C�t�̍X�V����
		UpdateLife();

		// �X�R�A�̍X�V����
		UpdateScore();

		// �X�^�[�̍X�V����
		UpdateStar();

		// ���C���̍X�V����
		UpdateLine();

		// �A���[�X�V
		UpdateArrow();

		// �w�i�X�V
		UpdateBg();

		// �O���b�h�X�V
		UpdateGrid();

		// ���C�t���Ȃ��Ȃ�Ȃ��ŃQ�[���I��(��)
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
			// �O��ʂ̋Ȃ��~�߂�
			StopSound(g_pBGM[g_Music], E_DS8_FLAG_NONE);
			// ���Ɏg���Ȃ̍Đ��ʒu����ԍŏ��ɐݒ�
			g_pBGM[BGM_RESULT]->SetCurrentPosition(0);
			// �Đ�	
			PlaySound(g_pBGM[BGM_RESULT], E_DS8_FLAG_LOOP);

			Result = true;
		}

		// �R���{�̍X�V����
		UpdateCombo();

		// ���U���g�̍X�V����
		UpdateResult();	

		break;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(128, 128, 255, 0), 1.0f, 0);

	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		// ��ʑJ��
		switch (g_nStage)
		{
		case STAGE_TITLE:
			// �^�C�g���̕`�揈��
			DrawTitle();
			break;
		case STAGE_SELECT:
			// �Z���N�g�`��
			DrawSelect();

			break;
		case STAGE_GAME:
			// �w�i�`��
			DrawBg();

			// ���C���̕`�揈��
			DrawLine();

			// �X�^�[�̕`�揈��
			DrawStar();

			// �A���[�`��
			DrawArrow();

			// �O���b�h�`��
			DrawGrid();

			// ���C�t�̕`�揈��
			DrawLife();

			// �X�R�A�̕`�揈��
			DrawScore();

			break;

		case STAGE_RESULT:
			// ���U���g�̕`�揈��
			DrawResult();

			// �X�R�A�̕`�揈��
			DrawScore();

			// �R���{�̕`�揈��
			DrawCombo();

			break;
		}

#ifdef _DEBUG
		// �f�o�b�O�\��
		DrawDebugFont();
#endif

		// Direct3D�ɂ��`��̏I��
		g_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
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
// �f�o�C�X�擾�֐�
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return(g_pD3DDevice);
}


#ifdef _DEBUG
//=============================================================================
// �f�o�b�O�\������
//=============================================================================
void DrawDebugFont(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];

	// �e�L�X�g�`��
	sprintf(str, _T("FPS:%d"), g_nCountFPS);
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	rect.top += 20;
	sprintf(str, _T("�ʒu:%d"), GetPos(0));
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	rect.top += 20;
	sprintf(str, _T("�^�C�~���O:%f, %f, %f, %f, %f"), GetTiming(0), GetTiming(1), GetTiming(2), GetTiming(3), GetTiming(4));
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	rect.top += 20;
	sprintf(str, _T("����:%f"), GetTime());
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	rect.top += 20;
	sprintf(str, _T("�J�E���g:%d"), GetCount());
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	rect.top += 20;
	sprintf(str, _T("�f�[�^:%d"), GetData());
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	rect.top += 20;
	sprintf(str, _T("�^�C��:%d"), timeGetTime());
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	rect.top += 20;
	sprintf(str, _T("���X�g:%f"), GetLastTim());
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	rect.top += 20;
	sprintf(str, _T("�e�X�^�[�ʒu X:%f �e�X�^�[�ʒu Y:%f"), GetPosTest(0), GetPosTest(1));
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	rect.top += 20;
	sprintf(str, _T("�X�p�m�o�ʒu X:%f"), GetSuperPos());
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	rect.top += 20;
	sprintf(str, _T("�^�񒆈ʒu X:%f"), GetSelectSuperPos());
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	rect.top += 20;
	sprintf(str, _T("�W���X�g:%d"), GetJust());
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	rect.top += 20;
	sprintf(str, _T("�O�b�h:%d"), GetGood());
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	rect.top += 20;
	sprintf(str, _T("�~�X:%d"), GetMiss());
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif

//=============================================================================
// ��ʑJ��
//=============================================================================
void SetStage(int stage
)
{
	if( stage < 0 || stage >= STAGE_MAX ) return;

	g_nStage = stage;
}

//=============================================================================
// �Đ����鉹�y
//=============================================================================
void SetMusic(int no)
{
	s_Music = no;
	g_Music = no;
}
//=============================================================================
// �Đ����鉹�y�̔ԍ��擾
//=============================================================================
int GetMusic()
{
	return g_Music;
}


//=============================================================================
// �Q�[���̍ď�������������
// �߂�l�F����
//=============================================================================
void InitGame(void)
{
	InitTitle(1);	// �^�C�g���̍ď�����
	InitResult(1);	// ���U���g�̍ď�����
	InitCheck();	// �`�F�b�N�̍ď�����
	InitLife(1);	// ���C�t�̍ď�����
	InitScore(1);	// �X�R�A�̍ď�����
	InitStar(1);	// �X�^�[�̍ď�����
	InitLine(1);	// ���C���̍ď�����
	InitArrow(1);	// �A���[�̍ď�����
	InitSelect(1);	// �Z���N�g�̍ď�����
	InitBg(1);		// �w�i�̍ď�����
	InitGrid(1);	// �O���b�h�̍ď�����
	InitLoad(1);	// ���[�h�̍ď�����
	InitCombo(1);	// �R���{�̍ď�����
}