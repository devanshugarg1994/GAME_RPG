#pragma once

#include"GameState.h"


class Game
{

private:
	// Variables
	sf::RenderWindow* window;
	sf::Event sfEvent;
	// How much each render and update call take 
	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;
	// Initialization
	void initWindow();
	void initStates();


public:
	Game();
	virtual ~Game();

	// Functions
	void updateSFMLEvents();
	void updateDt();
	void update();
	void render();
	void run();
};

