#pragma once

#include "pwm.hpp"

using namespace bsp::rp2040;
using namespace hal::pins;

enum class pwm_channel
{
    A,
    B
};

uint32_t getPwmSlice(const pin_id&& pin)
{
    return pin / 2;
}

pwm_channel getPwmChannel(const pin_id&& pin)
{
    return pin % 2 == 0 ? pwm_channel::A : pwm_channel::B;
}

void hal::pwm::enable(const pin_id&& pin)
{
    s_pwm.ch[getPwmSlice(std::move(pin))].csr.en = 1;
}

void hal::pwm::disable(const pin_id&& pin)
{
    s_pwm.ch[getPwmSlice(std::move(pin))].csr.en = 0;
}

void hal::pwm::writeCompare(const pins::pin_id&& pin, uint32_t value)
{
    if (getPwmChannel(std::move(pin)) == pwm_channel::A)
    {
        s_pwm.ch[getPwmSlice(std::move(pin))].cc.a = value;
    }
    else if (getPwmChannel(std::move(pin)) == pwm_channel::B)
    {
        s_pwm.ch[getPwmSlice(std::move(pin))].cc.b = value;
    }
}

void hal::pwm::writeWrap(const pins::pin_id&& pin, uint32_t value)
{
    s_pwm.ch[getPwmSlice(std::move(pin))].top.counter_wrap = value;
}