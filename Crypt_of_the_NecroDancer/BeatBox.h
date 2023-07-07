#pragma once
#include "GameNode.h"

class BeatBox : public GameNode
{
public:
	enum BEATBAR_DIRECTION : int
	{
		LEFT,
		RIGHT
	};

	struct BeatBar
	{
		GImage* img;
		RECT rc;

		int direction;

		int x, y;
		float speed;
	};

	struct AlphaImage
	{
		GImage* img;
		float x, y;
		BYTE alpha;
	};

private:
	GImage* _beatBoxImg;
	RECT _rc;

	vector<BeatBar*> _vBeatBar;

	AlphaImage _missed;

	float _count;
	bool _isMissed;

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

