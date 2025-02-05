#include <cstdint>
#include <cstddef>
#include <array>

#include "etl/vector.h"

#include "hal.hpp"
//#include "ln298n.hpp"
#include "rp2040.hpp"

#include "w25q32.hpp"

#include "experiments/uart.hpp"
#include "experiments/i2c.hpp"

using namespace hal;
using namespace hal::pins;
//using namespace drivers;

uint32_t freq = clock::getHz();

void sleep(const uint32_t ms)
{
    //hal::system::delay((ms / 1000000) * freq);
    hal::system::delay((freq / 1000) * ms);
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

void fpga_init()
{
    gpio::setupPin(24, pindir::out, pinfunc::CLOCK);
}

void print_hex(hal::uart uart, const std::uint32_t num)
{
    etl::format_spec format;
    format.hex().width(8).fill('0');

    etl::string<8> value;
    etl::to_string(num, value, format);
    uart.send(value);
}

int main(void)
{
    hal::spi spi = hal::spi::getInstance(hal::spi_id::spi1);
    hal::uart uart = hal::uart::getInstance(hal::uart_id::uart0);

    // Reset system to clean state
    system::init();

    clock::init();

    //init_xsoc();

    //pwmMain();

    //i2cMain();
    //uartMain();

    uart.enable(0, 1, 115200);

    //hal::spi::init(10, 9, 11, 8, (33 * 1000 * 1000)); // Init SPI to read flash
    spi.init(10, 9, 11, 8, (33 * 1000 * 1000)); // Init SPI to read flash

    /*
    etl::array<std::uint8_t, 1> msg{0x06};
    etl::array<std::uint8_t, 1> msgRcv{};
    hal::spi::writeAndRead<std::uint8_t, 1, 1>(msg, msgRcv);

    sleep(2);

    etl::array<std::uint8_t, 6> msg2{ 0x02, 0x0, 0x0, 0x00, 0x1, 0x1 };
    etl::array<std::uint8_t, 6> msgRcv2{};
    hal::spi::writeAndRead<std::uint8_t, 6, 6>(msg2, msgRcv2);

    sleep(2);

    etl::array<std::uint8_t, 6> msg3{ 0x9F, 0x0, 0x0, 0x00, 0x0, 0x0 };
    etl::array<std::uint8_t, 6> msgRcv3{};
    hal::spi::writeAndRead<std::uint8_t, 6, 6>(msg3, msgRcv3);
    */

    /*
    etl::array<std::uint8_t, 6> msg3{ 0x9F, 0x0, 0x0, 0x00, 0x0, 0x0 };
    etl::array<std::uint8_t, 6> msgRcv3{};
    spi.writeAndRead<std::uint8_t, 6, 6>(msg3, msgRcv3);

    uart.send("Info: ");
    print_hex(uart, bsp::rp2040::s_dma.ch[1].ctrl.en);
    print_hex(uart, bsp::rp2040::s_dma.ch[1].ctrl.busy);
    print_hex(uart, bsp::rp2040::s_spi_1.sr.rne);
    uart.send("Data: ");
    for (size_t i = 0; i < msgRcv3.size(); i++)
    {
        //print_hex(bsp::rp2040::s_spi_1.sr.rne);
        //print_hex(bsp::rp2040::s_spi_1.dr.data);
        print_hex(uart, msgRcv3.at(i));
        //sleep(10);
    }
    //print_hex(bsp::rp2040::s_spi_1.cpsr.cpsdvsr);
    //print_hex(bsp::rp2040::s_spi_1.cr0.scr);
    uart.send("End");
    print_hex(uart, bsp::rp2040::s_spi_1.sr.rne);
    uart.send("");
    */

    drivers::flash::w25q32 flash{ spi };
    drivers::flash::flash_info info = flash.read_info();

    flash.write_enable();
    drivers::flash::flash_status status = flash.read_status();

    uart.send("Info: ");
    print_hex(uart, info.manufacture_id);
    print_hex(uart, info.device_id);

    uart.send("Status: ");
    print_hex(uart, status.busy);
    print_hex(uart, status.write_enable);

    //etl::array<std::uint8_t, 1> data = { 0xFA };
    //flash.write_bytes<1>(0, data);

    auto bytes = flash.read_bytes<8>(0);

    uart.send("Bytes: ");
    for (size_t i = 0; i < bytes.size(); i++)
    {
        print_hex(uart, bytes.at(i));
    }

    sleep(1);
    //gpio::writePin(9, true);

    //bsp::rp2040::s_dma.
    auto regAddr = reinterpret_cast<uint32_t>(&bsp::rp2040::s_spi_1.cr1);

    print_hex(uart, regAddr);
    /*
    etl::format_spec format;
    format.hex().width(8).fill('0');

    etl::string<8> str;
    etl::to_string(regAddr, str, format);

    uart::send(str);
    */

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