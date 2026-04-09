#pragma once

#include "AsciiEngine/components/controller.hpp"
#include "AsciiEngine/core/component.hpp"
#include <vector>
#include <string>
#include <memory>
#include <type_traits>
#include <utility>

namespace AsciiEngine
{
	struct AsciiObject {
		int id;
		std::string name = "";
		int layer = 0;
		bool enabled = true;

		void setLayer(int n) { layer = n; }

		std::vector<std::unique_ptr<Component>> components;

		/*
		 * Adds a controller component to move the renderer.
		 * A renderer component must exist for this to work.
		 */
		Controller* addController(MovementControlType type);

		void setEnabled(bool value) { enabled = value; }

		void destroy();

		bool isDestroyed() { return destroyed; }

		bool isActiveAndEnabled()
		{
			return (!isDestroyed() && enabled);
		}

		template<typename T, typename... Args>
		T* addComponent(Args&&... args)
		{
			static_assert(
				std::is_base_of<Component, T>::value, "T must inherit from Component");

			auto comp = std::make_unique<T>(std::forward<Args>(args)...);
			comp->owner = this;

			T* raw = comp.get();
			components.push_back(std::move(comp));

			return raw;
		}

		template<typename T>
		T* getComponent()
		{
			for (auto &cmp : components) {
				auto casted = dynamic_cast<T*>(cmp.get());
				if (casted)
					return casted;
			}

			return nullptr;
		}

		template<typename T>
		std::vector<T*> getAllComponentsOfType()
		{
			std::vector<T*> result;

			for (auto &cmp : components) {
				auto casted = dynamic_cast<T*>(cmp.get());
				if (casted)
					result.push_back(casted);
			}

			return result;
		}

		template<typename T, typename... Args>
		T* getOrAddComponent(Args&&... args)
		{
			static_assert(std::is_base_of<Component, T>::value,
				"T must inherit component");

			T* t = nullptr;

			if (!hasComponent<T>()) {
				std::unique_ptr<T> tmp = std::make_unique<T>(std::forward<Args>(args)...);
				tmp->owner = this;
				t = tmp.get();
				components.push_back(std::move(tmp));
			} else {
				t = getComponent<T>();
			}

			return t;
		}

		template<typename T>
		bool hasComponent()
		{
			auto cmp = getComponent<T>();
			return cmp != nullptr;
		}

		template<typename ...T>
		bool hasAllComponents()
		{
			return (hasComponent<T>() && ...);
		}

		template<typename T>
		bool hasEnabledComponent()
		{
			auto *cmp = getComponent<T>();

			if (cmp != nullptr)
				return cmp->isEnabled();

			return false;
		}

	private:
		AsciiObject& operator=(const AsciiObject&) = delete;

		bool destroyed = false;
	};
}
