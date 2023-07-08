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

		float x, y;
		float speed;

		int alpha;
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
	vector<Note> _vNote;
	queue<int> _qNoteData;

	FrameImage _heartRate;

	unsigned int _noteCycle;

	bool _isBeat;
	bool _isMusic;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	bool getBeat() { return _isBeat; }

	Beat() {}
	~Beat() {}
};

