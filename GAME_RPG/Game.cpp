#include "Game.h"
// Static functions

// INIT functions

// creating game window using Config/window.init file.
void Game::initWindow()
{
	// Default setting

	std::string title = "NONE";
	sf::VideoMode window_bounds(720, 720);
	unsigned int frameRate = 120;
	bool vertical_syn_enabled = false;

	std::ifstream ifs("Config/window.init");

	if (ifs.is_open()) {
		std::getline(ifs, title);
		ifs >> window_bounds.width;
		ifs >> window_bounds.height;
		ifs >> frameRate;
		ifs >> vertical_syn_enabled;
	}
	ifs.close();
	this->window = new sf::RenderWindow(window_bounds, title);
	this->window->setFramerateLimit(frameRate);
	this->window->setVerticalSyncEnabled(vertical_syn_enabled);
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

void Game::updateDt()
{
	this->dt = this->dtClock.restart().asSeconds();
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
		this->updateDt();
		this->update();
		this->render();

	}
}
