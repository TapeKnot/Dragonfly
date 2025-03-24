#pragma once
#ifndef __VECTOR_H__
#define __VECTOR_H__

namespace df {

	class Vector {

	private:
		float m_x;	// Horizontal component
		float m_y;	// Vertical component

	public:
		
		// Create Vector with (x,y).
		Vector(float init_x, float init_y);

		// Default 2D (x,y) at (0,0).
		Vector();

		// Get/set horizontal component.
		void setX(float new_x);
		float getX() const;

		// Get/set vertical component.
		void setY(float new_y);
		float getY() const;

		// Set horizontal & vertical components.
		void setXY(float new_x, float new_y);

		// Return magnitude of vetor.
		float getMagnitude() const;

		// Normalize vector.
		void normalize();

		// Scale vector.
		void scale(float s);

		// Add two Vectors, return new Vector.
		Vector operator+(const Vector& other) const;

		// Subtract two Vectors, return new Vector.
		Vector operator-(const Vector& other) const;

		// Multiply two Vectors, return new Vector.
		Vector operator*(const Vector& other) const;

		// Divide two Vectors, return new Vector.
		Vector operator/(const Vector& other) const;

		// Compare equality of two Vectors, return result.
		bool operator==(const Vector& other) const;

		// Compare inequality of two Vectors, return result.
		bool operator!=(const Vector& other) const;

		// Iverses one Vector, return new Vector.
		Vector operator!() const;
	};
}

#endif