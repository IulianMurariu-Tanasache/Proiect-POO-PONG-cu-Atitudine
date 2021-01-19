#include<iostream>
#include<cstring>
#include "Object.h"

Object::Object(const char* file, SDL_Rect src, SDL_Rect dst)
	:Texture(file, src),dest(dst)
{}

void Object::scale(float factor)
{
	dest.x *= factor;
	dest.w *= factor;
	dest.y *= factor;
	dest.h *= factor;
}

void Object::draw(Color c)
{
	SDL_Texture* texture = getTexture();
	if (texture)
	{
		SDL_RenderCopy(Stuff::renderer, texture, &src, &dest);
	}
	else
	{
		SDL_SetRenderDrawColor(Stuff::renderer, c.r, c.g, c.b, c.a);
		SDL_RenderFillRect(Stuff::renderer, &dest);
	}
}

void Object::setDestRect(int x, int y, int w, int h)
{
	if (x != -1)
		dest.x = x;
	if (y != -1)
		dest.y = y;
	if (w != -1)
		dest.w = w;
	if (h != -1)
		dest.h = h;
}

SDL_Rect Object::getDest() const
{
	return dest;
}

Object::Object(const Object& obj)
{
	if (obj.texture)
	{
		if (name)
			delete[] name;
		this->name = new char[strlen(obj.name) + 1];
		strcpy_s(name, strlen(obj.name) + 1, obj.name);
		SDL_Surface* tmp = IMG_Load(name);
		texture = SDL_CreateTextureFromSurface(Stuff::renderer, tmp);
		SDL_FreeSurface(tmp);
	}
	else
		this->texture = nullptr;
	this->src = obj.src;
	this->dest = obj.dest;
}
