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

void Game::initStates()
{
	//this->states.push(new GameState(this->window));

}

// Constructor 
Game::Game()
{
	this->initWindow();
	this->initStates();
}

Game::~Game()
{
	delete this->window;

	while (!this->states.empty()) {
		delete this->states.top();
		this->states.pop();
	}
	

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

	if (!this->states.empty())
		this->states.top()->update(this->dt);

}

void Game::render()
{
	this->window->clear();
	// Render items
	if (!this->states.empty())
		this->states.top()->render();
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
