#pragma once
#include"SDL.h"
#include"SDL_image.h"
#include"GameStuff.h"
using namespace std;

class Texture {
protected:
	char* name = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Rect src;
public:
	Texture();
	Texture(const char* file, SDL_Rect src);
	Texture(const Texture& txt);
	~Texture();
	SDL_Texture* getTexture() const;
	void setTexture(SDL_Texture* t) { texture = t; };
	void setSrc(SDL_Rect s) { src = s; };
	SDL_Rect getSrc() const { return src; };
};
