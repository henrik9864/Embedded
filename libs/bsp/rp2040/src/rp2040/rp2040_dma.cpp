#include "rp2040_dma.hpp"

void hal::dma::enable(const std::uint32_t channel)
{
	bsp::rp2040::s_dma.ch[channel].ctrl.en = 0x1;
}

void hal::dma::disable(const std::uint32_t channel)
{
	bsp::rp2040::s_dma.ch[channel].ctrl.en = 0x0;
}

void hal::dma::start(const std::uint32_t channel)
{
	bsp::rp2040::s_dma_intr.multi_chan_trigger |= 0x1 << channel;
}

static std::uint32_t channelMask = 0x0; // TODO: Move into class

std::uint32_t hal::dma::requestChannel()
{
	for (size_t i = 0; i < MAX_CHANNELS; i++)
	{
		if ((channelMask & (1 << i)) == 0x0)
		{
			channelMask |= 1 << i;
			return i;
		}
	}

	return 0;
}

void hal::dma::freeChannel(const std::uint32_t channel)
{
	channelMask &= ~(1 << channel);
}

void hal::dma::setReadAddr(const std::uint32_t channel, const volatile void* addr)
{
	bsp::rp2040::s_dma.ch[channel].read = (std::uint32_t)addr;
}

void hal::dma::setWriteAddr(const std::uint32_t channel, const volatile void* addr)
{
	bsp::rp2040::s_dma.ch[channel].write = (std::uint32_t)addr;
}

void hal::dma::setTransCount(const std::uint32_t channel, const std::uint32_t count)
{
	bsp::rp2040::s_dma.ch[channel].trans = count;
}

void hal::dma::setReadIncrement(const std::uint32_t channel, const bool increment)
{
	bsp::rp2040::s_dma.ch[channel].ctrl.incr_read = increment;
}

void hal::dma::setWriteIncrement(const std::uint32_t channel, const bool increment)
{
	bsp::rp2040::s_dma.ch[channel].ctrl.incr_write = increment;
}

void hal::dma::setDreq(const std::uint32_t channel, const std::uint32_t dreq)
{
	bsp::rp2040::s_dma.ch[channel].ctrl.treq_sel = dreq;
}

void hal::dma::setChainTo(const std::uint32_t channel, const std::uint32_t chainChannel)
{
	bsp::rp2040::s_dma.ch[channel].ctrl.chain_to = chainChannel;
}

void hal::dma::setDataSize(const std::uint32_t channel, const hal::dmaChannelSize size)
{
	switch (size)
	{
	case hal::dmaChannelSize::SIZE_8:
		bsp::rp2040::s_dma.ch[channel].ctrl.data_size = 0x0;
		break;
	case hal::dmaChannelSize::SIZE_16:
		bsp::rp2040::s_dma.ch[channel].ctrl.data_size = 0x1;
		break;
	case hal::dmaChannelSize::SIZE_32:
		bsp::rp2040::s_dma.ch[channel].ctrl.data_size = 0x2;
		break;
	default:
		break;
	}
}

void hal::dma::setRing(const std::uint32_t channel, bool write, std::uint32_t sizeBits)
{
	bsp::rp2040::s_dma.ch[channel].ctrl.ring_size = sizeBits;
	bsp::rp2040::s_dma.ch[channel].ctrl.ring_sel = write;
}

void hal::dma::setBSwap(const std::uint32_t channel, bool bswap)
{
	bsp::rp2040::s_dma.ch[channel].ctrl.bswap = bswap;
}

void hal::dma::setIrqQuite(const std::uint32_t channel, bool quiet)
{
	bsp::rp2040::s_dma.ch[channel].ctrl.irq_quite = quiet;
}

void hal::dma::setPriority(const std::uint32_t channel, bool high)
{
	bsp::rp2040::s_dma.ch[channel].ctrl.high_priority = high;
}

void hal::dma::setSniffEnable(const std::uint32_t channel, bool sniff)
{
	bsp::rp2040::s_dma.ch[channel].ctrl.sniff_en = sniff;
}