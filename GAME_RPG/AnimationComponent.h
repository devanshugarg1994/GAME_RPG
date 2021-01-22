#pragma once
#include<iostream>
#include<map>
#include<string>


#include"SFML/Graphics.hpp"
#include"SFML/System.hpp"
#include"SFML/Window.hpp"
#include"SFML/Audio.hpp"
#include"SFML/Network.hpp"
class AnimationComponent
{
private:
	class Animation
	{

	public:
		//Variables
		sf::Sprite& sprite;
		sf::Texture& textureSheet;
		float animationTimer;
		float width;
		float height;
		sf::IntRect startRect;
		sf::IntRect currentRect;
		sf::IntRect endRect;
		float timer;
		Animation(sf::Sprite& sprite, sf::Texture& texture_sheet,
			float animation_timer,  int start_frames_x,  int start_frames_y,
			 int end_frames_x,  int end_frames_y, float width, float height)
			:sprite(sprite), textureSheet(texture_sheet), animationTimer(animation_timer), width(width), height(height)
		{
			this->startRect = sf::IntRect(start_frames_x * width, start_frames_y * height, width, height);
			this->endRect = sf::IntRect(end_frames_x * width, end_frames_y * height, width, height);
			this->timer = 0.f;
			this->currentRect = this->startRect;
			this->sprite.setTexture(this->textureSheet, true);
			this->sprite.setTextureRect(this->startRect);
		}

		// Functions
		void play(const float& dt) {
			this->timer += 10.f * dt;
			if (this->timer >= this->animationTimer) {
				this->timer = 0.f;

				if (this->currentRect != this->endRect) {
					this->currentRect.left += this->width;
				}
				else {
					this->currentRect.left = this->startRect.left;
				}
				this->sprite.setTextureRect(this->currentRect);
			}
		}

		void reset() {
			this->currentRect = this->startRect;
			this->timer = 0.f;
		}


	};

	sf::Sprite& sprite;
	sf::Texture& textureSheet;

	std::map<std::string, Animation*> animations;
	Animation* lastAnimation;
public:
	AnimationComponent(sf::Sprite& sprite, sf::Texture &texture_sheet);
	virtual ~AnimationComponent();

	// Functions
	void addAnimation(const std::string key, float animation_timer,
				 int start_frames_x,  int start_frames_y, 
				 int end_frames_x,  int end_frames_y, 
				float width, float height);
	void play(const std::string key, const float& dt);
};

