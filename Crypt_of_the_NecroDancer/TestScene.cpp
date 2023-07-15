#include "Stdafx.h"
#include "TestScene.h"

HRESULT TestScene::init(void)
{
	for (int i = 0; i < 2500; i++)
	{
		Tile* tile = new Tile;

		tile->imgNum = { 0, 0 };
		tile->posIdx = { i % 50, i / 50 };
		tile->isColiider = false;

		_tile.push_back(tile);
	}

	return S_OK;
}

void TestScene::release(void)
{
}

void TestScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		//delete(_tile[0]);

		_tile.erase(_tile.begin() + 2);
	}
}

void TestScene::render(void)
{
	for (int i = 0; i < _tile.size(); i++)
	{
		_time += TIMEMANAGER->getDeltaTime();
		IMAGEMANAGER->findImage("terrain1")->frameRender(getMemDC(), _tile[i]->posIdx.x * 64, _tile[i]->posIdx.y * 64, _tile[i]->imgNum.x, _tile[i]->imgNum.y);
	}


	cout << _time << endl;
	_time = 0.0f;
}
