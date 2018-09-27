#pragma once
#include "gameNode.h"
#include "player.h"

#define MAXBIRDSTATE 3

class smallCreatures :	public gameNode
{
private:
	float		_greenX, _purpleX, _blueX;
	float		_greenY, _purpleY, _blueY;
	float		_wiggleX, _wiggleY;
	float		_oldX, _oldY;
	float		_loopX, _loopY;
	int			_countGreen, _countPurple, _countBlue;
	int			_indexGreen, _indexPurple, _indexBlue;
	int			_stateGreen, _statePurple, _stateBlue;
	int			_dirGreen, _dirPurple, _dirBlue;
	RECT		_rc;
	tagImage	_smlBird_green[MAXBIRDSTATE];
	tagImage	_smlBird_purple[MAXBIRDSTATE];
	tagImage	_smlBird_blue[MAXBIRDSTATE];
public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	float getGreenX() { return _greenX; }
	float getGreenY() { return _greenY; }
	float getPurpleX() { return _purpleX; }
	float getPurpleY() { return _purpleY; }
	float getBlueX() { return _blueX; }
	float getBlueY() { return _blueY; }
	void setGreenX(float greenX) { _greenX = greenX; }
	void setGreenY(float greenY) { _greenY = greenY; }
	void setPurpleX(float purpleX) { _purpleX = purpleX; }
	void setPurpleY(float purpleY) { _purpleY = purpleY; }
	void setBlueX(float blueX) { _blueX = blueX; }
	void setBlueY(float blueY) { _blueY = blueY; }

	RECT getRect() { return _rc; }
	void setRect(RECT rc) { _rc = rc; }

	image* getGreenBirdImg(int state) { return _smlBird_green[state].img; }
	void setGreenBirdImg(tagImage img, int state) { _smlBird_green[state].img = img.img; }
	image* getPurpleBirdImg(int state) { return _smlBird_purple[state].img; }
	void setPurpleBirdImg(tagImage img, int state) { _smlBird_purple[state].img = img.img; }
	image* getBlueBirdImg(int state) { return _smlBird_blue[state].img; }
	void setBlueBirdImg(tagImage img, int state) { _smlBird_blue[state].img = img.img; }

	int getGreenState() { return _stateGreen; }
	void setGreenState(int state) { _stateGreen = state; }
	int getPurpleState() { return _statePurple; }
	void setPurpleState(int state) { _statePurple = state; }
	int getBlueState() { return _stateBlue; }
	void setBlueState(int state) { _stateBlue = state; }

	void iconAnimLoop(tagImage * img, int state, int dir, int index, int count);
	
	smallCreatures() {}
	~smallCreatures() {}
};

