#pragma once
#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__
#define IM df::InputManager::getInstance()
#include "Manager.h"
#include "../Events/EventKeyboard.h"
#include <SFML/Graphics.hpp>

namespace df {

	class InputManager : public Manager {

	private:
		InputManager();							// No constructing.
		InputManager(InputManager const&);		// No copying.
		void operator=(InputManager const&);	// No assigning.

	public:
		// Get the singleton instance of the InputManager.
		static InputManager& getInstance();

		// Get window ready to capture input.
		// Return 0 if ok, else return -1.
		int startUp();

		// Revert back to normal window mode.
		void shutDown();

		// Get input from the keyboard and mouse.
		// Pass event along to all Objects.
		void getInput() const;

		// Convert SFML input into Dragonfly input.
		Keyboard::Key convertKey(sf::Keyboard::Key key) const;
	};
}

#endif