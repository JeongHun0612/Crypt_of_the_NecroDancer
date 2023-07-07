#include "Stdafx.h"
#include "Beat.h"

HRESULT Beat::init(void)
{
	_heartRate.img = IMAGEMANAGER->findImage("beat_heart");
	_heartRate.rc = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y - 70, 180, 100);
	_heartRate.frameX = 0;
	_heartRate.frameY = 0;
	_heartRate.frameCount = 0.0f;

	_missed = IMAGEMANAGER->findImage("missed");

	return S_OK;
}

void Beat::release(void)
{
}

void Beat::update(void)
{
}

void Beat::render(void)
{
}
