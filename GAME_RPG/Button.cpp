#include "Button.h"



Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned int character_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_pressed_color,
	sf::Color idle_Color, sf::Color hover_Color, sf::Color pressed_Color)
{

	this->idleColor = idle_Color;
	this->hoverColor = hover_Color;
	this->pressedColor = pressed_Color;

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textPressedColor = text_pressed_color;


	this->buttonState = BTN_IDLE;
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setFillColor(this->idleColor);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(character_size);
	


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
			this->text.setFillColor(this->textPressedColor);

		}
		else
		{
			this->buttonState = BTN_HOVER;
			this->shape.setFillColor(this->hoverColor);
			this->text.setFillColor(this->textHoverColor);
		}
	}
	else {
		this->buttonState = BTN_IDLE;
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);

	}
}

void Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}
