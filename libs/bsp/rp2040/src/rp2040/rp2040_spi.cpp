#include "rp2040_spi.hpp"

using namespace hal::pins;

void hal::spi::init(const pins::pin_id&& clk, const pins::pin_id&& csn, const pins::pin_id&& rx, const pins::pin_id&& tx, const uint32_t baudrate)
{
	gpio::setupPin(std::move(tx), pindir::in, pinfunc::SPI);
	gpio::setupPin(std::move(rx), pindir::in, pinfunc::SPI);
	gpio::setupPin(std::move(clk), pindir::in, pinfunc::SPI);
	gpio::setupPin(std::move(csn), pindir::in, pinfunc::SPI);

	// Reset SPI and wait
	bsp::rp2040::s_resets.reset.spi_0 = 1;
	bsp::rp2040::s_resets.reset.spi_0 = 0;
	while (!bsp::rp2040::s_resets.reset_done.spi_0) {}

	setBaudrate(std::move(baudrate));
	setFormat(8, clk_phase::phase_0, clock_polarity::polarity_0, bit_order::msb);

	// Enable DMA
	bsp::rp2040::s_spi_0.dmacr.rxdmae = 1;
	bsp::rp2040::s_spi_0.dmacr.txdmae = 1;

	bsp::rp2040::s_spi_0.cr1.sse = 1;
}

std::uint32_t hal::spi::setBaudrate(const uint32_t baudrate)
{
	auto freq = hal::clock::getHz();

	uint32_t prescale, postdiv;
	for (prescale = 2; prescale <= 254; prescale += 2) {
		if (freq < (prescale + 2) * 256 * (uint64_t)baudrate)
			break;
	}

	for (postdiv = 256; postdiv > 1; --postdiv) {
		if (freq / (prescale * (postdiv - 1)) > baudrate)
			break;
	}

	// Setup SPI with baudrate
	uint32_t enableMask = bsp::rp2040::s_spi_0.cr1.sse;
	bsp::rp2040::s_spi_0.cr1.sse = 0;

	bsp::rp2040::s_spi_0.cpsr.cpsdvsr = prescale;
	bsp::rp2040::s_spi_0.cr0.scr = postdiv - 1;

	bsp::rp2040::s_spi_0.cr1.sse = enableMask;

	return freq / (prescale * postdiv);
}

void hal::spi::setFormat(const uint32_t dataBits, const hal::clk_phase&& phase, const hal::clock_polarity&& polarity, const hal::bit_order&& bitOrder)
{
	uint32_t enableMask = bsp::rp2040::s_spi_0.cr1.sse;
	bsp::rp2040::s_spi_0.cr1.sse = 0;

	bsp::rp2040::s_spi_0.cr0.dss = dataBits - 1;
	bsp::rp2040::s_spi_0.cr0.spo = static_cast<std::uint16_t>(polarity);
	bsp::rp2040::s_spi_0.cr0.sph = static_cast<std::uint16_t>(phase);

	bsp::rp2040::s_spi_0.cr1.sse = enableMask;
}