#include "Stdafx.h"
#include "Beat.h"
#include "FileManager.h"

HRESULT Beat::init(void)
{
	// ��Ʈ ���� �ҷ����� (stage 1-1)
	FileManager::loadBeatFile("stage1-1.txt", _qNoteData);

	// ���� �ڵ� �ʱ�ȭ
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
	// ���� �ڵ� �ִϸ��̼�
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

	// ��Ʈ ����
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

		// ��Ʈ�� ����� �� ���� ����
		if (_qNoteData.empty())
		{
			_isMusic = false;
		}
	}

	for (auto iter = _vNote.begin(); iter != _vNote.end();)
	{
		// ��Ʈ �̵�
		iter->x += iter->speed;
		iter->rc = RectMake(iter->x, iter->y, iter->img->getWidth(), iter->img->getHeight());

		// ���İ� ����
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
			// ��Ʈ ���� In
			if (iter->rc.right >= _heartRate.rc.left)
			{
				_isBeat = true;

				// ���� ��� ����
				if (iter->rc.right >= WINSIZE_X_HALF)
				{
					iter = _vNote.erase(iter);
					_isBeat = false;
				}
			}
		}

		if (iter->distance == RIGHT)
		{
			// ������ ��� ����
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
	 //��Ʈ ���
	for (auto iter = _vNote.begin(); iter != _vNote.end(); ++iter)
	{
		iter->img->alphaRender(hdc, iter->x, iter->y, iter->alpha);
	}

	// ���� �ڵ� ���
	_heartRate.img->frameRender(hdc, _heartRate.x, _heartRate.y);
	DrawRectMake(hdc, _heartRate.rc);
}
