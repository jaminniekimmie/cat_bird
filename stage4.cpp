#include "stdafx.h"
#include "stage4.h"

HRESULT stage4::init(void)
{
	_player = new player;
	_player->init();
	_player->setX(2000);
	_player->setX(609);
	_player->setY(220);

	_randNo = -1;
	_benchAngle = 0;
	_loopX = _loopY = 0;
	_wiggleX = _wiggleY = 0;
	_count = _index = _riverIndex = _goldenKeyIndex = _safeIndex = _clearCount = _gameCount = 0;
	_state = IDLE;
	_dir = LEFT;
	_whiteAlpha = 0;
	_gameClear = _gameOver = _goldenKeyGet = _bling = _boxOnLand[0] = _boxOnLand[1] =  false;
	_gameStart = _isWiggle = _isActive = true;

	//백그라운드 이미지 초기화
	IMAGEMANAGER->addImage("bg_arrowhead", "img/CB_bg_arrowhead_01.bmp", 144, 144);
	IMAGEMANAGER->addImage("map_stage4", "img/CB_map_stage4_01.bmp", 2560, 818, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("map_stage4_frame", "img/CB_map_stage4_frame_01.bmp", 2560, 818, true, RGB(255, 0, 255));

	_goldenKey[IDLE].frameX = 11;
	_goldenKey[IDLE].img = IMAGEMANAGER->addFrameImage("goldenKeyIdle", "img/CB_obj_goldenKey_Idle_sprite_01.bmp", 627, 57, _goldenKey[IDLE].frameX, 1, true, RGB(255, 0, 255));
	_goldenKey[IDLE].img->setX(618); _goldenKey[IDLE].img->setY(535);
	_goldenKey[1].frameX = 3;
	_goldenKey[1].img = IMAGEMANAGER->addFrameImage("goldenKeyGet", "img/CB_obj_goldenKey_get_sprite_01.bmp", 171, 54, _goldenKey[1].frameX, 1, true, RGB(255, 0, 255));
	_goldenKey[1].img->setX(618); _goldenKey[1].img->setY(535);

	for (int i = 0; i < 4; i++)
	{
		_river[i].img = new image;
		_river[i].frameX = 3;
		_river[i].img->init("img/CB_obj_water_sprite_01.bmp", 864, 144, _river[i].frameX, 1, true, RGB(255, 0, 255));
		_river[i].img->setY(670);
	}	
	_river[0].img->setX(380);
	_river[1].img->setX(_river[0].img->getX() + 288);
	_river[2].img->setX(1400);
	_river[3].img->setX(_river[2].img->getX() + 288);

	for (int i = 0; i < 2; i++)
	{
		_safe[i].img = new image;
		_safe[i].frameX = 12;
		_safe[i].img->init("img/CB_obj_safe_sprite_01.bmp", 852, 71, _safe[i].frameX, 1, true, RGB(255, 0, 255));
		_safe[i].img->setX(1177); _safe[i].img->setY((i * 71) + 491);
		_box[i].img = new image;
		_box[i].img->init("img/CB_obj_box_sprite_01.bmp", 70, 70, true, RGB(255, 0, 255));
		_box[i].img->setX((i * 498) + 360); _box[i].img->setY(280);
		_box[i].rc[RIGHT] = RectMake(_box[i].img->boundingBox().right - 15, _box[i].img->boundingBox().top + 15, 15, _box[i].img->getHeight() - 15);
		_box[i].rc[LEFT] = RectMake(_box[i].img->getX(), _box[i].img->boundingBox().top + 15, 15, _box[i].img->getHeight() - 15);
		_box[i].rc[UP] = RectMake(_box[i].img->getX(), _box[i].img->boundingBox().top, _box[i].img->getWidth(), 15);
		_boxGravity[i] = 0.0f;
		_boxSpeed[i] = 12.0f;
	}

	IMAGEMANAGER->addImage("whiteScreen", "img/CB_fx_whiteScreen_01.bmp", 1280, 720);

	_collider[0] = RectMake(538 , 476, 213, 15);	//천장
	_collider[1] = RectMake(113 , 261, 69, 15);
	_collider[2] = RectMake(182 , 190, 142, 15);
	_collider[3] = RectMake(324 , 261, 142, 15);
	_collider[4] = RectMake(466 , 190, 71, 15);
	_collider[5] = RectMake(537 , 119, 215, 15);
	_collider[6] = RectMake(752 , 190, 71, 15);
	_collider[7] = RectMake(823 , 261, 213, 15);
	_collider[8] = RectMake(1036, 476, 280, 15);
	_collider[9] = RectMake(1389, 334, 426, 15);
	_collider[10] = RectMake(1815, 264, 427, 15);
	_collider[11] = RectMake(341 , 405, 609, 15);
	_collider[12] = RectMake(167, 506, 15, 142);	//왼
	_collider[13] = RectMake(167, 190, 15, 71);
	_collider[14] = RectMake(380, 648, 15, 170);
	_collider[15] = RectMake(664, 626, 15, 7);
	_collider[16] = RectMake(950, 626, 15, 7);
	_collider[17] = RectMake(380, 626, 15, 7);
	_collider[18] = RectMake(451, 190, 15, 71);
	_collider[19] = RectMake(522, 119, 15, 71);
	_collider[20] = RectMake(1302, 405, 15, 71);
	_collider[21] = RectMake(1374, 334, 15, 71);
	_collider[22] = RectMake(1800, 264, 15, 70);
	_collider[23] = RectMake(736, 648, 15, 170);
	_collider[24] = RectMake(1445, 648, 15, 170);
	_collider[25] = RectMake(736, 342,  15, 134);
	_collider[26] = RectMake(950, 365, 15, 55);
	_collider[27] = RectMake(98, 261, 15, 245);
	_collider[28] = RectMake(608, 626 , 15, 7);		//오
	_collider[29] = RectMake(894, 626 , 15, 7);
	_collider[30] = RectMake(324, 626 , 15, 7);
	_collider[31] = RectMake(324, 190 , 15, 71);
	_collider[32] = RectMake(752, 119 , 15, 71);
	_collider[33] = RectMake(823, 190 , 15, 71);
	_collider[34] = RectMake(1036, 261, 15, 214);
	_collider[35] = RectMake(2242, 264, 15, 228);
	_collider[36] = RectMake(2029, 507, 15, 55);
	_collider[37] = RectMake(1886, 577, 15, 241);
	_collider[38] = RectMake(894 , 648, 15, 170);
	_collider[39] = RectMake(538 , 648, 15, 170);
	_collider[40] = RectMake(538 , 342, 15, 134);
	_collider[41] = RectMake(326 , 365, 15, 55);
	_collider[42] = RectMake(326 , 350, 639, 15);	//바닥
	_collider[43] = RectMake(538, 327, 213, 15);	//init 지점
	_collider[44] = RectMake(538 , 633, 213, 15);
	_collider[45] = RectMake(182 , 633, 213, 15);
	_collider[46] = RectMake(608 , 611, 71, 15);
	_collider[47] = RectMake(113 , 491, 69, 15);
	_collider[48] = RectMake(113 , 407, 69, 15);
	_collider[49] = RectMake(894 , 611, 71, 15);
	_collider[50] = RectMake(324 , 611, 71, 15);
	_collider[51] = RectMake(2029, 492, 228, 15);
	_collider[52] = RectMake(1886, 562, 157, 15);
	_collider[53] = RectMake(894, 633, 566, 15);
	//_collider[54] = RectMake(2118, 372, 566, 15);

	_wormHole = RectMakeCenter(2136, 390, 35, 35);

	return S_OK;
}

void stage4::release(void)
{
	_player->release();
	SAFE_DELETE(_player);
	for (int i = 0; i < 4; i++)
		SAFE_DELETE(_river[i].img);
	for (int i = 0; i < 2; i++)
	{
		SAFE_DELETE(_safe[i].img);
		SAFE_DELETE(_box[i].img);
	}
}

void stage4::update(void)
{
	_player->update();

	_loopY -= -sinf(-90.0f) * 1.01f;

	// cam process
	if (_player->getCamX() <= 0)
	{
		_player->setCamX(0);
	}
	else if (_player->getCamX() + WINSIZEX >= 2560)
	{
		_player->setCamX(2560 - WINSIZEX);
	}
	if (_player->getCamY() <= 0)
	{
		_player->setCamY(0);
	}
	else if (_player->getCamY() + WINSIZEY >= 818)
	{
		_player->setCamY(818 - WINSIZEY);
	}

	//물 찰랑
	_count++;
	if (_count % 5 == 0)
	{
		_riverIndex++;
		if (_riverIndex > _river[0].frameX)
		{
			_riverIndex = 0;
		}
		for (int i = 0; i < 4; i++)
			_river[i].img->setFrameX(_riverIndex);

		//열쇠 둥실
		_goldenKeyIndex++;
		if (_goldenKeyIndex > _goldenKey[_player->getGoldenKeyGet()].frameX)
		{
			_goldenKeyIndex = 0;
		}
		_goldenKey[_player->getGoldenKeyGet()].img->setFrameX(_goldenKeyIndex);

		//금고반짝
		for (int i = 0; i < 2; i++)
		{
			_safeIndex++;
			if (_safeIndex > _safe[i].frameX)
			{
				_safeIndex = 0;
			}
			_safe[i].img->setFrameX(_safeIndex);
		}
	}

	collide();
	screenBling();
	boxMoveCollide();
}

void stage4::render(void)
{
	RECT rc = RectMake(0, 0, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->loopRender("bg_arrowhead", getMemDC(), &rc, _loopX, _loopY);
	_player->getShadowImg(_player->getState())->frameRender(getMemDC(), _player->getX() - 13 - _player->getCamX(), _player->getY() - _player->getCamY());
	IMAGEMANAGER->render("map_stage4", getMemDC(), 0, 0, _player->getCamX(), _player->getCamY(), WINSIZEX, WINSIZEY);
	if (!_player->getGoldenKeyGet())
	{
		_goldenKey[_player->getGoldenKeyGet()].img->frameRender(getMemDC(), _goldenKey[_player->getGoldenKeyGet()].img->getX() - _player->getCamX(), _goldenKey[_player->getGoldenKeyGet()].img->getY() - _player->getCamY());
		_safe[0].img->frameRender(getMemDC(), _safe[0].img->getX() - _player->getCamX(), _safe[0].img->getY() - _player->getCamY());
		_safe[1].img->frameRender(getMemDC(), _safe[1].img->getX() - _player->getCamX(), _safe[1].img->getY() - _player->getCamY());
	}
	for (int i = 0; i < 4; i++)
		_river[i].img->frameRender(getMemDC(), _river[i].img->getX() - _player->getCamX(), _river[i].img->getY() - _player->getCamY());
	_box[0].img->render(getMemDC(), _box[0].img->getX() - _player->getCamX(), _box[0].img->getY() - _player->getCamY());
	_box[1].img->render(getMemDC(), _box[1].img->getX() - _player->getCamX(), _box[1].img->getY() - _player->getCamY());
	IMAGEMANAGER->render("map_stage4_frame", getMemDC(), 0, 0, _player->getCamX(), _player->getCamY(), WINSIZEX, WINSIZEY);
	_player->render();

	if (_player->getGoldenKeyGet() || _gameClear || _gameOver)
		IMAGEMANAGER->alphaRender("whiteScreen", getMemDC(), _whiteAlpha);

	if (KEYMANAGER->isToggleKey(VK_RETURN))
	{
		for (int i = 0; i < MAXCOLLIDER; i++)
			Rectangle(getMemDC(), _collider[i].left - _player->getCamX(), _collider[i].top - _player->getCamY(), _collider[i].right - _player->getCamX(), _collider[i].bottom - _player->getCamY());
		Rectangle(getMemDC(), _player->getRect().left - _player->getCamX(), _player->getRect().top - _player->getCamY(), _player->getRect().right - _player->getCamX(), _player->getRect().bottom - _player->getCamY());
		Rectangle(getMemDC(), _wormHole.left - _player->getCamX(), _wormHole.top - _player->getCamY(), _wormHole.right - _player->getCamX(), _wormHole.bottom - _player->getCamY());
		for (int i = 0; i < 4; i++)
			Rectangle(getMemDC(), _river[i].img->boundingBoxWithFrame().left - _player->getCamX(), _river[i].img->boundingBoxWithFrame().top - _player->getCamY(), _river[i].img->boundingBoxWithFrame().right - _player->getCamX(), _river[i].img->boundingBoxWithFrame().bottom - _player->getCamY());
		Rectangle(getMemDC(), _goldenKey[_player->getGoldenKeyGet()].img->boundingBoxWithFrame().left - _player->getCamX(), _goldenKey[_player->getGoldenKeyGet()].img->boundingBoxWithFrame().top - _player->getCamY(), _goldenKey[_player->getGoldenKeyGet()].img->boundingBoxWithFrame().right - _player->getCamX(), _goldenKey[_player->getGoldenKeyGet()].img->boundingBoxWithFrame().bottom - _player->getCamY());
		for (int i = 0; i < 2; i++)
		{
			Rectangle(getMemDC(), _safe[i].img->boundingBoxWithFrame().left - _player->getCamX(), _safe[i].img->boundingBoxWithFrame().top - _player->getCamY(), _safe[i].img->boundingBoxWithFrame().right - _player->getCamX(), _safe[i].img->boundingBoxWithFrame().bottom - _player->getCamY());
			Rectangle(getMemDC(), _box[i].img->boundingBox().left - _player->getCamX(), _box[i].img->boundingBox().top - _player->getCamY(), _box[i].img->boundingBox().right - _player->getCamX(), _box[i].img->boundingBox().bottom - _player->getCamY());
			Rectangle(getMemDC(), _box[i].rc[LEFT].left - _player->getCamX(), _box[i].rc[LEFT].top - _player->getCamY(), _box[i].rc[LEFT].right - _player->getCamX(), _box[i].rc[LEFT].bottom - _player->getCamY());
			Rectangle(getMemDC(), _box[i].rc[RIGHT].left - _player->getCamX(), _box[i].rc[RIGHT].top - _player->getCamY(), _box[i].rc[RIGHT].right - _player->getCamX(), _box[i].rc[RIGHT].bottom - _player->getCamY());
			Rectangle(getMemDC(), _box[i].rc[UP].left - _player->getCamX(), _box[i].rc[UP].top - _player->getCamY(), _box[i].rc[UP].right - _player->getCamX(), _box[i].rc[UP].bottom - _player->getCamY());
		}
	}

}

void stage4::collide()
{
	RECT temprc;

	if (_isActive)
	{
		if (_player->getY() + (_player->getRect().bottom - _player->getRect().top) >= _collider[43].top)
		{
			cameraWiggle();
		}

		for (int i = 0; i < MAXCOLLIDER; i++)
		{
			for (int j = 0; j < 2; j++)	//상자
			{
				if (IntersectRect(&temprc, &_collider[i], &_player->getRect()))
				{
					if (i <= 11)	//천장
					{
						_player->setY(_collider[i].bottom);
					}
					else if (12 <= i && i <= 27)	//왼쪽 벽
					{
						_player->setX(_collider[i].right);
					}
					else if (28 <= i && i <= 41)	//오른쪽 벽
					{
						_player->setX(_collider[i].left - (_player->getRect().right - _player->getRect().left));
					}
					else
					{
						//플레이어 점프했을 때 충돌처리
						if (-sinf(_player->getAngle()) * _player->getSpeed() * _player->getIsJump() + _player->getGravity() > 0 &&
							_player->getRect().bottom - (-sinf(_player->getAngle()) * _player->getSpeed() * _player->getIsJump() + _player->getGravity()) > 0 &&
							_player->getRect().right > _collider[i].left &&	_player->getRect().left < _collider[i].right && _player->getRect().bottom < _collider[i].bottom)// && _player->getY() - _oldY > 0)
						{
							_player->setOnLand(true);
							_player->setEffectX(_player->getX());
							_player->setEffectY(_collider[i].top);
							_player->setY(_collider[i].top - (_player->getRect().bottom - _player->getRect().top) + 1);
							_player->setIsJump(false);
							if (_player->getState() != WALK)
								_player->setState(IDLE);
							_player->setGravity(0.0f);
							_player->setSpeed(0.0f);
						}
					}
				}
			}
		}

		//입수했을 때
		for (int i = 0; i < 4; i++)
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

		for (int i = 0; i < 2; i++)
		{
			//금고와 부딪혔을 때
			if (IntersectRect(&temprc, &_player->getRect(), &_safe[i].img->boundingBox()) && !_player->getGoldenKeyGet())
				_player->setX(_safe[i].img->boundingBox().left - (_player->getRect().right - _player->getRect().left));
		}
	}

	//열쇠와 부딪혔을 때
	if (IntersectRect(&temprc, &_player->getRect(), &_goldenKey[_player->getGoldenKeyGet()].img->boundingBoxWithFrame()) && !_player->getGoldenKeyGet())
	{
		_player->setEffectX(_goldenKey[_player->getGoldenKeyGet()].img->getX() + _goldenKey[_player->getGoldenKeyGet()].img->getFrameWidth() / 2);
		_player->setEffectY(_goldenKey[_player->getGoldenKeyGet()].img->getY() + _goldenKey[_player->getGoldenKeyGet()].img->getFrameHeight() / 2);
		_player->setGoldenKeyGet(true);
		_bling = false;
	}

	//웜홀과 부딪혔을 때
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
void stage4::cameraWiggle()
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
			_player->setCamX(_player->getCamX() + RND->getInt(20) - 20);
			_player->setCamY(_player->getCamY() + RND->getInt(30));
		}
	}
}

void stage4::screenBling()
{
	//화면 반짝
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

void stage4::boxMoveCollide()
{
	RECT temprc, temprc2;

	for (int j = 0; j < 2; j++)
	{
		_boxGravity[j] += 0.55f;
		_box[j].img->setY(_box[j].img->getY() + _boxGravity[j]);

		for (int i = 0; i < MAXCOLLIDER; i++)
		{
			if (IntersectRect(&temprc, &_collider[i], &_box[j].img->boundingBox()))
			{
				if (i <= 11)	//천장
				{
					_box[j].img->setY(_collider[i].bottom);
				}
				else if (12 <= i && i <= 27)	//왼쪽 벽
				{
					_box[j].img->setX(_collider[i].right);
					if (IntersectRect(&temprc2, &_box[i].img->boundingBox(), &_player->getRect()))
					{
						
					}
				}
				else if (28 <= i && i <= 41)	//오른쪽 벽
				{
					_box[j].img->setX(_collider[i].left - (_box[j].img->getWidth()));
				}
				else
				{
					//상자 떨어졌을 때 충돌
					if (_boxGravity > 0 && _box[j].img->boundingBox().bottom - _boxGravity[j] > 0 && _box[j].img->boundingBox().right > _collider[i].left &&
						_box[j].img->boundingBox().left < _collider[i].right && _box[j].img->boundingBox().bottom < _collider[i].bottom)
					{
						if (j == 0)
							_player->setBoxOnLand0(true);
						else
							_player->setBoxOnLand1(true);

						_player->setEffectX(_box[j].img->getX());
						_player->setEffectY(_collider[i].top);
						_box[j].img->setY(_collider[i].top - _box[j].img->getHeight() + 1);
						_boxGravity[j] = 0.0f;
						_boxSpeed[j] = 0.0f;
						//_isWiggle = true;
						//cameraWiggle();
					}
				}
			}
			else
			{
				if (j == 0)
					_player->setBoxOnLand0(false);
				else
					_player->setBoxOnLand1(false);

				_boxSpeed[j] = 12.0f;
			}
		}
		//상자 밀기
		if (IntersectRect(&temprc, &_player->getRect(), &_box[j].rc[LEFT]))
		{
			_box[j].img->setX(_player->getRect().right);

			//플레이어가 밀고 있는데 금고와 부딪혔을 때
			if (IntersectRect(&temprc2, &_box[j].img->boundingBox(), &_safe[1].img->boundingBox()) && !_player->getGoldenKeyGet())
			{
				_box[j].img->setX(_safe[1].img->boundingBox().left - _box[j].img->getWidth());
				_player->setX(_box[j].img->boundingBox().left - (_player->getRect().right - _player->getRect().left));
			}

		}
		else if (IntersectRect(&temprc, &_player->getRect(), &_box[j].rc[RIGHT]))
		{
			_box[j].img->setX(_player->getRect().left - _box[j].img->getWidth());
		}
		//플레이어가 상자 위에 안착했을 때
		else if (IntersectRect(&temprc, &_player->getRect(), &_box[j].rc[UP]) && -sinf(_player->getAngle()) * _player->getSpeed() * _player->getIsJump() + _player->getGravity() > 0 &&
			_player->getRect().bottom - (-sinf(_player->getAngle()) * _player->getSpeed() * _player->getIsJump() + _player->getGravity()) > 0 &&
			_player->getRect().right > _box[j].rc[UP].left &&	_player->getRect().left < _box[j].rc[UP].right && _player->getRect().bottom < _box[j].rc[UP].bottom)
		{
			_player->setOnLand(true);
			_player->setEffectX(_player->getX());
			_player->setEffectY(_box[j].rc[UP].top);
			_player->setY(_box[j].rc[UP].top - (_player->getRect().bottom - _player->getRect().top) + 1);
			_player->setIsJump(false);
			_player->setState(IDLE);
			_player->setGravity(0.0f);
			_player->setSpeed(0.0f);
		}
		
		_box[j].rc[RIGHT] = RectMake(_box[j].img->boundingBox().right - 15, _box[j].img->boundingBox().top + 15, 15, _box[j].img->getHeight());
		_box[j].rc[LEFT] = RectMake(_box[j].img->getX(), _box[j].img->boundingBox().top + 15, 15, _box[j].img->getHeight());
		_box[j].rc[UP] = RectMake(_box[j].img->getX(), _box[j].img->boundingBox().top, _box[j].img->getWidth(), 15);
	}
}
