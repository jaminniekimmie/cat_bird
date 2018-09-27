#pragma once
#include "stage.h"
#include "player.h"

#define MAXCOLLIDER 42

class openingScene : public stage
{
private:
	
	float		_x, _y;
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

	openingScene() {}
	~openingScene() {}
};

