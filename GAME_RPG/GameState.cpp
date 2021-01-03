#include "GameState.h"

void GameState::initKeyBinds()
{
	std::ifstream ifs("Config/gameStates_keyBinds.init");

	if (ifs.is_open()) {

		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2) {
			this->keyBinds[key] = this->supportedKeys->at(key2);
		}
		//Closing file
		ifs.close();
	}
	else {
		std::cout << "Error! In opening file `gameStates_keyBinds.init` ";
		std::cout << "at the path: `Config/gameStates_keyBinds.init` " << std::endl;
	}

	// Debugging

		// Debugging purpose
	for (auto i : this->keyBinds) {
		std::cout << i.first << " " << i.second << std::endl;
	}

}

void GameState::initTextures()
{
	sf::Texture temp;
	temp.loadFromFile("Resources/Images/Sprites/Player/Mario.png");
	this->textures["PLAYER_IDLE"] = temp;
}

void GameState::initPlayers()
{
	this->player = new Player(0, 0, &this->textures["PLAYER_IDLE"]);
}

GameState::GameState(sf::RenderWindow * window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initKeyBinds();
	this->initTextures();
	this->initPlayers();
}

GameState::~GameState()
{
	delete this->player;
}



void GameState::updateInput(const float& dt)
{
	
	// for quiting the state we can press Escape

	//Update Player movement (TODO :Things related to player should be in player class)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_LEFT"))))
		this->player->move(dt, -1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_RIGHT"))))
		this->player->move(dt, 1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_DOWN"))))
		this->player->move(dt, 0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_UP"))))
		this->player->move(dt, 0.f, 1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("Close"))))
		this->endState();
}

void GameState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
	this->player->update(dt);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}

	this->player->render(target);
}
