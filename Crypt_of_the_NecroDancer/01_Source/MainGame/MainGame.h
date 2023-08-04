#pragma once

//#include "../Crypt_of_the_NecroDancer/GameNode.h"

#include "GameNode.h"

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