#include "Manager.h"
#include "WorldManager.h"

namespace df {

	Manager::Manager() {
		m_type = "Manager";
		m_is_started = false;
	}

	Manager::~Manager() {

	}

	// Set type identifier of Manager.
	void Manager::setType(std::string type) {
		m_type = type;
	}

	// Get type identifier of Manager.
	std::string Manager::getType() const {
		return m_type;
	}

	// Startup Manager.
	// Return 0 if ok, else negative number.
	int Manager::startUp() {
		m_is_started = true;
		if (m_is_started) return 0;
		else return -1;
	}

	// Shutdown Manager.
	void Manager::shutDown() {
		m_is_started = false;
	}

	// Return true when startUp() was executed ok, else false.
	bool Manager::isStarted() const {
		return m_is_started;
	}

	// Send event to all Objects.
	// Return count of number of events sent.
	int Manager::onEvent(const Event* p_event) const {
		int count = 0;

		ObjectList all_objects = WM.getAllObjects();
		for (int i = 0; i < all_objects.getCount(); i++) {
			all_objects[i]->eventHandler(p_event);
			count++;
		}

		return count;
	}
}