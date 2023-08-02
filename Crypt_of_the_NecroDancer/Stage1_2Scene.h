#pragma once
#include "GameScene.h"

class Stage1_2Scene : public GameScene
{
private:

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	Stage1_2Scene() {}
	~Stage1_2Scene() {}
};

