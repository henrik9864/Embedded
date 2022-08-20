#include <cstdint>
#include <cstddef>
#include <array>

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

void inline __attribute__((always_inline)) delay2(uint32_t ticks)
{
    ticks /= 4;
    while(ticks--) __asm("");
}

static inline void delay3(uint32_t cycles) {
    __asm volatile (
    ".syntax unified\n"
        "1: subs %0, #3\n"
        "bcs 1b\n"
        : "+r" (cycles) : : "memory"
        );
}

const uint32_t freq_133mhz = 133 * 1000000;
const uint32_t freq_125mhz = 125 * 1000000;
const uint32_t freq_100mhz = 100 * 1000000;
const uint32_t freq_48mhz = 48 * 1000000;
const uint32_t freq_12mhz = 12 * 1000000;
const uint32_t freq_10mhz = 10 * 1000000;
const uint32_t freq_6mhz = 6.5 * 1000000;
const uint32_t freq_1_15mhz = 1.15 * 1000000;
const uint32_t freq_1mhz = 1 * 1000000;
const uint32_t freq_100khz = 100000;
const uint32_t freq_noe = 0x10000000;

const uint32_t freq = freq_48mhz;

void sleep(const uint32_t ns)
{
    delay3((ns / 1000000000) * freq);
    //delay3(ns * 0.048f);
}

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

void init_xsoc()
{
    s_xsoc.control.freq_range = 0xaab;
    s_xsoc.startup.delay = 47;

    // Enable XOSC clock
    s_xsoc.control.enable = 0xfab;

    while (!s_xsoc.status.stable  || !s_xsoc.status.enabled) {}
}

void init_pll_sys(const uint32_t div, const uint32_t fbdiv, const uint32_t postdiv1, const uint32_t postdiv2)
{
    // Reset PLL and wait
    s_resets.reset.pll_sys = 1;
    s_resets.reset.pll_sys = 0;
    while (!s_resets.reset_done.pll_sys) {}

    s_pll_sys.control.refdiv = div; // Set PLL divide
    s_pll_sys.fbdiv.div = fbdiv;
    s_pll_sys.prim.postdiv1 = postdiv1;
    s_pll_sys.prim.postdiv2 = postdiv2;

    // Turn on PLL
    s_pll_sys.pwr.vcopd = 0x0;
    s_pll_sys.pwr.pd = 0x0;
    while (!s_pll_sys.control.lock) {}
    s_pll_sys.pwr.postdivpd = 0x0;
}

void init_pll_usb(const uint32_t div, const uint32_t fbdiv, const uint32_t postdiv1, const uint32_t postdiv2)
{
    // Reset PLL and wait
    s_resets.reset.pll_usb = 1;
    s_resets.reset.pll_usb = 0;
    while (!s_resets.reset_done.pll_usb) {}

    s_pll_usb.control.refdiv = div; // Set PLL divide
    s_pll_usb.fbdiv.div = fbdiv;
    s_pll_usb.prim.postdiv1 = postdiv1;
    s_pll_usb.prim.postdiv2 = postdiv2;

    // Turn on PLL
    s_pll_usb.pwr.vcopd = 0x0;
    s_pll_usb.pwr.pd = 0x0;
    while (!s_pll_usb.control.lock) {}
    s_pll_usb.pwr.postdivpd = 0x0;
}

void init_gpio()
{
    s_resets.reset.io_bank_0 = 1;
    s_resets.reset.pads_bank_0 = 1;

    s_resets.reset.io_bank_0 = 0;
    s_resets.reset.pads_bank_0 = 0;
    while (!s_resets.reset_done.io_bank_0 || !s_resets.reset_done.pads_bank_0) {}
}

void init_uart(uint32_t baud)
{
    s_resets.reset.uart_0 = 1;

    s_resets.reset.uart_0 = 0;
    while (!s_resets.reset_done.uart_0) {}

    baud = (freq_133mhz * 4) / baud;
}

void setup_clocks()
{
    // Disable resus that my have been enabled.
    s_clocks.sys_resus.control.enable = 0x0;

    s_clocks.ref.control.src = 0x2; // Set ref clk src to xsoc

    s_clocks.sys.control.src = 0x1; // Set sys src to pll_sys
    s_clocks.sys.control.auxsrc = 0x0; // Set sys auxsrc to pll_sys

    s_clocks.peripheral.control.enable = 0x1; // Enable peri clock
    s_clocks.peripheral.control.auxsrc = 0x0; // Set auxsrc to clk_sys

    s_clocks.usb.control.enable = 0x1; // Enable usb clock
    s_clocks.usb.control.auxsrc = 0x0; // Set auxsrc to pll_usb

    s_clocks.adc.control.enable = 0x1; // Enable usb clock
    s_clocks.adc.control.auxsrc = 0x0; // Set auxsrc to pll_usb

    s_clocks.rtc.div.integer = 256; // 12MHz / 256 = 46875 Hz
    s_clocks.rtc.control.enable = 0x1; // Enable rtc clock
    s_clocks.rtc.control.auxsrc = 0x3; // Set rtc clk src to xsoc
}

int main(void)
{
    init_xsoc();

    // Setup SYS PLL for 12 MHz * 133 / 6 / 2 = 133 MHz
    //init_pll_sys(1, 133, 6, 2);
    
    // Setup SYS PLL for 12 MHz * 120 / 6 / 5 = 48 MHz
    init_pll_sys(1, 120, 6, 5);

    // Setup SYS PLL for 12 MHz * 120 / 6 / 5 = 48 MHz
    init_pll_usb(1, 120, 6, 5);

    setup_clocks();

    init_gpio();

    const uint32_t LedPin = 8;
    const uint32_t LedPin2 = 14;
    const uint32_t WS28Pin = 16;

    // Set pin 16(WS2812B LED) as out
    s_io_bank_0.gpio[LedPin].control.funcsel = 5; // Set func mode to SIO
    s_sio.gpio_oe_set = 1 << LedPin;

    s_io_bank_0.gpio[LedPin2].control.funcsel = 5; // Set func mode to SIO
    s_sio.gpio_oe_set = 1 << LedPin2;

    // Set pin 25(LED) as out
    s_io_bank_0.gpio[25].control.funcsel = 5; // Set func mode to SIO
    s_sio.gpio_oe_set = 1 << 25;
    s_sio.gpio_out_set = 1 << 25;

    const std::array<uint32_t, 24> arr = { 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0 };
    //const std::array<uint32_t, 24> arr = { 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0 };

    // Blink
    while (true)
    {
        // WS2812B
        for (const auto bit : arr)
        {
            if (bit == 1)
            {
                //s_sio.gpio_out_set = 1 << LedPin;
                //sleep(800 * 100000000);
                //delay3(38);

                //s_sio.gpio_out_clr = 1 << LedPin;
                //sleep(450 * 100000000);
                //delay3(21);

                s_sio.gpio_out_set = 1 << LedPin;
                sleep(100 * 100000000);
            }
            else
            {
                //s_sio.gpio_out_set = 1 << LedPin;
                //sleep(400 * 100000000);
                //delay3(19);

                //s_sio.gpio_out_clr = 1 << LedPin;
                //sleep(450 * 100000000);
                //delay3(40);

                s_sio.gpio_out_set = 1 << LedPin2;
                sleep(100 * 100000000);
            }

            s_sio.gpio_out_clr = 1 << LedPin;
            s_sio.gpio_out_clr = 1 << LedPin2;

            sleep(100 * 100000000);
        }

        s_sio.gpio_out_clr = 1 << LedPin;
        s_sio.gpio_out_clr = 1 << LedPin2;
        sleep(2000 * 100000000);

        //s_sio.gpio_out_set = 1 << LedPin;
        //delay3(freq * 5);

        //s_sio.gpio_out_clr = 1 << LedPin;
        //delay3(freq * 5);
    }
    return(0);
}

/*
int main(void)
{
    s_resets.reset.pll_sys = 0;
    s_resets.reset.io_bank_0 = 0;
    s_resets.reset.pads_bank_0 = 0;

    while (!s_resets.reset_done.io_bank_0 || !s_resets.reset_done.pads_bank_0 || !s_resets.reset_done.pll_sys) {}

    s_clocks.sys_resus.control.enable = 0x0;

    const bool enable_xsoc = true;

    if constexpr(enable_xsoc)
    {
        s_xsoc.control.freq_range = 0xaab;
        //s_xsoc.startup.x4 = 47;
        s_xsoc.startup.delay = 47;

        // Enable XOSC clock
        s_xsoc.control.enable = 0xfab; // Enable

        while (!s_xsoc.status.stable  || !s_xsoc.status.enabled) {}
    }
    else
    {
        s_xsoc.control.enable = 0xd1e; // Disable
    }

    s_clocks.ref.control.src = 0x2;
    s_clocks.sys.control.src = 0x0;

    s_resets.reset.pll_sys = 0;
    while (!s_resets.reset_done.pll_sys) {}

    s_pll_sys.control.refdiv = 0x1;
    s_pll_sys.fbdiv.div = 40;
    s_pll_sys.prim.postdiv1 = 4;
    s_pll_sys.prim.postdiv2 = 1;

    s_pll_sys.pwr.vcopd = 0x1;
    s_pll_sys.pwr.pd = 0x1;
    while (!s_pll_sys.control.lock) {}
    s_pll_sys.pwr.postdivpd = 0x1;

    s_clocks.sys.control.auxsrc = 0x0;
    s_clocks.sys.control.src = 0x0;

    s_clocks.sys.control.src = 0x0;
    s_clocks.sys.control.src = 0x0;

    while (!s_clocks.sys.selected) {}
    while (!s_clocks.ref.selected) {}

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

    // Set clock source
    s_clocks.sys.control.auxsrc = 0x0; // PLL
    //s_clocks.sys.control.auxsrc = 0x3; // XSOC

    while (!s_clocks.sys.selected) {}

    //s_clocks.sys.control.src = 0x0;
    s_clocks.sys.control.src = 0x1;
    //s_clocks.ref.control.src = 0x2;

    while (!s_clocks.sys.selected) {}

    s_clocks.sys.div.integer = 0x1;
    //s_clocks.ref.div.integer = 0x1;

    //delay(100000 * 10);

    //s_clocks.sys.control.auxsrc = 0x0;

    // Enable XSOC as GPIO0
    s_clocks.gpio[0].control.auxsrc = 0x5;
    s_clocks.gpio[0].control.enable = 0x1;
    //s_clocks.gpio[0].div.integer = 0x10000;

    s_io_bank_0.gpio[21].control.funcsel = 8; // Set Pin 21 as clock out

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
    while (true)
    {
        s_sio.gpio_out_set = 1 << 25;
        delay2(freq);

        s_sio.gpio_out_clr = 1 << 25;
        delay2(freq);
    }
    return(0);
}
*/