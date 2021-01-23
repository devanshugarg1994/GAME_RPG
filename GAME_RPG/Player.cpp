#include "Player.h"

void Player::initVariables()
{
}

void Player::initComponenets()
{
	this->createMovementComponent(200.f, 10.f, 5.f);
}

Player::Player(float x, float y,sf::Texture& texture_sheet)
{

	// As per now following point need to take for the order in which the function are called
	// 1. `initVariable` needed to be called first.  
	// 2. `setPosition` should called after `setTexture` as in Super class `Entity`
	//     position of sprite is set whose texture is set using `setTexture`.
	// 3.  `initComponenets` use to init  different components on player which may or may depend on the other initializations. 
	// 
	this->initVariables();
	//this->setTexture(texture_sheet); // if the player do not have multiple animation and the spritesheet contain only the character then we have to use it.
	this->setPosition(x, y);

	this->createHitBoxComponent(this->sprite, 0.f, 0.f, 64, 64);
	this->createMovementComponent(200.f, 10.f, 5.f);
	
	/** 
	*  Point to note here is that if the player has animations then textutre set by animation itself ie.. it will change on movement 
	*  But is not then we have to do it here. 
	*/
	this->createAnimationComponent(texture_sheet);
	this->animationComponent->addAnimation("IDLE_LEFT", 9.f, 0, 0, 8, 0, 64, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 4.f, 0, 1, 3, 1, 64, 64);
}

Player::~Player()
{
}

void Player::update(const float& dt)
{
	this->movementComponent->update(dt);
	if (this->movementComponent->getState(IDLE)) {
		this->animationComponent->play("IDLE_LEFT", dt);
	}
	else if(this->movementComponent->getState(MOVING_LEFT)) {
		this->animationComponent->play("WALK_LEFT", dt);

	}

	if (this->hitboxComponent) {
		this->hitboxComponent->update(dt);
	}

}
