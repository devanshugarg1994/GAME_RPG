#pragma once

#include"SFML/Graphics.hpp"
#include"SFML/System.hpp"
#include"SFML/Window.hpp"
#include"SFML/Audio.hpp"
#include"SFML/Network.hpp"

enum movement_states {IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_DOWN, MOVING_UP};

class MovementComponent
{
private:
	sf::Sprite &sprite;
	//`maxVelocity`is max speed which could be reached. When we press button then on every updation loop 'updateInput' at `GameState`
	// and direction, new speed is set and maximum speed is checked on the basis of input before actual update in velocity.
	// After that updation loop for MovementComponent is called and velocity is calculated
	// on Every call of update we reduce some speed using dragFactor 
	float maxVelocity;
	float acceleration;
	// `dragFactor` is variable that is used decrrease the speed continously(Act as friction here).
	float dragFactor;

	sf::Vector2f velocity;



public:
	MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float dragFactor);
	virtual ~MovementComponent();

	const sf::Vector2f& getVelocity() const;
	const bool getState(const short unsigned state) const;
	void move(const float dir_x, const float dir_y, const float& dt);
	void update(const float& dt);
};

