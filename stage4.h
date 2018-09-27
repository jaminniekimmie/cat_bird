#pragma once
#include "stage.h"
#include "player.h"

#define MAXCOLLIDER 55

class stage4 : public stage
{
private:
	player *	 _player;
	tagImage	_goldenKey[2];
	tagImage	_river[4];
	tagImage	_safe[2];
	tagImage	_box[2];
	int			_randNo;
	float		_x, _y;
	float		_wiggleX, _wiggleY;
	float		_loopX, _loopY;
	float		_benchAngle;
	float		oldX, oldY;
	float		tempX, tempY;
	float		_boxGravity[2], _boxSpeed[2];
	int			_count, _index;
	int			_safeIndex;
	int			_riverIndex;
	int			_goldenKeyIndex;
	int			_state, _dir;
	int			_clearCount, _gameCount;
	int			_whiteAlpha;
	bool		_isActive;
	bool		_isWiggle;
	bool		_goldenKeyGet;
	bool		_bling;
	bool		_boxOnLand[2];
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
	void boxMoveCollide();

	stage4() {}
	~stage4() {}
};

