#include "Ball.h"
#include "Player.h"
#include "Game.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
using namespace std;

#define UP_ARROW 72
#define DOWN_ARROW 80
#define ENTER_KEY 13
#define ESCAPE_KEY 27

void Game::redrawMap()
{
	COORD coord;
	CONSOLE_CURSOR_INFO curInfo;
	coord.X = 0;
	coord.Y = 0;
	curInfo.bVisible = false;
	curInfo.dwSize = 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void Game::drawMap()
{
	redrawMap();
	size_t player1X = player1->getX();
	size_t player1Y = player1->getY();
	size_t player2X = player2->getX();
	size_t player2Y = player2->getY();

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	for (size_t i = 0; i < mapWidth; i++)
		cout << '\xB2';
	cout << endl;

	for (size_t i = 0; i < mapHeight; i++)
	{
		for (size_t j = 0; j < mapWidth; j++)
		{
			if ((j == 0) || (j == mapWidth - 1))
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
				cout << '\xB2';
			}

			else if ((j == ball->getX()) && (i == ball->getY()))
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
				cout << 'O';
			}

			else if ((j == player1X) && (i == player1Y))
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
				cout << '\xDB';
			}
			else if ((j == player1X) && (i == player1Y + 1))
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
				cout << '\xDB';
			}
			else if ((j == player1X) && (i == player1Y + 2))
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
				cout << '\xDB';
			}
			else if ((j == player1X) && (i == player1Y + 3))
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
				cout << '\xDB';
			}

			else if ((j == player2X) && (i == player2Y))
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
				cout << '\xDB';
			}
			else if ((j == player2X) && (i == player2Y + 1))
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
				cout << '\xDB';
			}
			else if ((j == player2X) && (i == player2Y + 2))
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
				cout << '\xDB';
			}
			else if ((j == player2X) && (i == player2Y + 3))
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
				cout << '\xDB';
			}

			else
				cout << ' ';
		}
		cout << endl;
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	for (size_t i = 0; i < mapWidth; i++)
		cout << '\xB2';
	cout << endl;

	cout << "Score: " << player1->getScore() << "\t\t\t\t\t  Score: " << player2->getScore() << endl;
}

void Game::getGameInput()
{
	ball->checkDirection();
	size_t player1Y = player1->getY();
	size_t player2Y = player2->getY();

	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
			if (player1Y > 0)
				player1->moveUp();
			break;

		case 's':
			if (player1Y < mapHeight - 4)
				player1->moveDown();
			break;

		case UP_ARROW:
			if (player2Y > 0)
				player2->moveUp();
			break;

		case DOWN_ARROW:
			if (player2Y < mapHeight - 4)
				player2->moveDown();
				break;

		case 'g':
			if (ball->getDirection() == STOP)
				ball->randDirection();
			break;

		case 'r':
			resetGame();
			break;

		case ESCAPE_KEY:
			menuSelectedItem = 0;
			break;
		}
	}
}

void Game::collisionLogic()
{
	size_t ballX = ball->getX();
	size_t ballY = ball->getY();
	direction ballDir = ball->getDirection();
	size_t player1X = player1->getX();
	size_t player1Y = player1->getY();
	size_t player2X = player2->getX();
	size_t player2Y = player2->getY();

	if (ballY == 0)
		(ballDir == UPLEFT) ? ball->setDirection(DOWNLEFT) : ball->setDirection(DOWNRIGHT);
	if (ballY == mapHeight)
		(ballDir == DOWNLEFT) ? ball->setDirection(UPLEFT) : ball->setDirection(UPRIGHT);

	if (ballX - 1 == player1X)
		for (size_t i = 0; i < 4; i++)
			if (ballY == player1Y + i)
				(ballDir == DOWNLEFT) ? ball->setDirection(DOWNRIGHT) : ball->setDirection(UPRIGHT);
	if (ballX + 1 == player2X)
		for (size_t i = 0; i < 4; i++)
			if (ballY == player2Y + i)
				(ballDir == DOWNRIGHT) ? ball->setDirection(DOWNLEFT) : ball->setDirection(UPLEFT);

	if (ballX < player1X)
	{
		player2->scoreUp();
		resetGame();
	}
	if (ballX > player2X)
	{
		player1->scoreUp();
		resetGame();
	}
}

inline void Game::resetGame()
{
	ball->reset();
	player1->reset();
	player2->reset();
}

void Game::drawMenu()
{
	system("color 7");

	helpMenuClear = false;
	if (!menuClear)
		system("cls");
	menuClear = true;

	COORD coord;
	CONSOLE_CURSOR_INFO curInfo;
	curInfo.bVisible = false;
	curInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);

	const char* menuItems[]{ "   PLAY   ", "   HELP   ", "   EXIT   " };
	const char* menuSelectedItems[]{ ">> PLAY <<", ">> HELP <<", ">> EXIT <<" };

	for (size_t i = 0, j = 0; i < 3; i++, j += 2)
	{
		if (i == menuSelectedItem)
		{
			coord.X = (mapWidth / 2) - (strlen(menuSelectedItems[menuSelectedItem]) / 2);
			coord.Y = mapHeight / 2 + j;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
			cout << menuSelectedItems[menuSelectedItem] << endl;
		}
		else
		{
			coord.X = (mapWidth / 2) - (strlen(menuItems[i]) / 2);
			coord.Y = mapHeight / 2 + j;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
			cout << menuItems[i] << endl;
		}
	}
	getMenuInput();
}

void Game::getMenuInput()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
		case UP_ARROW:
			if (menuSelectedItem > 0)
				menuSelectedItem--;
			break;

		case 's':
		case DOWN_ARROW:
			if (menuSelectedItem < 2)
				menuSelectedItem++;
			break;

		case ENTER_KEY:
			switch (menuSelectedItem)
			{
			case 0:
				menuSelectedItem = 3;
				break;

			case 1:
				menuSelectedItem = 4;
				break;

			case 2:
				gameOver = true;
				break;
			}
			break;
		}
	}
}

void Game::drawHelpMenu()
{
	menuClear = false;
	if (!helpMenuClear)
		system("cls");
	helpMenuClear = true;

	COORD coord;
	coord.X = 8;
	coord.Y = 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	cout << "PLAYER 1:" << endl;

	coord.X = 39;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	cout << "PLAYER 2:" << endl;


	coord.X = 7;
	coord.Y = 4;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	cout << "w - move up" << endl;

	coord.X = 35;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	cout << "UP ARROW - move up" << endl;

	coord.X = 6;
	coord.Y = 6;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	cout << "s - move down" << endl;

	coord.X = 32;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	cout << "DOWN ARROW - move down" << endl;


	coord.X = 26;
	coord.Y = 12;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	cout << "GAME:" << endl;

	coord.X = 22;
	coord.Y = 14;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	cout << "g - start game" << endl;

	coord.X = 21;
	coord.Y = 16;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	cout << "r - restart game" << endl;

	coord.X = 24;
	coord.Y = 18;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	cout << "ESC - menu" << endl;
}

Game::Game()
	:mapWidth{ 60 }, mapHeight{ 20 }, ball{ new Ball(mapWidth / 2, mapHeight / 2) }, 
	player1{ new Player(2, mapHeight / 2 - 2) }, player2{ new Player(mapWidth - 3, mapHeight / 2 - 2) }, gameOver{ false }
{}

void Game::run()
{
	while (!gameOver)
	{
		if (menuSelectedItem < 3)
			drawMenu();
		else if (menuSelectedItem == 4)
			drawHelpMenu();
		else
		{
			Sleep(20);
			drawMap();
			getGameInput();
			collisionLogic();
		}
	}
}