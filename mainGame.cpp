#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## 초기화 ## init(void)
//=============================================================
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);
	//이곳에서 초기화를 한다

	//_player = new player;
	//_player->init();

	_titlePage = new titlePage;
	//_titlePage->init();
	_openingScene = new openingScene;
	//_openingScene->init();
	_stage1 = new stage1;
	//_stage1->init();
	_stage2 = new stage2;
	//_stage2->init();
	_stage3 = new stage3;
	//_stage3->init();
	_stage4 = new stage4;
	//_stage4->init();

	IMAGEMANAGER->addImage("UI_topBar_stage1", "img/CB_UI_topBar_stage1_01.bmp", 1280, 67, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_topBar_stage2", "img/CB_UI_topBar_stage2_01.bmp", 1280, 67, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_topBar_stage3", "img/CB_UI_topBar_stage3_01.bmp", 1280, 67, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_topBar_stage4", "img/CB_UI_topBar_stage4_01.bmp", 1280, 67, true, RGB(255, 0, 255));

	_score[0].img = IMAGEMANAGER->addImage("no0", "img/CB_no_0_01.bmp", 23, 22, true, RGB(255, 0, 255));
	_score[1].img = IMAGEMANAGER->addImage("no1", "img/CB_no_1_01.bmp", 14, 22, true, RGB(255, 0, 255));
	_score[2].img = IMAGEMANAGER->addImage("no2", "img/CB_no_2_01.bmp", 23, 22, true, RGB(255, 0, 255));
	_score[3].img = IMAGEMANAGER->addImage("no3", "img/CB_no_3_01.bmp", 23, 22, true, RGB(255, 0, 255));
	_score[4].img = IMAGEMANAGER->addImage("no4", "img/CB_no_4_01.bmp", 23, 22, true, RGB(255, 0, 255));
	_score[5].img = IMAGEMANAGER->addImage("no5", "img/CB_no_5_01.bmp", 23, 22, true, RGB(255, 0, 255));
	_score[6].img = IMAGEMANAGER->addImage("no6", "img/CB_no_6_01.bmp", 23, 22, true, RGB(255, 0, 255));
	_score[7].img = IMAGEMANAGER->addImage("no7", "img/CB_no_7_01.bmp", 23, 22, true, RGB(255, 0, 255));
	_score[8].img = IMAGEMANAGER->addImage("no8", "img/CB_no_8_01.bmp", 23, 22, true, RGB(255, 0, 255));
	_score[9].img = IMAGEMANAGER->addImage("no9", "img/CB_no_9_01.bmp", 23, 22, true, RGB(255, 0, 255));
	
	_transition[0].frameY = 25;
	_transition[0].img = IMAGEMANAGER->addFrameImage("transition_diagonal", "img/CB_dia_transition_diagonal_sprite_01.bmp", 1280, 18000, 1, _transition[0].frameY, true, RGB(255, 0, 255));
	_transition[1].frameY = 21;
	_transition[1].img = IMAGEMANAGER->addFrameImage("transition_directional", "img/CB_dia_transition_directional_sprite_01.bmp", 1280, 15198, 1, _transition[1].frameY, true, RGB(255, 0, 255));

	_currentScene = _stage4;
	_currentScene->init();

	_inOrOut = TRANS_OUT;
	_loopX = _loopY = 0;
	_count = _index = _gameCount = 0;
	_scoreNo = 0;
	_randNo = -1;

	return S_OK;
}

//=============================================================
//	## 해제 ## release(void)
//=============================================================
void mainGame::release(void)
{
	gameNode::release();
	//init함수에서 동적할당 new를 사용했다면 이곳에서 delete 사용한다
	//이미지매니져 사용시 safe_delete 할 필요 없다

	_titlePage->release();
	SAFE_DELETE(_titlePage);
	_openingScene->release();
	SAFE_DELETE(_openingScene);
	_stage1->release();
	SAFE_DELETE(_stage1);
	_stage2->release();
	SAFE_DELETE(_stage2);
	_stage3->release();
	SAFE_DELETE(_stage3);
	_stage4->release();
	SAFE_DELETE(_stage4);

}

//=============================================================
//	## 업데이트 ## update(void)
//=============================================================
void mainGame::update(void)
{
	gameNode::update();
	//이곳에서 계산식, 키보드, 마우스등등 업데이트를 한다
	//간단하게 이곳에서 코딩한다고 생각하면 된다

	//현재씬만 업데이트
	_currentScene->update();
	if (_currentScene != _titlePage)
	{

		if (_currentScene->getGameStart())
		{
			_inOrOut = TRANS_OUT;
			transitionAnim();
			_gameCount++;
			if (_gameCount > 50)
			{
				_gameCount = 0;
				_currentScene->setGameStart(false);
			}
		}
		if (_currentScene->getGameOver())
		{
			_gameCount++;
			if (_gameCount > 50)
			{
				_inOrOut = TRANS_IN;
				transitionAnim();
			}
			if (_gameCount > 100)
			{
				_gameCount = 0;
				_scoreNo++;
				_currentScene->init();
			}
		}
		if (_currentScene->getGameClear())
		{
			_gameCount++;
			if (_gameCount > 50 && _currentScene != _titlePage)
			{
				_inOrOut = TRANS_IN;
				transitionAnim();
			}
			if (_gameCount > 100)
			{
				_gameCount = 0;
				if (_currentScene == _stage1)
				{
					_currentScene = _stage2;
					_currentScene->init();
				}
				else if (_currentScene == _stage2)
				{
					_currentScene = _stage3;
					_currentScene->init();
				}
				else if (_currentScene == _stage3)
				{
					_currentScene = _stage4;
					_currentScene->init();
				}
				else if (_currentScene == _stage4)
				{
					_currentScene = _titlePage;
					_currentScene->init();
				}
			}
		}
	}


	if (KEYMANAGER->isOnceKeyDown(VK_F9))
	{
		this->init();
	}
}

//=============================================================
//	## 렌더 ## render(void)
//=============================================================
void mainGame::render(void)
{
	//흰색 빈 비트맵(이것도 렌더에 그냥 둘것!!)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
//=============================================================

	//백그라운드 이미지 렌더
	_currentScene->render();
	if (_currentScene == _stage1)
	{
		IMAGEMANAGER->render("UI_topBar_stage1", getMemDC());
	}
	else if (_currentScene == _stage2)
	{
		IMAGEMANAGER->render("UI_topBar_stage2", getMemDC());
	}
	else if (_currentScene == _stage3)
	{
		IMAGEMANAGER->render("UI_topBar_stage3", getMemDC());
	}
	else if (_currentScene == _stage4)
	{
		IMAGEMANAGER->render("UI_topBar_stage4", getMemDC());
	}
	if (_currentScene != _titlePage)
	{
		//스코어
		if (_scoreNo >= 10)
		{
			_score[_scoreNo / 10].img->render(getMemDC(), 57, 14);
			_score[_scoreNo % 10].img->render(getMemDC(), 57 + _score[_scoreNo / 10].img->getWidth(), 14);
		}
		else
		{
			_score[_scoreNo].img->render(getMemDC(), 57, 14);
		}

		//트랜지션
		if (_currentScene->getGameStart() || _currentScene->getGameOver() || _currentScene->getGameClear())
		{
			if (_randNo == -1)
			{
				_randNo = RND->getInt(2);
				if (_inOrOut == TRANS_IN)
				{
					_index = 0;
				}
				else
				{
					_index = _transition[_randNo].frameY;
				}
			}
			_transition[_randNo].img->frameRender(getMemDC(), 0, 0);
		}
		else
			_randNo = -1;
	}

//=============================================================
	//백버퍼의 내용을 HDC에 그린다 (이것도 렌더에 그냥 둘것!!)
	this->getBackBuffer()->render(getHDC());
}

void mainGame::transitionAnim()
{
	if (_inOrOut == TRANS_OUT)
	{
		_count++;
		if (_count % 2 == 0)
		{
			if (_index <= 0)
			{
				_index = 0;
				//_currentScene->setGameStart(false);
			}
			else
				_index--;

			_transition[_randNo].img->setFrameY(_index);
		}
	}
	else	//IN
	{
		_count++;
		if (_count % 2 == 0)
		{
			if (_index >= _transition[_randNo].frameY)
			{
				_index = _transition[_randNo].frameY;
			}
			else
				_index++;

			_transition[_randNo].img->setFrameY(_index);
		}
	}
}
