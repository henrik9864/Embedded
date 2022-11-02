#pragma once

#include <cstdint>

#include "pins.hpp"

namespace hal
{
    // TODO: Mabye move into hal class?
    void put(const uint32_t a1, const uint32_t a2)
    {
        *reinterpret_cast<uint32_t*>(a1) = a2;
    }

    uint32_t get(const uint32_t a1)
    {
        return *reinterpret_cast<uint32_t*>(a1);
    }

    volatile void delay(const uint32_t a1)
    {
        for (size_t i = 0; i < a1; i++)
        {
            __asm("NOP");
        }
    }

    class system
    {
    public:
        static void init();
    };
}