#include "Game.h"
// Static functions

// INIT functions
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "SFML works!");
}

// Constructor 
Game::Game()
{
	this->initWindow();
}

Game::~Game()
{
	delete this->window;

}

// Functions
void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();
		
	}
}

void Game::update()
{
	this->updateSFMLEvents();

}

void Game::render()
{
	this->window->clear();

	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen()) {
		this->update();
		this->render();

	}
}
