#include "Stdafx.h"
#include "Timer.h"

#include <mmsystem.h>
// TimeGetTime 함수를 사용하기 위한 라이브러리 추가
// 윈도우가 시작되고 난 뒤의 시간을 리턴
#pragma comment (lib, "winmm.lib")

Timer::Timer()
{
}

Timer::~Timer()
{
}

HRESULT Timer::init()
{
	// 좀 더 정확한 시간 값을 저장하기 위해 64비트 정수형을 사용 ( 1 / 1000000)
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
	{
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

void Timer::tick(float lockFPS)
{
	QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);

	// 한 프레임 당 경과량 구하기
	_timeElapsed = (_curTime - _prevTime) * _timeScale;

	if (lockFPS > 0.0f)
	{
		// 고정 프레임 (lockFPS)을 만족할 때 까지 반복
		while (_timeElapsed < (1.0f / lockFPS))
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);

			_timeElapsed = (_curTime - _prevTime) * _timeScale;
		}
	}

	_prevTime = _curTime;				// 이전 시간값 저장
	_FPSFrameCount++;					// 프레임 카운트 증가
	_FPSTimeElapsed += _timeElapsed;	// 초당 프레임 시간 경과량 증가
	_worldTime += _timeElapsed;			// 전체 시간 경과량 증가

	// 프레임 초기화를 1초마다 진행
	if (_FPSTimeElapsed > 1.0f)
	{
		_frameRate = _FPSFrameCount;
		_FPSFrameCount = 0;
		_FPSTimeElapsed = 0.0f;
	}
}

UINT Timer::getFrameRate(char* str) const
{
	if (str != NULL)
	{
		wsprintf(str, "FPS : %d", _frameRate);
	}

	return _frameRate;
}
