#include<iostream>
#include"Text.h"
#include"GameStuff.h"
using namespace std;

Text::Text(const char* c, SDL_Rect d)
{
	message = new char[strlen(c) + 1];
	strcpy_s(message, strlen(c) + 1, c);
	dest = d;
}

Text::~Text()
{
	if (message)
		delete[] message;
}

void Text::draw()
{
	SDL_Color White = { 255,255,255 };
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Stuff::font, message, White);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(Stuff::renderer, surfaceMessage);
	SDL_RenderCopy(Stuff::renderer, Message, NULL, &dest);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}

void Text::setMessage(const char* c)
{
	if (message)
		delete[] message;
	message = new char[strlen(c) + 1];
	strcpy_s(message, strlen(c) + 1, c);
}

void Text::scale(float factor)
{
	dest.x *= factor;
	dest.w *= factor;
	dest.y *= factor;
	dest.h *= factor;
}
