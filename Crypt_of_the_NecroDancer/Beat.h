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

		int distance;
		int alpha;

		float x, y;
		float speed;
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

private:
	vector<Note> _vNoteLeft;
	vector<Note> _vNoteRight;

	//vector<Note> _vNote;
	queue<int> _qNoteData;

	FrameImage _heartRate;
	POINT _eraseLine;

	unsigned int _noteCycle;

	bool _isBeat;				// ���ڰ� �´���
	bool _isSuccess;			// ���ڿ� ���� Ű �Է¿� �����ߴ���
	bool _isMusic;				// ���� ������ ����ǰ� �ִ���

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	void moveNote(vector<Note> &vNote);

	bool getBeat() { return _isBeat; }

	bool getSuccess() { return _isSuccess; }
	void setSuccess(bool isSuccess) { _isSuccess = isSuccess; }

	Beat() {}
	~Beat() {}
};

