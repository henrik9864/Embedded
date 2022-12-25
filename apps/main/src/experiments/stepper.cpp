#include "experiments/stepper.hpp"

using namespace hal;
using namespace hal::pins;

void stepperMain()
{
    // Setup led pin
    gpio::setupPin(std::move(LedPin), pindir::out, pinfunc::SIO);

    // Setup stepper pins as out
    gpio::setupPin(std::move(StepperC0), pindir::out, pinfunc::SIO);
    gpio::setupPin(std::move(StepperC1), pindir::out, pinfunc::SIO);
    gpio::setupPin(std::move(StepperC2), pindir::out, pinfunc::SIO);
    gpio::setupPin(std::move(StepperC3), pindir::out, pinfunc::SIO);

	// Setup stepper driver
	drivers::LN298NDriver driver(StepperC0, StepperC1, StepperC2, StepperC3);

    const uint32_t spd = 1;

    // Stepper motor
    while (true)
    {
        if (!gpio::readPin(15))
        {
            system::delay(1000 / spd);
            continue;
        }

        gpio::togglePin(std::move(LedPin));

        driver.stepForward();
        system::delay(1000 / spd);
    }
}