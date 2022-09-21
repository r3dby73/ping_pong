class Ball
{
	size_t x, y;
	size_t startX, startY;
	direction dir;

public:
	Ball();
	Ball(size_t, size_t);

	size_t getX();
	size_t getY();
	void setDirection(direction);
	direction getDirection();

	void randDirection();
	void checkDirection();
	void reset();
};