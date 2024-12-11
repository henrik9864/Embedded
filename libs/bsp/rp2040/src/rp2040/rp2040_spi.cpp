#include "rp2040_spi.hpp"

using namespace hal::pins;

void hal::spi::init(const pins::pin_id&& clk, const pins::pin_id&& csn, const pins::pin_id&& rx, const pins::pin_id&& tx, const uint32_t baudrate)
{
	// Reset SPI and wait
	bsp::rp2040::s_resets.reset.spi_1 = 1;
	bsp::rp2040::s_resets.reset.spi_1 = 0;
	while (!bsp::rp2040::s_resets.reset_done.spi_1) {}

	gpio::setupPin(std::move(clk), pindir::in, pinfunc::SPI);
	gpio::setupPin(std::move(csn), pindir::out, pinfunc::SPI);
	gpio::setupPin(std::move(rx), pindir::in, pinfunc::SPI);
	gpio::setupPin(std::move(tx), pindir::in, pinfunc::SPI);

	setBaudrate(std::move(baudrate));
	setFormat(8, clk_phase::phase_1, clock_polarity::polarity_0, bit_order::msb);

	//bsp::rp2040::s_spi_1.cr0.frf = 0x2; // 0x00 is motorola spi

	// Enable DMA
	bsp::rp2040::s_spi_1.dmacr.rxdmae = 1;
	bsp::rp2040::s_spi_1.dmacr.txdmae = 1;

	// Enable SPI
	bsp::rp2040::s_spi_1.cr1.sse = 1;
}

std::uint32_t hal::spi::setBaudrate(const uint32_t baudrate)
{
	auto freq = hal::clock::getHz();

	uint32_t prescale, postdiv;
	for (prescale = 2; prescale <= 254; prescale += 2) {
		if (freq < ((prescale + 2) * 256 * (uint64_t)baudrate))
			break;
	}

	for (postdiv = 256; postdiv > 1; --postdiv) {
		if (freq / ((prescale * (postdiv - 1)) > baudrate))
			break;
	}

	// Setup SPI with baudrate
	uint32_t enableMask = bsp::rp2040::s_spi_1.cr1.sse;
	bsp::rp2040::s_spi_1.cr1.sse = 0;

	// TODO: This calculation is wrong
	//bsp::rp2040::s_spi_1.cpsr.cpsdvsr = prescale;
	bsp::rp2040::s_spi_1.cpsr.cpsdvsr = 4;
	//bsp::rp2040::s_spi_1.cr0.scr = postdiv - 1;
	bsp::rp2040::s_spi_1.cr0.scr = 1;

	bsp::rp2040::s_spi_1.cr1.sse = enableMask;

	return freq / (prescale * postdiv);
}

void hal::spi::setFormat(const uint32_t dataBits, const hal::clk_phase&& phase, const hal::clock_polarity&& polarity, const hal::bit_order&& bitOrder)
{
	uint32_t enableMask = bsp::rp2040::s_spi_1.cr1.sse;
	bsp::rp2040::s_spi_1.cr1.sse = 0;

	bsp::rp2040::s_spi_1.cr0.dss = dataBits - 1;
	bsp::rp2040::s_spi_1.cr0.spo = static_cast<std::uint16_t>(polarity);
	bsp::rp2040::s_spi_1.cr0.sph = static_cast<std::uint16_t>(phase);

	bsp::rp2040::s_spi_1.cr1.sse = enableMask;
}

template<typename T, std::uint32_t sizeIn, std::uint32_t sizeOut>
void hal::spi::writeAndRead(const etl::array<T, sizeIn>& dataOut, etl::array<T, sizeOut>& dataIn)
{
	static std::uint32_t null;

	std::uint32_t dma_rx = hal::dma::requestChannel();
	std::uint32_t dma_tx = hal::dma::requestChannel();

	hal::dma::setDefault(dma_rx);
	hal::dma::setDefault(dma_tx);

	// Setup TX
	hal::dma::setDataSize(dma_tx, dmaChannelSize::SIZE_8);
	hal::dma::setDreq(dma_tx, 18);
	hal::dma::setReadIncrement(dma_tx, true);
	hal::dma::setWriteIncrement(dma_tx, false);

	hal::dma::setTransCount(dma_tx, dataOut.size());
	hal::dma::setReadAddr(dma_tx, &dataOut.at(0));
	hal::dma::setWriteAddr(dma_tx, &bsp::rp2040::s_spi_1.dr.data);

	// Setup RX
	hal::dma::setDataSize(dma_rx, dmaChannelSize::SIZE_8);
	hal::dma::setDreq(dma_rx, 19);
	hal::dma::setReadIncrement(dma_rx, false);
	hal::dma::setWriteIncrement(dma_rx, true);

	hal::dma::setTransCount(dma_rx, dataIn.size());
	hal::dma::setReadAddr(dma_rx, &bsp::rp2040::s_spi_1.dr.data);
	hal::dma::setWriteAddr(dma_rx, &dataIn.at(0));

	hal::dma::enable(dma_rx);
	hal::dma::enable(dma_tx);

	hal::dma::start(dma_rx);
	hal::dma::start(dma_tx);

	/*
	//sleep(10);

	hal::dma::disable(dma_rx);
	hal::dma::disable(dma_tx);

	hal::dma::freeChannel(dma_rx);
	hal::dma::freeChannel(dma_tx);
	*/
}

// TODO: this is not optimal
template void hal::spi::writeAndRead<std::uint8_t, 6, 6>(const etl::array<std::uint8_t, 6>& dataOut, etl::array<std::uint8_t, 6>& dataIn);