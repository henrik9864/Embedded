#pragma once

#include <cstdint>
#include "pins.hpp"

namespace hal
{
	enum class clksrc : uint32_t;

	class clock
	{
	public:
		static void init();

		static void setupGpio(const pins::pin_id&& pin, const hal::clksrc&& src);
		static void startGpio(const pins::pin_id&& pin);
		static void stopGpio(const pins::pin_id&& pin);

		static uint32_t getHz();
	};
}