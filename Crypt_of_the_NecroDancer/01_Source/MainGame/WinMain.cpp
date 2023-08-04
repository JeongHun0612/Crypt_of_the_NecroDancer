// stdafx.h : 자주 사용하지만 자주 변경되지는 않는 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이 들어 있는 포함 파일입니다.
#include "Stdafx.h"
#include "MainGame.h"

/*
▶ TCHAR

- THCAR형은 프로젝트의 문자셋 설정에 따라 자동적으로 char 또는 wchar_t로 Type_Casting 되는 중간 매크로 자료형

- 멀티 바이트와 유니 코드 환경에서 별도의 수정 작업 없이 프로그램을 구동하기 위해서는 TCHAR형으로 문자열을 표현할 것을 추천

- 일반적으로 윈도우 응용 프로그램에서 문자열 상수를 쓰기 위해서는 중간 설정에 따라 char* 또는 wchar_t*로 변환해 주는 _T 매크로를 이용해야 한다.

LPSTR       ->      Long Pointer       =    char*
LPCSTR      ->      Constant           =    const char*
LPCTSTR     ->      t_string           =    const tchar*
*/

HINSTANCE _hInstance;
HWND _hWnd;
POINT _ptMouse = { 0, 0 };


// 콜백
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

MainGame* _mg;

int APIENTRY WinMain(HINSTANCE hInstance,		 // hInstance       ->   프로그램 인스턴스 핸들
					 HINSTANCE hPrevInstance,	 // hPrevInstance   ->   이전에 실행된 인스턴스 핸들
					 LPSTR    lpszCmdParam,		 // lpszCmdParam    ->   명령형으로 입력된 프로그램 인수
					 int       nCmdShow)		 // nCmdShow        ->   프로그램이 시작될 형태 (최소화 / 크기 등등)
{

	_mg = new MainGame();

	// 인스턴스를 전역 변수에 담는다.
	_hInstance = hInstance;

	// 1-1. 윈도우창 구조체 선언 및 초기화
	// WNDCLASS : 이 구조체는 윈도우즈 운영체제에서 윈도우 생성을 명령하기 위해서
	//            커스텀한 윈도우를 식별할 수 있는 정보 등을 기록하는 역학을 수행한다.
	WNDCLASS wndClass;

	wndClass.cbClsExtra = 0;                                            // 클래스 여분 메모리
	wndClass.cbWndExtra = 0;                                            // 윈도우 여분 메모리
	wndClass.hbrBackground = (HBRUSH)(GetStockObject(WHITE_BRUSH));     // 백그라운드
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);                     // 마우스 커서
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);                   // 아이콘
	wndClass.hInstance = hInstance;                                     // 윈도우를 소요할 프로그램의 식별자 정보
	wndClass.lpfnWndProc = (WNDPROC)WndProc;                            // 윈도우 프로시저
	wndClass.lpszClassName = WINNAME;									// 클래스 이름 (식별자 정보)
	wndClass.lpszMenuName = NULL;                                       // 메뉴 이름
	wndClass.style = CS_HREDRAW | CS_VREDRAW;                           // 윈도우 스타일 (다시 그리기 정보)


	// 1-2. 윈도우 클래스 등록
	RegisterClass(&wndClass);

// 스크린 타입이 FULLSCREEN일 시 필요한 데이터 선언
#ifdef FULLSCREEN
	// 디바이스 모드 구조체 (화면 디스플레이 관련 구조체)
	DEVMODE dm;

	ZeroMemory(&dm, sizeof(DEVMODE));	// 메모리 초기화

	dm.dmSize = sizeof(DEVMODE);
	dm.dmBitsPerPel = 32;				// 32비트 트루컬러
	dm.dmPanningWidth = 1980;			// 가로 해상도
	dm.dmPanningHeight = 1020;			// 세로 해상도
	dm.dmDisplayFrequency = 60;			// 주사율 (재생빈도 60Hz)

	// 필드 설정
	dm.dmFields = DM_BITSPERPEL | DM_PANNINGHEIGHT | DM_PANNINGHEIGHT | DM_DISPLAYFREQUENCY;

	if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
	{
		ChangeDisplaySettings(&dm, 0);
	}
#endif

	// 1-3. 화면에 보여줄 윈도우 창 생성
	_hWnd = CreateWindow
	(
		WINNAME,				// 윈도우 클래스 식별자
		WINNAME,				// 윈도우 타이틀 바 이름
		WINSTYLE,				// 윈도우 스타일
		WINSTART_X,             // 윈도우 화면 X 좌표
		WINSTART_Y,             // 윈도우 화면 Y 좌표
		WINSIZE_X,              // 윈도우 화면 가로 크기
		WINSIZE_Y,              // 윈도우 화면 세로 크기
		NULL,                   // 부모 윈도우 -> GetDesktopWindow
		(HMENU)NULL,            // 메뉴 핸들
		hInstance,              // 인스턴스 지정
		NULL                    // 윈도우의 자식 윈도우를 생성하면 지정하고 그렇지 않다면 NULL을 잡아라
								//  ㄴ 필요에 의해서 사용하기도 하지만 지금은 NULL
	);

	// 클라이언트 영역의 사이즈를 정확히 잡아주기 위해
	setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

	// 1-4. 화면에 윈도우창 보여주기
	ShowWindow(_hWnd, nCmdShow);

	// 메인 게임 클래스 초기화를 실패하면 종료
	if (FAILED(_mg->init()))
	{
		return 0;
	}


	// 2. 메세지 루프
	// MSG : 운영체제에서 발생하는 메세지 정보를 저장하기 위한 구조체
	MSG message;

	/*
	★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
	▶ 메세지 루프 종류

	1. GetMessage
	ㄴ 메세지를 꺼내 올 수 있을때까지 멈춰있는 함수 (대기)
	ㄴ GetMessage는 메세지 큐로부터 하나의 메세지를 가져오는 역할을 수행한다.
	ㄴ 단, 메세지 큐가 비어 있을 경우 메세지가(발생한 메세지 X) 들어올때까지 대기한다.

	2. PeekMessage (게임에서 주로 사용하는 메세지 루프)
	ㄴ 메세지가 없더라도 반환 되는 함수

	TranslateMessage
	ㄴ 키보드의 입력 메시지 처리를 담당
	ㄴ 입력된 키가 문자키인지 확인 후 대문자 혹은 소문자, 한글 / 영문인지에 대해 WH_CHAR 메세지를 발생 시킨다.

	DispatchMessage
	ㄴ 윈도우 프로시저에서 전달된 메세지를 실제 윈도우로 전달해 준다.
	*/

	while (true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;

			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			TIMEMANAGER->update(60.0f);
			SOUNDMANAGER->update();

			_mg->update();
			_mg->render();
		}
	}

	_mg->release();
	delete(_mg);
	UnregisterClass(WINNAME, hInstance);

	return (int)message.wParam;
}

/*
▶ Window Procedure
ㄴ 메세지를 운영체제에 전달 -> 강제로 운영체제가 호출되게 해준다.
ㄴ WinMain()이 아닌 운영체제에 의해 호출이 되는 콜백(Callback) 함수
ㄴ 윈도우를 생성할 때 반드시 지정을 해줘야 한다.

- 기억해야 할건 윈도우 프로시저 내부에서는 윈도우에서 발생한 모든 메세지를 처리하는 것이 아니라
  특정 메세지만을 처리하고 나머지 메세지는 DefWindowProc 함수가 처리하도록 로직을 설계하는게 일반적이다.

※ 위 내용은 반드시 기억할것

hWnd		->		어느 윈도우에서 발생한 메세지인지 구분
iMessage	->		메세지 구분 번호
wParam		->		unsigned int -> 마우스 버튼의 상태, 키보드 조합 키의 상태를 전달
lParam		->		unsigned long -> 마우스 클릭 좌표를 전달


▶ WM_PAINT

- 윈도우를 다시 그려야 할때 사용하는 메세지

1. 윈도우가 처음 만들어졌을때
2. 윈도우 크기를 조절하고 싶을때
3. 윈도우가 다른 윈도우에 가려졌다가 다시 보일때
4. 특정 함수가 호출이 될 때 -> InvalidateRect, Invalidate, UpdateAllViews 등등..
	ㄴ 기본적으로 렌더링 관련된 함수가 나오면 PAINT를 떠올려야 한다.

*/

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _mg->MainProc(hWnd, iMessage, wParam, lParam);
}

void setWindowSize(int x, int y, int width, int height)
{
	RECT rc = { 0, 0, width, height };

	// 실제 윈도우 크기 조정
	AdjustWindowRect(&rc, WINSTYLE, false);

	// 얻어온 렉트의 정보로 윈도우 사이즈 셋팅
	// ZORDER : 이미지 간의 레이어에 대한 처리를 하는 기법
	// NOZORDER : 이미지 레이어를 비켜주지 않겠다.
	SetWindowPos(_hWnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top), SWP_NOZORDER | SWP_NOMOVE);
}