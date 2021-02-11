#include "stdafx.h"

#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float dragFactor)
	: sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), dragFactor(dragFactor)
{
	this->maxVelocity = maxVelocity;
}

MovementComponent::~MovementComponent()
{

}

const float& MovementComponent::getMaxVelocity() const
{
	return this->maxVelocity;
}

const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}

const bool MovementComponent::getState(const short unsigned state) const
{
	switch (state)
	{
	case IDLE:
		if (this->velocity.x == 0.f && this->velocity.y == 0.f)
			return true;
		break;	
	case MOVING:
		if (this->velocity.x != 0.f || this->velocity.y != 0.f)
			return true;
		break;	
	case MOVING_LEFT:
		if (this->velocity.x < 0.f)
			return true;
		break;	
	case MOVING_RIGHT:
		if (this->velocity.x > 0.f)
			return true;
		break;
	case MOVING_UP:
		if (this->velocity.y < 0.f)
			return true;
		break;
	case MOVING_DOWN:
		if (this->velocity.y > 0.f)
			return true;
		break;
	default:
		break;
	}

	return false;
}



void MovementComponent::move(const float dir_x, const float dir_y, const float &dt)
{
	this->velocity.x += this->acceleration * dir_x;
	this->velocity.y += this->acceleration * dir_y;
}

void MovementComponent::update(const float& dt)
{
	// If entity is moving i.e.. it's position Vector is change using the `MovementComponent` component
	// We always decrease it's speed using dragFactor(Try to relate it with friction).

	//---------------------- For x direction------------------------------------------------------------

	// if we are moving in positive direction i.e.. right side.
	if (this->velocity.x > 0.f) {

		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = this->maxVelocity;

		this->velocity.x -= this->dragFactor;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0;
	}

	// if we are moving in negative direction i.e.. left side.
	else if (this->velocity.x < 0.f) {
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;

		this->velocity.x += this->dragFactor;
		if (this->velocity.x > 0.f)
			this->velocity.x = 0;
	}


	//---------------------- For y direction------------------------------------------------------------

	// if we are moving in poistive direction i.e.. upward direction.
	if (this->velocity.y > 0.f) {
		if (this->velocity.y > this->maxVelocity)
			this->velocity.y = this->maxVelocity;

		this->velocity.y -= this->dragFactor;
		if (this->velocity.y < 0.f)
			this->velocity.y = 0;
	}
	// if we are moving in negative direction i.e.. downward side.
	else if (this->velocity.y < 0.f) {
		if (this->velocity.y < -this->maxVelocity)
			this->velocity.y = -this->maxVelocity;

		this->velocity.y += this->dragFactor;
		if (this->velocity.y > 0.f)
			this->velocity.y = 0;
	}

	// Updating the position using SFML move function present on instance of `Sprite`
	this->sprite.move(this->velocity * dt);

}
