#pragma once
#include "GameNode.h"
#include "Tile.h"

class FileManager
{
public:
	static void loadBeatFile(const char* fileName, queue<int>& queueList);
	static void loadTileMapFile(const char* fileName, vector<Tile>& vTileList, TILE_TYPE type);
	static void loadEnemyFile(const char* fileName, vector<Enemy*>& vEnemyList);
};

