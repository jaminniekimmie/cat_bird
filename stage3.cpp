#include "stdafx.h"
#include "stage3.h"

HRESULT stage3::init(void)
{
	_player = new player;
	_player->init();
	_player->setX(390);
	_player->setY(540);

	_randNo = -1;
	_benchAngle = 0;
	_loopX = _loopY = 0;
	_wiggleX = _wiggleY = 0;
	_count = _index = _riverIndex = _crownIndex = _goldenKeyIndex = _clearCount = _gameCount = 0;
	_state = IDLE;
	_dir = LEFT;
	_whiteAlpha = 0;
	_gameClear = _gameOver = _goldenKeyGet = _bling = false;
	_gameStart = _isWiggle = _isActive = true;

	//¹é±×¶ó¿îµå ÀÌ¹ÌÁö ÃÊ±âÈ­
	IMAGEMANAGER->addImage("bg_arrowhead", "img/CB_bg_arrowhead_01.bmp", 144, 144);
	IMAGEMANAGER->addImage("map_stage3", "img/CB_map_stage3_01.bmp", 2557, 903, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("map_stage3_frame", "img/CB_map_stage3_frame_01.bmp", 2557, 903, true, RGB(255, 0, 255));

	_goldenKey[IDLE].frameX = 11;
	_goldenKey[IDLE].img = IMAGEMANAGER->addFrameImage("goldenKeyIdle", "img/CB_obj_goldenKey_Idle_sprite_01.bmp", 1142, 750, 627, 57, _goldenKey[IDLE].frameX, 1, true, RGB(255, 0, 255));
	_goldenKey[1].frameX = 3;
	_goldenKey[1].img = IMAGEMANAGER->addFrameImage("goldenKeyGet", "img/CB_obj_goldenKey_get_sprite_01.bmp", 1142, 750, 171, 54, _goldenKey[1].frameX, 1, true, RGB(255, 0, 255));

	_crown.frameX = 10;
	_crown.img = IMAGEMANAGER->addFrameImage("crown", "img/CB_crown_sprite_01.bmp", 600, 28, _crown.frameX, 1, true, RGB(255, 0, 255));
	_crown.img->setX(1142); _crown.img->setY(300);

	for (int i = 0; i < 2; i++)
	{
		_river[i].img = new image;
		_river[i].frameX = 3;
		_river[i].img->init("img/CB_obj_water_sprite_01.bmp", 864, 144, _river[i].frameX, 1, true, RGB(255, 0, 255));
		_river[i].img->setY(700);
	}
	_river[0].img->setX(410);
	_river[1].img->setX(1600);

	for (int i = 0; i < 12; i++)
		_dot[i].img = IMAGEMANAGER->addImage("dot", "img/CB_obj_dot_sprite_01.bmp", 9, 9);

	for (int i = 0; i < 4; i++)
	{
		_bench[i].img = new image;
		_bench[i].img->init("img/CB_obj_bench_sprite_01.bmp", 500.0f, 500.0f, 126, 21, true, RGB(255, 0, 255));
	}

	_benchPivot = IMAGEMANAGER->addImage("benchPivot", "img/CB_obj_benchPivot_sprite_01.bmp", 1163, 519, 24, 28, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("whiteScreen", "img/CB_fx_whiteScreen_01.bmp", 1280, 720);

	_collider[0] = RectMake(0, 615, 495, 15);		//init ÁöÁ¡
	_collider[1] = RectMake(0, 0, 2557, 259);		//ÃµÀå
	_collider[2] = RectMake(196, 316, 85, 15);		//¸Ç ¿Þ ÃµÀå °è´Ü ¹Ø
	_collider[3] = RectMake(266, 259, 15, 56);		//¸Ç ¿Þ ÃµÀå °è´Ü ¹Ø
	_collider[4] = RectMake(2059, 316, 85, 15 );	//¿À ³¡ ÃµÀå
	_collider[5] = RectMake(638, 316, 284, 15 );	//ÃµÀå
	_collider[6] = RectMake(1417, 316, 286, 15);	//ÃµÀå
	_collider[7] = RectMake(196, 331, 15, 141);		//¿Þº®
	_collider[8] = RectMake(266, 488, 15, 55 );		//init ÁöÁ¡ À§À§ °è´Ü º®
	_collider[9] = RectMake(339, 559, 15, 55 );		//¸Ç ¿Þ initÁöÁ¡ À§ °è´Ü º®
	_collider[10] = RectMake(481, 630, 15, 273);	//¸Ç ¿Þ initÁöÁ¡ ¾Æ·¡ÂÊ º®
	_collider[11] = RectMake(836, 488, 15, 269);	//Áß°£ º® ¿À
	_collider[12] = RectMake(1049, 772, 15, 130);	//¿Þ ÀÌ»¡ º®
	_collider[13] = RectMake(1688, 488, 15, 415);	//2º® ¿À
	_collider[14] = RectMake(907, 259, 15, 56  );	//¿Þº®
	_collider[15] = RectMake(1688, 259, 15, 57 );	//¿Þº®
	_collider[16] = RectMake(1121, 822, 15, 7  );	//¿­¼è ¿ÞÂÊ º®
	_collider[17] = RectMake(1279, 772, 15, 131);	//¿À ÀÌ»¡ º®
	_collider[18] = RectMake(638, 488, 15, 415);	//Áß°£ º® ¿Þ
	_collider[19] = RectMake(1490, 488, 15, 269);	//2º® ¿Þ
	_collider[20] = RectMake(1846, 630, 15, 273);	//¿À ¿úÈ¦ ¹Ø ÁöÁ¡ ¿Àº®
	_collider[21] = RectMake(1987, 559, 15, 57 );	//¿À ¿úÈ¦ ¿· °è´Ü º®
	_collider[22] = RectMake(2059, 488, 15, 56 );	//¿À ¿úÈ¦ ¿· À§ °è´Ü º®
	_collider[23] = RectMake(2059, 259, 15, 56 );	//¿À ³¡ ÃµÀå º®
	_collider[24] = RectMake(2129, 331, 15, 141);	//¿À º®
	_collider[25] = RectMake(638, 259, 15, 56  );	//¿Àº®
	_collider[26] = RectMake(1417, 259, 15, 57 );	//¿Àº®
	_collider[27] = RectMake(1207, 822, 15, 7  );	//¿­¼è ¿À¸¥ÂÊ º®
	_collider[28] = RectMake(266, 544, 87, 15);		//¸Ç ¿Þ initÁöÁ¡ À§ °è´Ü Å¾
	_collider[29] = RectMake(196, 473, 85, 15);		//¸Ç ¿Þ init ÁöÁ¡ À§À§ °è´Ü Å¾
	_collider[30] = RectMake(638, 473, 213, 15);	//Áß°£ Å¾
	_collider[31] = RectMake(836, 757, 228, 15 );	//¿Þ ÀÌ»¡ Å¾
	_collider[32] = RectMake(1279, 757, 211, 15);	//¿À ÀÌ»¡ Å¾
	_collider[33] = RectMake(1490, 473, 213, 15);	//2Å¾
	_collider[34] = RectMake(1846, 615, 711, 15);	//¿À ¿úÈ¦ ¹Ø ÁöÁ¡ Å¾
	_collider[35] = RectMake(1987, 544, 72, 15 );	//¿À ¿úÈ¦ ¿· °è´Ü Å¾
	_collider[36] = RectMake(2059, 473, 70, 15 );	//¿À ¿úÈ¦ ¿· À§ °è´Ü Å¾
	_collider[37] = RectMake(1207, 807, 71, 15 );	//¿­¼è ¿À Å¾
	_collider[38] = RectMake(1064, 807, 71, 15 );	//¿­¼è ¿Þ Å¾
	_collider[39] = RectMake(1064, 829, 214, 74);	//¿­¼è ÀÖ´Â ¹Ù´Ú
	_collider[40] = RectMake(851, 571, 71, 15);		//¼±¹Ý ¿Þ
	_collider[41] = RectMake(1419, 571, 71, 15);	//¼±¹Ý ¿À

	_wormHole = RectMakeCenter(1922, 558, 35, 35);

	_teeth[0] = RectMake(851, 737, 140, 20);
	_teeth[1] = RectMake(1346, 737, 140, 20);

	return S_OK;
}

void stage3::release(void)
{
	_player->release();
	SAFE_DELETE(_player);
	for (int i = 0; i < 4; i++)
		SAFE_DELETE(_bench[i].img);
	for (int i = 0; i < 2; i++)
		SAFE_DELETE(_river[i].img);
}

void stage3::update(void)
{
	_player->update();

	_loopY -= -sinf(-90.0f) * 1.01f;

	// cam process
	if (_player->getCamX() <= 0)
	{
		_player->setCamX(0);
	}
	else if (_player->getCamX() + WINSIZEX >= 2557)
	{
		_player->setCamX(2557 - WINSIZEX);
	}
	if (_player->getCamY() <= 0)
	{
		_player->setCamY(0);
	}
	else if (_player->getCamY() + WINSIZEY >= 903)
	{
		_player->setCamY(903 - WINSIZEY);
	}

	//¹° Âû¶û
	_count++;
	if (_count % 5 == 0)
	{
		_riverIndex++;
		if (_riverIndex > _river[0].frameX)
		{
			_riverIndex = 0;
		}
		for (int i = 0; i < 6; i++)
			_river[i].img->setFrameX(_riverIndex);

	//¿Õ°ü µÕ½Ç
		_crownIndex++;
		if (_crownIndex > _crown.frameX)
		{
			_crownIndex = 0;
		}
		_crown.img->setFrameX(_crownIndex);

	//¿­¼è µÕ½Ç
		_goldenKeyIndex++;
		if (_goldenKeyIndex > _goldenKey[_player->getGoldenKeyGet()].frameX)
		{
			_goldenKeyIndex = 0;
		}
		_goldenKey[_player->getGoldenKeyGet()].img->setFrameX(_goldenKeyIndex);
	}

	benchRotate();
	collide();
	screenBling();
	
}

void stage3::render(void)
{
	RECT rc = RectMake(0, 0, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->loopRender("bg_arrowhead", getMemDC(), &rc, _loopX, _loopY);
	_player->getShadowImg(_player->getState())->frameRender(getMemDC(), _player->getX() - 13 - _player->getCamX(), _player->getY() - _player->getCamY());
	IMAGEMANAGER->render("map_stage3", getMemDC(), 0, 0, _player->getCamX(), _player->getCamY(), WINSIZEX, WINSIZEY);
	if (!_player->getGoldenKeyGet())
		_goldenKey[_player->getGoldenKeyGet()].img->frameRender(getMemDC(), _goldenKey[_player->getGoldenKeyGet()].img->getX() - _player->getCamX(), _goldenKey[_player->getGoldenKeyGet()].img->getY() - _player->getCamY());
	if (!_player->getCrownGet())
		IMAGEMANAGER->frameRender("crown", getMemDC(), _crown.img->getX() - _player->getCamX(), _crown.img->getY() - _player->getCamY());	//¿Õ°ü
	for (int i = 0; i < 2; i++)
		_river[i].img->frameRender(getMemDC(), _river[i].img->getX() - _player->getCamX(), _river[i].img->getY() - _player->getCamY());
	for (int i = 0; i < 12; i++)
		IMAGEMANAGER->render("dot", getMemDC(), _dot[i].x - _player->getCamX(), _dot[i].y - _player->getCamY());
	IMAGEMANAGER->render("benchPivot", getMemDC(), _benchPivot->getX() - _player->getCamX(), _benchPivot->getY() - _player->getCamY());
	IMAGEMANAGER->render("map_stage3_frame", getMemDC(), 0, 0, _player->getCamX(), _player->getCamY(), WINSIZEX, WINSIZEY);
	_player->render();
	for (int i = 0; i < 4; i++)
		_bench[i].img->render(getMemDC(), _bench[i].img->getX() - _player->getCamX(), _bench[i].img->getY() - _player->getCamY());

	if (_player->getGoldenKeyGet() || _gameClear || _gameOver)
		IMAGEMANAGER->alphaRender("whiteScreen", getMemDC(), _whiteAlpha);

	if (KEYMANAGER->isToggleKey(VK_RETURN))
	{
		for (int i = 0; i < MAXCOLLIDER; i++)
			Rectangle(getMemDC(), _collider[i].left - _player->getCamX(), _collider[i].top - _player->getCamY(), _collider[i].right - _player->getCamX(), _collider[i].bottom - _player->getCamY());
		Rectangle(getMemDC(), _player->getRect().left - _player->getCamX(), _player->getRect().top - _player->getCamY(), _player->getRect().right - _player->getCamX(), _player->getRect().bottom - _player->getCamY());
		Rectangle(getMemDC(), _wormHole.left - _player->getCamX(), _wormHole.top - _player->getCamY(), _wormHole.right - _player->getCamX(), _wormHole.bottom - _player->getCamY());
		for (int i = 0; i < 2; i++)
			Rectangle(getMemDC(), _river[i].img->boundingBoxWithFrame().left - _player->getCamX(), _river[i].img->boundingBoxWithFrame().top - _player->getCamY(), _river[i].img->boundingBoxWithFrame().right - _player->getCamX(), _river[i].img->boundingBoxWithFrame().bottom - _player->getCamY());
		Rectangle(getMemDC(), _goldenKey[_player->getGoldenKeyGet()].img->boundingBoxWithFrame().left - _player->getCamX(), _goldenKey[_player->getGoldenKeyGet()].img->boundingBoxWithFrame().top - _player->getCamY(), _goldenKey[_player->getGoldenKeyGet()].img->boundingBoxWithFrame().right - _player->getCamX(), _goldenKey[_player->getGoldenKeyGet()].img->boundingBoxWithFrame().bottom - _player->getCamY());
		Rectangle(getMemDC(), _crown.img->boundingBoxWithFrame().left + 15 - _player->getCamX(), _crown.img->boundingBoxWithFrame().top - _player->getCamY(), _crown.img->boundingBoxWithFrame().right - 5 - _player->getCamX(), _crown.img->boundingBoxWithFrame().bottom - _player->getCamY());
		Rectangle(getMemDC(), _teeth[0].left - _player->getCamX(), _teeth[0].top - _player->getCamY(), _teeth[0].right - _player->getCamX(), _teeth[0].bottom - _player->getCamY());
		Rectangle(getMemDC(), _teeth[1].left - _player->getCamX(), _teeth[1].top - _player->getCamY(), _teeth[1].right - _player->getCamX(), _teeth[1].bottom - _player->getCamY());
		for (int i = 0; i < 4; i++)
			Rectangle(getMemDC(), _bench[i].img->boundingBox().left - _player->getCamX(), _bench[i].img->boundingBox().top - _player->getCamY(), _bench[i].img->boundingBox().right - _player->getCamX(), _bench[i].img->boundingBox().bottom - _player->getCamY());

		//if (_player->getOnBench())
		//	TextOut(getMemDC(), 300, 100, "TRUE", strlen("TRUE"));
		//else
		//	TextOut(getMemDC(), 300, 100, "FALSE", strlen("FALSE"));
	}
	
}

void stage3::collide()
{
	RECT temprc;

	if (_isActive)
	{
		if (_player->getY() + (_player->getRect().bottom - _player->getRect().top) >= _collider[0].top)
		{
			/*_player->setY(_collider[0].top - (_player->getRect().bottom - _player->getRect().top));
			_player->setGravity(0.0f);
			_player->setIsJump(false);
			_player->setSpeed(0.0f);
			_player->setState(IDLE);*/
			cameraWiggle();
		}

		for (int i = 0; i < MAXCOLLIDER; i++)
		{
			if (IntersectRect(&temprc, &_collider[i], &_player->getRect()))
			{
				if (1 <= i && i <= 5)	//ÃµÀå
				{
					_player->setY(_collider[i].bottom);
				}
				else if (7 <= i && i <= 16)	//¿ÞÂÊ º®
				{
					_player->setX(_collider[i].right);
				}
				else if (17 <= i && i <= 27)	//¿À¸¥ÂÊ º®
				{
					_player->setX(_collider[i].left - (_player->getRect().right - _player->getRect().left));
				}
				else
				{
					if (-sinf(_player->getAngle()) * _player->getSpeed() * _player->getIsJump() + _player->getGravity() > 0 &&
						_player->getRect().bottom - (-sinf(_player->getAngle()) * _player->getSpeed() * _player->getIsJump() + _player->getGravity()) > 0 &&
						_player->getRect().right > _collider[i].left &&	_player->getRect().left < _collider[i].right && _player->getRect().bottom < _collider[i].bottom)// && _player->getY() - _oldY > 0)
					{
						_player->setOnLand(true);
						_player->setEffectX(_player->getX());
						_player->setEffectY(_collider[i].top);
						_player->setY(_collider[i].top - (_player->getRect().bottom - _player->getRect().top) + 1);
						_player->setIsJump(false);
						_player->setState(IDLE);
						_player->setGravity(0.0f);
						_player->setSpeed(0.0f);
					}
				}
			}
		}

		//µÎµÕ½Ç º¥Ä¡¿¡ ¾ÈÂøÇßÀ» ¶§
		for (int i = 0; i < 4; i++)
		{
			if (IntersectRect(&temprc, &_bench[i].img->boundingBox(), &_player->getRect()))
			{

				if (-sinf(_player->getAngle()) * _player->getSpeed() * _player->getIsJump() + _player->getGravity() > 0 &&
					_player->getRect().bottom - (-sinf(_player->getAngle()) * _player->getSpeed() * _player->getIsJump() + _player->getGravity()) > 0 &&
					_player->getRect().right > _bench[i].img->boundingBox().left &&	_player->getRect().left < _bench[i].img->boundingBox().right && _player->getRect().bottom < _bench[i].img->boundingBox().bottom)// && _player->getY() - _oldY > 0)
				{
					if (!_player->getOnBench())
					{
						tempX = _bench[i].img->getX() - _player->getX();
						_player->setOnBench(true);
					}

					if (oldY - _bench[i].img->getY() < 0)
					{
						//³»·Á°¥‹š

					}
					else
					{
						//¿Ã¶ó°¥¶§
					}

					_player->setOnLand(true);
					if (tempX < 0)
					{
						_player->setX(_bench[i].img->getX() + abs(tempX));
					}
					else
					{
						_player->setX(_bench[i].img->getX() - abs(tempX));
					}
					
					_player->setY(_bench[i].img->getY() - (_player->getRect().bottom - _player->getRect().top) + 1);
					_player->setEffectX(_player->getX());
					_player->setEffectY(_bench[i].img->boundingBox().top);
					//_player->setX(_bench[i].img->boundingBox().right - _bench[i].img->boundingBox().right - _player->getX());
					
					_player->setIsJump(false);
					_player->setState(IDLE);
					_player->setGravity(0.0f);
					_player->setSpeed(0.0f);
					//if (!_onBench)
					//{
					//	tempX = _bench[i].img->boundingBox().right - _player->getX();
					//	_onBench = true;
					//}
					//_player->setX(_bench[i].img->boundingBox().right - tempX);
				}
			}
		}

		//ÀÌ»¡¿¡ ²ÈÇûÀ» ¶§
		for (int i = 0; i < 2; i++)
		{
			if (IntersectRect(&temprc, &_player->getRect(), &_teeth[i]))
			{
				_player->setY(_teeth[i].top - (_player->getRect().bottom - _player->getRect().top) + 1);
				setGameOver(true);
				_player->setEffectX(_player->getX());
				_player->setEffectY(_teeth[i].top);
				_player->setGravity(0.0f);
				_player->setAngle(90.0f);
				_player->setIsJump(true);
				_player->setSpeed(7.0f);
				_player->setState(FAIL);
				_isActive = false;
				_bling = false;
			}
		}

		//ÀÔ¼öÇßÀ» ¶§
		for (int i = 0; i < 2; i++)
		{
			if (IntersectRect(&temprc, &_player->getRect(), &_river[i].img->boundingBoxWithFrame()))
			{
				_player->setY(_river[i].img->boundingBoxWithFrame().top - (_player->getRect().bottom - _player->getRect().top) + 1);
				setGameOver(true);
				_player->setEffectX(_player->getX());
				_player->setEffectY(_river[i].img->boundingBoxWithFrame().top);
				_player->setGravity(0.0f);
				_player->setAngle(90.0f);
				_player->setIsJump(true);
				_player->setSpeed(7.0f);
				_player->setState(FAIL);
				_isActive = false;
				_bling = false;
			}
		}
	}

	//¿Õ°ü°ú ºÎµúÇûÀ» ¶§
	if (IntersectRect(&temprc, &_player->getRect(), &_crown.img->boundingBoxWithFrame()) && !_player->getCrownGet())
	{
		_player->setEffectX(_crown.img->getX() + _crown.img->getFrameWidth() / 2);
		_player->setEffectY(_crown.img->getY() + _crown.img->getFrameHeight() / 2);
		_player->setCrownGet(true);
		_bling = false;
	}

	//¿­¼è¿Í ºÎµúÇûÀ» ¶§
	if (IntersectRect(&temprc, &_player->getRect(), &_goldenKey[_player->getGoldenKeyGet()].img->boundingBoxWithFrame()) && !_player->getGoldenKeyGet())
	{
		_player->setEffectX(_goldenKey[_player->getGoldenKeyGet()].img->getX() + _goldenKey[_player->getGoldenKeyGet()].img->getFrameWidth() / 2);
		_player->setEffectY(_goldenKey[_player->getGoldenKeyGet()].img->getY() + _goldenKey[_player->getGoldenKeyGet()].img->getFrameHeight() / 2);
		_player->setGoldenKeyGet(true);
		_bling = false;
	}

	//¿úÈ¦°ú ºÎµúÇûÀ» ¶§
	if (IntersectRect(&temprc, &_player->getRect(), &_wormHole))
	{
		if (_player->getState() != IDLE && _player->getState() != WALK)
		{
			_player->setEffectX(_wormHole.left);
			_player->setEffectY(_wormHole.bottom);
			_player->setGravity(0.0f);
			_player->setState(TRANS);
			_player->setX(_wormHole.left - 16);
			_player->setY(_wormHole.top - 4);
			_gameStart = false;
			_gameClear = true;
			_bling = false;
			_isWiggle = true;
			cameraWiggle();
		}
	}
}
void stage3::cameraWiggle()
{
	// screen wiggle
	if (_isWiggle)
	{
		if (_gameCount > 10)
		{
			_isWiggle = false;
			_gameCount = 0;
		}
		else
		{
			_gameCount++;
			//_player->setCamX(_player->getCamX() + RND->getInt(20) - 20);
			_player->setCamY(_player->getCamY() + RND->getInt(30) - 30);
		}
	}
}

void stage3::screenBling()
{
	//È­¸é ¹ÝÂ¦
	if (_player->getGoldenKeyGet() || _player->getCrownGet() || _gameClear || _gameOver)
	{
		if (_count % 3 == 0)
		{
			if (!_bling)
			{
				if (_whiteAlpha < 120)
					_whiteAlpha += 120 / 3;
				else
				{
					_whiteAlpha = 120;
					_bling = true;
				}
			}
			else
			{
				if (_whiteAlpha <= 0)
				{
					_whiteAlpha = 0;
				}
				else
				{
					_whiteAlpha -= 120 / 6;
				}
			}
		}
	}
}

void stage3::benchRotate()
{
	if (_count % 5 == 0)
		_benchAngle += 0.05;
	for (int i = 0; i < 3; i++)
	{
		_dot[i].x = cosf(_benchAngle) * ((i + 1) * 42) + (_benchPivot->getX() + _benchPivot->getWidth() / 2 - 5);
		_dot[i].y = -sinf(_benchAngle) * ((i + 1) * 42) + (_benchPivot->getY() + _benchPivot->getHeight() / 2 - 5);

		_dot[i + 3].x = cosf(_benchAngle + PI_2) * ((i + 1) * 42) + (_benchPivot->getX() + _benchPivot->getWidth() / 2 - 5);
		_dot[i + 3].y = -sinf(_benchAngle + PI_2) * ((i + 1) * 42) + (_benchPivot->getY() + _benchPivot->getHeight() / 2 - 5);
		
		_dot[i + 6].x = cosf(_benchAngle + PI) * ((i + 1) * 42) + (_benchPivot->getX() + _benchPivot->getWidth() / 2 - 5);
		_dot[i + 6].y = -sinf(_benchAngle + PI) * ((i + 1) * 42) + (_benchPivot->getY() + _benchPivot->getHeight() / 2 - 5);
		
		_dot[i + 9].x = cosf(_benchAngle - PI_2) * ((i + 1) * 42) + (_benchPivot->getX() + _benchPivot->getWidth() / 2 - 5);
		_dot[i + 9].y = -sinf(_benchAngle - PI_2) * ((i + 1) * 42) + (_benchPivot->getY() + _benchPivot->getHeight() / 2 - 5);
	}
	for (int i = 0; i < 4; i++)
	{
		//oldX = _bench[i].x;
		//oldY = _bench[i].y;

		oldX = _bench[i].img->getX();
		oldY = _bench[i].img->getY();

		//_bench[i].x = cosf(_benchAngle + PI_2 * i) * 168 + _benchPivot->getX() + _benchPivot->getWidth() / 2 - _bench[i].img->getWidth() / 2;
		//_bench[i].y = -sinf(_benchAngle + PI_2 * i) * 170 + _benchPivot->getY() + _benchPivot->getHeight() / 2 -_bench[i].img->getHeight() / 2;
		//_bench[i].img->setX(_bench[i].x);
		//_bench[i].img->setY(_bench[i].y);

		_bench[i].img->setX(cosf(_benchAngle + PI_2 * i) * 168 + _benchPivot->getX() + _benchPivot->getWidth() / 2 - _bench[i].img->getWidth() / 2);
		_bench[i].img->setY(-sinf(_benchAngle + PI_2 * i) * 170 + _benchPivot->getY() + _benchPivot->getHeight() / 2 - _bench[i].img->getHeight() / 2);
	}
}

