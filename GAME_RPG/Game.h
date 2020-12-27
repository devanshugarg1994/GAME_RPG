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
	//Constructors/Destructors
	Game();
	virtual ~Game();

	/** ---------- Functions ---------------- **/
	
	//Regular
	void endApplication();

	//Update
	void updateSFMLEvents();
	void updateDt();
	void update();

	//Render
	void render();

	//Core
	void run();
};

