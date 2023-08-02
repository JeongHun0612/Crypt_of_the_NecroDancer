#include "Stdafx.h"
#include "Beat.h"
#include "FileManager.h"

HRESULT Beat::init()
{
	// ���� �ڵ� �ʱ�ȭ
	_heartImg.img = IMAGEMANAGER->findImage("beat_heart");
	_heartImg.x = WINSIZE_X_HALF - _heartImg.img->getFrameWidth() / 2;
	_heartImg.y = WINSIZE_Y - 130;
	_heartImg.frameX = 0;
	_heartImg.frameY = 0;
	_heartImg.frameCount = 0.0f;

	// ��Ʈ ���� ����
	_eraseLine = { WINSIZE_X_HALF, WINSIZE_Y - 80 };

	// ��Ʈ ���� ����
	_beatRate = RectMakeCenter(_heartImg.x + _heartImg.img->getFrameWidth() / 2, _heartImg.y + _heartImg.img->getFrameHeight() / 2, 180, 100);

	// ������ �̹��� �ʱ�ȭ
	_missedImg = IMAGEMANAGER->findImage("missed");
	_missedImg->setX(WINSIZE_X_HALF - _missedImg->getWidth() / 2);
	_missedImg->setY(WINSIZE_Y - 130);
	_missedAlpha = 255;

	return S_OK;
}

HRESULT Beat::init(const char* fileName, const char* soundName)
{
	// ��Ʈ ���� �ҷ�����
	FileManager::loadBeatFile(fileName, _qNoteData);
	_soundName = soundName;

	_noteFrameX = 0;
	_noteCycle = _qNoteData.front();
	_qNoteData.pop();

	_isBeat = false;
	_isStep = false;
	_isMusic = true;
	_isMissed = false;
	_isSuccess = false;

	return S_OK;
}


void Beat::update(void)
{
	// ���� �ڵ� �ִϸ��̼�
	_heartImg.frameCount += TIMEMANAGER->getDeltaTime();

	if (_heartImg.frameCount >= 0.276f)
	{
		if (_heartImg.frameX == _heartImg.img->getMaxFrameX())
		{
			_heartImg.frameX = 0;
		}
		else
		{
			_heartImg.frameX++;
		}

		_heartImg.img->setFrameX(_heartImg.frameX);

		_heartImg.frameCount = 0;
	}


	// ��Ʈ ����
	//unsigned int soundPos = SOUNDMANAGER->getPosition("stage1_1");

	static int soundPos = 0;
	soundPos += 1044 * TIMEMANAGER->getDeltaTime();

	if (_noteCycle <= soundPos && _isMusic)
	{
		createNote();

		_noteCycle = _qNoteData.front();
		_qNoteData.pop();

		if (soundPos >= 140000)
		{
			_noteFrameX = 2;
		}

		// ��Ʈ�� ����� �� ���� ����
		if (_qNoteData.empty())
		{
			_isMusic = false;
		}
	}

	for (int i = 0; i < _vNoteLeft.size(); i++)
	{
		// ��Ʈ �̵�
		_vNoteLeft[i].x += _vNoteLeft[i].speed;
		_vNoteLeft[i].rc = RectMake(_vNoteLeft[i].x, _vNoteLeft[i].y, _vNoteLeft[i].img->getFrameWidth(), _vNoteLeft[i].img->getFrameHeight());

		_vNoteRight[i].x += _vNoteRight[i].speed;
		_vNoteRight[i].rc = RectMake(_vNoteRight[i].x, _vNoteRight[i].y, _vNoteLeft[i].img->getFrameWidth(), _vNoteRight[i].img->getFrameHeight());

		// ���İ� ����
		if (_vNoteLeft[i].alpha < 255)
		{
			_vNoteLeft[i].alpha += 2;
			_vNoteRight[i].alpha += 2;

			if (_vNoteLeft[i].alpha > 255)
			{
				_vNoteLeft[i].alpha = 255;
				_vNoteRight[i].alpha = 255;
			}
		}

		// ��Ʈ Ű�Է� ���� ���� In
		RECT rt;
		if (IntersectRect(&rt, &_vNoteLeft[i].rc, &_beatRate) && !_vNoteLeft[i].isDestory)
		{
			_isBeat = true;

			if (_isSuccess)
			{
				_vNoteLeft[i].isDestory = true;
				_vNoteRight[i].isDestory = true;

				_beatCount++;
				_isBeat = false;
				_isSuccess = false;
			}
		}

		// ��Ʈ ���� ����
		if (_vNoteLeft[i].isDestory)
		{
			_vNoteLeft[i].speed = 0.f;
			_vNoteRight[i].speed = 0.f;

			_vNoteLeft[i].alpha -= 10;
			_vNoteRight[i].alpha -= 10;

			if (_vNoteLeft[i].alpha <= 0)
			{
				_vNoteLeft.erase(_vNoteLeft.begin() + i);
				_vNoteRight.erase(_vNoteRight.begin() + i);
			}
		}

		if (PtInRect(&_vNoteLeft[i].rc, _eraseLine))
		{
			_beatCount++;
			_isBeat = false;
			_vNoteLeft.erase(_vNoteLeft.begin() + i);
			_vNoteRight.erase(_vNoteRight.begin() + i);
		}
	}

	// ������ ���°� true�� �� ������ ��ü ����
	if (_isMissed)
	{
		createMissed();
		SOUNDMANAGER->play("missed_beat");
		_isMissed = false;
	}

	// ������ ��ü �ִϸ��̼�
	moveMissed();
}

void Beat::render(HDC hdc)
{
	//��Ʈ ���
	for (int i = 0; i < _vNoteLeft.size(); i++)
	{
		_vNoteLeft[i].img->frameAlphaRender(hdc, _vNoteLeft[i].x, _vNoteLeft[i].y, _vNoteLeft[i].frameX, _vNoteLeft[i].img->getFrameY(), _vNoteLeft[i].alpha);
		_vNoteRight[i].img->frameAlphaRender(hdc, _vNoteRight[i].x, _vNoteRight[i].y, _vNoteLeft[i].frameX, _vNoteLeft[i].img->getFrameY(), _vNoteRight[i].alpha);
	}

	// ���� �ڵ� ���
	_heartImg.img->frameRender(hdc, _heartImg.x, _heartImg.y);

	// ������ ���
	for (auto iter = _vMissed.begin(); iter != _vMissed.end(); ++iter)
	{
		iter->img->alphaRender(hdc, iter->x, iter->y, iter->alpha);
	}
}

void Beat::createNote()
{
	for (int i = 0; i < 2; i++)
	{
		Note note;
		note.img = IMAGEMANAGER->findImage("beat_bar");
		note.y = WINSIZE_Y - 100;
		note.frameX = _noteFrameX;
		note.alpha = 50;
		note.isDestory = false;

		if (i == LEFT)
		{
			note.x = -50;
			note.speed = 5.0f;

			_vNoteLeft.push_back(note);
		}
		else
		{
			note.x = WINSIZE_X + 50;
			note.speed = -5.0f;

			_vNoteRight.push_back(note);;
		}
	}
}

void Beat::createMissed()
{
	Missed missed;
	missed.img = IMAGEMANAGER->findImage("missed");
	missed.x = WINSIZE_X_HALF - _missedImg->getWidth() / 2;
	missed.y = WINSIZE_Y - 130;
	missed.alpha = 255;

	_vMissed.push_back(missed);
}

void Beat::moveMissed()
{
	for (auto iter = _vMissed.begin(); iter != _vMissed.end();)
	{
		iter->y -= 0.4f;
		iter->alpha -= 2;

		if (iter->alpha <= 0)
		{
			iter = _vMissed.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}
