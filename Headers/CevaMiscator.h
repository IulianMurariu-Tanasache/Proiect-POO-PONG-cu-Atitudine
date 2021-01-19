#pragma once
#include"Object.h"

class CevaMiscator : public Object
{
protected:
	int xSpeed;
	int ySpeed;
public:
	CevaMiscator(const char* file = "", SDL_Rect src = { 0,0,0,0 }, SDL_Rect dst = { 0,0,0,0 }) :Object(file, src, dst) { xSpeed = ySpeed = 0; };
	void setSpeed(int xs = 0, int ys = 0) { xSpeed = xs; ySpeed = ys; };
	int getXSpeed() { return xSpeed; };
	int getYSpeed() { return ySpeed; };
	virtual void update() = 0;
	virtual bool OutOfBounds() = 0;
};
