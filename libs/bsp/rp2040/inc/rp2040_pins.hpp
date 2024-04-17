#pragma once

#include "pins.hpp"
#include "rp2040_regs.hpp"

enum class hal::pins::pinfunc : uint32_t
{
	SPI = 1,
	UART = 2,
	I2C = 3,
	PWM = 4,
	SIO = 5,
	PIO0 = 6,
	PIO1 = 7,
	CLOCK = 8,
	USB = 9
};
