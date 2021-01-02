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

GameState::GameState(sf::RenderWindow * window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initKeyBinds();
}

GameState::~GameState()
{
}

void GameState::endState()
{
	std::cout << "End State" << std::endl;
}

void GameState::updateInput(const float& dt)
{
	this->checkForQuit();

	//Update Player movement (TODO :Things related to player should be in player class)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_LEFT"))))
		this->player.move(dt, -1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_RIGHT"))))
		this->player.move(dt, 1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_DOWN"))))
		this->player.move(dt, 0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_UP"))))
		this->player.move(dt, 0.f, 1.f);
}

void GameState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
	this->player.update(dt);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target) {
		//std::cout << "Warning! Targetted context is not passed" << std::endl;
		//std::cout<< "Using window context passed at State Abstarct class" <<std::endl;
		target = this->window;
	}

	this->player.render(target);
}
