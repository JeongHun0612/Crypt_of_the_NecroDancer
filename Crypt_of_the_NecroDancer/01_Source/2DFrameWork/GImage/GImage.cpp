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
    // 재초기화 방지 (혹시 값이 있다면 먼저 릴리즈하고 접근)
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

    // 리소스를 얻어 오는데 실패
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
    // 재초기화 방지 (혹시 값이 있다면 먼저 릴리즈하고 접근)
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

    // 리소스를 얻어 오는데 실패
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
    // 재초기화 방지 (혹시 값이 있다면 먼저 릴리즈하고 접근)
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
    // strcpy -> 인자 1개 더 추가
    // ㄴ 고질적인 문자/문자열에서 사이즈 문제를 해결한 함수
    // 복사받을 변수, 길이, 원본)
    strcpy_s(_fileName, idx, fileName);

    _isTrans = isTrans;
    _transColor = transColor;

    // 리소스를 얻어 오는데 실패
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

    // 알파블렌드 옵션
    _blendFunc.BlendFlags = 0;
    _blendFunc.AlphaFormat = 0;
    _blendFunc.BlendOp = AC_SRC_OVER;       // 블렌드 옵션 - 픽셀보간 사용하지 않고 그냥 그리겠다. (CPU를 많이 사용하면 오래걸리기떄문에 GPU에게 맡겨야한다.)
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

// 특히 이미지에서는 매우 중요한 함수 (메모리 관리)
void GImage::release(void)
{
    if (_imageInfo)
    {
        // 이미지 삭제
        SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
        DeleteObject(_imageInfo->hBit);
        DeleteDC(_imageInfo->hMemDC);

        // 포인터 삭제
        SAFE_DELETE(_imageInfo);
        SAFE_DELETE_ARRAY(_fileName);

        // 투명 컬러키 초기화
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
        // GdiTransparentBlt() : 비트맵을 불러올때 특정 색상을 제외하고 복사한다.
        GdiTransparentBlt
        (
            hdc,                        // 복사할 장소의 DC (화면 DC)
            0,                          // 복사될 좌표 시작 X
            0,                          // 복사될 좌표 시작 Y
            _imageInfo->width,          // 복사될 이미지 가로 크기
            _imageInfo->height,         // 복사될 이미지 세로 크기
            _imageInfo->hMemDC,         // 복사될 대상 메모리 DC
            0, 0,                       // 복사 시작지점
            _imageInfo->width,          // 복사 영역 가로 크기
            _imageInfo->height,         // 복사 영역 세로 크기
            _transColor                 // 복사할 때 제외할 색상 (마젠타)
        );
    }

    else
    {
        // ◈ BitBlt() : DC간의 영역끼리 서로 고속 복사를 해준다.
        //      ㄴ SRCCOPY : 소스 영역을 영역에 복사한다.
        BitBlt(hdc, 0, 0, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, SRCCOPY);
    }
}

void GImage::render(HDC hdc, int destX, int destY)
{
    if (_isTrans)
    {
        // GdiTransparentBlt() : 비트맵을 불러올때 특정 색상을 제외하고 복사한다.
        GdiTransparentBlt
        (
            hdc,                        // 복사할 장소의 DC (화면 DC)
            destX,                      // 복사될 좌표 시작 X
            destY,                      // 복사될 좌표 시작 Y
            _imageInfo->width,          // 복사될 이미지 가로 크기
            _imageInfo->height,         // 복사될 이미지 세로 크기
            _imageInfo->hMemDC,         // 복사될 대상 메모리 DC
            0, 0,                       // 복사 시작지점
            _imageInfo->width,          // 복사 영역 가로 크기
            _imageInfo->height,         // 복사 영역 세로 크기
            _transColor                 // 복사할 때 제외할 색상 (마젠타)
        );
    }

    else
    {
        // ◈ BitBlt() : DC간의 영역끼리 서로 고속 복사를 해준다.
        //      ㄴ SRCCOPY : 소스 영역을 영역에 복사한다.
        BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, SRCCOPY);
    }
}

// 이미지 클리핑 : 원본 이미지를 지정해서 가로, 세로 크기를 잘라서 내가 원하는곳에 렌더
void GImage::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
    if (_isTrans)
    {
        // GdiTransparentBlt() : 비트맵을 불러올때 특정 색상을 제외하고 복사한다.
        GdiTransparentBlt
        (
            hdc,                        // 복사할 장소의 DC (화면 DC)
            destX,                      // 복사될 좌표 시작 X
            destY,                      // 복사될 좌표 시작 Y
            sourWidth,                  // 복사될 이미지 가로 크기
            sourHeight,                 // 복사될 이미지 세로 크기
            _imageInfo->hMemDC,         // 복사될 대상 메모리 DC
            sourX, sourY,               // 복사 시작지점
            sourWidth,                  // 복사 영역 가로 크기
            sourHeight,                 // 복사 영역 세로 크기
            _transColor                 // 복사할 때 제외할 색상 (마젠타)
        );
    }

    else
    {
        // ◈ BitBlt() : DC간의 영역끼리 서로 고속 복사를 해준다.
        //      ㄴ SRCCOPY : 소스 영역을 영역에 복사한다.

        BitBlt(hdc, destX, destY, sourWidth, sourHeight, _imageInfo->hMemDC, sourX, sourY, SRCCOPY);
    }
}

void GImage::render(HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight)
{
    if (_isTrans)
    {
        // GdiTransparentBlt() : 비트맵을 불러올때 특정 색상을 제외하고 복사한다.
        GdiTransparentBlt
        (
            hdc,                        // 복사할 장소의 DC (화면 DC)
            destX,                      // 복사될 좌표 시작 X
            destY,                      // 복사될 좌표 시작 Y
            destWidth,                   // 복사될 이미지 가로 크기
            destHeight,                 // 복사될 이미지 세로 크기
            _imageInfo->hMemDC,         // 복사될 대상 메모리 DC
            sourX, sourY,               // 복사 시작지점
            sourWidth,                  // 복사 영역 가로 크기
            sourHeight,                 // 복사 영역 세로 크기
            _transColor                 // 복사할 때 제외할 색상 (마젠타)
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
        // ◈ BitBlt() : DC간의 영역끼리 서로 고속 복사를 해준다.
        //      ㄴ SRCCOPY : 소스 영역을 영역에 복사한다.
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
    // 이미지 예외처리
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
        // ◈ BitBlt() : DC간의 영역끼리 서로 고속 복사를 해준다.
        //      ㄴ SRCCOPY : 소스 영역을 영역에 복사한다.
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
    // 알파블렌드를 처음 사용하면 초기화
    if (!_blendImage) initForAlphaBlend();

    _blendFunc.SourceConstantAlpha = alpha;

    // 이미지 예외처리
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
        // 1. 출력해야 할 DC에 그려져 있는 내용을 블렌드 이미지에 그린다. (복사)
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

        // 2. 원본 이미지의 배경을 없앤 후 블렌드 이미지에 그린다.
        GdiTransparentBlt
        (
            _blendImage->hMemDC,                                        // 복사할 장소의 DC (화면 DC)
            0, 0,                                                       // 복사될 좌표 시작
            _imageInfo->frameWidth,                                     // 복사될 이미지 가로 크기
            _imageInfo->frameHeight,                                    // 복사될 이미지 세로 크기
            _imageInfo->hMemDC,                                         // 복사될 대상 메모리 DC
            _imageInfo->currentFrameX * _imageInfo->frameWidth,         // 복사 시작지점 X
            _imageInfo->currentFrameY * _imageInfo->frameHeight,        // 복사 시작지점 Y
            _imageInfo->frameWidth,                                     // 복사 영역 가로 크기
            _imageInfo->frameHeight,                                    // 복사 영역 세로 크기
            _transColor                                                 // 복사할 때 제외할 색상 (마젠타)
        );


        // 3. 블렌드 이미지를 화면에 그린다.
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

    // offset 값이 음수인 경우 보정
    if (offsetX < 0)
    {
        offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
    }

    if (offsetY < 0)
    {
        offsetY = _imageInfo->height + (offsetY % _imageInfo->height);
    }

    // 그려지는 영역 세팅
    RECT rcSour = {};
    int sourWidth;
    int sourHeight;

    // 그려지는 DC 영역 (화면 크기)
    RECT rcDest = {};
    // 그려야할 전체 영역
    int drawAreaX = drawArea->left;
    int drawAreaY = drawArea->top;
    int drawAreaW = drawArea->right - drawArea->left;
    int drawAreaH = drawArea->bottom - drawArea->top;

    // 세로 루프 영역
    for (int y = 0; y < drawAreaH; y += sourHeight)
    {
        // 소스 영역의 높이 계산
        rcSour.top = (y + offsetY) % _imageInfo->height;
        rcSour.bottom = _imageInfo->height;
        sourHeight = rcSour.bottom - rcSour.top;

        // 소스 영역이 그리는 화면을 넘어갔다면 (화면밖으로 나갔다)
        if (y + sourHeight > drawAreaH)
        {
            // 넘어간 그림의 값만큼 botoom값을 올려준다.
            rcSour.bottom -= (y + sourHeight) - drawAreaH;
            sourHeight = rcSour.bottom - rcSour.top;
        }

        // 그려지는 영역
        rcDest.top = y + drawAreaY;
        rcDest.bottom = rcDest.top + sourHeight;


        // 가로 루프영역
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

// 알파 렌더
void GImage::alphaRender(HDC hdc, BYTE alpha)
{
    // 알파블렌드를 처음 사용하면 초기화
    if (!_blendImage) initForAlphaBlend();

    _blendFunc.SourceConstantAlpha = alpha;

    if (_isTrans)
    {
        // 1. 출력해야 할 DC에 그려져 있는 내용을 블렌드 이미지에 그린다. (복사)
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

        // 2. 원본 이미지의 배경을 없앤 후 블렌드 이미지에 그린다.
        GdiTransparentBlt
        (
            _blendImage->hMemDC,                // 복사할 장소의 DC (화면 DC)
            0, 0,                               // 복사될 좌표 시작
            _imageInfo->width,                  // 복사될 이미지 가로 크기
            _imageInfo->height,                 // 복사될 이미지 세로 크기
            _imageInfo->hMemDC,                 // 복사될 대상 메모리 DC
            0, 0,                               // 복사 시작지점
            _imageInfo->width,                  // 복사 영역 가로 크기
            _imageInfo->height,                 // 복사 영역 세로 크기
            _transColor                         // 복사할 때 제외할 색상 (마젠타)
        );

        // 3. 블렌드 이미지를 화면에 그린다.
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
    // 알파블렌드를 처음 사용하면 초기화
    if (!_blendImage) initForAlphaBlend();

    _blendFunc.SourceConstantAlpha = alpha;

    if (_isTrans)
    {
        // 1. 출력해야 할 DC에 그려져 있는 내용을 블렌드 이미지에 그린다. (복사)
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

        // 2. 원본 이미지의 배경을 없앤 후 블렌드 이미지에 그린다.
        GdiTransparentBlt
        (
            _blendImage->hMemDC,                // 복사할 장소의 DC (화면 DC)
            0, 0,                               // 복사될 좌표 시작
            _imageInfo->width,                  // 복사될 이미지 가로 크기
            _imageInfo->height,                 // 복사될 이미지 세로 크기
            _imageInfo->hMemDC,                 // 복사될 대상 메모리 DC
            0, 0,                               // 복사 시작지점
            _imageInfo->width,                  // 복사 영역 가로 크기
            _imageInfo->height,                 // 복사 영역 세로 크기
            _transColor                         // 복사할 때 제외할 색상 (마젠타)
        );

        // 3. 블렌드 이미지를 화면에 그린다.
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