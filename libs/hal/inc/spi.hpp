#pragma once

#include "pins.hpp"

namespace hal
{
	enum class clk_phase {
		phase_0 = 0,
		phase_1 = 1
	};

	enum class clock_polarity {
		polarity_0 = 0,
		polarity_1 = 1
	};

	enum bit_order {
		lsb = 0,
		msb = 1
	};

	class spi
	{
	public:
		static void init(const pins::pin_id&& clk, const pins::pin_id&& csn, const pins::pin_id&& tx, const pins::pin_id&& rx, const uint32_t baudrate);
		static std::uint32_t setBaudrate(const std::uint32_t baudrate);
		static void setFormat(const uint32_t dataBits, const hal::clk_phase&& phase, const hal::clock_polarity&& polarity, const hal::bit_order&& bitOrder);

		static void write();
	};
}