#include "Sound.h"

namespace df {

	Sound::Sound() {
		m_p_sound = NULL;
		m_label = "";
	}

	Sound::~Sound() {
		if (m_p_sound == NULL)
			delete(m_p_sound);
	}

	// Load sound buffer from file.
	// Return 0 if ok, else -1.
	int Sound::loadSound(std::string filename) {
		if (m_sound_buffer.loadFromFile(filename) == false) return -1;

		m_p_sound = new sf::Sound(m_sound_buffer);

		return 0;
	}

	// Set label associated with sound.
	void Sound::setLabel(std::string new_label) {
		m_label = new_label;
	}

	// Get label associated with sound.
	std::string Sound::getLabel() const {
		return m_label;
	}

	// Play sound.
	// If loop is true, repeat play when done.
	void Sound::play(bool loop) {
		m_p_sound->setLooping(loop);
		m_p_sound->play();
	}

	// Stop sound.
	void Sound::stop() {
		m_p_sound->stop();
	}

	// Pause sound.
	void Sound::pause() {
		m_p_sound->pause();
	}

	// Return SFML sound.
	sf::Sound Sound::getSound() const {
		return *m_p_sound;
	}
}