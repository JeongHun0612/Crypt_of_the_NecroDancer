#include "../PCH/Stdafx.h"
#include "GImage.h"

GImage::GImage() : _imageInfo(nullptr)
, _fileName(nullptr)
, _isTrans(false)
, _transColor(RGB(0, 0, 0))
, _blendImage(NULL)
{
}

HRESULT GImage::init(int width, int height)
{
    // ���ʱ�ȭ ���� (Ȥ�� ���� �ִٸ� ���� �������ϰ� ����)
    if (_imageInfo != nullptr) this->release();

    HDC hdc = GetDC(_hWnd);

    _imageInfo = new IMAGE_INFO;

    _imageInfo->loadType = LOAD_EMPTY;
    _imageInfo->resID = 0;
    _imageInfo->hMemDC = CreateCompatibleDC(hdc);
    _imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
    _imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
    _imageInfo->width = width;
    _imageInfo->height = height;

    _fileName = nullptr;

    _isTrans = false;
    _transColor = RGB(0, 0, 0);

    // ���ҽ��� ��� ���µ� ����
    if (_imageInfo->hBit == 0)
    {
        release();
        return E_FAIL;
    }

    ReleaseDC(_hWnd, hdc);

    return S_OK;
}

HRESULT GImage::init(const DWORD resID, int width, int height, bool isTrans, COLORREF transColor)
{
    // ���ʱ�ȭ ���� (Ȥ�� ���� �ִٸ� ���� �������ϰ� ����)
    if (_imageInfo != nullptr) this->release();

    HDC hdc = GetDC(_hWnd);

    _imageInfo = new IMAGE_INFO;

    _imageInfo->loadType = LOAD_RESOURCE;
    _imageInfo->resID = resID;
    _imageInfo->hMemDC = CreateCompatibleDC(hdc);
    _imageInfo->hBit = (HBITMAP)LoadBitmap(_hInstance, MAKEINTRESOURCE(_imageInfo->resID));
    _imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
    _imageInfo->width = width;
    _imageInfo->height = height;

    _fileName = nullptr;

    _isTrans = isTrans;
    _transColor = transColor;

    // ���ҽ��� ��� ���µ� ����
    if (_imageInfo->hBit == 0)
    {
        release();
        return E_FAIL;
    }

    ReleaseDC(_hWnd, hdc);

    return S_OK;
}

HRESULT GImage::init(const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
    // ���ʱ�ȭ ���� (Ȥ�� ���� �ִٸ� ���� �������ϰ� ����)
    if (_imageInfo != nullptr) this->release();

    HDC hdc = GetDC(_hWnd);

    _imageInfo = new IMAGE_INFO;

    _imageInfo->loadType = LOAD_FILE;
    _imageInfo->resID = 0;
    _imageInfo->hMemDC = CreateCompatibleDC(hdc);
    _imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    _imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
    _imageInfo->width = width;
    _imageInfo->height = height;

    int len = (int)strlen(fileName);
    int idx = len + 1;

    _fileName = new char[idx];
    // strcpy -> ���� 1�� �� �߰�
    // �� �������� ����/���ڿ����� ������ ������ �ذ��� �Լ�
    // ������� ����, ����, ����)
    strcpy_s(_fileName, idx, fileName);

    _isTrans = isTrans;
    _transColor = transColor;

    // ���ҽ��� ��� ���µ� ����
    if (_imageInfo->hBit == 0)
    {
        release();
        return E_FAIL;
    }

    ReleaseDC(_hWnd, hdc);

    return S_OK;
}

HRESULT GImage::init(const char* fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
    if (_imageInfo != nullptr) this->release();

    HDC hdc = GetDC(_hWnd);

    _imageInfo = new IMAGE_INFO;

    _imageInfo->loadType = LOAD_FILE;
    _imageInfo->resID = 0;
    _imageInfo->hMemDC = CreateCompatibleDC(hdc);
    _imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    _imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
    _imageInfo->x = x;
    _imageInfo->y = y;
    _imageInfo->width = width;
    _imageInfo->height = height;

    int len = (int)strlen(fileName);
    int idx = len + 1;
    _fileName = new char[idx];
    strcpy_s(_fileName, idx, fileName);

    _isTrans = isTrans;
    _transColor = transColor;

    if (_imageInfo->hBit == 0)
    {
        release();
        return E_FAIL;
    }

    ReleaseDC(_hWnd, hdc);

    return S_OK;
}

HRESULT GImage::init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
    if (_imageInfo != nullptr) this->release();

    HDC hdc = GetDC(_hWnd);

    _imageInfo = new IMAGE_INFO;

    _imageInfo->loadType = LOAD_FILE;
    _imageInfo->resID = 0;
    _imageInfo->hMemDC = CreateCompatibleDC(hdc);
    _imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    _imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
    _imageInfo->width = width;
    _imageInfo->height = height;
    _imageInfo->currentFrameX = 0;
    _imageInfo->currentFrameY = 0;
    _imageInfo->maxFrameX = maxFrameX - 1;
    _imageInfo->maxFrameY = maxFrameY - 1;
    _imageInfo->frameWidth = width / maxFrameX;
    _imageInfo->frameHeight = height / maxFrameY;

    int len = (int)strlen(fileName);
    int idx = len + 1;
    _fileName = new char[idx];
    strcpy_s(_fileName, idx, fileName);

    _isTrans = isTrans;
    _transColor = transColor;

    if (_imageInfo->hBit == 0)
    {
        release();
        return E_FAIL;
    }

    ReleaseDC(_hWnd, hdc);

    return S_OK;
}

HRESULT GImage::init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
    if (_imageInfo != nullptr) this->release();

    HDC hdc = GetDC(_hWnd);

    _imageInfo = new IMAGE_INFO;

    _imageInfo->loadType = LOAD_FILE;
    _imageInfo->resID = 0;
    _imageInfo->hMemDC = CreateCompatibleDC(hdc);
    _imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    _imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
    _imageInfo->x = x;
    _imageInfo->y = y;
    _imageInfo->width = width;
    _imageInfo->height = height;
    _imageInfo->currentFrameX = 0;
    _imageInfo->currentFrameY = 0;
    _imageInfo->maxFrameX = maxFrameX - 1;
    _imageInfo->maxFrameY = maxFrameY - 1;
    _imageInfo->frameWidth = width / maxFrameX;
    _imageInfo->frameHeight = height / maxFrameY;

    int len = (int)strlen(fileName);
    int idx = len + 1;
    _fileName = new char[idx];
    strcpy_s(_fileName, idx, fileName);

    _isTrans = isTrans;
    _transColor = transColor;

    if (_imageInfo->hBit == 0)
    {
        release();
        return E_FAIL;
    }

    ReleaseDC(_hWnd, hdc);

    return S_OK;
}

HRESULT GImage::initForAlphaBlend(void)
{
    HDC hdc = GetDC(_hWnd);

    // ���ĺ����� �ɼ�
    _blendFunc.BlendFlags = 0;
    _blendFunc.AlphaFormat = 0;
    _blendFunc.BlendOp = AC_SRC_OVER;       // ������ �ɼ� - �ȼ����� ������� �ʰ� �׳� �׸��ڴ�. (CPU�� ���� ����ϸ� �����ɸ��⋚���� GPU���� �ðܾ��Ѵ�.)
    //_blendFunc.SourceConstantAlpha = 0;

    _blendImage = new IMAGE_INFO;
    _blendImage->loadType = LOAD_FILE;
    _blendImage->resID = 0;
    _blendImage->hMemDC = CreateCompatibleDC(hdc);
    _blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
    _blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
    _blendImage->width = WINSIZE_X;
    _blendImage->height = WINSIZE_Y;

    ReleaseDC(_hWnd, hdc);

    return S_OK;
}

void GImage::setTransColor(bool isTrans, COLORREF transColor)
{
    _isTrans = isTrans;
    _transColor = transColor;
}

// Ư�� �̹��������� �ſ� �߿��� �Լ� (�޸� ����)
void GImage::release(void)
{
    if (_imageInfo)
    {
        // �̹��� ����
        SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
        DeleteObject(_imageInfo->hBit);
        DeleteDC(_imageInfo->hMemDC);

        // ������ ����
        SAFE_DELETE(_imageInfo);
        SAFE_DELETE_ARRAY(_fileName);

        // ���� �÷�Ű �ʱ�ȭ
        _isTrans = false;
        _transColor = RGB(0, 0, 0);
    }

    if (_blendImage)
    {
        SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
        DeleteObject(_blendImage->hBit);
        DeleteObject(_blendImage->hMemDC);

        SAFE_DELETE(_blendImage);
    }
}

void GImage::render(HDC hdc)
{
    if (_isTrans)
    {
        // GdiTransparentBlt() : ��Ʈ���� �ҷ��ö� Ư�� ������ �����ϰ� �����Ѵ�.
        GdiTransparentBlt
        (
            hdc,                        // ������ ����� DC (ȭ�� DC)
            0,                          // ����� ��ǥ ���� X
            0,                          // ����� ��ǥ ���� Y
            _imageInfo->width,          // ����� �̹��� ���� ũ��
            _imageInfo->height,         // ����� �̹��� ���� ũ��
            _imageInfo->hMemDC,         // ����� ��� �޸� DC
            0, 0,                       // ���� ��������
            _imageInfo->width,          // ���� ���� ���� ũ��
            _imageInfo->height,         // ���� ���� ���� ũ��
            _transColor                 // ������ �� ������ ���� (����Ÿ)
        );
    }

    else
    {
        // �� BitBlt() : DC���� �������� ���� ���� ���縦 ���ش�.
        //      �� SRCCOPY : �ҽ� ������ ������ �����Ѵ�.
        BitBlt(hdc, 0, 0, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, SRCCOPY);
    }
}

void GImage::render(HDC hdc, int destX, int destY)
{
    if (_isTrans)
    {
        // GdiTransparentBlt() : ��Ʈ���� �ҷ��ö� Ư�� ������ �����ϰ� �����Ѵ�.
        GdiTransparentBlt
        (
            hdc,                        // ������ ����� DC (ȭ�� DC)
            destX,                      // ����� ��ǥ ���� X
            destY,                      // ����� ��ǥ ���� Y
            _imageInfo->width,          // ����� �̹��� ���� ũ��
            _imageInfo->height,         // ����� �̹��� ���� ũ��
            _imageInfo->hMemDC,         // ����� ��� �޸� DC
            0, 0,                       // ���� ��������
            _imageInfo->width,          // ���� ���� ���� ũ��
            _imageInfo->height,         // ���� ���� ���� ũ��
            _transColor                 // ������ �� ������ ���� (����Ÿ)
        );
    }

    else
    {
        // �� BitBlt() : DC���� �������� ���� ���� ���縦 ���ش�.
        //      �� SRCCOPY : �ҽ� ������ ������ �����Ѵ�.
        BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, SRCCOPY);
    }
}

// �̹��� Ŭ���� : ���� �̹����� �����ؼ� ����, ���� ũ�⸦ �߶� ���� ���ϴ°��� ����
void GImage::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
    if (_isTrans)
    {
        // GdiTransparentBlt() : ��Ʈ���� �ҷ��ö� Ư�� ������ �����ϰ� �����Ѵ�.
        GdiTransparentBlt
        (
            hdc,                        // ������ ����� DC (ȭ�� DC)
            destX,                      // ����� ��ǥ ���� X
            destY,                      // ����� ��ǥ ���� Y
            sourWidth,                  // ����� �̹��� ���� ũ��
            sourHeight,                 // ����� �̹��� ���� ũ��
            _imageInfo->hMemDC,         // ����� ��� �޸� DC
            sourX, sourY,               // ���� ��������
            sourWidth,                  // ���� ���� ���� ũ��
            sourHeight,                 // ���� ���� ���� ũ��
            _transColor                 // ������ �� ������ ���� (����Ÿ)
        );
    }

    else
    {
        // �� BitBlt() : DC���� �������� ���� ���� ���縦 ���ش�.
        //      �� SRCCOPY : �ҽ� ������ ������ �����Ѵ�.

        BitBlt(hdc, destX, destY, sourWidth, sourHeight, _imageInfo->hMemDC, sourX, sourY, SRCCOPY);
    }
}

void GImage::render(HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight)
{
    if (_isTrans)
    {
        // GdiTransparentBlt() : ��Ʈ���� �ҷ��ö� Ư�� ������ �����ϰ� �����Ѵ�.
        GdiTransparentBlt
        (
            hdc,                        // ������ ����� DC (ȭ�� DC)
            destX,                      // ����� ��ǥ ���� X
            destY,                      // ����� ��ǥ ���� Y
            destWidth,                   // ����� �̹��� ���� ũ��
            destHeight,                 // ����� �̹��� ���� ũ��
            _imageInfo->hMemDC,         // ����� ��� �޸� DC
            sourX, sourY,               // ���� ��������
            sourWidth,                  // ���� ���� ���� ũ��
            sourHeight,                 // ���� ���� ���� ũ��
            _transColor                 // ������ �� ������ ���� (����Ÿ)
        );
    }

    else
    {
        StretchBlt(hdc, destX, destY, destWidth, destHeight, _imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, SRCCOPY);
    }
}

void GImage::frameRender(HDC hdc, int destX, int destY)
{
    if (_isTrans)
    {
        GdiTransparentBlt
        (
            hdc,
            destX,
            destY,
            _imageInfo->frameWidth,
            _imageInfo->frameHeight,
            _imageInfo->hMemDC,
            _imageInfo->currentFrameX * _imageInfo->frameWidth,
            _imageInfo->currentFrameY * _imageInfo->frameHeight,
            _imageInfo->frameWidth,
            _imageInfo->frameHeight,
            _transColor
        );
    }

    else
    {
        // �� BitBlt() : DC���� �������� ���� ���� ���縦 ���ش�.
        //      �� SRCCOPY : �ҽ� ������ ������ �����Ѵ�.
        BitBlt(hdc, destX, destY,
            _imageInfo->frameWidth,
            _imageInfo->frameHeight,
            _imageInfo->hMemDC,
            _imageInfo->currentFrameX * _imageInfo->frameWidth,
            _imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
    }
}

void GImage::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
    // �̹��� ����ó��
    _imageInfo->currentFrameX = currentFrameX;
    _imageInfo->currentFrameY = currentFrameY;

    if (currentFrameX > _imageInfo->maxFrameX)
    {
        _imageInfo->currentFrameX = _imageInfo->maxFrameX;
    }

    if (currentFrameY > _imageInfo->maxFrameY)
    {
        _imageInfo->currentFrameY = _imageInfo->maxFrameY;
    }


    if (_isTrans)
    {
        GdiTransparentBlt
        (
            hdc,
            destX,
            destY,
            _imageInfo->frameWidth,
            _imageInfo->frameHeight,
            _imageInfo->hMemDC,
            _imageInfo->currentFrameX * _imageInfo->frameWidth,
            _imageInfo->currentFrameY * _imageInfo->frameHeight,
            _imageInfo->frameWidth,
            _imageInfo->frameHeight,
            _transColor
        );
    }

    else
    {
        // �� BitBlt() : DC���� �������� ���� ���� ���縦 ���ش�.
        //      �� SRCCOPY : �ҽ� ������ ������ �����Ѵ�.
        BitBlt(hdc, destX, destY,
            _imageInfo->frameWidth,
            _imageInfo->frameHeight,
            _imageInfo->hMemDC,
            _imageInfo->currentFrameX * _imageInfo->frameWidth,
            _imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
    }
}

void GImage::frameAlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
    // ���ĺ����带 ó�� ����ϸ� �ʱ�ȭ
    if (!_blendImage) initForAlphaBlend();

    _blendFunc.SourceConstantAlpha = alpha;

    // �̹��� ����ó��
    _imageInfo->currentFrameX = currentFrameX;
    _imageInfo->currentFrameY = currentFrameY;

    if (currentFrameX > _imageInfo->maxFrameX)
    {
        _imageInfo->currentFrameX = _imageInfo->maxFrameX;
    }

    if (currentFrameY > _imageInfo->maxFrameY)
    {
        _imageInfo->currentFrameY = _imageInfo->maxFrameY;
    }

    if (_isTrans)
    {
        // 1. ����ؾ� �� DC�� �׷��� �ִ� ������ ������ �̹����� �׸���. (����)
        BitBlt
        (
            _blendImage->hMemDC,
            0,
            0,
            _imageInfo->frameWidth,
            _imageInfo->frameHeight,
            hdc,
            destX,
            destY,
            SRCCOPY
        );

        // 2. ���� �̹����� ����� ���� �� ������ �̹����� �׸���.
        GdiTransparentBlt
        (
            _blendImage->hMemDC,                                        // ������ ����� DC (ȭ�� DC)
            0, 0,                                                       // ����� ��ǥ ����
            _imageInfo->frameWidth,                                     // ����� �̹��� ���� ũ��
            _imageInfo->frameHeight,                                    // ����� �̹��� ���� ũ��
            _imageInfo->hMemDC,                                         // ����� ��� �޸� DC
            _imageInfo->currentFrameX * _imageInfo->frameWidth,         // ���� �������� X
            _imageInfo->currentFrameY * _imageInfo->frameHeight,        // ���� �������� Y
            _imageInfo->frameWidth,                                     // ���� ���� ���� ũ��
            _imageInfo->frameHeight,                                    // ���� ���� ���� ũ��
            _transColor                                                 // ������ �� ������ ���� (����Ÿ)
        );


        // 3. ������ �̹����� ȭ�鿡 �׸���.
        AlphaBlend
        (
            hdc,
            destX, destY,
            _imageInfo->frameWidth,
            _imageInfo->frameHeight,
            _blendImage->hMemDC,
            0,
            0,
            _imageInfo->frameWidth,
            _imageInfo->frameHeight,
            _blendFunc
        );
    }

    else
    {
        AlphaBlend(hdc,
            destX, destY,
            _imageInfo->frameWidth,
            _imageInfo->frameHeight,
            _imageInfo->hMemDC, 
            _imageInfo->currentFrameX * _imageInfo->frameWidth,
            _imageInfo->currentFrameY * _imageInfo->frameHeight,
            _imageInfo->frameWidth,
            _imageInfo->frameHeight,
            _blendFunc);
    }
}

void GImage::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
    //IMAGEMANAGER->loopRender("bg_loop", getMemDC(), &RectMake(0, 0, WINSIZE_X, WINSIZE_Y), _bgSpeed, _offsetY);
    //IMAGEMANAGER->loopRender("bg_loop", getMemDC(), &RectMake(100, WINSIZE_Y / 2 - 200, 800, 400), _bgSpeed, _offsetY);

    // offset ���� ������ ��� ����
    if (offsetX < 0)
    {
        offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
    }

    if (offsetY < 0)
    {
        offsetY = _imageInfo->height + (offsetY % _imageInfo->height);
    }

    // �׷����� ���� ����
    RECT rcSour = {};
    int sourWidth;
    int sourHeight;

    // �׷����� DC ���� (ȭ�� ũ��)
    RECT rcDest = {};
    // �׷����� ��ü ����
    int drawAreaX = drawArea->left;
    int drawAreaY = drawArea->top;
    int drawAreaW = drawArea->right - drawArea->left;
    int drawAreaH = drawArea->bottom - drawArea->top;

    // ���� ���� ����
    for (int y = 0; y < drawAreaH; y += sourHeight)
    {
        // �ҽ� ������ ���� ���
        rcSour.top = (y + offsetY) % _imageInfo->height;
        rcSour.bottom = _imageInfo->height;
        sourHeight = rcSour.bottom - rcSour.top;

        // �ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ� (ȭ������� ������)
        if (y + sourHeight > drawAreaH)
        {
            // �Ѿ �׸��� ����ŭ botoom���� �÷��ش�.
            rcSour.bottom -= (y + sourHeight) - drawAreaH;
            sourHeight = rcSour.bottom - rcSour.top;
        }

        // �׷����� ����
        rcDest.top = y + drawAreaY;
        rcDest.bottom = rcDest.top + sourHeight;


        // ���� ��������
        for (int x = 0; x < drawAreaW; x += sourWidth)
        {
            rcSour.left = (x + offsetX) % _imageInfo->width;
            rcSour.right = _imageInfo->width;
            sourWidth = rcSour.right - rcSour.left;

            if (x + sourWidth > drawAreaW)
            {
                rcSour.right -= (x + sourWidth) - drawAreaW;
                sourWidth = rcSour.right - rcSour.left;
            }

            rcDest.left = x + drawAreaX;
            rcDest.right = rcDest.right + sourWidth;

            render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, sourWidth, sourHeight);
        }
    }
}

void GImage::loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{

}

// ���� ����
void GImage::alphaRender(HDC hdc, BYTE alpha)
{
    // ���ĺ����带 ó�� ����ϸ� �ʱ�ȭ
    if (!_blendImage) initForAlphaBlend();

    _blendFunc.SourceConstantAlpha = alpha;

    if (_isTrans)
    {
        // 1. ����ؾ� �� DC�� �׷��� �ִ� ������ ������ �̹����� �׸���. (����)
        BitBlt
        (
            _blendImage->hMemDC,
            0, 0,
            _imageInfo->frameWidth,
            _imageInfo->frameHeight,
            hdc,
            0, 0,
            SRCCOPY
        );

        // 2. ���� �̹����� ����� ���� �� ������ �̹����� �׸���.
        GdiTransparentBlt
        (
            _blendImage->hMemDC,                // ������ ����� DC (ȭ�� DC)
            0, 0,                               // ����� ��ǥ ����
            _imageInfo->width,                  // ����� �̹��� ���� ũ��
            _imageInfo->height,                 // ����� �̹��� ���� ũ��
            _imageInfo->hMemDC,                 // ����� ��� �޸� DC
            0, 0,                               // ���� ��������
            _imageInfo->width,                  // ���� ���� ���� ũ��
            _imageInfo->height,                 // ���� ���� ���� ũ��
            _transColor                         // ������ �� ������ ���� (����Ÿ)
        );

        // 3. ������ �̹����� ȭ�鿡 �׸���.
        AlphaBlend
        (
            hdc,
            0, 0,
            _imageInfo->width,
            _imageInfo->height,
            _blendImage->hMemDC,
            0, 0,
            _imageInfo->width,
            _imageInfo->height,
            _blendFunc
        );
    }

    else
    {
        AlphaBlend(hdc, 0, 0, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
    }
}

void GImage::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
    // ���ĺ����带 ó�� ����ϸ� �ʱ�ȭ
    if (!_blendImage) initForAlphaBlend();

    _blendFunc.SourceConstantAlpha = alpha;

    if (_isTrans)
    {
        // 1. ����ؾ� �� DC�� �׷��� �ִ� ������ ������ �̹����� �׸���. (����)
        BitBlt
        (
            _blendImage->hMemDC,
            0, 0,
            _imageInfo->width,
            _imageInfo->height,
            hdc,
            destX, destY,
            SRCCOPY
        );

        // 2. ���� �̹����� ����� ���� �� ������ �̹����� �׸���.
        GdiTransparentBlt
        (
            _blendImage->hMemDC,                // ������ ����� DC (ȭ�� DC)
            0, 0,                               // ����� ��ǥ ����
            _imageInfo->width,                  // ����� �̹��� ���� ũ��
            _imageInfo->height,                 // ����� �̹��� ���� ũ��
            _imageInfo->hMemDC,                 // ����� ��� �޸� DC
            0, 0,                               // ���� ��������
            _imageInfo->width,                  // ���� ���� ���� ũ��
            _imageInfo->height,                 // ���� ���� ���� ũ��
            _transColor                         // ������ �� ������ ���� (����Ÿ)
        );

        // 3. ������ �̹����� ȭ�鿡 �׸���.
        AlphaBlend
        (
            hdc,
            destX, destY,
            _imageInfo->width,
            _imageInfo->height,
            _blendImage->hMemDC,
            0, 0,
            _imageInfo->width,
            _imageInfo->height,
            _blendFunc
        );
    }

    else
    {
        AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
    }
}

void GImage::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{

}