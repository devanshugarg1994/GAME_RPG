#include "stdafx.h"

#include "Gui.h"

gui::Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned int character_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_pressed_color,
	sf::Color idle_Color, sf::Color hover_Color, sf::Color pressed_Color,
	sf::Color outline_idle_Color, sf::Color outline_hover_Color, sf::Color outline_pressed_Color, short unsigned id)

{
	this->id = id;

	this->idleColor = idle_Color;
	this->hoverColor = hover_Color;
	this->pressedColor = pressed_Color;

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textPressedColor = text_pressed_color;


	this->outlineIdleColor = outline_idle_Color;
	this->outlineHoverColor = outline_hover_Color;
	this->outlinePressedColor = outline_pressed_Color;

	this->buttonState = BTN_IDLE;
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setFillColor(this->idleColor);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(this->outlineIdleColor);

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

gui::Button::~Button()
{

}

const bool gui::Button::isPressed() const
{
	if(this->buttonState == BTN_PRESSED)
		return true;
	return false;
}

const std::string gui::Button::getText() const
{
	return this->text.getString();
}

const short unsigned& gui::Button::getId() const
{
	return this->id;

}

void gui::Button::setText(const std::string text)
{
	this->text.setString(sf::String(text));
}

void gui::Button::setId(const short unsigned id)
{
	this->id = id;
}



void gui::Button::update(const sf::Vector2f& mousePos)
{
	//Hover
	if (this->shape.getGlobalBounds().contains(mousePos)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->buttonState = BTN_PRESSED;
			this->shape.setFillColor(this->pressedColor);
			this->text.setFillColor(this->textPressedColor);
			this->shape.setOutlineColor(this->outlinePressedColor);
		}
		else
		{
			this->buttonState = BTN_HOVER;
			this->shape.setFillColor(this->hoverColor);
			this->text.setFillColor(this->textHoverColor);
			this->shape.setOutlineColor(this->outlineHoverColor);
		}
	}
	else {
		this->buttonState = BTN_IDLE;
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);
		this->shape.setOutlineColor(this->outlineIdleColor);
	}
}

void gui::Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}

//----------------------------------DropDownList---------------------------

gui::DropDownList::DropDownList(float x, float y, float width, float height, sf::Font& font, std::string* list, unsigned numOfelements, unsigned default_index)
	:font(font), showList(false), keyTimeMax(10.f), keyTime(0.f)
{
	this->activeElement = new gui::Button(x, y, width, height, &this->font, list[default_index], 12,
		sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
		sf::Color(225, 225, 225, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50)
	);
	for (int i= 0; i < numOfelements; i++) {
		this->list.push_back(
			new gui::Button(x , (y  + (height * i + 1)), width , height, &this->font, list[i], 12,
				sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
				sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
				sf::Color(225, 225, 225, 0), sf::Color(255, 255, 255, 0), sf::Color(20, 20, 20, 0), 
				i
			));
	}
}

gui::DropDownList::~DropDownList()
{
	delete this->activeElement;
	for (auto*& it : this->list) {
		delete it;
	}
}

const unsigned short& gui::DropDownList::getActiveElement() const
{
	return this->activeElement->getId();
}

const bool gui::DropDownList::getKeyTime()
{
	if (this->keyTime >= this->keyTimeMax)
	{
		this->keyTime = 0.f;
		return true;
	}
	return false;
}

void gui::DropDownList::updateKeyTime(const float& dt)
{
	if (this->keyTime <= this->keyTimeMax)
	{
		this->keyTime += 10.f * dt;
	}

}

void gui::DropDownList::update(const sf::Vector2f& mousePos, const float& dt)
{
	this->updateKeyTime(dt);
	this->activeElement->update(mousePos);
	if (this->activeElement->isPressed() && this->getKeyTime()) {
		if (this->showList) {
			this->showList = false;
		}
		else {
			this->showList = true; 
		}
	}
	if (this->showList) {
		for (auto& it : this->list)
		{
			it->update(mousePos);

			if (it->isPressed() && this->getKeyTime()) {
				this->showList = false;
				this->activeElement->setText(it->getText());
				this->activeElement->setId(it->getId());
			}
		}
	}

}

void gui::DropDownList::render(sf::RenderTarget& target)
{
	this->activeElement->render(target);
	if (this->showList) {
		for (auto& it : this->list)
		{
			it->render(target);
		}
	}
}
