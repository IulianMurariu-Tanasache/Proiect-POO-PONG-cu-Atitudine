#pragma once
#include"UI.h"

class Button : public UI
{
public:
	Button(const char* file = "", SDL_Rect src = { 0,0,0,0 }, SDL_Rect dst = { 0,0,0,0 }, const char* n = "") :UI(file, src, dst, n) {};
	virtual int OnClick() = 0;
	virtual void draw() = 0;
};

class Play : public Button
{
public:
	Play(const char* file = "", SDL_Rect src = { 0,0,0,0 }, SDL_Rect dst = { 0,0,0,0 }, const char* n = "") : Button(file,src,dst,n) {};
	int OnClick() ;
	void draw() ;
};

class Back : public Button
{
public:
	Back(const char* file = "", SDL_Rect src = { 0,0,0,0 }, SDL_Rect dst = { 0,0,0,0 }, const char* n = "") :Button(file, src, dst, n) {};
	int OnClick() ;
	void draw() ;
};

class Settings : public Button
{
public:
	Settings(const char* file = "", SDL_Rect src = { 0,0,0,0 }, SDL_Rect dst = { 0,0,0,0 }, const char* n = "") :Button(file, src, dst, n) {};
	int OnClick() ;
	void draw() ;
};

class Exit : public Button
{
public:
	Exit(const char* file = "", SDL_Rect src = { 0,0,0,0 }, SDL_Rect dst = { 0,0,0,0 }, const char* n = "") :Button(file, src, dst, n) {};
	int OnClick() ;
	void draw() ;
};