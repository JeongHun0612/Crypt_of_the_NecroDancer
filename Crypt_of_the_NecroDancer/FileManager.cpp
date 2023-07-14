#include "Stdafx.h"
#include "FileManager.h"

void FileManager::loadBeatFile(const char* fileName, queue<int> &queueList)
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

void FileManager::loadTileFile(const char* fileName, vector<Tile>& vectorList)
{
	char filePath[MAX_PATH] = "Resources/TileMap/";
	strcat_s(filePath, fileName);

	ifstream loadStream(filePath);

	if (loadStream.is_open())
	{
		while (!loadStream.eof())		// 파일의 끝에 도달하면 -1을 반환
		{
			char line[128];
			loadStream.getline(line, 128);

			Tile tile;
			tile.posIdx.x = line[0] - 48;
			tile.posIdx.y = line[2] - 48;
			tile.imgNum.x = line[4] - 48;
			tile.imgNum.y = line[6] - 48;
			tile.isExist = line[8] - 48;
			tile.isColiider = line[10] - 48;

			vectorList.push_back(tile);
		}
	}
}
