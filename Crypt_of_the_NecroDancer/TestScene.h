#pragma once
#include "GameNode.h"

class TestScene : public GameNode
{
public:
	struct Tile
	{
		POINT imgNum;
		POINT posIdx;
		bool isColiider;
	};

private:
	vector<Tile*> _tile;

	float _time;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

