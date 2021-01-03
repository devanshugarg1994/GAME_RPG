#include "Player.h"

void Player::initVariables()
{
}

void Player::initComponenets()
{
}

Player::Player(float x, float y,sf::Texture *texture)
{
	this->initVariables();
	this->initComponenets();
	this->createSprite(texture);
	this->setPosition(x, y);
}

Player::~Player()
{
}
