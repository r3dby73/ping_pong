#include "Ball.h"
#include "Player.h"
#include "Game.h"
#include <iostream>
#include <Windows.h>
using namespace std;

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

Game::Game()
	:mapWidth{ 60 }, mapHeight{ 20 }, ball{ new Ball(mapWidth / 2, mapHeight / 2) }, 
	player1{ new Player(2, mapHeight / 2 - 2) }, player2{ new Player(mapWidth - 3, mapHeight / 2 - 2) }, gameOver{ false }
{}