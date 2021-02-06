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

	//	// Debugging purpose
	//for (auto i : this->keyBinds) {
	//	std::cout << i.first << " " << i.second << std::endl;
	//}

}

void GameState::initfonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis_Light.ttf")) {
		throw("ERROR::MAINMENUSATAE::COULD NOTLOAD FONT");
	}
}
void GameState::initPauseMenu()
{
	this->pMenu = new PauseMenu(*this->window, this->font);
	this->pMenu->addButtons("QUIT", 250.f, "Quit");
}
void GameState::initTextures()
{
	sf::Texture temp;
	temp.loadFromFile("Resources/Images/Sprites/Player/PLAYER_SHEET2.png");
	this->textures["PLAYER_IDLE"] = temp;
}

void GameState::initPlayers()
{
	this->player = new Player(0, 0, this->textures["PLAYER_IDLE"]);
}

GameState::GameState(sf::RenderWindow * window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initKeyBinds();
	this->initfonts();
	this->initPauseMenu();
	this->initTextures();
	this->initPlayers();
}

GameState::~GameState()
{
	delete this->pMenu;
	delete this->player;
}



void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("Close"))) && this->getKeyTime())
		if (!this->paused) {
			this->pauseState();
		}
		else {
			this->unpauseState();
		}
	}


void GameState::updatePlayerInput(const float& dt)
{
	
	// for quiting the state we can press Escape

	//Update Player movement (TODO :Things related to player should be in player class)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_LEFT"))))
		this->player->move(-1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_RIGHT"))))
		this->player->move(1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_DOWN"))))
		this->player->move(0.f, 1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_UP"))))
		this->player->move(0.f, -1.f, dt);

}
void GameState::updatePauseButtons()
{
	if (this->pMenu->isButtonPressed("QUIT"))
	{
		this->endState();
	}
}
// If pause we do not update the scene.
void GameState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateKeyTime(dt);
	this->updateInput(dt);

	if (!this->paused) {
		this->updatePlayerInput(dt);
		this->player->update(dt);
	}
	else {
		this->pMenu->update(this->mousePosView);
		this->updatePauseButtons();
	}

}

// If paused then we stop updating but render the scene.
void GameState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}
	this->player->render(*target);

	if (this->paused) {
		this->pMenu->render(*target);
	}
}
