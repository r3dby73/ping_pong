class Game
{
	bool menuClear = false;
	bool helpMenuClear = false;

	size_t mapWidth, mapHeight;
	Ball* ball;
	Player* player1;
	Player* player2;
	bool gameOver;
	size_t menuSelectedItem = 0;

	void redrawMap();
	void drawMap();
	void getGameInput();
	void collisionLogic();
	void resetGame();
	void drawMenu();
	void getMenuInput();
	void drawHelpMenu();
	void getMenuHelpInput();

public:
	Game();
	void run();
};