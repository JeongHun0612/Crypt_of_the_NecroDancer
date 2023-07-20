#include "Stdafx.h"
#include "TileMap.h"
#include "FileManager.h"

HRESULT TileMap::init(void)
{
	_startIdx = 0;

	// Lobby TileMap 초기화
	FileManager::loadTileMapFile("Lobby_Terrain.txt", _vLobbyTerrain, TILE_TYPE::TERRAIN);
	FileManager::loadTileMapFile("Lobby_Wall.txt", _vLobbyWall, TILE_TYPE::WALL);


	// Lobby TileMap 초기화
	FileManager::loadTileMapFile("Stage1-1_Terrain.txt", _vStage1Terrain, TILE_TYPE::TERRAIN);
	FileManager::loadTileMapFile("Stage1-1_Wall.txt", _vStage1Wall, TILE_TYPE::WALL);

	return S_OK;
}

void TileMap::release(void)
{
}

void TileMap::setStartIdx(int playerIdxX, int playerIdxY, int max_col)
{
	// 247
	if (playerIdxX - 9 >= 0 && playerIdxY - 6 >= 0)
	{
		int startX = playerIdxX - 9;
		int startY = playerIdxY - 6;

		_startIdx = (startY * max_col) + startX;
	}
	else
	{
		_startIdx = 0;
	}
}
