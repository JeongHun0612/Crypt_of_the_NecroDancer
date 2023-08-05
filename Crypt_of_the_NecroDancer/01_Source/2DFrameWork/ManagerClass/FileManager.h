#pragma once

class FileManager
{
public:
	static void loadBeatFile(const char* fileName, vector<int>& vBeatList);
	static void loadTileMapFile(const char* fileName, vector<Tile*>& vTileList, TILE_TYPE type);
	static void loadEnemyFile(const char* fileName, vector<Enemy*>& vEnemyList, vector<vector<Tile*>> _vTiles, int maxTileCol);
	static void loadItemFile(const char* fileName, vector<Item*>& vItemList, int maxTileCol);
};
