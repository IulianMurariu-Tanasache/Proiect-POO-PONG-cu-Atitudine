#pragma once
#include"Ball.h"

class PowerUps : public Object 
{
public:
	PowerUps(const char* file = "", SDL_Rect src = { 0,0,0,0 });
	virtual void doSomething(Ball& b) {};
	virtual void revert(Ball& b) {};
	bool collisionDetect(Ball& b);
};

class invertPower : PowerUps
{
public:
	invertPower(const char* file = "", SDL_Rect src = { 0,0,0,0 }) :PowerUps(file, src) {};
	void doSomething(Ball& b);
	void revert(Ball& b);
};

class fastPower : PowerUps
{
public:
	fastPower(const char* file = "", SDL_Rect src = { 0,0,0,0 }) :PowerUps(file, src) {};
	void doSomething(Ball& b);
	void revert(Ball& b);
};

class slowPower : PowerUps
{
public:
	slowPower(const char* file = "", SDL_Rect src = { 0,0,0,0 }) :PowerUps(file, src) {};
	void doSomething(Ball& b);
	void revert(Ball& b);
};

class bigPower : PowerUps
{
public:
	bigPower(const char* file = "", SDL_Rect src = { 0,0,0,0 }) :PowerUps(file, src) {};
	void doSomething(Ball& b);
	void revert(Ball& b);
};

class smallPower : PowerUps
{
public:
	smallPower(const char* file = "", SDL_Rect src = { 0,0,0,0 }) :PowerUps(file, src) {};
	void doSomething(Ball& b);
	void revert(Ball& b);
};

