#pragma once
#include"SDL_ttf.h"
#include"SDL.h"

class Text
{
private:
	SDL_Rect dest;
	char* message = nullptr;
public:
	Text(const char* c, SDL_Rect d);
	~Text();
	void draw();
	void scale(float factor);
	void setMessage(const char* c);

};