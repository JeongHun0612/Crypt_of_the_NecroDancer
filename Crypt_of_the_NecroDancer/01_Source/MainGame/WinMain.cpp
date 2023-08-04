// stdafx.h : ���� ��������� ���� ��������� �ʴ� ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������ ��� �ִ� ���� �����Դϴ�.
#include "Stdafx.h"
#include "MainGame.h"

/*
�� TCHAR

- THCAR���� ������Ʈ�� ���ڼ� ������ ���� �ڵ������� char �Ǵ� wchar_t�� Type_Casting �Ǵ� �߰� ��ũ�� �ڷ���

- ��Ƽ ����Ʈ�� ���� �ڵ� ȯ�濡�� ������ ���� �۾� ���� ���α׷��� �����ϱ� ���ؼ��� TCHAR������ ���ڿ��� ǥ���� ���� ��õ

- �Ϲ������� ������ ���� ���α׷����� ���ڿ� ����� ���� ���ؼ��� �߰� ������ ���� char* �Ǵ� wchar_t*�� ��ȯ�� �ִ� _T ��ũ�θ� �̿��ؾ� �Ѵ�.

LPSTR       ->      Long Pointer       =    char*
LPCSTR      ->      Constant           =    const char*
LPCTSTR     ->      t_string           =    const tchar*
*/

HINSTANCE _hInstance;
HWND _hWnd;
POINT _ptMouse = { 0, 0 };


// �ݹ�
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

MainGame* _mg;

int APIENTRY WinMain(HINSTANCE hInstance,		 // hInstance       ->   ���α׷� �ν��Ͻ� �ڵ�
					 HINSTANCE hPrevInstance,	 // hPrevInstance   ->   ������ ����� �ν��Ͻ� �ڵ�
					 LPSTR    lpszCmdParam,		 // lpszCmdParam    ->   ��������� �Էµ� ���α׷� �μ�
					 int       nCmdShow)		 // nCmdShow        ->   ���α׷��� ���۵� ���� (�ּ�ȭ / ũ�� ���)
{

	_mg = new MainGame();

	// �ν��Ͻ��� ���� ������ ��´�.
	_hInstance = hInstance;

	// 1-1. ������â ����ü ���� �� �ʱ�ȭ
	// WNDCLASS : �� ����ü�� �������� �ü������ ������ ������ ����ϱ� ���ؼ�
	//            Ŀ������ �����츦 �ĺ��� �� �ִ� ���� ���� ����ϴ� ������ �����Ѵ�.
	WNDCLASS wndClass;

	wndClass.cbClsExtra = 0;                                            // Ŭ���� ���� �޸�
	wndClass.cbWndExtra = 0;                                            // ������ ���� �޸�
	wndClass.hbrBackground = (HBRUSH)(GetStockObject(WHITE_BRUSH));     // ��׶���
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);                     // ���콺 Ŀ��
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);                   // ������
	wndClass.hInstance = hInstance;                                     // �����츦 �ҿ��� ���α׷��� �ĺ��� ����
	wndClass.lpfnWndProc = (WNDPROC)WndProc;                            // ������ ���ν���
	wndClass.lpszClassName = WINNAME;									// Ŭ���� �̸� (�ĺ��� ����)
	wndClass.lpszMenuName = NULL;                                       // �޴� �̸�
	wndClass.style = CS_HREDRAW | CS_VREDRAW;                           // ������ ��Ÿ�� (�ٽ� �׸��� ����)


	// 1-2. ������ Ŭ���� ���
	RegisterClass(&wndClass);

// ��ũ�� Ÿ���� FULLSCREEN�� �� �ʿ��� ������ ����
#ifdef FULLSCREEN
	// ����̽� ��� ����ü (ȭ�� ���÷��� ���� ����ü)
	DEVMODE dm;

	ZeroMemory(&dm, sizeof(DEVMODE));	// �޸� �ʱ�ȭ

	dm.dmSize = sizeof(DEVMODE);
	dm.dmBitsPerPel = 32;				// 32��Ʈ Ʈ���÷�
	dm.dmPanningWidth = 1980;			// ���� �ػ�
	dm.dmPanningHeight = 1020;			// ���� �ػ�
	dm.dmDisplayFrequency = 60;			// �ֻ��� (����� 60Hz)

	// �ʵ� ����
	dm.dmFields = DM_BITSPERPEL | DM_PANNINGHEIGHT | DM_PANNINGHEIGHT | DM_DISPLAYFREQUENCY;

	if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
	{
		ChangeDisplaySettings(&dm, 0);
	}
#endif

	// 1-3. ȭ�鿡 ������ ������ â ����
	_hWnd = CreateWindow
	(
		WINNAME,				// ������ Ŭ���� �ĺ���
		WINNAME,				// ������ Ÿ��Ʋ �� �̸�
		WINSTYLE,				// ������ ��Ÿ��
		WINSTART_X,             // ������ ȭ�� X ��ǥ
		WINSTART_Y,             // ������ ȭ�� Y ��ǥ
		WINSIZE_X,              // ������ ȭ�� ���� ũ��
		WINSIZE_Y,              // ������ ȭ�� ���� ũ��
		NULL,                   // �θ� ������ -> GetDesktopWindow
		(HMENU)NULL,            // �޴� �ڵ�
		hInstance,              // �ν��Ͻ� ����
		NULL                    // �������� �ڽ� �����츦 �����ϸ� �����ϰ� �׷��� �ʴٸ� NULL�� ��ƶ�
								//  �� �ʿ信 ���ؼ� ����ϱ⵵ ������ ������ NULL
	);

	// Ŭ���̾�Ʈ ������ ����� ��Ȯ�� ����ֱ� ����
	setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

	// 1-4. ȭ�鿡 ������â �����ֱ�
	ShowWindow(_hWnd, nCmdShow);

	// ���� ���� Ŭ���� �ʱ�ȭ�� �����ϸ� ����
	if (FAILED(_mg->init()))
	{
		return 0;
	}


	// 2. �޼��� ����
	// MSG : �ü������ �߻��ϴ� �޼��� ������ �����ϱ� ���� ����ü
	MSG message;

	/*
	�ڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡ�
	�� �޼��� ���� ����

	1. GetMessage
	�� �޼����� ���� �� �� ���������� �����ִ� �Լ� (���)
	�� GetMessage�� �޼��� ť�κ��� �ϳ��� �޼����� �������� ������ �����Ѵ�.
	�� ��, �޼��� ť�� ��� ���� ��� �޼�����(�߻��� �޼��� X) ���ö����� ����Ѵ�.

	2. PeekMessage (���ӿ��� �ַ� ����ϴ� �޼��� ����)
	�� �޼����� ������ ��ȯ �Ǵ� �Լ�

	TranslateMessage
	�� Ű������ �Է� �޽��� ó���� ���
	�� �Էµ� Ű�� ����Ű���� Ȯ�� �� �빮�� Ȥ�� �ҹ���, �ѱ� / ���������� ���� WH_CHAR �޼����� �߻� ��Ų��.

	DispatchMessage
	�� ������ ���ν������� ���޵� �޼����� ���� ������� ������ �ش�.
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
�� Window Procedure
�� �޼����� �ü���� ���� -> ������ �ü���� ȣ��ǰ� ���ش�.
�� WinMain()�� �ƴ� �ü���� ���� ȣ���� �Ǵ� �ݹ�(Callback) �Լ�
�� �����츦 ������ �� �ݵ�� ������ ����� �Ѵ�.

- ����ؾ� �Ұ� ������ ���ν��� ���ο����� �����쿡�� �߻��� ��� �޼����� ó���ϴ� ���� �ƴ϶�
  Ư�� �޼������� ó���ϰ� ������ �޼����� DefWindowProc �Լ��� ó���ϵ��� ������ �����ϴ°� �Ϲ����̴�.

�� �� ������ �ݵ�� ����Ұ�

hWnd		->		��� �����쿡�� �߻��� �޼������� ����
iMessage	->		�޼��� ���� ��ȣ
wParam		->		unsigned int -> ���콺 ��ư�� ����, Ű���� ���� Ű�� ���¸� ����
lParam		->		unsigned long -> ���콺 Ŭ�� ��ǥ�� ����


�� WM_PAINT

- �����츦 �ٽ� �׷��� �Ҷ� ����ϴ� �޼���

1. �����찡 ó�� �����������
2. ������ ũ�⸦ �����ϰ� ������
3. �����찡 �ٸ� �����쿡 �������ٰ� �ٽ� ���϶�
4. Ư�� �Լ��� ȣ���� �� �� -> InvalidateRect, Invalidate, UpdateAllViews ���..
	�� �⺻������ ������ ���õ� �Լ��� ������ PAINT�� ���÷��� �Ѵ�.

*/

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _mg->MainProc(hWnd, iMessage, wParam, lParam);
}

void setWindowSize(int x, int y, int width, int height)
{
	RECT rc = { 0, 0, width, height };

	// ���� ������ ũ�� ����
	AdjustWindowRect(&rc, WINSTYLE, false);

	// ���� ��Ʈ�� ������ ������ ������ ����
	// ZORDER : �̹��� ���� ���̾ ���� ó���� �ϴ� ���
	// NOZORDER : �̹��� ���̾ �������� �ʰڴ�.
	SetWindowPos(_hWnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top), SWP_NOZORDER | SWP_NOMOVE);
}