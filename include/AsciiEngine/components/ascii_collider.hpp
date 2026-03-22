#pragma once

#include "AsciiEngine/core/component.hpp"
#include <vector>

namespace AsciiEngine
{
	struct AsciiObject;

	struct AsciiCollider : Component {
		// return: all other objects with colliders
		std::vector<AsciiObject*>& getContacts() { return contacts; }
		bool hasContacts() { return contacts.size() > 0; }

		virtual void onContact() {};

	private:
		std::vector<AsciiObject*> contacts;
	};
}
