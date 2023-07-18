#include "Stdafx.h"
#include "FileManager.h"

void FileManager::loadBeatFile(const char* fileName, queue<int>& queueList)
{
	char filePath[MAX_PATH] = "Resources/Beat/";
	strcat_s(filePath, fileName);

	ifstream loadStream(filePath);

	if (loadStream.is_open())
	{
		while (!loadStream.eof())		// 파일의 끝에 도달하면 -1을 반환
		{
			string line;
			getline(loadStream, line);	// 파일을 읽어들인다.

			int cutIndex = 0;

			while (true)
			{
				cutIndex = line.find(",");

				if (cutIndex == -1)
				{
					queueList.push(stoi(line));
					break;
				}

				int beatMS = stoi(line.substr(0, cutIndex));
				queueList.push(beatMS);								// ","를 기준으로 자른 문자를 int형으로 변환해서 queue에 저장

				cutIndex++;
				line = line.substr(cutIndex, line.length());		// 자른 문자열 이후부터 다시 재할당 (line)
			}
		}
	}

	loadStream.close();
}

void FileManager::loadTileMapFile(const char* fileName, vector<Tile>& vTileList, TILE_TYPE type)
{
	char filePath[MAX_PATH] = "Resources/TileMap/";
	strcat_s(filePath, fileName);

	ifstream loadStream(filePath);

	int tileType = 0;

	while (!loadStream.eof())		// 파일의 끝에 도달하면 -1을 반환
	{
		string line;
		getline(loadStream, line);	// 파일을 읽어들인다.

		int cutIndex = 0;
		int count = 0;

		Tile tile;

		while (true)
		{
			cutIndex = line.find(",");

			if (cutIndex == -1)
			{
				switch (type)
				{
				case TILE_TYPE::TERRAIN:
					tile.terrain = (TERRAIN)stoi(line);
					break;
				case TILE_TYPE::WALL:
					tile.wall = (WALL)stoi(line);
					break;
				case TILE_TYPE::DECO:
					break;
				}
				break;
			}

			int tileData = stoi(line.substr(0, cutIndex));

			switch (count)
			{
			case 0:
				tile.idxY = tileData;
				break;
			case 1:
				tile.idxX = tileData;
				break;
			case 2:
				tile.frameX = tileData;
				break;
			case 3:
				tile.frameY = tileData;
				break;
			case 4:
				tile.isColiider = tileData;
				break;
			case 5:
				tile.isExist = tileData;
				break;
			case 6:
				tile.hardness = tileData;
			}

			cutIndex++;
			line = line.substr(cutIndex, line.length());
			count++;
		}

		tile.isLight = false;

		vTileList.push_back(tile);
	}
}