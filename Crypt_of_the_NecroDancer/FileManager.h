#pragma once
#include "GameNode.h"

class FileManager
{
public:
	static void loadBeatFile(const char* fileName, queue<int>& queueList);
	static void loadTileFile(const char* fileName, vector<Tile> &vectorList);
};

