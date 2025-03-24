#include <stdexcept>
#include "ObjectList.h"

namespace df {

	// Default constructor.
	ObjectList::ObjectList() {
		m_count = 0;
		m_p_obj[0] = {};
	}

	// Insert object pointer in list.
	// Return 0 if ok, else -1.
	int ObjectList::insert(Object* p_o) {
		if (m_count == MAX_OBJECTS) return -1;

		m_p_obj[m_count] = p_o;
		m_count++;
		
		return 0;
	}

	// Remove object pointer from list.
	// Return 0 if found, else -1.
	int ObjectList::remove(Object* p_o) {
		for (int i = 0; i < m_count; i++) {
			if (m_p_obj[i] == p_o) {						// Found...
				for (int j = i; j < m_count - 1; j++) {		// ...so scoot over!
					m_p_obj[j] = m_p_obj[j + 1];
				}
				m_count--;
				return 0;
			}
		}

		return -1;
	}

	// Clear list (setting count to 0).
	void ObjectList::clear() {
		m_count = 0;
	}

	// Return count of number of objects in list.
	int ObjectList::getCount() const {
		return m_count;
	}

	// Return true if list is empty, else false.
	bool ObjectList::isEmpty() const {
		return m_count == 0;
	}

	// Return true if list is full, else false.
	bool ObjectList::isFull() const {
		return m_count == MAX_OBJECTS;
	}

	// Index into list.
	Object*& ObjectList::operator[](int index) {
		if (index >= m_count || index < 0) throw std::out_of_range("Invalid index!");

		return m_p_obj[index];
	}
}