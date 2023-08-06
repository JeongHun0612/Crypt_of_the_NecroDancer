#pragma once

// 4005라는 경고를 무시하겠다.
#pragma warning(disable : 4005)
// 4005 : DXGI 등 그래픽 인터페이스에서 매크로 관련하여 출력되는 경고

// SDKDDKVER.h는 프로그램에서 지원할 OS 혹은 라이브러리에 따라 Windows 헤더에서 코드가 포함될 함수 / 상수 등을 제어하는데 사용 한다.
#include <SDKDDKVER.h>

// 거의 사용되지 않는 내용은 Windows 헤더에서 제외
// ㄴ GDI+를 사용하려면 헤더파일에서 꺼내와야 한다.
//#include <ole2.h>
#define WIN32_LEAN_AND_MEAN

// 디버깅 콘솔창
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

// ! 라이브러리 추가 ============================================================================================================
#pragma comment (lib, "msimg32.lib")

//! Windows 헤더 파일 ============================================================================================================
#include <Windows.h>

//! C 런타임 헤더 파일 ============================================================================================================
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <time.h>
#include <tchar.h>
#include <stdio.h>


//! C++ 런타임 헤더 파일 ============================================================================================================
#include <iostream>
#include <fstream>
#include <istream>
#include <string>

// C++11에서 추가된 시간 관련 라이브러리 (STL)
#include <chrono>		
#include <random>
#include <vector>
#include <queue>
#include <stack>
#include <map>

/*
unordered_map : Hash 자료구조
ㄴ 일반적 상황에서 map보다 검색속도가 더 빠르다.
ㄴ 검색 속도가 빠른 이유는 중복된 데이터를 허용하지 않기 때문이다.
	단, 유사 데이터가 많을 시 (key), 해쉬 충돌이 발생할 여지가 생기기 때문에 성능 저하가 발생한다.
*/
#include <unordered_map>
#include <cassert>

// bitset : 비트 연산을 좀 더 쉽게 관리해 주는 함수를 지원하는 STL
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
// ! D2D/D3D 헤더 파일 ============================================================================================================
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

// # 사용자 정의 헤더 파일 # ================================================================================================
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


// # 싱글톤 # ==============================================================================================================
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

// # 매크로 #  ==============================================================================================================


// ! 타이틀
#define WINNAME				(LPTSTR)(TEXT("Crypt of the NecroDancer"))

// ! 전체 화면 
//#define FULLSCREEN

#ifdef FULLSCREEN
#define WINSTART_X		0
#define WINSTART_Y		0
//GetSystemMetrics() : 인자로 전달되는 시스템 설정 정보를 반환
// ㄴ SM_CXSCREEN + SM_CYSCREEN = 현재 화면 해상도 X / Y 축 반환
#define WINSIZE_X		GetSystemMetrics(SM_CXSCREEN)  
#define WINSIZE_Y		GetSystemMetrics(SM_CYSCREEN)

#define WINSIZE_X_HALF		WINSIZE_X / 2
#define WINSIZE_Y_HALF		WINSIZE_Y / 2
#define WINSTYLE		WS_POPUPWINDOW | WS_MAXIMIZE

#else
 
// ! 윈도우 창 초기화 매크로
#define WINSTART_X			400
#define WINSTART_Y			100

#define WINSIZE_X			1280
#define WINSIZE_Y			800

#define WINSIZE_X_HALF		WINSIZE_X / 2
#define WINSIZE_Y_HALF		WINSIZE_Y / 2

// WS_CAPTION : 타이틀바를 가지기 위한 옵션
// WS_SYSMENU : 제목 표시줄에 컨트롤 메뉴 상자 창
#define WINSTYLE			WS_CAPTION | WS_SYSMENU
#endif

// ! 타일 객체 초기화 매크로
#define TILESIZE			64




// # 매크로 함수 #  ================================================================================================================
// 클래스에서 동적할당된 부분 해제
// 매크로 함수가 2줄 이상 내려갈때 \를 사용하면 된다.
#define SAFE_DELETE(p)			{if(p) {delete(p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = nullptr;}}

// # 전역 변수 # (데이터 영역) =======================================================================================================
// extern 키워드는 다른 헤더 / cpp에서 변수를 공유해서 쓰기 위해 사용한다.
// ㄴ 객체를 공유하기 위해 사용하면 더 좋다.
// 기본적으로 전역 변수는 키워드를 생략해도 기본적으로 extern화 되는 경우가 많다.
extern HINSTANCE		_hInstance;
extern HWND				_hWnd;
// X 좌표와 Y 좌표를 평면의 좌표에 정의할 때 사용을 한다.
extern POINT			_ptMouse;