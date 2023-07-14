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

		float x, y;
		float speed;

		bool isDestory;
	};

	struct FrameImage
	{
		GImage* img;
		RECT rc;

		float x, y;
		int frameX;
		int frameY;
		float frameCount;
	};

	struct Missed
	{
		GImage* img;
		float x, y;
		int alpha;
	};

private:
	vector<Note> _vNoteLeft;			// ���� ��Ʈ ����
	vector<Note> _vNoteRight;			// ������ ��Ʈ ����

	queue<int> _qNoteData;				// ���� ������ ��� ������
	unsigned int _noteCycle;			// ��Ʈ�� �����Ǵ� �ֱ�

	FrameImage _heartRate;				// ����ڵ� �̹���
	POINT _eraseLine;					// ����ڵ� �̹��� ����� ��Ʈ ���� ����

	vector<Missed> _vMissed;			// ������ �̹��� ����
	GImage* _missedImg;					// ������ �̹���
	int _missedAlpha;					// ������ �̹��� ���İ�

	bool _isBeat;						// ���ڰ� �´���
	bool _isMusic;						// ���� ������ ����ǰ� �ִ���
	bool _isMissed;						// ���ڿ� ���� Ű �Է¿� �����ߴ���
	bool _isSuccess;					// ���ڿ� ���� Ű �Է¿� �����ߴ���

public:
	HRESULT init(void);
	void update(void);
	void render(HDC hdc);

	void createNote();

	void createMissed();
	void moveMissed();

	bool getBeat() { return _isBeat; }

	bool getIsMissed() { return _isMissed; }
	void setIsMissed(bool isMissed) { _isMissed = isMissed; }

	bool getIsSuccess() { return _isSuccess; }
	void setIsSuccess(bool isSuccess) { _isSuccess = isSuccess; }

	Beat() {}
	~Beat() {}
};

