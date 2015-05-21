/*
*	�w�b�_�[�t�@�C���̃C���N���[�h
*	���C�u�����̃����N
*	�}�N����`
*
*	2015/05/01		Y.Ozawa
*/

#pragma once

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include "Application.h"
#include "Object.h"
#include "Model.h"
#include "Texture.h"
#include "Camera.h"
#include "Light.h"
#include "Debug.h"
#include "Common.h"

//���C�u�����̃����N
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

//�}�N����`

//�R���\�[�����J��
#define OpenConsole() {\
	AllocConsole();\
	FILE *fp;\
	freopen_s(&fp, "CONOUT$", "w", stdout);\
	freopen_s(&fp, "CONIN$", "r", stdin);\
}
//�R���\�[�������
#define CloseConsole() {\
	FreeConsole();\
}
//�|�C���^�������[�X����
#define SafeRelease(p) {\
	if (p)\
		{\
		p->Release();\
		p = nullptr;\
		}\
}


