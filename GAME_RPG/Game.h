#pragma once
#include<iostream>
#include<ctime>
#include<cstdlib>
#include"SFML/Graphics.hpp"
#include"SFML/System.hpp"
#include"SFML/Window.hpp"
#include"SFML/Audio.hpp"
#include"SFML/Network.hpp"


class Game
{

private:
	// Variables
	sf::RenderWindow* window;
	sf::Event sfEvent;
	// How much each render and update call take 
	sf::Clock dtClock;
	float dt;

	// Initialization
	void initWindow();


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

