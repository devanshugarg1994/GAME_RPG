#pragma once
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<stack>
#include<map>
#include<fstream>
#include<sstream>

#include "Entity.h"

class State
{
private: 
	
protected:
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keyBinds;
	sf::RenderWindow* window;
	std::vector<sf::Texture> textures;
	bool quit;
	
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	// Functions

	virtual void initKeyBinds() = 0;
public:
	State(sf::RenderWindow * window, std::map<std::string, int>* supportedKeys);
	virtual ~State(); 

	// Accessrors

	const bool& getQuit() const;
	virtual void checkForQuit();

	virtual void endState() = 0;
	virtual void updateMousePositions();
	virtual void updateInput(const float &dt =0) = 0;
	virtual void update(const float &dt) = 0;
	virtual void render(sf::RenderTarget * target = nullptr) = 0;
};

