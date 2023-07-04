#pragma once
#include "GameNode.h"
#include "TitleScene.h"
#include "LobbyScene.h"

class MainGame : public GameNode
{
private:
	RECT rc;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	MainGame() {}
	~MainGame() {}
};