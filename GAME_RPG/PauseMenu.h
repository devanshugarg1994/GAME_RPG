#pragma once

#include"SFML/Graphics.hpp"
#include"SFML/System.hpp"
#include"SFML/Window.hpp"
#include"SFML/Audio.hpp"
#include"SFML/Network.hpp"

#include<string>
#include "Button.h"
class PauseMenu
{

private:
	sf::Font& font;
	sf::Text menuText;
	sf::RectangleShape background;
	sf::RectangleShape continer;

	std::map<std::string, Button*> buttons;
public: 
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	virtual ~PauseMenu();

	//Functions

	std::map<std::string, Button*>& getButtons();
	const bool& isButtonPressed(const std::string key);
	void addButtons(const std::string key, float y , const std::string text);
	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderTarget& target);

};

