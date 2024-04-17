#include "experiments/uart.hpp"

using namespace hal;
using namespace hal::pins;

void setup_uart_clocks()
{
    // Disable resus that my have been enabled.
    bsp::rp2040::s_clocks.sys_resus.control.enable = 0x0;

    bsp::rp2040::s_clocks.ref.control.src = 0x2; // Set ref clk src to xsoc

    bsp::rp2040::s_clocks.sys.control.src = 0x0; // Set sys src to ref
    bsp::rp2040::s_clocks.sys.control.auxsrc = 0x0; // Set sys auxsrc to pll_sys
    bsp::rp2040::s_clocks.sys.div.integer = 0x1; // Reset div

    bsp::rp2040::s_clocks.peripheral.control.enable = 0x1; // Enable peri clock
    bsp::rp2040::s_clocks.peripheral.control.auxsrc = 0x4; // Set auxsrc to xosc
}

void uartMain()
{
    //setup_uart_clocks();

    uart::enable(0, 1);

    /*
    while (true)
    {
        for (size_t i = 0; i < 10; i++)
        {
            uart::send("wow3");
            system::delay(12000000 / 10);
        }
    }
    */
}