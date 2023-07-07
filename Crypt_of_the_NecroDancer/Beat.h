#pragma once
#include "SingletonBase.h"
class Beat : public SingletonBase<Beat>
{
private:
	struct Note
	{
		GImage* img;
		RECT rc;

		float x, y;
		float speed;
	};

	struct FrameImage
	{
		GImage* img;
		RECT rc;

		int frameX;
		int frameY;
		float frameCount;
	};

private:
	vector<Note> _vNote;

	FrameImage _heartRate;
	GImage* _missed;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	Beat() {}
	~Beat() {}
};

