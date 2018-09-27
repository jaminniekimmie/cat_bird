#pragma once
#include "stage.h"
#include "player.h"
#include "smallCreatures.h"

#define MAXCOLLIDER 25

class stage1 :	public stage
{
private:
	player *	_player;
	smallCreatures * _smlCr;
	tagImage	_crown;
	float		_x, _y;
	float		_wiggleX, _wiggleY;
	float		_loopX, _loopY;
	int			_randNo;
	int			_count, _index;
	int			_crownIndex;
	int			_state, _dir;
	int			_clearCount, _gameCount;
	int			_whiteAlpha;
	bool		_isActive;
	bool		_isWiggle;
	bool		_crownGet;
	bool		_bling;
	RECT		_rc;
	RECT		_collider[MAXCOLLIDER];
	RECT		_wormHole;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	float getX() { return _x; }
	float getY() { return _y; }
	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }
	RECT getRect() { return _rc; }
	void setRect(RECT rc) { _rc = rc; }

	void collide();
	void cameraWiggle();
	void screenBling();

	stage1() {}
	~stage1() {}
};

