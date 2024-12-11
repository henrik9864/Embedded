#pragma once

#include "clock.hpp"

#include "rp2040.hpp"
#include "rp2040_pins.hpp"

enum class hal::clksrc : uint32_t
{
	GPIO0,
	GPIO1,
	USB,
	PLL_USB,
	SYSTEM,
	PLL_SYSTEM,
	XOSC,
	ROSC
};
