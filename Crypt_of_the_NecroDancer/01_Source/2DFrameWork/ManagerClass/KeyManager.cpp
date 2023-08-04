#include "Stdafx.h"
#include "KeyManager.h"

HRESULT KeyManager::init(void)
{
	// 키 값을 전부 눌려있지 않은 상태로 초기화
	for (int i = 0; i < KEY_MAX; i++)
	{
		this->setKeyUp(i, false);
		this->setKeyDown(i, false);
	}

	return S_OK;
}

bool KeyManager::isOnceKeyDown(int key)
{
	/*
	▶ GetAsyncKeyState

	- 어떤 키가 입력된건지 체크 / 프로그램에서 키를 입력 받고 싶을 때 사용하는 API 공용 함수

	- 기본적으로 메세지 큐에 있는 키의 정보를 확인 한다.

	- 키가 눌린 시점을 체크하기 위해 &(AND) 연산을 사용해서 확인한다.

	0x0000
	0x0001
	0x8000
	0x8001
	*/

	// 비트 단위로 AND 연산을 한다.
	// ㄴ 둘다 1일 때만 결과가 1이고 / 아니라면 결과가 0
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!this->getKeyDown()[key])
		{
			this->setKeyDown(key, true);
			return true;
		}
	}
	else
	{
		this->setKeyDown(key, false);
	}

	return false;
}

bool KeyManager::isOnceKeyUp(int key)
{
	if (GetKeyState(key) & 0x8000)
	{
		this->setKeyUp(key, true);
	}
	else
	{
		if (this->getKeyUp()[key])
		{
			this->setKeyUp(key, false);
			return true;
		}
	}

	return false;
}

bool KeyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		return true;
	}

	return false;
}

bool KeyManager::isToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001)
	{
		return true;
	}

	return false;
}

bool KeyManager::isAnyKeyDown()
{
	for (int i = 0; i < KEY_MAX; i++)
	{
		if (GetAsyncKeyState(i) & 0x8000)
		{
			return true;
		}
	}

	return false;
}
