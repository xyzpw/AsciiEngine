#pragma once

// not an api

#include <vector>
#include <memory>
#include <string>
#include <functional>
#include <unordered_map>
#include "AsciiEngine/components/controller.hpp"
#include "AsciiEngine/components/behaviour.hpp"
#include "AsciiEngine/common/color.hpp"
#include "AsciiEngine/common/sprite.hpp"
#include "AsciiEngine/math/vector2.hpp"
#include "AsciiEngine/math/ray.hpp"
#include "AsciiEngine/physics/raycast_hit.hpp"
#include "AsciiEngine/core/debug.hpp"

namespace AsciiEngine
{
	#define KEYBOARD_REPEAT_RATE_MS 25

	inline std::unordered_map<int, ColorPair> colorRegistry;

	struct AsciiObject;
	struct Scene;

	struct Engine {
		static Engine& instance();

		Debug debug;

		int maxColumns, maxRows;
		int getMaxColumns() { return maxColumns; }
		int getMaxRows() { return maxRows; }
		// column at display midpoint
		int getMidpointCol() { return (maxColumns - 1) / 2; }
		// row at display midpoint
		int getMidpointRow() { return (maxRows - 1) / 2; }
		/* is the specified point within terminal */
		bool isInDisplay(int col, int row);
		bool isInDisplay(const Math::Vector2 &v);

		bool isRunning() { return running; }

		int currentFrame = 0;
		float deltaTime;
		bool currentlyInFrame = false;
		Scene* activeScene;

		Math::Vector2 gravity = Math::Vector2(0, 9.80665f);

		/* create an empty ascii object */
		AsciiObject* createAsciiObject();
		// create ascii object with a name
		AsciiObject* createAsciiObject(const std::string &name);
		/* create ascii object with a sprite renderer component */
		AsciiObject* createAsciiObject(int col, int row, const Sprite &sprite);
		/*
		 * @name: scene name
		 * @load: load the scene upon creation?
		 */
		Scene* createScene(const std::string &name, bool load = false);

		/*
		 * Register an input key.
		 *
		 * @key: input key
		 * @action: function to run on key input
		 */
		void registerKeyAction(int key, std::function<void()> action);
		// register key to quit engine
		void registerQuitKey(int key)
		{
			registerKeyAction(key, [&]() { quit(); });
		}

		void run();
		void quit();
		void loadScene(const std::string &name);
		void unloadScene();
		// run call before quitting
		void onQuit(std::function<void()> call) { onQuitFns.push_back(call); };
		// run after starting
		void onStart(std::function<void()> call) { onStartFns.push_back(call); }

		/*
		 * return: true if the key is detected this frame
		 */
		bool isKeyPressed(int k);

		/*
		 * return: true only on the frame the key is first detected
		 *
		 * This ignores the delayed "held" state and only triggers
		 * on new input.
		 */
		bool isKeyJustPressed(int k);

		/*
		 * return: true if the key is considered held
		 *
		 * This does not reflect the true physical key state;
		 * a key remains active for a short time after input, allowing
		 * held keys to be simulated.
		 */
		bool isKeyHeld(int k);

		/*
		 * return: true if the key was active but is no longer active
		 *
		 * This is based on the input time window, not the true
		 * physical release of the key
		 */
		bool isKeyReleased(int k);

		/*
		 * return: the current active key
		 *
		 * This is based on the input time window and may not
		 * reflect the true physical key being pressed.
		 */
		int currentActiveKey();

		/*
		 * return: how long the current key has been active (in seconds)
		 *
		 * This uses the simulated active state, not true key
		 * hold time.
		 */
		float currentKeyDownTime();

		// return: true if the scene is currently displayed
		bool isSceneActive(const std::string &name);

		void setTickInterval(int ms);

		// run call after the current frame ends
		void runAfterFrame(std::function<void()> call);

		// call function after $t$ seconds
		void runAfterSeconds(float seconds, std::function<void()> call);

		std::vector<Physics::RaycastHit> rayCircle(const Math::Vector2 &origin, float distance);
		bool raycast(const Math::Ray &ray, float distance, Physics::RaycastHit &out);
		std::vector<Physics::RaycastHit> raycastAll(const Math::Ray &ray, float distance);

		/* return: object of which occurs at this point on terminal */
		AsciiObject* getAsciiObjectAt(int col, int row);
		AsciiObject* getAsciiObjectAt(const Math::Vector2 &v);

		std::vector<AsciiObject*> getAllAsciiObjects();
		std::vector<AsciiObject*> getAllAsciiObjectsByName(const std::string &name);
		AsciiObject* getAsciiObjectByName(const std::string &name);
		AsciiObject* getAsciiObjectById(int id);

	private:
		Engine() = default;
		~Engine() = default;

		Engine(const Engine&) = delete;
		Engine& operator=(const Engine&) = delete;

		bool running = false;
		int TICK_INTERVAL_MS = 16;

		std::vector<std::unique_ptr<AsciiObject>> asciiObjects;
		std::vector<std::unique_ptr<Scene>> scenes;
		std::vector<std::function<void()>> onStartFns;
		std::vector<std::function<void()>> onQuitFns;
		unsigned int objectCounter = 0;

		// sort global objects list in ascending order by their layer
		void sortObjectsByLayer();

		void renderScene();
		void renderHud();
		void drawObjectSprites();
		// display and update animations
		void handleAnimations();

		void checkSpriteColliders();
		void checkPhysicsBodies();

		void processAllControllers();
		void processAllConditionalActions();
		void processController(Controller *ctrl);

		void updateAllBehaviours();
		void lateUpdateAllBehaviours();

		void callOnBehaviours(void (Behaviour::*method)());
		/* Call a function on an object if it is active and enabled. */
		void callOnAllActiveObjects(std::function<void(AsciiObject*)> call);
		void callOnAllActiveObjects(std::function<void(AsciiObject*)> call,
				std::function<bool(AsciiObject*)> cond);
	};
}
