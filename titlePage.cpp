#include "stdafx.h"
#include "titlePage.h"

HRESULT titlePage::init(void)
{
	_count = _initIndex = _clickIndex = 0;
	_isClick = false;
	setGameStart(true);
	string str;

	for (int i = 0; i < MAXINIT; i++)
	{
		str = "img/CB_title/CB_title_init (" + to_string(i + 1) + ").bmp";
		_titleInit[i].img = new image;
		_titleInit[i].img->init(str.c_str(), 1280, 720);
	}

	for (int i = 0; i < MAXCLICK; i++)
	{
		str = "img/CB_title/CB_title_click_sprite (" + to_string(i + 1) + ").bmp";
		_titleClick[i].img = new image;
		_titleClick[i].img->init(str.c_str(), 1280, 720);
	}

	_tapButton = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 500, 100);

	return S_OK;
}

void titlePage::release(void)
{
	for (int i = 0; i < MAXINIT; i++)
		SAFE_DELETE(_titleInit[i].img);
	for (int i = 0; i < MAXCLICK; i++)
		SAFE_DELETE(_titleClick[i].img);
}

void titlePage::update(void)
{
	_count++;
	if (_count % 2 == 0)
	{
		if (!_isClick)
		{
			_clickIndex = 0;
			if (_initIndex >= MAXINIT - 1)
				_initIndex = MAXINIT - 1;
			else
				_initIndex++;
		}
		else
		{
			_initIndex = 0;
			if (_clickIndex >= MAXCLICK - 1)
			{
				_clickIndex = MAXCLICK - 1;
				this->setGameClear(true);
			}
			else
				_clickIndex++;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && PtInRect(&_tapButton, _ptMouse))
		_isClick = true;
}

void titlePage::render(void)
{
	if (!_isClick)
		_titleInit[_initIndex].img->render(getMemDC(), 0, 0);
	else
		_titleClick[_clickIndex].img->render(getMemDC(), 0, 0);

	if (KEYMANAGER->isToggleKey(VK_RETURN))
		Rectangle(getMemDC(), _tapButton);
}
