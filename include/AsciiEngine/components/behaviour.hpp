#pragma once

#include "AsciiEngine/core/component.hpp"

namespace AsciiEngine
{
	struct Behaviour : Component {
		virtual void start() {};
		virtual void update() {};
		virtual void lateUpdate() {};
		virtual void onInput(int k) {};
		virtual void onDestroy() {};

		Behaviour() {}

		/* calls the start function if it has not been called yet */
		void tryStart()
		{
			if (!startCalled) {
				start();
				startCalled = true;
			}
		}

	private:
		bool startCalled = false;
	};
}
