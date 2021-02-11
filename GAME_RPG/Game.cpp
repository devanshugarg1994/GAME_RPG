#include "stdafx.h"

#include "Game.h"
// Static functions

// INIT functions

void Game::initVariables()
{
	this->window = NULL;
	this->dt = 0.f;
	this->fullScreen = false;
}

// creating game window using Config/window.init file.
void Game::initWindow()
{
	// Default setting
	std::ifstream ifs("Config/window.init");
	this->videoModes = sf::VideoMode::getFullscreenModes();
	
	std::string title = "NONE";
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
	bool fullscreen = false;
	unsigned int frameRate = 120;
	bool vertical_syn_enabled = false;
	unsigned antialiasing_level = 0;

	if (ifs.is_open()) {
		std::getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> fullscreen;
		ifs >> frameRate;
		ifs >> vertical_syn_enabled;
		ifs >> antialiasing_level;
	}
	ifs.close();
	this->fullScreen = fullscreen;
	this->windowSettings.antialiasingLevel = antialiasing_level;
	if (this->fullScreen) {
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, this->windowSettings);

	}
	else {
		this->window = new sf::RenderWindow(window_bounds, title,  sf::Style::Titlebar | sf::Style::Close, this->windowSettings);
	}
	this->window->setFramerateLimit(frameRate);
	this->window->setVerticalSyncEnabled(vertical_syn_enabled);
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
	this->states.push(new MainMenuState(this->window, &(this->supportedKeys), &this->states));
}

// Constructor 
Game::Game()
{
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
