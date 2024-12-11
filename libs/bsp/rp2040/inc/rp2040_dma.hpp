#pragma once

#include "dma.hpp"
#include "pins.hpp"

#include "rp2040.hpp"

enum class hal::dmaChannelSize : std::uint32_t
{
	SIZE_8,
	SIZE_16,
	SIZE_32
};
