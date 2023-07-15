#include "Stdafx.h"
#include "GameNode.h"

HRESULT GameNode::init(void)
{
	_hdc = GetDC(_hWnd);
	_managerInit = false;

	return S_OK;
}

HRESULT GameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (managerInit)
	{
		// ������ ����
		// �� ���α׷��� ��ɾ �������� ���� �־��� �ִ� ��� ���߿� � ����� ���� ����� �������� ���� ����
		setlocale(LC_ALL, "korean");

		// �̱��� �Ŵ��� �ʱ�ȭ
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		TIMEMANAGER->init();
		SCENEMANAGER->init();
		SOUNDMANAGER->init();

		// �̱��� Ŭ���� �ʱ�ȭ
		RND->init();
		CAMERA->init();
	}

	return S_OK;
}

void GameNode::release(void)
{
	if (_managerInit)
	{
		// �̱��� �Ŵ��� ����
		KEYMANAGER->releaseSingleton();

		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		
		TIMEMANAGER->releaseSingleton();

		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();

		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();

		UIMANAGER->releaseSingleton();


		// �̱��� Ŭ���� ����
		RND->releaseSingleton();
		PLAYER->release();
		PLAYER->releaseSingleton();
		BEAT->releaseSingleton();
		CAMERA->release();
		CAMERA->releaseSingleton();
	}

	ReleaseDC(_hWnd, _hdc);
}

void GameNode::update(void)
{
	//! Do Noting
	//InvalidateRect(_hWnd, NULL, false);
}

void GameNode::render(void)
{
	//! Do Noting
}

// ���� ���ν���
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
	case WM_KEYDOWN:
		switch (wParam)
		{
			
		}
		break;
	case WM_MOUSEMOVE:
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;

	case WM_DESTROY: // �Ҹ���
		// PostQuitMessage() : �� �Լ��� �޼��� ť�� Quit �޼����� ������ ������ �Ѵ�.
		// ��, Quit �޼����� �����ϴ� ���� GetMessage �Լ��� FALSE�� ��ȯ������ �޼��� ������ ����ȴ�.
		PostQuitMessage(0);
		return 0;
	}

	// ������ ���ν������� ó������ ���� ������ �޼����� ó���� �ش�.
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}