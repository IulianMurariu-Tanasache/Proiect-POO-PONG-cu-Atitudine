#include<iostream>
#include"Player.h"

int Player::SPEED = 4;

Player::Player(const char* file, SDL_Rect src, SDL_Rect dst)
	:CevaMiscator(file, src, dst) {
}

void Player1::update()
{
	Uint32 cTime = SDL_GetTicks();
	Uint32 deltaTime = cTime - Stuff::sTime - Stuff::cTime;
	//cout << deltaTime << '\n';
	int xs = 0, ys = 0;
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_SCANCODE_A]) {
		xs = -SPEED;
	}
	if (keystate[SDL_SCANCODE_D]) {
		xs = +SPEED;
	}
	if (!(keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_D]))
		xs = 0;
	if (keystate[SDL_SCANCODE_W]) {
		ys = -SPEED - 1;
	}
	if (keystate[SDL_SCANCODE_S]) {
		ys = SPEED + 1;
	}
	if (!(keystate[SDL_SCANCODE_S] || keystate[SDL_SCANCODE_W]))
		ys = 0;
	if (keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_S] || keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_W]) {
		dest.x += (int)(xs * (deltaTime / 10));
		dest.y += (int)(ys * (deltaTime / 10));
		if (OutOfBounds())
		{
			dest.x -= xs;
			dest.y -= ys;
		}
		xSpeed = xs;
		ySpeed = ys;
	}
	else
		setSpeed();
}

bool Player1::scored(Ball& b) {
	if (b.centreX + b.radius >= 1260 * Stuff::rezProp && b.centreY + b.radius <= 460 *Stuff::rezProp && b.centreY - b.radius >= 260 * Stuff::rezProp)
	{
		score++;
		b.reset(1);
		return true;
	}
	return false;
}

bool Player2::scored(Ball& b) {
	if (b.centreX - b.radius <= 20 * Stuff::rezProp && b.centreY + b.radius <= 460 * Stuff::rezProp && b.centreY - b.radius >= 260 * Stuff::rezProp)
	{
		score++;
		b.reset(2);
		return true;
	}
	return false;
}

void Player2::update()
{
	Uint32 cTime = SDL_GetTicks();
	Uint32 deltaTime = cTime - Stuff::sTime - Stuff::cTime;
	int xs = 0, ys = 0;
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_SCANCODE_LEFT]) {
		xs = -SPEED;
	}
	if (keystate[SDL_SCANCODE_RIGHT]) {
		xs = +SPEED;
	}
	if (!(keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_RIGHT]))
		xs = 0;
	if (keystate[SDL_SCANCODE_UP]) {
		ys = -SPEED - 1;
	}
	if (keystate[SDL_SCANCODE_DOWN]) {
		ys = SPEED + 1;
	}
	if (!(keystate[SDL_SCANCODE_DOWN] || keystate[SDL_SCANCODE_UP]))
		ys = 0;
	if (keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_DOWN] || keystate[SDL_SCANCODE_RIGHT] || keystate[SDL_SCANCODE_UP]) {
		dest.x += (int)(xs * (deltaTime / 10));
		dest.y += (int)(ys * (deltaTime / 10));
		if (OutOfBounds())
		{
			dest.x -= xs;
			dest.y -= ys;
		}
		setSpeed(xs, ys);
	}
	else
		setSpeed();
}

bool Player1::OutOfBounds()
{
	SDL_Rect d = getDest();
	if (dest.x + dest.w > 200 * Stuff::rezProp || dest.x < 20 * Stuff::rezProp || dest.y < 0 * Stuff::rezProp || dest.y + dest.h > 720 * Stuff::rezProp)
		return true;
	return false;
}

bool Player2::OutOfBounds()
{
	SDL_Rect d = getDest();
	if (dest.x + dest.w > 1260 * Stuff::rezProp || dest.x < 1080 * Stuff::rezProp || dest.y < 0 * Stuff::rezProp || dest.y + dest.h > 720 * Stuff::rezProp)
		return true;
	return false;
}

bool Player1::collision(Ball& b)
{
	int bxs = b.xSpeed, bys = b.ySpeed;
	if (((b.centreX - b.radius <= dest.x + dest.w && b.centreX + b.radius > dest.x + dest.w) || (b.centreX + b.radius >= dest.x && b.centreX - b.radius < dest.x)) && b.centreY + b.radius >= dest.y && b.centreY - b.radius <= dest.y + dest.h)
	{
		b.dir = !b.dir;
		/*if (b.centreX - b.radius <= dest.x && (b.centreY - b.radius <= dest.y + dest.h && b.centreY + b.radius >= dest.y))
			b.centreX -= (b.centreX + b.radius) - dest.x;
		else if (b.centreX + b.radius >= dest.x + dest.w && (b.centreY - b.radius <= dest.y + dest.h && b.centreY + b.radius >= dest.y))
			b.centreX += (dest.x + dest.w) - (b.centreX - b.radius);
		if (b.centreY + b.radius >= dest.y + dest.h && (b.centreX <= dest.x + dest.w && b.centreX >= dest.x))
			b.centreY += (dest.y + dest.h) - (b.centreY + b.radius);
		else if (b.centreY - b.radius <= dest.y && (b.centreX <= dest.x + dest.w && b.centreX >= dest.x))
			b.centreY -= (b.centreY - b.radius) - dest.y;*/
		while ((b.centreX - b.radius <= dest.x + dest.w && b.centreX + b.radius >= dest.x) && ((b.centreX - b.radius <= dest.x && (b.centreY - b.radius <= dest.y + dest.h && b.centreY + b.radius >= dest.y)) || (b.centreX + b.radius >= dest.x + dest.w && (b.centreY - b.radius <= dest.y + dest.h && b.centreY + b.radius >= dest.y)))) {
			b.centreX -= bxs;
		}
		while ((b.centreY + b.radius >= dest.y && b.centreY - b.radius <= dest.y + dest.h) && ((b.centreY + b.radius >= dest.y + dest.h && (b.centreX <= dest.x + dest.w && b.centreX >= dest.x)) || (b.centreY - b.radius <= dest.y && (b.centreX <= dest.x + dest.w && b.centreX >= dest.x))))
		{
			b.centreY -= bys;
		}
		if (ySpeed < 0 && bys > 0 || ySpeed > 0 && bys < 0)
			bys *= -1;
		bxs *= -1;
		bxs += xSpeed;
		bys += ySpeed;
		b.setSpeed(bxs, bys);
		return true;
	}
	return false;
}

bool Player2::collision(Ball& b)
{
	int bxs = b.xSpeed, bys = b.ySpeed;
	if (((b.centreX - b.radius < dest.x && b.centreX + b.radius >= dest.x) || (b.centreX + b.radius > dest.x + dest.w && b.centreX - b.radius <= dest.x + dest.w)) && b.centreY + b.radius >= dest.y && b.centreY - b.radius <= dest.y + dest.h)
	{
			b.dir = !b.dir;
			while ((b.centreX - b.radius <= dest.x + dest.w && b.centreX + b.radius >= dest.x) && ((b.centreX - b.radius <= dest.x && (b.centreY - b.radius <= dest.y + dest.h && b.centreY + b.radius >= dest.y)) || (b.centreX + b.radius >= dest.x + dest.w && (b.centreY - b.radius <= dest.y + dest.h && b.centreY + b.radius >= dest.y)))) {
				b.centreX -= bxs;
			}
			while ((b.centreY + b.radius >= dest.y && b.centreY - b.radius <= dest.y + dest.h) && ((b.centreY + b.radius >= dest.y + dest.h && (b.centreX <= dest.x + dest.w && b.centreX >= dest.x)) || (b.centreY - b.radius <= dest.y && (b.centreX <= dest.x + dest.w && b.centreX >= dest.x))))
			{
				b.centreY -= bys;
			}
			if (ySpeed < 0 && bys > 0 || ySpeed > 0 && bys < 0)
				bys *= -1;
			bxs *= -1;
			bxs += xSpeed;
			bys += ySpeed;
			b.setSpeed(bxs, bys);
			return true;
	}
	return false;
}





