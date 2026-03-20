#include "AsciiEngine/ascii_object.hpp"
#include "AsciiEngine/engine.hpp"

namespace AsciiEngine
{

	void AsciiObject::destroy()
	{
		destroyed = true;
	}
}
