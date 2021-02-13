#include "stdafx.h"

#include "Game.h"
// Static functions

// INIT functions

void Game::initVariables()
{
	this->window = NULL;
	this->dt = 0.f;
}

void Game::initGraphicsSettings()
{
	this->gSettings.loadFromFile("Config/graphics.init");
}

// creating game window using Config/window.init file.
void Game::initWindow()
{
	// Default setting
	if (this->gSettings.fullScreen) {
		this->window = new sf::RenderWindow(this->gSettings.resolution, this->gSettings.title, sf::Style::Fullscreen, this->gSettings.contextSettings);

	}
	else {
		this->window = new sf::RenderWindow(this->gSettings.resolution, this->gSettings.title, sf::Style::Titlebar | sf::Style::Close, this->gSettings.contextSettings);
	}
	this->window->setFramerateLimit(this->gSettings.frameRateLimit);
	this->window->setVerticalSyncEnabled(this->gSettings.verticalSync);
}

void Game::initKeys()
{
	std::ifstream ifs("Config/supported_keys.init");

	if (ifs.is_open()) {

		std::string key = "";
		int key_value = 0;

		while (ifs >> key >> key_value) {
			this->supportedKeys[key] = key_value;
		}
		//Closing file
		ifs.close();
	}
	else {
		std::cout << "Error! In opening file `supported_keys.init` at the path: `Config/supported_keys.init` " << std::endl;
	}

	//// Debugging purpose
	//for (auto i : this->supportedKeys) {
	//	std::cout << i.first << " " << i.second << std::endl;
	//}
}

void Game::initStates()
{
	this->states.push(new MainMenuState(this->window, this->gSettings, &(this->supportedKeys), &this->states));
}

// Constructor 
Game::Game()
{
	this->initVariables();
	this->initGraphicsSettings();

	this->initWindow();
	this->initKeys();
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

void Game::endApplication()
{
	std::cout << "End Application!" << std::endl;
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

	if (!this->states.empty()) {
		this->states.top()->update(this->dt);

		if (this->states.top()->getQuit()) {
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	} 
	// If no state is there in `states` Queue then window is closed.
	else {
		this->endApplication();
		this->window->close();
	}
	

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
