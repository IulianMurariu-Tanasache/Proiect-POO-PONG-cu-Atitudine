#include"Tick.h"
#include"GameStuff.h"

void Tick::draw()
{
	SDL_Color c = WHITE;
	SDL_SetRenderDrawColor(Stuff::renderer, c.r, c.g, c.b, c.a);
	SDL_RenderFillRect(Stuff::renderer, &dest);
	if (ticked == false)
		c = BLACK;
	else
		c = { 50,50,50,255 };
	SDL_Rect d = getDest();
	d.x += 10;
	d.y += 10;
	d.w -= 20;
	d.h -= 20;
	SDL_SetRenderDrawColor(Stuff::renderer, c.r, c.g, c.b, c.a);
	SDL_RenderFillRect(Stuff::renderer, &d);
	
}
int Tick::OnClick()
{
	if (MouseOn())
	{
		ticked = !ticked;
		return 1;
	}
	return -1;
}