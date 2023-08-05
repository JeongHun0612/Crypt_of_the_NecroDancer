#pragma once
#include "../DesingPattern/SingletonBase.h"

class TimeManager : public SingletonBase<TimeManager>
{
private:
	float _timeScale;				// �ð� �����
	float _deltaTime;				// �� �����Ӵ� ��� �ð� (�� ƽ)

	__int64 _curTime;				// ���� �ð�
	__int64 _prevTime;				// ���� ������ �ð�
	__int64 _periodFrequency;		// �ð� �ֱ�

	unsigned long _frameRate;		// FPS
	unsigned long _FPSFrameCount;	// FPS ī��Ʈ

	float _FPSTimeElapsed;			// �� ������ �� �����
	float _worldTime;				// ��ü �ð� �����

public:
	HRESULT init();
	void update(float lockFPS = 0.0f);
	void render(HDC hdc);

	unsigned long getFrameRate() { return _frameRate; }
	float getDeltaTime()  { return _deltaTime; }
	float getWorldTime()  { return _worldTime; }

	TimeManager() {}
	~TimeManager() {}
};