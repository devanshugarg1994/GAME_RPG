#include "GameState.h"

GameState::GameState(sf::RenderWindow * window)
	: State(window)
{
}

GameState::~GameState()
{
}

void GameState::endState()
{
}

void GameState::update(const float& dt)
{
}

void GameState::render(sf::RenderTarget* target)
{
	std::cout << "Hello from game state" << std::endl;
}
