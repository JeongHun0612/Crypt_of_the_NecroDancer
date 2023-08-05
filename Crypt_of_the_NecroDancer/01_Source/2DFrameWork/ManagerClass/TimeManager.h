#pragma once
#include "../DesingPattern/SingletonBase.h"

class TimeManager : public SingletonBase<TimeManager>
{
private:
	float _timeScale;				// 시간 경과량
	float _deltaTime;				// 한 프레임당 경과 시간 (한 틱)

	__int64 _curTime;				// 현재 시간
	__int64 _prevTime;				// 이전 프레임 시간
	__int64 _periodFrequency;		// 시간 주기

	unsigned long _frameRate;		// FPS
	unsigned long _FPSFrameCount;	// FPS 카운트

	float _FPSTimeElapsed;			// 한 프레임 당 경과량
	float _worldTime;				// 전체 시간 경과량

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