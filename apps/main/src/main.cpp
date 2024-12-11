#include <cstdint>
#include <cstddef>
#include <array>

#include "etl/vector.h"

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

void print_hex(const std::uint32_t num)
{
    etl::format_spec format;
    format.hex().width(8).fill('0');

    etl::string<8> value;
    etl::to_string(num, value, format);
    uart::send(value);
}

static std::uint32_t null;

int main(void)
{
    // Reset system to clean state
    system::init();

    clock::init();

    //init_xsoc();

    //pwmMain();

    //i2cMain();
    uartMain();

    hal::spi::init(10, 9, 11, 8, (33 * 1000 * 1000)); // Init SPI to read flash

    //bsp::rp2040::s_spi_1.dr.data = 0x9F; // Wake up
    //bsp::rp2040::s_spi_1.dr.data = 0x00; // Wake up
    //bsp::rp2040::s_spi_1.dr.data = 0x00; // Wake up
    //bsp::rp2040::s_spi_1.dr.data = 0x05; // Read Status

    etl::array<std::uint8_t, 6> msg{0x9F, 0x0, 0x0, 0x0, 0x0, 0x0};
    etl::array<std::uint8_t, 6> msgRcv{};

    hal::spi::writeAndRead<std::uint8_t, 6, 6>(msg, msgRcv);

    //sleep(2);

    uart::send("Info: ");
    print_hex(bsp::rp2040::s_dma.ch[1].ctrl.en);
    print_hex(bsp::rp2040::s_dma.ch[1].ctrl.busy);
    print_hex(bsp::rp2040::s_spi_1.sr.rne);
    uart::send("Data: ");
    for (size_t i = 0; i < msgRcv.size(); i++)
    {
        //print_hex(bsp::rp2040::s_spi_1.sr.rne);
        //print_hex(bsp::rp2040::s_spi_1.dr.data);
        print_hex(msgRcv.at(i));
        //sleep(10);
    }
    //print_hex(bsp::rp2040::s_spi_1.cpsr.cpsdvsr);
    //print_hex(bsp::rp2040::s_spi_1.cr0.scr);
    uart::send("End");
    print_hex(bsp::rp2040::s_spi_1.sr.rne);
    uart::send("");
    /*
    */

    sleep(1);
    //gpio::writePin(9, true);

    //bsp::rp2040::s_dma.
    auto regAddr = reinterpret_cast<uint32_t>(&bsp::rp2040::s_spi_1.cr1);

    print_hex(regAddr);
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