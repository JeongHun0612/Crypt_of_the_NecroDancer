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

	bool _isBeat;				// 박자가 맞는지
	bool _isSuccess;			// 박자에 맞춰 키 입력에 성공했는지
	bool _isMusic;				// 현재 음악이 재생되고 있는지

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

