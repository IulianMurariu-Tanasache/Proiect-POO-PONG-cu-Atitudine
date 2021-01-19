#include "PowerUps.h"
#include "Player.h"
#include <stdlib.h>

PowerUps::PowerUps(const char* file, SDL_Rect src) 
    :Object(file, src)
{
    Stuff::powerTaken = false;
    Stuff::powerStartTime = Stuff::cTime;
    SDL_Rect dest;
    dest.w = 50;
    dest.h = 50;
    dest.x = rand() % (int)(1020 * Stuff::rezProp) + 200 * Stuff::rezProp;
    dest.y = rand() % (int)(640 * Stuff::rezProp) + 30 * Stuff::rezProp;
    this->dest = dest;
}

bool PowerUps::collisionDetect(Ball& b)
{
    int32_t* info = b.getInfo();
    if (((info[0]- info[2] < dest.x && info[0]+ info[2] >= dest.x) || (info[0]+ info[2] > dest.x + dest.w && info[0]- info[2] <= dest.x + dest.w)) && info[1] + info[2] >= dest.y && info[1] - info[2] <= dest.y + dest.h)
        return true;
    return false;
}

void smallPower::doSomething(Ball& b)
{
    if (!collisionDetect(b))
        return;
    Stuff::powerTaken = true;
    Stuff::powerStartTime = Stuff::cTime;
    int32_t* info = b.getInfo();
    b.setRadius(info[2] / 2);
}

void bigPower::revert(Ball& b)
{
    
    int32_t* info = b.getInfo();
    b.setRadius(info[2] / 2);
}

void bigPower::doSomething(Ball& b)
{
    if (!collisionDetect(b))
        return;
    Stuff::powerStartTime = Stuff::cTime;
    Stuff::powerTaken = true;
    int32_t* info = b.getInfo();
    b.setRadius(info[2] * 2);
}

void smallPower::revert(Ball& b)
{
    
    int32_t* info = b.getInfo();
    b.setRadius(info[2] * 2);
}

void fastPower::doSomething(Ball& b)
{
    if (!collisionDetect(b))
        return;
    Stuff::powerStartTime = Stuff::cTime;
    Stuff::powerTaken = true;
    b.BALL_SPEED *= 2;
}

void slowPower::revert(Ball& b)
{
    
    b.BALL_SPEED *= 2;
}

void slowPower::doSomething(Ball& b)
{
    if (!collisionDetect(b))
        return;
    Stuff::powerStartTime = Stuff::cTime;
    Stuff::powerTaken = true;
    b.BALL_SPEED /= 2;
}

void fastPower::revert(Ball& b)
{
    
    b.BALL_SPEED /= 2;
}

void invertPower::doSomething(Ball& b)
{
    if (!collisionDetect(b))
        return;
    Stuff::powerStartTime = Stuff::cTime;
    Stuff::powerTaken = true;
    Player::SPEED *= -1;
}

void invertPower::revert(Ball& b)
{
    Player::SPEED *= -1;
}

