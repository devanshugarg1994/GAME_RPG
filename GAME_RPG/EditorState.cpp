#include "stdafx.h"

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

void EditorState::initPauseMenu()
{
	this->pMenu = new PauseMenu(*this->window, this->font);
	this->pMenu->addButtons("QUIT", 250.f, "Quit");
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

void EditorState::initGui()
{
	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
	this->selectorRect.setFillColor(sf::Color::Transparent);
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::Green);
}

void EditorState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 10, 10);
}

EditorState::EditorState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initfonts();
	this->initKeyBinds();
	this->initButtons();
	this->initPauseMenu();
	this->initGui();
	this->initTileMap();

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
	delete this->pMenu;

	delete this->tileMap;



}



void EditorState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("Close"))) && this->getKeyTime())
		if (!this->paused) {
			this->pauseState();
		}
		else {
			this->unpauseState();
		}
}

// button in the mainMenuState  handle on every updation cycle
void EditorState::updateButtons()
{
	for (auto& button : this->buttons) {
		button.second->update(this->mousePosView);
	}

}

void EditorState::updateGUI()
{
	this->selectorRect.setPosition(this->mousePosView);
}

void EditorState::updatePauseButtons()
{
	if (this->pMenu->isButtonPressed("QUIT")) {
		this->endState();
	}
}

void EditorState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateKeyTime(dt);
	this->updateInput(dt);
	this->updatePauseButtons();
	if (!this->paused) {
		this->updateButtons();
		this->updateGUI();

	}
	else {
		this->pMenu->update(this->mousePosView);
		this->updatePauseButtons();
	}

}

void EditorState::renderButtons(sf::RenderTarget& target)
{
	for (auto& button : this->buttons) {
		button.second->render(target);
	}

}

void EditorState::renderGui(sf::RenderTarget& target)
{
	target.draw(this->selectorRect);
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}
	// Rendering Button used in State
	this->renderButtons(*target);
	this->renderGui(*target);
	this->tileMap->render(*target);
	// Rendering Pause Menu When `Escape` key is pressed which is bind with Quit functionality which end the state.
	if (this->paused) {
		this->pMenu->render(*target);
	}
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
