#include "Stdafx.h"
#include "Timer.h"

#include <mmsystem.h>
// TimeGetTime �Լ��� ����ϱ� ���� ���̺귯�� �߰�
// �����찡 ���۵ǰ� �� ���� �ð��� ����
#pragma comment (lib, "winmm.lib")

Timer::Timer()
{
}

Timer::~Timer()
{
}

HRESULT Timer::init()
{
	// �� �� ��Ȯ�� �ð� ���� �����ϱ� ���� 64��Ʈ �������� ��� ( 1 / 1000000)
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&_prevTime);

		// �ʴ� �ð� ��� ����
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

	// �� ������ �� ����� ���ϱ�
	_timeElapsed = (_curTime - _prevTime) * _timeScale;

	if (lockFPS > 0.0f)
	{
		// ���� ������ (lockFPS)�� ������ �� ���� �ݺ�
		while (_timeElapsed < (1.0f / lockFPS))
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);

			_timeElapsed = (_curTime - _prevTime) * _timeScale;
		}
	}

	_prevTime = _curTime;				// ���� �ð��� ����
	_FPSFrameCount++;					// ������ ī��Ʈ ����
	_FPSTimeElapsed += _timeElapsed;	// �ʴ� ������ �ð� ����� ����
	_worldTime += _timeElapsed;			// ��ü �ð� ����� ����

	// ������ �ʱ�ȭ�� 1�ʸ��� ����
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
