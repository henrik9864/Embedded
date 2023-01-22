#include "rp2040_uart.hpp"

using namespace hal::pins;

void hal::uart::enable(const pins::pin_id&& tx, const pins::pin_id&& rx)
{
    // (12000000 / ( 16 / 115200 )) = 6.514
    // 0.514 * 64 = 32.666
    bsp::rp2040::s_uart_0.ibrd.baud_divint = 6;
    bsp::rp2040::s_uart_0.fbrd.baud_divfrac = 33;

    bsp::rp2040::s_uart_0.lcr_h.fen = 1; // Enable fifo
    bsp::rp2040::s_uart_0.lcr_h.wlen = 0b11; // Set 8 data bits

    bsp::rp2040::s_uart_0.cr.rxe = 1; // Enable receive
    bsp::rp2040::s_uart_0.cr.txe = 1; // Enable transmit
    bsp::rp2040::s_uart_0.cr.uarten = 1; // Enable uart

    gpio::setupPin(std::move(tx), pindir::out, pinfunc::UART);
    gpio::setupPin(std::move(rx), pindir::out, pinfunc::UART);
}

void hal::uart::send(uint32_t data)
{
    while (bsp::rp2040::s_uart_0.fr.txff != 0) {};

    bsp::rp2040::s_uart_0.dr.data = data;
}


void hal::uart::send(etl::string_view str)
{
    for (size_t i = 0; i < str.length(); i++)
    {
        hal::uart::send(str.at(i));
    }

    hal::uart::send(0x0D);
    hal::uart::send(0x0A);
}

uint32_t hal::uart::recv()
{
    while (bsp::rp2040::s_uart_0.fr.rxfe != 0) {};

    return bsp::rp2040::s_uart_0.dr.data;
}