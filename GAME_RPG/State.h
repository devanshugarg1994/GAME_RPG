#pragma once
#include "Entity.h"

class State
{
private: 
	
protected:
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::stack<State*>* states;
	bool quit;
	bool paused;
	std::map<std::string, int> keyBinds;
	float keyTime;
	float keyTimeMax;

	
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
	const bool& getKeyTime();
	void endState(); // Shouldn't get Overrided
	void pauseState();
	void unpauseState();

	virtual void updateMousePositions();
	virtual void updateKeyTime(const float &dt);
	virtual void updateInput(const float &dt =0) = 0;
	virtual void update(const float &dt) = 0;
	virtual void render(sf::RenderTarget * target = nullptr) = 0;
};

