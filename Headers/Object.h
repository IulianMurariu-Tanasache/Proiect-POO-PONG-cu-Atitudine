#pragma once
#include"Texture.h"

class Object : public Texture
{
protected:
	SDL_Rect dest;
public:
	Object(const char* file = "", SDL_Rect src = { 0,0,0,0 }, SDL_Rect dst = { 0,0,0,0 });
	Object(const Object& obj);
	virtual ~Object() {};
	virtual void draw(Color c = BLACK);
	virtual void update() {};
	virtual void scale(float factor);
	void setDestRect(int x = -1, int y = -1, int w = -1, int h = -1);
	SDL_Rect getDest() const;
	virtual bool MouseOn() { return true; };
};

