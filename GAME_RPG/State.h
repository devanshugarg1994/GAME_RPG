#pragma once
#include "Player.h"
#include "GraphicsSetting.h"
class Player;
class State;
class StateData {
public:
	StateData() {
		//

	};
	float gridSize;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::stack<State*>* states;
	GraphicsSetting* gSetting;

};
class State
{
private: 
	
protected:
	StateData* stateData;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::stack<State*>* states;
	bool quit;
	bool paused;
	std::map<std::string, int> keyBinds;
	float keyTime;
	float keyTimeMax;
	float gridSize;
	
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	// Resources
	std::map<std::string, sf::Texture> textures;
	
	// Functions
	virtual void initKeyBinds() = 0;
public:
	State(StateData* state_data);
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

