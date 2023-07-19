#include "Stdafx.h"
#include "FileManager.h"

void FileManager::loadBeatFile(const char* fileName, queue<int>& queueList)
{
	char filePath[MAX_PATH] = "Resources/Beat/";
	strcat_s(filePath, fileName);

	ifstream loadStream(filePath);

	if (loadStream.is_open())
	{
		while (!loadStream.eof())		// ������ ���� �����ϸ� -1�� ��ȯ
		{
			string line;
			getline(loadStream, line);	// ������ �о���δ�.

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
				queueList.push(beatMS);								// ","�� �������� �ڸ� ���ڸ� int������ ��ȯ�ؼ� queue�� ����

				cutIndex++;
				line = line.substr(cutIndex, line.length());		// �ڸ� ���ڿ� ���ĺ��� �ٽ� ���Ҵ� (line)
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

	while (!loadStream.eof())		// ������ ���� �����ϸ� -1�� ��ȯ
	{
		string line;
		getline(loadStream, line);	// ������ �о���δ�.

		if (line.empty())
		{
			cout << "File Empty - " << fileName << endl;
			break;
		}

		int cutIndex = 0;
		int count = 0;

		Tile tile;

		int idxX = 0;
		int idxY = 0;
		int frameX = 0;
		int frameY = 0;
		bool isCollider = false;
		bool isExist = false;
		int hardNess = 0;
		TERRAIN terrain;
		WALL wall;

		while (true)
		{
			cutIndex = line.find(",");

			if (cutIndex == -1)
			{
				switch (type)
				{
				case TILE_TYPE::TERRAIN:
				{
					terrain = (TERRAIN)stoi(line);
					tile.init(idxX, idxY, frameX, frameY, isCollider, isExist, hardNess, terrain);
					vTileList.push_back(tile);
				}
					break;
				case TILE_TYPE::WALL:
				{
					wall = (WALL)stoi(line);
					tile.init(idxX, idxY, frameX, frameY, isCollider, isExist, hardNess, wall);
					vTileList.push_back(tile);
				}
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
				idxY = tileData;
				break;
			case 1:
				idxX = tileData;
				break;
			case 2:
				frameX = tileData;
				break;
			case 3:
				frameY = tileData;
				break;
			case 4:
				isCollider = tileData;
				break;
			case 5:
				isExist = tileData;
				break;
			case 6:
				hardNess = tileData;
			}

			cutIndex++;
			line = line.substr(cutIndex, line.length());
			count++;
		}
	}
}