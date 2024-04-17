#pragma once

#include <cstdint>

namespace hal
{
	class clock
	{
	public:
		static void init();

		static uint32_t getHz();
	};
}