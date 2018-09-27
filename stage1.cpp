#include "stdafx.h"
#include "stage1.h"

HRESULT stage1::init(void)
{
	_player = new player;
	_player->init();
	_player->setX(WINSIZEX / 2 - 32);
	_player->setY(WINSIZEY - 20);

	_smlCr = new smallCreatures;
	_smlCr->init();

	_randNo = -1;
	_loopX = _loopY = 0;
	_wiggleX = _wiggleY = 0;
	_count = _index = 0;
	_crownIndex = 0;
	_clearCount = _gameCount = 0;
	_state = IDLE;
	_whiteAlpha = 0;
	_gameClear = _gameOver = _crownGet = _bling = false;
	_gameStart = _isWiggle = _isActive = true;
	
	//백그라운드 이미지 초기화
	IMAGEMANAGER->addImage("bg_arrowhead", "img/CB_bg_arrowhead_01.bmp", 144, 144);
	IMAGEMANAGER->addImage("map_stage1", "img/CB_map_stage1_01.bmp", 1280, 924, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("map_stage1_frame", "img/CB_map_stage1_frame_01.bmp", 1280, 924, true, RGB(255, 0, 255));
	
	_crown.frameX = 10;
	_crown.img = IMAGEMANAGER->addFrameImage("crown", "img/CB_crown_sprite_01.bmp", WINSIZEX / 2 - 32, 513, 600, 28, _crown.frameX, 1, true, RGB(255, 0, 255));
	_crown.img->setX(WINSIZEX / 2 - 32); _crown.img->setY(513);


	IMAGEMANAGER->addImage("whiteScreen", "img/CB_fx_whiteScreen_01.bmp", 1280, 720);

	_collider[0] = RectMake(0, 780, 1280, 116);		//바닥
	_collider[1] = RectMake(0, 0, 1280, 135);		//ceiling
	_collider[2] = RectMake(0, 194, 409, 15);		//왼 천장 위 가로
	_collider[3] = RectMake(867, 194, 411, 15);		//오 천장 위 가로
	_collider[4] = RectMake(0, 266, 338, 15);		//왼 천장 아래 가로
	_collider[5] = RectMake(938, 269, 340, 15);		//오 천장 아래 가로
	//_collider[6] = RectMake(568, 484, 141, 15);		//중 사각형 아래
	_collider[7] = RectMake(0, 0, 282, 916);		//벽 왼
	_collider[8] = RectMake(409, 0, 15, 209);		//왼 천장 위 세로
	_collider[9] = RectMake(338, 0, 15, 281);		//왼 천장 아래 세로
	_collider[10] = RectMake(409, 725, 15, 190);	//왼 계단 벽
	_collider[11] = RectMake(694, 367, 15, 117);	//중 사각형 오
	_collider[12] = RectMake(995, 0, 285, 916);		//벽 오
	_collider[13] = RectMake(852, 0, 15, 209);		//오 천장 위 세로
	_collider[14] = RectMake(923, 0, 15, 284);		//오 천장 아래 세로
	_collider[15] = RectMake(852, 725, 15, 190);	//오 계단 벽
	_collider[16] = RectMake(568, 367, 15, 117);	//중 사각형 왼
	_collider[17] = RectMake(0, 710, 424, 15);		//왼 아래 계단
	_collider[18] = RectMake(852, 710, 426, 15);	//오 아래 계단
	_collider[19] = RectMake(282, 531, 133, 15);	//왼 위 선반
	_collider[20] = RectMake(281, 622, 71, 15);		//왼 아래 선반
	_collider[21] = RectMake(860, 531, 133, 15);	//오 위 선반
	_collider[22] = RectMake(922, 622, 71, 15);		//오 아래 선반
	_collider[23] = RectMake(568, 352, 141, 15);	//중 사각형 위
	_collider[24] = RectMake(497, 439, 283, 14);	//중 선반
	
	_wormHole = RectMakeCenter(WINSIZEX / 2, 291, 35, 35);

	_smlCr->setPurpleX(WINSIZEX / 2);
	_smlCr->setPurpleY(_collider[0].top);
	_smlCr->setGreenX(WINSIZEX - 100);
	_smlCr->setGreenY(_collider[21].top);

	return S_OK;
}

void stage1::release(void)
{
	_player->release();
	SAFE_DELETE(_player);
	_smlCr->release();
	SAFE_DELETE(_smlCr);
}

void stage1::update(void)
{
	_player->update();
	_smlCr->update();

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
	else if (_player->getCamY() + WINSIZEY >= 924)
	{
		_player->setCamY(924 - WINSIZEY);
	}

	//왕관 둥실
	_count++;
	if (_count % 5 == 0)
	{
		_crownIndex++;
		if (_crownIndex > _crown.frameX)
		{
			_crownIndex = 0;
		}
		_crown.img->setFrameX(_crownIndex);
	}

	collide();
	screenBling();
}

void stage1::render(void)
{
	RECT rc = RectMake(0, 0, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->loopRender("bg_arrowhead", getMemDC(), &rc, _loopX, _loopY);	//배경
	_player->getShadowImg(_player->getState())->frameRender(getMemDC(), _player->getX() - 13 - _player->getCamX(), _player->getY() - _player->getCamY());	//그림자
	IMAGEMANAGER->render("map_stage1", getMemDC(), 0, 0, _player->getCamX(), _player->getCamY(), WINSIZEX, WINSIZEY);	//맵
	if(!_player->getCrownGet())
		IMAGEMANAGER->frameRender("crown", getMemDC(), _crown.img->getX() - _player->getCamX(), _crown.img->getY() - _player->getCamY());	//왕관
	IMAGEMANAGER->render("map_stage1_frame", getMemDC(), 0, 0, _player->getCamX(), _player->getCamY(), WINSIZEX, WINSIZEY);		//맵 프레임
	_player->render();	//플레이어
	_smlCr->getGreenBirdImg(_smlCr->getGreenState())->frameRender(getMemDC(), _smlCr->getGreenX() - _player->getCamX(), _smlCr->getGreenY() - _player->getCamY());
	_smlCr->getPurpleBirdImg(_smlCr->getPurpleState())->frameRender(getMemDC(), _smlCr->getPurpleX() - _player->getCamX(), _smlCr->getPurpleY() - _player->getCamY());
	if (_player->getCrownGet() || _gameClear)
		IMAGEMANAGER->alphaRender("whiteScreen", getMemDC(), _whiteAlpha);

	if (KEYMANAGER->isToggleKey(VK_RETURN))
	{
		for (int i = 0; i < MAXCOLLIDER; i++)
			Rectangle(getMemDC(), _collider[i].left - _player->getCamX(), _collider[i].top - _player->getCamY(), _collider[i].right - _player->getCamX(), _collider[i].bottom - _player->getCamY());
		Rectangle(getMemDC(), _player->getRect().left - _player->getCamX(), _player->getRect().top - _player->getCamY(), _player->getRect().right - _player->getCamX(), _player->getRect().bottom - _player->getCamY());
		Rectangle(getMemDC(), _wormHole.left - _player->getCamX(), _wormHole.top - _player->getCamY(), _wormHole.right - _player->getCamX(), _wormHole.bottom - _player->getCamY());
		Rectangle(getMemDC(), _crown.img->boundingBoxWithFrame().left + 15 - _player->getCamX(), _crown.img->boundingBoxWithFrame().top - _player->getCamY(), _crown.img->boundingBoxWithFrame().right - 5 - _player->getCamX(), _crown.img->boundingBoxWithFrame().bottom - _player->getCamY());
	}
}

void stage1::collide()
{
	RECT temprc;

	if (_player->getY() + (_player->getRect().bottom - _player->getRect().top) >= _collider[0].top)
	{
		if (_randNo == -1)
		{
			_randNo = 1;
			_player->setEffectX(_player->getX());
			_player->setEffectY(_collider[0].top);
		}
		_player->setOnLand(true);
		_player->setY(_collider[0].top - (_player->getRect().bottom - _player->getRect().top));
		_player->setGravity(0.0f);
		_player->setIsJump(false);
		_player->setSpeed(0.0f);
		_player->setState(IDLE);
		cameraWiggle();
	}
	else
	{
		_randNo = -1;
	}

	for (int i = 0; i < MAXCOLLIDER; i++)
	{
		if (IntersectRect(&temprc, &_collider[i], &_player->getRect()))
		{
			if (1 <= i && i <= 6)	//천장
			{
				_player->setY(_collider[i].bottom);
			}
			else if (7 <= i && i <= 11)	//왼쪽 벽
			{
				_player->setX(_collider[i].right);
			}
			else if (12 <= i && i <= 16)	//오른쪽 벽
			{
				_player->setX(_collider[i].left - (_player->getRect().right - _player->getRect().left));
			}
			else
			{
				if (-sinf(_player->getAngle()) * _player->getSpeed() * _player->getIsJump() + _player->getGravity() > 0 && 
					_player->getRect().bottom - (-sinf(_player->getAngle()) * _player->getSpeed() * _player->getIsJump() + _player->getGravity()) > 0  && 
					_player->getRect().right > _collider[i].left &&	_player->getRect().left < _collider[i].right && _player->getRect().bottom < _collider[i].bottom)// && _player->getY() - _oldY > 0)
				{
					if (_randNo == -1)
					{
						_randNo = 1;
						_player->setEffectX(_player->getX());
						_player->setEffectY(_collider[i].top);
					}
					_player->setOnLand(true);
					_player->setY(_collider[i].top - (_player->getRect().bottom - _player->getRect().top) + 1);
					_player->setIsJump(false);
					_player->setState(IDLE);
					_player->setGravity(0.0f);
					_player->setSpeed(0.0f);
				}
			}
		}
	}

	//왕관과 부딪혔을 때
	if (IntersectRect(&temprc, &_player->getRect(), &_crown.img->boundingBoxWithFrame()))
	{
		_player->setEffectX(_crown.img->getX() + _crown.img->getFrameWidth() / 2);
		_player->setEffectY(_crown.img->getY() + _crown.img->getFrameHeight() / 2);
		_player->setCrownGet(true);
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

void stage1::cameraWiggle()
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
			_player->setCamX(_player->getCamX() + RND->getInt(1));
			if (_gameClear)
				_player->setCamY(_player->getCamY() + RND->getInt(30));
			else
				_player->setCamY(_player->getCamY() + RND->getInt(30) - 30);
		}
	}
}

void stage1::screenBling()
{
	//화면 반짝
	if (_player->getCrownGet() || _gameClear)
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
