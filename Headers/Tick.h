#pragma once
#include"UI.h"

class Tick : public UI
{
protected:
	bool ticked;
public:
	Tick(const char* file = "", SDL_Rect src = { 0,0,0,0 }, SDL_Rect dst = { 0,0,0,0 }, const char* n = "")
		:UI(file, src, dst) {
		name = new char[strlen(n) + 1];
		strcpy_s(name, strlen(n) + 1, n);
		ticked = false;
	}
	void draw();
	int OnClick();
	bool getTicked() { return ticked; };
	void setTicked(bool t) { ticked = t; };
};