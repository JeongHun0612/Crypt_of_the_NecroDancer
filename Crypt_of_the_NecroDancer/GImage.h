#pragma once

// GDI Image
class GImage
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0, LOAD_FILE,		// ���ҽ�, ����
		LOAD_EMPTY, LOAD_END				// �� ��Ʈ��, �ε� Done
	};

	typedef struct tagImage
	{
		DWORD		resID;
		HDC			hMemDC;
		HBITMAP		hBit;
		HBITMAP		hOBit;
		float		x;						// �̹��� x ��ǥ
		float		y;						// �̹��� y ��ǥ
		int			width;					// �̹��� ���� ũ��
		int			height;					// �̹��� ���� ũ��
		int			currentFrameX;			// ���� ������ X
		int			currentFrameY;			// ���� ������ Y
		int			maxFrameX;				// �ִ� ������ X
		int			maxFrameY;				// �ִ� ������ Y
		int			frameWidth;				// 1 ������ ���� ũ��
		int			frameHeight;			// 1 ������ ���� ũ��
		BYTE		loadType;

		tagImage()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, * LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;
	char*			_fileName;		// �̹��� ���� ���
	bool			_isTrans;		// �̹��� ��� ���� ����

	/*
	COLORREF

	- ��������� ������ ǥ���ϱ� ���� ��ȣ���� 32bit ������
	�� R, G, B ���� 1����Ʈ (8bit)�̸� 0 ~ 255������ ���� ǥ���ϴµ� ����ȭ �Ǿ� �ִ�.
	*/
	COLORREF		_transColor;	// ���� RGB �� (����Ÿ = RGB(255, 0, 255))

	BLENDFUNCTION _blendFunc;		// ���ĺ����� ���
	LPIMAGE_INFO _blendImage;		// ���ĺ����� �̹���

public:
	HRESULT init(int width, int height);

	// �̹��� ���ҽ��� �ʱ�ȭ
	HRESULT init(const DWORD resID, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	// �̹��� ���Ϸ� �ʱ�ȭ
	HRESULT init(const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	// ������ �̹��� ���Ϸ� �ʱ�ȭ
	HRESULT init(const char* fileName, float x, float y, int width, int height,
		bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY,
		bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY,
		bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));


	// ���� �̹��� �ʱ�ȭ
	HRESULT initForAlphaBlend(void);

	// ���� �÷�Ű ����
	void setTransColor(bool isTrans, COLORREF transColor);

	// ����
	void release(void);

	// ����
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);

	//�̹��� Ŭ����
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
	void render(HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight);

	// ������ ����
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	// ���� ���� ( �ݺ� / �̹����� �а� ���� ��� )
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	// ���ķ���
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	// = �ζ��� �Լ� = 
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	// �̹��� X ��ǥ
	inline float getX(void) { return _imageInfo->x; }
	inline void setX(float x) { _imageInfo->x = x; }

	// �̹��� Y ��ǥ
	inline float getY(void) { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y = y; }

	// �̹��� ���� ��ǥ
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	// �̹��� ���� / ���� ũ��
	inline int getWidth(void) { return _imageInfo->width; }
	inline int getHeight(void) { return _imageInfo->height; }

	// �ٿ�� �ڽ� (�浹�� ����)
	inline RECT boundingBox(void)
	{
		RECT rc =
		{
			(int)_imageInfo->x,
			(int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->width,
			(int)_imageInfo->y + _imageInfo->height,
		};

		return rc;
	}

	// �ٿ�� �ڽ� (�浹�� ����)
	inline RECT boundingBoxWithFrame(void)
	{
		RECT rc =
		{
			(int)_imageInfo->x,
			(int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->frameWidth,
			(int)_imageInfo->y + _imageInfo->frameHeight,
		};

		return rc;
	}

	// ������ X
	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;

		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}

	// ������ Y
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;

		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	// �̹��� 1������ ���� / ���� ũ��
	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

	// �ִ� ������ X / Y ����
	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }

	GImage();
	~GImage() {}
};
