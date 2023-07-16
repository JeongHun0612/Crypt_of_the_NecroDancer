#pragma once
#include "GameNode.h"
#include "TileNode.h"

class FileManager
{
public:
	static void loadBeatFile(const char* fileName, queue<int>& queueList);
};

