#include "stdafx.h"
#include "player.h"

HRESULT player::init(void)
{
	//멤버변수 초기화
	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;
	_camX = _x - WINSIZEX / 2;
	_camY = _y - WINSIZEY / 2;
	_effectX = _x;
	_effectY = _y;
	_count = _index = _effectCount = _gameCount = _smokeIndex = _featherIndex = _bubbleIndex = 0;
	_randNo = -1;
	_speed = 7.0f;
	_angle = 90.0f;
	_state = TRANS;
	_dir = RIGHT;
	_gravity = -4.0f;
	_onLand = _goldenKeyGet = _crownGet = _onBench = _boxOnLand[0] = _boxOnLand[1] = false;
	_rightKey = _leftKey = _upKey = false;
	_isJump = true;
	
	_cat[IDLE].frameX = _shadow[IDLE].frameX = 12;
	_cat[IDLE].img = IMAGEMANAGER->addFrameImage("catIdle", "img/CB_cat_idle_sprite_01.bmp", _x, _y, 816, 120, _cat[IDLE].frameX, 2, true, RGB(255, 0, 255));
	_shadow[IDLE].img = IMAGEMANAGER->addFrameImage("shadowIdle", "img/CB_shadow_idle_sprite_01.bmp", _x, _y, 816, 120, _shadow[IDLE].frameX, 2, true, RGB(255, 0, 255));

	_cat[WALK].frameX = _shadow[WALK].frameX = 3;
	_cat[WALK].img = IMAGEMANAGER->addFrameImage("catWalk", "img/CB_cat_walk_sprite_01.bmp", _x, _y, 204, 120, _cat[WALK].frameX, 2, true, RGB(255, 0, 255));
	_shadow[WALK].img = IMAGEMANAGER->addFrameImage("shadowWalk", "img/CB_shadow_walk_sprite_01.bmp", _x, _y, 204, 120, _shadow[WALK].frameX, 2, true, RGB(255, 0, 255));

	_cat[JUMP].frameX = _shadow[JUMP].frameX = 5;
	_cat[JUMP].img = IMAGEMANAGER->addFrameImage("catJump", "img/CB_cat_jump_sprite_01.bmp", _x, _y, 336, 120, _cat[JUMP].frameX, 2, true, RGB(255, 0, 255));
	_shadow[JUMP].img = IMAGEMANAGER->addFrameImage("shadowJump", "img/CB_shadow_jump_sprite_01.bmp", _x, _y, 336, 120, _shadow[JUMP].frameX, 2, true, RGB(255, 0, 255));

	_cat[FALL].frameX = _shadow[FALL].frameX = 6;
	_cat[FALL].img = IMAGEMANAGER->addFrameImage("catFall", "img/CB_cat_fall_sprite_01.bmp", _x, _y, 408, 120, _cat[FALL].frameX, 2, true, RGB(255, 0, 255));
	_shadow[FALL].img = IMAGEMANAGER->addFrameImage("shadowFall", "img/CB_shadow_fall_sprite_01.bmp", _x, _y, 408, 120, _shadow[FALL].frameX, 2, true, RGB(255, 0, 255));

	_cat[FLY].frameX = _shadow[FLY].frameX = 5;
	_cat[FLY].img = IMAGEMANAGER->addFrameImage("catFly", "img/CB_cat_fly_sprite_01.bmp", _x, _y, 340, 112, _cat[FLY].frameX, 2, true, RGB(255, 0, 255));
	_shadow[FLY].img = IMAGEMANAGER->addFrameImage("shadowFly", "img/CB_shadow_fly_sprite_01.bmp", _x, _y, 340, 112, _shadow[FLY].frameX, 2, true, RGB(255, 0, 255));

	_cat[LAND].frameX = _shadow[LAND].frameX = 2;
	_cat[LAND].img = IMAGEMANAGER->addFrameImage("catLand", "img/CB_cat_land_sprite_01.bmp", _x, _y, 136, 120, _cat[LAND].frameX, 2, true, RGB(255, 0, 255));
	_shadow[LAND].img = IMAGEMANAGER->addFrameImage("shadowLand", "img/CB_shadow_land_sprite_01.bmp", _x, _y, 136, 120, _shadow[LAND].frameX, 2, true, RGB(255, 0, 255));

	_cat[FAIL].frameX = _shadow[FAIL].frameX = 4;
	_cat[FAIL].img = IMAGEMANAGER->addFrameImage("catFail", "img/CB_cat_fail_sprite_01.bmp", _x, _y, 272, 120, _cat[FAIL].frameX, 2, true, RGB(255, 0, 255));
	_shadow[FAIL].img = IMAGEMANAGER->addFrameImage("shadowFail", "img/CB_shadow_fail_sprite_01.bmp", _x, _y, 272, 120, _shadow[FAIL].frameX, 2, true, RGB(255, 0, 255));

	_cat[TRANS].frameX = _shadow[TRANS].frameX = 4;
	_cat[TRANS].img = IMAGEMANAGER->addFrameImage("catTrans", "img/CB_cat_transform_sprite_01.bmp", _x, _y, 272, 120, _cat[TRANS].frameX, 2, true, RGB(255, 0, 255));
	_shadow[TRANS].img = IMAGEMANAGER->addFrameImage("shadowTrans", "img/CB_shadow_transform_sprite_01.bmp", _x, _y, 272, 120, _shadow[TRANS].frameX, 2, true, RGB(255, 0, 255));

	_smoke[0].frameX = _smoke[1].frameX = _smoke[2].frameX = 11;
	_smoke[0].img = IMAGEMANAGER->addFrameImage("smoke1", "img/CB_fx_land_smoke_sprite_01.bmp", _effectX, _effectY, 330, 30, _smoke[0].frameX, 1, true, RGB(255, 0, 255));
	_smoke[1].img = IMAGEMANAGER->addFrameImage("smoke2", "img/CB_fx_land_smoke_sprite_02.bmp", _effectX, _effectY, 231, 21, _smoke[1].frameX, 1, true, RGB(255, 0, 255));
	_smoke[2].img = IMAGEMANAGER->addFrameImage("smoke3", "img/CB_fx_takeOff_smoke_sprite_01.bmp", _effectX, _effectY, 198, 18, _smoke[2].frameX, 1, true, RGB(255, 0, 255));

	_feather[0].frameX = _feather[1].frameX = _feather[2].frameX = 14;
	_feather[0].img = IMAGEMANAGER->addFrameImage("feather1", "img/CB_fx_feather_sprite_01.bmp", _effectX, _effectY, 1176, 72, _feather[0].frameX, 1, true, RGB(255, 0, 255));
	_feather[1].img = IMAGEMANAGER->addFrameImage("feather2", "img/CB_fx_feather_sprite_02.bmp", _effectX, _effectY, 1176, 72, _feather[1].frameX, 1, true, RGB(255, 0, 255));
	_feather[2].img = IMAGEMANAGER->addFrameImage("feather3", "img/CB_fx_feather_sprite_03.bmp", _effectX, _effectY, 450, 21, _feather[2].frameX, 1, true, RGB(255, 0, 255));

	_bubbleWhite.frameX = 6;
	_bubbleWhite.img = IMAGEMANAGER->addFrameImage("bubbleWhite", "img/CB_fx_poppingBubble_white_sprite_01.bmp", _effectX, _effectY, 72, 12, _bubbleWhite.frameX, 1, true, RGB(255, 0, 255));

	_keyUp[0] = IMAGEMANAGER->addImage("keyUpIdle", "img/CB_key_up_idle_sprite_01.bmp", 125, 115, true, RGB(255, 0, 255));
	_keyUp[1] = IMAGEMANAGER->addImage("keyUpActive", "img/CB_key_up_active_sprite_01.bmp", 125, 115, true, RGB(255, 0, 255));

	_keyLeft[0] = IMAGEMANAGER->addImage("keyLeftIdle", "img/CB_key_left_idle_sprite_01.bmp", 125, 115, true, RGB(255, 0, 255));
	_keyLeft[1] = IMAGEMANAGER->addImage("keyLeftActive", "img/CB_key_left_active_sprite_01.bmp", 125, 115, true, RGB(255, 0, 255));

	_keyRight[0] = IMAGEMANAGER->addImage("keyRightIdle", "img/CB_key_right_idle_sprite_01.bmp", 125, 115, true, RGB(255, 0, 255));
	_keyRight[1] = IMAGEMANAGER->addImage("keyRightActive", "img/CB_key_right_active_sprite_01.bmp", 125, 115, true, RGB(255, 0, 255));

	return S_OK;
}

void player::release(void)
{
}

void player::update(void)
{
	_gameCount++;
	if (_gameCount > 25)
		_gravity += 0.55f;

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (_state != FLY && _state != TRANS)
			_state = WALK;
		if (_state != TRANS)
		{
			_dir = LEFT;
			_x -= 5.0f;
		}
		_leftKey = true;
		_onBench = false;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_state = IDLE;
		_leftKey = false;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (_state != FLY && _state != TRANS)
			_state = WALK;
		if (_state != TRANS)
		{
			_dir = RIGHT;
			_x += 5.0f;
		}
		_rightKey = true;
		_onBench = false;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_state = IDLE;
		_rightKey = false;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (!_isJump && _state != TRANS)
		{
			_onLand = false;
			_gravity = 0.0f;
			_angle = 90.0f;
			_isJump = true;
			_speed = 12.0f;
			_state = JUMP;
		}
		_upKey = true;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (_state == FALL)
		{
			_state = FLY;
		}
		_upKey = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		if (_isJump && _state == FLY)
		{
			_state = FALL;
			_gravity += 0.55f;
		}
		_upKey = false;
	}

	if (_gameCount > 25)
	{
		_y += -sin(_angle) * _speed + _gravity;
		if (-sinf(_angle) * _speed + _gravity > 0)
		{
			if (_state == FLY)
				_gravity -= 0.54f;
			else if (_state != FLY && _state != FAIL)
				_state = FALL;
		}
	}
	for (int i = 0; i < MAXSTATE; i++)
	{
		_cat[i].img->setX(_x);
		_cat[i].img->setY(_y);
	}

	_camX = _x - WINSIZEX / 2;
	_camY = _y - WINSIZEY / 2;

	_rc = _cat[_state].img->boundingBoxWithFrame();

	effectAnim();
}

void player::render(void)
{
	characterAnimLoop(_state);

	_cat[_state].img->frameRender(getMemDC(), _cat[_state].img->getX() - _camX, _cat[_state].img->getY() - _camY);

	if (_state == JUMP || _onLand || _boxOnLand[0] || _boxOnLand[1])
	{
		for (int i = 0; i < 4; i++)
		{
			_smoke[i].img->frameRender(getMemDC(), _effectX + i * 25 - _camX, _effectY - 5 - _camY);
		}
	}
	else
	{
		_smokeIndex = 0;
	}

	if (_state == TRANS)
	{
		_bubbleWhite.img->frameRender(getMemDC(), _effectX - 10 - _camX, _effectY + 10 - _camY);
	}
	else
	{
		_bubbleIndex = 0;
	}

	if (_goldenKeyGet || _crownGet || _state == TRANS || _state == FAIL)
	{
		for (int i = 0; i < 3; i++)
			_feather[i].img->frameRender(getMemDC(), _effectX - i * 5 - _camX, _effectY - i * 5 - _camY);
	}
	else
	{
		_featherIndex = 0;
	}

	_keyLeft[_leftKey]->alphaRender(getMemDC(), 44, 573, 70);
	_keyRight[_rightKey]->alphaRender(getMemDC(), 203, 573, 70);
	_keyUp[_upKey]->alphaRender(getMemDC(), 1110, 573, 70);


	char str[256];
	sprintf_s(str, "%d", _state);
	TextOut(getMemDC(), _x - _camX, _y - _camY, str, strlen(str));
}

void player::characterAnimLoop(int state)
{
	_cat[state].img->setFrameY(_dir);
	_shadow[state].img->setFrameY(_dir);

	if (_state == IDLE)
	{
		if (_dir == LEFT)
		{
			_count++;
			if (_count % 2 == 0)
			{
				if (_index <= 0)
				{
					_index = 0;
					if (_count % 100 == 0)
						_index = _cat[state].frameX;
				}
				else
					_index--;

				_cat[state].img->setFrameX(_index);
				_shadow[state].img->setFrameX(_index);
			}
		}
		else	//오른쪽프레임
		{
			_count++;
			if (_count % 2 == 0)
			{
				if (_index >= _cat[state].frameX)
				{
					_index = _cat[state].frameX;
					if (_count % 100 == 0)
						_index = 0;
				}
				else
					_index++;

				_cat[state].img->setFrameX(_index);
				_shadow[state].img->setFrameX(_index);
			}
		}
	}
	else
	{
		if (_dir == LEFT)
		{
			_count++;
			if (_count % 2 == 0)
			{
				_index--;
				if (_index < 0)
				{
					_index = _cat[state].frameX;
				}
				_cat[state].img->setFrameX(_index);
				_shadow[state].img->setFrameX(_index);
			}
		}
		else	//오른쪽프레임
		{
			_count++;
			if (_count % 2 == 0)
			{
				_index++;
				if (_index > _cat[state].frameX)
				{
					_index = 0;
				}
				_cat[state].img->setFrameX(_index);
				_shadow[state].img->setFrameX(_index);
			}
		}
	}
}

void player::effectAnim()
{
	if (_state == JUMP || _onLand || _boxOnLand[0] || _boxOnLand[1])
	{
		_effectCount++;
		if (_effectCount % 5 == 0)
		{
			for (int i = 0; i < 3; i++)
			{
				if (_smokeIndex >= _smoke[i].frameX)
				{
					_smokeIndex = _smoke[i].frameX;
				}
				else
					_smokeIndex++;

				_smoke[i].img->setFrameX(_smokeIndex);
			}
		}
	}
	if (_state == TRANS)
	{
		_effectX = _x;
		_effectY = _y;
		_effectCount++;
		if (_effectCount % 5 == 0)
		{
			if (_bubbleIndex >= _bubbleWhite.frameX)
			{
				_bubbleIndex = _bubbleWhite.frameX;
			}
			else
				_bubbleIndex++;

			_bubbleWhite.img->setFrameX(_bubbleIndex);
		}
	}
	if (_crownGet || _goldenKeyGet || _state == TRANS || _state == FAIL)
	{
		_effectCount++;
		if (_effectCount % 5 == 0)
		{
			for (int i = 0; i < 3; i++)
			{
				if (_featherIndex >= _feather[i].frameX)
				{
					_featherIndex = _feather[i].frameX;
				}
				else
					_featherIndex++;

				_feather[i].img->setFrameX(_featherIndex);
			}
		}
	}
}
