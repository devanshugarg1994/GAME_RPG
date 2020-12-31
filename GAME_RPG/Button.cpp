#include "Button.h"



Button::Button(float x, float y, float width, float height, sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color pressedColor)
{
	this->buttonState = BTN_IDLE;
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setPosition(sf::Vector2f(x, y));
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(12);
	
	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->pressedColor = pressedColor;

	this->shape.setFillColor(this->idleColor);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);
}

Button::~Button()
{
}

const bool Button::isPressed() const
{
	if(this->buttonState == BTN_PRESSED)
		return true;
	return false;
}



void Button::update(sf::Vector2f mousePos)
{
	//Hover
	if (this->shape.getGlobalBounds().contains(mousePos)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->buttonState = BTN_PRESSED;
			this->shape.setFillColor(this->pressedColor);
		}
		else
		{
			this->buttonState = BTN_HOVER;
			this->shape.setFillColor(this->hoverColor);
		}
	}
	else {
		this->buttonState = BTN_IDLE;
		this->shape.setFillColor(this->idleColor);
	}
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->text);
}
