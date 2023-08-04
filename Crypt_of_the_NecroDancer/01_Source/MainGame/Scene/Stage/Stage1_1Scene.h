#pragma once
#include "GameScene.h"

class Stage1_1Scene : public GameScene
{
private:

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	Stage1_1Scene() {}
	~Stage1_1Scene() {}
};