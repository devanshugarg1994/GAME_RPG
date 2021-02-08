#include "PauseMenu.h"



PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font)
	:font(font)
{
	this->background.setSize(sf::Vector2f(
		static_cast<float>(window.getSize().x),
		static_cast<float>(window.getSize().y)
	));

	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	this->continer.setSize(sf::Vector2f(
		static_cast<float>(window.getSize().x /4.f),
		static_cast<float>(window.getSize().y -100.f)
	));

	this->continer.setFillColor(sf::Color(20, 20, 20, 100));
	this->continer.setPosition(
		static_cast<float>(window.getSize().x) / 2.f - this->continer.getSize().x / 2.f,
	30.f);
	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
	this->menuText.setCharacterSize(60);
	this->menuText.setString("PAUSED");
	this->menuText.setPosition(this->continer.getPosition().x + this->continer.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
		this->continer.getPosition().y + 30.f);


}

PauseMenu::~PauseMenu()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}
}

std::map<std::string, gui::Button*>& PauseMenu::getButtons()
{
	return this->buttons;
}

const bool& PauseMenu::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

void PauseMenu::addButtons(const std::string key, float y, const std::string text)
{
	float width = 250.f;
	float height = 50.f;
	float x = this->continer.getPosition().x + this->continer.getSize().x / 2.f - width / 2.f;
	this->buttons[key] = new gui::Button(
		x, y, width, height, &this->font, text, 60,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

}

void PauseMenu::update(const sf::Vector2f& mousePos)
{
	for (auto& it : this->buttons)
	{
		it.second->update(mousePos);
	}
}

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->continer);
	for (auto& it : this->buttons) {
		it.second->render(target);
	}
	target.draw(this->menuText);
}
