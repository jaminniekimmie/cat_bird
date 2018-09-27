#pragma once
#include "gameNode.h"
#include "player.h"
#include "openingScene.h"
#include "titlePage.h"
#include "stage1.h"
#include "stage2.h"
#include "stage3.h"
#include "stage4.h"

enum inOrOut
{
	TRANS_IN = 0,
	TRANS_OUT
};

class mainGame : public gameNode
{
private:
	player *		_player;	//플레이어 클래스 선언
	stage *			_currentScene;
	titlePage *		_titlePage;
	openingScene *	_openingScene;
	stage1 *		_stage1;
	stage2 *		_stage2;
	stage3 *		_stage3;
	stage4 *		_stage4;
	tagImage		_transition[2];
	tagImage		_score[10];
	int				_scoreNo;
	int				_randNo;
	int				_loopX, _loopY;
	int				_gameCount;
	int				_count, _index;
	int				_inOrOut;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void transitionAnim();

	mainGame() {}
	~mainGame() {}
};

