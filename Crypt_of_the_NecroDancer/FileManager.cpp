#include "Stdafx.h"
#include "FileManager.h"

void FileManager::loadBeatFile(const char* fileName, queue<int> &queueList)
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