#pragma once

#include <cstdint>

#include "pins.hpp"

namespace hal
{
    class system
    {
    public:
        static void init();

        static void put(const uint32_t a1, const uint32_t a2);
        static uint32_t get(const uint32_t a1);
        static volatile void delay(const uint32_t a1);
    };
}