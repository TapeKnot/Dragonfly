#include "WorldManager.h"
#include "../ObjectList.h"
#include "../utility.h"
#include "../Events/EventCollision.h"
#include "DisplayManager.h"
#include "../Events/EventOut.h"
#include "../ViewObject.h"

namespace df {

	WorldManager::WorldManager() {
		setType("WorldManager");

		m_boundary = Box();
		m_view = Box();
	}

	// Get the singleton instance of the WorldManager.
	WorldManager& WorldManager::getInstance() {
		static WorldManager single;
		return single;
	}

	// Startup game world (initialize everything to empty).
	int WorldManager::startUp() {
		Manager::startUp();

		return 0;
	}

	// Shutdown game world (delete all game world Objects).
	void WorldManager::shutDown() {
		ObjectList list = m_updates;

		for (int i = 0; i < m_updates.getCount(); i++) {
			delete(list[i]);
		}

		Manager::shutDown();
	}

	// Insert Object into world. Return 0 if ok, else -1.
	int WorldManager::insertObject(Object* p_o) {
		return m_updates.insert(p_o);
	}

	// Remove Object from world. Return 0 if ok, else -1.
	int WorldManager::removeObject(Object* p_o) {
		return m_updates.remove(p_o);
	}

	// Return list of all Objects in world.
	ObjectList WorldManager::getAllObjects() const {
		return m_updates;
	}

	// Return list of all Objects in world matching type.
	ObjectList WorldManager::objectsOfType(std::string type) {
		ObjectList list;

		for (int i = 0; i < m_updates.getCount(); i++) {
			// If Object in list has same type, add to new list.
			if (m_updates[i]->getType() == type) {
				list.insert(m_updates[i]);
			}
		}

		return list;
	}

	// Update world.
	// Delete Objects marked for deletion.
	void WorldManager::update() {
		for (int i = 0; i < m_deletions.getCount(); i++) {
			delete(m_deletions[i]);
		}

		// Clear list for next update phase.
		m_deletions.clear();

		// Iterate through all Objects.
		for (int i = 0; i < m_updates.getCount(); i++) {
			Object* obj = m_updates[i];

			// Add velocity to position
			Vector new_pos = obj->predictPosition();

			// If Object should change position, then move.
			//if (new_pos != obj->getPosition()) {
			if (new_pos.getX() != obj->getPosition().getX() ||
				new_pos.getY() != obj->getPosition().getY()) {
				moveObject(obj, new_pos);
			}
		}
	}

	// Indicate Object is to be deleted at end of current game loop.
	// Return 0 if ok, else -1.
	int WorldManager::markForDelete(Object* p_o) {

		// Object might have already been marked, so only add once.
		for (int i = 0; i < m_deletions.getCount(); i++) {
			if (m_deletions[i] == p_o) {
				return 0;
			}
		}

		// Object not in list, so add.
		return m_deletions.insert(p_o);
	}

	// Draw all Objects.
	void WorldManager::draw() {
		for (int i = 0; i <= MAX_ALTITUDE; i++) {
			for (int j = 0; j < m_updates.getCount(); j++) {
				Object* temp_obj = m_updates[j];

				// Bounding box coordinates are relative to Object,
				// so convert to world coordinates.
				Box temp_box = utility::getWorldBox(temp_obj);

				// Only draw if Object would be visible on window (intersects view).
				if (temp_obj->getAltitude() == i && (utility::boxIntersectsBox(temp_box, m_view) || dynamic_cast <ViewObject*>(temp_obj))) {
					temp_obj->draw();
				}
			}
		}
	}

	// Return list of Objects collided with at position 'where'.
	// Collisions only with solid Objects.
	// Does not consider if p_o is solid or not.
	ObjectList WorldManager::getCollisions(const Object* p_o, Vector where) {

		ObjectList collisions = ObjectList();

		// Iterate through all Objects.
		for (int i = 0; i < m_updates.getCount(); i++) {
			Object* p_temp_o = m_updates[i];

			if (p_temp_o == p_o) continue;	// Do not consider self.

			// World position bounding box for object at where.
			Box b = utility::getWorldBox(p_o, where);

			// World position bounding box for other object.
			Box b_temp = utility::getWorldBox(p_temp_o);

			// Same location and both solid?
			if (utility::boxIntersectsBox(b, b_temp)
				&& p_temp_o->isSolid()) {
				collisions.insert(p_temp_o);
			}
		}

		return collisions;
	}

	// Move Object.
	// If collision with solid, send collision events.
	// If no collision with solid, move ok else don't move Object.
	// If Object is spectral, move ok.
	// Return 0 if move ok, else -1 if collision with solid.
	int WorldManager::moveObject(Object* p_o, Vector where) {
		if (p_o->isSolid()) {	// Need to be solid for collisions.

			// Get collisions.
			ObjectList collisions = getCollisions(p_o, where);

			if (!collisions.isEmpty()) {

				bool can_move = true;

				// Iterate over list.
				for (int i = 0; i < collisions.getCount(); i++) {
					Object* p_temp_o = collisions[i];

					// Create collision event.
					EventCollision c(p_o, p_temp_o, where);

					// Send to both objects.
					p_o->eventHandler(&c);
					p_temp_o->eventHandler(&c);

					// If both HARD, then cannot move.
					if (p_temp_o->getSolidness() == HARD && p_o->getSolidness() == HARD)
						can_move = false;	// Can't move.
				}

				if (!can_move) return -1;
			}
		}

		// If here, no collision between two HARD objects so allow move.
		Box orig_box = utility::getWorldBox(p_o);	// Original bounding box.
		p_o->setPosition(where);					// Move object.
		Box new_box = utility::getWorldBox(p_o);	// New bounding box.

		// If view is following this object, adjust view.
		if (p_view_following == p_o)
			setViewPosition(p_o->getPosition());

		// If object moved from inside to outside world, generate "out of bounds" event.
		if (utility::boxIntersectsBox(orig_box, m_boundary)			// Was in bounds?
			&& !utility::boxIntersectsBox(new_box, m_boundary)) {	// Now out of bounds?
			EventOut ov;											// Create "out" event.
			p_o->eventHandler(&ov);									// Send to Object.
		}

		// All is well.
		return 0;	// Move was ok.
	}

	// Set game world boundary.
	void WorldManager::setBoundary(Box new_boundary) {
		m_boundary = new_boundary;
	}

	// Get game world boundary.
	Box WorldManager::getBoundary() const {
		return m_boundary;
	}

	// Set player view of game world.
	void WorldManager::setView(Box new_view) {
		m_view = new_view;
	}

	// Get player view of game world.
	Box WorldManager::getView() const {
		return m_view;
	}

	// Set view to center window on position view_pos.
	// View edge will not go beyond world boundary.
	void WorldManager::setViewPosition(Vector view_pos) {
		
		// Make sure horizontal not out of world boundary.
		float x = view_pos.getX() - m_view.getHorizontal() / 2;
		if (x + m_view.getHorizontal() > m_boundary.getHorizontal())
			x = m_boundary.getHorizontal() - m_view.getHorizontal();
		if (x < 0)
			x = 0;

		// Make sure horizontal not out of world boundary.
		float y = view_pos.getY() - m_view.getVertical() / 2;
		if (y + m_view.getVertical() > m_boundary.getVertical())
			y = m_boundary.getVertical() - m_view.getVertical();
		if (y < 0)
			y = 0;

		// Set view.
		Vector new_corner(x, y);
		m_view.setCorner(new_corner);
	}

	// Set view to center window on Object.
	// Set to NULL to stop following.
	// If p_new_view_following not legit, return -1 else return 0.
	int WorldManager::setViewFollowing(Object* p_new_view_following) {
		
		// Set to NULL to turn 'off' following.
		if (p_new_view_following == NULL) {
			p_view_following = NULL;
			return 0;
		}

		bool found = false;

		for (int i = 0; i < m_updates.getCount(); i++) {
			if (m_updates[i] == p_new_view_following)
				found = true;
		}

		if (found) {
			p_view_following = p_new_view_following;
			setViewPosition(p_view_following->getPosition());
			return 0;
		}

		// If we get here, was not legit. Don't change current view.
		return -1;
	}
}