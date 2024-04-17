#include <cstdint>
#include <cstddef>
#include <array>

#include "hal.hpp"
//#include "ln298n.hpp"
#include "rp2040.hpp"

#include "experiments/uart.hpp"
#include "experiments/i2c.hpp"

using namespace hal;
using namespace hal::pins;
//using namespace drivers;

uint32_t freq = clock::getHz();

void sleep(const uint32_t ms)
{
    hal::system::delay((ms / 1000000) * freq);
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

int main(void)
{
    // Reset system to clean state
    system::init();

    clock::init();

    //init_xsoc();

    //pwmMain();

    // Setup SYS PLL for 12 MHz * 133 / 6 / 2 = 133 MHz
    //init_pll_sys(1, 133, 6, 2);
    //init_pll_sys(1, 100, 6, 1);
    
    // Setup SYS PLL for 12 MHz * 120 / 6 / 5 = 48 MHz
    //init_pll_sys(1, 120, 6, 5);
    //freq = freq_48mhz;

    // Setup USB PLL for 12 MHz * 120 / 6 / 5 = 48 MHz
    //init_pll_usb(1, 120, 6, 5);

    //setup_clocks();

    //i2cMain();
    uartMain();

    hal::spi::init(4, 5, 6, (33 * 1000 * 1000));

    etl::format_spec format;
    format.hex().width(8).fill('0');

    etl::string<8> str;
    etl::to_string(8, str, format);

    uart::send(str);

    // Registry check
    //if (reinterpret_cast<uint32_t>(&bsp::rp2040::s_uart_0.dmacr) != 0x40034000 + 0x048)
    //    return 0;

    gpio::setupPin(14, pindir::out, pinfunc::SIO);
    gpio::writePin(14, true);

    // Blink 182
    while (true)
    {
        sleep(30 * 1000000);
        gpio::togglePin(14);
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