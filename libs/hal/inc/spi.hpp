#pragma once

#include "pins.hpp"

namespace hal
{
	class spi
	{
	public:
		static void init(const pins::pin_id&& clk, const pins::pin_id&& tx, const pins::pin_id&& rx, const uint32_t&& baudrate);
	};
}