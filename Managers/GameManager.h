#pragma once
#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__
#define GM df::GameManager::getInstance()
#include "Manager.h"

namespace df {

	// Default frame time (game loop time) in milliseconds (33 ms == 30 f/s)
	const int FRAME_TIME_DEFAULT = 33;

	class GameManager : public Manager {

	private:
		GameManager();							// No constructing.
		GameManager(GameManager const&);		// No copying.
		void operator=(GameManager const&);		// No assigning.

		bool m_game_over;	// If true, stop game loop
		int m_frame_time;	// Target time per game loop, in milliseconds.

	public:
		// Get the singleton instance of the GameManager.
		static GameManager& getInstance();
		
		// Startup all GameManager services.
		int startUp();

		// Shut down GameManager services.
		void shutDown();
		
		// Run game loop.
		void run();

		// Set game over status to indicated value.
		// If true (default), will stop game loop.
		void setGameOver(bool new_game_over = true);

		// Get game over status.
		bool getGameOver() const;

		// Return fram time.
		// Frame time is target time for game loop, in milliseconds.
		int getFrameTime() const;
	};

}

#endif