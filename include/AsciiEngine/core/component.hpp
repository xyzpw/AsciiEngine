#pragma once

namespace AsciiEngine
{
	struct AsciiObject;

	struct Component {
		AsciiObject *owner = nullptr;
		virtual ~Component() = default;

		bool isEnabled() { return enabled; }
		void setEnabled(bool value) { enabled = value; }

	protected:
		bool enabled = true;

		bool hasOwner() { return owner != nullptr; }
	};
}
