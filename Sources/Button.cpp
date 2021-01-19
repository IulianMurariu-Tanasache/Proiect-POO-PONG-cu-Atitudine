#include"Button.h"
#include"GameStuff.h"

int Play::OnClick()
{
	if (MouseOn()) {
		return 2;
	}
	return -1;
}

int Back::OnClick()
{
	if (MouseOn())
		return 0;
	return -1;
}

int Settings::OnClick()
{
	if (MouseOn())
		return 1;
	return -1;
}

int Exit::OnClick()
{
	if (MouseOn())
		return 3;
	return -1;
}

void Exit::draw() 
{
	SDL_Color c = WHITE;
	SDL_SetRenderDrawColor(Stuff::renderer,c.r,c.g,c.b,c.a);
	SDL_RenderFillRect(Stuff::renderer, &dest);
	c = BLACK;
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Stuff::font, name, c);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(Stuff::renderer, surfaceMessage);
	SDL_Rect d = dest;
	d.x += 10;
	d.y -= 15;
	d.w -= 10;
	SDL_RenderCopy(Stuff::renderer, Message, NULL, &d);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}

void Play::draw()
{
	SDL_Color c = WHITE;
	SDL_SetRenderDrawColor(Stuff::renderer, c.r, c.g, c.b, c.a);
	SDL_RenderFillRect(Stuff::renderer, &dest);
	c = BLACK;
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Stuff::font, name, c);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(Stuff::renderer, surfaceMessage);
	SDL_Rect d = dest;
	d.x += 10;
	d.y -= 15;
	d.w -= 10;
	SDL_RenderCopy(Stuff::renderer, Message, NULL, &d);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}

void Settings::draw()
{
	SDL_Color c = WHITE;
	SDL_SetRenderDrawColor(Stuff::renderer, c.r, c.g, c.b, c.a);
	SDL_RenderFillRect(Stuff::renderer, &dest);
	c = BLACK;
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Stuff::font, name, c);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(Stuff::renderer, surfaceMessage);
	SDL_Rect d = dest;
	d.x += 10;
	d.y -= 15;
	d.w -= 10;
	SDL_RenderCopy(Stuff::renderer, Message, NULL, &d);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}

void Back::draw()
{
	SDL_Color c = WHITE;
	SDL_SetRenderDrawColor(Stuff::renderer, c.r, c.g, c.b, c.a);
	SDL_RenderFillRect(Stuff::renderer, &dest);
	c = BLACK;
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Stuff::font, name, c);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(Stuff::renderer, surfaceMessage);
	SDL_Rect d = dest;
	d.x += 10;
	d.y -= 15;
	d.w -= 10;
	SDL_RenderCopy(Stuff::renderer, Message, NULL, &d);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}