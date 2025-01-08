#include "experiments/pwm.hpp"

using namespace hal;
using namespace hal::pins;

void pwmMain()
{
    hal::pwn pwm = hal::pwn::getInstance(hal::pwn_id::pwn0);

    // Setup LedPin2 as PWM
    gpio::setupPin(LedPin, pindir::out, pinfunc::PWM);
    pwm.enable(LedPin);

    // PWM
    while (true)
    {
        for (auto rb = 0x0000; rb < 0x10000; rb++)
        {
            pwm.writeCompare(LedPin, rb);
            system::delay(0x10 / 2);
        }
    }
}