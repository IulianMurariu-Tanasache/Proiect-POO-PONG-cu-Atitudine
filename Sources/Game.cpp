#include"Game.h"
#include<iostream>
#include<string>
#include<vector>
#include<time.h>
#include"GameStuff.h"
#include"SaveManager.h"

using namespace std;

float Stuff::rezProp = 1;
int Stuff::rezW = 1280;
int Stuff::rezH = 720;
int Stuff::powerStartTime = 0;
Uint32 Stuff::cTime = 0;
Uint32 Stuff::sTime = 0;
bool Stuff::playingMusic = false;
bool Stuff::powerTaken = false;
bool Stuff::paused = false;
bool Stuff::ended = false;
bool Stuff::ai = false;
SDL_Window* Stuff::window = nullptr;
SDL_Renderer* Stuff::renderer = nullptr;
TTF_Font* Stuff::font = nullptr;
menus Stuff::menu = menus::mainMenu;

Player1* p1 = nullptr;
Player2* p2 = nullptr;
Ball* b = nullptr;
Object* back = nullptr;
Play* playButton = nullptr;
Back* backButton = nullptr;
Settings* settingsButton = nullptr;
Exit* exitButton = nullptr;
Mix_Music* music = nullptr;
Mix_Music* gameSong = nullptr;
Mix_Music* menuSong = nullptr;
Mix_Chunk* winSound = nullptr;
Mix_Chunk* ping1 = nullptr;
Mix_Chunk* ping2 = nullptr;
Mix_Chunk* scoreSound = nullptr;
Tick* musicOn = nullptr;
Tick* soundOn = nullptr;
Tick* fullscreen = nullptr;
Text* title = nullptr;
Text* scoreP1 = nullptr;
Text* scoreP2 = nullptr;
Text* soundOnText = nullptr;
Text* musicOnText = nullptr;
Text* fullscreenText = nullptr;
Text* pausedGame = nullptr;
Text* p1won = nullptr;
Text* p2won = nullptr;
PowerUps* power = nullptr;
vector<Text*> texts;
vector<Object*> objects;
vector<Tick*> ticks;

void setRezolution()
{
	if (fullscreen->getTicked())
	{
		float factor = 1920.0f / Stuff::rezW;
		//cout << factor << '\n';
		for (auto o : objects)
			o->scale(factor);
		for (auto t : texts)
			t->scale(factor);
		//cout << playButton->getDest().x <<'\n';
		Stuff::rezH = 1080;
		Stuff::rezW = 1920;
		Stuff::rezProp = factor;
		SDL_SetWindowFullscreen(Stuff::window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
	else if (fullscreen->getTicked() == false)
	{
		float factor = 1280.0f / Stuff::rezW;
		for (auto o : objects)
			o->scale(factor);
		for (auto t : texts)
			t->scale(factor);
		Stuff::rezH = 720;
		Stuff::rezW = 1280;
		Stuff::rezProp = 1;
		SDL_SetWindowFullscreen(Stuff::window, 0);
		SDL_SetWindowSize(Stuff::window, Stuff::rezW, Stuff::rezH);
	}
}

Game::Game(const char* t, int x, int y, int w, int h)
{
	Stuff::rezW = w;
	Stuff::rezH = h;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		Stuff::window = SDL_CreateWindow(t, x, y, w, h, SDL_WINDOW_SHOWN);
		if (Stuff::window == nullptr)
		{
			cout << "Creating window failed!\n";
			return;
		}
		Stuff::renderer= SDL_CreateRenderer(Stuff::window, -1, 0);
		if (Stuff::renderer == nullptr)
		{
			cout << "Creating Stuff::renderer failed!\n";
			return;

		}
		if (TTF_Init() == -1) {
			cout << "Libraria cu fonturile nu merge!\n";
		}
		Stuff::font = TTF_OpenFont("Assets/8-bit_Arcade_In.ttf", 35);
		if (!Stuff::font){
			cout << "Nu s-a incarcat fontul!\n";
			cout << TTF_GetError() << '\n';
		}
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
		menuSong = Mix_LoadMUS("Assets/menuSong.wav");
		gameSong = Mix_LoadMUS("Assets/gameSong.wav");
		winSound = Mix_LoadWAV("Assets/winSound.wav");
		ping1 = Mix_LoadWAV("Assets/pingpong1.wav");
		scoreSound = Mix_LoadWAV("Assets/scoreSound.wav");
		ping2 = Mix_LoadWAV("Assets/pingpong2.wav");
		music = menuSong;
		Stuff::menu = menus::mainMenu;
		back = new Object("Assets/back.png", { 0,0,1280,720 }, {0,0,1280,720});
		objects.push_back(back);
		p1 = new Player1("", { 0,0,0,0 }, { 50,50,20,100 });
		objects.push_back(p1);
		p2 = new Player2("", { 0,0,0,0 }, { 1230,50,20,100 });
		objects.push_back(p2);
		b = new Ball(1280 / 2, 720 / 2, 20);
		objects.push_back(b);
		playButton = new Play("", { 0,0,0,0 }, { 540,350,250,80 }, "Play");
		objects.push_back(playButton);
		settingsButton = new Settings("", { 0,0,0,0 }, { 540,450,250,80 }, "Settings");
		objects.push_back(settingsButton);
		exitButton = new Exit("", { 0,0,0,0 }, { 540,550,250,80 }, "Exit");
		objects.push_back(exitButton);
		backButton = new Back("", { 0,0,0,0 }, { 1170,650,100,60 }, "Back");
		objects.push_back(backButton);
		musicOn = new Tick("", { 0,0,0,0 }, {430,80,70,70},"Music On");
		objects.push_back(musicOn);
		ticks.push_back(musicOn);
		soundOn = new Tick("", { 0,0,0,0 }, {430,160,70,70},"Sound On");
		objects.push_back(soundOn);
		ticks.push_back(soundOn);
		fullscreen = new Tick("fullscreen", { 0,0,0,0 }, {430,240,70,70},"Fullscreen");
		objects.push_back(fullscreen);
		ticks.push_back(fullscreen);
		title = new Text((char*)"PONG CU ATITUDINE", { 150,-40,1000,280 });
		texts.push_back(title);
		pausedGame = new Text("PAUSE", {450,215,400,210});
		texts.push_back(pausedGame);
		p1won = new Text("PLAYER 1 WINS", {250,210,770,240});
		texts.push_back(p1won);
		p2won = new Text("PLAYER 2 WINS", { 250,210,770,240 });
		texts.push_back(p2won);
		scoreP1 = new Text("", { 50,-70,90,270 });
		texts.push_back(scoreP1);
		scoreP2 = new Text("", { 1280 - 90 - 50,-70,90,270 });
		texts.push_back(scoreP2);
		musicOnText = new Text("Music On", { 60,50,350,100 });
		texts.push_back(musicOnText);
		soundOnText = new Text("Sound On", { 60,130,350,100 });
		texts.push_back(soundOnText);
		fullscreenText = new Text("Fullscreen", { 60,210,350,100 });
		texts.push_back(fullscreenText);
		Stuff::cTime = SDL_GetTicks();
		running = true;
		music = menuSong;
		SaveManager::loadData(ticks);
		setRezolution();
	}
	else
	{
		cout << "Initializing failed!\n";
	}
}

Game::~Game()
{
	SDL_DestroyRenderer(Stuff::renderer);
	SDL_DestroyWindow(Stuff::window);
	Mix_FreeMusic(gameSong);
	Mix_FreeMusic(menuSong);
	Mix_FreeChunk(winSound);
	Mix_FreeChunk(scoreSound);
	Mix_FreeChunk(ping1);
	Mix_FreeChunk(ping2);
	delete p1;
	delete p2;
	delete b;
	delete back;
	delete playButton;
	delete backButton;
	delete settingsButton;
	delete exitButton;
	delete musicOn;
	delete soundOn;
	for (Text* t : texts)
		delete t;
	texts.clear();
	objects.clear();
	if (power != nullptr) {
		delete power;
	}
}

bool Game::isRunning()
{
	return running;
}

void Game::draw()
{
	SDL_SetRenderDrawColor(Stuff::renderer, 0, 0, 0, 255);
	SDL_RenderClear(Stuff::renderer);
	switch (Stuff::menu)
	{
	default:
	case mainMenu:
		title->draw();
		playButton->draw();
		settingsButton->draw();
		exitButton->draw();
		break;
	case menus::gameplay:
		back->draw();
		scoreP1->setMessage(to_string(p1->getScore()).c_str());
		scoreP2->setMessage(to_string(p2->getScore()).c_str());
		scoreP1->draw();
		scoreP2->draw();
		p1->draw(RED);
		p2->draw(BLUE);
		b->draw();
		backButton->draw();
		if (power != nullptr && Stuff::powerTaken == false)
			power->draw();
		if (Stuff::paused && Stuff::ended == false)
			pausedGame->draw();
		if (p1->checkWin())
			p1won->draw();
		else if (p2->checkWin())
			p2won->draw();
		break;
	case settings:
		soundOnText->draw();
		musicOnText->draw();
		fullscreenText->draw();
		musicOn->draw();
		soundOn->draw();
		fullscreen->draw();
		backButton->draw();
		break;
	case menus::exitGame:
		running = false;
		break;
	}
	SDL_RenderPresent(Stuff::renderer);
}

void Game::handleEvents()
{
	int m = -1;
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_KEYDOWN:
		if(event.key.keysym.sym == SDLK_p)
		{
			Stuff::paused = !Stuff::paused;
		}
		break;
	case SDL_QUIT:
		running = false;
		break;
	case SDL_MOUSEBUTTONDOWN:
		switch (Stuff::menu)
		{
		default:
		case mainMenu:
			if (playButton->OnClick() != -1)
			{
				m = playButton->OnClick();
				music = gameSong;
				Stuff::sTime = SDL_GetTicks();
				if(Stuff::playingMusic)
					Mix_PlayMusic(music, -1);
			}
			if (settingsButton->OnClick() != -1)
				m = settingsButton->OnClick();
			if (exitButton->OnClick() != -1)
				m = exitButton->OnClick();
			break;
		case settings:
			if (backButton->OnClick() != -1)
			{
				m = backButton->OnClick();
				SaveManager::saveData(ticks);
			}
			musicOn->OnClick();
			soundOn->OnClick();
			if (fullscreen->OnClick() == 1)
			{
				setRezolution();
			}
			break;
		case menus::gameplay:
			if (backButton->OnClick() != -1)
			{
				m = backButton->OnClick();
				music = menuSong;
				if (Stuff::playingMusic)
					Mix_PlayMusic(music, -1);
			}
			break;
		}
		break;
	}
	if (m != -1)
		Stuff::menu = (menus)m;
}

void Game::update()
{
	if (musicOn->getTicked() == false && Stuff::playingMusic == true)
	{
		Mix_HaltMusic();
		Stuff::playingMusic = false;
	}
	else if (musicOn->getTicked() == true && Stuff::playingMusic == false) {
		Mix_PlayMusic(music, -1);
		Stuff::playingMusic = true;
	}
	if (Stuff::menu == menus::gameplay)
	{
		if (Stuff::paused == false) {
			p1->update();
			p2->update();
			b->update();
			if ((p1->scored(*b) || p2->scored(*b)) && soundOn->getTicked())
				Mix_PlayChannel(-1, scoreSound, 0);
			if (p1->collision(*b) && soundOn->getTicked())
				Mix_PlayChannel(-1, ping1, 0);
			if (p2->collision(*b) && soundOn->getTicked())
				Mix_PlayChannel(-1, ping2, 0);
			Stuff::cTime = SDL_GetTicks() - Stuff::sTime;
			if (Stuff::cTime > 2999 && (Stuff::cTime / 1000) % 3 == 0 && power == nullptr)
			{
				powerUp p = powerUp(rand() % 5);
				switch (p)
				{
				case powerUp::smallBall:
					power = (PowerUps*)(new smallPower("Assets/smallPower.png", { 0,0,50,50 }));
					break;
				case big:
					power = (PowerUps*)(new bigPower("Assets/bigPower.png", { 0,0,50,50 }));
					break;
				case fast:
					power = (PowerUps*)(new fastPower("Assets/fastPower.png", { 0,0,50,50 }));
					break;
				case slow:
					power = (PowerUps*)(new slowPower("Assets/slowPower.png", { 0,0,50,50 }));
					break;
				case invert:
					power = (PowerUps*)(new invertPower("Assets/invertPower.png", { 0,0,50,50 }));
					break;
				}
			}
			if (power && Stuff::powerTaken == false)
			{
				power->doSomething(*b);
			}
			if (power != nullptr && Stuff::cTime - Stuff::powerStartTime > 7000)
			{
				;			if (Stuff::powerTaken)
					power->revert(*b);
				delete power;
				power = nullptr;
			}
		}
		if (p1->checkWin() || p2->checkWin() || Stuff::ended == true) {
			if(Stuff::ended == false)
			{
				Stuff::ended = true;
				Stuff::paused = true;
				Stuff::sTime = SDL_GetTicks();
			}
			if (SDL_GetTicks() - Stuff::sTime > 2500)
			{
				b->reset();
				p1->setScore(0);
				p2->setScore(0);
				Stuff::cTime = 0;
				Stuff::sTime = 0;
				Stuff::powerStartTime = 0;
				Stuff::powerTaken = false;
				Stuff::paused = false;
				Stuff::ended = false;
				if (power)
					delete power;
				power = nullptr;
			}
		}
	}
}
