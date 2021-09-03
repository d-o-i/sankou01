//=============================================================================
//
// ���f������ [model.cpp]
// Author : 
//
//=============================================================================
#include "model.h"
#include "input.h"

//*****************************************************************************

/*
1) ball.x�Ƃ����ӂ��[.dds�ƃJ�[�r�[.dds���R�s�[����

main.cpp
#define WINDOW_NAME		"�w�Дԍ��@�N���X�@�o�Ȕԍ��@����"�@�@��ύX

model.cpp
2) �K���ɃJ�����⃂�f���̈ʒu�𒲐�
3�jLPDIRECT3DTEXTURE9	g_pD3DTextureModel2;��ǉ�

�}�N����`�֘A
#define	MODEL_CAR		"data/MODEL/ball.x"						// �ǂݍ��ރ��f����
#define TEXTURE_FILENAME2	"data/TEXTURE/�����ӂ��[.dds"		// �t�@�C���̖��O
#define TEXTURE_FILENAME	"data/TEXTURE/�J�[�r�[.dds"		// �t�@�C���̖��O
#define	VIEW_NEAR_Z		(1.0f)�ɕύX

InitModel(void)���̕ύX
4�j	D3DXCreateTextureFromFile(pDevice,					
�@�@�@�@TEXTURE_FILENAME2,		// �t�@�C���̖��O
		&g_pD3DTextureModel2);	// �ǂݍ��ރ������[�@��ǉ�

5�j�}���`�e�N�X�`���ݒ��ǉ�

DrawModel(void)���̕ύX
6�j	pDevice->SetTexture(1, g_pD3DTextureModel2);��ǉ�
7�j	pDevice->SetTexture(1, NULL)��ǉ�;

�m�F�o������e�N�X�`����ύX���Ă݂�
���e�N�X�`���̓T���v���m���m�ł�OK
�f�t���[�Y�e�N�X�`����K���ɕύX


*/





// �}�N����`
//*****************************************************************************
#define	MODEL_CAR		"data/MODEL/ball.x"						// �ǂݍ��ރ��f����
#define TEXTURE_FILENAME2	"data/TEXTURE/�����ӂ��[.dds"		// �t�@�C���̖��O
#define TEXTURE_FILENAME	"data/TEXTURE/Rock_Normal.bmp"		// �t�@�C���̖��O


#define	POS_CAMERA_P_X	(0.0f)											// �J�������_�̏����ʒu(X���W)
#define	POS_CAMERA_P_Y	(15.0f)											// �J�������_�̏����ʒu(Y���W)
#define	POS_CAMERA_P_Z	(-3.0f)										// �J�������_�̏����ʒu(Z���W)

#define	VIEW_ANGLE		(D3DXToRadian(45.0f))							// �r���[���ʂ̎���p
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��	
#define	VIEW_NEAR_Z		(1.0f)											// �r���[���ʂ�NearZ�l
#define	VIEW_FAR_Z		(1000.0f)										// �r���[���ʂ�FarZ�l

#define	VALUE_MOVE		(5.0f)											// �ړ���
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)								// ��]��

#define	NUM_LIGHT		(3)												// ���C�g�̐�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitCamera(void);
void InitLight(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTextureModel;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9	g_pD3DTextureModel2;		// �e�N�X�`���ւ̃|�C���^
LPD3DXMESH			g_pD3DXMeshModel;		// ���b�V�����ւ̃|�C���^
LPD3DXBUFFER		g_pD3DXBuffMatModel;	// �}�e���A�����ւ̃|�C���^
DWORD				g_nNumMatModel;			// �}�e���A�����̐�

D3DXVECTOR3			g_posModel;				// ���f���̈ʒu
D3DXVECTOR3			g_rotModel;				// ���f���̌���(��])
D3DXVECTOR3			g_sclModel;				// ���f���̑傫��(�X�P�[��)

D3DXVECTOR3			g_posCameraP;			// �J�����̎��_
D3DXVECTOR3			g_posCameraR;			// �J�����̒����_
D3DXVECTOR3			g_vecCameraU;			// �J�����̏�����x�N�g��

D3DXMATRIX			g_mtxView;				// �r���[�}�g���b�N�X
D3DXMATRIX			g_mtxProjection;		// �v���W�F�N�V�����}�g���b�N�X
D3DXMATRIX			g_mtxWorld;				// ���[���h�}�g���b�N�X

D3DLIGHT9			g_aLight[NUM_LIGHT];	// ���C�g���


//===================================================================================
//�V�F�[�_�[���O���[�o���ϐ�
//===================================================================================
LPDIRECT3DVERTEXSHADER9 g_VertexShader = nullptr;			// ���_�V�F�[�_�[
LPD3DXCONSTANTTABLE		g_VSConstantTable = nullptr;		// �萔�e�[�u��

LPDIRECT3DPIXELSHADER9	g_PixelShader = nullptr;			// �s�N�Z���V�F�[�_�[
LPD3DXCONSTANTTABLE		g_PSConstantTable = nullptr;		// �萔�e�[�u��



//=============================================================================
// ����������
//=============================================================================
HRESULT InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �J�����̏�����
	InitCamera();

	// ���C�g�̏�����
	InitLight();

	// �ʒu�E��]�E�X�P�[���̏����ݒ�
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
	 //X�t�@�C���̓ǂݍ���
	if(FAILED(D3DXLoadMeshFromX(MODEL_CAR,				// �ǂݍ��ރ��f���t�@�C����(X�t�@�C��)
								D3DXMESH_SYSTEMMEM,		// ���b�V���̍쐬�I�v�V�������w��
								pDevice,				// IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
								NULL,					// �אڐ��f�[�^���܂ރo�b�t�@�ւ̃|�C���^
								&g_pD3DXBuffMatModel,	// �}�e���A���f�[�^���܂ރo�b�t�@�ւ̃|�C���^
								NULL,					// �G�t�F�N�g�C���X�^���X�̔z����܂ރo�b�t�@�ւ̃|�C���^
								&g_nNumMatModel,		// D3DXMATERIAL�\���̂̐�
								&mesh)))	// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X
	{
		return E_FAIL;
	}

	mesh->CloneMesh(D3DXMESH_SYSTEMMEM, decl, pDevice, &g_pD3DXMeshModel);
	mesh->Release();
	D3DXComputeTangent(g_pD3DXMeshModel, 0, 0, 0, 0, NULL);

#if 1
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
								TEXTURE_FILENAME,		// �t�@�C���̖��O
								&g_pD3DTextureModel);	// �ǂݍ��ރ������[
#endif
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
		TEXTURE_FILENAME2,		// �t�@�C���̖��O
		&g_pD3DTextureModel2);	// �ǂݍ��ރ������[




		//�J�����O
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//���e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAREF, 255);

	//���l��alpharef�ȏ�̃s�N�Z���͕`��
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

	//���u�����h�ݒ�i�������j
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	//�}���`�e�N�X�`���̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);


	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);//ARG2�̐ݒ���g��
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_CURRENT);//ARG1�̓J�����g�F
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);//ARG2�̓e�N�X�`��

	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);//ARG2�̐ݒ���g��
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);//ARG2�̓J�����g�F


	pDevice->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 0);	//UV���W��0�Ԗڂ��g��

	pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_BLENDTEXTUREALPHA);//ARG1��ARG2�����u�����h����
	pDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);//ARG1��STAGE1����̏o�͐F
	pDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);//ARG2�̓X�e�[�W1�̃e�N�X�`��

	pDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
	pDevice->SetTextureStageState(1, D3DTSS_ALPHAARG1, D3DTA_CURRENT);
	pDevice->SetTextureStageState(1, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);


//	pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);//STAGE1�͖��g�p


	//==========================================================
	//�V�F�[�_�[���ǉ�
	//==========================================================
	LPD3DXBUFFER err = NULL;
	LPD3DXBUFFER code = NULL;
	HRESULT hr;


	//���_�V�F�[�_���R���p�C��&�쐬
	hr = D3DXCompileShaderFromFile("basic2.fx",		// �t�@�C����
		nullptr,		// �v���v���Z�b�T��`�ւ̃|�C���^ 
		nullptr,		// ID3DXInclude�i#include�^�����߁j
		"VS",			// ���_�V�F�[�_�[�֐��� 
		"vs_3_0",		// ���_�V�F�[�_�[�̃o�[�W���� 
		0,				// �R���p�C���I�v�V����
		&code,			// �R���p�C���ς݂̃V�F�[�_�[�R�[�h�iOUT�j
		&err,			// �R���p�C���G���[��񂪊i�[�����iOUT�j
		&g_VSConstantTable);	// �V�F�[�_�[���̃R���X�^���g�e�[�u���iOUT�j
	// �G���[����
	if (FAILED(hr))
	{
		if (err) {
			// �R���p�C���G���[����
			MessageBox(NULL, (LPSTR)err->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
		}
		else {
			// ���̑��̃G���[
			MessageBox(NULL, "�V�F�[�_�[�t�@�C�����ǌ��ݍ��߂܂���", "D3DXCompileShaderFromFile", MB_OK);
		}
		return false;
	}
	// ���_�V�F�[�_�[�I�u�W�F�N�g���쐬����
	hr = pDevice->CreateVertexShader((DWORD*)code->GetBufferPointer(), &g_VertexShader);
	if (FAILED(hr))
	{
		MessageBox(NULL, (LPSTR)err->GetBufferPointer(), "CreateVertexShader", MB_OK);
		return false;
	}

	//�s�N�Z���V�F�[�_���R���p�C��&�쐬
	hr = D3DXCompileShaderFromFile("basic2.fx",		// �t�@�C����
		nullptr,		// �v���v���Z�b�T��`�ւ̃|�C���^ 
		nullptr,		// ID3DXInclude�i#include�^�����߁j
		"PS",			// ���_�V�F�[�_�[�֐��� 
		"ps_3_0",		// ���_�V�F�[�_�[�̃o�[�W���� 
		0,				// �R���p�C���I�v�V����
		&code,			// �R���p�C���ς݂̃V�F�[�_�[�R�[�h�iOUT�j
		&err,			// �R���p�C���G���[��񂪊i�[�����iOUT�j
		&g_PSConstantTable);	// �V�F�[�_�[���̃R���X�^���g�e�[�u���iOUT�j
	// �G���[����
	if (FAILED(hr))
	{
		if (err) {
			// �R���p�C���G���[����
			MessageBox(NULL, (LPSTR)err->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
		}
		else {
			// ���̑��̃G���[
			MessageBox(NULL, "�V�F�[�_�[�t�@�C�����ǌ��ݍ��߂܂���", "D3DXCompileShaderFromFile", MB_OK);
		}
		return false;
	}
	// �R���p�C���ς݃R�[�h����s�N�Z���V�F�[�_�[�I�u�W�F�N�g���쐬����
	hr = pDevice->CreatePixelShader((DWORD*)code->GetBufferPointer(), &g_PixelShader);
	if (FAILED(hr))
	{
		MessageBox(NULL, (LPSTR)err->GetBufferPointer(), "CreatePixelShader", MB_OK);
		return false;
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitModel(void)
{
	if(g_pD3DTextureModel != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureModel->Release();
		g_pD3DTextureModel = NULL;
	}

	if(g_pD3DXMeshModel != NULL)
	{// ���b�V���̊J��
		g_pD3DXMeshModel->Release();
		g_pD3DXMeshModel = NULL;
	}

	if(g_pD3DXBuffMatModel != NULL)
	{// �}�e���A���̊J��
		g_pD3DXBuffMatModel->Release();
		g_pD3DXBuffMatModel = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateModel(void)
{

	g_rotModel.y += D3DXToRadian( 1.0f );
	g_rotModel.z += D3DXToRadian(  0.5f );

}

//=============================================================================
// �`�揈��
//=============================================================================

void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_mtxView, 
						&g_posCameraP,		// �J�����̎��_
						&g_posCameraR,		// �J�����̒����_
						&g_vecCameraU);		// �J�����̏�����x�N�g��

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_mtxView);


	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&g_mtxProjection,
								VIEW_ANGLE,			// �r���[���ʂ̎���p
								VIEW_ASPECT,		// �r���[���ʂ̃A�X�y�N�g��
								VIEW_NEAR_Z,		// �r���[���ʂ�NearZ�l
								VIEW_FAR_Z);		// �r���[���ʂ�FarZ�l

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_mtxProjection);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorld);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, g_sclModel.x, g_sclModel.y, g_sclModel.z);
	D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotModel.y, g_rotModel.x, g_rotModel.z);
	D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, g_posModel.x, g_posModel.y, g_posModel.z);
	D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);

	//
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);


	//==================================================================
	//�V�F�[�_�[���ǉ�
	//==================================================================
		// ���_�V�F�[�_�[�ƃs�N�Z���V�F�[�_�[���Z�b�g
	pDevice->SetVertexShader(g_VertexShader);
	pDevice->SetPixelShader(g_PixelShader);

	// �萔���Z�b�g
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

	////���̃x�N�g��
	//D3DXVECTOR4	Light = D3DXVECTOR4(0.5f, 0.0f, 1.0f, 0.0f);
	//g_PSConstantTable->SetVector(pDevice, "g_light", &Light);
	//�J�����̈ʒu

	D3DXVECTOR3 cv = D3DXVECTOR3(g_posCameraP.x, g_posCameraP.y, g_posCameraP.z);
	D3DXVECTOR4	Camera = D3DXVECTOR4(g_posCameraP.x, g_posCameraP.y, g_posCameraP.z, 0);
	D3DXVec3Transform(&Camera, &cv, &invMatrix);
	g_VSConstantTable->SetVector(pDevice, "g_Camera", &Camera);


	//=================================================
	// �T���v���[�X�e�[�g�p�����[�^�̐ݒ�
	int	stage = g_PSConstantTable->GetSamplerIndex("Sampler0");	//�T���v���[�C���f�b�N�X���擾
	int	stage2 = g_PSConstantTable->GetSamplerIndex("Sampler1");	//�T���v���[�C���f�b�N�X���擾

	pDevice->SetSamplerState(stage, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	pDevice->SetSamplerState(stage, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	pDevice->SetSamplerState(stage, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k���t�B���^���[�h��ݒ�
	pDevice->SetSamplerState(stage, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g��t�B���^���[�h��ݒ�

	pDevice->SetSamplerState(stage2, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	pDevice->SetSamplerState(stage2, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	pDevice->SetSamplerState(stage2, D3DSAMP_MINFILTER, D3DTEXF_POINT);	// �e�N�X�`���k���t�B���^���[�h��ݒ�
	pDevice->SetSamplerState(stage2, D3DSAMP_MAGFILTER, D3DTEXF_POINT);	// �e�N�X�`���g��t�B���^���[�h��ݒ�


	//=================================================


	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A�����ɑ΂���|�C���^���擾
	pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatModel->GetBufferPointer();

	for(int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(stage2, g_pD3DTextureModel);
		pDevice->SetTexture(stage, g_pD3DTextureModel2);

		// �`��
		g_pD3DXMeshModel->DrawSubset(nCntMat);
	}


	pDevice->SetTexture(1, NULL);


	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);

	//==================================================================
	//�V�F�[�_�[���ǉ�
	//==================================================================
	// ���_�V�F�[�_�[�ƃs�N�Z���V�F�[�_�[���f�t�H���g��
	pDevice->SetVertexShader(NULL);
	pDevice->SetPixelShader(NULL);



}

//=============================================================================
// �J�����̏���������
//=============================================================================
void InitCamera(void)
{
	g_posCameraP = D3DXVECTOR3(POS_CAMERA_P_X, POS_CAMERA_P_Y, POS_CAMERA_P_Z);
	g_posCameraR = D3DXVECTOR3(POS_CAMERA_P_X, POS_CAMERA_P_Y, 0.0f);
	g_vecCameraU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}

//=============================================================================
// ���C�g�̏���������
//=============================================================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 vecDir;

	// D3DLIGHT9�\���̂�0�ŃN���A����
	ZeroMemory(&g_aLight[0], sizeof(D3DLIGHT9));

	// ���C�g0�̃^�C�v�̐ݒ�
	g_aLight[0].Type = D3DLIGHT_DIRECTIONAL;

	// ���C�g0�̊g�U���̐ݒ�
	g_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���C�g0�̊����̐ݒ�
	g_aLight[0].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���C�g0�̕����̐ݒ�
	vecDir = D3DXVECTOR3(-0.0f, -0.6f, -1.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[0].Direction, &vecDir);

	// ���C�g0�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetLight(0, &g_aLight[0]);

	// ���C�g0���g�p�g�p��Ԃ�
	pDevice->LightEnable(0, TRUE);


	// D3DLIGHT9�\���̂�0�ŃN���A����
	ZeroMemory(&g_aLight[1], sizeof(D3DLIGHT9));

	// ���C�g1�̃^�C�v�̐ݒ�
	g_aLight[1].Type = D3DLIGHT_DIRECTIONAL;

	// ���C�g1�̊g�U���̐ݒ�
	g_aLight[1].Diffuse = D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f);

	// ���C�g1�̊����̐ݒ�
	g_aLight[1].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

    // ���C�g1�̕����̐ݒ�
	vecDir = D3DXVECTOR3(-0.0f, -1.0f, 0.8f);
	D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[1].Direction, &vecDir);

	// ���C�g1�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetLight(1, &g_aLight[1]);

	// ���C�g1�̐ݒ�
	pDevice->LightEnable(1, TRUE);

	// ���C�e�B���O���[�h��ON
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

