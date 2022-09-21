#include "Ball.h"
#include <stdlib.h>
#include <time.h>

enum direction { STOP = 0, UPLEFT = 1, DOWNLEFT = 2, UPRIGHT = 3, DOWNRIGHT = 4 };

inline Ball::Ball()
	:x{}, y{}, startX{}, startY{}, dir{}
{}

inline Ball::Ball(size_t x, size_t y)
	:x{ x }, y{ y }, startX{ x }, startY{ y }, dir{ STOP }
{}

inline size_t Ball::getX() { return x; }

inline size_t Ball::getY() { return y; }

void Ball::setDirection(direction dir)
{
	switch (dir)
	{
	case UPLEFT:
	case UPRIGHT:
	case DOWNLEFT:
	case DOWNRIGHT:
		this->dir = dir;
		break;
	}
}

inline direction Ball::getDirection() {	return dir; }

inline void Ball::randDirection()
{
	srand(time(NULL));
	dir = direction(1 + rand() % 4 - 1 + 1); // min + rand() % max - min + 1
}

void Ball::checkDirection()
{
	switch (dir)
	{
	case UPLEFT:
		x--;
		y--;
		break;

	case DOWNLEFT:
		x--;
		y++;
		break;

	case UPRIGHT:
		x++;
		y--;
		break;

	case DOWNRIGHT:
		x++;
		y++;
		break;
	}
}

inline void Ball::reset()
{
	x = startX;
	y = startY;
	dir = STOP;
}