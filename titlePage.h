#pragma once
#include "stage.h"
#include "player.h"

#define MAXINIT 63
#define MAXCLICK 36

class titlePage :	public stage
{
	tagImage	_titleInit[MAXINIT];
	tagImage	_titleClick[MAXCLICK];
	int			_count;
	int			_initIndex, _clickIndex;
	float		_x, _y;
	bool		_isClick;
	RECT		_tapButton;
	RECT		_rc;
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
	titlePage() {}
	~titlePage() {}
};

