#include "game.h"

Game *Game::_instance = nullptr;

Game *Game::instance()
{
	if (_instance == nullptr)
		_instance = new Game();
	return _instance;
}

void Game::newGame()
{

}

Game::Game(QObject *parent) : QObject(parent)
{

}
