#pragma once

// 4005��� ��� �����ϰڴ�.
#pragma warning(disable : 4005)
// 4005 : DXGI �� �׷��� �������̽����� ��ũ�� �����Ͽ� ��µǴ� ���

// SDKDDKVER.h�� ���α׷����� ������ OS Ȥ�� ���̺귯���� ���� Windows ������� �ڵ尡 ���Ե� �Լ� / ��� ���� �����ϴµ� ��� �Ѵ�.
#include <SDKDDKVER.h>

// ���� ������ �ʴ� ������ Windows ������� ����
// �� GDI+�� ����Ϸ��� ������Ͽ��� �����;� �Ѵ�.
//#include <ole2.h>
#define WIN32_LEAN_AND_MEAN

// ����� �ܼ�â
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

// ! ���̺귯�� �߰� ============================================================================================================
#pragma comment (lib, "msimg32.lib")

//! Windows ��� ���� ============================================================================================================
#include <Windows.h>

//! C ��Ÿ�� ��� ���� ============================================================================================================
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <time.h>
#include <tchar.h>
#include <stdio.h>


//! C++ ��Ÿ�� ��� ���� ============================================================================================================
#include <iostream>
#include <fstream>
#include <istream>
#include <string>

// C++11���� �߰��� �ð� ���� ���̺귯�� (STL)
#include <chrono>		
#include <random>
#include <vector>
#include <queue>
#include <stack>
#include <map>

/*
unordered_map : Hash �ڷᱸ��
�� �Ϲ��� ��Ȳ���� map���� �˻��ӵ��� �� ������.
�� �˻� �ӵ��� ���� ������ �ߺ��� �����͸� ������� �ʱ� �����̴�.
	��, ���� �����Ͱ� ���� �� (key), �ؽ� �浹�� �߻��� ������ ����� ������ ���� ���ϰ� �߻��Ѵ�.
*/
#include <unordered_map>
#include <cassert>

// bitset : ��Ʈ ������ �� �� ���� ������ �ִ� �Լ��� �����ϴ� STL
#include <bitset>

#include <unordered_set>

using namespace std;

using std::vector;
using std::queue;
using std::stack;
using std::map;
using std::unordered_map;
using std::unordered_set;
using std::bitset;
using std::string;

/*
// ! D2D/D3D ��� ���� ============================================================================================================
#include <D2D1.h>
#include <d2d1helper.h>
#include <d3dx9.h>
#include <D3DX11.h>
#include <d3d11shader.h>
#include <dinput.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

ID2D1Factory*				_ID2DFactory = nullptr;
ID2D1HwndRenderTarget*		_ID2DRenderTarget = nullptr;
*/

// # ����� ���� ��� ���� # ================================================================================================
#include "../ManagerClass/KeyManager.h"
#include "../ManagerClass/ImageManager.h"
#include "../ManagerClass/TimeManager.h"
#include "../ManagerClass/SceneManager.h"
#include "../ManagerClass/SoundManager.h"
#include "../../MainGame/UI/UIManager.h"

#include "../Utility/CommonMacroFunction.h"
#include "../Utility/Header.h"
#include "../Utility/RandomFunction.h"

#include "../../MainGame/Object/TileMap/TileMap.h"
#include "../../MainGame/Object/Player/Player.h"
#include "../../MainGame/Object/Beat/Beat.h"
#include "../Camera/Camera.h"


// # �̱��� # ==============================================================================================================
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define TIMEMANAGER TimeManager::getSingleton()
#define SCENEMANAGER SceneManager::getSingleton()
#define SOUNDMANAGER SoundManager::getSingleton()
#define UIMANAGER UIManager::getSingleton()

#define RND RandomFunction::getSingleton()
#define TILEMAP TileMap::getSingleton()
#define PLAYER Player::getSingleton()
#define CAMERA Camera::getSingleton()
#define BEAT Beat::getSingleton()

// # ��ũ�� #  ==============================================================================================================


// ! Ÿ��Ʋ
#define WINNAME				(LPTSTR)(TEXT("Crypt of the NecroDancer"))

// ! ��ü ȭ�� 
//#define FULLSCREEN

#ifdef FULLSCREEN
#define WINSTART_X		0
#define WINSTART_Y		0
//GetSystemMetrics() : ���ڷ� ���޵Ǵ� �ý��� ���� ������ ��ȯ
// �� SM_CXSCREEN + SM_CYSCREEN = ���� ȭ�� �ػ� X / Y �� ��ȯ
#define WINSIZE_X		GetSystemMetrics(SM_CXSCREEN)  
#define WINSIZE_Y		GetSystemMetrics(SM_CYSCREEN)

#define WINSIZE_X_HALF		WINSIZE_X / 2
#define WINSIZE_Y_HALF		WINSIZE_Y / 2
#define WINSTYLE		WS_POPUPWINDOW | WS_MAXIMIZE

#else
 
// ! ������ â �ʱ�ȭ ��ũ��
#define WINSTART_X			400
#define WINSTART_Y			100

#define WINSIZE_X			1280
#define WINSIZE_Y			800

#define WINSIZE_X_HALF		WINSIZE_X / 2
#define WINSIZE_Y_HALF		WINSIZE_Y / 2

// WS_CAPTION : Ÿ��Ʋ�ٸ� ������ ���� �ɼ�
// WS_SYSMENU : ���� ǥ���ٿ� ��Ʈ�� �޴� ���� â
#define WINSTYLE			WS_CAPTION | WS_SYSMENU
#endif

// ! Ÿ�� ��ü �ʱ�ȭ ��ũ��
#define TILESIZE			64




// # ��ũ�� �Լ� #  ================================================================================================================
// Ŭ�������� �����Ҵ�� �κ� ����
// ��ũ�� �Լ��� 2�� �̻� �������� \�� ����ϸ� �ȴ�.
#define SAFE_DELETE(p)			{if(p) {delete(p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = nullptr;}}

// # ���� ���� # (������ ����) =======================================================================================================
// extern Ű����� �ٸ� ��� / cpp���� ������ �����ؼ� ���� ���� ����Ѵ�.
// �� ��ü�� �����ϱ� ���� ����ϸ� �� ����.
// �⺻������ ���� ������ Ű���带 �����ص� �⺻������ externȭ �Ǵ� ��찡 ����.
extern HINSTANCE		_hInstance;
extern HWND				_hWnd;
// X ��ǥ�� Y ��ǥ�� ����� ��ǥ�� ������ �� ����� �Ѵ�.
extern POINT			_ptMouse;