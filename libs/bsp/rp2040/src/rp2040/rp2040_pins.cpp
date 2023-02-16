#include "rp2040_pins.hpp"

using namespace bsp::rp2040;
using namespace hal::pins;

void gpio::setupPin(const pin_id&& pin, const pindir&& dir, const pinfunc&& func)
{
	s_io_bank_0.gpio[pin].control.funcsel = static_cast<uint32_t>(func);

	if (func != pinfunc::SIO)
		return;

	if (dir == pindir::out)
	{
		s_sio.gpio_oe_set = 1 << pin; // Set output enable for pin
	}
	else if (dir == pindir::in)
	{
		s_sio.gpio_oe_clr = 1 << pin; // Clear output enable for pin
	}
}

bool gpio::readPin(const pin_id&& pin)
{
	return s_sio.gpio_in & 1 << pin;
}

void gpio::writePin(const pin_id&& pin, bool value)
{
	if (value)
	{
		s_sio.gpio_out_set = 1 << pin;
	}
	else
	{
		s_sio.gpio_out_clr = 1 << pin;
	}
}

void gpio::togglePin(const pin_id&& pin)
{
	s_sio.gpio_out_xor = 1 << pin;
}

void gpio::setPullUp(const pin_id&& pin)
{
	s_pads_bank_0.gpio[pin].pde = 0x1;
}

void gpio::setPullDown(const pin_id&& pin)
{
	s_pads_bank_0.gpio[pin].pue = 0x1;
}