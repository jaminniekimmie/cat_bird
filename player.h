#pragma once
#include "gameNode.h"

#define MAXSTATE 8

enum playerState
{
	IDLE = 0,
	WALK,
	FLY,
	JUMP,
	FALL,
	LAND,
	FAIL,
	TRANS
};
enum direction
{
	RIGHT = 0,
	LEFT,
	UP,
	DOWN
};
struct tagImage
{
	image* img;
	float frameX, frameY;
	float x, y;
	RECT rc[4];
};
class player : public gameNode
{
private:
	int		_state;
	int		_gameCount;
	int		_index, _count, _effectCount;
	int		_smokeIndex, _featherIndex, _bubbleIndex;
	int		_dir;
	int		_randNo;
	float	_effectX, _effectY;
	float	_x, _y;
	float	_camX, _camY;
	float	_speed;
	float	_angle;
	float	_gravity;
	bool	_isJump;
	bool	_isFly;
	bool	_onLand;
	bool	_crownGet, _goldenKeyGet;
	bool	_gameStart;
	bool	_rightKey, _leftKey, _upKey;
	bool	_onBench;
	bool	_boxOnLand[2];
	RECT	_rc;
	RECT	_catCollideRc[4];
	tagImage	_cat[MAXSTATE];
	tagImage	_shadow[MAXSTATE];
	tagImage	_smoke[3];
	tagImage	_feather[3];
	tagImage	_bubbleWhite;
	image*		_keyUp[2];
	image*		_keyLeft[2];
	image*		_keyRight[2];

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
	image* getShadowImg(int state) { return _shadow[state].img; }
	void setShadowImg(tagImage img, int state) { _shadow[state].img = img.img; }
	float getCamX() { return _camX; }
	float getCamY() { return _camY; }
	void setCamX(float camX) { _camX = camX; }
	void setCamY(float camY) { _camY = camY; }
	float getEffectX() { return _effectX; }
	float getEffectY() { return _effectY; }
	void setEffectX(float effectX) { _effectX = effectX; }
	void setEffectY(float effectY) { _effectY = effectY; }
	int getState() { return _state; }
	void setState(int state) { _state = state; }
	int getDir() { return _dir; }
	void setDir(int dir) { _dir = dir; }
	float getGravity() { return _gravity; }
	void setGravity(float gravity) { _gravity = gravity; }
	float getSpeed() { return _speed; }
	void setSpeed(float speed) { _speed = speed; }
	float getAngle() { return _angle; }
	void setAngle(float angle) { _angle = angle; }
	bool getIsJump() { return _isJump; }
	void setIsJump(bool isJump) { _isJump = isJump; }
	bool getIsFly() { return _isFly; }
	void setIsFly(bool isFly) { _isFly = isFly; }
	bool getCrownGet() { return _crownGet; }
	void setCrownGet(bool crownGet) { _crownGet = crownGet; }
	bool getGoldenKeyGet() { return _goldenKeyGet; }
	void setGoldenKeyGet(bool goldenKeyGet) { _goldenKeyGet = goldenKeyGet; }
	bool getOnLand() { return _onLand; }
	void setOnLand(bool onLand) { _onLand = onLand; }
	bool getOnBench() { return _onBench; }
	void setOnBench(bool onBench) { _onBench = onBench; }
	bool getBoxOnLand0() { return _boxOnLand[0]; }
	void setBoxOnLand0(bool boxOnLand) { _boxOnLand[0] = boxOnLand; }
	bool getBoxOnLand1() { return _boxOnLand[1]; }
	void setBoxOnLand1(bool boxOnLand) { _boxOnLand[1] = boxOnLand; }
	void characterAnimLoop(int state);
	void effectAnim();

	player() {}
	~player() {}
};

