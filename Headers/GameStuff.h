#pragma once
#include"SDL_mixer.h"
#include"SDL.h"
#include"SDL_ttf.h"

enum menus { mainMenu, settings, gameplay, exitGame };
enum powerUp { fast, slow, big, smallBall, invert};

struct Color {
	int r, g, b, a;
};
#define RED {255,0,0,255}
#define BLUE {0,0,255,255}
#define GREEN {0,255,0,255}
#define WHITE {255,255,255,255}
#define BLACK {0,0,0,255}


class Stuff{
public:
	static bool ai;
	static bool ended;
	static bool paused;
	static int powerStartTime;
	static bool powerTaken;
	static menus menu;
	static float rezProp;
	static int rezW, rezH;
	static Uint32 cTime;
	static Uint32 sTime;
	static bool playingMusic;
	static SDL_Window* window;
	static SDL_Renderer* renderer;
	static TTF_Font* font;
};
