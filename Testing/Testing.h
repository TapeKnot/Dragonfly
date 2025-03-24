#pragma once
#include <stdlib.h>

namespace ts {

	const static int TEST_LOG_LEVEL = 1;

	class Testing {

	private:
		static void writeResult(bool result, const char* function);

		static void testUtility();
		static bool testUtility_getTimeString();
		static bool testUtility_positionsIntersect();
		static bool testUtility_discardCR();
		static bool testUtility_boxIntersectsBox();
		static bool testUtility_getWorldBox();
		static bool testUtility_worldToView();
		static bool testUtility_viewToWorld();
		static bool testUtility_toString();

		static void setupTestEnvironment_objectMovement();

		static void testLogManager();
		static bool testLogManager_writeLog();

		static void testGameManager();
		static bool testGameManager_gameOver();
		static bool testGameManager_getFrameTime();
		static bool testGameManager_stepEvent();

		static void testWorldManager();
		static bool testWorldManager_insertObject();
		static bool testWorldManager_removeObject();
		static bool testWorldManager_getAllObjects();
		static bool testWorldManager_objectsOfType();
		static bool testWorldManager_update();
		static bool testWorldManager_markForDelete();
		static bool testWorldManager_draw();
		static bool testWorldManager_getCollisions();
		static bool testWorldManager_moveObject();
		static bool testWorldManager_setViewPosition();
		static bool testWorldManager_setViewFollowing();

		static void testDisplayManager();
		static bool testDisplayManager_drawCh();
		static bool testDisplayManager_drawString();
		static bool testDisplayManager_charHeight();
		static bool testDisplayManager_charWidth();
		static bool testDisplayManager_spacesToPixels();
		static bool testDisplayManager_pixelsToSpaces();

		static void testInputManager();
		static bool testInputManager_convertKey();
		static bool testInputManager_getInput();

		static void testResourceManager();
		static bool testResourceManager_loadSprite();
		static bool testResourceManager_unloadSprite();
		static bool testResourceManager_getSprite();
		static bool testResourceManager_loadSound();
		static bool testResourceManager_unloadSound();
		static bool testResourceManager_getSound();
		static bool testResourceManager_loadMusic();
		static bool testResourceManager_unloadMusic();
		static bool testResourceManager_getMusic();

		static void testClock();
		static bool testClock_delta();
		static bool testClock_split();

		static void testVector();
		static bool testVector_getMagnitude();
		static bool testVector_scale();
		static bool testVector_normalize();
		static bool testVector_operatorPlus();
		static bool testVector_operatorMinus();
		static bool testVector_operatorMultiply();
		static bool testVector_operatorDivide();
		static bool testVector_operatorEquals();
		static bool testVector_operatorDoesNotEqual();
		static bool testVector_operatorNot();

		static void testObject();
		static bool testObject_eventHandler();
		static bool testObject_draw();
		static bool testObject_kinematics();

		static void testObjectList();
		static bool testObjectList_insert();
		static bool testObjectList_remove();
		static bool testObjectList_clear();

		static void testViewObject();
		static bool testViewObject_draw();
		static bool testViewObject_eventHandler();
		static bool testViewObject_setLocation();

		static void testEvent();
		static bool testEvent_getType();
		static bool testEvent_setType();

		static void testEventStep();
		static bool testEventStep_getType();
		static bool testEventStep_setType();

		static void testFrame();
		static bool testFrame_draw();

		static void testSprite();
		static bool testSprite_addFrame();
		static bool testSprite_draw();

		static void testAnimation();
		static bool testAnimation_draw();
		static bool testAnimation_getBox();

		static void testSound();
		static bool testSound_loadSound();
		static bool testSound_play();
		static bool testSound_stop();
		static bool testSound_pause();

		static void testMusic();
		static bool testMusic_loadSound();
		static bool testMusic_play();
		static bool testMusic_stop();
		static bool testMusic_pause();

	public:
		static void testAll();
	};

}
