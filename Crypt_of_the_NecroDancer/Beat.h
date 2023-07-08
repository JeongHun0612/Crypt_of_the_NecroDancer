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

	FrameImage _heartRate;

	float _noteCreateCycle;

	bool _isBeat;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	bool getBeat() { return _isBeat; }

	Beat() {}
	~Beat() {}
};

