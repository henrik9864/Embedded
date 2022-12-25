#include "experiments/pwm.hpp"

using namespace hal;
using namespace hal::pins;

void pwmMain()
{
    // Setup LedPin2 as PWM
    gpio::setupPin(std::move(LedPin), pindir::out, pinfunc::PWM);
    pwm::enable(std::move(LedPin));

    // PWM
    while (true)
    {
        for (auto rb = 0x0000; rb < 0x10000; rb++)
        {
            pwm::writeCompare(std::move(LedPin), rb);
            system::delay(0x10 / 2);
        }
    }
}