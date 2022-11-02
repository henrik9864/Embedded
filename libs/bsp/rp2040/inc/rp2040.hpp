#pragma once

#include "rp2040_pins.hpp"

using namespace bsp::rp2040;
using namespace hal;

void system::init()
{
    s_resets.reset.pio_0 = 1;
    s_resets.reset.pads_bank_0 = 1;
    s_resets.reset.io_bank_0 = 1;
    s_resets.reset.pwm = 1;
    s_resets.reset.pads_bank_0 = 1;

    s_resets.reset.pio_0 = 0;
    s_resets.reset.pads_bank_0 = 0;
    s_resets.reset.io_bank_0 = 0;
    s_resets.reset.pwm = 0;
    s_resets.reset.pads_bank_0 = 0;

    while ( !s_resets.reset_done.pio_0 &&
            !s_resets.reset_done.pads_bank_0 &&
            !s_resets.reset_done.io_bank_0 && 
            !s_resets.reset_done.pwm && 
            !s_resets.reset_done.pads_bank_0) {}
}