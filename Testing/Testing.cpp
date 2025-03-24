#include <Windows.h>
#include "Testing.h"
#include "../utility.h"
#include "../Managers/LogManager.h"
#include "../Clock.h"
#include "../Managers/GameManager.h"
#include "../Vector.h"
#include "../Object.h"
#include "../ViewObject.h"
#include "../ObjectList.h"
#include "../Events/Event.h"
#include "../Events/EventStep.h"
#include "../Events/EventView.h"
#include "../Managers/DisplayManager.h"
#include "../Managers/WorldManager.h"
#include "../Managers/InputManager.h"
#include "../Managers/ResourceManager.h"
#include "../Frame.h"
#include "../Sprite.h"
#include "../Animation.h"
#include "../Box.h"
#include "../Sound.h"
#include "../Music.h"

namespace ts {

	int m_passed_tests = 0;
	int m_total_tests = 0;

	void Testing::testAll() {

		//GM.startUp();

		testUtility();

		testLogManager();

		testClock();

		testGameManager();

		testWorldManager();

		testVector();

		testObject();

		testViewObject();

		testObjectList();

		testEvent();

		testEventStep();

		testDisplayManager();

		testFrame();

		testSprite();

		testResourceManager();

		testAnimation();

		DM.swapBuffers();

		testSound();

		testMusic();

		printf("\nSummary: %d of %d tests passed.", m_passed_tests, m_total_tests);
		LM.writeLog(TEST_LOG_LEVEL, "\nSummary: %d of %d tests passed.", m_passed_tests, m_total_tests);

		Sleep(10000);
	}

	// Writes a log with the given function name and result.
	void Testing::writeResult(bool result, const char* function) {
		const char* resultStr = "";

		if (result) {
			resultStr = "PASS";
			m_passed_tests++;
		}
		else {
			resultStr = "FAIL";
		}
		m_total_tests++;

		printf("%s\t: %s\n", resultStr, function);
		LM.writeLog(TEST_LOG_LEVEL, "%s\t: %s", resultStr, function);
	}

	// --- TEST ENVIRONMENTS ---
	/*void Testing::setupTestEnvironment_objectMovement() {

	}*/
	
	// --- UTILITY ---
	void Testing::testUtility() {
		writeResult(testUtility_getTimeString(), "testUtility_getTimeString");
		writeResult(testUtility_positionsIntersect(), "testUtility_positionsIntersect");
		writeResult(testUtility_discardCR(), "testUtility_discardCR");
		writeResult(testUtility_boxIntersectsBox(), "testUtility_boxIntersectsBox");
		writeResult(testUtility_getWorldBox(), "testUtility_getWorldBox");
		writeResult(testUtility_worldToView(), "testUtility_worldToView");
		writeResult(testUtility_viewToWorld(), "testUtility_viewToWorld");
		writeResult(testUtility_toString(), "testUtility_toString");
	}

	bool Testing::testUtility_getTimeString() {

		std::string time_string = df::utility::getTimeString();

		if (time_string.size() != 8) return false;
		else if (time_string[2] != ':') return false;
		else if (time_string[5] != ':') return false;

		return true;
	}

	bool Testing::testUtility_positionsIntersect() {
		df::Vector vec1(1, 2);
		df::Vector vec2(2, 2);	// Positive Edge of intersection
		df::Vector vec3(1, 1);	// Negative edge of intersection
		df::Vector vecOOB(-1, 0);	// Out-of-bounds

		if (df::utility::positionsIntersect(vec1, vec1) == false) return false;
		else if (df::utility::positionsIntersect(vec1, vec2) == false) return false;
		else if (df::utility::positionsIntersect(vec1, vec3) == false) return false;

		return df::utility::positionsIntersect(vec1, vecOOB) == false;
	}

	bool Testing::testUtility_discardCR() {
		std::string testStr = "TESTING, TESTING...\n\r";

		df::utility::discardCR(testStr);

		return testStr[testStr.size() - 1] != '\r';
	}

	bool Testing::testUtility_boxIntersectsBox() {
		df::Box box1(df::Vector(0.5, 0.5), 1, 1);
		df::Box box2(df::Vector(-0.5, -0.5), 1, 1);
		df::Box box3(df::Vector(-1.0, -1.0), 2, 3);
		df::Box box4(df::Vector(-5.0, -5.0), 1, 2);

		if (df::utility::boxIntersectsBox(box1, box1) != true) return false;
		if (df::utility::boxIntersectsBox(box1, box2) != true) return false;
		if (df::utility::boxIntersectsBox(box1, box3) != true) return false;
		if (df::utility::boxIntersectsBox(box3, box4) != false) return false;

		return true;
	}

	bool Testing::testUtility_getWorldBox() {
		df::Object testObj1;

		testObj1.setBox(df::Box(df::Vector(5.0, 5.0), 1, 1));

		df::Box new_box = df::utility::getWorldBox(&testObj1);

		return new_box.getCorner().getX() == 5.0 && new_box.getCorner().getY() == 5.0 && new_box.getHorizontal() == 1.0 && new_box.getVertical() == 1.0;
	}

	bool Testing::testUtility_worldToView() {
		df::Vector w2v = df::utility::worldToView(df::Vector(2,3));
		
		return w2v.getX() == 2 && w2v.getY() == 3;
	}

	bool Testing::testUtility_viewToWorld() {
		df::Vector v2w = df::utility::viewToWorld(df::Vector(2, 3));

		return v2w.getX() == 2 && v2w.getY() == 3;
	}

	bool Testing::testUtility_toString() {
		return df::utility::toString(123456789) == "123456789";
	}

	// --- LOGMANAGER ---
	void Testing::testLogManager() {
		writeResult(testLogManager_writeLog(), "testLogManager_writeLog");
	}

	bool Testing::testLogManager_writeLog() {

		int test_int = 885;
		float test_float = 2.34f;
		const char* test_string = "Hello World!\n";

		LM.writeLog(TEST_LOG_LEVEL, "%d", test_int);		// Int
		LM.writeLog(TEST_LOG_LEVEL, "%02d", test_int);		// Truncated Int
		LM.writeLog(TEST_LOG_LEVEL, "%f", test_float);		// Float
		LM.writeLog(TEST_LOG_LEVEL, "%s", test_string);		// String

		return true;
	}

	// --- GAMEMANAGER ---
	void Testing::testGameManager() {
		writeResult(testGameManager_gameOver(), "testGameManager_gameOver");
		writeResult(testGameManager_getFrameTime(), "testGameManager_getFrameTime");
	}

	bool Testing::testGameManager_gameOver() {

		GM.setGameOver();

		if (GM.getGameOver() != true) return false;

		GM.setGameOver(false);

		if (GM.getGameOver() != false) return false;

		return true;
	}

	bool Testing::testGameManager_getFrameTime() {

		return GM.getFrameTime() == 33;
	}

	bool Testing::testGameManager_stepEvent() {	// TODO: Finish stepEvent testing.
		df::Object* testObj = new df::Object();

		return false;
	}

	// --- WORLD MANAGER ---
	void Testing::testWorldManager() {
		writeResult(testWorldManager_insertObject(), "testWorldManager_insertObject");
		//writeResult(testWorldManager_removeObject(), "testWorldManager_removeObject");
		//writeResult(testWorldManager_getAllObjects(), "testWorldManager_getAllObjects");
		//writeResult(testWorldManager_objectsOfType(), "testWorldManager_objectsOfType");
		//writeResult(testWorldManager_update(), "testWorldManager_update");
		//writeResult(testWorldManager_markForDelete(), "testWorldManager_markForDelete");
		//writeResult(testWorldManager_draw(), "testWorldManager_draw");
		//writeResult(testWorldManager_getCollisions(), "testWorldManager_getCollisions");
		//writeResult(testWorldManager_moveObject(), "testWorldManager_moveObject");
		//writeResult(testWorldManager_setViewPosition(), "testWorldManager_setViewPosition");
		//writeResult(testWorldManager_setViewFollowing(), "testWorldManager_setViewFollowing");
	}

	bool Testing::testWorldManager_insertObject() {
		df::Object test_obj;	// Object constructor calls insertObject()

		df::ObjectList obj_list = WM.getAllObjects();

		return obj_list.getCount() == 1 && obj_list[0] == &test_obj;
	}

	bool Testing::testWorldManager_removeObject() {
		// TODO: Implement.
		return false;
	}

	bool Testing::testWorldManager_getAllObjects() {
		// TODO: Implement.
		return false;
	}

	bool Testing::testWorldManager_objectsOfType() {
		// TODO: Implement.
		return false;
	}

	bool Testing::testWorldManager_update() {
		// TODO: Implement.
		return false;
	}

	bool Testing::testWorldManager_markForDelete() {
		df::Object test_obj;

		WM.markForDelete(&test_obj);	// Mark object for deletion.

		WM.update();					// Run update loop; will delete object.

		df::ObjectList obj_list = WM.getAllObjects();

		return obj_list.getCount() == 0;	// Is object deleted?

		return false;
	}

	bool Testing::testWorldManager_draw() {
		// TODO: Implement.
		return false;
	}

	bool Testing::testWorldManager_getCollisions() {
		// TODO: Implement.
		return false;
	}

	bool Testing::testWorldManager_moveObject() {
		// TODO: Implement.
		return false;
	}

	bool Testing::testWorldManager_setViewPosition() {
		// TODO: Implement.
		return false;
	}

	bool Testing::testWorldManager_setViewFollowing() {
		// TODO: Implement.
		return false;
	}


	// --- DISPLAY MANAGER ---
	void Testing::testDisplayManager() {
		writeResult(testDisplayManager_drawCh(), "testDisplayManager_drawCh");
		writeResult(testDisplayManager_drawString(), "testDisplayManager_drawString");

		writeResult(testDisplayManager_charHeight(), "testDisplayManager_charHeight");
		writeResult(testDisplayManager_charWidth(), "testDisplayManager_charWidth");
		writeResult(testDisplayManager_spacesToPixels(), "testDisplayManager_spacesToPixels");
		writeResult(testDisplayManager_pixelsToSpaces(), "testDisplayManager_pixelsToSpaces");
	}

	bool Testing::testDisplayManager_drawCh() {
		DM.startUp();
		
		if (DM.drawCh(df::Vector(10, 5), '@', df::YELLOW) == 0) {
			return true;
		}
		else return false;
	}

	bool Testing::testDisplayManager_drawString() {
		DM.startUp();

		if (DM.drawString(df::Vector(20, 20), "TESTING, TESTING...", df::LEFT_JUSTIFIED, df::WHITE) != 0) return false;
		if (DM.drawString(df::Vector(60, 15), "It can't be helped.", df::CENTER_JUSTIFIED, df::BLUE) != 0) return false;
		if (DM.drawString(df::Vector(40, 9), "VIVA VIVA LA REVOLUCIÓN", df::RIGHT_JUSTIFIED, df::GREEN) != 0) return false;

		return true;
	}

	bool Testing::testDisplayManager_charHeight() {
		DM.startUp();

		return DM.charHeight() == 32.0f;
	}

	bool Testing::testDisplayManager_charWidth() {
		DM.startUp();

		return DM.charWidth() == 12.8f;
	}

	bool Testing::testDisplayManager_spacesToPixels() {
		DM.startUp();

		df::Vector returnVec = DM.spacesToPixels(df::Vector(50, 50));

		return returnVec.getX() == 640.0f && returnVec.getY() == 1600.0f;
	}

	bool Testing::testDisplayManager_pixelsToSpaces() {
		DM.startUp();

		df::Vector returnVec = DM.pixelsToSpaces(df::Vector(50, 50));

		return returnVec.getX() == 3.90625f && returnVec.getY() == 1.5625f;
	}

	// --- INPUT MANAGER ---
	void Testing::testInputManager() {
		writeResult(testInputManager_convertKey(), "testInputManager_convertKey");
		//writeResult(testInputManager_getInput(), "testInputManager_getInput");
	}

	bool Testing::testInputManager_convertKey() {
		if (IM.convertKey(sf::Keyboard::Key::A) != df::Keyboard::Key::A) return false;

		if (IM.convertKey(sf::Keyboard::Key::LShift) != df::Keyboard::Key::LEFTSHIFT) return false;

		if (IM.convertKey(sf::Keyboard::Key::Equal) != df::Keyboard::Key::PLUS) return false;

		if (IM.convertKey(sf::Keyboard::Key::Comma) != df::Keyboard::Key::UNDEFINED_KEY) return false;

		return true;
	}

	bool Testing::testInputManager_getInput() {
		// Not possible to test autonomously...
		return false;
	}

	// --- RESOURCE MANAGER ---
	void Testing::testResourceManager() {
		RM.startUp();

		writeResult(testResourceManager_loadSprite(), "testResourceManager_loadSprite");
		writeResult(testResourceManager_unloadSprite(), "testResourceManager_unloadSprite");
		writeResult(testResourceManager_getSprite(), "testResourceManager_getSprite");
		writeResult(testResourceManager_loadSound(), "testResourceManager_loadSound");
		writeResult(testResourceManager_unloadSound(), "testResourceManager_unloadSound");
		writeResult(testResourceManager_getSound(), "testResourceManager_getSound");
		writeResult(testResourceManager_loadMusic(), "testResourceManager_loadMusic");
		writeResult(testResourceManager_unloadMusic(), "testResourceManager_unloadMusic");
		writeResult(testResourceManager_getMusic(), "testResourceManager_getMusic");

		RM.shutDown();
	}

	bool Testing::testResourceManager_loadSprite() {
		return RM.loadSprite("Testing/testSprite.txt", "testing") == 0;
	}

	bool Testing::testResourceManager_unloadSprite() {
		RM.loadSprite("Testing/testSprite.txt", "testing");

		return RM.unloadSprite("testing") == 0;
	}

	bool Testing::testResourceManager_getSprite() {
		RM.loadSprite("Testing/testSprite.txt", "testing");

		return RM.getSprite("testing") != NULL;
	}

	bool Testing::testResourceManager_loadSound() {
		return RM.loadSound("Testing/nuke.wav", "testSound") == 0;
	}

	bool Testing::testResourceManager_unloadSound() {
		RM.loadSound("Testing/nuke.wav", "testSound");

		return RM.unloadSound("testSound") == 0;
	}

	bool Testing::testResourceManager_getSound() {
		RM.loadSound("Testing/nuke.wav", "testSound");

		return RM.getSound("testSound") != NULL;
	}

	bool Testing::testResourceManager_loadMusic() {
		return RM.loadMusic("Testing/start-music.wav", "testMusic") == 0;
	}

	bool Testing::testResourceManager_unloadMusic() {
		RM.loadMusic("Testing/start-music.wav", "testMusic");

		return RM.unloadMusic("testMusic") == 0;
	}

	bool Testing::testResourceManager_getMusic() {
		RM.loadMusic("Testing/start-music.wav", "testMusic");

		return RM.getMusic("testMusic") != NULL;
	}

	// --- CLOCK ---
	void Testing::testClock() {
		writeResult(testClock_delta(), "testClock_delta");
		writeResult(testClock_split(), "testClock_split");
	}

	bool Testing::testClock_delta() {

		df::Clock clock;
		clock.delta();

		Sleep(100);	// 1 second
		long int first_delta = clock.delta();

		Sleep(100);	// 1 second
		long int second_delta = clock.delta();

		long int diff_delta = second_delta - first_delta;
		//printf("Deltas: %ld, %ld, %ld\n", first_delta, second_delta, diff_delta);

		return (diff_delta > -500 && diff_delta < 500);	// Elapsed time within 500 milliseconds of each other
	}

	bool Testing::testClock_split() {

		df::Clock clock;
		clock.delta();

		Sleep(100);	// 1 second
		long int first_split = clock.split();

		Sleep(100);	// 1 second
		long int second_split = clock.split();

		long int diff_split = second_split - first_split;
		//printf("Splits: %ld, %ld, %ld\n", first_split, second_split, diff_split);

		return (diff_split > -300 && diff_split < 300);	// Split difference should be same as first split
	}

	// --- VECTOR ---
	void Testing::testVector() {
		writeResult(testVector_getMagnitude(), "testVector_getMagnitude");
		writeResult(testVector_scale(), "testVector_scale");
		writeResult(testVector_normalize(), "testVector_normalize");
		writeResult(testVector_operatorPlus(), "testVector_operatorPlus");

		/*writeResult(testVector_operatorMinus(), "testVector_operatorMinus");
		writeResult(testVector_operatorMultiply(), "testVector_operatorMultiply");
		writeResult(testVector_operatorDivide(), "testVector_operatorDivide");
		writeResult(testVector_operatorEquals(), "testVector_operatorEquals");
		writeResult(testVector_operatorDoesNotEqual(), "testVector_operatorDoesNotEqual");
		writeResult(testVector_operatorNot(), "testVector_operatorNot");*/
	}

	bool Testing::testVector_getMagnitude() {

		df::Vector origin;					// Zero vector
		if (origin.getMagnitude() != 0) return false;

		df::Vector posVec(2.0f, 2.0f);		// Positive Vector
		if (posVec.getMagnitude() != 2.828427f) return false;

		df::Vector negVec(-3.5f, -1.11f);	// Negative Vector
		if (negVec.getMagnitude() != 3.67179775f) return false;

		return true;
	}

	bool Testing::testVector_scale() {

		df::Vector vec1(5.0f, 5.0f);		// Scale Vector
		vec1.scale(15);
		if (vec1.getX() != 75.0f || vec1.getY() != 75.0f) return false;
		
		df::Vector origin;					// Scale 0 by Vector
		origin.scale(14);
		if (origin.getX() != 0.0f || origin.getY() != 0.0f) return false;

		df::Vector vec2(5.0f, 5.0f);		// Scale Vector by 0
		vec2.scale(0);
		if (vec2.getX() != 0.0f || vec2.getY() != 0.0f) return false;

		df::Vector vec3(5.0f, 5.0f);		// Scale Vector by negative
		vec3.scale(-15);
		if (vec3.getX() != -75.0f || vec3.getY() != -75.0f) return false;

		return true;
	}

	bool Testing::testVector_normalize() {
		df::Vector origin;						// Normalize 0 Vector
		origin.normalize();
		if (origin.getX() != 0.0f || origin.getY() != 0.0f) return false;

		df::Vector posVec(5.0f, 5.0f);						// Normalize Positive Vector
		posVec.normalize();
		if (posVec.getX() != 0.7071067812f || posVec.getY() != 0.7071067812f) return false;

		df::Vector negVec(-5.0f, -5.0f);						// Normalize Negative Vector
		negVec.normalize();
		if (negVec.getX() != -0.7071067812f || negVec.getY() != -0.7071067812f) return false;

		df::Vector mixVec(-5.0f, 5.0f);						// Normalize Half/Half Vector
		mixVec.normalize();
		if (mixVec.getX() != -0.7071067812f || mixVec.getY() != 0.7071067812f) return false;

		return true;
	}

	bool Testing::testVector_operatorPlus() {

		df::Vector origin;
		df::Vector vec1(5.0f, 5.0f);
		df::Vector newVec = origin + vec1;
		if (newVec.getX() != 5.0f || newVec.getY() != 5.0f) return false;

		df::Vector vec2(-5.0f, -5.0f);
		newVec = vec1 + vec2;
		if (newVec.getX() != 0.0f || newVec.getY() != 0.0f) return false;

		newVec = vec1 + vec1;
		if (newVec.getX() != 10.0f || newVec.getY() != 10.0f) return false;

		return true;
	}

	bool Testing::testVector_operatorMinus() {
		df::Vector origin;
		df::Vector vec1(5.0f, 5.0f);
		df::Vector newVec = origin - vec1;
		if (newVec.getX() != -5.0f || newVec.getY() != -5.0f) return false;

		df::Vector vec2(-5.0f, -5.0f);
		newVec = vec1 - vec2;
		if (newVec.getX() != 10.0f || newVec.getY() != 10.0f) return false;

		newVec = vec1 - vec1;
		if (newVec.getX() != 0.0f || newVec.getY() != 0.0f) return false;

		return true;
	}

	bool Testing::testVector_operatorMultiply() {
		df::Vector origin;
		df::Vector vec1(5.0f, 5.0f);
		df::Vector newVec = origin - vec1;
		if (newVec.getX() != -5.0f || newVec.getY() != -5.0f) return false;

		df::Vector vec2(-5.0f, -5.0f);
		newVec = vec1 - vec2;
		if (newVec.getX() != 10.0f || newVec.getY() != 10.0f) return false;

		newVec = vec1 - vec1;
		if (newVec.getX() != 0.0f || newVec.getY() != 0.0f) return false;

		return true;
	}

	bool Testing::testVector_operatorDivide() {
		return false;
	}

	bool Testing::testVector_operatorEquals() {
		return false;
	}

	bool Testing::testVector_operatorDoesNotEqual() {
		return false;
	}

	bool Testing::testVector_operatorNot() {
		return false;
	}

	// --- OBJECT ---
	void Testing::testObject() {
		writeResult(testObject_eventHandler(), "testObject_eventHandler");
		writeResult(testObject_draw(), "testObject_draw");
	}

	bool Testing::testObject_eventHandler() {
		df::Object testObject;
		df::Event testEvent;
		df::EventStep testStepEvent;

		testObject.eventHandler(&testEvent);
		testObject.eventHandler(&testStepEvent);

		return true;	// Review results in Logfile.
	}

	bool Testing::testObject_draw() {
		df::Object testObj1;
		df::Object testObj2;
		df::Object testObj3;

		testObj1.setPosition(df::Vector(10, 10));
		testObj2.setPosition(df::Vector(15, 15));
		testObj3.setPosition(df::Vector(10, 10));

		testObj1.setAltitude(0);
		testObj2.setAltitude(df::MAX_ALTITUDE);

		if (testObj3.setAltitude(df::MAX_ALTITUDE + 1) != -1) return false;

		// Assign animations
		RM.loadSprite("Testing/testSprite2.txt", "testing2");

		df::Sprite* spr = RM.getSprite("testing2");

		df::Animation anim = df::Animation();

		anim.setSprite(spr);

		testObj1.setAnimation(anim);
		testObj2.setAnimation(anim);
		testObj3.setAnimation(anim);
		
		WM.draw();

		//GM.run();	// Activate this statement to see full animation.

		return true;
	}

	bool Testing::testObject_kinematics() {
		return false;
	}

	// --- VIEWOBJECT ---
	void Testing::testViewObject() {
		writeResult(testViewObject_draw(), "testViewObject_draw");
		//writeResult(testViewObject_eventHandler(), "testViewObject_eventHandler");
		//writeResult(testViewObject_setLocation(), "testViewObject_setLocation");
	}

	bool Testing::testViewObject_draw() {
		df::ViewObject view_obj;

		view_obj.setViewString("Points");
		view_obj.setValue(9999);
		view_obj.setDrawValue();
		view_obj.setBorder(false);
		view_obj.setColor(df::BLUE);
		view_obj.setLocation(df::CENTER_RIGHT);

		return view_obj.draw() == 0;
	}

	bool Testing::testViewObject_eventHandler() {
		df::ViewObject view_obj;

		view_obj.setViewString("Points");
		view_obj.setValue(9999);			// Setting points to 9999.
		view_obj.setDrawValue();
		view_obj.setBorder(true);
		view_obj.setColor(df::BLUE);
		view_obj.setLocation(df::TOP_RIGHT);

		const df::EventView* e();

		//view_obj.eventHandler(e);

		// TODO: Send event to ViewObject.

		return false;
	}

	bool Testing::testViewObject_setLocation() {
		// TODO: Implement.
		return false;
	}

	// --- OBJECTLIST ---
	void Testing::testObjectList() {
		writeResult(testObjectList_insert(), "testObjectList_insert");
		writeResult(testObjectList_remove(), "testObjectList_remove");
		writeResult(testObjectList_clear(), "testObjectList_clear");
	}

	bool Testing::testObjectList_insert() {
		df::ObjectList list;

		df::Object obj;
		list.insert(&obj);
		if (list[0] != &obj) return false;

		df::Object obj2;
		list.insert(&obj2);

		return list[1] == &obj2;
	}

	bool Testing::testObjectList_remove() {
		df::ObjectList list;

		df::Object obj;
		df::Object obj2;
		df::Object obj3;
		df::Object obj4;
		list.insert(&obj);
		list.insert(&obj2);
		list.insert(&obj3);
		list.insert(&obj4);

		list.remove(&obj2);

		return list[0] == &obj && list[1] == &obj3 && list[2] == &obj4;
	}

	bool Testing::testObjectList_clear() {
		df::ObjectList list;

		list.clear();				// Clear empty list

		if (list.getCount() != 0) return false;

		df::Object obj;
		df::Object obj2;
		df::Object obj3;
		df::Object obj4;
		list.insert(&obj);
		list.insert(&obj2);
		list.insert(&obj3);
		list.insert(&obj4);

		list.clear();

		return list.getCount() == 0;
	}

	// --- EVENT ---
	void Testing::testEvent() {
		writeResult(testEvent_getType(), "testEvent_getType");
		writeResult(testEvent_setType(), "testEvent_setType");
	}

	bool Testing::testEvent_getType() {
		df::Event testEvent;

		return testEvent.getType() == "df::undefined";
	}

	bool Testing::testEvent_setType() {
		df::Event testEvent;

		testEvent.setType("ts::testing");

		return testEvent.getType() == "ts::testing";
	}

	// --- STEP EVENT ---
	void Testing::testEventStep() {
		writeResult(testEventStep_getType(), "testEventStep_getType");
		writeResult(testEventStep_setType(), "testEventStep_setType");
	}

	bool Testing::testEventStep_getType() {
		df::EventStep testEvent;

		return testEvent.getType() == "df::step";
	}

	bool Testing::testEventStep_setType() {
		df::EventStep testEvent;

		testEvent.setType("ts::testing");

		return testEvent.getType() == "ts::testing";
	}

	// --- FRAME ---
	void Testing::testFrame() {
		writeResult(testFrame_draw(), "testFrame_draw");
	}

	bool Testing::testFrame_draw() {
		df::Frame testFrame(5, 5, "**********-----**********");	// Should appear as a box of *'s with a horizontal line of -'s

		if (testFrame.draw(df::Vector(5, 5), df::WHITE) == 0) return true;
		else return false;
	}

	// --- SPRITE ---
	void Testing::testSprite() {
		writeResult(testSprite_addFrame(), "testSprite_addFrame");
		writeResult(testSprite_draw(), "testSprite_draw");
	}

	bool Testing::testSprite_addFrame() {
		df::Sprite testSprite(2);	// Create sprite with a max frames of 2.
		df::Frame testFrame = df::Frame();

		if (testSprite.addFrame(testFrame) != 0) return false;
		if (testSprite.addFrame(testFrame) != 0) return false;

		return testSprite.addFrame(testFrame) == -1;
	}

	bool Testing::testSprite_draw() {
		df::Sprite testSprite(2);	// Create sprite with a max frames of 2.
		df::Frame testFrame1(3, 3, "#########");
		df::Frame testFrame2(3, 3, "123456789");

		if (testSprite.addFrame(testFrame1) != 0) return false;
		if (testSprite.addFrame(testFrame2) != 0) return false;

		if (testSprite.draw(1, df::Vector(20, 5))) return false;

		return true;
	}

	// --- ANIMATION ---
	void Testing::testAnimation() {
		writeResult(testAnimation_draw(), "testAnimation_draw");
		writeResult(testAnimation_getBox(), "testAnimation_getBox");
	}

	bool Testing::testAnimation_draw() {
		df::Frame fr0(3, 3, "000000000");
		df::Frame fr1(3, 3, "111111111");
		df::Sprite spr(2);
		spr.setWidth(3);
		spr.setHeight(3);
		spr.setSlowdown(1);
		spr.addFrame(fr0);
		spr.addFrame(fr1);
		spr.setColor(df::BLUE);

		df::Animation anim = df::Animation();
		anim.setSprite(&spr);

		anim.draw(df::Vector(50, 10));

		return anim.draw(df::Vector(50, 10)) == 0;
	}

	bool Testing::testAnimation_getBox() {
		df::Frame fr0(3, 3, "000000000");
		df::Frame fr1(3, 3, "111111111");
		df::Sprite spr(2);
		spr.setWidth(3);
		spr.setHeight(3);
		spr.setSlowdown(1);
		spr.addFrame(fr0);
		spr.addFrame(fr1);
		spr.setColor(df::BLUE);

		df::Animation anim = df::Animation();
		anim.setSprite(&spr);

		df::Box box = anim.getBox();

		return box.getHorizontal() == 3 && box.getVertical() == 3;
	}

	// --- SOUND ---
	void Testing::testSound() {
		writeResult(testSound_loadSound(), "testSound_loadSound");
		writeResult(testSound_play(), "testSound_play");
		writeResult(testSound_stop(), "testSound_stop");
		writeResult(testSound_pause(), "testSound_pause");
	}

	bool Testing::testSound_loadSound() {
		df::Sound test_sound = df::Sound();

		if (test_sound.loadSound("ThisShouldFail.wav") != -1) return false;
		if (test_sound.loadSound("Testing/nuke.wav") != 0) return false;
		
		return true;
	}

	bool Testing::testSound_play() {
		df::Sound test_sound = df::Sound();
		test_sound.loadSound("Testing/nuke.wav");
		test_sound.play();

		Sleep(4000);

		// Listen to hear if it plays!

		return true;
	}

	bool Testing::testSound_stop() {
		df::Sound test_sound = df::Sound();
		test_sound.loadSound("Testing/nuke.wav");
		test_sound.play();

		Sleep(1000);

		test_sound.stop();

		Sleep(1000);

		// Listen to hear if it stops!

		return true;
	}

	bool Testing::testSound_pause() {
		df::Sound test_sound = df::Sound();
		test_sound.loadSound("Testing/nuke.wav");
		test_sound.play();

		Sleep(1000);

		test_sound.pause();

		Sleep(1000);

		test_sound.play();

		Sleep(3000);

		// Listen to hear if it pauses!

		return true;
	}

	// --- MUSIC ---
	void Testing::testMusic() {
		writeResult(testMusic_loadSound(), "testMusic_loadSound");
		writeResult(testMusic_play(), "testMusic_play");
		writeResult(testMusic_stop(), "testMusic_stop");
		writeResult(testMusic_pause(), "testMusic_pause");
	}

	bool Testing::testMusic_loadSound() {
		df::Music test_music = df::Music();

		if (test_music.loadMusic("ThisShouldFail.wav") != -1) return false;
		if (test_music.loadMusic("Testing/start-music.wav") != 0) return false;

		return true;
	}

	bool Testing::testMusic_play() {
		df::Music test_music = df::Music();
		test_music.loadMusic("Testing/start-music.wav");
		test_music.play();

		Sleep(4000);

		// Listen to hear if it plays!

		return true;
	}

	bool Testing::testMusic_stop() {
		df::Music test_music = df::Music();
		test_music.loadMusic("Testing/start-music.wav");
		test_music.play();

		Sleep(1000);

		test_music.stop();

		Sleep(1000);

		// Listen to hear if it stops!

		return true;
	}

	bool Testing::testMusic_pause() {
		df::Music test_music = df::Music();
		test_music.loadMusic("Testing/start-music.wav");
		test_music.play();

		Sleep(1000);

		test_music.pause();

		Sleep(1000);

		test_music.play();

		Sleep(3000);

		// Listen to hear if it pauses!

		return true;
	}
}