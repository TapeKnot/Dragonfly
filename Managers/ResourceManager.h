#pragma once
#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__
#define RM df::ResourceManager::getInstance()

// System includes.
#include <string>

// Engine includes.
#include "Manager.h"
#include "../Sprite.h"
#include "../Sound.h"
#include "../Music.h"

namespace df {

	// Maximum number of unique assets in game.
	const int MAX_SPRITES = 500;

	const int MAX_SOUNDS = 50;
	const int MAX_MUSICS = 50;

	class ResourceManager : public Manager {

	private:
		ResourceManager();							// No constructing.
		ResourceManager(ResourceManager const&);	// No copying.
		void operator=(ResourceManager const&);		// No assigning.

		Sprite* m_p_sprite[MAX_SPRITES];			// Array of sprites.
		int m_sprite_count;							// Count of number of loaded sprites.
		Sound m_sound[MAX_SOUNDS];					// Array of sound buffers.
		int m_sound_count;							// Count of number of loaded sounds.
		Music m_music[MAX_MUSICS];					// Array of music buffers.
		int m_music_count;							// Count of number of loaded musics.

	public:
		// Get the singleton instance of the ResourceManager.
		static ResourceManager& getInstance();

		// Get ResourceManager ready to manager for resources.
		int startUp();

		// Shut down ResourceManager, freeing up any allocated Sprites.
		void shutDown();

		// Load Sprite from file.
		// Assign indicated label to sprite.
		// Return 0 if ok, else -1.
		int loadSprite(std::string filename, std::string label);

		// Unload Sprite with indicated label.
		// Return 0 if ok, else -1.
		int unloadSprite(std::string label);

		// Find Sprite with indicated label.
		// Return pointer to it if found, else NULL.
		Sprite* getSprite(std::string label) const;

		// Load Sound from file.
		// Return 0 if ok, else -1.
		int loadSound(std::string filename, std::string label);

		// Remove Sound with indicated label.
		// Return 0 if ok, else -1.
		int unloadSound(std::string label);

		// Find Sound with indicated label.
		// Return pointer to it if found, else NULL.
		Sound* getSound(std::string label);

		// Associate file with Music.
		// Return 0 if ok, else -1.
		int loadMusic(std::string filename, std::string label);

		// Remove label for Music with indicated label.
		// Return 0 if ok, else -1.
		int unloadMusic(std::string label);

		// Find Music with indicated label.
		// Return pointer to it if found, else NULL.
		Music* getMusic(std::string label);
	};

}

#endif