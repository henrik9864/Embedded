#include "rp2040_dma.hpp"

void hal::dma::enable(const std::uint32_t channel)
{
	bsp::rp2040::s_dma_intr.inte0 |= (1 << channel);
}

void hal::dma::disable(const std::uint32_t channel)
{
	bsp::rp2040::s_dma_intr.inte0 &= ~(1 << channel);
}