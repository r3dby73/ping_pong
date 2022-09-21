#include "Game.h"

int main()
{
	system("mode con cols=60 lines=24");
	Game game = Game();
	game.run();

	return 0;
}