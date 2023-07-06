#pragma once
#include "GameNode.h"

class BeatBox : public GameNode
{
public:
	struct BeatBar
	{
		GImage* img;
		POINT pos;
		RECT rc;

		int direction;
		float speed;
	};

private:
	GImage* _beatBoxImg;
	RECT _rc;

	vector<BeatBar> _vBeatBar;

	float _count;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void crateBeatBar();
	void moveBeatBar();

	BeatBox() {}
	~BeatBox() {}
};

