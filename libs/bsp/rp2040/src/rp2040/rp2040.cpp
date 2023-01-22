#include "rp2040.hpp"

using namespace bsp::rp2040;
using namespace hal;

void system::init()
{
    s_resets.reset.pio_0 = 1;
    s_resets.reset.io_bank_0 = 1;
    s_resets.reset.pwm = 1;
    s_resets.reset.i2c0 = 1;
    s_resets.reset.i2c1 = 1;
    s_resets.reset.uart_0 = 1;
    s_resets.reset.uart_1 = 1;
    s_resets.reset.pads_bank_0 = 1;

    s_resets.reset.pio_0 = 0;
    s_resets.reset.io_bank_0 = 0;
    s_resets.reset.pwm = 0;
    s_resets.reset.i2c0 = 0;
    s_resets.reset.i2c1 = 0;
    s_resets.reset.uart_0 = 0;
    s_resets.reset.uart_1 = 0;
    s_resets.reset.pads_bank_0 = 0;

    while (!s_resets.reset_done.pio_0 &&
        !s_resets.reset_done.io_bank_0 &&
        !s_resets.reset_done.pwm &&
        !s_resets.reset_done.i2c0 &&
        !s_resets.reset_done.i2c1 &&
        !s_resets.reset_done.uart_0 &&
        !s_resets.reset_done.uart_1 &&
        !s_resets.reset_done.pads_bank_0) {
    }
}

// TODO: Mabye move into hal class?
void system::put(const uint32_t a1, const uint32_t a2)
{
    *reinterpret_cast<uint32_t*>(a1) = a2;
}

uint32_t system::get(const uint32_t a1)
{
    return *reinterpret_cast<uint32_t*>(a1);
}

volatile void system::delay(uint32_t a1)
{
    __asm volatile (
    ".syntax unified\n"
        "1: subs %0, #3\n"
        "bcs 1b\n"
        : "+r" (a1) : : "memory"
        );
}