#include "Stdafx.h"
#include "FileManager.h"

#include "Slime_Green.h"
#include "Slime_Blue.h"
#include "Slime_Orange.h"
#include "Skeleton_Normal.h"
#include "Skeleton_Yellow.h"
#include "Skeleton_Black.h"
#include "Zombie.h"
#include "Bat_Blue.h"
#include "Bat_Red.h"
#include "Monkey_Normal.h"
#include "Monkey_White.h"
#include "Ghost.h"
#include "Wraith.h"
#include "Minotaur_Normal.h"
#include "Dragon_Red.h"

#include "ShopKeeper.h"

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
	vTileList.clear();

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
		tile->_alpha = 80;
		tile->_isLight = false;
		tile->_isSearch = false;

		while (true)
		{
			cutIndex = line.find(",");

			if (cutIndex == -1)
			{
				switch (type)
				{
				case TILE_TYPE::TERRAIN:
				{
					tile->_terrainType = (TERRAIN_TYPE)stoi(line);
					vTileList.push_back(tile);
				}
				break;
				case TILE_TYPE::WALL:
				{
					tile->_wallType = (WALL_TYPE)stoi(line);
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
				tile->_frameY = tileData;
				break;
			case 3:
				tile->_frameX = tileData;
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

void FileManager::loadEnemyFile(const char* fileName, vector<Enemy*>& vEnemyList, vector<vector<Tile*>> _vTiles, int maxTileCol)
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
				case (int)ENEMY_TYPE::SLIME_GREEN:
					_enemy = new Slime_Green;
					_enemy->init(idxX, idxY, _vTiles, maxTileCol);
					break;
				case (int)ENEMY_TYPE::SLIME_BLUE:
					_enemy = new Slime_Blue;
					_enemy->init(idxX, idxY, _vTiles, maxTileCol);
					break;
				case (int)ENEMY_TYPE::SLIME_ORANGE:
					_enemy = new Slime_Orange;
					_enemy->init(idxX, idxY, _vTiles, maxTileCol);
					break;
				case (int)ENEMY_TYPE::SKELETON_NORMAL:
					_enemy = new Skeleton_Normal;
					_enemy->init(idxX, idxY, _vTiles, maxTileCol);
					break;
				case (int)ENEMY_TYPE::SKELETON_YELLOW:
					_enemy = new Skeleton_Yellow;
					_enemy->init(idxX, idxY, _vTiles, maxTileCol);
					break;
				case (int)ENEMY_TYPE::SKELETON_BLACK:
					_enemy = new Skeleton_Black;
					_enemy->init(idxX, idxY, _vTiles, maxTileCol);
					break;
				case (int)ENEMY_TYPE::ZOMBIE:
					_enemy = new Zombie;
					_enemy->init(idxX, idxY, _vTiles, maxTileCol);
					break;
				case (int)ENEMY_TYPE::BAT_BLUE:
					_enemy = new Bat_Blue;
					_enemy->init(idxX, idxY, _vTiles, maxTileCol);
					break;
				case (int)ENEMY_TYPE::BAT_RED:
					_enemy = new Bat_Red;
					_enemy->init(idxX, idxY, _vTiles, maxTileCol);
					break;
				case (int)ENEMY_TYPE::MONKEY_NORMAL:
					_enemy = new Monkey_Normal;
					_enemy->init(idxX, idxY, _vTiles, maxTileCol);
					break;
				case (int)ENEMY_TYPE::MONKEY_WHITE:
					_enemy = new Monkey_White;
					_enemy->init(idxX, idxY, _vTiles, maxTileCol);
					break;
				case (int)ENEMY_TYPE::GHOST:
					_enemy = new Ghost;
					_enemy->init(idxX, idxY, _vTiles, maxTileCol);
					break;
				case (int)ENEMY_TYPE::WRAITH:
					_enemy = new Wraith;
					_enemy->init(idxX, idxY, _vTiles, maxTileCol);
					break;
				case (int)ENEMY_TYPE::MINOTAUR_NORMAL:
					_enemy = new Minotaur_Normal;
					_enemy->init(idxX, idxY, _vTiles, maxTileCol);
					break;
				case (int)ENEMY_TYPE::DRAGON_RED:
					_enemy = new Dragon_Red;
					_enemy->init(idxX, idxY, _vTiles, maxTileCol);
					break;
				case (int)ENEMY_TYPE::SHOPKEEPER:
					_enemy = new ShopKeeper;
					_enemy->init(idxX, idxY, _vTiles, maxTileCol);
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

void FileManager::loadItemFile(const char* fileName, vector<Item*>& vItemList)
{
	vItemList.clear();

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

		ITEM_TYPE itemType;
		int type;

		while (true)
		{
			cutIndex = line.find(",");

			if (cutIndex == -1)
			{
				Item* _item;

				switch (stoi(line))
				{
				//case (int)ITEM_TYPE::SHOVEL:
				//	_item = new Shovel;
				//	break;
				//case (int)ITEM_TYPE::WEAPON:
				//	_item = new Weapon;
				//	break;
				//case (int)ITEM_TYPE::ARMOR:
				//	_item = new Armor;
				//	_item->init(idxX, idxY, stats, (ARMOR_TYPE)type);
				//	break;
				}

				vItemList.push_back(_item);
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
