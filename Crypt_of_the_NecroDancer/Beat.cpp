#include "Stdafx.h"
#include "Beat.h"
#include "FileManager.h"

HRESULT Beat::init(void)
{
	// 노트 정보 불러오기 (stage 1-1)
	FileManager::loadBeatFile("stage1-1.txt", _qNoteData);

	// 심장 박동 초기화
	_heartRate.img = IMAGEMANAGER->findImage("beat_heart");
	_heartRate.x = WINSIZE_X_HALF - _heartRate.img->getFrameWidth() / 2;
	_heartRate.y = WINSIZE_Y - 130;
	_heartRate.rc = RectMakeCenter(_heartRate.x + _heartRate.img->getFrameWidth() / 2, _heartRate.y + _heartRate.img->getFrameHeight() / 2, 180, 100);
	_heartRate.frameX = 0;
	_heartRate.frameY = 0;
	_heartRate.frameCount = 0.0f;

	_noteCycle = 0;

	_isBeat = false;
	_isMusic = true;

	SOUNDMANAGER->setPosition("stage1-1", 170000);

	return S_OK;
}

void Beat::release(void)
{

}

void Beat::update(void)
{
	// 심장 박동 애니메이션
	_heartRate.frameCount += TIMEMANAGER->getDeltaTime();

	if (_heartRate.frameCount >= 0.5f)
	{
		if (_heartRate.frameX == _heartRate.img->getMaxFrameX())
		{
			_heartRate.frameX = 0;
		}
		else
		{
			_heartRate.frameX++;
		}

		_heartRate.img->setFrameX(_heartRate.frameX);

		_heartRate.frameCount = 0;
	}

	// 노트 생성
	unsigned int soundPos = SOUNDMANAGER->getPosition("stage1-1");
	cout << soundPos << endl;

	if (_noteCycle <= soundPos && _isMusic)
	{
		for (int i = 0; i < 2; i++)
		{
			Note note;
			note.img = IMAGEMANAGER->findImage("beat_bar1");
			note.y = WINSIZE_Y - 100;
			note.alpha = 50;

			if (i == LEFT)
			{
				note.x = -50;
				note.speed = 5.0f;
				note.distance = LEFT;
			}
			if (i == RIGHT)
			{
				note.x = WINSIZE_X + 50;
				note.speed = -5.0f;
				note.distance = RIGHT;
			}

			_vNote.push_back(note);
		}

		_noteCycle = _qNoteData.front();
		_qNoteData.pop();

		// 노트가 비었을 때 음악 종료
		if (_qNoteData.empty())
		{
			_isMusic = false;
		}
	}

	for (auto iter = _vNote.begin(); iter != _vNote.end();)
	{
		// 노트 이동
		iter->x += iter->speed;
		iter->rc = RectMake(iter->x, iter->y, iter->img->getWidth(), iter->img->getHeight());

		// 알파값 변경
		if (iter->alpha < 255)
		{
			iter->alpha += 2;

			if (iter->alpha > 255)
			{
				iter->alpha = 255;
			}
		}

		if (iter->distance == LEFT)
		{
			// 비트 범위 In
			if (iter->rc.right >= _heartRate.rc.left)
			{
				_isBeat = true;

				// 왼쪽 노드 제거
				if (iter->rc.right >= WINSIZE_X_HALF)
				{
					iter = _vNote.erase(iter);
					_isBeat = false;
				}
			}
		}

		if (iter->distance == RIGHT)
		{
			// 오른쪽 노드 제거
			if (iter->rc.left <= WINSIZE_X_HALF)
			{
				iter = _vNote.erase(iter);
			}
		}

		if (iter != _vNote.end())
		{
			++iter;
		}
	}
}

void Beat::render(HDC hdc)
{
	 //노트 출력
	for (auto iter = _vNote.begin(); iter != _vNote.end(); ++iter)
	{
		iter->img->alphaRender(hdc, iter->x, iter->y, iter->alpha);
	}

	// 심장 박동 출력
	_heartRate.img->frameRender(hdc, _heartRate.x, _heartRate.y);
	DrawRectMake(hdc, _heartRate.rc);
}
