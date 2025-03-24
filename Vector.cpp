#include <cmath>
#include "Vector.h"

namespace df {

	// Create Vector with (x,y).
	Vector::Vector(float init_x, float init_y) {
		m_x = init_x;
		m_y = init_y;
	}

	// Default 2D (x,y) at (0,0).
	Vector::Vector() {
		m_x = 0;
		m_y = 0;
	}

	// Get/set horizontal component.
	void Vector::setX(float new_x) {
		m_x = new_x;
	}
	float Vector::getX() const {
		return m_x;
	}

	// Get/set vertical component.
	void Vector::setY(float new_y) {
		m_y = new_y;
	}
	float Vector::getY() const {
		return m_y;
	}

	// Set horizontal & vertical components.
	void Vector::setXY(float new_x, float new_y) {
		m_x = new_x;
		m_y = new_y;
	}

	// Return magnitude of vetor.
	float Vector::getMagnitude() const {
		return sqrt(m_x * m_x + m_y * m_y);
	}

	// Normalize vector.
	void Vector::normalize() {
		float length = getMagnitude();

		if (length > 0) {
			m_x /= length;
			m_y /= length;
		}
	}

	// Scale vector.
	void Vector::scale(float s) {
		m_x *= s;
		m_y *= s;
	}

	// Add two Vectors, return new Vector.
	Vector Vector::operator+(const Vector& other) const {
		Vector newVec;
		newVec.m_x = this->m_x + other.m_x;
		newVec.m_y = this->m_y + other.m_y;

		return newVec;
	}

	// Subtract two Vectors, return new Vector.
	Vector Vector::operator-(const Vector& other) const {
		Vector newVec;
		newVec.m_x = this->m_x - other.m_x;
		newVec.m_y = this->m_y - other.m_y;

		return newVec;
	}

	// Multiply two Vectors, return new Vector.
	Vector Vector::operator*(const Vector& other) const {
		Vector newVec;
		newVec.m_x = this->m_x * other.m_x;
		newVec.m_y = this->m_y * other.m_y;

		return newVec;
	}

	// Divide two Vectors, return new Vector.
	Vector Vector::operator/(const Vector& other) const {
		Vector newVec;
		newVec.m_x = this->m_x / other.m_x;
		newVec.m_y = this->m_y / other.m_y;

		return newVec;
	}

	// Compare equality of two Vectors, return result.
	bool Vector::operator==(const Vector& other) const {
		return this->m_x == other.m_x && this->m_y == other.m_y;
	}

	// Compare inequality of two Vectors, return result.
	bool Vector::operator!=(const Vector& other) const {
		return this->m_x != other.m_x && this->m_y != other.m_y;
	}

	// Iverses one Vector, return new Vector.
	Vector Vector::operator!() const {
		Vector newVec;
		newVec.m_x = this->m_x * -1;
		newVec.m_y = this->m_y * -1;

		return newVec;
	}
}