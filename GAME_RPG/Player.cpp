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
	// 3. `initComponenets` use to init  different components on player which may or may depend on the other initializations. 
	// 
	this->initVariables();
	//this->setTexture(texture_sheet); // if the player do not have multiple animation and the spritesheet contain only the character then we have to use it.
	this->setPosition(x, y);

	this->createHitBoxComponent(this->sprite, 0.f, 0.f, 64.f, 64.f);
	this->createMovementComponent(200.f, 10.f, 5.f);
	
	/** 
	*  Point to note here is that if the player has animations then textutre set by animation itself ie.. it will change on movement 
	*  But is not then we have to do it here. 
	*/
	this->createAnimationComponent(texture_sheet);
	this->animationComponent->addAnimation("WALK", 4.f, 4, 1, 7, 1, 64, 64); // @Todo: if we add new aniamtion to entity then for sigle updation iteration entity will set to first frame of the new animation which need to fix. 
	this->animationComponent->addAnimation("Back", 4.f, 12, 1, 15, 1, 64, 64);
	this->animationComponent->addAnimation("IDLE", 8.f, 0, 0, 8, 0, 64, 64);

}

Player::~Player()
{
}

void Player::debugFun()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		this->debug = true;
	}
}

void Player::updateAnimation(const float& dt)
{
	if (this->debug) {
		this->animationComponent->play("Back", dt, true);
		if (this->animationComponent->isDone("Back")) {
			this->debug = false;
		}
	}

	if (this->movementComponent->getState(IDLE)) {
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComponent->getState(MOVING_LEFT)) {
		this->sprite.setScale(1.0f, 1.0f);
		this->sprite.setOrigin(0, 0);

		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}

	else if (this->movementComponent->getState(MOVING_RIGHT)) {
		this->sprite.setScale(-1.0f, 1.0f);
		this->sprite.setOrigin(64, 0);

		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}

	else if (this->movementComponent->getState(MOVING_UP)) {
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());

	}
	else if (this->movementComponent->getState(MOVING_DOWN)) {
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());

	}
}

void Player::update(const float& dt)
{

	this->movementComponent->update(dt);
	this->debugFun();
	this->updateAnimation(dt);
	this->hitboxComponent->update(dt);

}
