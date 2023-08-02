#pragma once
#include "SingletonBase.h"

class Beat : public SingletonBase<Beat>
{
private:
	enum NOTE_DISTANCE
	{
		LEFT,
		RIGHT
	};

	struct Note
	{
		GImage* img;
		RECT rc;

		int alpha;
		int frameX;

		float x, y;
		float speed;

		bool isDestory;
	};

	struct Missed
	{
		GImage* img;
		float x, y;
		int alpha;
	};

private:
	const char* _soundName;				// ���� ���� �̸�

	vector<Note> _vNoteLeft;			// ���� ��Ʈ ����
	vector<Note> _vNoteRight;			// ������ ��Ʈ ����

	queue<int> _qNoteData;				// ���� ������ ��� ������
	unsigned int _noteCycle;			// ��Ʈ�� �����Ǵ� �ֱ�

	FrameImage _heartImg;				// ����ڵ� �̹���
	POINT _eraseLine;					// ����ڵ� �̹��� ����� ��Ʈ ���� ����

	RECT _beatRate;						// ��Ʈ ���� ���� ��Ʈ

	vector<Missed> _vMissed;			// ������ �̹��� ����
	GImage* _missedImg;					// ������ �̹���
	int _beatCount;						// ���� ����
	int _missedAlpha;					// ������ �̹��� ���İ�
	int _noteFrameX;					// ��Ʈ �̹��� ������X

	bool _isBeat;						// ���ڰ� �´���
	bool _isStep;						// �� ������ ��������
	bool _isMusic;						// ���� ������ ����ǰ� �ִ���
	bool _isMissed;						// ���ڿ� ���� Ű �Է¿� �����ߴ���
	bool _isSuccess;					// ���ڿ� ���� Ű �Է¿� �����ߴ���

public:
	HRESULT init();
	HRESULT init(const char* fileName, const char* soundName);
	void update(void);
	void render(HDC hdc);

	void createNote();

	void createMissed();
	void moveMissed();


	// Get / Set
	bool getIsBeat() { return _isBeat; }
	void setIsBeat(bool isBeat) { _isBeat = isBeat; }

	bool getIsMissed() { return _isMissed; }
	void setIsMissed(bool isMissed) { _isMissed = isMissed; }

	bool getIsSuccess() { return _isSuccess; }
	void setIsSuccess(bool isSuccess) { _isSuccess = isSuccess; }

	bool getIsStep() { return _isStep; }
	void setIsStep(bool isStep) { _isStep = isStep; }

	int getBeatCount() { return _beatCount; }

	RECT getBeatRate() { return _beatRate; }


	Beat() {}
	~Beat() {}
};

