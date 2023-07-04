#include "Stdafx.h"
#include "GameNode.h"

HRESULT GameNode::init(void)
{
	return S_OK;
}

HRESULT GameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (managerInit)
	{
		// 타이머 초기화
		SetTimer(_hWnd, 1, 10, NULL);

		RND->init();
		KEYMANAGER->init();
		IMAGEMANAGER->init();
	}

	return S_OK;
}

void GameNode::release(void)
{
	if (_managerInit)
	{
		// 동적할당과 같이 삭제하지 않고 종료하면 메모리 누수가 발생한다.
		KillTimer(_hWnd, 1);

		RND->releaseSingleton();
		KEYMANAGER->releaseSingleton();
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
	}

	ReleaseDC(_hWnd, _hdc);
}

void GameNode::update(void)
{
	InvalidateRect(_hWnd, NULL, false);
}

void GameNode::render(void)
{
	//! Do Noting
}

// 메인 프로시저
LRESULT GameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_TIMER:
		this->update();
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		this->render();

		EndPaint(hWnd, &ps);
		break;

	case WM_MOUSEMOVE:
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;

	case WM_DESTROY: // 소멸자
		// PostQuitMessage() : 이 함수는 메세지 큐에 Quit 메세지를 보내는 역할을 한다.
		// 즉, Quit 메세지를 수신하는 순간 GetMessage 함수가 FALSE를 반환함으로 메세지 루프가 종료된다.
		PostQuitMessage(0);
		return 0;
	}

	// 윈도우 프로시저에서 처리되지 않은 나머지 메세지를 처리해 준다.
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}