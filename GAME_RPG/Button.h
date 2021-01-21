#pragma once
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<sstream>


#include"SFML/Graphics.hpp"
#include"SFML/System.hpp"
#include"SFML/Window.hpp"
#include"SFML/Audio.hpp"
#include"SFML/Network.hpp"

enum button_states {
	BTN_IDLE = 0,
	BTN_HOVER, BTN_PRESSED
};
class Button
{
private:
	short unsigned buttonState;
	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color textIdleColor;
	sf::Color textHoverColor;
	sf::Color textPressedColor;


	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color pressedColor;

public:
	Button(float x, float y, float width, float height,
		sf::Font* font, std::string text, unsigned int character_size,
		sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_pressed_color,
		sf::Color idleColor, sf::Color hoverColor, sf::Color pressedColor);
	~Button();
	const bool isPressed() const;
	void update(sf::Vector2f mousePos);
	void render(sf::RenderTarget *target);

};

