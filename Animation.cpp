#include "Animation.h"

namespace df {

	// Animation constructor
	Animation::Animation() {
		m_p_sprite = NULL;
		m_name = "";
		m_index = 0;
		m_slowdown_count = 0;
	}

	// Set associated Sprite to a new one.
	// Note, Sprite is managed by ResourceManager.
	// Set Sprite index to 0 (first frame).
	void Animation::setSprite(Sprite* p_new_sprite) {
		m_p_sprite = p_new_sprite;

		m_index = 0;
	}

	// Return pointer to associated Sprite.
	Sprite* Animation::getSprite() const {
		return m_p_sprite;
	}

	// Set Sprite name (in ResourceManager).
	void Animation::setName(std::string new_name) {
		m_name = new_name;
	}

	// Get Sprite name (in ResourceManager).
	std::string Animation::getName() const {
		return m_name;
	}

	// Set index of current Sprite frame to be displayed.
	void Animation::setIndex(int new_index) {
		m_index = new_index;
	}

	// Get index of current Sprite frame to be displayed.
	int Animation::getIndex() const {
		return m_index;
	}

	// Set animation slowdown count (-1 means stop animation).
	void Animation::setSlowdownCount(int new_slowdown_count) {
		m_slowdown_count = new_slowdown_count;
	}

	// Get animation slowdown count (-1 means stop animation).
	int Animation::getSlowdownCount() const {
		return m_slowdown_count;
	}

	// Draw single frame centered at position (x,y).
	// Drawing accounts for slowdown, and advances Sprite frame.
	// Return 0 if ok, else -1.
	int Animation::draw(Vector position) {

		// If sprite not defined, don't continue further.
		if (m_p_sprite == NULL) return -1;

		// Ask Sprite to draw current frame.
		int index = getIndex();
		m_p_sprite->draw(index, position);

		// If slowdown count is -1, then animation is frozen.
		if (getSlowdownCount() == -1)
			return 0;

		// Increment counter.
		int count = getSlowdownCount();
		count++;

		// advance sprite index, if appropriate.
		if (count >= m_p_sprite->getSlowdown()) {
			count = 0;	// Reset counter.
			index++;	// Advance frame.

			// If at last frame, loop to beginning.
			if (index >= m_p_sprite->getFrameCount())
				index = 0;

			// Set index for next draw().
			setIndex(index);
		}

		// Set counter for next draw().
		setSlowdownCount(count);

		return 0;
	}

	// Get bounding box of associated Sprite.
	Box Animation::getBox() const {

		// If no Sprite, return unit Box centered at (0,0).
		if (m_p_sprite == NULL) {
			Box box(Vector(-0.5, -0.5), 0.99, 0.99);
			return box;
		}

		// Create Box around centered Sprite.
		Vector corner(-1 * m_p_sprite->getWidth() / 2.0,
			-1 * m_p_sprite->getHeight() / 2.0);
		Box box(corner, m_p_sprite->getWidth(), m_p_sprite->getHeight());

		return box;
	}
}