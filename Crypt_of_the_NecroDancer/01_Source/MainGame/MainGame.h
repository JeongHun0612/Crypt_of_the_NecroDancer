#pragma once
#include "../2DFrameWork/GameCore/GameNode.h"

class MainGame : public GameNode
{
private:

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	
	void initImage();
	void initSound();

	MainGame() {}
	~MainGame() {}
};