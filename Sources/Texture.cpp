#include"Texture.h"
#include<iostream>
#include<cstring>

Texture::Texture()
{
	name = nullptr;
	texture = nullptr;
	src = { 0,0,0,0 };
}

Texture::Texture(const char* file, SDL_Rect src)
{
	name = new char[strlen(file) + 1];
	strcpy_s(name, strlen(file) + 1, file);
	try {
		texture = IMG_LoadTexture(Stuff::renderer, file);
	}
	catch (int e){
		texture = nullptr;
		name = nullptr;
	}
	this->src = src;
}

Texture::~Texture()
{
	SDL_DestroyTexture(texture);
	texture = nullptr;
	if (name)
		delete[] name;
	name = nullptr;
}

/*void Texture::operator= (const Texture& txt)
{
	if (txt.texture)
	{
		if (name)
			delete[] name;
		this->name = new char[strlen(txt.name) + 1];
		strcpy_s(name, strlen(txt.name) + 1, txt.name);
		SDL_Surface* tmp = IMG_Load(name);
		texture = SDL_CreateTextureFromSurface(Stuff::renderer, tmp);
		SDL_FreeSurface(tmp);
	}
	else
		this->texture = nullptr;
	this->src = txt.src;
}*/

Texture::Texture(const Texture& txt)
{
	if (txt.texture)
	{
		if (name)
			delete[] name;
		this->name = new char[strlen(txt.name) + 1];
		strcpy_s(name, strlen(txt.name) + 1, txt.name);
		SDL_Surface* tmp = IMG_Load(name);
		texture = SDL_CreateTextureFromSurface(Stuff::renderer, tmp);
		SDL_FreeSurface(tmp);
	}
	else
		this->texture = nullptr;
	this->src = txt.src;
}

SDL_Texture* Texture::getTexture() const
{
	return texture;
}

