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
	std::stack<State*>* states;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keyBinds;
	sf::RenderWindow* window;
	bool quit;
	
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	// Resources
	std::map<std::string, sf::Texture> textures;
	
	// Functions
	virtual void initKeyBinds() = 0;
public:
	State(sf::RenderWindow * window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~State(); 

	// Accessrors

	const bool& getQuit() const;

	void endState(); // Shouldn't get Overrided

	virtual void updateMousePositions();
	virtual void updateInput(const float &dt =0) = 0;
	virtual void update(const float &dt) = 0;
	virtual void render(sf::RenderTarget * target = nullptr) = 0;
};

