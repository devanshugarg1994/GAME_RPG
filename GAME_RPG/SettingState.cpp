#include "SettingState.h"


void SettingState::initVariables()
{
	this->modes = sf::VideoMode::getFullscreenModes();
}

void SettingState::initBackgrounds()
{
	this->background.setSize(sf::Vector2f(
		static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y))
	);

	if (!this->backgroundTexture.loadFromFile("BG.png")) {
		throw ("ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE");
	}
	this->background.setTexture(&this->backgroundTexture);
}

void SettingState::initfonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis_Light.ttf")) {
		throw("ERROR::MAINMENUSATAE::COULD NOTLOAD FONT");
	}
}

void SettingState::initButtons()
{
	this->buttons["APPLY"] = new gui::Button(300, 900, 150, 50, &this->font, "Apply", 32,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["BACK"] = new gui::Button(600, 900, 150, 50, &this->font, "Back", 32,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

void SettingState::initGUI()
{
	std::vector<std::string> modes_str;
	for (auto& i : this->modes) {
		modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}
	this->dropDownList["RESOLUTION"] = new gui::DropDownList(450.f, 400.f, 200.f, 50.f, font, modes_str.data(), modes_str.size());
}

void SettingState::initText()
{
	this->optionsText.setFont(this->font);
	this->optionsText.setPosition(sf::Vector2f(100.f, 100.f));

	this->optionsText.setCharacterSize(30);
	this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));


	this->optionsText.setString("Resolution \nFullScreen \nAntialiasing");
}

void SettingState::initKeyBinds()
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

	//	// Debugging purpose
	//for (auto i : this->keyBinds) {
	//	std::cout << i.first << " " << i.second << std::endl;
	//}

}

SettingState::SettingState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackgrounds();
	this->initfonts();
	this->initKeyBinds();
	this->initButtons();
	this->initGUI();
	this->initText();

}

SettingState::~SettingState()
{
	// 1) Vector is automatically destroyed when go out of scope but the memory is the vector is pointing in case if vector is a
	// collection of pointer we have to manually delete the object
	// 2) Here Vector object is sttaic object create on stack memeory so it get delted when go out of scope
	// 3) But in case keys second key is a pointer hence we have to maually delete it.
	for (auto it = this->buttons.begin(); it != this->buttons.end(); it++) {
		delete it->second;
	}
	for (auto it = this->dropDownList.begin(); it != this->dropDownList.end(); it++) {
		delete it->second;
	}
}



void SettingState::updateInput(const float& dt)
{

}

void SettingState::updateGUI(const float& dt)
{
	for (auto& it : this->dropDownList)
	{
		it.second->update(this->mousePosView, dt);
	}
}

// button in the mainMenuState  handle on every updation cycle
void SettingState::updateButtons()
{
	for (auto& button : this->buttons) {
		button.second->update(this->mousePosView);
	}

	if (this->buttons["BACK"]->isPressed()) {
		this->endState();
	}

	if (this->buttons["APPLY"]->isPressed()) {
		this->window->create(this->modes[this->dropDownList["RESOLUTION"]->getActiveElement()], "test", sf::Style::Default);
	}


}

void SettingState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
	this->updateButtons();
	this->updateGUI(dt);

}

void SettingState::renderGUI(sf::RenderTarget& target)
{
	for (auto& list : this->dropDownList) {
		list.second->render(target);
	}
}

void SettingState::renderButtons(sf::RenderTarget& target)
{
	for (auto& button : this->buttons) {
		button.second->render(target);
	}
}

void SettingState::render(sf::RenderTarget* target)
{
	if (!target) {
		//std::cout << "Warning! Targetted context is not passed" << std::endl;
		//std::cout<< "Using window context passed at State Abstarct class" <<std::endl;
		target = this->window;
	}

	target->draw(this->background);
	this->renderButtons(*target);
	this->renderGUI(*target);
	target->draw(this->optionsText);
	// Mouse POsition for Debuging
	sf::Text mousePos;
	mousePos.setPosition(this->mousePosView.x, this->mousePosView.y - 50.f);
	mousePos.setFont(this->font);
	mousePos.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " * " << this->mousePosView.y;
	mousePos.setString(ss.str());
	target->draw(mousePos);
}
