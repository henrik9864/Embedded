#include <cstdint>
#include <cstddef>

#include "rp2040.hpp"

void put(const uint32_t a1, const uint32_t a2)
{
    *reinterpret_cast<uint32_t*>(a1) = a2;
}

uint32_t get(const uint32_t a1)
{
    return *reinterpret_cast<uint32_t*>(a1);
}

volatile void delay(const uint32_t a1)
{
    for (size_t i = 0; i < a1; i++)
    {
        __asm("NOP");
    }
}

int main ( void )
{
    s_resets.reset.bits.io_bank_0 = 0;
    s_resets.reset.bits.pads_bank_0 = 0;

    while (!s_resets.reset_done.bits.io_bank_0 ||!s_resets.reset_done.bits.pads_bank_0) {}

    s_io_bank_0.gpio[25].control.bits.funcsel = 5;
    s_sio.gpio_oe_set = 1 << 25;
    s_sio.gpio_out_set = 1 << 25;

    while(true)
    {
        volatile auto d = 0x100000;

        s_sio.gpio_out_set = 1 << 25;
        delay(d);

        s_sio.gpio_out_clr = 1 << 25;
        delay(d);
    }
    return(0);
}