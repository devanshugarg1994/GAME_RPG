#include "stdafx.h"
#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet)
	:sprite(sprite), textureSheet(texture_sheet), lastAnimation(nullptr), priorityAnimation(nullptr)
{
}

AnimationComponent::~AnimationComponent()
{
	for (auto& i : this->animations) {
		delete i.second;
	}
}

const bool& AnimationComponent::isDone(std::string key) 
{
	return this->animations[key]->isDone();
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

// If animation get change to another animation then we reset the animation which is running, hence when we return to back that state it will start fresh. 
// If any animation which is running and we change the animation then direct conversion will look jittery.
// Hence if send priority = true then animation will only change when the priority end.
const bool& AnimationComponent::play(const std::string key, const float& dt, const bool priority)
{
	
	if (this->priorityAnimation) {
		if (this->priorityAnimation == this->animations[key]) {
			if (this->lastAnimation != this->animations[key]) {
				if (this->lastAnimation == nullptr) {
					this->lastAnimation = this->animations[key];
				}
				else {
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}
			if (this->animations[key]->play(dt)) {
				this->priorityAnimation = nullptr;
			}
		}

	}
	else {
		if (priority) {
			this->priorityAnimation = this->animations[key];
		}
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
	return this->animations[key]->isDone();

}
const bool& AnimationComponent::play(const std::string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority)

{
	if (this->priorityAnimation) {
		if (this->priorityAnimation == this->animations[key]) {
			if (this->lastAnimation != this->animations[key]) {
				if (this->lastAnimation == nullptr) {
					this->lastAnimation = this->animations[key];
				}
				else {
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}
			if (this->animations[key]->play(dt, abs(modifier / modifier_max))) {
				this->priorityAnimation = nullptr;
			}
		}

	}
	else {
		if (priority) {
			this->priorityAnimation = this->animations[key];
		}
		if (this->lastAnimation != this->animations[key]) {
			if (this->lastAnimation == nullptr) {
				this->lastAnimation = this->animations[key];
			}
			else {
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}
		this->animations[key]->play(dt, abs(modifier / modifier_max));

	}	
	return this->animations[key]->isDone();
}