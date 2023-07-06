#pragma once
#include "GameNode.h"
#include "Player.h"
#include "BeatBox.h"
#include "Slime_Green.h"

class LobbyScene : public GameNode
{
private:
	BeatBox _beatBox;

	Player _player;

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

