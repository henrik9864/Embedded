#pragma once

#include <cstdint>

namespace hal
{
	class dma
	{
	public:
		static void enable(const std::uint32_t channel);
		static void disable(const std::uint32_t channel);
	};
}