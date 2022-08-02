#include <cstdint>
#include <cstddef>

#include "rp2040.h"

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

const uint32_t freq_125mhz = 125 * 1000000;
const uint32_t freq_100mhz = 100 * 1000000;
const uint32_t freq_12mhz = 12 * 1000000;
const uint32_t freq_10mhz = 10 * 1000000;
const uint32_t freq_6mhz = 6.5 * 1000000;
const uint32_t freq_1mhz = 1 * 1000000;
const uint32_t freq_100khz = 100000;
const uint32_t freq_noe = 0x10000000;

const uint32_t freq = freq_100khz;

void blink()
{
    s_sio.gpio_out_set = 1 << 25;
    delay(freq);

    s_sio.gpio_out_clr = 1 << 25;
}

void blinkFase()
{
    s_sio.gpio_out_set = 1 << 25;
    delay(10);

    s_sio.gpio_out_clr = 1 << 25;
}


int main(void)
{
    s_xsoc.startup.delay = 47;

    // Enable XOSC clock
    s_xsoc.control.enable = 0xfab;

    while (!s_xsoc.status.stable) {}

    /*
    delay(freq_100khz / 10);
    blinkFase();
    //s_clocks.sys.div.integer = 0xaa0 + 0x1;

    //s_rsoc.control.freq_range = 0xaa0;
    //s_rsoc.div.div = 0xaa0 + 1;

    s_pll_sys.control.refdiv = 0x1;
    s_pll_sys.fbdiv.div = 120;

    s_pll_sys.pwr.pd = 1;
    s_pll_sys.pwr.vcopd = 1;

    blinkFase();

    //while(!s_pll_sys.control.lock) { delay(1); };

    delay(freq_100khz / 10);
    blinkFase();

    s_pll_sys.prim.postdiv1 = 6;
    s_pll_sys.prim.postdiv2 = 5;

    s_pll_sys.pwr.postdivpd = 1;

    delay(freq_100khz / 10);

    */

    s_pll_sys.prim.postdiv1 = 6;
    s_pll_sys.prim.postdiv2 = 5;
    s_pll_sys.fbdiv.div = 120;

    //s_pll_sys.control.refdiv = 0x1;

    // Set clock source
    s_clocks.sys.control.src = 0x0;
    s_clocks.sys.control.auxsrc = 0x0;

    while (!s_clocks.sys.selected) {}

    s_clocks.sys.control.src = 0x1;
    s_clocks.sys.div.integer = 0x1;

    //uint32_t add = reinterpret_cast<uint32_t>(&s_rsoc.div);

    s_resets.reset.io_bank_0 = 0;
    s_resets.reset.pads_bank_0 = 0;

    while (!s_resets.reset_done.io_bank_0 || !s_resets.reset_done.pads_bank_0) {}

    s_io_bank_0.gpio[25].control.funcsel = 5;
    s_sio.gpio_oe_set = 1 << 25;
    s_sio.gpio_out_set = 1 << 25;

    /*
    if (add == 0x40060000 + 0x10 && false)
    {
        blink();
        delay(freq / 2);

        blink();
        delay(freq / 2);

        blink();
        delay(freq / 2);

        blink();
        delay(freq / 2);
    }
    */

    /*
    for (size_t i = 0; i < 10; i++)
    {
        blink();

        if (i == s_clocks.sys.control.auxsrc)
        {
            delay(0x100 / 3);
            blink();
        }

        delay(0x100 * 10);
    }
    */
    while (true)
    {
        s_sio.gpio_out_clr = 1 << 25;
        delay(freq);

        s_sio.gpio_out_set = 1 << 25;
        delay(freq);
    }
    return(0);
}