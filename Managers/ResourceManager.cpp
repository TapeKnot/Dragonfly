#include <iostream>
#include <fstream>
#include <ctype.h>

using std::cout;
using std::endl;

#include "ResourceManager.h"
#include "LogManager.h"
#include "../Testing/Testing.h"
#include "../utility.h"

namespace df {

	ResourceManager::ResourceManager() {
		setType("ResourceManager");

		m_sprite_count = 0;
	}

	ResourceManager& ResourceManager::getInstance() {
		static ResourceManager single;
		return single;
	}

	// Get ResourceManager ready to manager for resources.
	int ResourceManager::startUp() {
		m_sprite_count = 0;

		Manager::startUp();

		return 0;
	}

	// Shut down ResourceManager, freeing up any allocated Sprites.
	void ResourceManager::shutDown() {
		for (int i = 0; i < m_sprite_count; i++) {
			if (m_p_sprite[i] != NULL)
				delete(m_p_sprite[i]);
		}

		m_sprite_count = 0;

		Manager::shutDown();
	}

	// Load Sprite from file.
	// Assign indicated label to sprite.
	// Return 0 if ok, else -1.
	int ResourceManager::loadSprite(std::string filename, std::string label) {
		// Check if room in array.
		if (m_sprite_count == MAX_SPRITES) {	// Sprite array full?
			printf("\tERROR\t: ResourceManager.loadSprite() - Sprite array full (%d / %d).\n", m_sprite_count, MAX_SPRITES);
			LM.writeLog(ts::TEST_LOG_LEVEL, "\tERROR\t: ResourceManager.loadSprite() - Sprite array full (%d / %d).\n", m_sprite_count, MAX_SPRITES);
			return -1;
		}

		std::ifstream file(filename);

		// Open file.
		if (file.is_open()) {
			int frame_count = 0;
			int width = 0;
			int height = 0;
			int slowdown = 0;
			Color color = UNDEFINED_COLOR;

			std::string line;
			std::vector<std::string> data;

			getline(file, line);	// Read line 1.
			utility::discardCR(line);
			frame_count = stoi(line);
			data.push_back(line);	// Add line to vector.

			getline(file, line);	// Read line 2.
			utility::discardCR(line);
			width = stoi(line);
			data.push_back(line);	// Add line to vector.

			getline(file, line);	// Read line 3.
			utility::discardCR(line);
			height = stoi(line);
			data.push_back(line);	// Add line to vector.

			getline(file, line);	// Read line 4.
			utility::discardCR(line);
			slowdown = stoi(line);
			data.push_back(line);	// Add line to vector.

			getline(file, line);	// Read line 5.
			utility::discardCR(line);
			if (line == "black") color = BLACK;
			else if (line == "red") color = RED;
			else if (line == "green") color = GREEN;
			else if (line == "yellow") color = YELLOW;
			else if (line == "blue") color = BLUE;
			else if (line == "magenta") color = MAGENTA;
			else if (line == "cyan") color = CYAN;
			else if (line == "white") color = WHITE;
			else {
				printf("\tERROR\t: ResourceManager.loadSprite() - Undefined color passed.\n");
				LM.writeLog(ts::TEST_LOG_LEVEL, "\tERROR\t: ResourceManager.loadSprite() - Undefined color passed.\n");
				file.close();
				return -1;
			}
			data.push_back(line);	// Add line to vector.

			// Make new Sprite.
			Sprite* spr = new Sprite(frame_count);

			spr->setWidth(width);
			spr->setHeight(height);
			spr->setSlowdown(slowdown);
			spr->setColor(color);

			// Read and add frames to Sprite.
			for (int f = 0; f < frame_count; f++) {
				Frame new_frame = Frame();
				std::string temp_string = "";

				for (int h = 0; h < height; h++) {
					getline(file, line);
					utility::discardCR(line);
					if (line.length() != width) {
						printf("\tERROR\t: ResourceManager.loadSprite() - Invalid frame string width (%d / %d).\n", (int)line.length(), width);
						LM.writeLog(ts::TEST_LOG_LEVEL, "\tERROR\t: ResourceManager.loadSprite() - Invalid frame string width (%d / %d).\n", line.length(), width);

						file.close();
						return -1;
					}
					temp_string.append(line);
				}

				new_frame.setString(temp_string);
				new_frame.setWidth(width);
				new_frame.setHeight(height);

				spr->addFrame(new_frame);
			}

			// Close file when done.
			file.close();

			// If no errors in any of above, add to ResourceManager.
			spr->setLabel(label);
			m_p_sprite[m_sprite_count] = spr;
			m_sprite_count++;

			return 0;
			
		}
		else {
			// If here, unable to open file.
			printf("\tERROR\t: ResourceManager.loadSprite() - Unable to open file.\n");
			LM.writeLog(ts::TEST_LOG_LEVEL, "\tERROR\t: ResourceManager.loadSprite() - Unable to open file.\n");
			return -1;
		}
	}

	// Unload Sprite with indicated label.
	// Return 0 if ok, else -1.
	int ResourceManager::unloadSprite(std::string label) {
		for (int i = 0; i < m_sprite_count; i++) {
			if (m_p_sprite[i]->getLabel() == label) {
				delete(m_p_sprite[i]);

				for (int j = i; j < m_sprite_count - 1; j++) {
					m_p_sprite[j] = m_p_sprite[j + 1];
				}

				m_sprite_count--;

				return 0;
			}
		}

		// Sprite not found.
		printf("\tERROR\t: ResourceManager.unloadSprite() - Sprite not found.\n");
		LM.writeLog(ts::TEST_LOG_LEVEL, "\tERROR\t: ResourceManager.unloadSprite() - Sprite not found.\n");
		return -1;
	}

	// Find Sprite with indicated label.
	// Return pointer to it if found, else NULL.
	Sprite* ResourceManager::getSprite(std::string label) const {
		for (int i = 0; i < m_sprite_count; i++) {
			if (label == m_p_sprite[i]->getLabel())
				return m_p_sprite[i];
		}

		printf("\tERROR\t: ResourceManager.getSprite() - Sprite not found.\n");
		LM.writeLog(ts::TEST_LOG_LEVEL, "\tERROR\t: ResourceManager.getSprite() - Sprite not found.\n");
		return NULL;	// Sprite not found.
	}

	// Load Sound from file.
	// Return 0 if ok, else -1.
	int ResourceManager::loadSound(std::string filename, std::string label) {
		
		if (m_sound_count >= MAX_SOUNDS) {
			LM.writeLog(ts::TEST_LOG_LEVEL, "\tERROR\t: ResourceManager.loadSound() - Sound array full.\n");
			return -1;
		}

		if (m_sound[m_sound_count].loadSound(filename) == -1) {
			LM.writeLog(ts::TEST_LOG_LEVEL, "\tERROR\t: ResourceManager.loadSound() - Unable to load from file.\n");
			return -1;
		}

		// All is well.
		m_sound[m_sound_count].setLabel(label);
		m_sound_count++;
		return 0;
	}

	// Remove Sound with indicated label.
	// Return 0 if ok, else -1.
	int ResourceManager::unloadSound(std::string label) {

		for (int i = 0; i < m_sound_count; i++) {
			if (label == m_sound[i].getLabel()) {

				// Scoot over remaining sound
				for (int j = i; j < m_sound_count - 1; j++) {
					m_sound[j] = m_sound[j + 1];
				}

				m_sound_count--;

				return 0;
			}
		}

		return -1;	// Sound not found.
	}

	// Find Sound with indicated label.
	// Return pointer to it if found, else NULL.
	Sound* ResourceManager::getSound(std::string label) {

		for (int i = 0; i < m_sound_count; i++) {
			if (label == m_sound[i].getLabel()) {
				return &m_sound[i];
			}
		}

		return NULL;	// Sound not found.
	}

	// Associate file with Music.
	// Return 0 if ok, else -1.
	int ResourceManager::loadMusic(std::string filename, std::string label) {

		if (m_music_count >= MAX_MUSICS) {
			LM.writeLog(ts::TEST_LOG_LEVEL, "\tERROR\t: ResourceManager.loadMusic() - Music array full.\n");
			return -1;
		}

		if (m_music[m_music_count].loadMusic(filename) == -1) {
			LM.writeLog(ts::TEST_LOG_LEVEL, "\tERROR\t: ResourceManager.loadMusic() - Unable to load from file.\n");
			return -1;
		}

		// All is well.
		m_music[m_music_count].setLabel(label);
		m_music_count++;
		return 0;
	}

	// Remove label for Music with indicated label.
	// Return 0 if ok, else -1.
	int ResourceManager::unloadMusic(std::string label) {

		for (int i = 0; i < m_music_count; i++) {
			if (label == m_music[i].getLabel()) {

				m_music[i].setLabel("");

				m_music_count--;

				return 0;
			}
		}

		return -1;	// Sound not found.
	}

	// Find Music with indicated label.
	// Return pointer to it if found, else NULL.
	Music* ResourceManager::getMusic(std::string label) {

		for (int i = 0; i < m_music_count; i++) {
			if (label == m_music[i].getLabel()) {
				return &m_music[i];
			}
		}

		return NULL;	// Sound not found.
	}
}