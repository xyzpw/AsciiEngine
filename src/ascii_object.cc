#include "AsciiEngine/ascii_object.hpp"
#include "AsciiEngine/engine.hpp"

namespace AsciiEngine
{

	void AsciiObject::destroy()
	{
		destroyed = true;

		/* notify behaviours this object was destroyed*/
		for (auto &cmp : getAllComponentsOfType<Behaviour>()) {
			if (cmp->isEnabled())
				cmp->onDestroy();
		}
	}
}
