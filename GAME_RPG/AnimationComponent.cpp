#include "AnimationComponent.h"



AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet)
	:sprite(sprite), textureSheet(texture_sheet), lastAnimation(nullptr)
{
}

AnimationComponent::~AnimationComponent()
{
	for (auto& i : this->animations) {
		delete i.second;
	}
}

void AnimationComponent::addAnimation(const std::string key, float animation_timer,
	 int start_frames_x,  int start_frames_y, 
	 int end_frames_x,  int end_frames_y, 
	float width, float height)
{
	this->animations[key] = new Animation(this->sprite, this->textureSheet, animation_timer,
		start_frames_x, start_frames_y,
		end_frames_x, end_frames_y, 
		width, height);
}

void AnimationComponent::play(const std::string key, const float& dt)
{
	if (this->lastAnimation != this->animations[key]) {
		if (this->lastAnimation == nullptr) {
			this->lastAnimation = this->animations[key];
		}
		else {
			this->lastAnimation->reset();
			this->lastAnimation = this->animations[key];
		}
	}
	this->animations[key]->play(dt);
}
