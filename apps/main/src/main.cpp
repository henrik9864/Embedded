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

const uint32_t freq = freq_1mhz;

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
    s_xsoc.control.freq_range = 0xaab;
    s_xsoc.startup.x4 = 0x1;
    s_xsoc.startup.delay = 0x00c4;

    // Enable XOSC clock
    s_xsoc.control.enable = 0xfab; // Enable
    //s_xsoc.control.enable = 0xd1e; // Disable

    while (!s_xsoc.status.stable || !s_xsoc.status.enabled) {}

    s_clocks.sys.control.src = 0x0;
    s_clocks.sys.control.src = 0x0;

    while (!s_clocks.sys.selected) {}
    while (!s_clocks.ref.selected) {}

    /*
    //Turn on PLL for 48mhz
    s_pll_usb.control.refdiv = 0x1;
    s_pll_usb.fbdiv.div = 64;

    s_pll_usb.pwr.pd = 0x0;
    s_pll_usb.pwr.vcopd = 0x0;

    while (s_pll_usb.control.lock) {}

    s_pll_usb.prim.postdiv1 = 4;
    s_pll_usb.prim.postdiv2 = 4;

    s_pll_usb.pwr.postdivpd = 0x0;
    //s_pll_sys.pwr.dsmpd = 0x0;
    */

    // Set clock source
    s_clocks.sys.control.auxsrc = 0x0; // PLL
    //s_clocks.sys.control.auxsrc = 0x3; // XSOC

    while (!s_clocks.sys.selected) {}

    s_clocks.sys.control.src = 0x1;
    //s_clocks.ref.control.src = 0x2;

    while (!s_clocks.sys.selected) {}

    s_clocks.sys.div.integer = 0x1;
    //s_clocks.ref.div.integer = 0x1;

    //delay(100000 * 10);

    //s_clocks.sys.control.auxsrc = 0x0;


    s_resets.reset.io_bank_0 = 0;
    s_resets.reset.pads_bank_0 = 0;

    while (!s_resets.reset_done.io_bank_0 || !s_resets.reset_done.pads_bank_0) {}

    s_io_bank_0.gpio[25].control.funcsel = 5;
    s_sio.gpio_oe_set = 1 << 25;
    s_sio.gpio_out_set = 1 << 25;

    uint32_t add = reinterpret_cast<uint32_t>(&s_xsoc.dormant);
    if (add == 0x40024000 + 0x09)
    {
        blink();
        delay(freq / 4);

        blink();
        delay(freq / 4);

        blink();
        delay(freq / 4);

        blink();
        delay(freq / 4);
    }
    /*
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
        s_sio.gpio_out_set = 1 << 25;
        delay(freq);

        s_sio.gpio_out_clr = 1 << 25;
        delay(freq);
    }
    return(0);
}