class Player
{
	size_t x, y;
	size_t startX, startY;
	size_t score;

public:
	Player();
	Player(size_t x, size_t y);

	size_t getX();
	size_t getY();
	size_t getScore();

	void scoreUp();
	void moveUp();
	void moveDown();
	void reset();
};