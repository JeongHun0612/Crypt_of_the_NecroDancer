#include "Stdafx.h"
#include "TileMap.h"
#include "FileManager.h"

HRESULT TileMap::init(void)
{
	// Lobby TileMap √ ±‚»≠
	//FileManager::loadTileMapFile("Lobby_Terrain.txt", _vLobbyTerrain, TILE_TYPE::TERRAIN);
	//FileManager::loadTileMapFile("Lobby_Wall.txt", _vLobbyWall, TILE_TYPE::WALL);

	return S_OK;
}

void TileMap::release(void)
{
}
