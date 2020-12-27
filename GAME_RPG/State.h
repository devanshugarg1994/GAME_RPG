#pragma once
#include<iostream>
#include<ctime>
#include<cstdlib>
#include"SFML/Graphics.hpp"
#include"SFML/System.hpp"
#include"SFML/Window.hpp"
#include"SFML/Audio.hpp"
#include"SFML/Network.hpp"
#include<vector>
#include<stack>
#include<map>
#include<fstream>
#include<sstream>
class State
{
private:
	sf::RenderWindow* window;
	std::vector<sf::Texture> textures;
	bool quit;
public:
	State(sf::RenderWindow * window);
	virtual ~State(); 

	// Accessrors

	const bool& getQuit() const;
	virtual void checkForQuit();

	virtual void endState() = 0;
	virtual void updateKeyBinds(const float &dt =0) = 0;
	virtual void update(const float &dt) = 0;
	virtual void render(sf::RenderTarget * target = nullptr) = 0;
};

