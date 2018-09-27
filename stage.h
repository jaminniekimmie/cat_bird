#pragma once
#include "gameNode.h"
class stage :
	public gameNode
{
protected:
	bool _gameStart, _gameClear, _gameOver;

public:
	stage();
	~stage();

	bool getGameStart() { return _gameStart; }
	void setGameStart(bool gameStart) { _gameStart = gameStart; }
	bool getGameClear() { return _gameClear; }
	void setGameClear(bool gameClear) { _gameClear = gameClear; }
	bool getGameOver() { return _gameOver; }
	void setGameOver(bool gameOver) { _gameOver = gameOver; }
};

