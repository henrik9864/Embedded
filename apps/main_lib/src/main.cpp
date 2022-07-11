#include <cstdint>
#include <cstddef>

#include "rp2040.h"
#include "new/rp2040_regs.hpp"

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
    //if (sio.cpuid.Read() == Pico::Sio::Core::Core1)
    //    return 0;

    s_resets.reset.bits.io_bank_0 = 0;
    //resets.reset.io_bank_0 = 0;
    s_resets.reset.bits.pads_bank_0 = 0;
    //resets.reset.pads_bank_0 = 0;

    while (!s_resets.reset_done.bits.io_bank_0 ||!s_resets.reset_done.bits.pads_bank_0) {}
    //while (!resets.reset_done.io_bank_0 ||!resets.reset_done.pads_bank_0) {}

    iobank0.gpio[24].control.funcsel = 5;
    iobank0.gpio[25].control.funcsel = 5;
    iobank0.gpio[26].control.funcsel = 5;
    //s_io_bank_0.gpio[25].control.funcsel = 5;
    //sio.gpio_oe_set.SetBit(25, 1);
    //sio.gpio_out_set.SetBit(25, 1);
    //s_sio.gpio_oe_set = 1 << 25;
    //s_sio.gpio_out_set = 1 << 25;

    while(true)
    {
        volatile auto d = 0x100000;

        sio.gpio_out_set.SetBit(25, 1);
        //s_sio.gpio_out_set = 1 << 25;
        delay(d);

        sio.gpio_out_clr.SetBit(25, 1);
        //s_sio.gpio_out_clr = 1 << 25;
        delay(d);
    }
    return(0);
}