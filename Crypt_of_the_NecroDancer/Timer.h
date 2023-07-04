#pragma once
class Timer
{
private:
	float _timeScale;				// �ð� �����
	float _timeElapsed;				// �� �����Ӵ� ��� �ð� (�� ƽ)

	__int64 _curTime;				// ���� �ð�
	__int64 _prevTime;				// ���� ������ �ð�
	__int64 _periodFrequency;		// �ð� �ֱ�

	UINT _frameRate;				// FPS
	UINT _FPSFrameCount;			// FPS ī��Ʈ

	float _FPSTimeElapsed;			// �� ������ �� �����
	float _worldTime;				// ��ü �ð� �����

public:
	Timer();
	~Timer();

	HRESULT init();

	// ���� �ð� ���
	void tick(float lockFPS = 0.0f);
	UINT getFrameRate(char* str = nullptr) const;
	float getElapsedTime() const { return _timeElapsed; }
	float getWorldTime() const { return _worldTime; }
};

