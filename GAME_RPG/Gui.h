#pragma once
#include<iostream>



#include"SFML/Graphics.hpp"
#include"SFML/System.hpp"
#include"SFML/Window.hpp"
#include"SFML/Audio.hpp"
#include"SFML/Network.hpp"

enum button_states {
	BTN_IDLE = 0,
	BTN_HOVER, BTN_PRESSED
};

namespace gui {
	class Button
	{
	private:
		short unsigned buttonState;
		short unsigned id;
		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;

		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textPressedColor;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color pressedColor;

		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlinePressedColor;

	public:
		Button(float x, float y, float width, float height,
			sf::Font* font, std::string text, unsigned int character_size,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_pressed_color,
			sf::Color idle_Color, sf::Color hover_Color, sf::Color pressed_Color,
			sf::Color outline_idle_Color = sf::Color::Transparent, 
			sf::Color outline_hover_Color = sf::Color::Transparent, 
			sf::Color outline_pressed_Color = sf::Color::Transparent, 
			short unsigned id = 0);
		~Button();
		const bool isPressed() const;
		const std::string getText() const;
		const short unsigned& getId() const;
		void setText(const std::string text);
		void setId(const short unsigned id);
		void update(const sf::Vector2f& mousePos);
		void render(sf::RenderTarget& target);

	};

	class DropDownList
	{
	private:
		sf::Font& font; 
		bool showList;
		float keyTime;
		float keyTimeMax;

		gui:: Button* activeElement;
		std::vector<gui::Button *> list;

	public:
		DropDownList(float x, float y, float width, float height, sf::Font& font, std::string* list, unsigned numOfelements, unsigned defaukt_index = 0);
		~DropDownList();

		const unsigned short& getActiveElement() const;
		const bool getKeyTime();
		void updateKeyTime(const float& dt);
		void update(const sf::Vector2f& mousePos, const float& dt);
		void render(sf::RenderTarget& target);
	};
}

