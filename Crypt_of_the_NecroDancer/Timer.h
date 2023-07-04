#pragma once
class Timer
{
private:
	float _timeScale;				// 시간 경과량
	float _timeElapsed;				// 한 프레임당 경과 시간 (한 틱)

	__int64 _curTime;				// 현재 시간
	__int64 _prevTime;				// 이전 프레임 시간
	__int64 _periodFrequency;		// 시간 주기

	UINT _frameRate;				// FPS
	UINT _FPSFrameCount;			// FPS 카운트

	float _FPSTimeElapsed;			// 한 프레임 당 경과량
	float _worldTime;				// 전체 시간 경과량

public:
	Timer();
	~Timer();

	HRESULT init();

	// 현재 시간 계산
	void tick(float lockFPS = 0.0f);
	UINT getFrameRate(char* str = nullptr) const;
	float getElapsedTime() const { return _timeElapsed; }
	float getWorldTime() const { return _worldTime; }
};

