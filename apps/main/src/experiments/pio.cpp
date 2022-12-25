#include "experiments/pio.hpp"

using namespace hal;
using namespace hal::pins;
using namespace bsp::rp2040;

void setup_pio()
{
    // Reset state machines
    //s_pio_0.control.sm_restart = 0x1;
    //s_pio_0.control.clkdiv_restart = 0x1;

    //s_pio_0.fdebug.rxstall = 0x0;
    //s_pio_0.fdebug.rxunder = 0x0;
    //s_pio_0.fdebug.txover = 0x0;
    //s_pio_0.fdebug.txstall = 0x0;

    // Load blink PIO program
    s_pio_0.instr_mem[0] = 0xe081;
    s_pio_0.instr_mem[1] = 0xfe01;
    s_pio_0.instr_mem[2] = 0xfd00;
    s_pio_0.instr_mem[3] = 0x0001;
}

void setup_sm0()
{
    s_pio_0.sm[0].clkdiv.integer = 0xFFFF;
    s_pio_0.sm[0].pinctrl.set_count = 1;
    s_pio_0.sm[0].pinctrl.set_base = 14;
}

void pioMain()
{
    // Setup LedPin2 and WS28Pin as pio out pins.
    gpio::setupPin(std::move(LedPin), pindir::out, pinfunc::PIO0);

    setup_pio();
    setup_sm0();

    // Enable PIO 0
    bsp::rp2040::s_pio_0.control.sm_enable = 15; // Enable all cores!!!!

    while (true)
    {
        system::delay(1);
    }
}