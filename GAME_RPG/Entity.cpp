#include "Entity.h"

void Entity::initVaribles()
{
	this->movementComponent = nullptr;
	this->animationComponent = nullptr;
	this->hitboxComponent = nullptr;
}

Entity::Entity()
{
	this->initVaribles();
}

Entity::~Entity()
{
	delete this->movementComponent;
	delete this->animationComponent;
	delete this->hitboxComponent;
}

void Entity::setTexture(sf::Texture& texture_sheet)
{
	this->sprite.setTexture(texture_sheet);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float dragFactor)
{
	this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration,  dragFactor);
}

void Entity::createAnimationComponent(sf::Texture& texture_sheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

void Entity::createHitBoxComponent(sf::Sprite& sprite, const float offset_x, const float offset_y, const float width, const float height)
{
	this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
	if (this->movementComponent) {
		this->movementComponent->move(dir_x, dir_y, dt); // setting the direction on basis of key pressed
	}
}

void Entity::setPosition(const float x, const float y)
{
		this->sprite.setPosition(x, y);
}

void Entity::update(const float& dt)
{


}

void Entity::render(sf::RenderTarget& target)
{
		target.draw(this->sprite);

		if (this->hitboxComponent) {
			this->hitboxComponent->render(target);
		}

}


