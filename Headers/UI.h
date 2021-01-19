#pragma once
#include<iostream>
#include"Object.h"
#include"SDL_ttf.h"

class UI : public Object
{
protected:
	char* name = nullptr;
public:
	UI(const char* file = "", SDL_Rect src = { 0,0,0,0 }, SDL_Rect dst = { 0,0,0,0 }, const char* n = "")
		:Object(file, src, dst) {
		name = new char[strlen(n) + 1];
		strcpy_s(name, strlen(n) + 1, n);
	}
	virtual ~UI() { if (name)delete[]name; };
	virtual void draw() = 0;
	virtual int OnClick() = 0;
	virtual bool MouseOn()
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		if (x >= dest.x && x <= dest.x + dest.w && y >= dest.y && y <= dest.y + dest.h)
			return true;
		return false;
	}
};