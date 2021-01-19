#pragma once
#include"Player.h"
#include"Ball.h"
#include"Button.h"
#include"Text.h"
#include"SDL_mixer.h"
#include"Tick.h"
#include"PowerUps.h"


class Game {
private:
	bool running = false;
public:
	Game(const char* title = "", int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED, int w = 1280, int h = 720);
	~Game();
	bool isRunning();
	void update();
	void handleEvents();
	void draw();
};