#include "rp2040_clock.hpp"

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

static uint32_t freq = freq_12mhz;

using namespace hal::pins;

void init_xsoc()
{
    bsp::rp2040::s_xsoc.control.freq_range = 0xaab;
    bsp::rp2040::s_xsoc.startup.delay = 47;

    // Enable XOSC clock
    bsp::rp2040::s_xsoc.control.enable = 0xfab;

    while (!bsp::rp2040::s_xsoc.status.stable || !bsp::rp2040::s_xsoc.status.enabled) {}
}

void setup_clocks()
{
    // Disable resus that my have been enabled.
    bsp::rp2040::s_clocks.sys_resus.control.enable = 0x0;

    bsp::rp2040::s_clocks.ref.control.src = 0x2; // Set ref clk src to xsoc

    //bsp::rp2040::s_clocks.sys.control.src = 0x1; // Set sys src to auxsrc
    bsp::rp2040::s_clocks.sys.control.src = 0x0; // Set sys src to ref
    bsp::rp2040::s_clocks.sys.control.auxsrc = 0x0; // Set sys auxsrc to pll_sys
    bsp::rp2040::s_clocks.sys.control.src = 0x1; // Set sys src to auxsrc
    bsp::rp2040::s_clocks.sys.div.integer = 0x1; // Reset div

    bsp::rp2040::s_clocks.peripheral.control.auxsrc = 0x0; // Set auxsrc to pll_sys
    bsp::rp2040::s_clocks.peripheral.control.enable = 0x1; // Enable peri clock
    //bsp::rp2040::s_clocks.peripheral.control.auxsrc = 0x4; // Set auxsrc to xosc

    bsp::rp2040::s_clocks.usb.control.enable = 0x1; // Enable usb clock
    bsp::rp2040::s_clocks.usb.control.auxsrc = 0x0; // Set auxsrc to pll_usb

    bsp::rp2040::s_clocks.adc.control.enable = 0x1; // Enable usb clock
    bsp::rp2040::s_clocks.adc.control.auxsrc = 0x0; // Set auxsrc to pll_usb

    bsp::rp2040::s_clocks.rtc.div.integer = 256; // 12MHz / 256 = 46875 Hz
    bsp::rp2040::s_clocks.rtc.control.enable = 0x1; // Enable rtc clock
    bsp::rp2040::s_clocks.rtc.control.auxsrc = 0x3; // Set rtc clk src to xsoc
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

void hal::clock::init()
{
    init_xsoc();

    // Setup SYS PLL for 12 MHz * 120 / 6 / 5 = 48 MHz
    //init_pll_sys(1, 120, 6, 5);
    //freq = freq_48mhz;

    // Setup SYS PLL for 12 MHz * 133 / 6 / 2 = 133 MHz
    init_pll_sys(1, 133, 6, 2);
    freq = freq_133mhz;

    setup_clocks();
}

void hal::clock::setupGpio(const pin_id&& pin, const hal::clksrc&& src)
{
    std::uint32_t gpclk;
    if (pin == 21) gpclk = 0;
    else if (pin == 23) gpclk = 1;
    else if (pin == 24) gpclk = 2;
    else if (pin == 25) gpclk = 3;

    switch (src)
    {
    case hal::clksrc::PLL_SYSTEM:
        bsp::rp2040::s_clocks.gpio[gpclk].control.auxsrc = 0x0;
        break;
    case hal::clksrc::GPIO0:
        bsp::rp2040::s_clocks.gpio[gpclk].control.auxsrc = 0x1;
        break;
    case hal::clksrc::GPIO1:
        bsp::rp2040::s_clocks.gpio[gpclk].control.auxsrc = 0x2;
        break;
    case hal::clksrc::PLL_USB:
        bsp::rp2040::s_clocks.gpio[gpclk].control.auxsrc = 0x3;
        break;
    case hal::clksrc::ROSC:
        bsp::rp2040::s_clocks.gpio[gpclk].control.auxsrc = 0x4;
        break;
    case hal::clksrc::XOSC:
        bsp::rp2040::s_clocks.gpio[gpclk].control.auxsrc = 0x5;
        break;
    case hal::clksrc::SYSTEM:
        bsp::rp2040::s_clocks.gpio[gpclk].control.auxsrc = 0x6;
        break;
    case hal::clksrc::USB:
        bsp::rp2040::s_clocks.gpio[gpclk].control.auxsrc = 0x6;
        break;
    default:
        break;
    }

    bsp::rp2040::s_clocks.gpio[gpclk].div.integer = 4;
}

void hal::clock::startGpio(const pin_id&& pin)
{
    std::uint32_t gpclk;
    if (pin == 21) gpclk = 0;
    else if (pin == 23) gpclk = 1;
    else if (pin == 24) gpclk = 2;
    else if (pin == 25) gpclk = 3;

    bsp::rp2040::s_clocks.gpio[gpclk].control.enable = 0x1;
}

void hal::clock::stopGpio(const pin_id&& pin)
{
    std::uint32_t gpclk;
    if (pin == 21) gpclk = 0;
    else if (pin == 23) gpclk = 1;
    else if (pin == 24) gpclk = 2;
    else if (pin == 25) gpclk = 3;

    bsp::rp2040::s_clocks.gpio[gpclk].control.enable = 0x0;
}

uint32_t hal::clock::getHz()
{
    return freq;
}