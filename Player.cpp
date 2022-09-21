#include "Player.h"

inline Player::Player()
	:x{}, y{}, startX{}, startY{}, score{}
{}

inline Player::Player(size_t x, size_t y)
	:x{ x }, y{ y }, startX{ x }, startY{ y }, score{}
{}

inline size_t Player::getX() { return x; }

inline size_t Player::getY() { return y; }

inline size_t Player::getScore() { return score; }

inline void Player::scoreUp() { score++; }

inline void Player::moveUp() { y -= 2; }

inline void Player::moveDown() { y += 2; }

inline void Player::reset()
{
	x = startX;
	y = startY;
}