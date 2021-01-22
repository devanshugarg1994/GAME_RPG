#pragma once

#include "MovementComponent.h"
#include "AnimationComponent.h"

class Entity
{
private:
	void initVaribles();
protected:
	sf::Sprite sprite;

	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;
public:
	Entity();
	virtual ~Entity();
	//Components function
	void setTexture(sf::Texture& texture_sheet);
	void createMovementComponent(float maxVelocity, const float acceleration, const float dragFactor); 
	void createAnimationComponent(sf::Texture& texture_sheet);
	//Functions
	virtual void move(const float dir_x, const float dir_y, const float& dt);
	virtual void setPosition(const float x, const float y);
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target = NULL);
};



