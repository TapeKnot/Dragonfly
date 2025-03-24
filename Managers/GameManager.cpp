#include <stdio.h>
#include <stdarg.h>
#include <Windows.h>
#include "GameManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "../Clock.h"
#include "../ObjectList.h"
#include "../Events/EventStep.h"
#include "DisplayManager.h"
#include "InputManager.h"
#include "../Testing/TestMoveObject.h"
#include "../Testing/TestReticle.h"
#include "../Box.h"

namespace df {

	GameManager::GameManager() {
		setType("GameManager");
		m_game_over = false;
		m_frame_time = FRAME_TIME_DEFAULT;
	}

	GameManager& GameManager::getInstance() {
		static GameManager single;
		return single;
	}

	// Startup all GameManager services.
	int GameManager::startUp() {
		setGameOver(false);

		if (timeBeginPeriod(1) == TIMERR_NOCANDO)
			printf("ERROR in GameManager.startUp(): timeBeginPeriod() failed.\n");

		Manager::startUp();

		// Start up other managers in order
		LM.startUp();
		WM.startUp();

		if (LM.isStarted()) DM.startUp();

		WM.setBoundary(Box(Vector(), DM.getHorizontal(), DM.getVertical()));
		WM.setView(Box(Vector(), DM.getHorizontal(), DM.getVertical()));

		if (DM.isStarted()) IM.startUp();

		return 0;
	}

	// Shut down GameManager services.
	void GameManager::shutDown() {
		LM.shutDown();
		WM.shutDown();
		DM.shutDown();
		IM.shutDown();
		Manager::shutDown();

		if (timeEndPeriod(1) == TIMERR_NOCANDO)
			printf("ERROR in GameManager.shutDown(): timeEndPeriod() failed.\n");

		setGameOver();
	}

	// Run game loop.
	void GameManager::run() {
		Clock clock;
		long int loop_time = 0;
		long int intended_sleep_time = 0;
		long int actual_sleep_time = 0;
		long int adjust_time = 0;

		int step_count = 0;

		/*TestMoveObject moveObj;
		TestReticle reticle;*/

		//printf("START RUNNING\n");
		while (!m_game_over) {
			clock.delta();

			EventStep s;
			s.setStepCount(step_count);
			step_count++;
			onEvent(&s);

			IM.getInput();

			WM.update();

			// Draw all Objects.
			WM.draw();

			// Render new frame.
			DM.swapBuffers();

			// Measure loop time & sleep
			loop_time = clock.split();
			//printf("\tLoop Time : %ld ms\n", loop_time);
			intended_sleep_time = m_frame_time - loop_time - adjust_time;
			if (intended_sleep_time < 0) intended_sleep_time = 0;
			//printf("\Intended Sleep Time : %ld ms\n", intended_sleep_time);
			clock.delta();
			Sleep(intended_sleep_time);

			actual_sleep_time = clock.split();
			//printf("\Actual Sleep Time : %ld ms\n", actual_sleep_time);
			adjust_time = actual_sleep_time - intended_sleep_time;
			if (adjust_time < 0) adjust_time = 0;
			//printf("\Adjust Time : %ld ms\n", adjust_time);
		}
	}

	// Set game over status to indicated value.
	// If true (default), will stop game loop.
	void GameManager::setGameOver(bool new_game_over) {
		m_game_over = new_game_over;
	}

	// Get game over status.
	bool GameManager::getGameOver() const {
		return m_game_over;
	}

	// Return fram time.
	// Frame time is target time for game loop, in milliseconds.
	int GameManager::getFrameTime() const {
		return m_frame_time;
	}
}