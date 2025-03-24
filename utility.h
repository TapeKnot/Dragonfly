#pragma once
#include <SFML/System.hpp>
#include "Vector.h"
#include "Box.h"
#include "Object.h"

namespace df {

	class utility {
	public:
		static char* getTimeString();

		// Returns true if two positions intersect, else false.
		static bool positionsIntersect(Vector p1, Vector p2);

		// Remove the carriage return ('\r') from line
		// (if there - typical of Windows).
		static void discardCR(std::string& str);

		// Return true if boxes intersect, else false.
		static bool boxIntersectsBox(Box A, Box B);

		// Convert relative bounding Box for Object to absolute world Box.
		static Box getWorldBox(const Object* p_o);

		// Convert relative bounding Box for Object to absolute world Box.
		static Box getWorldBox(const Object* p_o, Vector where);

		// Convert world position to view position.
		static Vector worldToView(Vector world_pos);

		// Convert view position to world position.
		static Vector viewToWorld(Vector view_pos);

		// Convert int to a string, returning string.
		static std::string toString(int i);
	};

}
