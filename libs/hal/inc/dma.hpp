#pragma once

#include <cstdint>

namespace hal
{
	enum class dmaChannelSize : std::uint32_t;

	class dma
	{
	public:
		static void setReadAddr(const std::uint32_t channel, const volatile void* addr);
		static void setWriteAddr(const std::uint32_t channel, const volatile void* addr);
		static void setTransCount(const std::uint32_t channel, const std::uint32_t count);
		static void setReadIncrement(const std::uint32_t channel, const bool increment);
		static void setWriteIncrement(const std::uint32_t channel, const bool increment);
		static void setDreq(const std::uint32_t channel, const std::uint32_t dreq);
		static void setChainTo(const std::uint32_t channel, const std::uint32_t chainChannel);
		static void setDataSize(const std::uint32_t channel, const hal::dmaChannelSize size);
		static void setRing(const std::uint32_t channel, bool write, std::uint32_t sizeBits);
		static void setBSwap(const std::uint32_t channel, bool bswap);
		static void setIrqQuite(const std::uint32_t channel, bool quiet);
		static void setPriority(const std::uint32_t channel, bool high);
		static void setSniffEnable(const std::uint32_t channel, bool sniff);

		static void setDefault(const std::uint32_t channel)
		{
			hal::dma::setReadIncrement(channel, true);
			hal::dma::setWriteIncrement(channel, false);
			hal::dma::setDreq(channel, 63);
			hal::dma::setChainTo(channel, channel);
			hal::dma::setRing(channel, false, 0);
			hal::dma::setBSwap(channel, false);
			hal::dma::setIrqQuite(channel, false);
			hal::dma::disable(channel);
			hal::dma::setSniffEnable(channel, false);
			hal::dma::setPriority(channel, false);
		}

		static void enable(const std::uint32_t channel);
		static void disable(const std::uint32_t channel);
		static void start(const std::uint32_t channel);

		static std::uint32_t requestChannel();
		static void freeChannel(const std::uint32_t channel);
	private:
		static const std::uint32_t MAX_CHANNELS = 12;
	};
}