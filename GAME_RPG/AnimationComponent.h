#pragma once


/** AnimationComponent class contain an inner class `Aniamtion` which will be actually update the frame according to the `animtion_timer`
	AnimationComponent act as manager which hold all animation refernces as a key value pair relted to entity.
	This key-value pair is used to play animation and update animation according to entity intreaction with world.

*/
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
		bool done;

		Animation(sf::Sprite& sprite, sf::Texture& texture_sheet,
			float animation_timer,  int start_frames_x,  int start_frames_y,
			 int end_frames_x,  int end_frames_y, float width, float height)
				:sprite(sprite), textureSheet(texture_sheet), animationTimer(animation_timer), width(width), height(height),
				  timer(0.f) , done(false)
		{
			this->startRect = sf::IntRect(start_frames_x * width, start_frames_y * height, width, height);
			this->endRect = sf::IntRect(end_frames_x * width, end_frames_y * height, width, height);
			this->timer = 0.f;
			this->currentRect = this->startRect;
			this->sprite.setTexture(this->textureSheet, true);
			this->sprite.setTextureRect(this->startRect);
		}

		const bool& isDone() const {
			return this->done;
		}

		// Actual function which  is called on every updation loop which is responsible for changing the frame 
		// of the animation using provided textutre.
		// which animation frame need change  among the associated animation with entity is decided by  entity or it's subclasses
		const bool& play(const float& dt) {
			this->done = false;
			this->timer += 100.f * dt;
			if (this->timer >= this->animationTimer) {
				this->timer = 0.f;

				// Animate
				if (this->currentRect != this->endRect) {
					this->currentRect.left += this->width;
				}
				//reset
				else {
					this->currentRect.left = this->startRect.left;
					this->done = true;
				}
				this->sprite.setTextureRect(this->currentRect);
			}
			return this->done;
		}

		const bool& play(const float& dt, float modifier_percentage) {
			this->done = false;

			this->timer += modifier_percentage * 100.f * dt;
			if (this->timer >= this->animationTimer) {
				this->timer = 0.f;

				if (this->currentRect != this->endRect) {
					this->currentRect.left += this->width;
				}
				else {
					this->currentRect.left = this->startRect.left;
					this->done = true;
				}
				this->sprite.setTextureRect(this->currentRect);
			}
			return this->done;

		}

		void reset() {
			this->currentRect = this->startRect;
			this->timer = this->animationTimer;
		}


	};

	sf::Sprite& sprite;
	sf::Texture& textureSheet;

	std::map<std::string, Animation*> animations;
	Animation* lastAnimation;
	Animation* priorityAnimation;
public:
	AnimationComponent(sf::Sprite& sprite, sf::Texture &texture_sheet);
	virtual ~AnimationComponent();

	const bool& isDone(std::string key);

	// Functions
	void addAnimation(const std::string key, float animation_timer,
				 int start_frames_x,  int start_frames_y, 
				 int end_frames_x,  int end_frames_y, 
				 float width, float height);
	const bool& play(const std::string key, const float& dt, const bool priority = false);
	const bool& play(const std::string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority = false);
};

