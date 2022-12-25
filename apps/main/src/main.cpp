#include <cstdint>
#include <cstddef>
#include <array>

#include "hal.hpp"
//#include "ln298n.hpp"
#include "rp2040.hpp"

using namespace hal;
using namespace hal::pins;
//using namespace drivers;

const uint32_t freq_200mhz = 200 * 1000000;
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

const uint32_t freq = freq_48mhz;

void sleep(const uint32_t ns)
{
    hal::system::delay((ns / 1000000000) * freq);
}

void init_xsoc()
{
    bsp::rp2040::s_xsoc.control.freq_range = 0xaab;
    bsp::rp2040::s_xsoc.startup.delay = 47;

    // Enable XOSC clock
    bsp::rp2040::s_xsoc.control.enable = 0xfab;

    while (!bsp::rp2040::s_xsoc.status.stable  || !bsp::rp2040::s_xsoc.status.enabled) {}
}

void init_pll_sys(const uint32_t div, const uint32_t fbdiv, const uint32_t postdiv1, const uint32_t postdiv2)
{
    // Reset PLL and wait
    bsp::rp2040::s_resets.reset.pll_sys = 1;
    bsp::rp2040::s_resets.reset.pll_sys = 0;
    while (!bsp::rp2040::s_resets.reset_done.pll_sys) {}

    bsp::rp2040::s_pll_sys.control.refdiv = div; // Set PLL divide
    bsp::rp2040::s_pll_sys.fbdiv.div = fbdiv;
    bsp::rp2040::s_pll_sys.prim.postdiv1 = postdiv1;
    bsp::rp2040::s_pll_sys.prim.postdiv2 = postdiv2;

    // Turn on PLL
    bsp::rp2040::s_pll_sys.pwr.vcopd = 0x0;
    bsp::rp2040::s_pll_sys.pwr.pd = 0x0;
    while (!bsp::rp2040::s_pll_sys.control.lock) {}
    bsp::rp2040::s_pll_sys.pwr.postdivpd = 0x0;
}

void init_pll_usb(const uint32_t div, const uint32_t fbdiv, const uint32_t postdiv1, const uint32_t postdiv2)
{
    // Reset PLL and wait
    bsp::rp2040::s_resets.reset.pll_usb = 1;
    bsp::rp2040::s_resets.reset.pll_usb = 0;
    while (!bsp::rp2040::s_resets.reset_done.pll_usb) {}

    bsp::rp2040::s_pll_usb.control.refdiv = div; // Set PLL divide
    bsp::rp2040::s_pll_usb.fbdiv.div = fbdiv;
    bsp::rp2040::s_pll_usb.prim.postdiv1 = postdiv1;
    bsp::rp2040::s_pll_usb.prim.postdiv2 = postdiv2;

    // Turn on PLL
    bsp::rp2040::s_pll_usb.pwr.vcopd = 0x0;
    bsp::rp2040::s_pll_usb.pwr.pd = 0x0;
    while (!bsp::rp2040::s_pll_usb.control.lock) {}
    bsp::rp2040::s_pll_usb.pwr.postdivpd = 0x0;
}

void setup_clocks()
{
    // Disable resus that my have been enabled.
    bsp::rp2040::s_clocks.sys_resus.control.enable = 0x0;

    bsp::rp2040::s_clocks.ref.control.src = 0x2; // Set ref clk src to xsoc

    bsp::rp2040::s_clocks.sys.control.src = 0x1; // Set sys src to pll_sys
    bsp::rp2040::s_clocks.sys.control.auxsrc = 0x0; // Set sys auxsrc to pll_sys
    bsp::rp2040::s_clocks.sys.div.integer = 0x1; // Reset div

    bsp::rp2040::s_clocks.peripheral.control.enable = 0x1; // Enable peri clock
    bsp::rp2040::s_clocks.peripheral.control.auxsrc = 0x0; // Set auxsrc to clk_sys

    bsp::rp2040::s_clocks.usb.control.enable = 0x1; // Enable usb clock
    bsp::rp2040::s_clocks.usb.control.auxsrc = 0x0; // Set auxsrc to pll_usb

    bsp::rp2040::s_clocks.adc.control.enable = 0x1; // Enable usb clock
    bsp::rp2040::s_clocks.adc.control.auxsrc = 0x0; // Set auxsrc to pll_usb

    bsp::rp2040::s_clocks.rtc.div.integer = 256; // 12MHz / 256 = 46875 Hz
    bsp::rp2040::s_clocks.rtc.control.enable = 0x1; // Enable rtc clock
    bsp::rp2040::s_clocks.rtc.control.auxsrc = 0x3; // Set rtc clk src to xsoc
}

int main(void)
{
    // Reset system to clean state
    system::init();

    init_xsoc();

    //pwmMain();

    // Setup SYS PLL for 12 MHz * 133 / 6 / 2 = 133 MHz
    //init_pll_sys(1, 133, 6, 2);
    //init_pll_sys(1, 100, 6, 1);
    
    // Setup SYS PLL for 12 MHz * 120 / 6 / 5 = 48 MHz
    init_pll_sys(1, 120, 6, 5);

    // Setup USB PLL for 12 MHz * 120 / 6 / 5 = 48 MHz
    init_pll_usb(1, 120, 6, 5);

    setup_clocks();

    // Registry check
    if (reinterpret_cast<uint32_t>(&bsp::rp2040::s_i2c_0.tar) != 0x40044000 + 0x04)
        return 0;

    // Blink 182
    while (true)
    {
        system::delay(1);
    }
    return 0;
}

/*
// 360ns at 133mhz
volatile void delay(const uint32_t a1)
{
    for (size_t i = 0; i < a1; i++)
    {
        __asm("NOP");
    }
}

// 235ns at 133mhz
void inline __attribute__((always_inline)) delay2(uint32_t ticks)
{
    //ticks /= 4;
    while(ticks--) __asm("");
}

// 225ns at 133mhz
static inline void delay3(uint32_t cycles) {
    __asm volatile (
    ".syntax unified\n"
        "1: subs %0, #3\n"
        "bcs 1b\n"
        : "+r" (cycles) : : "memory"
        );
}
*/