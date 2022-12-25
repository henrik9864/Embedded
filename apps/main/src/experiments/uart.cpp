#include "experiments/uart.hpp"

using namespace hal;

void setup_uart_clocks()
{
    // Disable resus that my have been enabled.
    bsp::rp2040::s_clocks.sys_resus.control.enable = 0x0;

    bsp::rp2040::s_clocks.ref.control.src = 0x2; // Set ref clk src to xsoc

    bsp::rp2040::s_clocks.sys.control.src = 0x0; // Set sys src to pll_sys
    bsp::rp2040::s_clocks.sys.control.auxsrc = 0x0; // Set sys auxsrc to pll_sys
    bsp::rp2040::s_clocks.sys.div.integer = 0x1; // Reset div
}

void uartMain()
{
    setup_uart_clocks();

    while (true)
    {
        system::delay(1);
    }
}