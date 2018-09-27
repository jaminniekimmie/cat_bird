#pragma once
#include "stage.h"
#include "player.h"

#define MAXCOLLIDER 42

class stage3 : public stage
{
private:
	player *	_player;
	tagImage	_goldenKey[2];
	tagImage	_river[2];
	tagImage 	_dot[12];
	tagImage 	_bench[4];
	tagImage	_crown;
	image *		_benchPivot;
	int			_randNo;
	float		_x, _y;
	float		_wiggleX, _wiggleY;
	float		_loopX, _loopY;
	float		_benchAngle;
	float		oldX, oldY;
	float		tempX;
	int			_count, _index;
	int			_riverIndex;
	int			_crownIndex;
	int			_goldenKeyIndex;
	int			_state, _dir;
	int			_clearCount, _gameCount;
	int			_whiteAlpha;
	bool		_isActive;
	bool		_isWiggle;
	bool		_goldenKeyGet;
	bool		_bling;
	RECT		_rc;
	RECT		_collider[MAXCOLLIDER];
	RECT		_wormHole;
	RECT		_teeth[2];

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
	void benchRotate();

	stage3() {}
	~stage3() {}
};

