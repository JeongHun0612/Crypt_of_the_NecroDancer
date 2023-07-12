#include "Stdafx.h"
#include "TestCameraScene.h"

HRESULT TestCameraScene::init(void)
{
	_bg = IMAGEMANAGER->findImage("title");

	_camera.posCT = { 0.f, 0.f };
	_camera.posLT = { _camera.posCT.x - 300.f, _camera.posCT.y - 200.f };
	_camera.prevPos = { (float)WINSIZE_X_HALF, (float)WINSIZE_Y_HALF };
	_camera.rc = RectMakeCenter(_camera.posLT.x, _camera.posLT.y, 600, 400);

	_cameraDiff = { 0.f, 0.f };

	_player.pos = { (float)WINSIZE_X_HALF, (float)WINSIZE_Y_HALF };
	_player.rc = RectMakeCenter(_player.pos.x, _player.pos.y, 100, 100);

	_enemy.pos = { (float)WINSIZE_X_HALF - 100.f, (float)WINSIZE_Y_HALF - 100.f };
	_enemy.rc = RectMakeCenter(_enemy.pos.x, _enemy.pos.y, 50, 50);

	_mapPosLT = { 200.f, 200.f };

	return S_OK;
}

void TestCameraScene::release(void)
{
}

void TestCameraScene::update(void)
{
	_cameraDiff.x = (_player.pos.x - _camera.posCT.x) * TIMEMANAGER->getDeltaTime() * 5.f;
	_cameraDiff.y = (_player.pos.y - _camera.posCT.y) * TIMEMANAGER->getDeltaTime() * 5.f;

	_camera.posLT = { _camera.posCT.x - 300.f, _camera.posCT.y - 200.f };

	//_player.pos.x += ((float)WINSIZE_X_HALF - _player.pos.x) * TIMEMANAGER->getDeltaTime() * 5.f;
	//_player.pos.y += ((float)WINSIZE_Y_HALF - _player.pos.y) * TIMEMANAGER->getDeltaTime() * 5.f;

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_camera.posCT.x -= 64.f;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_camera.posCT.x += 64.f;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		_camera.posCT.y -= 64.f;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		_camera.posCT.y += 64.f;
	}
}

void TestCameraScene::render(void)
{
	char strPos[120];
	sprintf_s(strPos, "Camera.x : %f", _camera.posCT.x);
	TextOut(getMemDC(), WINSIZE_X - 200, 0, strPos, strlen(strPos));

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			RectangleMake(getMemDC(), _mapPosLT.x + (j * 64), _mapPosLT.y + (i * 64), 64, 64);
		}
	}

	// Ä«¸Þ¶ó

	//_camera.posCT.x -= _cameraDiff.x;
	//_camera.posCT.y -= _cameraDiff.y;

	RectangleMakeCenter(getMemDC(), _camera.posCT.x += _cameraDiff.x, _camera.posCT.y += _cameraDiff.y, 600, 400);

	RectangleMakeCenter(getMemDC(), _player.pos.x, _player.pos.y, 100, 100);
}
