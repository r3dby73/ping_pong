#include "Ball.h"
#include "Player.h"
#include "Game.h"
#include <iostream>
#include <Windows.h>
using namespace std;

Game::Game()
	:mapWidth{ 60 }, mapHeight{ 20 }, ball{ new Ball(mapWidth / 2, mapHeight / 2) }, 
	player1{ new Player(2, mapHeight / 2 - 2) }, player2{ new Player(mapWidth - 3, mapHeight / 2 - 2) }, gameOver{ false }
{}