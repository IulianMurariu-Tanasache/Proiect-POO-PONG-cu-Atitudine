#pragma once
#include"Ball.h"
#define WinScore 7

class Player : public CevaMiscator
{
public:
	static int SPEED;
	Player(const char* file = "", SDL_Rect src = { 0,0,0,0 }, SDL_Rect dst = { 0,0,0,0 });
	virtual void update() = 0;
	virtual bool OutOfBounds() = 0;
	virtual bool collision(Ball& b) = 0;
	virtual bool scored(Ball& b) = 0;
	virtual int getScore() = 0;
	virtual bool checkWin() = 0;
	void scale(float factor)
	{
		dest.x *= factor;
		dest.w *= factor;
		dest.y *= factor;
		dest.h *= factor;
		SPEED = round(SPEED * factor);
	}
};

class Player1 : public Player
{
private:
	int score;
public:
	Player1(const char* file = "", SDL_Rect src = { 0,0,0,0 }, SDL_Rect dst = { 0,0,0,0 }) : Player(file, src, dst) { score = 0; };
	void update() ;
	bool OutOfBounds() ;
	bool collision(Ball& b);
	bool scored(Ball& b);
	int getScore() { return score; }
	bool checkWin() {
		return score >= WinScore;
	}
	void setScore(int s) { score = s; }
};

class Player2 : public Player
{
private:
	int score;
public:
	Player2(const char* file = "", SDL_Rect src = { 0,0,0,0 }, SDL_Rect dst = { 0,0,0,0 }) : Player(file, src, dst) { score = 0; };
	void update() ;
	bool OutOfBounds() ;
	bool collision(Ball& b);
	bool scored(Ball& b);
	int getScore() { return score; }
	bool checkWin() {
		return score >= WinScore;
	}
	void setScore(int s) { score = s; }
};