#include <cstdint>
#include <cstddef>
#include <array>

#include "hal.hpp"
#include "rp2040.hpp"

using namespace hal;
using namespace hal::pins;

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
const uint32_t freq_noe = 0x10000000;

const uint32_t freq = freq_48mhz;

void sleep(const uint32_t ns)
{
    hal::delay((ns / 1000000000) * freq);
}

void blink()
{
    bsp::rp2040::s_sio.gpio_out_set = 1 << 25;
    hal::delay(freq);

    bsp::rp2040::s_sio.gpio_out_clr = 1 << 25;
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

void setup_pio()
{
    // Reset state machines
    //s_pio_0.control.sm_restart = 0x1;
    //s_pio_0.control.clkdiv_restart = 0x1;

    //s_pio_0.fdebug.rxstall = 0x0;
    //s_pio_0.fdebug.rxunder = 0x0;
    //s_pio_0.fdebug.txover = 0x0;
    //s_pio_0.fdebug.txstall = 0x0;

    // Load blink PIO program
    bsp::rp2040::s_pio_0.instr_mem[0] = 0xe081;
    bsp::rp2040::s_pio_0.instr_mem[1] = 0xfe01;
    bsp::rp2040::s_pio_0.instr_mem[2] = 0xfd00;
    bsp::rp2040::s_pio_0.instr_mem[3] = 0x0001;
}

void setup_sm0()
{
    bsp::rp2040::s_pio_0.sm[0].clkdiv.integer = 0xFFFF;
    bsp::rp2040::s_pio_0.sm[0].pinctrl.set_count = 1;
    bsp::rp2040::s_pio_0.sm[0].pinctrl.set_base = 14;
}

int main(void)
{
    // Reset system to clean state
    system::init();

    //init_xsoc();

    // Setup SYS PLL for 12 MHz * 133 / 6 / 2 = 133 MHz
    //init_pll_sys(1, 133, 6, 2);
    //init_pll_sys(1, 100, 6, 1);
    
    // Setup SYS PLL for 12 MHz * 120 / 6 / 5 = 48 MHz
    //init_pll_sys(1, 120, 6, 5);

    // Setup USB PLL for 12 MHz * 120 / 6 / 5 = 48 MHz
    //init_pll_usb(1, 120, 6, 5);

    //setup_clocks();

    //const uint32_t WS28Pin = 16;
    const uint32_t WS28Pin = 14;
    const uint32_t LedPin2 = 14;
    const uint32_t LedPin = 8;

    const uint32_t StepperC0 = 3;
    const uint32_t StepperC1 = 4;
    const uint32_t StepperC2 = 5;
    const uint32_t StepperC3 = 6;

    // Setup pin 16 and 25(WS2812B and LED) as out
    gpio::setupPin(std::move(LedPin), pindir::out, pinfunc::SIO);
    gpio::setupPin(25, pindir::out, pinfunc::SIO);

    // Setup stepper pins as out
    gpio::setupPin(std::move(StepperC0), pindir::out, pinfunc::SIO);
    gpio::setupPin(std::move(StepperC1), pindir::out, pinfunc::SIO);
    gpio::setupPin(std::move(StepperC2), pindir::out, pinfunc::SIO);
    gpio::setupPin(std::move(StepperC3), pindir::out, pinfunc::SIO);


    // Setup LedPin2 and WS28Pin as pio out pins.
    //gpio::setupPin(std::move(LedPin2), pindir::out, pinfunc::PIO0);
    gpio::setupPin(std::move(WS28Pin), pindir::out, pinfunc::PIO0);

    // Setup LedPin2 as PWM
    gpio::setupPin(std::move(LedPin2), pindir::out, pinfunc::PWM);
    pwm::enable(std::move(LedPin2));

    const std::array<uint32_t, 24> arr = { 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0 };
    //const std::array<uint32_t, 24> arr = { 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0 };

    setup_pio();
    setup_sm0();

    // Enable PIO 0
    bsp::rp2040::s_pio_0.control.sm_enable = 15; // Enable all cores!!!!

    // Registry check
    if (reinterpret_cast<uint32_t>(&s_pwm.ints) != 0x40050000 + 0xb0)
        return 0;

    const uint32_t spd = 4;

    while (true)
    {
        gpio::writePin(std::move(StepperC0), 1);
        gpio::writePin(std::move(StepperC1), 0);
        gpio::writePin(std::move(StepperC2), 1);
        gpio::writePin(std::move(StepperC3), 0);

        delay(1000 / spd);

        gpio::writePin(std::move(StepperC0), 0);
        gpio::writePin(std::move(StepperC1), 1);
        gpio::writePin(std::move(StepperC2), 1);
        gpio::writePin(std::move(StepperC3), 0);

        delay(1000 / spd);

        gpio::writePin(std::move(StepperC0), 0);
        gpio::writePin(std::move(StepperC1), 1);
        gpio::writePin(std::move(StepperC2), 0);
        gpio::writePin(std::move(StepperC3), 1);

        delay(1000 / spd);

        gpio::writePin(std::move(StepperC0), 1);
        gpio::writePin(std::move(StepperC1), 0);
        gpio::writePin(std::move(StepperC2), 0);
        gpio::writePin(std::move(StepperC3), 1);

        delay(1000 / spd);
    }
    

    // PWM
    while (true)
    {
        for(auto rb = 0x0000; rb < 0x10000; rb++)
        {
            pwm::writeCompare(std::move(LedPin2), rb);
            delay(0x10 / 2);
        }
    }

    // Blink 182
    while (true)
    {
        gpio::togglePin(std::move(LedPin));
        delay(100000);

        gpio::togglePin(std::move(LedPin));
        delay(100000);
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