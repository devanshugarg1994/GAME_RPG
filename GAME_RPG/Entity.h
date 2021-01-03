#pragma once

#include"SFML/Graphics.hpp"
#include"SFML/System.hpp"
#include"SFML/Window.hpp"
#include"SFML/Audio.hpp"
#include"SFML/Network.hpp"
class Entity
{
private:
	void initVaribles();
protected:
	sf::Texture* texture;
	sf::Sprite *sprite;

	float movementSpeed;

public:
	Entity();
	virtual ~Entity();
	//Components function
	void createSprite(sf::Texture* texture);
	
	//Functions
	virtual void move(const float& dt, const float dir_x, const float dir_y);
	virtual void setPosition(const float x, const float y);
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target = NULL);
};



