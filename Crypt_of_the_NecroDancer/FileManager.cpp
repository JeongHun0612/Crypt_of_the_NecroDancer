#include "Stdafx.h"
#include "FileManager.h"

#include "Slime_Green.h"
#include "Slime_Blue.h"
#include "Skeleton_Normal.h"
#include "Skeleton_Black.h"

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

void FileManager::loadTileMapFile(const char* fileName, vector<Tile*>& vTileList, TILE_TYPE type)
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

		Tile* tile = new Tile;

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
					tile->_terrain = (TERRAIN)stoi(line);
					//tile->init(idxX, idxY, frameX, frameY, isCollider, isExist, hardNess, terrain);
					vTileList.push_back(tile);
				}
				break;
				case TILE_TYPE::WALL:
				{
					tile->_wall = (WALL)stoi(line);
					//tile->init(idxX, idxY, frameX, frameY, isCollider, isExist, hardNess, wall);
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
				tile->_idxY = tileData;
				break;
			case 1:
				tile->_idxX = tileData;
				break;
			case 2:
				tile->_frameX = tileData;
				break;
			case 3:
				tile->_frameY = tileData;
				break;
			case 4:
				tile->_isCollider = tileData;
				break;
			case 5:
				tile->_isExist = tileData;
				break;
			case 6:
				tile->_hardNess = tileData;
			}

			cutIndex++;
			line = line.substr(cutIndex, line.length());
			count++;
		}
	}
}

void FileManager::loadEnemyFile(const char* fileName, vector<Enemy*>& vEnemyList)
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

		int idxX = 0;
		int idxY = 0;

		while (true)
		{
			cutIndex = line.find(",");

			if (cutIndex == -1)
			{
				Enemy* _enemy;

				switch (stoi(line))
				{
				case ENEMY_TYPE::SLIME_GREE:
					_enemy = new Slime_Green;
					_enemy->init(idxY, idxX);
					break;
				case ENEMY_TYPE::SLIME_BLUE:
					_enemy = new Slime_Blue;
					_enemy->init(idxY, idxX);
					break;
				case ENEMY_TYPE::SKELETON_NORMAL:
					_enemy = new Skeleton_Normal;
					_enemy->init(idxY, idxX);
					break;
				case ENEMY_TYPE::SKELETON_BLACK:
					_enemy = new Skeleton_Black;
					_enemy->init(idxY, idxX);
					break;
				}

				vEnemyList.push_back(_enemy);
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
			}

			cutIndex++;
			line = line.substr(cutIndex, line.length());
			count++;
		}
	}
}
