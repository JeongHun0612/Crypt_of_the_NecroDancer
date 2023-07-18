#pragma once
#include "GameNode.h"
#include "Player.h"

class GameScene : public GameNode
{
private:


	int _nextIdxX;
	int _nextIdxY;
	PLAYER_DIRECTION _nextDirection;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

