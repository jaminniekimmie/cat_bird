#include "stdafx.h"
#include "smallCreatures.h"

HRESULT smallCreatures::init(void)
{
	_countGreen = _countPurple = _countBlue = 0;
	_indexGreen = _indexPurple = _indexBlue = 0;
	_stateGreen = RND->getInt(3);
	_statePurple = RND->getInt(3);
	_stateBlue = RND->getInt(3);
	_dirGreen = RND->getInt(2);
	_dirPurple = RND->getInt(2);
	_dirBlue = RND->getInt(2);
	_greenX = _purpleX = _blueX = 0;
	_greenY = _purpleY = _blueY = 0;

	_smlBird_green[IDLE].frameX = 3;
	_smlBird_green[IDLE].img = IMAGEMANAGER->addImage("smlBirdGreenIdle", "img/CB_smlBird_green_idle_sprite_01.bmp", 135, 63, _smlBird_green[IDLE].frameX, 2, true, RGB(255, 0, 255));
	_smlBird_green[WALK].frameX = 4;
	_smlBird_green[WALK].img = IMAGEMANAGER->addImage("smlBirdGreenWalk", "img/CB_smlBird_green_walk_sprite_01.bmp", 180, 63, _smlBird_green[WALK].frameX, 2, true, RGB(255, 0, 255));
	_smlBird_green[FLY].frameX = 5;
	_smlBird_green[FLY].img = IMAGEMANAGER->addImage("smlBirdGreenFly", "img/CB_smlBird_green_fly_sprite_01.bmp", 225, 63, _smlBird_green[FLY].frameX, 2, true, RGB(255, 0, 255));

	_smlBird_purple[IDLE].frameX = 3;
	_smlBird_purple[IDLE].img = IMAGEMANAGER->addImage("smlBirdPurpleIdle", "img/CB_smlBird_purple_idle_sprite_01.bmp", 180, 80, _smlBird_purple[IDLE].frameX, 2, true, RGB(255, 0, 255));
	_smlBird_purple[WALK].frameX = 4;
	_smlBird_purple[WALK].img = IMAGEMANAGER->addImage("smlBirdPurpleWalk", "img/CB_smlBird_purple_walk_sprite_01.bmp", 240, 80, _smlBird_purple[WALK].frameX, 2, true, RGB(255, 0, 255));
	_smlBird_purple[FLY].frameX = 5;
	_smlBird_purple[FLY].img = IMAGEMANAGER->addImage("smlBirdPurpleFly", "img/CB_smlBird_purple_fly_sprite_01.bmp", 300, 80, _smlBird_purple[FLY].frameX, 2, true, RGB(255, 0, 255));

	_smlBird_blue[IDLE].frameX = 3;
	_smlBird_blue[IDLE].img = IMAGEMANAGER->addImage("smlBirdBlueIdle", "img/CB_smlBird_blue_idle_sprite_01.bmp", 180, 80, _smlBird_blue[IDLE].frameX, 2, true, RGB(255, 0, 255));
	_smlBird_blue[WALK].frameX = 4;
	_smlBird_blue[WALK].img = IMAGEMANAGER->addImage("smlBirdBlueWalk", "img/CB_smlBird_blue_walk_sprite_01.bmp", 240, 80, _smlBird_blue[WALK].frameX, 2, true, RGB(255, 0, 255));
	_smlBird_blue[FLY].frameX = 5;
	_smlBird_blue[FLY].img = IMAGEMANAGER->addImage("smlBirdBlueFly", "img/CB_smlBird_blue_fly_sprite_01.bmp", 300, 80, _smlBird_blue[FLY].frameX, 2, true, RGB(255, 0, 255));
	
	_smlBird_green[_stateGreen].img->setX(_greenX);
	_smlBird_green[_stateGreen].img->setY(_greenY - _smlBird_green[_stateGreen].img->getFrameHeight());
	_smlBird_purple[_statePurple].img->setX(_purpleX);
	_smlBird_purple[_statePurple].img->setY(_purpleY - _smlBird_purple[_statePurple].img->getFrameHeight());
	_smlBird_blue[_stateBlue].img->setX(_blueX);
	_smlBird_blue[_stateBlue].img->setY(_blueY - _smlBird_blue[_stateBlue].img->getFrameHeight());

	return S_OK;
}

void smallCreatures::release(void)
{
}

void smallCreatures::update(void)
{

	iconAnimLoop(_smlBird_green, _stateGreen, _dirGreen, _indexGreen, _countGreen);
	iconAnimLoop(_smlBird_purple, _statePurple, _dirPurple, _indexPurple, _countPurple);
	iconAnimLoop(_smlBird_blue, _stateBlue, _dirBlue, _indexBlue, _countBlue);
}

void smallCreatures::render(void)
{
	_smlBird_green[_stateGreen].img->frameRender(getMemDC(), _smlBird_green[_stateGreen].img->getX(), _smlBird_green[_stateGreen].img->getY());
	_smlBird_purple[_statePurple].img->frameRender(getMemDC(), _smlBird_purple[_statePurple].img->getX(), _smlBird_purple[_statePurple].img->getY());
	_smlBird_blue[_stateBlue].img->frameRender(getMemDC(), _smlBird_blue[_stateBlue].img->getX(), _smlBird_blue[_stateBlue].img->getY());
}

void smallCreatures::iconAnimLoop(tagImage * img, int state, int dir, int index, int count)
{
	img[state].img->setFrameY(dir);

	if (state == IDLE)
	{
		if (dir == LEFT)
		{
			count++;
			if (count % 2 == 0)
			{
				if (index <= 0)
				{
					index = 0;
					if (count % 100 == 0)
						index = img[state].frameX;
				}
				else
					index--;

				img[state].img->setFrameX(index);
			}
		}
		else	//오른쪽프레임
		{
			count++;
			if (count % 2 == 0)
			{
				if (index >= img[state].frameX)
				{
					index = img[state].frameX;
					if (count % 100 == 0)
						index = 0;
				}
				else
					index++;

				img[state].img->setFrameX(index);
			}
		}
	}
	else
	{
		if (dir == LEFT)
		{
			count++;
			if (count % 2 == 0)
			{
				index--;
				if (index < 0)
				{
					index = img[state].frameX;
				}
				img[state].img->setFrameX(index);
			}
		}
		else	//오른쪽프레임
		{
			count++;
			if (count % 2 == 0)
			{
				index++;
				if (index > img[state].frameX)
				{
					index = 0;
				}
				img[state].img->setFrameX(index);
			}
		}
	}
}
