#include "EventCollision.h"

namespace df {

	// Create collision event at (0,0) with o1 and o2 NULL.
	EventCollision::EventCollision() {
		setType(COLLISION_EVENT);
		m_pos = Vector();
		m_p_obj1 = NULL;
		m_p_obj2 = NULL;
	}

	// Create collision event between o1 and o2 at position p.
	// Object o1 'caused' collision by moving into object o2.
	EventCollision::EventCollision(Object* p_o1, Object* p_o2, Vector p) {
		setType(COLLISION_EVENT);
		m_pos = p;
		m_p_obj1 = p_o1;
		m_p_obj2 = p_o2;
	}

	// Set object that caused collision.
	void EventCollision::setObject1(Object* p_new_o1) {
		m_p_obj1 = p_new_o1;
	}

	// Return object that caused collision.
	Object* EventCollision::getObject1() const {
		return m_p_obj1;
	}

	// Set object that was collided with.
	void EventCollision::setObject2(Object* p_new_o2) {
		m_p_obj2 = p_new_o2;
	}

	// Return object that was collided with.
	Object* EventCollision::getObject2() const {
		return m_p_obj2;
	}

	// Set position of collision.
	void EventCollision::setPosition(Vector new_pos) {
		m_pos = new_pos;
	}

	// Return position of collision.
	Vector EventCollision::getPosition() const {
		return m_pos;
	}
}