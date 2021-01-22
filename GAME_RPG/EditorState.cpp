#include "EditorState.h"


void EditorState::initVariables()
{
}



void EditorState::initfonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis_Light.ttf")) {
		throw("ERROR::MAINMENUSATAE::COULD NOTLOAD FONT");
	}
}

void EditorState::initButtons()
{


}

void EditorState::initKeyBinds()
{
	std::ifstream ifs("Config/editorStates_keyBinds.init");

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
		std::cout << "Error! In opening file `editorStates_keyBinds.init` ";
		std::cout << "at the path: `Config/editorStates_keyBinds.init` " << std::endl;
	}

	//	// Debugging purpose
	//for (auto i : this->keyBinds) {
	//	std::cout << i.first << " " << i.second << std::endl;
	//}

}

EditorState::EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initVariables();
	this->initfonts();
	this->initKeyBinds();
	this->initButtons();

}

EditorState::~EditorState()
{
	// 1) Vector is automatically destroyed when go out of scope but the memory is the vector is pointing in case if vector is a
	// collection of pointer we have to manually delete the object
	// 2) Here Vector object is sttaic object create on stack memeory so it get delted when go out of scope
	// 3) But in case keys second key is a pointer hence we have to maually delete it.
	for (auto it = this->buttons.begin(); it != this->buttons.end(); it++) {
		delete it->second;
	}


}



void EditorState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("Close"))))
		this->endState();
}

// button in the mainMenuState  handle on every updation cycle
void EditorState::updateButtons()
{
	for (auto& button : this->buttons) {
		button.second->update(this->mousePosView);
	}

}

void EditorState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
	this->updateButtons();
}

void EditorState::renderButtons(sf::RenderTarget* target)
{
	for (auto& button : this->buttons) {
		button.second->render(target);
	}

}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target) {
		//std::cout << "Warning! Targetted context is not passed" << std::endl;
		//std::cout<< "Using window context passed at State Abstarct class" <<std::endl;
		target = this->window;
	}

	this->renderButtons(target);

	// Mouse POsition for Debuging
	//sf::Text mousePos;
	//mousePos.setPosition(this->mousePosView.x, this->mousePosView.y - 50.f);
	//mousePos.setFont(this->font);
	//mousePos.setCharacterSize(12);
	//std::stringstream ss;
	//ss << this->mousePosView.x << " * " << this->mousePosView.y;
	//mousePos.setString(ss.str());
	//target->draw(mousePos);
}
