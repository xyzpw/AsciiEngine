#include "AsciiEngine/core/save_manager.hpp"
#include <string>
#include <filesystem>
#include <fstream>

namespace AsciiEngine
{
	void SaveManager::load()
	{
		if (was_initialized)
			return;

		was_initialized = true;

		if (!std::filesystem::exists(save_location))
			return;

		std::fstream file(save_location);

		std::string ln;
		while (std::getline(file, ln)) {
			auto sep = ln.find(' ');
			if (sep == std::string::npos)
				continue;

			std::string k = ln.substr(0, sep);
			std::string v = ln.substr(sep + 1);

			saved_values[k] = v;
		}
	}

	void SaveManager::save()
	{
		if (saved_values.empty())
			return;

		std::ofstream file(save_location);
		if (!file.is_open())
			return;

		for (const auto &[k,v] : saved_values) {
			file << k << ' ' << v << '\n';
		}
	}

	bool SaveManager::keyExists(const std::string &key) const
	{
		return saved_values.contains(key);
	}
}
