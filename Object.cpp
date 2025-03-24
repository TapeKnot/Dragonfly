#include "Object.h"
#include "Managers/WorldManager.h"
#include "Managers/LogManager.h"
#include "Managers/DisplayManager.h"
#include "Managers/ResourceManager.h"

namespace df {

	// Construct Object. Set default parameters and add to game world (WorldManager).
	Object::Object() {
		static int max_id = 0;

		m_id = max_id;
		max_id++;

		m_type = "Object";
		m_position = Vector();
		m_altitude = MAX_ALTITUDE / 2;
		m_direction = Vector();
		m_speed = 0.0f;
		m_solidness = HARD;
		m_box = Box(Vector(m_position.getX() - 0.5, m_position.getY() - 0.5), 1, 1);

		// Add self to game world.
		WM.insertObject(this);
	}

	// Destroy Object and remove from game world (WorldManager).
	Object::~Object() {
		WM.removeObject(this);
	}

	// Set Object id.
	void Object::setId(int new_id) {
		m_id = new_id;
	}

	// Get Object id.
	int Object::getId() const {
		return m_id;
	}

	// Set type identifier of Object.
	void Object::setType(std::string new_type) {
		m_type = new_type;
	}

	// Get type identifier of Object.
	std::string Object::getType() const {
		return m_type;
	}

	// Set position of Object.
	void Object::setPosition(Vector new_pos) {
		m_position = new_pos;
	}

	// Get position of Object.
	Vector Object::getPosition() const {
		return m_position;
	}

	void Object::update() {

	}

	// Handle event (default is to ignore everything).
	// Return 0 if ignored, else 1 if handled.
	int Object::eventHandler(const Event* p_e) {
		if (p_e->getType() == "df::undefined") {
			LM.writeLog(1, "\tObject.eventHandler: Event Handled.");
		}
		else if (p_e->getType() == "df::step") {
			LM.writeLog(1, "\tObject.eventHandler: EventStep Handled.");
		}

		return 0;
	}

	// Set altitude of Object, with checks for range [0, MAX_ALTITUDE].
	// Return 0 if ok, else -1.
	int Object::setAltitude(int new_altitude) {
		if (new_altitude >= 0 && new_altitude <= MAX_ALTITUDE) {
			m_altitude = new_altitude;
			return 0;
		}
		else return -1;
	}

	// Return altitude of Object.
	int Object::getAltitude() const {
		return m_altitude;
	}

	// Set speed of Object.
	void Object::setSpeed(float speed) {
		m_speed = speed;
	}

	// Get speed of Object.
	float Object::getSpeed() const {
		return m_speed;
	}

	// Set direction of Object.
	void Object::setDirection(Vector new_direction) {
		m_direction = new_direction;
	}

	// Get direction of Object.
	Vector Object::getDirection() const {
		return m_direction;
	}

	// Set direction and speed of Object.
	void Object::setVelocity(Vector new_velocity) {
		m_speed = new_velocity.getMagnitude();

		Vector temp_vec = new_velocity;
		temp_vec.normalize();

		m_direction = Vector(temp_vec.getX(), temp_vec.getY());
	}

	// Get velocity of Object based on direction and speed.
	Vector Object::getVelocity() const {
		Vector temp_vec = m_direction;
		temp_vec.scale(m_speed);

		return temp_vec;
	}

	// Predict Object position based on speed and direction.
	// Return predicted position.
	Vector Object::predictPosition() {
		// Add velocity to position.
		Vector new_pos = m_position + getVelocity();

		// Return new position.
		return new_pos;
	}

	// Returns true if HARD or SOFT, and false otherwise.
	bool Object::isSolid() const {
		return m_solidness == HARD || m_solidness == SOFT;
	}

	// Set object solidness, with checks for consistency.
	// Return 0 if ok, else -1.
	int Object::setSolidness(Solidness new_solid) {
		if (new_solid == HARD || new_solid == SOFT || new_solid == SPECTRAL) {
			m_solidness = new_solid;
			return 0;
		}
		else return -1;
	}

	// Return object solidness.
	Solidness Object::getSolidness() const {
		return m_solidness;
	}

	// Set Sprite for this Object to animate.
	// Return 0 if ok, else -1.
	int Object::setSprite(std::string sprite_label) {
		Sprite* spr(RM.getSprite(sprite_label));

		if (spr == NULL) return -1;

		m_animation.setSprite(spr);

		setBox(m_animation.getBox());

		return 0;
	}

	// Set Animation for this Object to a new one.
	// Set bounding box to size of associated Sprite.
	void Object::setAnimation(Animation new_animation) {
		m_animation = new_animation;
	}

	// Get Animation for this Object.
	Animation Object::getAnimation() const {
		return m_animation;
	}

	// Draw Object Animation.
	// Return 0 if ok, else -1.
	int Object::draw() {
		df::Vector pos = getPosition();

		return m_animation.draw(pos);
	}

	// Set Object's bounding box.
	void Object::setBox(Box new_box) {
		m_box = new_box;
	}

	// Get Object's bounding box.
	Box Object::getBox() const {
		return m_box;
	}
}