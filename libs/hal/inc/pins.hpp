#pragma once

#include <cstdint>

namespace hal::pins
{
	enum class pindir
	{
		in,
		out
	};

	typedef uint32_t pin_id;

	class gpio
	{
	public:
		static void setupPin(const pin_id&& pin, const pindir&& dir);
		static bool readPin(const pin_id&& pin);
		static void writePin(const pin_id&& pin, bool value);
		static void togglePin(const pin_id&& pin);
	};
}