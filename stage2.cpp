#include "stdafx.h"
#include "stage2.h"

HRESULT stage2::init(void)
{
	_player = new player;
	_player->init();
	_player->setX(285);
	_player->setY(550);

	_smlCr = new smallCreatures;
	_smlCr->init();

	_randNo = -1;
	_loopX = _loopY = 0;
	_wiggleX = _wiggleY = 0;
	_count = _index = _clearCount = _gameCount = 0;
	_state = IDLE;
	_whiteAlpha = 0;
	_gameClear = _gameOver = _bling = false;
	_gameStart = _isWiggle = _isActive = true;

	//백그라운드 이미지 초기화
	IMAGEMANAGER->addImage("bg_arrowhead", "img/CB_bg_arrowhead_01.bmp", 144, 144);
	IMAGEMANAGER->addImage("map_stage2", "img/CB_map_stage2_01.bmp", 1280, 1013, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("map_stage2_frame", "img/CB_map_stage2_frame_01.bmp", 1280, 1013, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("whiteScreen", "img/CB_fx_whiteScreen_01.bmp", 1280, 720);

	_collider[0] = RectMake(0, 0, 1280, 180);		// 천장
	_collider[1] = RectMake(0, 306, 212, 15);		// 왼 위 코너 아랫쪽
	_collider[2] = RectMake(1068, 306, 212, 15);	// 오 위 코너 아랫쪽
	_collider[3] = RectMake(0, 0, 141, 1013);		// 왼 벽
	_collider[4] = RectMake(197, 0, 15, 306);		// 왼 위 코너 오른쪽
	_collider[5] = RectMake(197, 550, 15, 56);		// 왼 중간 코너 오른쪽
	_collider[6] = RectMake(412, 621, 15, 392);		// 왼 절벽 벽
	_collider[7] = RectMake(1139, 0, 141, 1013);	// 오 벽
	_collider[8] = RectMake(1068, 0, 15, 306);		// 오 위 코너 왼쪽
	_collider[9] = RectMake(1068, 550, 15, 56);		// 오 중간 왼쪽
	_collider[10] = RectMake(853, 621, 15, 392);	// 오 절벽 벽
	_collider[11] = RectMake(0, 535, 212, 15);		// 왼 중간 코너 탑
	_collider[12] = RectMake(0, 606, 427, 15);		// 왼 아래 코너 탑	//init 지점
	_collider[13] = RectMake(1068, 535, 212, 15);	// 오 중간 코너 탑
	_collider[14] = RectMake(853, 606, 427, 15);	// 오 아래 코너 탑

	_wormHole = RectMakeCenter(943, 547, 35, 35);

	return S_OK;
}

void stage2::release(void)
{
	_player->release();
	SAFE_DELETE(_player);
}

void stage2::update(void)
{
	_player->update();

	_loopY -= -sinf(-90.0f) * 1.01f;

	// cam process
	if (_player->getCamX() <= 0)
	{
		_player->setCamX(0);
	}
	else if (_player->getCamX() + WINSIZEX >= 1280)
	{
		_player->setCamX(1280 - WINSIZEX);
	}
	if (_player->getCamY() <= 0)
	{
		_player->setCamY(0);
	}
	else if (_player->getCamY() + WINSIZEY >= 1013)
	{
		_player->setCamY(1013 - WINSIZEY);
	}

	collide();
	screenBling();
}

void stage2::render(void)
{
	RECT rc = RectMake(0, 0, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->loopRender("bg_arrowhead", getMemDC(), &rc, _loopX, _loopY);
	_player->getShadowImg(_player->getState())->frameRender(getMemDC(), _player->getX() - 13 - _player->getCamX(), _player->getY() - _player->getCamY());
	IMAGEMANAGER->render("map_stage2", getMemDC(), 0, 0, _player->getCamX(), _player->getCamY(), WINSIZEX, WINSIZEY);
	_player->render();
	//IMAGEMANAGER->render("map_stage2_frame", getMemDC(), 0, 0, _player->getCamX(), _player->getCamY(), WINSIZEX, WINSIZEY);
	if (_gameClear || _gameOver)
		IMAGEMANAGER->alphaRender("whiteScreen", getMemDC(), _whiteAlpha);

	if (KEYMANAGER->isToggleKey(VK_RETURN))
	{
		for (int i = 0; i < MAXCOLLIDER; i++)
			Rectangle(getMemDC(), _collider[i].left - _player->getCamX(), _collider[i].top - _player->getCamY(), _collider[i].right - _player->getCamX(), _collider[i].bottom - _player->getCamY());
		Rectangle(getMemDC(), _player->getRect().left - _player->getCamX(), _player->getRect().top - _player->getCamY(), _player->getRect().right - _player->getCamX(), _player->getRect().bottom - _player->getCamY());
		Rectangle(getMemDC(), _wormHole.left - _player->getCamX(), _wormHole.top - _player->getCamY(), _wormHole.right - _player->getCamX(), _wormHole.bottom - _player->getCamY());
	}
}

void stage2::collide()
{
	RECT temprc;
	if (_isActive)
	{
		if (_player->getY() + (_player->getRect().bottom - _player->getRect().top) >= _collider[12].top)
		{
			/*_player->setY(_collider[12].top - (_player->getRect().bottom - _player->getRect().top));
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
				if (i <= 2)	//천장
				{
					_player->setY(_collider[i].bottom);
				}
				else if (3 <= i && i <= 6)	//왼쪽 벽
				{
					_player->setX(_collider[i].right);
				}
				else if (7 <= i && i <= 10)	//오른쪽 벽
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

		//나락으로 떨어졌을 때
		if (_player->getRect().bottom >= 1013)
		{
			setGameOver(true);
			_player->setEffectX(_player->getX());
			_player->setEffectY(_player->getY());
			_player->setGravity(0.0f);
			_player->setAngle(90.0f);
			_player->setIsJump(true);
			_player->setSpeed(7.0f);
			_player->setState(FAIL);
			_isActive = false;
			_bling = false;
			_player->setY(1013 - (_player->getRect().bottom - _player->getRect().top));
		}
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

void stage2::cameraWiggle()
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

void stage2::screenBling()
{
	//화면 반짝
	if (_gameClear || _gameOver)
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
					//_bling = false;
				}
				else
				{
					_whiteAlpha -= 120 / 6;
				}
			}
		}
	}
}

