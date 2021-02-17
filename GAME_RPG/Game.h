#pragma once

#include "MainMenuState.h"

class Game
{

private:
	// Variables
	sf::RenderWindow* window;
	GraphicsSetting gSettings;
	StateData stateData;
	sf::Event sfEvent;

	// How much each render and update call take 
	sf::Clock dtClock;
	float dt;
	// Resourcses
	std::vector<sf::Texture> texture;
	std::stack<State*> states;
	std::map<std::string, int> supportedKeys;
	float gridSize;
	// Initialization
	void initVariables();
	void initGraphicsSettings();
	void initWindow();
	void initKeys();
	void initStateData();
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

