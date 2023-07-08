#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Slime_Green.h"

class LobbyScene : public GameNode
{
private:
	Player _player;

	GImage* _tile;

	vector<Slime> _vSlime;

	float _count;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	LobbyScene() {}
	~LobbyScene() {}
};

