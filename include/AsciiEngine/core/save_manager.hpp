#pragma once

#include <string>
#include <map>
#include <type_traits>

namespace AsciiEngine
{
	struct SaveManager {
		/*
		 * updates cached data to save file
		 */
		void load();

		/*
		 * save stored data to file
		 */
		void save();

		/*
		 * save user info
		 * @key: name of retrievable value
		 * @value: value to be stored
		 *
		 * NOTE: this does not update the file
		 */
		template<typename T>
		void setValue(const std::string &key, const T &value)
		{
			static_assert(std::is_arithmetic_v<T> ||
				      std::is_same_v<T, std::string>);

			if constexpr (std::is_same_v<T, std::string>) {
				saved_values[key] = value;
			} else {
				saved_values[key] = std::to_string(value);
			}
		}

		/*
		 * retrieve a value from the local save file
		 */
		template<typename T>
		T getValue(const std::string &key) const
		{
			static_assert(std::is_arithmetic_v<T> ||
				      std::is_same_v<T, std::string>);

			auto it = saved_values.find(key);

			if (it == saved_values.end())
				return T{};

			if constexpr (std::is_same_v<T, std::string>) {
				return it->second;
			} else if constexpr (std::is_same_v<T, bool>) {
				return it->second == "1" ||
				       it->second == "true" ||
				       it->second == "TRUE";
			} else if constexpr (std::is_integral_v<T>) {
				return static_cast<T>(std::stoll(it->second));
			} else if constexpr (std::is_floating_point_v<T>) {
				return static_cast<T>(std::stod(it->second));
			}
		}

		/*
		 * retrieve a value from the local file
		 * @defaultValue: return value if the key does not exist
		 */
		template<typename T>
		T getValue(const std::string &key,
			   const T &defaultValue) const
		{
			return keyExists(key) ? getValue<T>(key) : defaultValue;
		}

		/*
		 * remove a saved key from the local file
		 */
		void remove(const std::string &key);

		/*
		 * return: true if the key exists in local file
		 */
		bool keyExists(const std::string &key) const;

		private:
		bool was_initialized = false;
		const std::string save_location = "saved.txt";

		// data of the local save
		std::map<std::string, std::string> saved_values;
	};
}
