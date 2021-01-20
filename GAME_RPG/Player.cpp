#include "Player.h"

void Player::initVariables()
{
}

void Player::initComponenets()
{
	this->createMovementComponent(200.f, 10.f, 5.f);
}

Player::Player(float x, float y,sf::Texture &texture)
{

	// As per now following point need to take for the order in which the function are called
	// 1. `initVariable` needed to be called first.  
	// 2. `setPosition` should called after `setTexture` as in Super class `Entity`
	//     position of sprite is set whose texture is set using `setTexture`.
	// 3.  `initComponenets` use to init  different components on player which may or may depend on the other initializations. 
	// 
	this->initVariables();
	this->setTexture(texture);
	this->setPosition(x, y);
	this->initComponenets();
}

Player::~Player()
{
}
