#pragma once
#include"CevaMiscator.h"

class Ball : public CevaMiscator
{
	friend class Player1;
	friend class Player2;
private:
	bool changeDir;
	int32_t centreX, centreY;
	int32_t radius;
	int32_t defRadius;
	bool dir; // daca merge spre stanga e false;
public:
	int BALL_SPEED = 12;
	Ball(int32_t centreX, int32_t centreY, int32_t radius, const char* file = "", SDL_Rect src = { 0,0,0,0 }, SDL_Rect dst = { 0,0,0,0 });
	void reset(int unde = 0);
	void draw();
	void update() ;
	void setCenter(int32_t x, int32_t y) { centreX = x; centreY = y; };
	void setRadius(int32_t r) { radius = r; };
	bool OutOfBounds() ;
	int32_t* getInfo() { int32_t info[] = { centreX, centreY, radius }; return info; };
	void scale(float factor)
	{
		radius = defRadius * Stuff::rezProp;
		BALL_SPEED = round(BALL_SPEED * factor);
	}
};
