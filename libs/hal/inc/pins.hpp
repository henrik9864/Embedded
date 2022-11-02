#pragma once

#include <cstdint>

namespace hal::pins
{
	enum class pindir
	{
		in,
		out
	};

	enum class pinfunc : uint32_t;

	typedef uint32_t pin_id;

	class gpio
	{
	public:
		static void setupPin(const pin_id&& pin, const pindir&& dir, const pinfunc&& func);
		static bool readPin(const pin_id&& pin);
		static void writePin(const pin_id&& pin, bool value);
		static void togglePin(const pin_id&& pin);
	};
}