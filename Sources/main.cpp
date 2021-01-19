#include"Game.h"

int main(int argc, char* argv[])
{
	const int FPS = 60;
	int fpsDelay = 1000 / FPS;
	Uint32 fpsStart;
	Uint32 fpsCurrent;
	Game game("PONG CU ATITUDINE");
	while (game.isRunning())
	{
		fpsStart = SDL_GetTicks();
		game.handleEvents();
		game.update();
		game.draw();
		fpsCurrent = SDL_GetTicks() - fpsStart;
		if (fpsDelay > fpsCurrent)
			SDL_Delay(fpsDelay - fpsCurrent);

	}
	return 0;
}