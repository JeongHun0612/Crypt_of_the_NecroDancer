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

	_eraseLine = { WINSIZE_X_HALF, WINSIZE_Y - 80 };

	_noteCycle = _qNoteData.front();
	_qNoteData.pop();

	_isBeat = false;
	_isSuccess = false;
	_isMusic = true;

	return S_OK;
}

void Beat::release(void)
{

}

void Beat::update(void)
{
	// ���� �ڵ� �ִϸ��̼�
	_heartRate.frameCount += TIMEMANAGER->getDeltaTime();

	if (_heartRate.frameCount >= 0.276f)
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
	//unsigned int soundPos = SOUNDMANAGER->getPosition("stage1-1");
	static int test = 0;
	test += 10;

	if (_noteCycle <= test && _isMusic)
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

				_vNoteLeft.push_back(note);
			}
			else
			{
				note.x = WINSIZE_X + 50;
				note.speed = -5.0f;
				note.distance = RIGHT;

				_vNoteRight.push_back(note);;
			}
		}

		_noteCycle = _qNoteData.front();
		_qNoteData.pop();

		// ��Ʈ�� ����� �� ���� ����
		if (_qNoteData.empty())
		{
			_isMusic = false;
		}
	}

	moveNote(_vNoteLeft);
	moveNote(_vNoteRight);
}

void Beat::render(HDC hdc)
{
	//��Ʈ ���
	for (auto iter = _vNoteLeft.begin(); iter != _vNoteLeft.end(); ++iter)
	{
		iter->img->alphaRender(hdc, iter->x, iter->y, iter->alpha);
	}
	for (auto iter = _vNoteRight.begin(); iter != _vNoteRight.end(); ++iter)
	{
		iter->img->alphaRender(hdc, iter->x, iter->y, iter->alpha);
	}

	// ���� �ڵ� ���
	_heartRate.img->frameRender(hdc, _heartRate.x, _heartRate.y);
	//DrawRectMake(hdc, _heartRate.rc);
}

void Beat::moveNote(vector<Note>& vNote)
{
	for (auto iter = vNote.begin(); iter != vNote.end(); ++iter)
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

		// ��Ʈ Ű�Է� ���� ���� In
		RECT rt;
		if (IntersectRect(&rt, &iter->rc, &_heartRate.rc))
		{
			_isBeat = true;
		}

		// ��Ʈ ���� ���� ����
		if (PtInRect(&iter->rc, _eraseLine) || iter->alpha == 0)
		{
			iter = vNote.erase(iter);

			_isBeat = false;
		}
	}
}
