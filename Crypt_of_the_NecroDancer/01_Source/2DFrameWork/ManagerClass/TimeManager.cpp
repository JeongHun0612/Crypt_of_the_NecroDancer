#include "../PCH/Stdafx.h"
#include "TimeManager.h"

HRESULT TimeManager::init()
{
	// 좀 더 정확한 시간 값을 저장하기 위해 64비트 정수형을 사용 ( 1 / 1000000)
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
	{
		// 이전 시간을 받아온다.
		QueryPerformanceCounter((LARGE_INTEGER*)&_prevTime);

		// 초당 시간 계산 범위
		_timeScale = 1.0f / _periodFrequency;
	}

	_frameRate = 0;
	_FPSFrameCount = 0;
	_FPSTimeElapsed = 0;
	_worldTime = 0.0f;

	return S_OK;
}

void TimeManager::update(float lockFPS)
{
	QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);

	//_deltaTime = (현재 시간 - 지난 프레임에 체킹한 시간) * _timeScale;
	_deltaTime = (_curTime - _prevTime) * _timeScale;

	if (lockFPS > 0.0f)
	{
		// 고정 프레임 (lockFPS)을 만족할 때 까지 반복
		while (_deltaTime < (1.0f / lockFPS))
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);

			_deltaTime = (_curTime - _prevTime) * _timeScale;
		}
	}

	_prevTime = _curTime;				// 이전 시간값 저장
	_FPSFrameCount++;					// 프레임 카운트 증가
	_FPSTimeElapsed += _deltaTime;		// 초당 프레임 시간 경과량 증가
	_worldTime += _deltaTime;			// 전체 시간 경과량 증가

	// 프레임 초기화를 1초마다 진행
	if (_FPSTimeElapsed > 1.0f)
	{
		_frameRate = _FPSFrameCount;
		_FPSFrameCount = 0;
		_FPSTimeElapsed = 0.0f;
	}
}

void TimeManager::render(HDC hdc)
{
	char strFrame[256];



	// FPS
	sprintf_s(strFrame, "FramePerSec : %d", _frameRate);
	TextOut(hdc, 10, WINSIZE_Y - 80, strFrame, strlen(strFrame));

	// 월드 타임 (전체 경과 시간)
	sprintf_s(strFrame, "WorldTime : %f", _worldTime);
	TextOut(hdc, 10, WINSIZE_Y - 60, strFrame, strlen(strFrame));

	// 한 프레임당 경과 시간
	sprintf_s(strFrame, "DeltaTime : %f", _deltaTime);
	TextOut(hdc, 10, WINSIZE_Y - 40, strFrame, strlen(strFrame));
}
