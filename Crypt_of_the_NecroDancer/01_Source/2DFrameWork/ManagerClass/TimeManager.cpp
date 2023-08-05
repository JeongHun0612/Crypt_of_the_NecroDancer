#include "../PCH/Stdafx.h"
#include "TimeManager.h"

HRESULT TimeManager::init()
{
	// �� �� ��Ȯ�� �ð� ���� �����ϱ� ���� 64��Ʈ �������� ��� ( 1 / 1000000)
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
	{
		// ���� �ð��� �޾ƿ´�.
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

void TimeManager::update(float lockFPS)
{
	QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);

	//_deltaTime = (���� �ð� - ���� �����ӿ� üŷ�� �ð�) * _timeScale;
	_deltaTime = (_curTime - _prevTime) * _timeScale;

	if (lockFPS > 0.0f)
	{
		// ���� ������ (lockFPS)�� ������ �� ���� �ݺ�
		while (_deltaTime < (1.0f / lockFPS))
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);

			_deltaTime = (_curTime - _prevTime) * _timeScale;
		}
	}

	_prevTime = _curTime;				// ���� �ð��� ����
	_FPSFrameCount++;					// ������ ī��Ʈ ����
	_FPSTimeElapsed += _deltaTime;		// �ʴ� ������ �ð� ����� ����
	_worldTime += _deltaTime;			// ��ü �ð� ����� ����

	// ������ �ʱ�ȭ�� 1�ʸ��� ����
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

	// ���� Ÿ�� (��ü ��� �ð�)
	sprintf_s(strFrame, "WorldTime : %f", _worldTime);
	TextOut(hdc, 10, WINSIZE_Y - 60, strFrame, strlen(strFrame));

	// �� �����Ӵ� ��� �ð�
	sprintf_s(strFrame, "DeltaTime : %f", _deltaTime);
	TextOut(hdc, 10, WINSIZE_Y - 40, strFrame, strlen(strFrame));
}
