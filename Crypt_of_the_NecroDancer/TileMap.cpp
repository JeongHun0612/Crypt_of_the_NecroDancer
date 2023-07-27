#include "Stdafx.h"
#include "TileMap.h"
#include "FileManager.h"

HRESULT TileMap::init(void)
{
	// Lobby TileMap 초기화
	FileManager::loadTileMapFile("Lobby_Terrain.txt", _vLobbyTerrain, TILE_TYPE::TERRAIN);
	FileManager::loadTileMapFile("Lobby_Wall.txt", _vLobbyWall, TILE_TYPE::WALL);

	_vLobbyTiles.push_back(_vLobbyTerrain);
	_vLobbyTiles.push_back(_vLobbyWall);


	// Stage TileMap 초기화
	FileManager::loadTileMapFile("Stage1-1_Terrain.txt", _vStage1Terrain, TILE_TYPE::TERRAIN);
	FileManager::loadTileMapFile("Stage1-1_Wall.txt", _vStage1Wall, TILE_TYPE::WALL);

	_vStage1Tiles.push_back(_vStage1Terrain);
	_vStage1Tiles.push_back(_vStage1Wall);

	return S_OK;
}

void TileMap::release(void)
{
}