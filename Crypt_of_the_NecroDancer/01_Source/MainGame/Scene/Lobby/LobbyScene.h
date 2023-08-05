#pragma once
#include "../Stage/GameScene.h"

class LobbyScene : public GameScene
{
private:

public:
	HRESULT init();
	void release();
	void update();
	void render();

	LobbyScene() {}
	~LobbyScene() {}
};

