#pragma once
#include <iostream>
#include <string>

class GameState
{
public:
	
	virtual ~GameState() = 0 {};

	virtual bool OnEnter() = 0;
	virtual GameState* Update() = 0;
	virtual bool Render() = 0;
	virtual void OnExit() = 0;

private:
	
};

