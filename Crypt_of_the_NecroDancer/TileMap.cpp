#include "Stdafx.h"
#include "TileMap.h"
#include "FileManager.h"

HRESULT TileMap::init(void)
{
	// Lobby TileMap �ʱ�ȭ
	FileManager::loadTileMapFile("Lobby_Terrain.txt", _vLobbyTerrain, TILE_TYPE::TERRAIN);
	FileManager::loadTileMapFile("Lobby_Wall.txt", _vLobbyWall, TILE_TYPE::WALL);


	// Lobby TileMap �ʱ�ȭ
	FileManager::loadTileMapFile("Stage1-1_Terrain.txt", _vStage1Terrain, TILE_TYPE::TERRAIN);
	FileManager::loadTileMapFile("Stage1-1_Wall.txt", _vStage1Wall, TILE_TYPE::WALL);

	return S_OK;
}

void TileMap::release(void)
{
}