#include<iostream>
#include<time.h>
#include<cmath>
#include"Ball.h"

using namespace std;

Ball::Ball(int32_t centreX, int32_t centreY, int32_t radius, const char* file, SDL_Rect src, SDL_Rect dst)
	:CevaMiscator(file, src, dst) 
{
    srand((unsigned)time(NULL));
    changeDir = true;
    this->centreX = centreX;
    this->centreY = centreY;
    this->radius = radius;
    this->defRadius = radius;
    reset();
}

void Ball::draw()
{
    const int32_t diameter = (radius * 2);
    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);
    Color c = WHITE;
    SDL_SetRenderDrawColor(Stuff::renderer, c.r, c.g, c.b, c.a);
    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(Stuff::renderer, centreX + x, centreY - y);
        SDL_RenderDrawPoint(Stuff::renderer, centreX + x, centreY + y);
        for (int32_t i = -y; i < y; ++i)
            SDL_RenderDrawPoint(Stuff::renderer, centreX + x, centreY + i);
        SDL_RenderDrawPoint(Stuff::renderer, centreX - x, centreY - y);
        SDL_RenderDrawPoint(Stuff::renderer, centreX - x, centreY + y);
        for (int32_t i = -y; i < y; ++i)
            SDL_RenderDrawPoint(Stuff::renderer, centreX - x, centreY + i);
        SDL_RenderDrawPoint(Stuff::renderer, centreX + y, centreY - x);
        SDL_RenderDrawPoint(Stuff::renderer, centreX + y, centreY + x);
        for (int32_t i = -x; i < x; ++i)
            SDL_RenderDrawPoint(Stuff::renderer, centreX + y, centreY + i);
        SDL_RenderDrawPoint(Stuff::renderer, centreX - y, centreY - x);
        SDL_RenderDrawPoint(Stuff::renderer, centreX - y, centreY + x);
        for (int32_t i = -x; i < x; ++i)
            SDL_RenderDrawPoint(Stuff::renderer, centreX - y, centreY + i);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

void Ball::update()
{
    Uint32 cTime = SDL_GetTicks();
    Uint32 deltaTime = cTime - Stuff::sTime - Stuff::cTime;
    int cxs = xSpeed, cys = ySpeed;
    if (OutOfBounds()) {
        if (centreX + radius > 1280 * Stuff::rezProp || centreX - radius < 0)
        {
            dir = !dir;
            cys *= -1;
            cxs *= -1;
            centreX += cxs;
            centreY += cys;
        }
        else {
            centreX -= cxs;
            centreY -= cys;
        }
        changeDir = true;
    }
    if (changeDir)
    {
        cxs /= abs(cxs);
        cys /= abs(cys);
        cxs *= (rand() % 4) + BALL_SPEED;
        cys *= (rand() % 3 - 1) * (rand() % 3) + BALL_SPEED;
        cys *= -1;
        setSpeed((int)(cxs * (deltaTime / 10)) , (int)(cys * (deltaTime / 10)));
        changeDir = false;
    }   
    centreX += cxs;
    centreY += cys;
}

bool Ball::OutOfBounds()
{
    if (centreX + radius > 1280 * Stuff::rezProp || centreX - radius < 0 || centreY + radius > 720 * Stuff::rezProp || centreY - radius < 0)
        return true;
    return false;
}

void Ball::reset(int unde)
{
    int cxs = 0, cys = 0;
    centreX = 1280 * Stuff::rezProp / 2;
    centreY = 720 * Stuff::rezProp / 2;
    changeDir = true;
    switch (unde) {
    case 0:
    default:
        while (cxs == 0 || cys == 0)
        {
            cxs = (rand() % 3 + 2 + BALL_SPEED ) * (rand() % 2 - 1) ;
            cys = (rand() % 4 + 2 + BALL_SPEED ) * (rand() % 2 - 1) ;
        }
        dir = false;
        if (cxs > 0)
            dir = true;
        break;
    case 1:
        while (cxs == 0 || cys == 0)
        {
            cxs = (rand() % 3 + 2) + BALL_SPEED;
            cys = (rand() % 4 + 2 + BALL_SPEED) * (rand() % 2 - 1);
        }
        dir = true;
        break;
    case 2:
        while (cxs == 0 || cys == 0)
        {
            cxs = (rand() % 3 + 2) * -1 - BALL_SPEED;
            cys = (rand() % 4 + 2 + BALL_SPEED) * (rand() % 2 - 1) ;
        }
        dir = false;
        break;
    }
    //this->centreX = centreX;
    //this->centreY = centreY;
    //this->radius = radius;
    setSpeed(cxs, cys);
}