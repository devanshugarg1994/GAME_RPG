#include "MainMenuState.h"

void MainMenuState::initfonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis_Light.ttf")) {
		throw("ERROR::MAINMENUSATAE::COULD NOTLOAD FONT");
	}
}

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new Button(100, 100, 150, 50, &this->font, "Game Start", sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 100));

	this->buttons["EXIT_BUTTON"] = new Button(100, 300, 150, 50,
		&this->font, "Quit", sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 100));

}

void MainMenuState::initKeyBinds()
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

		// Debugging purpose
	for (auto i : this->keyBinds) {
		std::cout << i.first << " " << i.second << std::endl;
	}

}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initfonts();
	this->initKeyBinds();
	this->initButtons();
	this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	this->background.setFillColor(sf::Color::Magenta);
}

MainMenuState::~MainMenuState()
{
	// 1) Vector is automatically destroyed when go out of scope but the memory is the vector is pointing in case if vector is a
	// collection of pointer we have to manually delete the object
	// 2) Here Vector object is sttaic object create on stack memeory so it get delted when go out of scope
	// 3) But in case keys second key is a pointer hence we have to maually delete it.
	for (auto it = this->buttons.begin(); it != this->buttons.end(); it++) {
		delete it->second;
	}


}

void MainMenuState::endState()
{
	std::cout << "End State" << std::endl;
}

void MainMenuState::updateInput(const float& dt)
{
	this->checkForQuit();

}

// button in the mainMenuState  handle on ecery updaion cycle
void MainMenuState::updateButtons()
{
	for (auto& button : this->buttons) {
		button.second->update(this->mousePosView);
	}
	if (this->buttons["GAME_STATE"]->isPressed()) {
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	}
	if (this->buttons["EXIT_BUTTON"]->isPressed()) {
		this->quit = true;
	}
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
	this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto& button : this->buttons) {
		button.second->render(target);
	}

}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target) {
		//std::cout << "Warning! Targetted context is not passed" << std::endl;
		//std::cout<< "Using window context passed at State Abstarct class" <<std::endl;
		target = this->window;
	}

	target->draw(this->background);
	this->renderButtons(target);
}