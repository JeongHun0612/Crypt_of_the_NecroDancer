#pragma once
#include "GameScene.h"

class StageScene : public GameScene
{
private:

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	StageScene() {}
	~StageScene() {}
};