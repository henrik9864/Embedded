#include "rp2040_spi.hpp"

using namespace hal::pins;

void hal::spi::init(const pins::pin_id&& clk, const pins::pin_id&& rx, const pins::pin_id&& tx, const uint32_t&& baudrate)
{
	gpio::setupPin(std::move(tx), pindir::in, pinfunc::SPI);
	gpio::setupPin(std::move(rx), pindir::in, pinfunc::SPI);
	gpio::setupPin(std::move(rx), pindir::in, pinfunc::SPI);

	// Reset SPI and wait
	bsp::rp2040::s_resets.reset.spi_0 = 1;
	bsp::rp2040::s_resets.reset.spi_0 = 0;
	while (!bsp::rp2040::s_resets.reset_done.spi_0) {}

	auto freq = clock::getHz();
	uint32_t prescale, postdiv;
	for (prescale = 2; prescale <= 254; prescale += 2) {
		if (freq < (prescale + 2) * 256 * (uint64_t)baudrate)
			break;
	}

	for (postdiv = 256; postdiv > 1; --postdiv) {
		if (freq / (prescale * (postdiv - 1)) > baudrate)
			break;
	}

	uint32_t enableMask = bsp::rp2040::s_spi_0.cr1.sse;
	bsp::rp2040::s_spi_0.cr1.sse = 0;

	bsp::rp2040::s_spi_0.cpsr.cpsdvsr = prescale;
	bsp::rp2040::s_spi_0.cr0.scr = postdiv - 1;

	bsp::rp2040::s_spi_0.cr1.sse = enableMask;

	bsp::rp2040::s_spi_0.dmacr.rxdmae = 1;
	bsp::rp2040::s_spi_0.dmacr.txdmae = 1;

	bsp::rp2040::s_spi_0.cr1.sse = 1;
}