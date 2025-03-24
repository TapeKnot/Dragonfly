#include <stdio.h>
#include <stdarg.h>
#include <SFML/System.hpp>
#include <sstream>
#include "utility.h"
#include "Managers/WorldManager.h"
using std::stringstream;

namespace df {

	// Returns a time string formatted as HH:MM:SS
	char* utility::getTimeString() {
		// String to return, made 'static' so persists.
		static char time_str[30];

		// System calls to get time.
		time_t now;
		if (time(&now) == NULL) {
			printf("ERROR in utility/getTimeString: time() returned NULL.");
		}
		struct tm* p_time = localtime(&now);
		if (p_time == nullptr) {
			printf("ERROR in utility/getTimeString: localtime() returned NULL.");
		}

		// '02' gives two digits, '%d' for integers.
		sprintf(time_str, "%02d:%02d:%02d",
			p_time->tm_hour,
			p_time->tm_min,
			p_time->tm_sec);

		return time_str;
	}

	// Returns true if two positions intersect, else false.
	bool utility::positionsIntersect(Vector p1, Vector p2) {
		return abs(p1.getX() - p2.getX()) <= 1 &&
			abs(p1.getY() - p2.getY()) <= 1;
	}

	// Remove the carriage return ('\r') from line
	// (if there - typical of Windows).
	void utility::discardCR(std::string& str) {
		if (str.size() > 0 && str[str.size() - 1] == '\r')
			str.erase(str.size() - 1);
	}

	// Return true if boxes intersect, else false.
	bool utility::boxIntersectsBox(Box A, Box B) {
		float Ax1 = A.getCorner().getX();
		float Bx1 = B.getCorner().getX();
		float Ay1 = A.getCorner().getY();
		float By1 = B.getCorner().getY();

		float Ax2 = A.getCorner().getX() + A.getHorizontal();
		float Bx2 = B.getCorner().getX() + B.getHorizontal();
		float Ay2 = A.getCorner().getY() + A.getVertical();
		float By2 = B.getCorner().getY() + B.getVertical();

		// Test horizontal overlap (x_overlap).
		bool x_overlap = (Bx1 <= Ax1 && Ax1 <= Bx2)	// Either left side of A in B?
			|| (Ax1 <= Bx1 && Bx1 <= Ax2);			// Or left side of B in A?

		// Test vertical overlap (y_overlap).
		bool y_overlap = (By1 <= Ay1 && Ay1 <= By2)	// Either top side of A in B?
			|| (Ay1 <= By1 && By1 <= Ay2);			// Or top side of B in A?

		return x_overlap && y_overlap;
	}

	// Convert relative bounding Box for Object to absolute world Box.
	Box utility::getWorldBox(const Object* p_o) {
		return getWorldBox(p_o, p_o->getPosition());
	}

	// Convert relative bounding Box for Object to absolute world Box.
	Box utility::getWorldBox(const Object* p_o, Vector where) {
		Box box = p_o->getBox();
		Vector corner = box.getCorner();
		corner.setX(corner.getX() + where.getX());
		corner.setY(corner.getY() + where.getY());
		box.setCorner(corner);

		return box;
	}

	// Convert world position to view position.
	Vector utility::worldToView(Vector world_pos) {
		Vector view_origin = WM.getView().getCorner();
		float view_x = view_origin.getX();
		float view_y = view_origin.getY();
		Vector view_pos(world_pos.getX() - view_x, world_pos.getY() - view_y);
		return view_pos;
	}

	// Convert view position to world position.
	Vector utility::viewToWorld(Vector view_pos) {
		Vector world_origin = WM.getBoundary().getCorner();
		float world_x = world_origin.getX();
		float world_y = world_origin.getY();
		Vector world_pos(view_pos.getX() - world_x, view_pos.getY() - world_y);
		return world_pos;
	}

	// Convert int to a string, returning string.
	std::string utility::toString(int i) {
		std::stringstream ss;	// Create stringstream.
		ss << i;				// Add number to stream.
		return ss.str();		// Return string with contents of stream.
	}
}