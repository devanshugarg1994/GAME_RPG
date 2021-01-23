#pragma once

#include <iostream>

#include"SFML/Graphics.hpp"
#include"SFML/System.hpp"
#include"SFML/Window.hpp"
#include"SFML/Audio.hpp"
#include"SFML/Network.hpp"
class HitboxComponent
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	float offsetX;
	float offsetY;

public:
	HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height );
	virtual ~HitboxComponent();

	bool checkIntersect(const sf::FloatRect& frect);
	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

