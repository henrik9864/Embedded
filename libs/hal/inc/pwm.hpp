#pragma once

#include <cstdint>
#include <cstddef>
#include <array>
#include "pins.hpp"

namespace hal
{
    class pwm
    {
    public:
        static void enable(const pins::pin_id&& pin);
        static void disable(const pins::pin_id&& pin);

        static void writeCompare(const pins::pin_id&& pin, uint32_t value);
        static void writeWrap(const pins::pin_id&& pin, uint32_t value);
    };
}